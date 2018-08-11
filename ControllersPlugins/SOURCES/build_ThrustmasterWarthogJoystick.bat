echo off


REM COMPILATION OF PLUGIN ThrustmasterWarthogJoystick
echo compiling ThrustmasterWarthogJoystick
echo.
cd ThrustmasterWarthogJoystick
qmake
mingw32-make release
echo.
copy /Y release\ThrustmasterWarthogJoystick.dll ..\..\PLUGINS
cd ..
echo.
echo.


echo finished
pause

