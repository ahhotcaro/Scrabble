#include "function.h"


void createPlayer(t_player player[], int total, char pioche[103])
{
    char chevalet[7];
    for (int i = 0; i < total; i++)
    {
        printf("Veuillez saisir le nom du joueur %d\n", i+1);
        scanf("%s",player[i].name);
        player[i].order = i;
        player[i].score = 0;
        player[i].winner = 0;
        player[i].num = total;
        initEasel(pioche, chevalet);
        strcpy(player[i].chevalet, chevalet);
    }
}

int nextTurnPlayer(t_player player[])
{
    int res;
    for (int i = 0; i < player[0].num; i++)
    {
        if (player[i].order == player[0].num - 1) res = i;
        player[i].order = (player[i].order + 1 )%player[0].num;
    }
    return res;
}

int turnPlayer(t_player player[])
{
    int res;
    for (int i = 0; i < player[0].num; i++)
    {
        if (player[i].order == 0) res = i;
    }
    return res;
}

int notWin(t_player player[])
{
    int res = 1;
    for (int i = 0; i < player[0].num; i++)
    {
        if (player[i].winner ==  1) res = 0;
    }
    return res;
}

