#include"conio2.h"
#include"functions.h"

int main() {
	int zn = 0, quit = FALSE, player = BLACK_PL, score_black = 0, score_white = 0, capture = FALSE, board_size = 0, x = BOARD_X + 1, y = BOARD_Y + 1, x_ko = 0, y_ko = 0;
	float bonus_points = 0;
	char** board_tab;

	// if the program is compiled in pure C, then we need to initialize
	// the library ourselves; __cplusplus is defined only if a C++ compiler
	// is used
#ifndef __cplusplus
	Conio2_Init();
#endif
	// set screen size
	textmode(C4350);

	// settitle sets the window title
	settitle("Jakub Falk 193252");

	// hide the blinking cursor
	_setcursortype(_NOCURSOR);

	// game state editor - initial configuration of black stones
	initial_configuration(zn, score_black, score_white, board_size, x, y, player, capture, x_ko, y_ko, board_tab, bonus_points);

	do {
		// make sure that cursor is not not visible
		_setcursortype(_NOCURSOR);

		// we set black to be the background color
		textbackground(BLACK);

		// clear the screen
		clrscr();

		// we set the text color
		textcolor(LIGHTGRAY);

		// show a legend
		draw_legend(score_black, score_white, player);

		// draw a board
		draw_board(board_size, board_tab);

		// check if cursor is not out of the board
		check_cursor(board_size, x, y);

		// draw position of the cursor in legend
		draw_pos_cursor(x, y);

		// move cursor around the board
		move_cursor(zn, x, y);

		// i - place a stone
		if (zn == 'i') place_stone(zn, score_black, score_white, board_size, x, y, player, capture, x_ko, y_ko, board_tab);

		// n - new game
		if (zn == 'n') new_game(zn, score_black, score_white, board_size, x, y, player, capture, x_ko, y_ko, board_tab, bonus_points);

		// q - quit the program
		if (zn == 'q') quit_program(zn, quit, board_size);

		// s - save the game state
		if (zn == 's') save_game_state(zn, score_black, score_white, board_size, player, x_ko, y_ko, board_tab, bonus_points);

		// l - load the game state
		if (zn == 'l') load_game_state(zn, score_black, score_white, board_size, player, x_ko, y_ko, board_tab, x, y, bonus_points);

		// f - finish the game
		if (zn == 'f') finish_game(zn, board_size, board_tab, score_black, score_white, quit, bonus_points);
		
	} while (quit != TRUE);

	// free memory from board array
	delete[] board_tab;

	_setcursortype(_NORMALCURSOR);	// show the cursor so it will be
	// visible after the program ends
	return 0;
}