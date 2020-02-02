echo off


REM COMPILATION OF PLUGIN vJoyDevice
echo compiling vJoyDevice
echo.
cd %~dp0\vJoyDevice
qmake
mingw32-make release
copy /Y release\vJoyDevice.dll ..\..\..\bin\ControllersPlugins
cd ..
echo.
echo.


echo finished
REM pause

