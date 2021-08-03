REM compilation and deployment of CleanQtProjects
echo compiling CleanQtProjects
echo.
qmake
mingw32-make release
echo.
cd release
windeployqt CleanQtProjects.exe
cd ..
echo.
echo.

