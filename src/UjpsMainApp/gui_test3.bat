echo off


set UJPSGUIEXE=%~dp0\..\..\bin\UJPS.exe
set PROFILESPATH=%~dp0\..\..\examples\Profiles
cd %PROFILESPATH%\ProfileTest
%UJPSGUIEXE% profileTest.pro 25 -play
echo.


pause

