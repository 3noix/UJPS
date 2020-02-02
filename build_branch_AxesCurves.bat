echo off


REM compilation and deployment of AxesCurves
cd AxesCurves
call build_AxesCurves_fct.bat
cd ..


REM create shortcut to AxesCurves
REM set SCRIPT="%~dp0\createShorcuts.vbs"
REM echo Set oWS = WScript.CreateObject("WScript.Shell") >> %SCRIPT%
REM echo sLinkFile = "%~dp0\AxesCurves.lnk" >> %SCRIPT%
REM echo Set oLink = oWS.CreateShortcut(sLinkFile) >> %SCRIPT%
REM echo oLink.TargetPath = "%~dp0\..\bin\AxesCurves.exe" >> %SCRIPT%
REM echo oLink.Save >> %SCRIPT%
REM cscript /nologo %SCRIPT%
REM del %SCRIPT%


echo build finished
pause

