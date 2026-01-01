@echo off
chcp 65001 >nul
echo 正在清理之前的编译文件...
del /q *.aux *.log *.out *.toc 2>nul
echo 清理完成！
echo.
call compile.bat

