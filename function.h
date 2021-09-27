// Includes section
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <dirent.h>

// Struct definitions
typedef struct playerStruct {
    char name[20];  // Pseudo du joueur
    int order;      // Place in the "queue" of the game loop
    int score;
    int winner;     // Boolean: 0 -> not winner | 1 -> winner
    int num;        // Total number of players
    char chevalet[7];
} t_player;

typedef struct wordStruct {
    char word[15];
    int pi;         // i position  ('x')
    char pj;        // j position ('y')
    char dir;       // may be ('H' or 'V')
} t_word;

// Function initialisation
void sleep();

// Board functions
void createBoard(char board[16][16][2]);    /* Create an 16*16*2 board (char)
                                             * with coordinates (A to O horizontally & 1 to 15 vertically);
                                             * correctly placed bonus boxes
                                             * ('@', '&', '$', '#', '%')
                                             */
void renderBoard(char board[16][16][2], t_player player, char pioche[]);   /* accept char table of [16][16][2] & struct player
                                                             * It prints out the game board
                                                             * & a side pannel of additionnal informations
                                                             * it uses player.score & player.name
                                                             * (of the given player)
                                                             */

// Word functions
void countWord(char board[16][16][2], t_word * word, t_player * player, int spc, int score); // Count scores of a word correctly placed
void addWord(char board[16][16][2], t_word * wordS, t_player * player); // Add a correctly placed word to coordinates (pi,pj) vertically or horizontally
t_word ** foundWord (char board[16][16][2], t_word * word); // Give the list of new word find
void noWord(); // Affiche un message si le joueur n'a pas saisi de coordonnées correctes

// Easel functions
void shuffleLetters(char * pioche);  // function that shuffle the letter drawer
void initEasel(char pioche[103],char chevalet[7]);    // Function that initialize a easel (of 7 letters)
void renderEasel(char chevalet[7]); // render the easel with scores for each letter
void changeEasel(char * params, char * chevalet, char * pioche); // Change the letters given in the command relative to the easel

// Score functions
void renderScore(int score, char name[20], int spc); // Render a scoreboard
int coundWordScore(t_word * word); // Calculate the score of a word without adding the multiplier coefficients

// Player functions
void createPlayer(t_player player[], int total, char pioche[103]); // Create an given number of different players
int nextTurnPlayer(t_player player[]); //  Give the index of the next turn player
int turnPlayer(t_player player[]); // Give the index of the current player
int notWin(t_player player[]); // 0 = no winner ; 1 = there is a winner
void renderScorePlayers(t_player player[]); // Render every player score

// Game functions
int grabTotalPlayer(FILE * F1); // Grab the number of total players
void saveGame(char board[16][16][2], t_player player[], char pioche[]); // Save game
void resumeGame(char board[16][16][2], t_player player[], char pioche[]); // Continue game
void renderHelp(); // Affiche l'aide
void menu(int* res, int* pS);   /* Render main menu
                                 * return choice with int pointer
                                 * res = continue (1) or create (0) a game
                                 * pS = render (1) or not (0) scores saved
                                 */

// Maths functions
int pow (int num, int p);   /* alt of pow  function from <math.h> (ne fonctionne pas)
                             * usage :
                             *  pow(a, b) <=> a^b
                             */
void decToHex(int number, char hex[4]);     /* Convert int into hex
                                             * accept integer + char table[4]
                                             * /!\ max len of hex string : 4
                                             */
int hexToDec(char hex[4]); /* Convert hex into int
                            * accept integer + char table[4]
                            * /!\ max len of hex string : 4
                            */

