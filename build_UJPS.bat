echo off

REM SET PATHS (line 4 to be updated with the paths that match your installation of Qt)
echo Setting up environment for Qt 5.7 usage...
set PATH=E:\Qt5.7\5.7\mingw53_32\bin;E:/Qt5.7/Tools/mingw530_32\bin;%PATH%
echo.


REM COMPILATION AND DEPLOYMENT OF CLEAN QT PROJECTS UTILITY
echo compilating CleanQtProjects
echo.
cd CleanQtProjects
qmake
mingw32-make release
echo.
cd release
windeployqt CleanQtProjects.exe
cd ../..
echo.
echo.


REM COMPILATION OF STATIC LIBS
echo compilating QtGameControllerModif
echo.
cd STATIC_LIBS/SOURCES/QtGameControllerModif
qmake
mingw32-make release
echo.
echo.

echo compilating VirtualJoysticks
echo.
cd ../VirtualJoysticks
qmake
mingw32-make release
echo.
echo.

echo compilating UjpsCore
echo.
cd ../UjpsCore
qmake
mingw32-make release
echo.
echo.


REM COMPILATION AND DEPLOYMENT OF MAIN PROGRAM
echo compilating the main program
echo.
cd ../../../PROGRAM
qmake
mingw32-make release
cd release
echo.
windeployqt Ujps.exe
cd ../..
copy /Y STATIC_LIBS\SOURCES\QtGameControllerModif\release\QtGameControllerModif.dll PROGRAM\release
copy /Y STATIC_LIBS\SOURCES\VirtualJoysticks\release\virtualJoysticks.dll PROGRAM\release
copy /Y STATIC_LIBS\SOURCES\UjpsCore\release\ujpsCore.dll PROGRAM\release
copy /Y vJoy218SDK-291116\SDK\lib\vJoyInterface.dll PROGRAM\release
echo.
echo.


REM COMPILATION AND DEPLOYMENT OF MONITORING
echo compilating monitoring program
echo.
cd MONITORING
qmake
mingw32-make release
echo.
cd release
windeployqt Monitoring.exe
cd ../..
copy /Y STATIC_LIBS\SOURCES\QtGameControllerModif\release\QtGameControllerModif.dll MONITORING\release
echo.
echo.


REM COMPILATION AND DEPLOYMENT OF AXES_CURVES
echo compilating axes curves program
echo.
cd AXES_CURVES
qmake
mingw32-make release
echo.
cd release
windeployqt AxesCurves.exe
cd ../..
copy /Y STATIC_LIBS\SOURCES\QtGameControllerModif\release\QtGameControllerModif.dll AXES_CURVES\release
echo.
echo.



echo build finished
pause

