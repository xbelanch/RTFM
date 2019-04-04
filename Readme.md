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

Per fer-ho aquí teniu el codi del `startup.bat` que has d'incloure en el directori

    @echo off
    subst r: d:\Raytracer
    call "C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Auxiliary\Build\vcvarsall.bat" x64

i el desem en el següent directori:

    C:\Users\Rotter\AppData\Roaming\Microsoft\Windows\Start Menu\Programs\Startup\


Hem iniciat l'ordinador i, si bé ha muntat la unitat R: no veiem que tingui cap efecte el call ¬¬ per tant, haurem de resldre aquest tema TODO


## Emacs setup

Aquest mereix un capítol a banda, ja que té un cert recorregut. Ara mateix, la única cosa que podem fer es afegir dins de Windows una variable d'entorn perquè s'executi des de terminal (tot i que, arran d'això, ha intentat crear, en el moment d'executar-se per primera vegada, un .emacs.d en la carpeta d'usuari).

He trobat a github un tema init.el força configurable: 




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


## Incloure SDL... i printf deixa de funcionar!


En primer lloc, aquí tens el nou bat perquè compili amb SDL:

    @echo off
    pwd
    mkdir ..\build
    pushd ..\build
    cl -Zi ..\code\raytracer.c /I..\dep\SDL2\include /link ..\dep\SDL2\lib\x64\SDL2.lib ..\dep\SDL2\lib\x64\SDL2main.lib  /SUBSYSTEM:CONSOLE /out:Ray.exe
    popd


En principci, recorda que has de ficar SUBSYSTEM:CONSOLE o del contrari, funcions com el printf deixen de funcionar. D'altra banda, si no inclous la SDL2main.lib, el linker es queixa que no troba el main... ah! gràcies a: [Error LNK2019 unresolved external symbol _main referenced in function “int __cdecl invoke_main(void)” (?invoke_main@@YAHXZ)](https://stackoverflow.com/questions/33400777/error-lnk2019-unresolved-external-symbol-main-referenced-in-function-int-cde) o [can i use printf with WinMain?](https://social.msdn.microsoft.com/Forums/en-US/1dea240a-0b09-4bbb-8bdf-e52a9c53f079/can-i-use-printf-with-winmain?forum=Vsexpressvc)

## Nous entrebancs: debug missing sdl_windows_main.c (solved)

De fet, un cop que ara funciona ;) en el moment de fer un debug ens trobem que el MVisual Studio demana el fitxer: ``sdl_windows_main.c``. Vaja el mateix que li passa a [Step Debugging SDL2 Visual Studio 2017](https://stackoverflow.com/questions/45068430/step-debugging-sdl2-visual-studio-2017)


Llavors, ens trobem en una situació en la qual hem de tornar a resoldre l'anterior qüestió, la del SUBSYSTEM:CONSOLE i veure quin main necessita per pode continuar gaudint del debugger del Microsoft Visual Studio 2017.

Tornem-hi! quan treiem el SDL2main al linker, obtenim el problema del compilador:

    LIBCMT.lib(exe_main.obj) : error LNK2019: unresolved external symbol main referenced in function "int __cdecl __scrt_common_main_seh(void)" (?__scrt_common_main_seh@@YAHXZ)
    Ray.exe : fatal error LNK1120: 1 unresolved externals

Anem a fer una mica de cerca ;) i sembla ser que hem trobat la solució en
aquesta web: [MVS2015 keeps giving “unresolved externals” error with
SDL2](https://stackoverflow.com/questions/33990387/mvs2015-keeps-giving-unresolved-externals-error-with-sdl2)

I no dóna errrs en el moment que inclouem abans de l'include
el `#define SDL_MAIN_HANDLED`. Ara cal veure si funciona el
debugger amb el MS Visual Studio 2017. I, tachan! funciona!
:D

Continuem! 

## SDL_Quit no funciona ##

En aquests moments, no podem entendre el perquè no funciona
la interrupció del SDL_QUIT i, per tant, no hi ha manera de
saber si la entrada de teclat funciona...

Ja està solventat en el moment d'incloure el següent codi:

      // Process events
      for(SDL_Event ev; SDL_PollEvent(&ev) != 0; )
        {

          if (ev.type == SDL_KEYDOWN)
            {
              switch (ev.key.keysym.sym) {
              case SDLK_ESCAPE:
                printf("Exit the program\n");
                interrupted = true;
                break;
              }
            }

        } 


## Compile des de Emacs 

M-x compile i li diem Build perque cridi el batch que hem creat a propòsit. El
problema immediat és que no reconeix el compilador de MS (cl is not found o
quelcom similar). Per tant, caldrà que trobem un manera de veure com, des
d'Emacs podem solventar aquesta història :-/

TODO: Cal revisar de nou la web de Muratori al respecte: [Shell
Bat](https://github.com/ecxr/handmadehero/blob/master/misc/shell.bat). Després
de veure com ho fa, trobaràs que ha fet el següent: adjuntar aquest argument

    /k r:/shell.bat 

en el paràmetre de executar el cmd.

Dins del shell.bat trobaràs el codi que executa, per una banda, l'entorn de
compilació i, d'altra banda, el canvi d'unitat a R:

Sobre això últim, cal veure si puc fer el mateix amb el cmder (més àgil que el
cmd). Hi ha un debat a Github: [Question: How to start cmder with a command](https://github.com/cmderdev/cmder/issues/457)

En tot cas, cal pensar en saber si podem crear un make en Windows per a
Emacs... molt interessant aquest recurs: [Visual C++ MSVC Building Tools (Emacs
on
Windows)](http://caiorss.github.io/Emacs-Elisp-Programming/Emacs_On_Windows.html#sec-1-7)
on explica una configuració d'entorn perquè pugui reconèixer l'entorn de
desenvolupament de M.V.Studio 2017


## La primera imatge  ##

Tot aquest tema queda inclós en el git fins al capítol 5 (part 1) on ja podeu
veure la imatge de l'esfera amb les normals acolorides...



## Reestructurant el codi  ##

La pregunta que es fa el llibre "How about several spheres?" implica que,
d'alguna manera, haguem de reestructura el codi, ja que ara mateix és simplement
un mess enorme. Com que ell proposa un codi en C++, tirarà de classes i altres
coses fancy de l'orientació a objectes. En el nostre cas ens remetrem al llibre
"Practical Ray Tracing in C", on proposa una abstracció en C dels objectes que
poden trobar-se en escena. Bàsicament, el que farem en llista de todo, serà el
següent:

* TODO: Crear un fitxer struct.h amb la definició de les estructures del Ray Tracing
* TODO: Reescriure el vectors.h perquè les operacions siguin macros 












