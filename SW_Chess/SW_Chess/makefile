CC = gcc
OBJS = main.o Widget.o SPWindow.o SPSimpleMainWindow.o SimpleButton.o SPCommon.o
 
EXEC = prog
CC_COMP_FLAG = -std=c99 -Wall -Wextra \
-Werror -pedantic-errors
SDL_COMP_FLAG = -I/usr/local/lib/sdl_2.0.5/include/SDL2 -D_REENTRANT
SDL_LIB = -L/usr/local/lib/sdl_2.0.5/lib -Wl,-rpath,/usr/local/lib/sdl_2.0.5/lib -Wl,--enable-new-dtags -lSDL2 -lSDL2main

$(EXEC): $(OBJS)
	$(CC) $(OBJS) $(SDL_LIB) -o $@
main.o: main.c SPSimpleMainWindow.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
Widget.o: Widget.c Widget.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
SimpleButton.o: SimpleButton.c SimpleButton.h Widget.h SPCommon.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
SPWindow.o: SPWindow.c SPWindow.h  
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
SPSimpleMainWindow.o: SPSimpleMainWindow.c SPSimpleMainWindow.h SPWindow.h SimpleButton.h Widget.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
SPCommon.o: SPCommon.c SPCommon.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
clean:
	rm -f *.o $(EXEC) $(UNIT_TESTS)
