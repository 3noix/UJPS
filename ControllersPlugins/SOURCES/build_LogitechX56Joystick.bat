echo off


REM COMPILATION OF PLUGIN LogitechX56Joystick
echo compiling LogitechX56Joystick
echo.
cd LogitechX56Joystick
qmake
mingw32-make release
echo.
copy /Y release\LogitechX56Joystick.dll ..\..\PLUGINS
cd ..
echo.
echo.


echo finished
REM pause

