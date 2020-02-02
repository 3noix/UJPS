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


REM create shortcut to UJPS main app
REM set SCRIPT="%~dp0\createShorcuts.vbs"
REM echo Set oWS = WScript.CreateObject("WScript.Shell") >> %SCRIPT%
REM echo sLinkFile = "%~dp0\UJPS.lnk" >> %SCRIPT%
REM echo Set oLink = oWS.CreateShortcut(sLinkFile) >> %SCRIPT%
REM echo oLink.TargetPath = "%~dp0\..\bin\UJPS.exe" >> %SCRIPT%
REM echo oLink.Save >> %SCRIPT%
REM cscript /nologo %SCRIPT%
REM del %SCRIPT%


echo build finished
pause

