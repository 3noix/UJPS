echo off

REM SET PATHS (line 4 to be updated with the paths that match your installation of Qt)
echo Setting up environment for Qt 5.11 usage...
set PATH=C:\Qt\5.11.0\mingw53_32\bin;C:\Qt\Tools\mingw530_32\bin;%PATH%
echo.


REM COMPILATION AND DEPLOYMENT OF CLEAN QT PROJECTS UTILITY
echo compiling CleanQtProjects
echo.
cd %~dp0\CleanQtProjects
qmake
mingw32-make release
echo.
cd release
windeployqt CleanQtProjects.exe
cd ../..
echo.
echo.


REM COMPILATION OF STATIC LIBS
echo compiling QtGameControllerModif
echo.
cd StaticLibs/SOURCES/QtGameControllerModif
qmake
mingw32-make release
echo.
echo.

echo compiling RealJoysticks
echo.
cd ../RealJoysticks
qmake
mingw32-make release
echo.
echo.

echo compiling VirtualJoysticks
echo.
cd ../VirtualJoysticks
qmake
mingw32-make release
echo.
echo.

echo compiling UjpsCore
echo.
cd ../UjpsCore
qmake
mingw32-make release
echo.
echo.


REM COMPILATION AND DEPLOYMENT OF CONTROLLERS PLUGINS
cd ../../../ControllersPlugins
If not exist PLUGINS mkdir PLUGINS
cd SOURCES
call build_ControllersPlugins_fct.bat


REM COMPILATION AND DEPLOYMENT OF UJPS MAIN APP
echo compiling UjpsMainApp
echo.
cd ../../UjpsMainApp
qmake ujps.pro
mingw32-make release
qmake ujps_console.pro
mingw32-make release
cd release
echo.
windeployqt UJPS.exe
cd ../..
copy /Y StaticLibs\SOURCES\QtGameControllerModif\release\QtGameControllerModif.dll UjpsMainApp\release
copy /Y StaticLibs\SOURCES\RealJoysticks\release\realJoysticks.dll UjpsMainApp\release
copy /Y StaticLibs\SOURCES\VirtualJoysticks\release\virtualJoysticks.dll UjpsMainApp\release
copy /Y StaticLibs\SOURCES\UjpsCore\release\ujpsCore.dll UjpsMainApp\release
copy /Y vJoy218SDK-291116\SDK\lib\vJoyInterface.dll UjpsMainApp\release
echo.
echo.


REM COMPILATION AND DEPLOYMENT OF MONITORING
echo compiling Monitoring
echo.
cd Monitoring
qmake
mingw32-make release
echo.
cd release
windeployqt Monitoring.exe
cd ../..
copy /Y StaticLibs\SOURCES\QtGameControllerModif\release\QtGameControllerModif.dll Monitoring\release
copy /Y StaticLibs\SOURCES\RealJoysticks\release\realJoysticks.dll Monitoring\release
copy /Y UjpsMainApp\release\Qt5Network.dll Monitoring\release
echo.
echo.


REM COMPILATION AND DEPLOYMENT OF CONTROLLERS INFO
echo compiling ControllersInfo
echo.
cd ControllersInfo
qmake
mingw32-make release
echo.
cd release
windeployqt ControllersInfo.exe
cd ../..
copy /Y StaticLibs\SOURCES\QtGameControllerModif\release\QtGameControllerModif.dll ControllersInfo\release
echo.
echo.


REM COMPILATION AND DEPLOYMENT OF AXES_CURVES
echo compiling AxesCurves
echo.
cd AxesCurves
qmake
mingw32-make release
echo.
cd release
windeployqt AxesCurves.exe
cd ../..
copy /Y StaticLibs\SOURCES\QtGameControllerModif\release\QtGameControllerModif.dll AxesCurves\release
copy /Y StaticLibs\SOURCES\RealJoysticks\release\realJoysticks.dll AxesCurves\release
copy /Y UjpsMainApp\release\Qt5Network.dll AxesCurves\release
echo.
echo.





REM create shortcut to UjpsMainApp
set SCRIPT="%~dp0\createShorcuts.vbs"
echo Set oWS = WScript.CreateObject("WScript.Shell") >> %SCRIPT%
echo sLinkFile = "%~dp0\UJPS.lnk" >> %SCRIPT%
echo Set oLink = oWS.CreateShortcut(sLinkFile) >> %SCRIPT%
echo oLink.TargetPath = "%~dp0\UjpsMainApp\release\UJPS.exe" >> %SCRIPT%
echo oLink.Save >> %SCRIPT%
cscript /nologo %SCRIPT%
del %SCRIPT%

REM create shortcut to Monitoring
set SCRIPT="%~dp0\createShorcuts.vbs"
echo Set oWS = WScript.CreateObject("WScript.Shell") >> %SCRIPT%
echo sLinkFile = "%~dp0\Monitoring.lnk" >> %SCRIPT%
echo Set oLink = oWS.CreateShortcut(sLinkFile) >> %SCRIPT%
echo oLink.TargetPath = "%~dp0\Monitoring\release\Monitoring.exe" >> %SCRIPT%
echo oLink.Save >> %SCRIPT%
cscript /nologo %SCRIPT%
del %SCRIPT%

REM create shortcut to ControllersInfo
set SCRIPT="%~dp0\createShorcuts.vbs"
echo Set oWS = WScript.CreateObject("WScript.Shell") >> %SCRIPT%
echo sLinkFile = "%~dp0\ControllersInfo.lnk" >> %SCRIPT%
echo Set oLink = oWS.CreateShortcut(sLinkFile) >> %SCRIPT%
echo oLink.TargetPath = "%~dp0\ControllersInfo\release\ControllersInfo.exe" >> %SCRIPT%
echo oLink.Save >> %SCRIPT%
cscript /nologo %SCRIPT%
del %SCRIPT%

REM create shortcut to AxesCurves
set SCRIPT="%~dp0\createShorcuts.vbs"
echo Set oWS = WScript.CreateObject("WScript.Shell") >> %SCRIPT%
echo sLinkFile = "%~dp0\AxesCurves.lnk" >> %SCRIPT%
echo Set oLink = oWS.CreateShortcut(sLinkFile) >> %SCRIPT%
echo oLink.TargetPath = "%~dp0\AxesCurves\release\AxesCurves.exe" >> %SCRIPT%
echo oLink.Save >> %SCRIPT%
cscript /nologo %SCRIPT%
del %SCRIPT%


echo build finished
pause

