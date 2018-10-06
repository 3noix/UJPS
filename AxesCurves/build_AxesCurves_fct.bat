REM compilation and deployment of AxesCurves app
echo compiling AxesCurves
echo.
qmake
mingw32-make release
cd release
echo.
windeployqt AxesCurves.exe
cd ..
copy /Y ..\StaticLibs\SOURCES\QtGameControllerModif\release\QtGameControllerModif.dll release
copy /Y ..\StaticLibs\SOURCES\RealJoysticks\release\realJoysticks.dll release
echo.
echo.

