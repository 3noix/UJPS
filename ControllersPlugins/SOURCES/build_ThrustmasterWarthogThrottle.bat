echo off


REM COMPILATION OF PLUGIN ThrustmasterWarthogThrottle
echo compiling ThrustmasterWarthogThrottle
echo.
cd ThrustmasterWarthogThrottle
qmake
mingw32-make release
copy /Y release\ThrustmasterWarthogThrottle.dll ..\..\..\bin\ControllersPlugins
cd ..
echo.
echo.


echo finished
REM pause

