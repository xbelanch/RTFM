

# Raytracer for the masses (again?)

Un Raytracer com a exucsa per treballar diferents qüestions que apariexen a handmade hero i per després compartir-lo amb la petitona i els petis ;)


## Create the virtual drive

Open command line and type `subst`:

    subst r: d:\Raytracer\

en aquest moments tenim un virtual drive que ens permetrà organitzar millor el data del projecte.


Segurament tindrem un problema de no poder modificar el label de la nova virtual drive. Davant d'això hi ha dues solucions:

* https://en.wikipedia.org/wiki/SUBST
* https://social.technet.microsoft.com/Forums/office/en-US/5cbc9ef4-b58a-4ba8-9b9d-84bfe1084827/change-label-of-subst-virtual-drive?forum=itproxpsp

Finalment hi ha un problema de persistència que es pot solucionar de diferents maneres: [
How to make SUBST mapping persistent across reboots?](https://superuser.com/questions/29072/how-to-make-subst-mapping-persistent-across-reboots)

En tot cas, aquesta part la deixarem per a més endavant. Hi ha l'opció de crear un batch i ubicar-lo en your Startup folder that does all the SUBSTs that you want to do.

Tot es veurà!

## Emacs setup

Aquest mereix un capítol a banda, ja que té un cert recorregut. Ara mateix, la única cosa que podem fer es afegir dins de Windows una variable d'entorn perquè s'executi des de terminal (tot i que, arran d'això, ha intentat crear, en el moment d'executar-se per primera vegada, un .emacs.d en la carpeta d'usuari).










## Creació del primer codi file

1. Obrim emacs i creem un primer fitxer (raytracer.c) amb una estructura bàsica. Amb git podeu veure'l si feu un git d2d75a073dd33b (First c file of raytracer)
2. Per compilar aquest fitxer cal iniciar l'environment del compilador de microsoft Visual Studio 2017 ([Run cl.exe from cmd](https://stackoverflow.com/questions/50830609/run-cl-exe-from-cmd)):


    call "C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Auxiliary\Build\vcvarsall.bat" x64


Amb això ja tenim l'entorn de desenvolupament. Anem a fer una primera compilació del codi:

    cl raytracer.c /Fe:ray.exe

L'opció [/Fe](https://docs.microsoft.com/en-us/cpp/build/reference/fe-name-exe-file?view=vs-2017) permet assignar el nom. No utilitzeu l'opció /out pq és outdated.

Es compila correctament en el moment de crear un executable (GG!)

## Plantejant una estructra básica

Es planteja dos directoris:

* code
* build

Es manté el code completament net per només incloure el codi font. I, a continuació, el build és pq derivem tot el resultat de la compilació. Per aquest motiu, proposa el següent ``build.bat``

    @echo off
    pwd
    mkdir ..\build
    pushd ..\build
    cl -Zi ..\code\raytracer.c /Fe:ray.exe
    popd


## Debug amb Visual Studio 2017

Si us heu fixat, hem inclos el parametre ``-Zi`` perquè generi els objectes de compilació necessari per començar a debug.

Un cop fet, cal executar la següent instrucció:

    devenv.exe ..\build\ray.exe


## Incloure SDL...



cl -iZ sdl.c /ISDL2\include /link SDL2\lib\x64\SDL2.lib SDL2\lib\x64\SDL2main.lib /SUBSYSTEM:WINDOWS /debug /out:sdlWinTest.exe
    devenv /debugexe sdlWinTest.exedev

