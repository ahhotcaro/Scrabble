#include "function.h"


void menu(int* res, int* pS)
{
    int choix;
    do
    {
        system("cls");
        printf("    /$$$$$$                               /$$       /$$       /$$          \n   /$$__  $$                             | $$      | $$      | $$          \n");
        printf("  | $$  \\__/  /$$$$$$$  /$$$$$$  /$$$$$$ | $$$$$$$ | $$$$$$$ | $$  /$$$$$$ \n  |  $$$$$$  /$$_____/ /$$__  $$|____  $$| $$__  $$| $$__  $$| $$ /$$__  $$\n");
        printf("   \\____  $$| $$      | $$  \\__/ /$$$$$$$| $$  \\ $$| $$  \\ $$| $$| $$$$$$$$\n   /$$  \\ $$| $$      | $$      /$$__  $$| $$  | $$| $$  | $$| $$| $$_____/\n");
        printf("  |  $$$$$$/|  $$$$$$$| $$     |  $$$$$$$| $$$$$$$/| $$$$$$$/| $$|  $$$$$$$\n   \\______/  \\_______/|__/      \\_______/|_______/ |_______/ |__/ \\_______/\n\n");
        printf("\t\t\t    __      \n\t\t\t|V||_ |\\|| |\n\t\t\t| ||__| ||_|\n\n");
        printf("\t\t1: Lancer une nouvelle partie\n\t\t2: Reprendre une partie sauvegardee\n\t\t3: Afficher l'aide\n\t\t4: Afficher les scores des joueurs\n");
        printf("\t\t5: Parametres\n\n\t\t6: Quitter\n\n\t");
        scanf("%d",&choix);
        switch(choix)
        {
            case 1:
                *res = 0; // Nouvelle partie
                break;
            case 2:
                *res = 1; // Continue une partie
                break;
            case 3:
                renderHelp(); // Affiche l'aide
                break;
            case 4:
                *pS = 1; // Affiche le score dans le futur
                break;
            case 5:
                // param
                break;
            case 6:
                exit(0); // Ferme la boucle de jeu
                break;
            default: printf("Veuillez saisir une option existante\n");
        }
    } while(choix!=5 && choix !=4 && choix!=2 && choix!=1);
}

void renderHelp()
{
    char garbage;
    system("cls");
    printf(" Aide du jeu :\n");
    printf("1 - Regles :\nLes mots poses sont composes des lettres disponibles sur le cavalet. Il faut saisir les colonnes en lettres et les lignes en chiffre.\n");
    printf("\nCommandes : /EXIT : aller au menu\t/SKIP : passer son tour\n\t    /SWAP lettres : on change ces lettres\n");
    printf("\n\tPress Any char to Continue (and Enter)\n");
    scanf(" %c", &garbage);
}

void renderScorePlayers(t_player player[])
{
    system("cls");
    printf("\n Scores de la partie en cours : \n\n");
    printf("\t|-----------------------------------------------|\n");
    char garbage;
    for (int i = 0; i < player[0].num; i++)
    {
        printf("\t|Pseudo : %s \t| Ordre : %d \t| Score : %d \t|\n",player[i].name, player[i].order, player[i].score);
        printf("\t|-----------------------------------------------|\n");
    }
    printf("\n\tPress Any letter in ASCII to Continue (and Enter)\n");
    scanf(" %c", &garbage);
}











