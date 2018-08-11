echo off


REM compilation and deployment of Monitoring
cd Monitoring
call build_Monitoring_fct.bat
cd ..


REM create shortcut to Monitoring
set SCRIPT="%~dp0\createShorcuts.vbs"
echo Set oWS = WScript.CreateObject("WScript.Shell") >> %SCRIPT%
echo sLinkFile = "%~dp0\Monitoring.lnk" >> %SCRIPT%
echo Set oLink = oWS.CreateShortcut(sLinkFile) >> %SCRIPT%
echo oLink.TargetPath = "%~dp0\Monitoring\release\Monitoring.exe" >> %SCRIPT%
echo oLink.Save >> %SCRIPT%
cscript /nologo %SCRIPT%
del %SCRIPT%


echo build finished
pause

