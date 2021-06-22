cls
@echo off

setlocal
set PATH=%PATH%;C:\mingw\bin;

echo *************************************************
echo This script compile makefile in Windows
echo *************************************************
echo PREREQUISITE:
echo Have MinGW installed on your computer

REM pause

call make

echo Build Done!!!
pause