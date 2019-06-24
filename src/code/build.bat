@echo off

pushd ..\build
del *.obj *.exe *.ilk *.pdb
cl -Zi /Fe:RayWin.exe ..\code\main.c ..\code\color.c ..\code\vector.c ..\code\ray.c ..\code\plane.c ..\code\sphere.c ..\code\camera.c ..\code\texture.c ..\code\hitable.c ..\code\material.c ..\code\trace.c 
popd






