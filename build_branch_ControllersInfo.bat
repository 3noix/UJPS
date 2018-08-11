echo off


REM compilation and deployment of ControllersInfo
cd ControllersInfo
call build_ControllersInfo_fct.bat
cd ..


REM create shortcut to ControllersInfo
set SCRIPT="%~dp0\createShorcuts.vbs"
echo Set oWS = WScript.CreateObject("WScript.Shell") >> %SCRIPT%
echo sLinkFile = "%~dp0\ControllersInfo.lnk" >> %SCRIPT%
echo Set oLink = oWS.CreateShortcut(sLinkFile) >> %SCRIPT%
echo oLink.TargetPath = "%~dp0\ControllersInfo\release\ControllersInfo.exe" >> %SCRIPT%
echo oLink.Save >> %SCRIPT%
cscript /nologo %SCRIPT%
del %SCRIPT%


echo build finished
pause

