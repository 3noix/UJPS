REM compilation and deployment of Monitoring app
echo compiling Monitoring
echo.
qmake
mingw32-make release
cd release
echo.
windeployqt Monitoring.exe
cd ..
copy /Y ..\StaticLibs\SOURCES\QtGameControllerModif\release\QtGameControllerModif.dll release
copy /Y ..\StaticLibs\SOURCES\RealJoysticks\release\realJoysticks.dll release
echo.
echo.
