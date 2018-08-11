echo off


REM compilation and deployment of AxesCurves
cd AxesCurves
call build_AxesCurves_fct.bat
cd ..


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

