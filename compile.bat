@echo off
chcp 65001 >nul
echo 正在编译 LaTeX 文档...
echo.

echo [1/2] 第一次编译（生成目录和交叉引用）...
xelatex -shell-escape -interaction=nonstopmode main.tex
if errorlevel 1 (
    echo.
    echo ❌ 编译失败！请检查错误信息。
    pause
    exit /b 1
)

echo.
echo [2/2] 第二次编译（更新目录和交叉引用）...
xelatex -shell-escape -interaction=nonstopmode main.tex
if errorlevel 1 (
    echo.
    echo ❌ 编译失败！请检查错误信息。
    pause
    exit /b 1
)

echo.
echo ✅ 编译成功！生成的 PDF 文件：main.pdf
echo.
pause

