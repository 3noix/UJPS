echo off


set UJPSCONSOLEEXE=%~dp0\..\bin\UJPS_console.exe
set PROFILESPATH=%~dp0\..\Profiles
cd %PROFILESPATH%\ProfileTest
%UJPSCONSOLEEXE% release\ProfileTest.dll 25
echo.


pause

