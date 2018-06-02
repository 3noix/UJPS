# UJPS: Universal Joystick Programming Software (C++) V2.3.0


This project allows the user to "program a set of real joysticks": events from the real joysticks are transformed into virtual joysticks and keyboard events. This transformation is defined in the "profile" defined by the user using C++ programming language. It is comparable to the proprietary "Thrustmaster TARGET scripts". But Thrustmaster TARGET scripts explicitly blocks non-Thrustmaster hardware. This tool works for any game controller recognized by Windows.


![ScreenShot](https://i.imgur.com/LgGH8RU.png)


It does not use HMI to define the profile such as in "Thrustmaster TARGET GUI", "Univeral Control Remapper" or "Joystick Gremlin". All the profile is defined in C++ source code... but there is no need to have an accurate understanding of C++ to be able to use it, just like for Thrustmaster TARGET scripts with C language.

Look at the files PROFILES/StarCitizen_3.0.1_v1/CODE/Profile.h and .cpp for an example !

Under the hood this tool uses:
- vJoy for virtual joysticks: http://vjoystick.sourceforge.net/site/ (installation needed)
- Qt 5 (installation needed)
- the non-official module QtGameController: https://github.com/openforeveryone/QGameController (not needed)


Installation: the whole procedure is discribed in the documentation:
- install Qt, prefer the version used to code this tool: https://download.qt.io/archive/qt/5.7/5.7.1/
- install vJoy : http://vjoystick.sourceforge.net/site/index.php/download-a-install/download (the big arrow in the middle)
- build the application using the bat file provided in this repository

![ScreenShot](https://i.imgur.com/TIaYK8H.png)

![ScreenShot](https://i.imgur.com/rbZOK0N.png)
