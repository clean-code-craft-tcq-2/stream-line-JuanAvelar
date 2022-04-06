@echo off

g++ -o bin\testcheck.exe -std=c++11 sender_test.cpp sender.cpp
IF %ERRORLEVEL% == 0 (
bin\testcheck.exe
) ELSE (
echo ****** COMPILATION TEST FAILED! ******
)

g++ -o bin\sender.exe -std=c++11 sender.cpp main.cpp
IF %ERRORLEVEL% == 0 (
bin\sender.exe
) ELSE (
echo ****** COMPILATION PRODUCTION FAILED! ******
)
