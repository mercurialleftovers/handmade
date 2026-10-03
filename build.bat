@echo off

REM IF EXIST out (
REM 	echo exists
REM ) ELSE (
REM 	mkdir out
REM )

pushd out
del /Q *.exe
cl /Zi ..\src\win32_handmade.cc  user32.lib
start win32_handmade.exe
popd
tools\raddbg.exe out\win32_handmade.exe

