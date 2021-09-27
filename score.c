#include "function.h"

void countWord(char board[16][16][2], t_word * word, t_player * player, int spc, int score)
{
    int len = strlen(word->word);
    int L[26][2] = {{'A',1},{'B',3},{'C',3},{'D',2},{'E',1},{'F',4},{'G',2},{'H',4},{'I',1},{'J',8},{'K',10},{'L',1},{'M',2},{'N',1},{'O',1},{'P',3},{'Q',8},{'R',8},{'S',1},{'T',1},{'U',1},{'V',4},{'W',10},{'X',10},{'Y',10},{'Z',10}};
    int lenL = 26, scrbbl = 0, tempS = 0;// Compteur de cases nouvellement posees | Score temporaire
    int countD = 0, countT = 0; // Compte le nombre de fois où l'on va multiplier le score du mot en respectivement x2 et x3
    int pj = word->pj - 'A';
    switch (word->dir)
    {
    case 'V' :
            for (int i = 0; i < len; i++) // On parcours toutes les lettres du mot
            {
                for (int j = 0 ; j < lenL; j++) // On parcours l'ensemble des lettres
                {
                    if (board[word->pi+i][pj][1] == L[j][0])// On trouve la bonne lettre
                    {
                        if (word->word[i] != ' ') // Si la lettre n'existait pas, alors on compte le mot
                        {
                            switch((int)board[word->pi+i][pj][0])
                            {
                            case 32:
                                tempS += L[j][1]; // Aucun bonus
                                break;
                            case 38: // Bonus *2 de la lettre
                                tempS += L[j][1]*2;
                                break;
                            case 37: // Bonus *3 de la lettre
                                tempS += L[j][1]*3;
                                break;
                            case 64: // Bonus *2 du mot
                                countD++;
                                break;
                            case 36:// Bonus *3 du mot
                                countT++;
                                break;
                            }
                        } else tempS += L[j][1]; // Case deja presente => pas de pts
                    }
                }
            }
            break;
        case 'H' :
            for (int i = 0; i < len; i++)
            {
                for (int j = 0 ; j < lenL; j++)
                {
                    if (board[word->pi][pj+i][1] == L[j][0])
                    {
                        if (word->word[i] != ' ')
                        {
                            switch((int)board[word->pi][pj+i][0])
                            {
                            case 38:
                                tempS+=L[j][1]*2;
                                break;
                            case 37:
                                tempS+=L[j][1]*3;
                                break;
                            case 64:
                                countD++;
                                break;
                            case 36:
                                countT++;
                                break;
                            }
                        } else tempS+= 0;
                    }
                }
            }
            break;
    }
    if (spc == 7) // Si le nombre de nouvelles lettres posees est 7 alors on fait un scrabble => On augmente le score de 50pts
        scrbbl = 50;
    score += tempS*pow(2,countD)*pow(3,countD) + scrbbl;
    player->score += score ;
    renderScore(score, player->name, spc);
}

int coundWordScore(t_word * word)
{
    int L[26][2] = {{'A',1},{'B',3},{'C',3},{'D',2},{'E',1},{'F',4},{'G',2},{'H',4},{'I',1},{'J',8},{'K',10},{'L',1},{'M',2},{'N',1},{'O',1},{'P',3},{'Q',8},{'R',8},{'S',1},{'T',1},{'U',1},{'V',4},{'W',10},{'X',10},{'Y',10},{'Z',10}};
    int score = 0;
    for (int i = 0; i < strlen(word->word); i++)
        for (int j = 0; j < 27; j++)
            if (L[j][0] == word->word[i])
                score += L[j][1];
    return score;
}


void renderScore(int score, char name[20], int spc)
{
    system("cls");
    if (score != 0)
    {
        printf("\n\n\n\n\n");
        printf("\t\t\t*************************\n");
        printf("\t\t\t*  %s a marque\t*\n", name);
        printf("\t\t\t*  %d\tpoints\t\t*\n", score);
        if (spc == 7)
            printf("\t\t\t*  \tScrabble ! + 50pts\t*\n");
        printf("\t\t\t*************************\n");
        printf("\n\n\n\n\n");
    } else
    {
        printf("\n\n\n\n\n");
        printf("\t\t\t*************************\n");
        printf("\t\t\t*  Ho non ! %s n'a*\n", name);
        printf("\t\t\t*  pas marque de point\t*\n");
        printf("\t\t\t*************************\n");
        printf("\n\n\n\n\n");
    }
    sleep(4);
}
