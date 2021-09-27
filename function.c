#include "function.h"


void createBoard(char board[16][16][2])
{
    // Init spaces
    for (int i = 0; i < 16; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            board[i][j][0] = ' ';
            board[i][j][1] = ' ';
        }
    }
    // Init coordonnees
    for (int i = 1; i < 16; i++)
    {
        board[0][i][1] = 64+i;
        if ((i < 10)) board[i][0][1] = 48+i%10;
        else
        {
            board[i][0][1] = 48+i%10;
            board[i][0][0] = '1';
        }
    }
    // Pose des caracteres speciaux
    // 1 - @        s'il y en a dans les coins ou au mileu ce n'est pas grave, puisqu'il est fait en premier, alors le caractere se fera ecraser par les autres d'apres
    for (int i = 1; i < 16; i++)
    {
        for (int j = 1 ; j < 16; j++)
        {
            if (((i-2)%4 == 0)&&((j-2)%4 == 0)) board[i][j][0] = '%'; // 2 - %
            if (((i == j) || (16-i == j)) && ((i<6) || (i > 10))) board[i][j][0] = '@';
            if (((i-4 == j)&&((i == 7)||(i==8)||(i==12)||(i==13))) || ((i+4 == j)&&((i == 3)||(i==4)||(i==8)||(i==9)))) board[i][j][0] = '&'; // diag de &
            if (((i == j)||(16-i == j))&&((i >6)&&( i < 10))) board[i][j][0] = '&'; // carre central de &
            if ((i%4 == 0)&&((j == 1)||(j == 8)||(j == 15))) board[i][j][0] = '&'; // bordures verticales de &
        }
    }
    // 4 - $    en avant dernier pour "ecraser" les caracteres
    int LPDol[8][2] = {{1,1}, {1,8}, {1,15}, {8,1}, {8,15}, {15,1}, {15,8}, {15,15}};   // On initialise la liste des positions des dollars (LPDol = Liste Positions Dollar
    int di,dj;                                                                          // di = position en i du dollar idem en j
    // & manquants, meme methode que $
    int LPEsp[8][2] = {{1,4},{1,12},{15,4},{15,12},{3,9},{7,13},{9,3},{13,7}};
    int ei, ej;
    for (int i = 0; i < 8; i++)                                                         // On parcour la liste en y mettant les dollars aux bons endroits
    {
        di = LPDol[i][0]; dj = LPDol[i][1];
        board[di][dj][0] = '$';
        ei = LPEsp[i][0]; ej = LPEsp[i][1];
        board[ei][ej][0] = '&';
    }
    // 5 - #        on le fait en dernier car il superposera les autres caracteres s'il y en a deja un sur la case
    board[8][8][0] = '#';
}

void renderBoard(char board [16][16][2], t_player player, char pioche[])
{
    system("cls");
    for (int i = 0; i < 16; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            printf(" ");
            for (int k = 0; k < 2; k++)
            {
                if ((k == 0) && (board[i][j][k] != ' ')) printf("\033[3m%c\033[0m", board[i][j][k]);
                else if ((board[i][j][k]>='A')&&(board[i][j][k]<='Z')) printf("%c", board[i][j][k]);
                else printf("%c",board[i][j][k]);
            }
            if ((i == 0)&&(j == 15)) printf("\t\033[1m\033[7m Scrabble V1.5 \033[0m"); // affichage a droite du jeu d'une partie de l'interface
            if ((i == 1)&&(j == 15)) printf("\t%s", player.name);
            if ((i == 2)&&(j == 15)) printf("\tScore : %d",player.score);
            if ((i == 4)&&(j == 15)) printf("\tLegende :");
            if ((i == 5)&&(j == 15)) printf("\t# : point de depart");
            if ((i == 6)&&(j == 15)) printf("\t& : lettre double");
            if ((i == 7)&&(j == 15)) printf("\t%% : lettre triple");
            if ((i == 8)&&(j == 15)) printf("\t@ : mot double");
            if ((i == 9)&&(j == 15)) printf("\t$ : mot triple");
            if ((i == 11)&&(j == 15)) printf("\tLettres restantes : %ld",strlen(pioche));
        }
        printf("\n");
    }
}





