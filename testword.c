#include "function.h"

void addWord(char board[16][16][2], t_word * wordS, t_player * player)
{
    char * word = wordS->word;
    int pi = wordS->pi;
    char dir = wordS->dir;

    int cp, spc = 0, cptSpace = 0, cptW = 0;

    int len = strlen(word);
    int score = 0;
    int pj = wordS->pj - '@';
    for (int i = 0; i < len; i++)
    {
        if (word[i]>= 'a') word[i]+= 'A'-'a';
    }
    t_word ** wordList;
    if (dir == 'V')
    {
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
            wordList = foundWord(board, wordS);
            cptW = wordList[0]->pi;
            for (int i = 0; i < cptW; i++)
                score += coundWordScore(wordList[i]);
            countWord(board, wordS, player, spc, score);
        } else noWord();
    } else {
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
            wordList = foundWord(board, wordS);
            cptW = wordList[0]->pi;
            for (int i = 0; i < cptW; i++)
                score += coundWordScore(wordList[i]);
            countWord(board, wordS, player, spc, score);
        } else noWord();
    }
}

void noWord()
{
    system("cls");
    printf("\n\n\n\n\n");
    printf("\t\t\t*************************\n");
    printf("\t\t\t*  Oh non ! La place    *\n");
    printf("\t\t\t*    est incorrecte     *\n");
    printf("\t\t\t*************************\n");
    printf("\n\n\n\n\n");
    sleep(3);
}

t_word ** foundWord (char board[16][16][2], t_word * word)
{
    t_word ** wordList;
    int len = strlen(word->word);
    int pj = word->pj - '@';
    for (int i = 0; i < len; i++)
        if (word->word[i]>= 'a') word->word[i]+= 'A'-'a';
    int posi, posj;
    int xmin, xmax, ymin, ymax;
    int cptW = 0; // Word counter
    char temp[15];
    wordList = (t_word **)malloc(sizeof(t_word*));
    for (int i = 0; i < 15; i++)
        wordList[i] = (t_word *)malloc(sizeof(t_word));
    if (word->dir == 'H')
    {
        posi = word->pi;
        posj = pj;
        for(int j = pj; j < pj+len; j++) // we browse each letter
        {
            xmax = posi+1;
            xmin = posi-1;
            // <-- search for extremums -->
            while((board[xmax][j][1] != ' ') && (xmax < 16))
                xmax++;
            while((board[xmin][j][1] != ' ') && (xmin > 1))
                xmin--;
            if ((xmax - xmin) > 2)
            {
                memset(temp,0,15*sizeof(char));
                for (int i = xmin; i < xmax; i++)
                {
                    if (i == posi)
                    {
                        temp[i-xmin] = word->word[j-posj];
                    } else {
                        temp[i-xmin] = board[i][j][1];
                    }
                    strcpy(wordList[cptW]->word, temp);
                }
                cptW++;
            }
        }
        ymax = posj+len;
        ymin = posj;
        // <-- search for extremums -->
        while((board[posj][ymax][1] != ' ') && (ymax < 16))
            ymax++;
        while((board[posj][ymin][1] != ' ') && (ymin > 1))
            ymin--;
        if ((ymax - ymin) > len)
        {
            memset(temp, 0, 15*sizeof(char));
            for (int j = ymin; j <= ymax; j++)
            {
                if (j >= posj && j < posj+len)
                {
                    temp[j-ymin] = word->word[j-posj];
                } else {
                    temp[j-ymin] = board[posi][j][1];
                }
                strcpy(wordList[cptW]->word,temp);
            }
        }
    } else {
        posi = word->pi;
        posj = pj;
        for(int i = posi; i < posi+len; i++) // we browse each letter
        {
            ymax = posj+1;
            ymin = posj-1;
            // <-- search for extremums -->
            while((board[i][ymax][1] != ' ') && (ymax < 16))
                ymax++;
            while((board[i][ymin][1] != ' ') && (ymin > 1))
                ymin--;
            if ((ymax - ymin) > 1)
            {
                memset(temp, 0, 15*sizeof(char));
                for (int j = ymin; j < ymax; j++)
                {
                    if (j == posj)
                    {
                        temp[j-ymin] = word->word[i-posi];
                    } else {
                        temp[j-ymin] = board[i][j][1];
                    }
                    strcpy(wordList[cptW]->word, temp);
                }
                cptW++;
            }
        }
        xmax = posi+len;
        xmin = posi;
        // <-- search for extremums -->
        while((board[xmax][posj][1] != ' ') && (xmax < 16))
            xmax++;
        while((board[xmin][posj][1] != ' ') && (xmin > 1))
            xmin--;
        if ((xmax - xmin) > len)
        {

            memset(temp, 0, 15*sizeof(char));
            for (int i = xmin; i <= xmax; i++)
            {
                if (i >= posi && i < posi+len)
                {
                    temp[i-xmin] = word->word[i-posi];
                } else {
                    temp[i-xmin] = board[i][posj][1];
                }
                strcpy(wordList[cptW]->word, temp);
            }
        }
    }
    wordList[0]->pi = cptW;
    return wordList;
}

