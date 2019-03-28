echo off


REM compilation of static lib VirtualJoysticks
cd StaticLibs/SOURCES/VirtualJoysticks
call build_VirtualJoysticks_fct.bat
cd ../../..


REM compilation of static lib UjpsCore
cd StaticLibs/SOURCES/UjpsCore
call build_UjpsCore_fct.bat
cd ../../..


REM compilation and deployment of UJPS main app
cd UjpsMainApp
call build_UJPS_main_app_fct.bat
cd ..


REM copy network dll for AxesCurves and Monitoring
REM (necessary because RemoteJoystickServer is in RealJoysticks.dll)
copy /Y UjpsMainApp\release\Qt5Network.dll AxesCurves\release


REM create shortcut to UJPS main app
set SCRIPT="%~dp0\createShorcuts.vbs"
echo Set oWS = WScript.CreateObject("WScript.Shell") >> %SCRIPT%
echo sLinkFile = "%~dp0\UJPS.lnk" >> %SCRIPT%
echo Set oLink = oWS.CreateShortcut(sLinkFile) >> %SCRIPT%
echo oLink.TargetPath = "%~dp0\UjpsMainApp\release\UJPS.exe" >> %SCRIPT%
echo oLink.Save >> %SCRIPT%
cscript /nologo %SCRIPT%
del %SCRIPT%


echo build finished
pause

