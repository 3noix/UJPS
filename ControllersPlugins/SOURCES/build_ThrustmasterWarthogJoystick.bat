echo off


REM COMPILATION OF PLUGIN ThrustmasterWarthogJoystick
echo compiling ThrustmasterWarthogJoystick
echo.
cd ThrustmasterWarthogJoystick
qmake
mingw32-make release
copy /Y release\ThrustmasterWarthogJoystick.dll ..\..\..\bin\ControllersPlugins
cd ..
echo.
echo.


echo finished
REM pause

