# UJPS: Universal Joystick Programming Software (C++) V3.2.1
## Overview

This project allows the user to "program a set of real joysticks": events from the real joysticks are transformed into virtual joysticks events and/or keyboard events. This transformation is defined in the "profile" defined by the user using C++ programming language. It is comparable to the proprietary "Thrustmaster TARGET C scripts". But Thrustmaster TARGET scripts explicitly blocks non-Thrustmaster hardware. This tool works for any game controller recognized by Windows.


![ScreenShot](https://i.imgur.com/qCnL9to.png)


It does not use GUI to define the profile such as in "Thrustmaster TARGET GUI", "Universal Control Remapper" or "Joystick Gremlin". All the profile are defined in C++ source code... but there is no need to have an accurate understanding of C++ to be able to use it, just like for Thrustmaster TARGET scripts with C language. The screenshot above is taken from the main program, which allows you to select your profile, compile it if needed and run it.


## Installation

The whole procedure is described in details in the documentation (the pdf in the root directory). You will need to:
- install vJoy for virtual joysticks: http://vjoystick.sourceforge.net/site/index.php/download-a-install/download
- install Qt 5: https://www.qt.io/download-qt-installer/
- build UJPS by running "build_all.bat" then "build_end_deployment.bat"

Why no "binaries release"? Both building UJPS and compiling a profile requires Qt 5. So if you don't have Qt 5 installed you will only be able to run profiles done by other users without the slightest modification (profiles binaries are dll files). And as the "UJPS community" is really small right now and as it is really easy to build the tool, I don't provide a "binaries release" right now. I could reconsider if some of you are interested.


## Examples

First, don't hesitate to take a look at the profiles examples in the "Profiles" directory. But here are a few lines of code of a UJPS profile, just to let you feel how a profile is coded. "tmwj" designates the ThrustMaster Warthog Joystick object and "TMWJ" the namespace that contains the names of its buttons, axes and povs:

```C++
bool Profile::setupJoysticks()
{
   // we retrieve pointers on real joysticks we are interested in
   tmwj = this->registerRealJoystick("Joystick - HOTAS Warthog");
   if (tmwj) {emit message("Warthog joystick detected !",Qt::black);}
   else {emit message("Warthog joystick not detected !",Qt::red); return false;}
   
   // setup of 1 virtual joystick
   vj1 = this->registerVirtualJoystick(1);
   if (vj1) {emit message("Virtual joystick 1 acquired",Qt::black);}
   else {emit message("Virtual joystick 1 failed to configure",Qt::red);}
   
   return (tmwj && vj1);
}
```
```C++
void Profile::runFirstStep()
{
   // registering a modifier button
   this->registerLayerDim1(Layers::In, tmwt, TMWJ::S4);
   
   // mappings creation
   MapAxis(tmwj,   TMWJ::JOYX, AllLayers, vj1, SC1::AxisFlightRoll);  // basic axis mapping
   MapButton(tmwj, TMWJ::TG1,  AllLayers, vj1, SC1::FireGroup1);      // basic button mapping
   Map(tmwj, ControlType::Button, TMWJ::S2,  AllLayers, new TriggerButtonPress{},   new ActionCallback{[this]() {this->myCustomFunction();}}); // custom function execution when S2 gets pressed
   Map(tmwj, ControlType::Button, TMWJ::H2U, AllLayers, new TriggerButtonRelease{},  // when H2U is released...
     new ActionChain{
       new ActionButtonPulse{vj1,SC1::ResetPowerDistribution,ms2cycles(200)},  // button pulse of 200 ms...
       new Delay{ms2cycles(300)},                                // ... and 300 ms after the beginning of the first pulse...
       new ActionKeyPulse{SCK::TrackIR_Center,0,ms2cycles(200)}  // ... a keystroke pulse of 200 ms
   });
}
```


## Other tools

Around the main UJPS program, a few other ones are provided (see screenshots at the end):
- ControllersInfo: it just provides some basic information about all the controllers currently connected
- AxesCurves: it helps you to find the good parameters for your axes curves
- Monitoring: it shows the real and virtual joysticks events with different modes (what sees the system, what sees UJPS, ... see the documentation for more details)

![ScreenShot](https://i.imgur.com/4Mm6XqP.png)

![ScreenShot](https://i.imgur.com/680nJwt.png)


## Remote controllers

Moreover UJPS also provides classes to ease the creation of "remote controllers" (if you don't know what I am talking about, take a look at Roccat Power Grid or LEA extended input). A "remote controller" is an application that runs on your PC or mobile devices and that can send joystick events to your profile and receive inputs from it. The provided classes take care of the network communication between the remote controller and the profile, but you have to program the GUI yourself... I do not provide a GUI editor like in Roccat Power Grid or LEA extended input. I just provide 2 examples of "Thrustmaster MFD Cougar" implemented as remote controllers:
- "MFD_dumb" which just simulates the bezel and sends the buttons changes to the profile
- "MFD_smart" which is more evolved than the first one. It includes a few MFD pages with basic graphics (only text). It does not send button changes, but actions requests which can be different for the same button on different MFD pages

These 2 examples can be run with the "ProfileMfd" profile provided.

![ScreenShot](https://i.imgur.com/NuoG9RB.png)
