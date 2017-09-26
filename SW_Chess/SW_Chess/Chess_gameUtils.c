
#include <assert.h>
#include "Chess_gameUtils.h"
#include <stdlib.h>
#include <string.h>
#include "ChessGUI_Utils.h"

//mine

/* In all functions, we assume that the arguments are legal - e.g. 0<=pos<=7. We check it elsewhere - the comp will do so by himself, and we will check arguments from the user on input or higher on calculation chain.
 */

#include "ChessGUI_Utils.h"




chessGame* createChessGame(int historySize, GAME_MODE_PLAYER mode, PLAYER_COLOR humanColor, int difficulty)
{

    if (historySize <= 0)
        return NULL;
    
    chessGame *gameSt = (chessGame *)malloc(sizeof(chessGame));
    if (gameSt == NULL) /* mem alloc failure */
        return NULL;
    
    gameSt->difficulty = difficulty;
    gameSt->currentPlayer = WHITES;
    gameSt->humanPlayerColor = humanColor;
    gameSt->historyArray = spArrayListCreate(historySize);
    gameSt->gameMode = mode;
    
    initChessBoard(gameSt);
	initGameGUIBoard(gameSt);
    
    return gameSt;
    
}


chessGame* copyChessGame(chessGame* src){
    chessGame *gameSt = (chessGame *)malloc(sizeof(chessGame));
    if (gameSt == NULL) /* mem alloc failure */
        return NULL;
    
    for(int i = 0; i<BOARD_SIZE; i++)
        for(int j = 0; j<BOARD_SIZE; j++)
            gameSt->gameBoard[i][j] = src->gameBoard[i][j];
    
    
    gameSt->currentPlayer = src->currentPlayer;
    gameSt->difficulty = src->difficulty;
    gameSt->historyArray = spArrayListCopy(src->historyArray);
    gameSt->gameMode = src->gameMode;
    gameSt->humanPlayerColor = src->humanPlayerColor;
    
    return gameSt;
    
}

void destroyChessGame(chessGame* src)
{
    if (src != NULL)
    {
        spArrayListDestroy(src->historyArray);
        free(src);
    }
}


CHESS_GAME_MESSAGE chessConsolePrintBoard(chessGame* src) {
    
    if (src == NULL)
        return CHESS_GAME_INVALID_ARGUMENT;
    
    for (int i = BOARD_SIZE - 1; i>-1; i--) {
        printf("%d| ", i+1 );
        for (int j = 0; j<BOARD_SIZE; j++) {
            printf("%c ", src->gameBoard[i][j]);
        }
        printf("|\n");
    }
    printf("  -----------------  \n");
    printf("   A B C D E F G H   \n");
    return CHESS_GAME_SUCCESS;
}


SPArrayList* allPossibleMoves(chessGame* src, int row, int col){
    SPArrayList* array = spArrayListCreate(64);
   
    
    for(int i = 0; i < BOARD_SIZE; i++){
        for(int j = 0; j<BOARD_SIZE; j++){
            if(isLegalMove(src, row, col, i, j)){
                spArrayListAddFirst(array, i, j, row, col, src->gameBoard[i][j],src->gameBoard[row][col],-1);
            }
        }
    }
    return array;
}


bool isLegalMove(chessGame* src, int prev_pos_row, int prev_pos_col, int next_pos_row, int next_pos_col){
    char figure = src->gameBoard[prev_pos_row][prev_pos_col];
    
    PLAYER_COLOR player;
    
    if(isWhiteFigure(figure))
        player = WHITES;
    else
        player = BLACKS;
    
    
    if(!isValidDestenetion(player, src->gameBoard[next_pos_row][next_pos_col]))
        return false;
    
    if(!isValidMove(src, prev_pos_row,  prev_pos_col,  next_pos_row,  next_pos_col))
        return false;
    
    if(checkAvoided(src, prev_pos_row, prev_pos_col, next_pos_row, next_pos_col))
        return true;
    else
        return false;

    
}

bool isValidMove(chessGame* src, int prev_pos_row, int prev_pos_col, int next_pos_row, int next_pos_col){
    char figure = src->gameBoard[prev_pos_row][prev_pos_col];
   

    
    switch(figure){
        case PAWN_BLACK:
        case PAWN_WHITE:
            return isValidPawnMove(src, prev_pos_row, prev_pos_col, next_pos_row, next_pos_col);
       
        case BISHOP_BLACK:
        case BISHOP_WHITE:
            return isValidBishopMove(src, prev_pos_row, prev_pos_col, next_pos_row, next_pos_col);
            
        case KNIGHT_BLACK:
        case KNIGHT_WHITE:
            return  isValidKnightMove(src, prev_pos_row, prev_pos_col, next_pos_row, next_pos_col);
         
        case ROOK_BLACK:
        case ROOK_WHITE:
            return isValidRookMove(src, prev_pos_row, prev_pos_col, next_pos_row, next_pos_col);
           
        case QUEEN_BLACK:
        case QUEEN_WHITE:
            return isValidQueenMove(src, prev_pos_row, prev_pos_col, next_pos_row, next_pos_col);
        
        case KING_WHITE:
        case KING_BLACK:
            return isValidKingMove(src, prev_pos_row, prev_pos_col, next_pos_row, next_pos_col);
           
    }

    return true;
}




CHESS_GAME_MESSAGE setChessMove(chessGame* src, int prev_pos_row, int prev_pos_col, int next_pos_row, int next_pos_col, bool needToCheckMoveValidiy, bool isValidForCrowning, int figureIndex){
    if(needToCheckMoveValidiy){
        if(src->gameBoard[prev_pos_row][prev_pos_col] == EMPTY_BOARD_POS)
            return CHESS_GAME_INVALID_POSITION;
        if(isWhiteFigure(src->gameBoard[prev_pos_row][prev_pos_col]) && src->currentPlayer == BLACKS)
            return CHESS_GAME_INVALID_POSITION;
        if(isBlackFigure(src->gameBoard[prev_pos_row][prev_pos_col]) && src->currentPlayer == WHITES)
            return CHESS_GAME_INVALID_POSITION;
        if(!isValidBoardPosition(prev_pos_row, prev_pos_col, next_pos_row, next_pos_col))
            return CHESS_GAME_INVALID_ARGUMENT;
        if(!isLegalMove(src, prev_pos_row, prev_pos_col, next_pos_row, next_pos_col))
            return CHESS_GAME_INVALID_MOVE;
    }
    if(spArrayListIsFull(src->historyArray))
        spArrayListRemoveFirst(src->historyArray);
        
    spArrayListAddLast(src->historyArray, next_pos_row, next_pos_col, prev_pos_row, prev_pos_col,src->gameBoard[next_pos_row][next_pos_col],src->gameBoard[prev_pos_row][prev_pos_col],figureIndex);
    src->gameBoard[next_pos_row][next_pos_col] = src->gameBoard[prev_pos_row][prev_pos_col];
    src->gameBoard[prev_pos_row][prev_pos_col] = EMPTY_BOARD_POS;
//    if(isValidForCrowning) //todo //todelete
//        crowning(src,next_pos_row,next_pos_col);
    switchCurrentPlayer(src);
    return CHESS_GAME_SUCCESS;
}


 //todo //todelete
void crowning(chessGame* src,int row,int col){
    
    if((src->gameBoard[row][col] != PAWN_BLACK) && (src->gameBoard[row][col] != PAWN_WHITE))
        return; /* no crowning */
    if(!(((src->currentPlayer == WHITES)&&(row == 7))||((src->currentPlayer == BLACKS)&&(row == 0))))
        return; /* no crowning */
    if((src->gameMode == TWO_PLAYERS)||(src->currentPlayer == src->humanPlayerColor)){
        return;
           //human crowning
    }
    /* if we are here - this is a computer crowning, just put a queen */
    if(src->currentPlayer == BLACKS)
        src->gameBoard[row][col] = QUEEN_BLACK;
    else
        src->gameBoard[row][col] = QUEEN_WHITE;
    return;
}



bool isCheckmate(chessGame* src){
    int king_row = -1, king_col = -1;
    /* first find the king */
    for(int i = 0; i< BOARD_SIZE; i++){
        for(int j = 0; j<BOARD_SIZE; j++){
            if(src->currentPlayer == WHITES){
                if(src->gameBoard[i][j] == KING_WHITE){
                    king_row = i;
                    king_col = j;
                }
            }
            else{
                
                if(src->gameBoard[i][j] == KING_BLACK){
                    king_row = i;
                    king_col = j;
                }
            }
        }
    }
    
    if(!isUnderPressure(src, king_row, king_col)) /* king isn't under attack */
        return false;
    SPArrayListNode* move;
    
    chessGame* gameCopy = copyChessGame(src);
    
    /* If we are here - we have a check. We don't use the 'is check' fucntion because we need to find the king anyway, and that will be 
     be just of usless code (sending a touple from place to place) - bad programming, as we will have a findKing function, and we'll 
     have to use in twice. Or have two isCheck functions */
    
    /* Now we need to check if this palyer has any move that will eliminate this check (and not result in another one) */
    
    for(int i = 0; i< BOARD_SIZE; i++){
        for(int j = 0; j<BOARD_SIZE; j++){
            if(gameCopy->currentPlayer == WHITES){
                if(isWhiteFigure(gameCopy->gameBoard[i][j])){
                    SPArrayList* moves = allPossibleMoves(gameCopy, i, j);
                    while(!spArrayListIsEmpty(moves)){
                        move = spArrayListGetFirst(moves);
                        setChessMove(gameCopy, move->prev_pos_row, move->prev_pos_col, move->current_pos_row, move->current_pos_col, false, false,-1);
                        if(!isUnderPressure(gameCopy, king_row, king_col)){
                            spArrayListDestroy(moves);
                            destroyChessGame(gameCopy);
                            return false;
                        }
                        undoChessPrevMove(gameCopy, false);
                        spArrayListRemoveFirst(moves);
                    }
                    spArrayListDestroy(moves);
                }
            }
           
            else{
                
                if(isBlackFigure(gameCopy->gameBoard[i][j])){
                    SPArrayList* moves = allPossibleMoves(gameCopy, i, j);
                    while(!spArrayListIsEmpty(moves)){
                        move = spArrayListGetFirst(moves);
                     
                        
                        setChessMove(gameCopy, move->prev_pos_row, move->prev_pos_col, move->current_pos_row, move->current_pos_col, false, false,-1);
                 
                        if(!isUnderPressure(gameCopy, king_row, king_col)){
                            spArrayListDestroy(moves);
                            destroyChessGame(gameCopy);
                            return false;
                        }
                        undoChessPrevMove(gameCopy, false);
                        spArrayListRemoveFirst(moves);
                    }
                    spArrayListDestroy(moves);
                }
            }
        }
    }
    destroyChessGame(gameCopy);

    return true;
}

bool hasValidMove(chessGame* src, int row, int col){
    for(int i = 0; i<BOARD_SIZE; i++){
        for(int j = 0; j<BOARD_SIZE; j++){
            if(isValidMove(src, row, col, i, j))
                return true;
        }
    }
    return false;
}


bool isStalemate(chessGame* src){
    int king_row = -1, king_col = -1;
    for(int i = 0; i< BOARD_SIZE; i++){
        for(int j = 0; j<BOARD_SIZE; j++){
            if(src->currentPlayer == WHITES){
                if(isWhiteFigure(src->gameBoard[i][j])){
                    if(src->gameBoard[i][j] == KING_WHITE){
                        king_row = i;
                        king_col = j;
                    }
                    if(hasValidMove(src, i, j)) /* ANY figure of this player has a legal move */
                        return false;
                }
            }
            else{
                 if(isBlackFigure(src->gameBoard[i][j])){
                     if(src->gameBoard[i][j] == KING_BLACK){
                         king_row = i;
                         king_col = j;
                     }
                     if(hasValidMove(src, i, j))
                         return false; /* ANY figure of this player has a legal move */
                 }
            }
        }
    }
   /* Tie: no valid moves, and king NOT under threat */
    return (!isUnderPressure(src, king_row, king_col) && !hasValidMove(src, king_row, king_col));
    
}

CHESS_GAME_MESSAGE undoChessPrevMove(chessGame* src, bool shouldPrint){
    if(spArrayListIsEmpty(src->historyArray))
        return CHESS_GAME_NO_HISTORY;
    SPArrayListNode* move = spArrayListGetLast(src->historyArray);
    spArrayListRemoveLast(src->historyArray);
    src->gameBoard[move->prev_pos_row][move->prev_pos_col] = move->moving_figure;
    src->gameBoard[move->current_pos_row][move->current_pos_col] = move->prev_pos_fig;
    switchCurrentPlayer(src);
    /* This way we can use the same function internally, without printing to console */
    if(shouldPrint)
        printf("Undo move for player %s : <%d,%c> -> <%d,%c>\n",getCurrentPlayerStringName(src),move->prev_pos_row + 1, getColumnChar(move->prev_pos_col),move->current_pos_row + 1, getColumnChar(move->current_pos_col));
    return CHESS_GAME_SUCCESS;
    
}

bool isCheck(chessGame* src){
    
    int king_row = -1, king_col = -1;
    for(int i = 0; i< BOARD_SIZE; i++){
        for(int j = 0; j<BOARD_SIZE; j++){
            if(src->currentPlayer == WHITES){
                if(src->gameBoard[i][j] == KING_WHITE){
                    king_row = i;
                    king_col = j;
                }
            }
            else{
          
                if(src->gameBoard[i][j] == KING_BLACK){
                    king_row = i;
                    king_col = j;
                }
            }
        }
    }

    
    return (isUnderPressure(src, king_row, king_col));

}


void get_moves(chessGame* src, int row, int col){
    if((row > 7)||(row < 0)||(col > 7)||(col < 0)){
        printf("Invalid position on the board\n");
        return;
    }
    if((src->currentPlayer == WHITES) && (!isWhiteFigure(src->gameBoard[row][col]))){
        printf("The specified position does not contain white player piece\n");
        return;
    }
    
    
    if((src->currentPlayer == BLACKS) && (!isBlackFigure(src->gameBoard[row][col]))){
        printf("The specified position does not contain black player piece\n");
        return;
    }

    SPArrayList* moves = allPossibleMoves(src, row, col);
    bool needHelpPrints;
    SPArrayListNode* node;
    if((src->difficulty == 1)||(src->difficulty == 2))
        needHelpPrints = true;
    else
        needHelpPrints = false;
    while(!spArrayListIsEmpty(moves)){
        node = spArrayListGetLast(moves);
        
        //todo //todelete
        
        //printf("<%d,%c>", node->current_pos_row + 1, getColumnChar(node->current_pos_col));
        //add * if threatend
        //add ^ if enemyfield
        //printf("\n");
        spArrayListRemoveLast(moves);
    }
    spArrayListDestroy(moves);
    
}

void loadGameInPlace(const char* filename, chessGame* src) {
	chessGame* newGame = loadGame(filename);
	if (newGame == NULL)
		return;
	for (int i = 0; i<8; i++)
		for (int j = 0; j<8; j++)
			src->gameBoard[i][j] = newGame->gameBoard[i][j];
	src->difficulty = newGame->difficulty;
	src->gameMode = newGame->gameMode;
	src->humanPlayerColor = newGame->humanPlayerColor;
	spArrayListDestroy(src->historyArray);
	src->historyArray = spArrayListCopy(newGame->historyArray);
	src->currentPlayer = newGame->currentPlayer;
	src->uiMode = newGame->uiMode;
	destroyChessGame(newGame);
	return;
}


void saveGameInLastestSlot(chessGame* src) {
	chessGame* tempGame = loadGame(SAVE_SLOT_4);
	if (tempGame)
		saveGame(tempGame, SAVE_SLOT_5);
	destroyChessGame(tempGame);
	tempGame = loadGame(SAVE_SLOT_3);
	if (tempGame)
		saveGame(tempGame, SAVE_SLOT_4);
	destroyChessGame(tempGame);
	tempGame = loadGame(SAVE_SLOT_2);
	if (tempGame)
		saveGame(tempGame, SAVE_SLOT_3);
	destroyChessGame(tempGame);
	tempGame = loadGame(SAVE_SLOT_1);
	if (tempGame)
		saveGame(tempGame, SAVE_SLOT_2);
	destroyChessGame(tempGame);
	saveGame(src, SAVE_SLOT_1);
}



void loadGameInPlace(const char* filename, chessGame* src){
    chessGame* newGame = loadGmae(filename);
    if(newGame == NULL)
        return;
    for(int i = 0; i<8; i++)
        for(int j = 0; j<8; j++)
            src->gameBoard[i][j] = newGame->gameBoard[i][j];
    src->difficulty = newGame->difficulty;
    src->gameMode = newGame->gameMode;
    src->humanPlayerColor = newGame->humanPlayerColor;
    spArrayListDestroy(src->historyArray);
    src->historyArray = spArrayListCopy(newGame->historyArray);
    src->currentPlayer = newGame->currentPlayer;
    src->uiMode = newGame->uiMode;
    destroyChessGame(newGame);
    return;
}


void saveGameInLastestSlot(chessGame* src){
    chessGame* tempGame = loadGmae(SAVE_SLOT_4);
    if(tempGame)
        saveGame(tempGame, SAVE_SLOT_5);
    destroyChessGame(tempGame);
    tempGame = loadGmae(SAVE_SLOT_3);
    if(tempGame)
        saveGame(tempGame, SAVE_SLOT_4);
    destroyChessGame(tempGame);
    tempGame = loadGmae(SAVE_SLOT_2);
    if(tempGame)
        saveGame(tempGame, SAVE_SLOT_3);
    destroyChessGame(tempGame);
    tempGame = loadGmae(SAVE_SLOT_1);
    if(tempGame)
        saveGame(tempGame, SAVE_SLOT_2);
    destroyChessGame(tempGame);
    saveGame(src, SAVE_SLOT_1);
}

/* Does not check if file is valid (in correct format */
chessGame* loadGame(const char* filename){
    chessGame* src = createChessGame(6, 2, 0, 1);
    if(strstr(filename, "load ") != 0) { /* Sometimes we send the whole command, and not just the path */
        filename += 5;
    }

    FILE *f = fopen(filename, "r+");
    if(f == NULL){
        printf("Error: File does not exist or cannot be opened\n"); 
        return NULL;
    }
    char* currentToken;
    int row;
    char delimiter[] = " \t\r\n<>";
    char currentStr[1024] = "\0";
    char * buffer = 0;
    long length;
   
    
    if (f) /* First we get the whole file */
    {
        fseek (f, 0, SEEK_END);
        length = ftell (f);
        fseek (f, 0, SEEK_SET);
        buffer = malloc (length);
        if (buffer)
        {
            fread (buffer, 1, length, f);
        }
        fclose (f);
    }
    /* printf("%s",buffer); */
    
    strcpy(currentStr, buffer);
    
    currentToken = strtok(currentStr, delimiter);
    free(buffer);
    /* Now we parse it */
    while(strncmp(currentToken,"/game",5) != 0){

        currentToken = strtok(NULL, delimiter);

        if(strncmp(currentToken, "difficulty", 10) == 0){

            currentToken = strtok(NULL, delimiter);
            src->difficulty = atoi(currentToken);
        }
        if(strncmp(currentToken, "current_turn", 12) == 0){
      
            currentToken = strtok(NULL, delimiter);
            if(strncmp(currentToken, "1", 1) == 0){
                src->currentPlayer = WHITES;
                continue;
            }
            if(strncmp(currentToken, "0", 1) == 0){
                src->currentPlayer = BLACKS;
                continue;
            }
       
        
        }
        if(strncmp(currentToken, "game_mode", 9) == 0){
   
            currentToken = strtok(NULL, delimiter);

            if(strncmp(currentToken, "1", 1) == 0){
                src->gameMode = ONE_PLAYER;
              
            }
            if(strncmp(currentToken, "2", 1) == 0){
                src->gameMode = TWO_PLAYERS;
                
            }
            /* need to advance it twice as the next one is "/game_mode" and it ends the loop prematurely */
            currentToken = strtok(NULL, delimiter);
            currentToken = strtok(NULL, delimiter);
       
        }
        if(strncmp(currentToken, "user_color", 10) == 0){

            currentToken = strtok(NULL, delimiter);

            if(strncmp(currentToken, "0", 1) == 0){
 
                src->humanPlayerColor = BLACKS;
                continue;
            }
            if(strncmp(currentToken, "1", 1) == 0){
 
                src->humanPlayerColor = WHITES;
                continue;
            }
       
        }
        if(strncmp(currentToken, "row_", 4) == 0){

            row = currentToken[4]  - '0';
            currentToken = strtok(NULL, delimiter);
            for(int k = 0; k < 8; k++)
                src->gameBoard[row-1][k] = currentToken[k];

        }


    }
    
    return src;

   }

bool saveGame(chessGame* src, const char* filename){

    if(strstr(filename, "save ") != 0) { /* Sometimes we send the whole command, and not just the path */
        filename += 5;					//////////////// +5 ? //////////////
    }
    FILE *file = fopen(filename, "w+");
    if(file == NULL){
        printf("File cannot be created or modified\n");
        return false;
    }
    fprintf(file, "<?xml version=""1.0""encoding=""UTF-8""?>\n<game>\n");
    if(src->currentPlayer == WHITES)
        fprintf(file, "<current_turn>%s</current_turn>\n", "1");
    else
        fprintf(file, "<current_turn>%s</current_turn>\n", "0");
    if((src->gameMode == ONE_PLAYER) && (src->humanPlayerColor == BLACKS)){
        fprintf(file, "<game_mode>%s</game_mode>\n", "1");
        fprintf(file, "<user_color>%s</user_color>\n", "0");
        fprintf(file, "<difficulty>%d</difficulty>\n", src->difficulty);
    }
    if((src->gameMode == ONE_PLAYER) && (src->humanPlayerColor == WHITES)){
        fprintf(file, "<game_mode>%s</game_mode>\n", "1");
        fprintf(file, "<user_color>%s</user_color>\n", "1");
        fprintf(file, "<difficulty>%d</difficulty>\n",src->difficulty);
    }
    if(src->gameMode == TWO_PLAYERS){
        fprintf(file, "<game_mode>%s</game_mode>\n", "2");
        fprintf(file, "<user_color></user_color>\n");
    }
    
    fprintf(file, "<board>\n");
    for(int i = BOARD_SIZE; i >0; i--){
        fprintf(file, "<row_%d>", i);
        for(int j = 0; j<BOARD_SIZE; j++){
            fprintf(file, "%c", src->gameBoard[i-1][j]);
        }
        fprintf(file, "</row_%d>\n", i);
    }
    
    fprintf(file, "</board>\n");
    fprintf(file, "</game>\n");
    fclose(file);
    return true;
}

char* getCurrentPlayerStringName(chessGame* src){
    if(src->currentPlayer == WHITES)
        return "white";
    return "black";
}


char* getFigureStringName(char figure){
    switch (figure) {
        case QUEEN_BLACK:
        case QUEEN_WHITE:
            return "queen";
        case PAWN_BLACK:
        case PAWN_WHITE:
            return "pawn";
        case KNIGHT_BLACK:
        case KNIGHT_WHITE:
            return "knight";
        case BISHOP_BLACK:
        case BISHOP_WHITE:
            return "bishop";
        case KING_BLACK:
        case KING_WHITE:
            return "king";
        case ROOK_BLACK:
        case ROOK_WHITE:
            return "rook";
    }
    return "error";
}


void checkGameEnd(chessGame* src){
    if(isStalemate(src)){
        printf("The game ends in a tie\n");
        terminateGame(src);
    }
    if(isCheckmate(src)){
        /* we have a fucntion to get a string name of the player, but here we want a capital letter, so this is shorter */
        if(src->currentPlayer == WHITES)
            printf("Checkmate! Black player wins the game\n");
        if(src->currentPlayer == BLACKS)
             printf("Checkmate! White player wins the game\n");
        terminateGame(src);
    }
    if(isCheck(src))
        printf("Check: %s King is threatened!\n",getCurrentPlayerStringName(src));
}

 
/* bye */
void terminateGame(chessGame* src){
    destroyChessGame(src);
    exit(0);
}

SPArrayListNode* GUIModeUndo(chessGame* src){
    
    if(spArrayListIsEmpty(src->historyArray))
        return NULL;
    SPArrayListNode* move = spArrayListGetLast(src->historyArray);
    spArrayListRemoveLast(src->historyArray);
    src->gameBoard[move->prev_pos_row][move->prev_pos_col] = move->moving_figure;
    src->gameBoard[move->current_pos_row][move->current_pos_col] = move->prev_pos_fig;
    switchCurrentPlayer(src);
    return move;
}
