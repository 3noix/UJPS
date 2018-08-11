echo off


REM COMPILATION OF PLUGIN ThrustmasterT16000MJoystick
echo compiling ThrustmasterT16000MJoystick
echo.
cd ThrustmasterT16000MJoystick
qmake
mingw32-make release
echo.
copy /Y release\ThrustmasterT16000MJoystick.dll ..\..\PLUGINS
cd ..
echo.
echo.


echo finished
pause

