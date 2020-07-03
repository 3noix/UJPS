#include "MyScene.h"
#include "../DEFAULT/Geometry.h"
#include "MfdSelectableTextItem.h"
#include "MfdPage_PWR.h"
#include "MfdPage_IFCS.h"
#include "MfdPage_SYS.h"

#include "ThrustmasterMfdCougar.h"
namespace TMFD = ThrustmasterMfdCougar;


///////////////////////////////////////////////////////////////////////////////
// RESUME :
//
//  CONSTRUCTEUR
//  SET CURRENT PAGE
//  SLOT BUTTON CHANGED
///////////////////////////////////////////////////////////////////////////////


// CONSTRUCTEUR ///////////////////////////////////////////////////////////////
MyScene::MyScene(QObject *parent) : MfdScene{parent}
{
	m_bOneButtonClicked = false;
	m_currentPage = nullptr;
	
	QObject::connect(this, SIGNAL(buttonChanged(uint,bool)), this, SLOT(slotButtonChanged(uint,bool)));
	
	// addition of pages text
	m_textPWR  = new MfdSelectableTextItem{"PWR",2.0,Qt::AlignCenter};
	m_textSHLD = new MfdSelectableTextItem{"SHLD",2.0,Qt::AlignCenter};
	m_textSCAN = new MfdSelectableTextItem{"SCAN",2.0,Qt::AlignCenter};
	m_textIFCS = new MfdSelectableTextItem{"IFCS",2.0,Qt::AlignCenter};
	m_textSYS  = new MfdSelectableTextItem{"SYS",2.0,Qt::AlignCenter};
	this->addItem(m_textPWR);
	this->addItem(m_textSHLD);
	this->addItem(m_textSCAN);
	this->addItem(m_textIFCS);
	this->addItem(m_textSYS);
	m_textPWR->setPos(QPointF{g.x1,g.y6});
	m_textSHLD->setPos(QPointF{g.x2,g.y6});
	m_textSCAN->setPos(QPointF{g.x3,g.y6});
	m_textIFCS->setPos(QPointF{g.x4,g.y6});
	m_textSYS->setPos(QPointF{g.x5,g.y6});
	
	// addition of pages
	m_page_PWR  = new MfdPage_PWR{this};
	m_page_IFCS = new MfdPage_IFCS{this};
	m_page_SYS  = new MfdPage_SYS{this};
	QObject::connect(m_page_PWR,  SIGNAL(buttonChanged2(uint,bool)), this, SIGNAL(buttonChanged2(uint,bool)));
	QObject::connect(m_page_IFCS, SIGNAL(buttonChanged2(uint,bool)), this, SIGNAL(buttonChanged2(uint,bool)));
	QObject::connect(m_page_SYS,  SIGNAL(buttonChanged2(uint,bool)), this, SIGNAL(buttonChanged2(uint,bool)));
}

// SET CURRENT PAGE ///////////////////////////////////////////////////////////
bool MyScene::setCurrentPage(AbstractMfdPage *page)
{
	if (page == m_currentPage) {return false;}
	
	if (m_currentPage) {this->removeItem(m_currentPage);}
	m_currentPage = page;
	if (m_currentPage) {this->addItem(m_currentPage);}
	return true;
}

// SLOT BUTTON CHANGED ////////////////////////////////////////////////////////
void MyScene::slotButtonChanged(uint button, bool bPressed)
{
	if (bPressed)
	{
		if (m_bOneButtonClicked) {return;}
		m_bOneButtonClicked = true;
		
		if (button == TMFD::OSB15)
		{
			m_textPWR->select();
			m_textSHLD->unselect();
			m_textSCAN->unselect();
			m_textIFCS->unselect();
			m_textSYS->unselect();
			this->setCurrentPage(m_page_PWR);
		}
		else if (button == TMFD::OSB14)
		{
			m_textPWR->unselect();
			m_textSHLD->select();
			m_textSCAN->unselect();
			m_textIFCS->unselect();
			m_textSYS->unselect();
			this->setCurrentPage(nullptr);
		}
		else if (button == TMFD::OSB13)
		{
			m_textPWR->unselect();
			m_textSHLD->unselect();
			m_textSCAN->select();
			m_textIFCS->unselect();
			m_textSYS->unselect();
			this->setCurrentPage(nullptr);
		}
		else if (button == TMFD::OSB12)
		{
			m_textPWR->unselect();
			m_textSHLD->unselect();
			m_textSCAN->unselect();
			m_textIFCS->select();
			m_textSYS->unselect();
			this->setCurrentPage(m_page_IFCS);
		}
		else if (button == TMFD::OSB11)
		{
			m_textPWR->unselect();
			m_textSHLD->unselect();
			m_textSCAN->unselect();
			m_textIFCS->unselect();
			m_textSYS->select();
			this->setCurrentPage(m_page_SYS);
		}
		else if (m_currentPage)
		{
			m_currentPage->process(button,true);
		}
	}
	else
	{
		m_bOneButtonClicked = false;
		if (m_currentPage) {m_currentPage->process(button,false);}
	}
}

