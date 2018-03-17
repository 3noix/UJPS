#include "AbstractProfile.h"
#include "VirtualJoystick.h"
#include "MAPPINGS/Mappings.h"
#include "TRIGGERS/Triggers.h"
#include "ACTIONS/Actions.h"
#include <vector>


///////////////////////////////////////////////////////////////////////////////
//  CONSTRUCTEUR ET DESTRUCTEUR
//  RESET
//
//  REGISTER REAL JOYSTICK
//  REGISTER VIRTUAL JOYSTICK
//  REGISTER LAYER DIM 1
//  REGISTER LAYER DIM 2
//
//  RUN ONE LOOP
//  PROCESS PENDING MAPPINGS REQUESTS
//  SET TIME STEP
//  MS 2 CYCLES
//
//  DO ACTION
//  ADD MAPPING
//  MAP
//  MAP BUTTON
//  MAP BUTTON TEMPO
//  MAP AXIS
//  MAP AXIS 1
//  MAP AXIS 2
//  MAP MERGE AXES
//
//  UNMAP ALL
//  UNMAP BUTTON
//  UNMAP AXIS
///////////////////////////////////////////////////////////////////////////////


// CONSTRUCTEUR ET DESTRUCTEUR ////////////////////////////////////////////////
AbstractProfile::AbstractProfile() : QObject()
{
	m_dtms = 15;
	m_isProcessingEvents = false;
}

AbstractProfile::~AbstractProfile()
{
	this->UnmapAll();
}

// RESET //////////////////////////////////////////////////////////////////////
void AbstractProfile::reset()
{
	this->UnmapAll();
	m_mappingsRequests.clear();
	m_layerCalculator.clear();
	m_changes.clear();
	m_realJoysticks.clear();
	m_virtualJoysticks.clear();
}








// REGISTER REAL JOYSTICK /////////////////////////////////////////////////////
void AbstractProfile::registerRealJoystick(AbstractRealJoystick *rj)
{
	m_realJoysticks.push_back(rj);
}

// REGISTER VIRTUAL JOYSTICK //////////////////////////////////////////////////
void AbstractProfile::registerVirtualJoystick(VirtualJoystick *vj)
{
	m_virtualJoysticks.push_back(vj);
}

// REGISTER LAYER DIM 1 ///////////////////////////////////////////////////////
void AbstractProfile::registerLayerDim1(Layers::LayerDim1 layer1, AbstractRealJoystick *rj, uint rButton)
{
	m_layerCalculator.registerLayerDim1(layer1,rj,rButton);
}

// REGISTER LAYER DIM 2 ///////////////////////////////////////////////////////
void AbstractProfile::registerLayerDim2(Layers::LayerDim2 layer2, AbstractRealJoystick *rj, uint rButton)
{
	m_layerCalculator.registerLayerDim2(layer2,rj,rButton);
}








// RUN ONE LOOP ///////////////////////////////////////////////////////////////
void AbstractProfile::runOneLoop()
{
	// retrieve the changes of each real joystick
	for (AbstractRealJoystick *rj : m_realJoysticks)
	{
		rj->readGameController();
		m_changes << rj->changes();
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
	
	// send a HID report to each virtual joystick
	for (VirtualJoystick *vj : m_virtualJoysticks) {vj->sendReport();}
	
	// the end
	m_changes.clear();
	this->processPendingMappingsRequests();
}

// PROCESS PENDING MAPPINGS REQUESTS //////////////////////////////////////////
void AbstractProfile::processPendingMappingsRequests()
{
	for (const MappingModifRequest &r : m_mappingsRequests)
	{
		if (r.type == MappingModifRequestType::RequestUnmapAll) {this->UnmapAll();}
		else if (r.type == MappingModifRequestType::RequestUnmapButton) {this->UnmapButton(r.rj,r.rnum);}
		else if (r.type == MappingModifRequestType::RequestUnmapAxis) {this->UnmapAxis(r.rj,r.rnum);}
		else if (r.type == MappingModifRequestType::RequestAddMapping) {this->addMapping(r.mapping);}
	}
	
	m_mappingsRequests.clear();
}

// SET TIME STEP //////////////////////////////////////////////////////////////
void AbstractProfile::setTimeStep(int dtms)
{
	Q_ASSERT(dtms > 0);
	m_dtms = dtms;
}

// MS 2 CYCLES ////////////////////////////////////////////////////////////////
uint AbstractProfile::ms2cycles(uint msecs) const
{
	Q_ASSERT(msecs > 0);
	return ((msecs%m_dtms) ? msecs/m_dtms+1 : msecs/m_dtms);
}







// DO ACTION //////////////////////////////////////////////////////////////////
void AbstractProfile::DoAction(AbstractAction *action, bool deleteWhenDone)
{
	Q_ASSERT(action);
	m_eventsQueue.postEvents(action->generateEvents());
	if (deleteWhenDone) {delete action;}
}

// ADD MAPPING ////////////////////////////////////////////////////////////////
void AbstractProfile::addMapping(AbstractMapping *m)
{
	Q_ASSERT(m);
	
	try
	{
		if (!m_isProcessingEvents)
			m_mappings << m; // add it directly
		else
			m_mappingsRequests << MappingModifRequest{MappingModifRequestType::RequestAddMapping,nullptr,0,m}; // add it in a queue, waiting for the current loop to end
	}
	catch (std::exception &e) {emit message(e.what(),Qt::red);}
}

// MAP ////////////////////////////////////////////////////////////////////////
void AbstractProfile::Map(AbstractRealJoystick *rj, ControlType type, uint rnum, LayersCombo lc, AbstractTrigger *trig, AbstractAction *act)
{
	this->addMapping(new MappingStandard(rj,type,rnum,lc,trig,act,m_eventsQueue));
}

// MAP BUTTON /////////////////////////////////////////////////////////////////
void AbstractProfile::MapButton(AbstractRealJoystick *rj, uint rButton, LayersCombo lc, VirtualJoystick *vj, uint vButton)
{
	this->addMapping(new MappingStandard(rj,ControlType::Button,rButton,lc,
						new TriggerButtonChange{},
						new ActionButtonSetChange(vj,vButton),
						m_eventsQueue));
}

// MAP BUTTON TEMPO ///////////////////////////////////////////////////////////
void AbstractProfile::MapButtonTempo(AbstractRealJoystick *rj, uint rButton, LayersCombo lc, uint cycles, AbstractAction *action1, AbstractAction *action2)
{
	this->addMapping(new MappingTempo(rj,rButton,lc,cycles,action1,action2,m_eventsQueue));
}

// MAP AXIS ///////////////////////////////////////////////////////////////////
void AbstractProfile::MapAxis(AbstractRealJoystick *rj, uint rAxis, LayersCombo lc, VirtualJoystick *vj, uint vAxis, AxisDirection d)
{
	this->addMapping(new MappingStandard(rj,ControlType::Axis,rAxis,lc,
					new TriggerAxisChange{},
					new ActionAxisSetChange(vj,vAxis,d),
					m_eventsQueue));
}

// MAP AXIS 1 /////////////////////////////////////////////////////////////////
void AbstractProfile::MapAxis1(AbstractRealJoystick *rj, uint rAxis, LayersCombo lc, const std::vector<float> &points, AbstractAction *actionPlus, AbstractAction *actionMoins)
{
	if (points.size() == 0)
	{
		emit message("MapAxis1: nbPoints must be > 0",Qt::red);
		return;
	}
	
	this->addMapping(new MappingAxis1(rj,rAxis,lc,points,actionPlus,actionMoins,m_eventsQueue));
}

void AbstractProfile::MapAxis1(AbstractRealJoystick *rj, uint rAxis, LayersCombo lc, uint nbPoints, AbstractAction *actionPlus, AbstractAction *actionMoins)
{
	if (nbPoints == 0)
	{
		emit message("MapAxis1: nbPoints must be > 0",Qt::red);
		return;
	}
	
	float pas = 2.0 / (float)nbPoints;
	std::vector<float> points(nbPoints);
	for (uint i=0; i<nbPoints; ++i) {points[i] = -1.0f + 0.5f*pas + i*pas;}
	this->addMapping(new MappingAxis1(rj,rAxis,lc,points,actionPlus,actionMoins,m_eventsQueue));
}

// MAP AXIS 2 /////////////////////////////////////////////////////////////////
void AbstractProfile::MapAxis2(AbstractRealJoystick *rj, uint rAxis, LayersCombo lc, const std::vector<float> &points, const std::vector<AbstractAction*> actions)
{
	if (points.size() == 0 || actions.size() != points.size()+1)
	{
		emit message("MapAxis2: nbPoints must be > 0 && nbActions == nbPoints+1",Qt::red);
		return;
	}
	
	this->addMapping(new MappingAxis2(rj,rAxis,lc,points,actions,m_eventsQueue));
}

void AbstractProfile::MapAxis2(AbstractRealJoystick *rj, uint rAxis, LayersCombo lc, uint nbPoints, const std::vector<AbstractAction*> actions)
{
	if (nbPoints == 0 || actions.size() != nbPoints+1)
	{
		emit message("MapAxis2: nbPoints must be > 0 && nbActions == nbPoints+1",Qt::red);
		return;
	}
	
	float pas = 2.0 / (float)nbPoints;
	std::vector<float> points(nbPoints);
	for (uint i=0; i<nbPoints; ++i) {points[i] = -1.0f + 0.5f*pas + i*pas;}
	this->addMapping(new MappingAxis2(rj,rAxis,lc,points,actions,m_eventsQueue));
}

// MAP MERGE AXES /////////////////////////////////////////////////////////////
void AbstractProfile::MapMergeAxes(AbstractRealJoystick *rj1, uint rAxis1, float k1, AbstractRealJoystick *rj2, uint rAxis2, float k2, LayersCombo lc, VirtualJoystick *vj, uint vAxis)
{
	this->addMapping(new MappingMergeAxes(rj1, rAxis1, k1, rj2, rAxis2, k2, lc, vj, vAxis, m_eventsQueue));
}






// UNMAP ALL //////////////////////////////////////////////////////////////////
void AbstractProfile::UnmapAll()
{
	if (!m_isProcessingEvents)
	{
		qDeleteAll(m_mappings);
		m_mappings.clear();
	}
	else
	{
		m_mappingsRequests << MappingModifRequest{MappingModifRequestType::RequestUnmapAll,nullptr,0,nullptr}; // add it in a queue, waiting for the current loop to end
		for (AbstractMapping *m : m_mappings) {m->aboutToBeDeleted();}
	}
}

// UNMAP BUTTON ///////////////////////////////////////////////////////////////
void AbstractProfile::UnmapButton(AbstractRealJoystick *rj, uint rButton)
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
		m_mappingsRequests << MappingModifRequest{MappingModifRequestType::RequestUnmapButton,rj,rButton,nullptr}; // add it in a queue, waiting for the current loop to end
		for (AbstractMapping *m : m_mappings)
		{
			if (m->isMappingButton(rj,rButton))
				m->aboutToBeDeleted();
		}
	}
}

// UNMAP AXIS /////////////////////////////////////////////////////////////////
void AbstractProfile::UnmapAxis(AbstractRealJoystick *rj, uint rAxis)
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
		m_mappingsRequests << MappingModifRequest{MappingModifRequestType::RequestUnmapAxis,rj,rAxis,nullptr}; // add it in a queue, waiting for the current loop to end
		for (AbstractMapping *m : m_mappings)
		{
			if (m->isMappingAxis(rj,rAxis))
				m->aboutToBeDeleted();
		}
	}
}

