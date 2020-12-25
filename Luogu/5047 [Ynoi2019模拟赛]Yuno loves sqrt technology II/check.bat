@echo off
:alb
gen > data.in
std < data.in > my.out
bf < data.in > bf.out
fc bf.out my.out
if not errorlevel 1 goto alb
pause
