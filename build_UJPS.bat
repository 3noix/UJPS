echo off

REM SET PATHS (line 4 to be updated with the paths that match your installation of Qt)
echo Setting up environment for Qt 5.7 usage...
set PATH=E:\Qt5.7\5.7\mingw53_32\bin;E:/Qt5.7/Tools/mingw530_32\bin;%PATH%
echo.


REM COMPILATION AND DEPLOYMENT OF CLEAN QT PROJECTS UTILITY
echo compiling CleanQtProjects
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
qmake
mingw32-make release
cd release
echo.
windeployqt Ujps.exe
cd ../..
copy /Y StaticLibs\SOURCES\QtGameControllerModif\release\QtGameControllerModif.dll UjpsMainApp\release
copy /Y StaticLibs\SOURCES\RealJoysticks\release\realJoysticks.dll UjpsMainApp\release
copy /Y StaticLibs\SOURCES\VirtualJoysticks\release\virtualJoysticks.dll UjpsMainApp\release
copy /Y StaticLibs\SOURCES\UjpsCore\release\ujpsCore.dll UjpsMainApp\release
copy /Y vJoy218SDK-291116\SDK\lib\vJoyInterface.dll UjpsMainApp\release
echo.
echo.


REM COMPILATION AND DEPLOYMENT OF MONITORING0
echo compiling Monitoring0
echo.
cd Monitoring0
qmake
mingw32-make release
echo.
cd release
windeployqt Monitoring0.exe
cd ../..
copy /Y StaticLibs\SOURCES\QtGameControllerModif\release\QtGameControllerModif.dll Monitoring0\release
echo.
echo.


REM COMPILATION AND DEPLOYMENT OF MONITORING1
echo compiling Monitoring1
echo.
cd Monitoring1
qmake
mingw32-make release
echo.
cd release
windeployqt Monitoring1.exe
cd ../..
copy /Y StaticLibs\SOURCES\QtGameControllerModif\release\QtGameControllerModif.dll Monitoring1\release
copy /Y StaticLibs\SOURCES\RealJoysticks\release\realJoysticks.dll Monitoring1\release
copy /Y UjpsMainApp\release\Qt5Network.dll Monitoring1\release
echo.
echo.


REM COMPILATION AND DEPLOYMENT OF MONITORING2
echo compiling Monitoring2
echo.
cd Monitoring2
qmake
mingw32-make release
echo.
cd release
windeployqt Monitoring2.exe
cd ../..
copy /Y StaticLibs\SOURCES\QtGameControllerModif\release\QtGameControllerModif.dll Monitoring2\release
copy /Y StaticLibs\SOURCES\RealJoysticks\release\realJoysticks.dll Monitoring2\release
copy /Y UjpsMainApp\release\Qt5Network.dll Monitoring2\release
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
set SCRIPT="%cd%\createShorcuts.vbs"
echo Set oWS = WScript.CreateObject("WScript.Shell") >> %SCRIPT%
echo sLinkFile = "%cd%\UJPS.lnk" >> %SCRIPT%
echo Set oLink = oWS.CreateShortcut(sLinkFile) >> %SCRIPT%
echo oLink.TargetPath = "%cd%\UjpsMainApp\release\UJPS.exe" >> %SCRIPT%
echo oLink.Save >> %SCRIPT%
cscript /nologo %SCRIPT%
del %SCRIPT%

REM create shortcut to Monitoring0
set SCRIPT="%cd%\createShorcuts.vbs"
echo Set oWS = WScript.CreateObject("WScript.Shell") >> %SCRIPT%
echo sLinkFile = "%cd%\Monitoring0.lnk" >> %SCRIPT%
echo Set oLink = oWS.CreateShortcut(sLinkFile) >> %SCRIPT%
echo oLink.TargetPath = "%cd%\Monitoring0\release\Monitoring0.exe" >> %SCRIPT%
echo oLink.Save >> %SCRIPT%
cscript /nologo %SCRIPT%
del %SCRIPT%

REM create shortcut to Monitoring1
set SCRIPT="%cd%\createShorcuts.vbs"
echo Set oWS = WScript.CreateObject("WScript.Shell") >> %SCRIPT%
echo sLinkFile = "%cd%\Monitoring1.lnk" >> %SCRIPT%
echo Set oLink = oWS.CreateShortcut(sLinkFile) >> %SCRIPT%
echo oLink.TargetPath = "%cd%\Monitoring1\release\Monitoring1.exe" >> %SCRIPT%
echo oLink.Save >> %SCRIPT%
cscript /nologo %SCRIPT%
del %SCRIPT%

REM create shortcut to Monitoring2
set SCRIPT="%cd%\createShorcuts.vbs"
echo Set oWS = WScript.CreateObject("WScript.Shell") >> %SCRIPT%
echo sLinkFile = "%cd%\Monitoring2.lnk" >> %SCRIPT%
echo Set oLink = oWS.CreateShortcut(sLinkFile) >> %SCRIPT%
echo oLink.TargetPath = "%cd%\Monitoring2\release\Monitoring2.exe" >> %SCRIPT%
echo oLink.Save >> %SCRIPT%
cscript /nologo %SCRIPT%
del %SCRIPT%

REM create shortcut to AxesCurves
set SCRIPT="%cd%\createShorcuts.vbs"
echo Set oWS = WScript.CreateObject("WScript.Shell") >> %SCRIPT%
echo sLinkFile = "%cd%\AxesCurves.lnk" >> %SCRIPT%
echo Set oLink = oWS.CreateShortcut(sLinkFile) >> %SCRIPT%
echo oLink.TargetPath = "%cd%\AxesCurves\release\AxesCurves.exe" >> %SCRIPT%
echo oLink.Save >> %SCRIPT%
cscript /nologo %SCRIPT%
del %SCRIPT%


echo build finished
pause

