echo off


REM compilation and deployment of ControllersInfo
cd ControllersInfo
call build_ControllersInfo_fct.bat
cd ..


REM create shortcut to ControllersInfo
REM set SCRIPT="%~dp0\createShorcuts.vbs"
REM echo Set oWS = WScript.CreateObject("WScript.Shell") >> %SCRIPT%
REM echo sLinkFile = "%~dp0\ControllersInfo.lnk" >> %SCRIPT%
REM echo Set oLink = oWS.CreateShortcut(sLinkFile) >> %SCRIPT%
REM echo oLink.TargetPath = "%~dp0\..\bin\ControllersInfo.exe" >> %SCRIPT%
REM echo oLink.Save >> %SCRIPT%
REM cscript /nologo %SCRIPT%
REM del %SCRIPT%


echo build finished
pause

