echo off


set UJPSCONSOLEEXE=%~dp0\..\..\bin\UJPS_console.exe
set PROFILESPATH=%~dp0\..\..\examples\Profiles
%UJPSCONSOLEEXE% %PROFILESPATH%\ProfileTest\release\ProfileTest.dll 25
echo.


pause

