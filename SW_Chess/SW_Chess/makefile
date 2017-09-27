CC = gcc
OBJS = Widget.o ChessGUI_Window.o Chess_GUIFlowMain.o ChessGUI_GameWindow.o ChessGUI_MainWindow.o Button.o ChessGUI_SettingsWindow.o ChessGUI_Utils.o ChessGUI_LoadWindow.o SPCommon.o Chess_ArrayList.o Chess_gameParser.o Chess_gameSettingsParser.o Chess_gameUtilsAux.o Chess_gameUtils.o SPMiniMax.o Chess_def.o Chess_FlowTwoPlayers.o Chess_FlowOnePlayer.o Chess_ConsoleFlowMain.o  main.o
EXEC = chessprog
CONSOLE_GAME_OBJS = Chess_FlowOnePlayer.o Chess_FlowTwoPlayers.o Chess_ConsoleFlowMain.o
GAME_UTILS = Chess_gameUtilsAux.o Chess_gameUtils.o SPMiniMax.o
GUI_GAME_OBJS = Widget.o ChessGUI_Window.o ChessGUI_GameWindow.o ChessGUI_MainWindow.o Button.o ChessGUI_SettingsWindow.o ChessGUI_Utils.o Chess_GUIFlowMain.o
AUX_UTILS = Chess_ArrayList.o Chess_gameParser.o Chess_gameSettingsParser.o
COMP_FLAG = -std=c99
SDL_COMP_FLAG = -I/usr/local/lib/sdl_2.0.5/include/SDL2 -D_REENTRANT
SDL_LIB = -L/usr/local/lib/sdl_2.0.5/lib -Wl,-rpath,/usr/local/lib/sdl_2.0.5/lib -Wl,--enable-new-dtags -lSDL2 -lSDL2main
$(EXEC): $(OBJS)
	$(CC) $(OBJS) $(SDL_LIB) -o $@
all: chessprog
Chess_def.o: Chess_def.h Chess_def.c
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
Chess_ArrayList.o: Chess_ArrayList.h Chess_ArrayList.c Chess_def.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
Chess_gameSettingsParser.o: Chess_gameSettingsParser.h Chess_gameSettingsParser.c
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
Chess_gameParser.o: Chess_gameParser.h Chess_gameParser.c
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
Chess_gameUtilsAux.o: Chess_gameUtilsAux.h Chess_gameUtilsAux.c Chess_ArrayList.h Chess_def.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
Chess_gameUtils.o: Chess_gameUtils.h Chess_gameUtils.c Chess_gameUtilsAux.h Chess_ArrayList.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
SPMiniMax.o: SPMiniMax.h SPMiniMax.c Chess_gameUtils.h Chess_gameUtilsAux.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
Chess_FlowOnePlayer.o: Chess_FlowOnePlayer.h Chess_FlowOnePlayer.c Chess_gameUtils.h SPMiniMax.h Chess_gameParser.h Chess_def.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
Chess_FlowTwoPlayers.o: Chess_FlowTwoPlayers.h Chess_FlowTwoPlayers.c Chess_FlowOnePlayer.h  Chess_gameUtils.h Chess_gameParser.h Chess_def.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
Chess_ConsoleFlowMain.o: Chess_ConsoleFlowMain.h Chess_ConsoleFlowMain.c Chess_FlowOnePlayer.h Chess_FlowTwoPlayers.h Chess_gameUtils.h Chess_gameParser.h Chess_def.h Chess_gameSettingsParser.h 
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
Widget.o: Widget.h Widget.c  
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
SPCommon.o: SPCommon.c SPCommon.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
Button.o: Button.h Button.c Widget.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
ChessGUI_Window.o: ChessGUI_Window.h ChessGUI_Window.h Chess_def.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
ChessGUI_SettingsWindow.o: ChessGUI_SettingsWindow.h ChessGUI_SettingsWindow.c ChessGUI_Window.h Widget.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
ChessGUI_LoadWindow.o: ChessGUI_LoadWindow.h ChessGUI_LoadWindow.c ChessGUI_Window.h Chess_gameUtils.h Widget.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
ChessGUI_MainWindow.o: ChessGUI_MainWindow.h ChessGUI_MainWindow.c ChessGUI_Window.h Chess_gameUtils.h Widget.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
ChessGUI_GameWindow.o: ChessGUI_GameWindow.h ChessGUI_GameWindow.c ChessGUI_Window.h Widget.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
Chess_GUIFlowMain.o: Chess_GUIFlowMain.h Chess_GUIFlowMain.c ChessGUI_MainWindow.h ChessGUI_LoadWindow.h ChessGUI_GameWindow.h ChessGUI_SettingsWindow.h Chess_gameUtils.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
ChessGUI_Utils.o: ChessGUI_Utils.h ChessGUI_Utils.c Chess_GUIFlowMain.h ChessGUI_Window.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
main.o: main.c Chess_GUIFlowMain.h Chess_ConsoleFlowMain.h 
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
clean:
	rm -f *.o $(EXEC)



