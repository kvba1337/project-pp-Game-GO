#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#define LEGEND_X  1 // legend position (x)
#define LEGEND_Y  1 // legend position (y)
#define BOARD_X   50 // board position (x)
#define BOARD_Y   1 // board position (y)
#define MARGIN      2 // margin of the board
#define CUSTOM_POS_X  40 // position for setting custom size of the board and showing score (x)
#define CUSTOM_POS_Y  10 // position for setting custom size of the board and showing score (y)
#define TRUE        1 // if something is true
#define FALSE       0 // if someting is false
#define BLACK_PL    0 // black's player
#define WHITE_PL    1 // white's player
#define MAX_SIZE    25 // max size of the board
#define MIN_SIZE    1 // min size of the board
#define BLACK_PIECE 'X' // black's piece
#define WHITE_PIECE 'O' // white's piece
#define NEUTRAL_PIECE '+' // neutral piece
#define KOMI 6.5 // bonus 6.5 points for white because black starts first
#define ENTER 0x0d // enter button

// main functions
void initial_configuration(int& zn, int& score_black, int& score_white, int& board_size, int& x, int& y, int& player, int& capture, int& x_ko, int& y_ko, char**& board_tab, float& bonus_points); // initial configuration of black stones
void draw_legend(int score_black, int score_white, int player); // draw a legend
void draw_board(int board_size, char** board_tab); // draw a board
void draw_pos_cursor(int x, int y); // draw position of the cursor in legend
void check_cursor(int board_size, int& x, int& y); // check if the cursor is not out of the board
void move_cursor(int& zn, int& x, int& y); // move cursor around the board
void place_stone(int& zn, int& score_black, int& score_white, int board_size, int& x, int& y, int& player, int& capture, int& x_ko, int& y_ko, char**& board_tab); // place a stone on the board
void new_game(int& zn, int& score_black, int& score_white, int& board_size, int& x, int& y, int& player, int& capture, int& x_ko, int& y_ko, char**& board_tab, float& bonus_points); // start a new game
void quit_program(int& zn, int& quit, int board_size); // quit the program
void save_game_state(int& zn, int& score_black, int& score_white, int board_size, int& player, int& x_ko, int& y_ko, char**& board_tab, float& bonus_points); // save the game state
void load_game_state(int& zn, int& score_black, int& score_white, int& board_size, int& player, int& x_ko, int& y_ko, char**& board_tab, int& x, int& y, float& bonus_points); // load the game state

// additional functions
void place_stone_handicap(int& zn, int board_size, int& x, int& y, char**& board_tab, float& bonus_points); // place a stone in initial configuration - handicap
void set_custom_size(int& board_size); // set custom size of the board
void choose_board_size(int& zn, int& board_size, char**& board_tab); // choose size of the board
void clear_board(int& score_black, int& score_white, int board_size, int& x, int& y, int& player, char**& board_tab); // clear a board (fill an array with NEUTRAL_PIECE)
void reset_board(int board_size, char**& board_tab); // // reset a board (delete an array and create a new one)
void set_border(int board_size, char**& board_tab, char color); // fill a border with given color
void print_num(int n); // print the number
void print_error_occupied(int board_size); // print error - place occupied
void print_error_suicide(int board_size); // print error - obvious suicide
void print_error_ko(int board_size); // print error - ko rule
void simple_capture(int& score_black, int board_size, int& capture, int& x_ko, int& y_ko, char**& board_tab, char color1, char color2); // simple capture
void check_suicide(int board_size, int x, int y, int& player, int& x_ko, int& y_ko, char**& board_tab, char color); // check if a move is not an obvious suicide 
void check_move(int& score_black, int board_size, int x, int y, int& player, int& capture, int& x_ko, int& y_ko, char**& board_tab, char color1, char color2); // check what move should do
void enter_file_name(int board_size, char*& file, char*& file_temp); // enter the file name
void finish_game(int &zn, int board_size, char** board_tab, int& score_black, int& score_white, int &quit, float& bonus_points); // finish the game and show results
#endif