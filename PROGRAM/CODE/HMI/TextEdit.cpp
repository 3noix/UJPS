#include <QMenu>
#include <QTime>
#include <QMouseEvent>

#include "TextEdit.h"


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// RESUME :
//
//  CONSTRUCTEUR
//  DESTRUCTEUR
//
//  CREATE ACTIONS
//  CONTEXT MENU EVENT
//  ADD MESSAGE
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



// CONSTRUCTEUR ET DESTRUCTEUR /////////////////////////////////////////////////////////////////////////////////////////////////
TextEdit::TextEdit(QWidget *parent) : QTextEdit(parent)
{
	this->setReadOnly(true);
	
	// actions
	this->createActions();
	
	// menu
	m_menu = new QMenu(this);
	m_menu->addAction(actionClear);
	m_menu->addSeparator();
	m_menu->addAction(actionCopy);
	m_menu->addAction(actionSelectAll);
	
	// connections
	connect(actionClear, SIGNAL(triggered()), this, SLOT(clear()));
	connect(actionCopy, SIGNAL(triggered()), this, SLOT(copy()));
	connect(actionSelectAll, SIGNAL(triggered()), this, SLOT(selectAll()));
}



// CREATE ACTIONS //////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TextEdit::createActions()
{
	// action clear
	actionClear = new QAction("Clear",this);
	actionClear->setStatusTip("Clear the content of the message box");
	actionClear->setIcon(QIcon(":/RESOURCES/ICONES/corbeille.png"));
	
	// action copy
	actionCopy = new QAction("Copy",this);
	actionCopy->setShortcut(QKeySequence("Ctrl+C"));
	actionCopy->setStatusTip("Copy the content of the message box");
	actionCopy->setIcon(QIcon(":/RESOURCES/ICONES/copy.png"));
	
	// action select all
	actionSelectAll = new QAction("Select all",this);
	actionSelectAll->setShortcut(QKeySequence("Ctrl+A"));
	actionSelectAll->setStatusTip("Select all the content of the message box");
	actionSelectAll->setIcon(QIcon(":/RESOURCES/ICONES/select.png"));
}


// CONTEXT MENU EVENT //////////////////////////////////////////////////////////////////////////////////////////////////////////
void TextEdit::contextMenuEvent(QContextMenuEvent *event)
{
	QPoint position = event->pos();
	m_menu->exec(this->mapToGlobal(position + QPoint(0,-10)));
}

// ADD MESSAGE /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TextEdit::addMessage(const QString &msg, QColor color)
{
	this->setTextColor(color);
	//this->append(QTime::currentTime().toString("hh:mm:ss") + " : " + msg);
	this->append(msg);
	this->repaint();
}



