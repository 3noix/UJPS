cd %~dp0
If not exist PLUGINS mkdir PLUGINS
cd SOURCES
start cmd.exe /c build_LogitechExtreme3D.bat
start cmd.exe /c build_LogitechX56Joystick.bat
start cmd.exe /c build_LogitechX56Throttle.bat
start cmd.exe /c build_MfgCrosswindRudderPedals.bat
start cmd.exe /c build_MicrosoftXbox360Gamepad.bat
start cmd.exe /c build_ThrustmasterT16000MJoystick.bat
start cmd.exe /c build_ThrustmasterTwcsThrottle.bat
start cmd.exe /c build_ThrustmasterWarthogJoystick.bat
start cmd.exe /c build_ThrustmasterWarthogThrottle.bat
start cmd.exe /c build_vJoyDevice.bat
cd ..
