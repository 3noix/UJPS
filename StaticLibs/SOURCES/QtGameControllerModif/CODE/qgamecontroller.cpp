/***************************************************************************
 *   Copyright (C) 2014 M Wellings                                         *
 *   info@openforeveryone.co.uk                                            *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License version 2 as     *
 *   published by the Free Software Foundation                             *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include "QGameController.h"
#include "QGameController_p.h"

#if defined (Q_OS_WIN)
#include "QGameController_win_p.h"
#else
#error Unsupported OS
#endif


///////////////////////////////////////////////////////////////////////////////
// EVENT //////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
QGameControllerEvent::QGameControllerEvent(uint controllerId)
	:d_ptr(new QGameControllerEventPrivate(this))
{
	Q_D(QGameControllerEvent);
	d->ControllerId = controllerId;
}

QGameControllerEvent::QGameControllerEvent(uint controllerId, QGameControllerEventPrivate &d)
	:d_ptr(&d)
{
	d.ControllerId = controllerId;
}

uint QGameControllerEvent::controllerId()
{
	Q_D(QGameControllerEvent);
	return d->ControllerId;
}

QGameControllerEvent::~QGameControllerEvent()
{
	delete d_ptr;
}


///////////////////////////////////////////////////////////////////////////////
// AXIS EVENT /////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
QGameControllerAxisEvent::QGameControllerAxisEvent(uint controllerId, uint axis, float value)
	: QGameControllerEvent(controllerId, *new QGameControllerAxisEventPrivate(this))
{
	Q_D(QGameControllerAxisEvent);
	d->iAxis = axis;
	d->value = value;
}

uint QGameControllerAxisEvent::axis()
{
	Q_D(QGameControllerAxisEvent);
	return d->iAxis;
}

float QGameControllerAxisEvent::value()
{
	Q_D(QGameControllerAxisEvent);
	return d->value;
}


///////////////////////////////////////////////////////////////////////////////
// BUTTON EVENT ///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
QGameControllerButtonEvent::QGameControllerButtonEvent(uint controllerId, uint button, bool pressed)
	: QGameControllerEvent(controllerId, *new QGameControllerButtonEventPrivate(this))
{
	Q_D(QGameControllerButtonEvent);
	d->iButton = button;
	d->bPressed = pressed;
}

uint QGameControllerButtonEvent::button()
{
	Q_D(QGameControllerButtonEvent);
	return d->iButton;
}

bool QGameControllerButtonEvent::pressed()
{
	Q_D(QGameControllerButtonEvent);
	return d->bPressed;
}


///////////////////////////////////////////////////////////////////////////////
// POV EVENT //////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
QGameControllerPovEvent::QGameControllerPovEvent(uint controllerId, uint pov, float angle)
	: QGameControllerEvent(controllerId, *new QGameControllerPovEventPrivate(this))
{
	Q_D(QGameControllerPovEvent);
	d->iPov = pov;
	d->angle = angle;
}

uint QGameControllerPovEvent::pov()
{
	Q_D(QGameControllerPovEvent);
	return d->iPov;
}

float QGameControllerPovEvent::angle()
{
	Q_D(QGameControllerPovEvent);
	return d->angle;
}


///////////////////////////////////////////////////////////////////////////////
// QGAMECONTROLLER ////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
QGameController::QGameController(uint id, QObject *parent) :
	QObject(parent), d_ptr(new QGameControllerPrivate(id, this))
{

}

QString QGameController::description()
{
	Q_D(QGameController);
	return d->Description;
}

QString QGameController::hardwareId()
{
	Q_D(QGameController);
	return d->HardwareId;
}

uint QGameController::id()
{
	Q_D(QGameController);
	return d->ID;
}

bool QGameController::isValid()
{
	Q_D(QGameController);
	return d->Valid;
}

uint QGameController::axesCount()
{
	Q_D(QGameController);
	return d->nbAxes;
}

uint QGameController::buttonsCount()
{
	Q_D(QGameController);
	return d->nbButtons;
}

uint QGameController::povsCount()
{
	Q_D(QGameController);
	return d->nbPovs;
}

float QGameController::axisValue(uint axis)
{
	Q_D(QGameController);
	if (axis >= d->AxesValues.size()) {return 0.0f;}
	return d->AxesValues.at(axis);
}

bool QGameController::buttonValue(uint button)
{
	Q_D(QGameController);
	if (button >= d->ButtonsValues.size()) {return false;}
	return d->ButtonsValues.at(button);
}

float QGameController::povValue(uint pov)
{
	Q_D(QGameController);
	if (pov >= d->PovsValues.size()) {return false;}
	return d->PovsValues.at(pov);
}

void QGameController::readGameController()
{
	Q_D(QGameController);
	d->readGameController();
}
