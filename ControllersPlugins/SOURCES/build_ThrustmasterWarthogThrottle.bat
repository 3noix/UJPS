echo off


REM COMPILATION OF PLUGIN ThrustmasterWarthogThrottle
echo compiling ThrustmasterWarthogThrottle
echo.
cd ThrustmasterWarthogThrottle
qmake
mingw32-make release
echo.
copy /Y release\ThrustmasterWarthogThrottle.dll ..\..\PLUGINS
cd ..
echo.
echo.


echo finished
pause

