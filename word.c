//#include "function.h"

void addWord(char board[16][16][2], char *word, int pi, char cpj, char dir, int *score)
{
    int cp, spc = 0;
    int cptSpace = 0;
    int len = strlen(word);
    int pj = cpj - '@';
    for (int i = 0; i < len; i++)
    {
        if (word[i]>= 'a') word[i]+= 'A'-'a';
    }
    char words[15][15];
    for (int i = 0; i < 15; i++)
        for (int j = 0; j < 15; j++)
            words[i][j] = '.';
    int wordsPos[15][3];
    switch (dir)
    {
    case 'V' :
            cp = 1; // correctly placed : Faux au debut, mais si l'endroit ou est place le mot contient # ou la bonne lettre a la bonne place c'est bon
            if (len + pi > 16) cp = 0; // Condition du 'hors plateau de jeu' en vertical
            else
            {
                for (int i = 0; i < len; i++)
                {
                    if ((board[pi+i][pj][1] == ' ') && (board[pi+i][pj][0] != '#')) cptSpace++; // Si mot pose sur aucun support, cptSpace = len, si cptSpace != len => ou pose sur # ou sur une lettre
                    if (((board[pi+i][pj][0] == '#') && (board[pi+i][pj][1] != ' ') && (board[pi+i][pj][1] != word[i])) || ((board[pi+i][pj][1] != word[i]) && (board[pi+i][pj][1] != ' '))) cp = 0;
                }
            }
            if ((cp == 1) && (cptSpace != len))
            {
                for (int i = 0; i < len; i++)
                {
                    if (board[pi+i][pj][1] == ' ') // Si la place est libre => on incremente le compteur de place libre + on affecte le mot
                    {
                        spc++;
                        board[pi+i][pj][1] = word[i];
                    } else word[i] = ' '; // Si la place est prise, on le la change pas, et la lettre n'apparait pas pour ne pas la compter
                }
                countWord(board,word,pi,pj,dir,score,spc);
                foundWord(board, word,pi,pj,dir,words,wordsPos);
                for (int i = 0; i < 15 ; i++)
                {
                    printf("%d\t",strlen(words[i]));
                    printf("%s\n",words[i]);
//                    char d;
//                    if (wordsPos[0])
//                    countWord(board,word,pi,pj,dir,score,0);
                }
                sleep(10);
            } else noWord();
            break;
        case 'H' :
            cp = 1; // correctly placed : Faux au debut, mais si l'endroit ou est place le mot contient # ou la bonne lettre a la bonne place c'est bon
            if (len + pj > 16) cp = 0; // condition de depassement en horizontal
            else {
                for (int i = 0; i < len; i++)
                {
                    if ((board[pi][pj+i][1] == ' ') && (board[pi][pj+i][0] != '#')) cptSpace++;
                    if (((board[pi][pj+i][0] == '#') && (board[pi][pj+i][1] != ' ') && (board[pi][pj+i][1] != word[i])) || ((board[pi][pj+i][1] != word[i]) && (board[pi][pj+i][1] != ' '))) cp = 0;
                }
            }
            if ((cp == 1) && (cptSpace != len))
            {
                for (int i = 0; i < len; i++)
                {
                    if (board[pi][pj+i][1] == ' ')
                    {
                        spc++;
                        board[pi][pj+i][1] = word[i];
                    } else word[i] = ' ';
                }
                countWord(board,word,pi,pj,dir,score,spc);
                foundWord(board, word,pi,pj,dir,words,wordsPos);
                for (int i = 0; i < 15 ; i++)
                {
                    printf("%d\t",strlen(words[i]));
                    printf("%s\n",words[i]);
//                    char d;
//                    if (wordsPos[0])
//                    countWord(board,word,pi,pj,dir,score,0);
                }
                sleep(10);
            } else noWord();
            break;
    }
}

void noWord()
{
    system("clear");
    printf("\n\n\n\n\n");
    printf("\t\t\t*************************\n");
    printf("\t\t\t*  Ho non ! La place\t*\n");
    printf("\t\t\t*  est incorrecte\t*\n");
    printf("\t\t\t*************************\n");
    printf("\n\n\n\n\n");
    sleep(3);
}

void foundWord (char board[16][16][2], char *word, int pi, char cpj, char dir, char words[15][15], int wordsPos[15][3])
{
    int len = strlen(word);
     int pj = cpj - '@';
    for (int i = 0; i < len; i++)
    {
        if (word[i]>= 'a') word[i]+= 'A'-'a';
    }
    int posi,posj;
    int xmin = 16, xmax = 1, ymin = 16, ymax = 1;
    int x, y;
    int cptW = 0;
    for (int i = 0; i < len; i++) // On parcours toutes les positions
    {
        xmin = pi; xmax = pi;
        if (dir == 'H')
        {
            posi = pi;
            posj = pj+i;
            x = pi-1;
            while(x > 0) // recherche de l'indice de la colonne minimal du mot
            {
                if (board[x][posj][1] == ' ') break;
                if (x < xmin) xmin = x;
                x--;
            }
            x = pi+1;
            while(x < 16)
            {
                if (board[x][posj][1] == ' ') break;
                if (x > xmax) xmax = x;
                x++;
            }
            if (((xmax - xmin) > 1) && board[posi][posj][1] == ' ')
            {
                cptW++;
                for (int j = xmin; j <= xmax ; j++)
                {
                    words[i][j-xmin] = board[j][posj][1];
                    if (j == pi) words[i][j-xmin] = word[i];
                }
                wordsPos[i][0] = xmin;
                wordsPos[i][1] = posj;
                wordsPos[i][2] = 1; // On met que 1 c'est direction verticale
            }
        }
        else
        {
            ymin = pj; ymax = pj;
            posi = pi+i;
            posj = pj;
            y = pj-1;
            while(y > 0) // recherche de l'indice de la colonne minimal du mot
            {
                if (board[posi][y][1] == ' ') break;
                if (y < ymin) ymin = y;
                y--;
            }
            y = pj+1;
            while(y < 16)
            {
                if (board[posi][y][1] == ' ') break;
                if (y > ymax) ymax = y;
                y++;
            }
            if (((ymax - ymin) > 1) && board[posi][posj][1] == ' ')
            {
                cptW++;
                for (int j = ymin; j <= ymax ; j++)
                {
                    words[i][j-ymin] = board[posi][j][1];
                    if (j == pj) words[i][j-ymin] = word[i];
                }
                wordsPos[14][0] = posi;
                wordsPos[14][1] = ymin;
                wordsPos[i][2] = 0; // 0 = horizontal
            }
        }
    }
    if (dir == 'H')
    {
        ymin = pj; ymax = pj;
        y = pj-1;
        while (y > 0) // recherche de l'indice de la colonne minimal du mot
        {
            if (board[pi][y][1] == ' ') break;
            if (y < ymin) ymin = y;
            y--;
        }
        y = pj+1;
        while (y < 16)
        {
            if (board[pi][y][1] == ' ') break;
            if (y > ymax) ymax = y;
            y++;
        }
        if ((ymax - ymin) > len)
        {
            cptW++;
            for (int j = ymin; j <= ymax ; j++)
            {
                words[14][j-ymin] = board[pi][j][1];
                if (j == pj) words[14][j-ymin] = word[0];
            }
            wordsPos[14][0] = ymin;
            wordsPos[14][1] = pj;
            wordsPos[14][2] = 0; // horizontal
        }
    }
    else
    {
        xmin = pi; xmax = pi;
        x = pi-1;
        while(x > 0) // recherche de l'indice de la colonne minimal du mot
        {
            if (board[x][pj][1] == ' ') break;
            if (x < xmin) xmin = x;
            x--;
        }
        x = pi+1;
        while(x < 16)
        {
            if (board[x][pj][1] == ' ') break;
            if (x > xmax) xmax = x;
            x++;
        }
        if ((xmax - xmin) > len)
        {
            cptW++;
            for (int j = xmin; j <= xmax ; j++)
            {
                words[14][j-xmin] = board[j][pj][1];
                if (j == pi) words[14][j-xmin] = word[0];
            }
            wordsPos[14][0] = pi;
            wordsPos[14][1] = xmin;
            wordsPos[14][2] = 1; // vertical
        }
    }
    removeDots(words);
}

void removeDots(char word[15][15])
{
    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            if (word[i][j] == '.')
            {
                word[i][j] = '\0';
                continue;
            }
        }
    }
}

