echo off


REM COMPILATION OF PLUGIN MicrosoftXbox360Gamepad
echo compiling MicrosoftXbox360Gamepad
echo.
cd MicrosoftXbox360Gamepad
qmake
mingw32-make release
copy /Y release\MicrosoftXbox360Gamepad.dll ..\..\..\..\bin\ControllersPlugins
cd ..
echo.
echo.


echo finished
REM pause

