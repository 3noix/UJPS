echo off


REM COMPILATION OF PLUGIN ThrustmasterTwcsThrottle
echo compiling ThrustmasterTwcsThrottle
echo.
cd ThrustmasterTwcsThrottle
qmake
mingw32-make release
copy /Y release\ThrustmasterTwcsThrottle.dll ..\..\..\bin\ControllersPlugins
cd ..
echo.
echo.


echo finished
REM pause

