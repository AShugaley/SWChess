

#include <assert.h>
#include "Chess_gameUtils.h"
#include <stdlib.h>
#include <string.h>



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


SPArrayList* allPossibleMoves(chessGame* src, int row, int col){
    SPArrayList* array = spArrayListCreate(64);
   // printf("HELLO");
    int index = 0;
    for(int i = 0; i < BOARD_SIZE; i++){
        for(int j = 0; j<BOARD_SIZE; j++){
            if(isLegalMove(src, row, col, i, j)){
               // printf("%d,%d,%d,%d\n", row,col,i,j);
                spArrayListAddFirst(array, i, j, row, col, src->gameBoard[i][j],src->gameBoard[row][col]);
                index++;
            }
        }
    }
    return array;
}


bool isLegalMove(chessGame* src, int prev_pos_row, int prev_pos_col, int next_pos_row, int next_pos_col){
    char figure = src->gameBoard[prev_pos_row][prev_pos_col];
    //assert(figure != EMPTY_BOARD_POS);
    PLAYER_COLOR player;
    
    if(isWhiteFigure(figure))
        player = WHITES;
    else
        player = BLACKS;
    
    
    if(!isValidDestenetion(player, src->gameBoard[next_pos_row][next_pos_col]))
        return false;
    //printf("JAJA\n");
    if(!isValidMove(src, prev_pos_row,  prev_pos_col,  next_pos_row,  next_pos_col)) //check if move is valid stuturally.
        return false;
    //printf("EMP\n");
    if(checkAvoided(src, prev_pos_row, prev_pos_col, next_pos_row, next_pos_col))
        return true;
    else
        return false;

    
}

bool isValidMove(chessGame* src, int prev_pos_row, int prev_pos_col, int next_pos_row, int next_pos_col){
    char figure = src->gameBoard[prev_pos_row][prev_pos_col];
   // assert(figure != EMPTY_BOARD_POS);

    
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




CHESS_GAME_MESSAGE setChessMove(chessGame* src, int prev_pos_row, int prev_pos_col, int next_pos_row, int next_pos_col, bool needToCheckMoveValidiy, bool isValidForCrowning){
    if(needToCheckMoveValidiy){
        if(src->gameBoard[prev_pos_row][prev_pos_col] == EMPTY_BOARD_POS)
            return CHESS_GAME_INVALID_POSITION;
        if(!isValidBoardPosition(prev_pos_row, prev_pos_col, next_pos_row, next_pos_col))
            return CHESS_GAME_INVALID_ARGUMENT;
        if(!isLegalMove(src, prev_pos_row, prev_pos_col, next_pos_row, next_pos_col))
            return CHESS_GAME_INVALID_MOVE;
    }
    if(spArrayListIsFull(src->historyArray))
        spArrayListRemoveFirst(src->historyArray);
        
    spArrayListAddLast(src->historyArray, next_pos_row, next_pos_col, prev_pos_row, prev_pos_col,src->gameBoard[next_pos_row][next_pos_col],src->gameBoard[prev_pos_row][prev_pos_col]);
    src->gameBoard[next_pos_row][next_pos_col] = src->gameBoard[prev_pos_row][prev_pos_col];
    src->gameBoard[prev_pos_row][prev_pos_col] = EMPTY_BOARD_POS;
//    if(isValidForCrowning)
//        crowning(src,next_pos_row,next_pos_col);
    switchCurrentPlayer(src);
    return CHESS_GAME_SUCCESS;
}

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
    if(!isUnderPressure(src, king_row, king_col))
        return false;
    SPArrayListNode* move;
     //printf("SasdF\n");
    chessGame* gameCopy = copyChessGame(src);
    for(int i = 0; i< BOARD_SIZE; i++){
        for(int j = 0; j<BOARD_SIZE; j++){
             //printf("SggF\n");
            if(gameCopy->currentPlayer == WHITES){
                if(isWhiteFigure(gameCopy->gameBoard[i][j])){
                    SPArrayList* moves = allPossibleMoves(gameCopy, i, j);
                    while(!spArrayListIsEmpty(moves)){
                        move = spArrayListGetFirst(moves);
                        setChessMove(gameCopy, move->prev_pos_row, move->prev_pos_col, move->current_pos_row, move->current_pos_col, false, false);
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
                 //printf("SF\n");
                if(isBlackFigure(gameCopy->gameBoard[i][j])){
                    SPArrayList* moves = allPossibleMoves(gameCopy, i, j);
                    while(!spArrayListIsEmpty(moves)){
                        move = spArrayListGetFirst(moves);
                        //printf("S");
                        
                        setChessMove(gameCopy, move->prev_pos_row, move->prev_pos_col, move->current_pos_row, move->current_pos_col, false, false);
                       // printf("E");
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
   // assert((king_col != -1) && (king_row != -1));
    //printf("HOLE");
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
                    if(hasValidMove(src, i, j))
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
                         return false;
                 }
            }
        }
    }
   // assert((king_col != -1) && (king_row != -1));
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

    //assert((king_col != -1) && (king_row != -1));
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

    SPArrayList* moves = allPossibleMoves(src, row, col);
    bool needHelpPrints;
    SPArrayListNode* node;
    if((src->difficulty == 1)||(src->difficulty == 2))
        needHelpPrints = true;
    else
        needHelpPrints = false;
    while(!spArrayListIsEmpty(moves)){
        node = spArrayListGetLast(moves);
        
        
        //printf("<%d,%c>", node->current_pos_row + 1, getColumnChar(node->current_pos_col));
        //add * if threatend
        //add ^ if enemyfield
        //printf("\n");
        spArrayListRemoveLast(moves);
    }
    spArrayListDestroy(moves);
    
}


//chessGame* loadGmae(const char* filename){
//    chessGame* src = createChessGame(6, 2, 1, 1);
//    if(strstr(filename, "load ") != 0) {
//        filename += 5;
//    }
//    FILE *file = fopen(filename, "r+");
//    if(file == NULL){
//        printf("File cannot be opened\n");
//        return NULL;
//    }
//    char* p = NULL;
//    char c[1];
//    char input[128][64];
//    int  i = 0;
//    int j = 0;
//    int row_number;
//    while (c != EOF){
//       
//        fgets( c, 1, file);
//        
//        printf("AA %c AA",c);
//        c = p[0];
//        printf("one\n");
//        printf("AA %c AA",c);
//       
//        if(c == '<'){
//            printf("two\n");
//            j = 0;
//            while(c != '>'){
//                printf("three\n");
//                c = fgetc(file);
//                input[i][j] = c;
//                j++;
//            }
//            i++;
//        }
//    }
//    for(int index =0 ; index < i+1; index++){
//        printf("%s\n", input[index]);
//    }
//    for(int index =0 ; index < i+1; index++){
//        if(strstr(input[index], "current_turn") != NULL){
//            if(input[index+1][0] == '1'){
//                src->currentPlayer = WHITES;
//                index++;
//                continue;
//            }
//            if(input[index+1][0] == '0'){
//                src->currentPlayer = BLACKS;
//                index++;
//                continue;
//            }
//            printf("ERROR LOADGAME #1");
//        }
//        if(strstr(input[index], "game_mode") != NULL){
//            if(input[index+1][0] == '1'){
//                src->gameMode = ONE_PLAYER;
//                index++;
//                continue;
//            }
//            if(input[index+1][0] == '2'){
//                 src->gameMode = TWO_PLAYERS;
//                index++;
//                continue;
//            }
//            printf("ERROR LOADGAME #2");
//        }
//        if(strstr(input[index], "user_color") != NULL){
//            if(input[index+1][0] == '1'){
//                src->humanPlayerColor = WHITES;
//                index++;
//                continue;
//            }
//            if(input[index+1][0] == '2'){
//                src->humanPlayerColor = BLACKS;
//
//                index++;
//                continue;
//            }
//            printf("ERROR LOADGAME #3");
//        }
//        if(strstr(input[index], "difficulty") != NULL){
//            src->difficulty =  input[index+1][0] - '0';
//            index++;
//            continue;
//
//        }
//        if(strstr(input[index], "row") != NULL){
//            
//            row_number =  input[index][4] - '0';
//            index++;
//            for(int k = 0; k < 8; k++)
//                src->gameBoard[row_number][k] = input[index][k];
//            continue;
//        }
//    }
//    return src;
//}

bool saveGame(chessGame* src, const char* filename){
    printf("HEL");
    if(strstr(filename, "save ") != 0) {
        filename += 5;
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
