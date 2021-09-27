#include "function.h"

void saveGame(char board[16][16][2], t_player player[], char pioche[])
{
    FILE * f = NULL;
    char temp[4] = {'0','0','0','0'};
    f = fopen ("assets/save.txt", "w");
    // sauvegarde joueur
    fprintf(f, "player[");
    for (int i = 0; i < player[0].num; i++)
    {
        fprintf (f, "{\"%s\"",player[i].name);
        fprintf (f, "o%d",player[i].order);
        decToHex(player[i].score, temp);
        fprintf (f, "s%s",temp);
        fprintf (f, "w%d",player[i].winner);
        fprintf (f, "t%d",player[i].num);
        fprintf (f, "c\"%s\"}",player[i].chevalet);
        for (int j=0;j<4;j++) temp[j] = '0';
    }
    fprintf(f, "]\nb{");
    // sauvegarde tableau
    for (int i = 0; i < 16 ; i++)
    {
        for( int j = 0; j < 16; j++)
        {
            fprintf(f, "%c", board[i][j][0]);
            fprintf(f, "%c", board[i][j][1]);
        }
    }
    fprintf(f, "}");
    fprintf(f, "p{%s}", pioche);
    fclose(f);
}

void resumeGame(char board[16][16][2], t_player * player, char pioche[])
{
    memset(pioche, 0, 103*sizeof(char));
    FILE * f = NULL;
    f = fopen ("assets/save.txt", "r");
    char val;
    // grab players data
    int i = 0, n = 0;
    char name[20], hex[4], c;
    while (!feof(f))
    {
        fscanf(f, "%c", &val);
        if (val == '}')i++;
        if ((val == '{') && (fgetc(f) == '"'))
        {
            memset(player[i].name, 0, sizeof(player[i].name)); // On vide player[i].name
            do
            {
                c = fgetc(f);
                if (c!= '"')
                    player[i].name[n++] = c;
            } while (c != '"');
            memset(name, 0, sizeof(name)); // On vide name
            n = 0;
        }
        if ((val == 's'))
        {
            for (int k = 0 ; k < 4 ; k ++) hex[k] = fgetc(f);
            player[i].score = hexToDec(hex);
        }
        if (val == 'o') player[i].order = (int)(fgetc(f) - 48);
        if (val == 'w') player[i].winner = (int)(fgetc(f) - 48);
        if (val == 't') player[i].num = (int)(fgetc(f) - 48);
        if ((val == 'c') && (fgetc(f) == '"'))
        {
            memset(player[i].chevalet, 0, sizeof(player[i].chevalet)); // On vide player[i].chevalet
            do
            {
                c = fgetc(f);
                if (c!= '"')
                    player[i].chevalet[n++] = c;
            } while (c != '"');
            n = 0;
        }
    }
    // Grab board data
    rewind(f); // on remonte au debut du fichier
    i = 0;
    while (!feof(f))
    {
        c = fgetc(f);
        if ((c == 'b') && (fgetc(f) == '{')) // début de la variable
        {
            for (int x = 0; x < 16; x++)
            {
                for (int y = 0; y < 16; y++)
                {
                    board[x][y][0] = fgetc(f);
                    board[x][y][1] = fgetc(f);
                }
            }
        }
        if ((c == 'p') && (fgetc(f) == '{'))
        {
            do
            {
            c = fgetc(f);
            if (c != '}')
                pioche[i++] = c;
            } while (c != '}');
        }
        pioche[i] = '\0';
    }
    fclose(f);
}


int grabTotalPlayer(FILE * F1)
{
    rewind(F1);
    char val = ' ';
    int ans;
    //<-- Grab the 'totalPlayer' int -->

    while (!feof(F1))
    {
        fscanf(F1,"%c", &val);
        if (val == 't')
        {
            ans = fgetc(F1) - '0';
            break;
        }
    }
    return ans;
}
