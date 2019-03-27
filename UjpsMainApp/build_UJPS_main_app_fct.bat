REM compilation and deployment of UJPS main app
echo compiling UjpsMainApp
echo.
qmake ujps.pro
mingw32-make release
qmake ujps_console.pro
mingw32-make release
cd release
echo.
windeployqt UJPS.exe
cd ..
copy /Y ..\StaticLibs\SOURCES\Settings\release\settings.dll release
copy /Y ..\StaticLibs\SOURCES\VigemWrapper\release\vigemWrapper.dll release
copy /Y ..\StaticLibs\SOURCES\QtGameControllerModif\release\QtGameControllerModif.dll release
copy /Y ..\StaticLibs\SOURCES\RealJoysticks\release\realJoysticks.dll release
copy /Y ..\StaticLibs\SOURCES\VirtualJoysticks\release\virtualJoysticks.dll release
copy /Y ..\StaticLibs\SOURCES\UjpsCore\release\ujpsCore.dll release
copy /Y ..\vJoy218SDK-291116\SDK\lib\vJoyInterface.dll release
echo.
echo.

