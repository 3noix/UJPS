echo off


REM COMPILATION OF PLUGIN MicrosoftXbox360Gamepad
echo compiling MicrosoftXbox360Gamepad
echo.
cd MicrosoftXbox360Gamepad
qmake
mingw32-make release
echo.
copy /Y release\MicrosoftXbox360Gamepad.dll ..\..\PLUGINS
cd ..
echo.
echo.


echo finished
REM pause

