#ifndef VJOY_DEVICE
#define VJOY_DEVICE


#include "RealJoystick.h"
class GameController;

#define INSIDE_PLUGIN
#include "../../../INCLUDES/vJoyDevice.h"


class vJoyDevice : public RealJoystick
{
	Q_OBJECT
	
	
	public:
		vJoyDevice(GameController *c);
		vJoyDevice(const vJoyDevice &other) = delete;
		vJoyDevice(vJoyDevice &&other) = delete;
		vJoyDevice& operator=(const vJoyDevice &other) = delete;
		vJoyDevice& operator=(vJoyDevice &&other) = delete;
		~vJoyDevice() = default;
		
		QString description() const override final;
		
		QString buttonName(uint button) const override final;
		QStringList buttonsNames() const override final;
		
		QString axisName(uint axis) const override final;
		QStringList axesNames() const override final;
		
		
	private:
		QStringList m_axesNames;
};

#endif
