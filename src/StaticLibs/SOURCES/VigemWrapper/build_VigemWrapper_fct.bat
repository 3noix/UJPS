REM compilation of VigemWrapper
echo compiling VigemWrapper
echo.
qmake
mingw32-make release
copy /Y release\vigemWrapper.dll ..\..\..\..\bin
echo.
echo.

