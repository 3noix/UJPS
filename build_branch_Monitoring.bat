echo off


REM compilation and deployment of Monitoring
cd Monitoring
call build_Monitoring_fct.bat
cd ..


REM create shortcut to Monitoring
REM set SCRIPT="%~dp0\createShorcuts.vbs"
REM echo Set oWS = WScript.CreateObject("WScript.Shell") >> %SCRIPT%
REM echo sLinkFile = "%~dp0\Monitoring.lnk" >> %SCRIPT%
REM echo Set oLink = oWS.CreateShortcut(sLinkFile) >> %SCRIPT%
REM echo oLink.TargetPath = "%~dp0\..\bin\Monitoring.exe" >> %SCRIPT%
REM echo oLink.Save >> %SCRIPT%
REM cscript /nologo %SCRIPT%
REM del %SCRIPT%


echo build finished
pause

