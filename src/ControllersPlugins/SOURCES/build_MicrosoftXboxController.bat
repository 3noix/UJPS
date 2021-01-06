echo off


REM COMPILATION OF PLUGIN MicrosoftXboxController
echo compiling MicrosoftXboxController
echo.
cd MicrosoftXboxController
qmake
mingw32-make release
copy /Y release\MicrosoftXboxController.dll ..\..\..\..\bin\ControllersPlugins
cd ..
echo.
echo.


echo finished
REM pause

