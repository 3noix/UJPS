#include <iostream>
#include "HidDevice.h"
#include "VigemPidWhiteListerConsole.h"


int main(int argc, char *argv[])
{
	QCoreApplication app{argc,argv};
	Q_UNUSED(app)
	std::cout << "Utility program to shut down Warthog throttle leds started" << std::endl;
	
	// white-list the app
	QString devconDirPath = QCoreApplication::applicationDirPath() + "/../../../3rdparty/ViGEm/Resources/";
	VigemPidWhiteListerConsole vigemInterface{devconDirPath};
	if (vigemInterface.vigemIsReady())
	{
		vigemInterface.whiteList(QCoreApplication::applicationPid());
		std::cout << "White-list in ViGEm: OK" << std::endl;
	}
	else
	{
		std::cout << "White-list in ViGEm: NO (ViGEm not setup)" << std::endl;
	}
	
	// find Thrustmaster Warthog Throttle
	HidDevice d{0x044F,0x0404};
	if (!d.openHidDevice())
	{
		std::cout << "Warthog throttle found: NO" << std::endl;
		std::cout << "Press return to terminate" << std::endl;
		std::cin.get();
		return 1;
	}
	else
	{
		std::cout << "Warthog throttle found: OK" << std::endl;
	}
	
	// shut down the lights
	std::cout << "Warthog throttle found" << std::endl;
	quint8 data[4];
	data[0] = 1;
	data[1] = 6;
	data[2] = 0; // flags (for leds and backlit)
	data[3] = 0; // brightness
	d.writeData(data,4); // it waits for finished before continuing
	
	// remove this application from the white list
	// (to avoid to pollute the white list with many invalid pids)
	if (vigemInterface.vigemIsReady())
		vigemInterface.blackList(QCoreApplication::applicationPid());
	
	// the end
	std::cout << "Leds should be off now" << std::endl;
	std::cout << "Press return to terminate" << std::endl;
	//std::cin.get();
	return 0;
}

