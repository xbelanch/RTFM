# TODO: try to rewrite that Makefile similar to the explanation
# https://stackoverflow.com/questions/26028834/makefile-move-object-files

.PHONY: ray
.PHONY: clean

PROGRAM = Ray
FILES.c = main.c color.c vector.c ray.c plane.c sphere.c camera.c texture.c hitable.c material.c trace.c
FILES.o = ${FILES.c:.c=.o}

CC      = gcc
SFLAGS  = -std=c99
GFLAGS  = -g
OFLAGS  = -O3
WFLAG1  = -Wall
WFLAG2  = -Wextra
WFLAG3  = -Werror
WFLAG4  = -Wno-unused-parameter
WFLAG5  = -Wno-unused-variable
WFLAG6  = -ggdb
WFLAGS  = ${WFLAG1} ${WFLAG2} ${WFLAG3} ${WFLAG4} ${WFLAG5} ${WFLAG6}
UFLAGS  = # Set on command line only

CFLAGS  = ${SFLAGS} ${GFLAGS} ${OFLAGS} ${WFLAGS} ${UFLAGS}
LDFLAGS = -lSDL2
ifeq ($(OS),Windows_NT)
INCSDLPATH = -I../dep/x86_64-w64-mingw32/include/SDL2
LIBSDLPATH = -L../dep/x86_64-w64-mingw32/lib
else
LDFLAGS = -lSDL2 -lSDL2main -lm
endif

all:    ${PROGRAM}

${PROGRAM}: main.c
	${CC} -o ../build/$@ ${CFLAGS} ${FILES.c} ${LDFLAGS} ${INCSDLPATH} ${LIBSDLPATH}

# Clean all the object files and the binary
clean:
#		@$(RM) -rfv $(TARGET)
