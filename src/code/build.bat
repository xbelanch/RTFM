@echo off

pushd ..\build
cl -Zi ..\code\raytracer.c /I..\dep\SDL2\include /link ..\dep\SDL2\lib\x64\SDL2.lib  /SUBSYSTEM:CONSOLE /out:Ray.exe
popd






