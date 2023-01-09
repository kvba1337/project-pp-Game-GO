#include"functions.h"
#include"conio2.h"
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

using namespace std;

// setting custom size of the board
void set_custom_size(int& board_size) {
    int ok = FALSE;
    do {
        char* custom_size;
        char* temp_size;
        temp_size = (char*)malloc(sizeof(char) * 100);
        if (!temp_size) return;
        textcolor(BLUE);
        gotoxy(CUSTOM_POS_X, CUSTOM_POS_Y + 12);
        cputs("Please set the board size: ");
        gotoxy(CUSTOM_POS_X, CUSTOM_POS_Y + 13);
        int word_length = 0;
        for (;;) { // getting custom size of the board from user input to temponary array
            temp_size[word_length] = getche();
            if (temp_size[word_length] == ENTER) break;
            else word_length++;
        }
        custom_size = (char*)malloc(sizeof(char) * word_length);
        for (int i = 0; i < word_length; i++) { // copying size of the board to original array
            custom_size[i] = temp_size[i];
        }
        if (atoi(custom_size) > MAX_SIZE || atoi(custom_size) < MIN_SIZE) {
            textcolor(RED);
            gotoxy(CUSTOM_POS_X, CUSTOM_POS_Y + 15);
            cputs("This size is not available");
            getch();
            delline();
            gotoxy(CUSTOM_POS_X, CUSTOM_POS_Y + 13);
            delline();
        }
        else {
            ok = TRUE;
            board_size = atoi(custom_size);
        }
        free (custom_size);
        free(temp_size);
    } while (ok != TRUE);
}

// choose size of the board
void choose_board_size(int& zn, int& board_size, char**& board_tab) {
    textcolor(LIGHTGRAY);
    gotoxy(CUSTOM_POS_X, CUSTOM_POS_Y + 5);
    cputs("Choose size of the board: ");
    gotoxy(CUSTOM_POS_X, CUSTOM_POS_Y + 7);
    cputs("1. 9x9");
    gotoxy(CUSTOM_POS_X, CUSTOM_POS_Y + 8);
    cputs("2. 13x13");
    gotoxy(CUSTOM_POS_X, CUSTOM_POS_Y + 9);
    cputs("3. 19x19");
    gotoxy(CUSTOM_POS_X, CUSTOM_POS_Y + 10);
    cputs("4. CUSTOM SIZE (MAX 25x25)");
    zn = getch();
    switch (zn) {
    case '1':
        board_size = 9;
        break;
    case '2':
        board_size = 13;
        break;
    case '3':
        board_size = 19;
        break;
    case '4':
        set_custom_size(board_size);
        break;
    default:
        choose_board_size(zn, board_size, board_tab);
        break;
    }
    board_tab = new char* [board_size + MARGIN]; // creating a two-element array of the size chosen by the player
    for (int i = 0; i < board_size + MARGIN; i++)
        board_tab[i] = new char[board_size + MARGIN];
}

// clear a board (fill an array with NEUTRAL_PIECE)
void clear_board(int& score_black, int& score_white, int board_size, int& x, int& y, int& player, char**& board_tab) {
    for (int i = 1; i <= board_size; i++)
        for (int j = 1; j <= board_size; j++)
            board_tab[i][j] = NEUTRAL_PIECE;

    x = BOARD_X + 1; // setting position of the cursor to (1, 1) array
    y = BOARD_Y + 1;
    score_black = 0;
    score_white = 0;
    player = BLACK_PL;
}

// reset a board (delete an array and create a new one)
void reset_board(int board_size, char**& board_tab) {
    delete[] board_tab;
    board_tab = new char* [board_size + MARGIN];
    for (int i = 0; i < board_size + MARGIN; i++)
        board_tab[i] = new char[board_size + MARGIN];
}

// fill a border with given color piece
void set_border(int board_size, char**& board_tab, char color) {
    for (int j = 0; j <= board_size + 1; j++)
        board_tab[0][j] = color;
    for (int j = 0; j <= board_size + 1; j++)
        board_tab[board_size + 1][j] = color;
    for (int j = 1; j <= board_size; j++)
        board_tab[j][0] = color;
    for (int j = 1; j <= board_size; j++)
        board_tab[j][board_size + 1] = color;
}

// print the number
void print_num(int n) {
    if (n > 9) {
        int a = n / 10;
        n -= 10 * a;
        print_num(a);
    }
    putchar('0' + n);
}

// draw a legend
void draw_legend(int score_black, int score_white, int player) {
    gotoxy(LEGEND_X, LEGEND_Y);
    cputs("Jakub Falk, 193252");
    gotoxy(LEGEND_X, LEGEND_Y + 2);
    cputs("Implemented functionalities:");
    gotoxy(LEGEND_X, LEGEND_Y + 3);
    cputs("a, b, c, d, e, f, g, h, k");
    gotoxy(LEGEND_X, LEGEND_Y + 5);
    cputs("Controls:");
    gotoxy(LEGEND_X, LEGEND_Y + 6);
    cputs("q       = quit the program");
    gotoxy(LEGEND_X, LEGEND_Y + 7);
    cputs("arrows = moving");
    gotoxy(LEGEND_X, LEGEND_Y + 8);
    cputs("n       = start a new game");
    gotoxy(LEGEND_X, LEGEND_Y + 9);
    cputs("enter   = confirm");
    gotoxy(LEGEND_X, LEGEND_Y + 10);
    cputs("esc     = cancel");
    gotoxy(LEGEND_X, LEGEND_Y + 11);
    cputs("i       = place a stone");
    gotoxy(LEGEND_X, LEGEND_Y + 12);
    cputs("s       = save the game state");
    gotoxy(LEGEND_X, LEGEND_Y + 13);
    cputs("l       = load the game state");
    gotoxy(LEGEND_X, LEGEND_Y + 14);
    cputs("f       = finish the game");
    gotoxy(LEGEND_X, LEGEND_Y + 17);
    cputs("Black's (X) score: ");
    print_num(score_black);
    gotoxy(LEGEND_X, LEGEND_Y + 18);
    cputs("White's (O) score: ");
    print_num(score_white);
    gotoxy(LEGEND_X, LEGEND_Y + 21);
    if (player == BLACK_PL) cputs("BLACK TO MOVE (X)");
    else cputs("WHITE TO MOVE (O)");
}

// draw a board
void draw_board(int board_size, char** board_tab) {
    for (int i = 0; i < board_size + MARGIN; i++) {
        for (int j = 0; j < board_size + MARGIN; j++) {
            gotoxy(BOARD_X + j, BOARD_Y + i);
            if (i == 0 || i == board_size + 1) { // drawing horizontal border of the board
                gotoxy(BOARD_X + j, BOARD_Y + i);
                cputs("-");
            }
            else if (j == 0 || j == board_size + 1) cputs("|"); // drawing vertical border of the board
            else putch(board_tab[i][j]); // drawing pieces and empty places
        }
    }
}

// check if the cursor is not out of the board
void check_cursor(int board_size, int& x, int& y) {
    if (x <= BOARD_X) x++;
    if (x > BOARD_X + board_size) x--;
    if (y <= BOARD_Y) y++;
    if (y > BOARD_Y + board_size) y--;
}

// print position of the cursor in legend
void draw_pos_cursor(int x, int y) {
    textcolor(LIGHTGRAY);
    gotoxy(LEGEND_X, LEGEND_Y + 15);
    cputs("Position of the cursor: ");
    print_num(x);
    cputs(", ");
    print_num(y);
}

// print error - place occupied
void print_error_occupied(int board_size) {
    textcolor(RED);
    gotoxy(BOARD_X, BOARD_Y + board_size + 6);
    delline();
    cputs("You can't put a stone - PLACE OCCUPIED");
    gotoxy(BOARD_X, BOARD_Y + board_size + 7);
    cputs("Click ANY button to continue");
    getch();
}

// print error - obvious suicide
void print_error_suicide(int board_size) {
    textcolor(RED);
    gotoxy(BOARD_X, BOARD_Y + board_size + 6);
    cputs("You can't put a stone - OBVIOUS SUICIDE");
    gotoxy(BOARD_X, BOARD_Y + board_size + 7);
    cputs("Click ANY button to continue");
    getch();
}

// print error - ko rule
void print_error_ko(int board_size) {
    textcolor(RED);
    gotoxy(BOARD_X, BOARD_Y + board_size + 6);
    delline();
    cputs("You can't put a stone  - KO RULE");
    gotoxy(BOARD_X, BOARD_Y + board_size + 7);
    cputs("Click ANY button to continue");
    getch();
}

// simple capture by black player
void simple_capture(int& score, int board_size, int& capture, int& x_ko, int& y_ko, char**& board_tab, char color1, char color2) {
    for (int i = 1; i <= board_size; i++) {
        for (int j = 1; j <= board_size; j++) {
            if (board_tab[i][j] == color2) {
                set_border(board_size, board_tab, color1);
                if (board_tab[i][j - 1] == color1 && board_tab[i + 1][j] == color1 && board_tab[i][j + 1] == color1 && board_tab[i - 1][j] == color1) {
                    score++;
                    board_tab[i][j] = NEUTRAL_PIECE;
                    capture = TRUE; // remember that capture has been made
                    x_ko = BOARD_X + j; // remember position of ko (x)
                    y_ko = BOARD_Y + i; // remember position of ko (y)
                }
            }
        }
    }
}

// check if a move is not an obvious suicide - black
void check_suicide(int board_size, int x, int y, int& player, int& x_ko, int& y_ko, char**& board_tab, char color) {
    set_border(board_size, board_tab, color);
    if (board_tab[y - BOARD_Y - 1][x - BOARD_X] == color && board_tab[y - BOARD_Y + 1][x - BOARD_X] == color && board_tab[y - BOARD_Y][x - BOARD_X - 1] == color && board_tab[y - BOARD_Y][x - BOARD_X + 1] == color) { // the placed piece is surrounded by opponent's stones
        board_tab[y - BOARD_Y][x - BOARD_X] = NEUTRAL_PIECE;
        print_error_suicide(board_size);
    }
    else {
        x_ko = 0; // reset position of ko (x)
        y_ko = 0; // reset position of ko (y)
        if (color == WHITE_PIECE) player++;
        else player--;
    }
}

// check what black's move should do
void check_move(int& score, int board_size, int x, int y, int& player, int& capture, int& x_ko, int& y_ko, char**& board_tab, char color1, char color2) {
    capture = FALSE; // remove the memory that a capture was made
    board_tab[y - BOARD_Y][x - BOARD_X] = color1;
    set_border(board_size, board_tab, color1);
    simple_capture(score, board_size, capture, x_ko, y_ko, board_tab, color1, color2);
    if (capture == FALSE) check_suicide(board_size, x, y, player, x_ko, y_ko, board_tab, color2);
    else {
        if (color1 == BLACK_PIECE) player++;
        else player--;
    }
}


// place a stone
void place_stone(int& zn, int& score_black, int& score_white, int board_size, int& x, int& y, int& player, int& capture, int& x_ko, int& y_ko, char**& board_tab) {
    textcolor(BLUE);
    gotoxy(BOARD_X, BOARD_Y + board_size + 6);
    cputs("Click ENTER to put a stone");
    gotoxy(BOARD_X, BOARD_Y + board_size + 7);
    cputs("Click ESC to cancel");
    zn = getch();
    if (zn == ENTER) {
        gotoxy(x, y);
        if (player == BLACK_PL) { // black's move
            if (board_tab[y - BOARD_Y][x - BOARD_X] != NEUTRAL_PIECE) print_error_occupied(board_size);
            else if (x_ko == x && y_ko == y) print_error_ko(board_size);
            else check_move(score_black, board_size, x, y, player, capture, x_ko, y_ko, board_tab, BLACK_PIECE, WHITE_PIECE);
        }
        else if (player == WHITE_PL) { // white's move
            if (board_tab[y - BOARD_Y][x - BOARD_X] != NEUTRAL_PIECE) print_error_occupied(board_size);
            else if (x_ko == x && y_ko == y) print_error_ko(board_size);
            else check_move(score_white, board_size, x, y, player, capture, x_ko, y_ko, board_tab, WHITE_PIECE, BLACK_PIECE);
        }
        if (x == BOARD_X + board_size) x--; // cursor is on the right edge of the board
        else x++;
    }
}

// moving the cursor
void move_cursor(int& zn, int& x, int& y) {
    gotoxy(x, y);
    textcolor(LIGHTGRAY);
    textbackground(BLACK);
    putch('*');
    // we wait for key press and get its code
        // most key codes correspond to the characters, like
        // a is 'a', 2 is '2', + is '+', but some special keys
        // like cursors provide two characters, where the first
        // one is zero, e.g., "up arrow" is zero and 'H'
    zn = getch();

    // we do not want the key 'H' to play role of "up arrow"
    // so we check if the first code is zero
    if (zn == 0) {
        zn = getch();		// the next code knowing that this
        if (zn == 0x48) y--;	// will be a special key
        else if (zn == 0x50) y++;
        else if (zn == 0x4b) x--;
        else if (zn == 0x4d) x++;
    }
}

// place a stone - handicap
void place_stone_handicap(int& zn, int board_size, int& x, int& y, char**& board_tab, float& bonus_points) {
    textcolor(BLUE);
    gotoxy(BOARD_X, BOARD_Y + board_size + 9);
    cputs("Click ENTER to put a stone");
    gotoxy(BOARD_X, BOARD_Y + board_size + 10);
    cputs("Click ESC to cancel");
    zn = getch();
    if (zn == ENTER) {
        if (board_tab[y - BOARD_Y][x - BOARD_X] != NEUTRAL_PIECE) {
            delline();
            gotoxy(BOARD_X, BOARD_Y + board_size + 7);
            delline();
            gotoxy(BOARD_X, BOARD_Y + board_size + 8);
            delline();
            print_error_occupied(board_size);
            zn = 0;
        }
        else {
            gotoxy(x, y);
            board_tab[y - BOARD_Y][x - BOARD_X] = BLACK_PIECE;
            zn = 0;
            bonus_points += 0.5;
            if (x == BOARD_X + board_size) x--;
            else x++;
        }
    }
}

// game state editor - initial configuration od black stones
void initial_configuration(int& zn, int& score_black, int& score_white, int& board_size, int& x, int& y, int& player, int& capture, int& x_ko, int& y_ko, char**& board_tab, float& bonus_points) {
    textcolor(LIGHTGRAY);
    clrscr();
    choose_board_size(zn, board_size, board_tab);
    clear_board(score_black, score_white, board_size, x, y, player, board_tab);
    do {
        textbackground(BLACK);
        clrscr();
        textcolor(LIGHTGRAY);
        draw_legend(score_black, score_white, player);
        draw_board(board_size, board_tab);
        textcolor(YELLOW);
        gotoxy(BOARD_X, BOARD_Y + board_size + 6);
        cputs("Put initial configuration");
        gotoxy(BOARD_X, BOARD_Y + board_size + 7);
        cputs("Click ENTER to continue");
        check_cursor(board_size, x, y);
        draw_pos_cursor(x, y);
        move_cursor(zn, x, y);
        if (zn == 'i') place_stone_handicap(zn, board_size, x, y, board_tab, bonus_points);
    } while (zn != ENTER);
}

// new game
void new_game(int& zn, int& score_black, int& score_white, int& board_size, int& x, int& y, int& player, int& capture, int& x_ko, int& y_ko, char**& board_tab, float& bonus_points) {
    textcolor(BLUE);
    gotoxy(BOARD_X, BOARD_Y + board_size + 6);
    cputs("Click ENTER to start new game");
    gotoxy(BOARD_X, BOARD_Y + board_size + 7);
    cputs("Click ESC to cancel");
    zn = getch();
    if (zn == ENTER) {
        x_ko = 0;
        y_ko = 0;
        capture = FALSE;
        for (int i = 0; i < board_size + MARGIN; i++)
            delete[] board_tab[i];
        delete[] board_tab;
        initial_configuration(zn, score_black, score_white, board_size, x, y, player, capture, x_ko, y_ko, board_tab, bonus_points);
    }
}

// quit the program
void quit_program(int& zn, int& quit, int board_size) {
    textcolor(BLUE);
    gotoxy(BOARD_X, BOARD_Y + board_size + 6);
    cputs("Click ENTER to quit the program");
    gotoxy(BOARD_X, BOARD_Y + board_size + 7);
    cputs("Click ESC to cancel");
    zn = getch();
    if (zn == ENTER) quit = TRUE;
}

// enter the file name
void enter_file_name(int board_size, char*& file, char*& file_temp) {
    file_temp = (char*)malloc(sizeof(char) * 100);
    if (!file_temp) return;
    int length = 0;
    int ch = 0;
    textcolor(BLUE);
    gotoxy(BOARD_X, BOARD_Y + board_size + 7);
    delline();
    gotoxy(BOARD_X, BOARD_Y + board_size + 6);
    cputs("Please enter the name of file: ");
    gotoxy(BOARD_X, BOARD_Y + board_size + 7);
    while (ch != ENTER) { // getting file name from user input to temponary array
        ch = getche();
        file_temp[length] = ch;
        length++;
    }
    if (length==1) { // user didn't input any name of file
        textcolor(RED);
        gotoxy(BOARD_X, BOARD_Y + board_size + 8);
        cputs("You didn't put a name of file");
        getch();
        delline();
        enter_file_name(board_size, file, file_temp);
    }
    file_temp[length - 1] = '\0'; // delete enter at the end from array
    file = (char*)malloc(sizeof(char) * length);
    strcpy(file, file_temp);
}

// save the game state
void save_game_state(int& zn, int& score_black, int& score_white, int board_size, int& player, int& x_ko, int& y_ko, char**& board_tab, float& bonus_points) {
    char* file;
    char* file_temp;
    enter_file_name(board_size, file, file_temp);
    gotoxy(BOARD_X, BOARD_Y + board_size + 6);
    cputs("Cick ENTER to confirm saving the game state");
    gotoxy(BOARD_X, BOARD_Y + board_size + 7);
    cputs("Click ESC to cancel");
    zn = getch();
    if (zn == ENTER) {
        FILE* pFile;
        pFile = fopen(file, "w");
        if (pFile != NULL) {
            fputc(board_size, pFile);
            for (int i = 1; i <= board_size; i++) { // saving position of the stones
                for (int j = 1; j <= board_size; j++) {
                    fputc(board_tab[i][j], pFile);
                }
                fputs("\n", pFile);
            }
            fputc(player, pFile);
            fputc(score_black, pFile);
            fputc(score_white, pFile);
            fputc(bonus_points, pFile);
            fputc(x_ko, pFile);
            fputc(y_ko, pFile);
            fputs("\n", pFile);
            fclose(pFile);
        }
    }
    free (file);
    free (file_temp);
}

// load the game state
void load_game_state(int& zn, int& score_black, int& score_white, int& board_size, int& player, int& x_ko, int& y_ko, char**& board_tab, int& x, int& y, float& bonus_points) {
    char* file;
    char* file_temp;
    enter_file_name(board_size, file, file_temp);
    gotoxy(BOARD_X, BOARD_Y + board_size + 6);
    cputs("Cick ENTER to confirm loading the game state");
    gotoxy(BOARD_X, BOARD_Y + board_size + 7);
    cputs("Click ESC to cancel");
    zn = getch();
    if (zn == ENTER) {
        FILE* pFile;
        pFile = fopen(file, "r");
        if (pFile != NULL) {
            board_size = fgetc(pFile);
            clrscr();
            reset_board(board_size, board_tab);
            for (int i = 1; i <= board_size; i++) {
                for (int j = 1; j <= board_size; j++) { // reading position of the stones
                    char c = fgetc(pFile);
                    if (c == BLACK_PIECE) board_tab[i][j] = BLACK_PIECE;
                    else if (c == WHITE_PIECE) board_tab[i][j] = WHITE_PIECE;
                    else board_tab[i][j] = NEUTRAL_PIECE;
                }
                fgetc(pFile);
            }
            player = fgetc(pFile);
            score_black = fgetc(pFile);
            score_white = fgetc(pFile);
            bonus_points = fgetc(pFile);
            x_ko = fgetc(pFile);
            y_ko = fgetc(pFile);
            fgetc(pFile);
            fclose(pFile);
        }
        else {
            textcolor(RED);
            gotoxy(BOARD_X, BOARD_Y + board_size + 8);
            delline();
            cputs("This file doesn't exist");
            getch();
        }
    }
    free(file);
    free(file_temp);
}

void finish_game(int& zn, int board_size, char ** board_tab, int& score_black, int& score_white, int& quit, float& bonus_points) {
    textcolor(BLUE);
    gotoxy(BOARD_X, BOARD_Y + board_size + 6);
    cputs("Click ENTER to finish the game");
    gotoxy(BOARD_X, BOARD_Y + board_size + 7);
    cputs("Click ESC to cancel");
    zn = getch();
    if (zn == ENTER) {
        int winner = 0;
        for (int i = 1; i <= board_size; i++) { // counting both player's stones on the board
            for (int j = 1; j <= board_size; j++) {
                if (board_tab[i][j] == BLACK_PIECE) score_black++;
                else if (board_tab[i][j] == WHITE_PIECE) score_white++;
            }
        }
        float score_white_bonus = score_white + KOMI + bonus_points;
        char buffer[5];
        sprintf_s(buffer, 5, "%.1f", score_white_bonus);

        if (score_black > score_white_bonus) winner = BLACK_PL;
        else if (score_black < score_white_bonus) winner = WHITE_PL;
        else winner = 2;

        clrscr();
        gotoxy(CUSTOM_POS_X, CUSTOM_POS_Y + 5);
        textcolor(RED);

        if (winner == BLACK_PL) cputs("BLACK WINS THE GAME");
        else if (winner == WHITE_PL) cputs("WHITE WINS THE GAME");
        else cputs("DRAW");

        gotoxy(CUSTOM_POS_X, CUSTOM_POS_Y + 7);
        textcolor(LIGHTGRAY);
        cputs("Score black: ");
        print_num(score_black);
        gotoxy(CUSTOM_POS_X, CUSTOM_POS_Y + 8);
        cputs("Score white: ");
        fputs(buffer, stdout);
        gotoxy(CUSTOM_POS_X, CUSTOM_POS_Y + 10);
        textcolor(BLUE);
        cputs("Press ANY button to quit the program");
        getch();
        quit = TRUE;
    }
}