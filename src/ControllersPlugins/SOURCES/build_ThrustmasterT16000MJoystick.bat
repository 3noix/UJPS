echo off


REM COMPILATION OF PLUGIN ThrustmasterT16000MJoystick
echo compiling ThrustmasterT16000MJoystick
echo.
cd ThrustmasterT16000MJoystick
qmake
mingw32-make release
copy /Y release\ThrustmasterT16000MJoystick.dll ..\..\..\..\bin\ControllersPlugins
cd ..
echo.
echo.


echo finished
REM pause

