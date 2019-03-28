REM compilation and deployment of ControllersInfo app
echo compiling ControllersInfo
echo.
qmake
mingw32-make release
cd release
echo.
windeployqt ControllersInfo.exe
cd ..
copy /Y ..\StaticLibs\SOURCES\Settings\release\settings.dll release
copy /Y ..\StaticLibs\SOURCES\VigemWrapper\release\vigemWrapper.dll release
copy /Y ..\StaticLibs\SOURCES\QtGameControllerModif\release\QtGameControllerModif.dll release
echo.
echo.

