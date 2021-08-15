# UJPS: Universal Joystick Programming Software (C++) V3.5.0
## Overview

This project allows the user to "program a set of real joysticks": events from the real joysticks are transformed into virtual joysticks events and/or keyboard events. This transformation is defined in the "profile" defined by the user using C++ programming language. It is comparable to the proprietary "Thrustmaster TARGET C scripts". But Thrustmaster TARGET scripts explicitly blocks non-Thrustmaster hardware. This tool works for any game controller recognized by Windows.


![ScreenShot](https://i.imgur.com/qCnL9to.png)


It does not use GUI to define the profile such as in "Thrustmaster TARGET GUI", "Universal Control Remapper" or "Joystick Gremlin". All the profile are defined in C++ source code... but there is no need to have an accurate understanding of C++ to be able to use it, just like for Thrustmaster TARGET scripts with C language. The screenshot above is taken from the main program, which allows you to select your profile, compile it if needed and run it.

UJPS also permits to create "remote controllers" (with HTML/CSS/JS or with C++ Qt). A "remote controller" is an application that runs on mobile devices (or on external screens of your PC) that can send "joystick events" to your profile -just like if it were a normal joystick- and receive inputs from it.


## Installation

You will need to:
- Install [vJoy](http://vjoystick.sourceforge.net/site/index.php/download-a-install/download), for virtual joysticks
- Install [Qt](https://www.qt.io/download-qt-installer/). To avoid any Qt version and compilers issues, I recommend Qt 5.15.1 or 5.15.2 with MinGW 8.1.0 32-bit and including the additional QtCharts module. In the installation / maintenance tool, you should at least check the following items:
```bash
+-- Qt
  +-- Qt 5.15.1
    +-- MinwGW 8.1.0 32-bit
    +-- Qt Charts
+-- Developer and Designer Tools
  +-- MinwGW 8.1.0 32-bit
```
- Get UJPS
    - <strike>Using a release (not available yet)</strike>
	- Cloning and building UJPS:
	    - Version 1: open a git bash window, go the the directory where you want to add UJPS and type ```git clone https://github.com/3noix/UJPS.git --recurse-submodules```
		- Version 2: perform an usual cloning, then add the submodules: ```cd 3rdparty/HttpServer```, ```git submodule init```, ```git submodule update```, ```cd 3rdparty/QtPromise```, ```git submodule init``` and ```git submodule update```
	    - Finally build UJPS by running "build.bat" then "deploy.bat"

Why no "binaries release"? Both building UJPS and compiling a profile requires Qt 5. So if you don't have Qt 5 installed you will only be able to run profiles done by other users without the slightest modification (profiles binaries are dll files). And as the "UJPS community" is really small right now and as it is really easy to build the tool, I don't provide a "binaries release" right now. I could reconsider if some of you are interested.


## Examples

Currently UJPS offers 2 different ways to create profiles:
- With Target-like functions, by subclassing the AbstractProfileTarget class ([see examples](https://github.com/3noix/UJPS/tree/master/examples/Profiles/Target))
- [With rawer functions](https://github.com/3noix/UJPS/tree/master/src/StaticLibs/UjpsCore/src/BASIC), by subclassing the AbstractProfileBasic ([see examples](https://github.com/3noix/UJPS/tree/master/examples/Profiles/Basic))

Here we will only take a look at the "Thrustmaster Target" way. <b>Don't hesitate to take a look at the profiles examples in the ["examples/Profiles"](https://github.com/3noix/UJPS/tree/master/examples/Profiles) directory, this is the easiest way to get started.</b> Just below is most of the code of a simple UJPS profile just for the demo. "tmwj" designates the ThrustMaster Warthog Joystick object and "TMWJ" the namespace that contains the names of its buttons, axes and povs:

```C++
// file: Profile.h
#include "AbstractProfileTarget.h"
class EnhancedJoystick;

class Profile : public AbstractProfileTarget
{
   Q_OBJECT
   Q_PLUGIN_METADATA(IID "Profile")
   Q_INTERFACES(AbstractProfile)
   
   public:
      Profile();
      Profile(const Profile &other) = delete;
      Profile(Profile &&other) = delete;
      Profile& operator=(const Profile &other) = delete;
      Profile& operator=(Profile &&other) = delete;
      virtual ~Profile() = default;
      
   private:
      virtual bool setupJoysticks() override final;
      virtual void runFirstStep() override final;
      
      void myCustomFunction();
      EnhancedJoystick *tmwj; // Thrustmaster Warthog Joystick
      VirtualJoystick  *vj1;  // virtual joystick #1
};
```
```C++
// file: Controls.h
// It is very useful to give explicit names instead of using numbers
#include "WindowsKeys.h"
#include "vJoyDevice.h"
namespace VJOY = vJoyDevice;

namespace Controls_Keyboard
{
   const uint TrackIR_Pause  = Keys::Key_F8;
   const uint TrackIR_Center = Keys::Key_F9;
}

namespace Controls_vJoy1
{
   const uint AxisFlightRoll   = VJOY::X;
   const uint AxisFlightPitch  = VJOY::Y;
   const uint AxisFlightYaw    = VJOY::Z;
   const uint AxisFlightThrust = VJOY::ROTX;
   
   const uint PushToTalk  = VJOY::DX1;
   const uint Autopilot   = VJOY::DX2;
   const uint Autoland    = VJOY::DX3;
   const uint Autothrust  = VJOY::DX4;
   const uint LandingGear = VJOY::DX5;
}
```
```C++
//file: Profile.cpp
#include "Profile.h"
#include "TRIGGERS/Triggers.h"
#include "ACTIONS/Actions.h"
LayersCombo AllLayers{};

#include "VirtualJoystick.h"
#include "EnhancedJoystick.h"
#include "ThrustmasterWarthogJoystick.h"
#include "Controls.h"
namespace TMWJ = ThrustmasterWarthogJoystick;
namespace CTLK = Controls_Keyboard;
namespace CTL1 = Controls_vJoy1;


bool Profile::setupJoysticks()
{
   // we retrieve pointers on real joysticks we are interested in
   if (tmwj = this->registerRealJoystick(TMWJ::Description))
      emit message("Warthog joystick detected !",Qt::black);
   else {
      emit message("Warthog joystick not detected !",Qt::red);
      return false;
   }
   
   // virtual joystick(s) setup
   if (vj1 = this->registerVirtualJoystick(1))
      emit message("Virtual joystick 1 acquired",Qt::black);
   else {
      emit message("Virtual joystick 1 failed to configure",Qt::red);
      return false;
   }
   
   return true;
}

void Profile::runFirstStep() // executed one time at the beginning
{
   vj1->resetReport();
   
   // Basic axis mapping
   // The axis "AxisFlightRoll" of virtual joystick 1 will follow the JOYX axis of TMWJ
   MapAxis(tmwj, TMWJ::JOYX, AllLayers, vj1, CTL1::AxisFlightRoll);
   
   // Basic button mapping
   // The button "PushToTalk" of virtual joystick 1 will follow the TG1 button of TMWJ
   MapButton(tmwj, TMWJ::TG1, AllLayers, vj1, CTL1::PushToTalk);
   
   // Standard mapping
   // The code just below does exactly the same as the basic button mapping but with
   // a lower level function. It can be used with a wide range of triggers and actions,
   // and you can create your own ones.
   Map(tmwj, ControlType::Button, TMWJ::TG1, AllLayers,
      new TriggerButtonChange{},                      // at each change of TG1 button
      new ActionButtonSetChange{vj1, CTL1::Autopilot} // the change is reproduced on this one
   );
   
   // Standard mapping
   // With different triggers and actions
   Map(tmwj, ControlType::Button, TMWJ::H2U, AllLayers,
      new TriggerButtonRelease{},  // each time H2U button is released...
      new ActionChain{
         new ActionButtonPulse{vj1,CTL1::Autoland,ms2cycles(200)},  // button pulse of 200 ms...
         new Delay{ms2cycles(300)},  // ...and 300 ms after the beginning of the first pulse...
         new ActionKeyPulse{CTLK::TrackIR_Center,0,ms2cycles(200)}, // ...a keystroke for 200 ms
         new ActionCallback{[this]() {this->myCustomFunction();}}   // ...and myCustomFunction is executed*
   });
   // *mappings can be deleted and added inside such functions: they are not frozen
   // after the initial definition done in this "runFirstStep" function
}
```


## Other tools

Around the main UJPS program, a few other ones are provided:
- ControllersInfo: it just provides some basic information about all the controllers currently connected
- AxesCurves: it helps you to find the good parameters for your axes curves
- Monitoring: it shows the real and virtual joysticks events with different modes (what sees the system, what sees UJPS, ... see the documentation for more details)

![ScreenShot](https://i.imgur.com/4Mm6XqP.png)

![ScreenShot](https://i.imgur.com/680nJwt.png)


## Remote controllers

Moreover UJPS permits to create "remote controllers" (if you don't know what I am talking about, take a look at Roccat Power Grid, LEA extended input or GameGlass). A "remote controller" is an application that runs on mobile devices (or on external screens of your PC) that can send "joystick events" to your profile and receive inputs from it. In the examples I provide 2 ways of creating such "remote controllers":
- With a Qt desktop application ([see examples](https://github.com/3noix/UJPS/tree/master/examples/RemoteControllers)). Classes are already done to take care of the communication with the profile. So you can focus on the GUI in C++ Qt. I provide 2 examples ("MFD_dumb" and "MFD_smart") which reproduce a "Thrustmaster MFD Cougar". Both of them works with the ["ProfileMfd"](https://github.com/3noix/UJPS/tree/master/examples/Profiles/Target/ProfileMfd) profile.
- With Web files: define your GUI in HTML, CSS (and optionnally JS) and use the provided JS functions to take care of the communication with the profile ([see examples](https://github.com/3noix/UJPS/tree/master/examples/Profiles/Basic/ProfileWebRemote)). Connect your mobile device to your local Wifi network, and type in a browser the url given by the UJPS main app (you must start the profile).


![ScreenShot](https://i.imgur.com/NuoG9RB.png)
