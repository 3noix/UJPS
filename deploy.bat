echo off


cd bin
windeployqt UJPS.exe
windeployqt Monitoring.exe
cd ..
copy /Y 3rdparty\vJoy218SDK-291116\SDK\lib\vJoyInterface.dll bin
copy /Y 3rdparty\HttpServer\src\release\httpServer.dll bin


REM create shortcuts to the 4 apps
REM set SCRIPT="%~dp0\createShorcuts.vbs"
REM echo Set oWS = WScript.CreateObject("WScript.Shell") >> %SCRIPT%

REM echo sLinkFile1 = "%~dp0\AxesCurves.lnk" >> %SCRIPT%
REM echo Set oLink1 = oWS.CreateShortcut(sLinkFile1) >> %SCRIPT%
REM echo oLink1.TargetPath = "%~dp0\..\bin\AxesCurves.exe" >> %SCRIPT%
REM echo oLink1.Save >> %SCRIPT%

REM echo sLinkFile2 = "%~dp0\ControllersInfo.lnk" >> %SCRIPT%
REM echo Set oLink2 = oWS.CreateShortcut(sLinkFile2) >> %SCRIPT%
REM echo oLink2.TargetPath = "%~dp0\..\bin\ControllersInfo.exe" >> %SCRIPT%
REM echo oLink2.Save >> %SCRIPT%

REM echo sLinkFile3 = "%~dp0\Monitoring.lnk" >> %SCRIPT%
REM echo Set oLink3 = oWS.CreateShortcut(sLinkFile3) >> %SCRIPT%
REM echo oLink3.TargetPath = "%~dp0\..\bin\Monitoring.exe" >> %SCRIPT%
REM echo oLink3.Save >> %SCRIPT%

REM echo sLinkFile4 = "%~dp0\UJPS.lnk" >> %SCRIPT%
REM echo Set oLink4 = oWS.CreateShortcut(sLinkFile4) >> %SCRIPT%
REM echo oLink4.TargetPath = "%~dp0\..\bin\UJPS.exe" >> %SCRIPT%
REM echo oLink4.Save >> %SCRIPT%

REM cscript /nologo %SCRIPT%
REM del %SCRIPT%


echo.
echo.
pause
