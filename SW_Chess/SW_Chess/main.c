#include <stdio.h>
#include <stdlib.h>
#include "Chess_gameUtils.h"
#include "Chess_gameUtilsAux.h"
#include "SPMiniMax.h"


#include <stdbool.h>

#include "unit_test_util.h"
#include "Chess_gameParser.h"
#include "Chess_gameSettingsParser.h"
#include "Chess_ArrayList.h"


#define CAPACITY_SIZE 10

void TestBoard(chessGame* src);
static bool spParserCheckIsInt();
static bool spParserCheckParseLine();



//////////////////check - ALEX//////////////////
void TestBoard(chessGame* src) {
	for (int i = 0; i < BOARD_SIZE; i++)
		for (int j = 0; j < BOARD_SIZE; j++)
			src->gameBoard[i][j] = EMPTY_BOARD_POS;


	//whites
	src->gameBoard[1][5] = QUEEN_WHITE;
	//src->gameBoard[0][1] = KING_WHITE;
	//    src->gameBoard[0][1] = KNIGHT_WHITE;
	//    src->gameBoard[0][2] = BISHOP_WHITE;
	//    src->gameBoard[0][3] = QUEEN_WHITE;
	//    src->gameBoard[0][4] = KING_WHITE;
	//    src->gameBoard[0][5] = BISHOP_WHITE;
	//    src->gameBoard[0][6] = KNIGHT_WHITE;
	//    src->gameBoard[0][7] = ROOK_WHITE;



	//blacks
	src->gameBoard[2][6] = QUEEN_BLACK;
	//src->gameBoard[5][0] = KING_BLACK;
	//    src->gameBoard[7][1] = KNIGHT_BLACK;
	//    src->gameBoard[7][2] = BISHOP_BLACK;
	//    src->gameBoard[7][3] = QUEEN_BLACK;
	//    src->gameBoard[7][4] = KING_BLACK;
	//    src->gameBoard[7][5] = BISHOP_BLACK;
	//    src->gameBoard[7][6] = KNIGHT_BLACK;
	//    src->gameBoard[7][7] = ROOK_BLACK;

}
	//////////////////check - ALEX- end//////////////////


	//////////////////check - MOR//////////////////
static bool spParserCheckIsInt()
{
	ASSERT_TRUE(spParserIsInt("1"));
	ASSERT_TRUE(spParserIsInt("11"));
	ASSERT_TRUE(spParserIsInt("111"));
	ASSERT_TRUE(spParserIsInt("-1"));
	ASSERT_TRUE(spParserIsInt("-11"));
	ASSERT_TRUE(spParserIsInt("-111"));
	ASSERT_TRUE(spParserIsInt("01"));
	ASSERT_TRUE(spParserIsInt("011"));
	ASSERT_TRUE(spParserIsInt("0111"));
	ASSERT_TRUE(spParserIsInt("-01"));
	ASSERT_TRUE(spParserIsInt("-011"));
	ASSERT_TRUE(spParserIsInt("-0111"));

	ASSERT_TRUE(spParserIsInt("-0"));
	ASSERT_TRUE(spParserIsInt("00000"));
	//ASSERT_TRUE(spParserIsInt("2.1"));  //this is false, just checked 
	return true;
}
/*
static bool spParserCheckParseLine() {
	CHESS_COMMAND cmd;
	cmd = spParserPraseLine("undo");
	ASSERT_TRUE(cmd.cmd == CHESS_UNDO_MOVE);
	cmd = spParserPraseLine("add_disc	17\n");
	ASSERT_TRUE(cmd.cmd == SP_ADD_DISC && cmd.validArg && cmd.arg == 17);
	cmd = spParserPraseLine("	add_disc 17\n");
	ASSERT_TRUE(cmd.cmd == SP_ADD_DISC && cmd.validArg && cmd.arg == 17);
	cmd = spParserPraseLine("aDd_disc 17");
	ASSERT_TRUE(cmd.cmd == SP_INVALID_LINE && !cmd.validArg);

	/////////////////////// Additional Checking (Mor) - WORKING 
	cmd = spParserPraseLine("	add_disc 17\t");
	ASSERT_TRUE(cmd.cmd == SP_ADD_DISC && cmd.validArg && cmd.arg == 17);
	cmd = spParserPraseLine("	unD 17\n");
	ASSERT_TRUE(cmd.cmd == SP_INVALID_LINE && !cmd.validArg);
	cmd = spParserPraseLine("	undo_move\n");
	ASSERT_TRUE(cmd.cmd == SP_UNDO_MOVE && !cmd.validArg);
	cmd = spParserPraseLine("  restart   \n ");
	ASSERT_TRUE(cmd.cmd == SP_RESTART && !cmd.validArg);
	/////////////////////////////

	return true;
	}
	*/

static bool spArrayListBasicGetTest() {
	SPArrayList* list = spArrayListCreate(CAPACITY_SIZE);
	ASSERT_TRUE(list != NULL);
	for (int i = 0; i < CAPACITY_SIZE; i++) {
		ASSERT_TRUE(spArrayListAddLast(list, i, i,i,i ) == SP_ARRAY_LIST_SUCCESS);
	}
	for (int i = 0; i < CAPACITY_SIZE; i++) {
		ASSERT_TRUE(spArrayListGetAt(list, i) == i);
	}
	spArrayListDestroy(list);
	return true;
}

static bool spArrayListBasicCopyTest() {
	SPArrayList* list = spArrayListCreate(CAPACITY_SIZE);
	ASSERT_TRUE(list != NULL);
	for (int i = 0; i < CAPACITY_SIZE; i++) {
		ASSERT_TRUE(spArrayListAddFirst(list, i,i,i,i) == SP_ARRAY_LIST_SUCCESS);
	}
	SPArrayList* copyList = spArrayListCopy(list);
	for (int i = 0; i < CAPACITY_SIZE; i++) {
		ASSERT_TRUE(spArrayListGetAt(copyList, i) == spArrayListGetAt(list, i));
	}
	spArrayListDestroy(list);
	spArrayListDestroy(copyList);
	return true;
}

static bool spArrayListBasicRemoveTest() {
	SPArrayList* list = spArrayListCreate(CAPACITY_SIZE);
	ASSERT_TRUE(list != NULL);
	for (int i = 0; i < CAPACITY_SIZE; i++) {
		ASSERT_TRUE(spArrayListAddFirst(list, i,i,i,i) == SP_ARRAY_LIST_SUCCESS);
	}
	ASSERT_TRUE(spArrayListSize(list) == CAPACITY_SIZE);
	for (int i = 0; i < CAPACITY_SIZE; i++) {
		ASSERT_TRUE(spArrayListRemoveFirst(list) == SP_ARRAY_LIST_SUCCESS);
		ASSERT_TRUE(spArrayListSize(list) == CAPACITY_SIZE - i - 1);
	}
	ASSERT_TRUE(spArrayListIsEmpty(list));
	spArrayListDestroy(list);
	return true;
}

static bool spArrayListBasicAddTest() {
	SPArrayList* list = spArrayListCreate(CAPACITY_SIZE);
	ASSERT_TRUE(list != NULL);
	for (int i = 0; i < CAPACITY_SIZE; i++) {
		ASSERT_TRUE(spArrayListAddFirst(list, i,i,i,i) == SP_ARRAY_LIST_SUCCESS);
		ASSERT_TRUE(spArrayListSize(list) == i + 1);
	}
	ASSERT_TRUE(spArrayListSize(list) == CAPACITY_SIZE);
	spArrayListDestroy(list);
	return true;
}
static bool spArrayListCreateTest() {
	SPArrayList* list = spArrayListCreate(CAPACITY_SIZE);
	ASSERT_TRUE(list != NULL);
	spArrayListDestroy(list);
	return true;
}
	//////////////////check - MOR - end//////////////////




int main(int argc, const char * argv[]) {
	
	//////////////////check - ALEX//////////////////
	printf("Hello, World!\n");
    chessGame* src = createChessGame(5, TWO_PLAYERS);
    TestBoard(src);
    chessConsolePrintBoard(src);
    printf("hello\n");
    printf("\n%d\n",isValidMove(src, 1, 5, 3, 7) == true);
    printf("\n%d\n",isValidMove(src, 1, 5, 2, 6) == true);
    

	////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////


	//////////////////check - MOR//////////////////
	RUN_TEST(spParserCheckIsInt);
	RUN_TEST(spParserCheckParseLine);
	RUN_TEST(spArrayListCreateTest);
	RUN_TEST(spArrayListBasicAddTest);
	RUN_TEST(spArrayListBasicRemoveTest);
	RUN_TEST(spArrayListBasicGetTest);
	RUN_TEST(spArrayListBasicCopyTest);
	
    
    return 0;
}


