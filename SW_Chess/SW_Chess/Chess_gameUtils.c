#include <assert.h>
#include "Chess_gameUtils.h"
#include <stdlib.h>
#include <string.h>
#include "ChessGUI_Utils.h"



chessGame* createChessGame(int historySize, GAME_MODE_PLAYER mode, PLAYER_COLOR humanColor, int difficulty)
{

    if (historySize <= 0)
        return NULL;
    
    chessGame *gameSt = (chessGame *)malloc(sizeof(chessGame));
    if (gameSt == NULL)
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


chessGame* copyChessGame(chessGame* src){ // INCOMPLETE!!
    chessGame *gameSt = (chessGame *)malloc(sizeof(chessGame));
    if (gameSt == NULL)
        return NULL;
    for(int i = 0; i<BOARD_SIZE; i++)
        for(int j = 0; j<BOARD_SIZE; j++)
            gameSt->gameBoard[i][j] = src->gameBoard[i][j];
    gameSt->currentPlayer = src->currentPlayer;
    
    gameSt->historyArray = spArrayListCopy(src->historyArray);
    
    gameSt->gameMode = src->gameMode;
    
    return gameSt;
    
}

void destroyChessGame(chessGame* src){
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


movesArray* allPossibleMoves(chessGame* src, int row, int col){
    movesArray* array = (movesArray *)malloc(sizeof(movesArray));
    
    int index = 0;
    for(int i = 0; i < BOARD_SIZE; i++){
        for(int j = 0; j<BOARD_SIZE; j++){
            if(isValidMove(src, row, col, i, j)){
                array->moves[index][0] =  row;
                array->moves[index][1] = col;
                array->moves[index][2] = i;
                array->moves[index][3] = j;
                index++;
            }
        }
    }
    array->moves[index][0] = -1;
    return array;
}


bool isValidMove(chessGame* src, int prev_pos_row, int prev_pos_col, int next_pos_row, int next_pos_col){
    
    char figure = src->gameBoard[prev_pos_row][prev_pos_col];
    assert(figure != EMPTY_BOARD_POS);
    PLAYER_COLOR player;
    
    
    if(isWhiteFigure(figure))
        player = WHITES;
    else
        player = BLACKS;
  
    
    if(!isValidDestenetion(player, src->gameBoard[next_pos_row][next_pos_col]))
        return false;
    
    switch(figure){
        case PAWN_BLACK:
        case PAWN_WHITE:
              return isValidPawnMove(src, prev_pos_row, prev_pos_col, next_pos_row, next_pos_col);
        case BISHOP_BLACK:
        case BISHOP_WHITE:
              return isValidBishopMove(src, prev_pos_row, prev_pos_col, next_pos_row, next_pos_col);
        case KNIGHT_BLACK:
        case KNIGHT_WHITE:
              return isValidKnightMove(src, prev_pos_row, prev_pos_col, next_pos_row, next_pos_col);
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
    printf("should not get here #453"); // delete
    return false;
}


CHESS_GAME_MESSAGE setChessMove(chessGame* src, int prev_pos_row, int prev_pos_col, int next_pos_row, int next_pos_col){
    if(src->gameBoard[prev_pos_row][prev_pos_col] == EMPTY_BOARD_POS)
        return CHESS_GAME_INVALID_POSITION;
    if(!isValidBoardPosition(prev_pos_row, prev_pos_col, next_pos_row, next_pos_col))
        return CHESS_GAME_INVALID_ARGUMENT;
    if(!isValidMove(src, prev_pos_row, prev_pos_col, next_pos_row, next_pos_col))
        return CHESS_GAME_INVALID_MOVE;
    src->gameBoard[next_pos_row][next_pos_col] = src->gameBoard[prev_pos_row][prev_pos_col];
    src->gameBoard[prev_pos_row][prev_pos_col] = EMPTY_BOARD_POS;
    switchCurrentPlayer(src);
    if(spArrayListIsFull(src->historyArray))
        spArrayListRemoveLast(src->historyArray);
    spArrayListAddLast(src->historyArray, next_pos_row, next_pos_col, prev_pos_row, prev_pos_col,src->gameBoard[prev_pos_row][prev_pos_col]);
    return CHESS_GAME_SUCCESS;
}


bool isCheckmate(chessGame* src){
    bool checkmate = false;
    switchCurrentPlayer(src);
    if(isCheck(src))
       checkmate = true;
    switchCurrentPlayer(src);
    return checkmate;
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
    bool has_valid_move = false;
    bool under_pressure = false;
    if(src->currentPlayer == WHITES){
        for(int i = 0; i<BOARD_SIZE; i++){
            for(int j = 0; j<BOARD_SIZE; j++){
                if(isWhiteFigure(src->gameBoard[i][j])){
                    if(src->gameBoard[i][j] == KING_WHITE){
                        under_pressure = isUnderPressure(src, i, j);
                    }
                    has_valid_move = hasValidMove(src, i, j);
                    if(has_valid_move)
                        return false;
                }
            }
        }
    }
    else{
        for(int i = 0; i<BOARD_SIZE; i++){
            for(int j = 0; j<BOARD_SIZE; j++){
                if(isWhiteFigure(src->gameBoard[i][j])){
                    if(src->gameBoard[i][j] == KING_WHITE){
                        under_pressure = isUnderPressure(src, i, j);
                    }
                has_valid_move = hasValidMove(src, i, j);
                }
                if(has_valid_move)
                    return false;
            }
        }
    }
    return (!under_pressure);
            
        
}

CHESS_GAME_MESSAGE undoChessPrevMove(chessGame* src, bool shouldPrint){
    if(spArrayListIsEmpty(src->historyArray))
        return CHESS_GAME_NO_HISTORY;
    SPArrayListNode* move = spArrayListGetLast(src->historyArray);
    spArrayListRemoveLast(src->historyArray);
    src->gameBoard[move->prev_pos_row][move->prev_pos_col] = src->gameBoard[move->current_pos_row][move->current_pos_col];
    src->gameBoard[move->current_pos_row][move->current_pos_col] = move->prev_pos_fig;
    switchCurrentPlayer(src);
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
    
    
    assert((king_col != -1) && (king_row != -1));
    return (isUnderPressure(src, king_row, king_col));

}

//pre - this function cannot be called if we have two players! Cannot at all!!
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

    movesArray* moves = allPossibleMoves(src, row, col);
    int counter = 0;
    char columnChar;
    bool needHelpPrints;
    if((src->difficulty == 1)||(src->difficulty == 2))
        needHelpPrints = true;
    else
        needHelpPrints = false;
    while(moves->moves[counter][0] != -1){
        columnChar = getColumnChar(moves->moves[counter][3]);
        printf("<%d,%c>", moves->moves[counter][2], columnChar);
        //add * if threatend
        //add ^ if enemyfield
        printf("\n");
        counter++;
    }
    
}


bool saveGame(chessGame* src, const char* filename){

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
    return true;
}

char* getCurrentPlayerStringName(chessGame* src){
    if(src->currentPlayer == WHITES)
        return "White";
    return "Black";
}


void checkGameEnd(chessGame* src){
    if(isStalemate(src)){
        printf("The game is tied\n");
        terminateGame(src);
    }
    if(isCheckmate(src)){
        if(src->currentPlayer == WHITES)
            printf("Checkmate! Black player wins the game\n");
        if(src->currentPlayer == BLACKS)
             printf("Checkmate! White player wins the game\n");
        terminateGame(src);
    }
    if(isCheck(src))
        printf("Check: %s King is threatened!\n",getCurrentPlayerStringName(src));
}



void terminateGame(chessGame* src){
    destroyChessGame(src);
    exit(0);
}
