@echo off
chcp 65001
cls
del /Q /S out\*
mkdir out

..\tools\mingw64\bin\g++.exe main\main.cpp -O2 -Wall out\main.exe
