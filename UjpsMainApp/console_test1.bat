echo off


set UJPSCONSOLEEXE=%~dp0\release\UJPS_console.exe
set PROFILESPATH=%~dp0\..\Profiles
%UJPSCONSOLEEXE% %PROFILESPATH%\ProfileTest\release\ProfileTest.dll 25
echo.


pause

