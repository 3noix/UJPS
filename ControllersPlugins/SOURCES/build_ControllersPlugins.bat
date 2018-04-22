echo off

REM SET PATHS (line 4 to be updated with the paths that match your installation of Qt)
echo Setting up environment for Qt 5.7 usage...
set PATH=E:\Qt5.7\5.7\mingw53_32\bin;E:/Qt5.7/Tools/mingw530_32\bin;%PATH%
echo.


REM COMPILATION OF PLUGIN vJoyDevice
echo compiling vJoyDevice
echo.
cd vJoyDevice
qmake
mingw32-make release
echo.
copy /Y release\vJoyDevice.dll ..\..\PLUGINS
cd ..
echo.
echo.


REM COMPILATION OF PLUGIN ThrustmasterWarthogJoystick
echo compiling ThrustmasterWarthogJoystick
echo.
cd ThrustmasterWarthogJoystick
qmake
mingw32-make release
echo.
copy /Y release\ThrustmasterWarthogJoystick.dll ..\..\PLUGINS
cd ..
echo.
echo.


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


REM COMPILATION OF PLUGIN MfgCrosswindRudderPedals
echo compiling MfgCrosswindRudderPedals
echo.
cd MfgCrosswindRudderPedals
qmake
mingw32-make release
echo.
copy /Y release\MfgCrosswindRudderPedals.dll ..\..\PLUGINS
cd ..
echo.
echo.


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


REM COMPILATION OF PLUGIN LogitechExtreme3D
echo compiling LogitechExtreme3D
echo.
cd LogitechExtreme3D
qmake
mingw32-make release
echo.
copy /Y release\LogitechExtreme3D.dll ..\..\PLUGINS
cd ..
echo.
echo.

echo build finished
pause

