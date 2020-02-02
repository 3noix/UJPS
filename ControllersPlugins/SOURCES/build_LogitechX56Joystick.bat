echo off


REM COMPILATION OF PLUGIN LogitechX56Joystick
echo compiling LogitechX56Joystick
echo.
cd LogitechX56Joystick
qmake
mingw32-make release
copy /Y release\LogitechX56Joystick.dll ..\..\..\bin\ControllersPlugins
cd ..
echo.
echo.


echo finished
REM pause

