#include "AbstractProfileTarget.h"
#include "RealJoysticksManager.h"
#include "EnhancedJoystick.h"
#include "RemoteJoystickServer.h"
#include "VirtualJoystick.h"
#include "MAPPINGS/Mappings.h"
#include "TRIGGERS/Triggers.h"
#include "ACTIONS/Actions.h"

#include <QCoreApplication>
#include <vector>


///////////////////////////////////////////////////////////////////////////////
//  CONSTRUCTEUR ET DESTRUCTEUR
//  PLAY
//  STOP
//  RUN
//  IS INIT COMPLETE
//
//  REGISTER REAL JOYSTICK
//  REGISTER REMOTE JOYSTICK
//  SLOT REMOTE JOYSTICK CONNECTED
//  REGISTER VIRTUAL JOYSTICK
//  REGISTER LAYER DIM 1
//  REGISTER LAYER DIM 2
//
//  PROCESS PENDING MAPPINGS REQUESTS
//  DO ACTION
//  START REXEC
//  STOP REXEC
//
//  ADD MAPPING
//  MAP
//  MAP BUTTON
//  MAP BUTTON TEMPO
//  MAP AXIS
//  MAP AXIS RELATIVE
//  MAP AXIS 1
//  MAP AXIS 2
//  MAP MERGE AXES
//  MAP SPLIT AXIS
//  MAP POV
//
//  UNMAP ALL
//  UNMAP BUTTON
//  UNMAP AXIS
//  UNMAP POV
//  UNMAP REXEC
///////////////////////////////////////////////////////////////////////////////


// CONSTRUCTEUR ET DESTRUCTEUR ////////////////////////////////////////////////
AbstractProfileTarget::AbstractProfileTarget() : AbstractProfile{}, m_eventsQueue{this}
{
	m_isProcessingEvents = false;
	m_bFirstStep = true;
}

AbstractProfileTarget::~AbstractProfileTarget()
{
	this->stop();
}

// PLAY ///////////////////////////////////////////////////////////////////////
bool AbstractProfileTarget::play()
{
	m_bFirstStep = true;
	return this->setupJoysticks();
}

// STOP ///////////////////////////////////////////////////////////////////////
void AbstractProfileTarget::stop()
{
	this->UnmapAll();
	
	m_mappingsRequests.clear();
	m_layerCalculator.clear();
	m_changes.clear();
	
	qDeleteAll(m_realJoysticks);
	qDeleteAll(m_virtualJoysticks);
	m_remoteJoysticks.clear();
	m_realJoysticks.clear();
	m_virtualJoysticks.clear();
}

// RUN ////////////////////////////////////////////////////////////////////////
void AbstractProfileTarget::run()
{
	// retrieve the changes of each real joystick
	for (AbstractRealJoystick *rj : m_realJoysticks)
	{
		rj->readGameController();
		m_changes << rj->changes();
	}
	
	// first run
	if (m_bFirstStep)
	{
		m_bFirstStep = false;
		this->runFirstStep();
		// flush virtual then real joysticks
		for (VirtualJoystick *vj : m_virtualJoysticks) {vj->flush();} // send HID report to vJoy devices
		for (AbstractRealJoystick *rj : m_realJoysticks) {rj->flush();} // implementation defined
		m_changes.clear();
		return;
	}
	
	// process layers changes
	m_layerCalculator.computeLayer();
	Layer currentLayer = m_layerCalculator.layer();
	if (m_layerCalculator.layerChanged())
	{
		for (AbstractMapping *m : m_mappings)
		{m->setLayer(currentLayer);}
	}
	
	// analyse real joysticks events to generate virtual joysticks events
	m_isProcessingEvents = true;
	for (const JoystickChange &ch : m_changes)
	{
		for (AbstractMapping *m : m_mappings)
		{
			if (m->reactsToChanges() && m->isActiveInLayer(currentLayer) && m->isTriggered(ch))
			{m->performAction(ch);}
		}
	}
	
	// browse all triggers that can reacts even when there is no event
	for (AbstractMapping *m : m_mappings)
	{
		if (m->reactsToStates() && m->isActiveInLayer(currentLayer) && m->isTriggered())
		{m->performAction();}
	}
	m_isProcessingEvents = false;
	
	// process events:
	//     - keyboard events are sent immediatly
	//     - for virtual joysticks, perform only setButton and setAxis
	m_eventsQueue.processEvents();
	
	// flush virtual then real joysticks
	for (VirtualJoystick *vj : m_virtualJoysticks) {vj->flush();} // send HID report to vJoy devices
	for (AbstractRealJoystick *rj : m_realJoysticks) {rj->flush();} // implementation defined
	
	// the end
	m_changes.clear();
	this->processPendingMappingsRequests();
}

// IS INIT COMPLETE ///////////////////////////////////////////////////////////
bool AbstractProfileTarget::isInitComplete() const
{
	auto isConnected = [] (RemoteJoystickServer *rjs) {return rjs->isConnected();};
	return std::all_of(m_remoteJoysticks.begin(),m_remoteJoysticks.end(),isConnected);
}





// REGISTER REAL JOYSTICK /////////////////////////////////////////////////////
EnhancedJoystick* AbstractProfileTarget::registerRealJoystick(const QString &description, int num)
{
	RealJoysticksManager *rjm = this->realJoysticksManager();
	if (!rjm) {return nullptr;}
	
	AbstractRealJoystick *rj = rjm->joystick(description,num);
	if (!rj) {return nullptr;}
	
	EnhancedJoystick *erj = new EnhancedJoystick{rj,false};
	m_realJoysticks.push_back(erj);
	return erj;
}

// REGISTER REMOTE JOYSTICK ///////////////////////////////////////////////////
EnhancedJoystick* AbstractProfileTarget::registerRemoteJoystick(RemoteJoystickServer *rjs)
{
	if (!rjs) {return nullptr;}
	
	QObject::connect(rjs, SIGNAL(connected()),    this, SLOT(slotRemoteJoystickConnected()));
	QObject::connect(rjs, SIGNAL(disconnected()), this, SIGNAL(remoteJoystickDisconnected()));
	EnhancedJoystick *erj = new EnhancedJoystick{rjs,true};
	m_realJoysticks.push_back(erj);
	m_remoteJoysticks.push_back(rjs);
	return erj;
}

// SLOT REMOTE JOYSTICK CONNECTED /////////////////////////////////////////////
void AbstractProfileTarget::slotRemoteJoystickConnected()
{
	if (this->isInitComplete())
		emit asyncInitComplete();
}

// REGISTER VIRTUAL JOYSTICK //////////////////////////////////////////////////
VirtualJoystick* AbstractProfileTarget::registerVirtualJoystick(uint id)
{
	try
	{
		VirtualJoystick *vj = new VirtualJoystick{id};
		QObject::connect(vj, SIGNAL(message(QString,QColor)), this, SIGNAL(message(QString,QColor)));
		m_virtualJoysticks.push_back(vj);
		return vj;
	}
	catch (std::exception &e)
	{
		emit message(e.what(),Qt::red);
		return nullptr;
	}
}

// REGISTER LAYER DIM 1 ///////////////////////////////////////////////////////
void AbstractProfileTarget::registerLayerDim1(Layers::LayerDim1 layer1, AbstractRealJoystick *rj, uint rButton)
{
	m_layerCalculator.registerLayerDim1(layer1,rj,rButton);
}

// REGISTER LAYER DIM 2 ///////////////////////////////////////////////////////
void AbstractProfileTarget::registerLayerDim2(Layers::LayerDim2 layer2, AbstractRealJoystick *rj, uint rButton)
{
	m_layerCalculator.registerLayerDim2(layer2,rj,rButton);
}






// PROCESS PENDING MAPPINGS REQUESTS //////////////////////////////////////////
void AbstractProfileTarget::processPendingMappingsRequests()
{
	for (const MappingModifRequest &r : m_mappingsRequests)
	{
		if (r.type == MappingModifRequestType::RequestUnmapAll)         {this->UnmapAll();}
		else if (r.type == MappingModifRequestType::RequestUnmapButton) {this->UnmapButton(r.rj,r.rnum);}
		else if (r.type == MappingModifRequestType::RequestUnmapAxis)   {this->UnmapAxis(r.rj,r.rnum);}
		else if (r.type == MappingModifRequestType::RequestUnmapPov)    {this->UnmapPov(r.rj,r.rnum);}
		else if (r.type == MappingModifRequestType::RequestUnmapRexec)  {this->UnmapRexec(r.rnum);}
		else if (r.type == MappingModifRequestType::RequestAddMapping)  {this->addMapping(r.mapping);}
	}
	
	m_mappingsRequests.clear();
}

// DO ACTION //////////////////////////////////////////////////////////////////
void AbstractProfileTarget::DoAction(AbstractAction *action, bool deleteWhenDone)
{
	Q_ASSERT(action);
	m_eventsQueue.postEvents(action->generateEvents());
	if (deleteWhenDone) {delete action;}
}

// START REXEC ////////////////////////////////////////////////////////////////
bool AbstractProfileTarget::startRexec(uint id, uint cycles, AbstractAction *action)
{
	if (id == -1u) {return false;}					// this id is reserved
	if (m_rexecIds.contains(id)) {return false;}	// only one rexec per id
	
	// the user (profile programmer) must be careful to delete this action in his profile to avoid a memory leak
	this->addMapping(new MappingRexec{id,cycles,action,m_eventsQueue});
	m_rexecIds << id;
	return true;
}

bool AbstractProfileTarget::startRexec(uint id, uint cycles, std::function<void()> fct)
{
	if (id == -1u) {return false;}					// this id is reserved
	if (m_rexecIds.contains(id)) {return false;}	// only one rexec per id
	
	// this action (created below from the functor) is deleted when stopRexec is called with this id
	ActionCallback *action = new ActionCallback{fct};
	this->addMapping(new MappingRexec{id,cycles,action,m_eventsQueue});
	m_rexecFunctionsActionsToDelete.insert(std::make_pair(id,action));
	m_rexecIds << id;
	return true;
}

// STOP REXEC /////////////////////////////////////////////////////////////////
bool AbstractProfileTarget::stopRexec(uint id)
{
	if (id == -1u) {return false;}					// this id is reserved
	if (!m_rexecIds.contains(id)) {return false;}	// no rexec mapping with this id
	
	this->UnmapRexec(id);
	m_rexecIds.removeAll(id);
	if (m_rexecFunctionsActionsToDelete.count(id) > 0) {delete m_rexecFunctionsActionsToDelete.extract(id).mapped();}
	return true;
}






// ADD MAPPING ////////////////////////////////////////////////////////////////
void AbstractProfileTarget::addMapping(AbstractMapping *m)
{
	Q_ASSERT(m);
	
	try
	{
		if (!m_isProcessingEvents)
		{
			m_mappings << m; // add it directly
			if (m->isMappingRexec(-1u)) {m->performAction();} // if it comes from a rexec, we execute it right away (we don't wait next step)
		}
		else
		{
			m_mappingsRequests.push_back(MappingModifRequest{MappingModifRequestType::RequestAddMapping,nullptr,0,m}); // add it in a queue, waiting for the current loop to end
		}
	}
	catch (std::exception &e) {emit message(e.what(),Qt::red);}
}

// MAP ////////////////////////////////////////////////////////////////////////
void AbstractProfileTarget::Map(AbstractRealJoystick *rj, ControlType type, uint rnum, LayersCombo lc, AbstractTrigger *trig, AbstractAction *act)
{
	this->addMapping(new MappingStandard{rj,type,rnum,lc,trig,act,m_eventsQueue});
}

// MAP BUTTON /////////////////////////////////////////////////////////////////
void AbstractProfileTarget::MapButton(AbstractRealJoystick *rj, uint rButton, LayersCombo lc, VirtualJoystick *vj, uint vButton)
{
	this->addMapping(new MappingStandard{rj,ControlType::Button,rButton,lc,
						new TriggerButtonChange{},
						new ActionButtonSetChange{vj,vButton},
						m_eventsQueue});
}

// MAP BUTTON TEMPO ///////////////////////////////////////////////////////////
void AbstractProfileTarget::MapButtonTempo(AbstractRealJoystick *rj, uint rButton, LayersCombo lc, uint cycles, AbstractAction *action1, AbstractAction *action2)
{
	this->addMapping(new MappingTempo{rj,rButton,lc,cycles,action1,action2,m_eventsQueue});
}

// MAP AXIS ///////////////////////////////////////////////////////////////////
void AbstractProfileTarget::MapAxis(AbstractRealJoystick *rj, uint rAxis, LayersCombo lc, VirtualJoystick *vj, uint vAxis, AxisDirection d)
{
	this->addMapping(new MappingStandard{rj,ControlType::Axis,rAxis,lc,
					new TriggerAxisChange{},
					new ActionAxisSetChange{vj,vAxis,d},
					m_eventsQueue});
}

// MAP AXIS RELATIVE //////////////////////////////////////////////////////////
void AbstractProfileTarget::MapAxisRelative(AbstractRealJoystick *rj, uint rAxis, LayersCombo lc, VirtualJoystick *vj, uint vAxis, float timeMinToMax)
{
	this->addMapping(new MappingAxisRelative{rj,rAxis,lc,vj,vAxis,2*this->timeStep()/timeMinToMax,m_eventsQueue});
}

// MAP AXIS 1 /////////////////////////////////////////////////////////////////
void AbstractProfileTarget::MapAxis1(AbstractRealJoystick *rj, uint rAxis, LayersCombo lc, const std::vector<float> &points, AbstractAction *actionPlus, AbstractAction *actionMoins)
{
	if (points.size() == 0)
	{
		emit message("MapAxis1: nbPoints must be > 0",Qt::red);
		return;
	}
	
	this->addMapping(new MappingAxis1{rj,rAxis,lc,points,actionPlus,actionMoins,m_eventsQueue});
}

void AbstractProfileTarget::MapAxis1(AbstractRealJoystick *rj, uint rAxis, LayersCombo lc, uint nbPoints, AbstractAction *actionPlus, AbstractAction *actionMoins)
{
	if (nbPoints == 0)
	{
		emit message("MapAxis1: nbPoints must be > 0",Qt::red);
		return;
	}
	
	float pas = 2.0 / (float)nbPoints;
	std::vector<float> points(nbPoints);
	for (uint i=0; i<nbPoints; ++i) {points[i] = -1.0f + 0.5f*pas + i*pas;}
	this->addMapping(new MappingAxis1{rj,rAxis,lc,points,actionPlus,actionMoins,m_eventsQueue});
}

// MAP AXIS 2 /////////////////////////////////////////////////////////////////
void AbstractProfileTarget::MapAxis2(AbstractRealJoystick *rj, uint rAxis, LayersCombo lc, const std::vector<float> &points, const std::vector<AbstractAction*> actions)
{
	if (points.size() == 0 || actions.size() != points.size()+1)
	{
		emit message("MapAxis2: nbPoints must be > 0 && nbActions == nbPoints+1",Qt::red);
		return;
	}
	
	this->addMapping(new MappingAxis2{rj,rAxis,lc,points,actions,m_eventsQueue});
}

void AbstractProfileTarget::MapAxis2(AbstractRealJoystick *rj, uint rAxis, LayersCombo lc, uint nbPoints, const std::vector<AbstractAction*> actions)
{
	if (nbPoints == 0 || actions.size() != nbPoints+1)
	{
		emit message("MapAxis2: nbPoints must be > 0 && nbActions == nbPoints+1",Qt::red);
		return;
	}
	
	float pas = 2.0 / (float)nbPoints;
	std::vector<float> points(nbPoints);
	for (uint i=0; i<nbPoints; ++i) {points[i] = -1.0f + 0.5f*pas + i*pas;}
	this->addMapping(new MappingAxis2{rj,rAxis,lc,points,actions,m_eventsQueue});
}

// MAP MERGE AXES /////////////////////////////////////////////////////////////
void AbstractProfileTarget::MapMergeAxes(AbstractRealJoystick *rj1, uint rAxis1, float k1, AbstractRealJoystick *rj2, uint rAxis2, float k2, LayersCombo lc, VirtualJoystick *vj, uint vAxis, AbstractAxisCurve *curve)
{
	this->addMapping(new MappingMergeAxes{rj1, rAxis1, k1, rj2, rAxis2, k2, lc, vj, vAxis, curve, m_eventsQueue});
}

// MAP SPLIT AXIS /////////////////////////////////////////////////////////////
void AbstractProfileTarget::MapSplitAxis(AbstractRealJoystick *rj, uint rAxis, LayersCombo lc, VirtualJoystick *vj1, uint vAxis1, VirtualJoystick *vj2, uint vAxis2)
{
	this->addMapping(new MappingSplitAxis{rj, rAxis, lc, vj1, vAxis1, vj2, vAxis2, m_eventsQueue});
}

// MAP POV ////////////////////////////////////////////////////////////////////
void AbstractProfileTarget::MapPov(AbstractRealJoystick *rj, uint rPov, LayersCombo lc, VirtualJoystick *vj, uint vPov)
{
	this->addMapping(new MappingStandard{rj,ControlType::Pov,rPov,lc,
					new TriggerPovChange{},
					new ActionPovSetChange{vj,vPov},
					m_eventsQueue});
}






// UNMAP ALL //////////////////////////////////////////////////////////////////
void AbstractProfileTarget::UnmapAll()
{
	if (!m_isProcessingEvents)
	{
		qDeleteAll(m_mappings);
		m_mappings.clear();
	}
	else
	{
		m_mappingsRequests.push_back(MappingModifRequest{MappingModifRequestType::RequestUnmapAll,nullptr,0,nullptr}); // add it in a queue, waiting for the current loop to end
		for (AbstractMapping *m : m_mappings) {m->aboutToBeDeleted();}
	}
}

// UNMAP BUTTON ///////////////////////////////////////////////////////////////
void AbstractProfileTarget::UnmapButton(AbstractRealJoystick *rj, uint rButton)
{
	if (!m_isProcessingEvents)
	{
		int n = m_mappings.size();
		for (int i=n-1; i>=0; --i)
		{
			if (m_mappings[i]->isMappingButton(rj,rButton))
			{delete m_mappings.takeAt(i);}
		}
	}
	else
	{
		m_mappingsRequests.push_back(MappingModifRequest{MappingModifRequestType::RequestUnmapButton,rj,rButton,nullptr}); // add it in a queue, waiting for the current loop to end
		for (AbstractMapping *m : m_mappings)
		{
			if (m->isMappingButton(rj,rButton))
				m->aboutToBeDeleted();
		}
	}
}

// UNMAP AXIS /////////////////////////////////////////////////////////////////
void AbstractProfileTarget::UnmapAxis(AbstractRealJoystick *rj, uint rAxis)
{
	if (!m_isProcessingEvents)
	{
		int n = m_mappings.size();
		for (int i=n-1; i>=0; --i)
		{
			if (m_mappings[i]->isMappingAxis(rj,rAxis))
			{delete m_mappings.takeAt(i);}
		}
	}
	else
	{
		m_mappingsRequests.push_back(MappingModifRequest{MappingModifRequestType::RequestUnmapAxis,rj,rAxis,nullptr}); // add it in a queue, waiting for the current loop to end
		for (AbstractMapping *m : m_mappings)
		{
			if (m->isMappingAxis(rj,rAxis))
				m->aboutToBeDeleted();
		}
	}
}

// UNMAP POV //////////////////////////////////////////////////////////////////
void AbstractProfileTarget::UnmapPov(AbstractRealJoystick *rj, uint rPov)
{
	if (!m_isProcessingEvents)
	{
		int n = m_mappings.size();
		for (int i=n-1; i>=0; --i)
		{
			if (m_mappings[i]->isMappingPov(rj,rPov))
			{delete m_mappings.takeAt(i);}
		}
	}
	else
	{
		m_mappingsRequests.push_back(MappingModifRequest{MappingModifRequestType::RequestUnmapPov,rj,rPov,nullptr}); // add it in a queue, waiting for the current loop to end
		for (AbstractMapping *m : m_mappings)
		{
			if (m->isMappingPov(rj,rPov))
				m->aboutToBeDeleted();
		}
	}
}

// UNMAP REXEC ////////////////////////////////////////////////////////////////
void AbstractProfileTarget::UnmapRexec(uint id)
{
	if (!m_isProcessingEvents)
	{
		int n = m_mappings.size();
		for (int i=n-1; i>=0; --i)
		{
			if (m_mappings[i]->isMappingRexec(id))
			{delete m_mappings.takeAt(i);}
		}
	}
	else
	{
		m_mappingsRequests.push_back(MappingModifRequest{MappingModifRequestType::RequestUnmapRexec,nullptr,id,nullptr}); // add it in a queue, waiting for the current loop to end
		for (AbstractMapping *m : m_mappings)
		{
			if (m->isMappingRexec(id))
				m->aboutToBeDeleted();
		}
	}
}

