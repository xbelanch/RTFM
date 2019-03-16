@echo off
pwd
mkdir ..\build
pushd ..\build
cl -Zi ..\code\raytracer.c /Fe:ray.exe
popd

