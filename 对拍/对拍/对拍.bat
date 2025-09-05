@echo off

rem Compile the source files
g++ my.cpp -o my.exe -O2
g++ std.cpp -o std.exe -O2
g++ gen.cpp -o gen.exe -O2

:loop
set seed=%random%
echo Running with seed: %seed%
gen.exe %seed% > data.txt
my.exe < data.txt > my.txt
std.exe < data.txt > std.txt

fc my.txt std.txt
if errorlevel 1 (
    echo WA on seed: %seed%
    pause
    exit
)

echo AC
goto loop
