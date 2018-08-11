echo off


REM COMPILATION OF PLUGIN vJoyDevice
echo compiling vJoyDevice
echo.
cd %~dp0\vJoyDevice
qmake
mingw32-make release
echo.
copy /Y release\vJoyDevice.dll ..\..\PLUGINS
cd ..
echo.
echo.


echo finished
pause

