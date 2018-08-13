echo off


REM COMPILATION OF PLUGIN ThrustmasterTwcsThrottle
echo compiling ThrustmasterTwcsThrottle
echo.
cd ThrustmasterTwcsThrottle
qmake
mingw32-make release
echo.
copy /Y release\ThrustmasterTwcsThrottle.dll ..\..\PLUGINS
cd ..
echo.
echo.


echo finished
REM pause

