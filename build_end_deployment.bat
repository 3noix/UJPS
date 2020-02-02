echo off

cd bin
windeployqt UJPS.exe
windeployqt Monitoring.exe
cd ..
copy /Y vJoy218SDK-291116\SDK\lib\vJoyInterface.dll bin

echo.
echo.
pause
