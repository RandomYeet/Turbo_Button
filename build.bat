@echo off

windres ./src/resource.rc -O coff -o ./src/resource.res
gcc ./src/main.c ./src/resource.res -o ./build/Turbo.exe