REM COMPILATION OF PLUGIN vJoyDevice
echo compiling vJoyDevice
echo.
cd %~dp0\vJoyDevice
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


REM COMPILATION OF PLUGIN ThrustmasterT16000MJoystick
echo compiling ThrustmasterT16000MJoystick
echo.
cd ThrustmasterT16000MJoystick
qmake
mingw32-make release
echo.
copy /Y release\ThrustmasterT16000MJoystick.dll ..\..\PLUGINS
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


REM COMPILATION OF PLUGIN MicrosoftXbox360Controller
echo compiling MicrosoftXbox360Controller
echo.
cd MicrosoftXbox360Controller
qmake
mingw32-make release
echo.
copy /Y release\MicrosoftXbox360Controller.dll ..\..\PLUGINS
cd ..
echo.
echo.


REM COMPILATION OF PLUGIN LogitechX56Joystick
echo compiling LogitechX56Joystick
echo.
cd LogitechX56Joystick
qmake
mingw32-make release
echo.
copy /Y release\LogitechX56Joystick.dll ..\..\PLUGINS
cd ..
echo.
echo.


REM COMPILATION OF PLUGIN LogitechX56Throttle
echo compiling LogitechX56Throttle
echo.
cd LogitechX56Throttle
qmake
mingw32-make release
echo.
copy /Y release\LogitechX56Throttle.dll ..\..\PLUGINS
cd ..
echo.
echo.

