/*
 *  /$$$$$$                               /$$       /$$       /$$                /$$    /$$   /$$       /$$$$$$$
 * /$$__  $$                             | $$      | $$      | $$               | $$   | $$ /$$$$      | $$____/
 *| $$  \__/  /$$$$$$$  /$$$$$$  /$$$$$$ | $$$$$$$ | $$$$$$$ | $$  /$$$$$$      | $$   | $$|_  $$      | $$
 *|  $$$$$$  /$$_____/ /$$__  $$|____  $$| $$__  $$| $$__  $$| $$ /$$__  $$     |  $$ / $$/  | $$      | $$$$$$$
 * \____  $$| $$      | $$  \__/ /$$$$$$$| $$  \ $$| $$  \ $$| $$| $$$$$$$$      \  $$ $$/   | $$      |_____  $$
 * /$$  \ $$| $$      | $$      /$$__  $$| $$  | $$| $$  | $$| $$| $$_____/       \  $$$/    | $$       /$$  \ $$
 *|  $$$$$$/|  $$$$$$$| $$     |  $$$$$$$| $$$$$$$/| $$$$$$$/| $$|  $$$$$$$        \  $/    /$$$$$$ /$$|  $$$$$$/
 * \______/  \_______/|__/      \_______/|_______/ |_______/ |__/ \_______/         \_/    |______/|__/ \______/
 */


/**   Scrabble V1.5 16/10/2020                  **/
/** @AudreyCampdoras @CarolineAhHot @BenoitFage **/

#include "function.h"


int main()
{
    srand(time(NULL)); // Random activated
    char board[16][16][2], pioche[103];
    t_word * word;
    word = (t_word *)malloc(sizeof(t_word));
    int totalPlayer = 3, currentPlayer = 0, resume = 0, playerScoreMenu = 0;
    menu(&resume, &playerScoreMenu);
    while (playerScoreMenu)
    {
        system("cls");
        FILE *F1 = fopen("assets/save.txt", "r");
        if (F1 == NULL)
        {
            printf("\n\n\n\n\n");
            printf("\t\t\t*****************************************\n");
            printf("\t\t\t*                                       *\n");
            printf("\t\t\t*  Il n'y a pas de partie sauvegardee.  *\n");
            printf("\t\t\t*                                       *\n");
            printf("\t\t\t*****************************************\n");
            printf("\n\n\n\n\n");
            sleep(3);
            playerScoreMenu = 0;
            menu(&resume, &playerScoreMenu);
        } else
        {
            totalPlayer = grabTotalPlayer(F1);
            t_player player[totalPlayer];
            resumeGame(board, player, pioche);
            renderScorePlayers(player);
            fclose(F1);
            playerScoreMenu = 0;
            menu(&resume, &playerScoreMenu);
        }
    }
    if (resume)
    {
        system("cls");
        FILE *F1 = fopen("assets/save.txt", "r");
        if (F1 == NULL)
        {
            printf("\n\n\n\n\n");
            printf("\t\t\t*****************************************\n");
            printf("\t\t\t*  Il n'y a pas de partie a continuer.  *\n");
            printf("\t\t\t*          Commencez en une !           *\n");
            printf("\t\t\t*****************************************\n");
            printf("\n\n\n\n\n");
            sleep(3);
            resume = 0;
        } else
        {
            totalPlayer = grabTotalPlayer(F1);
            fclose(F1);
        }
    }
    if (!resume)
    {
        system("cls");
        printf("\nCombien de joueurs vont jouer ?\nJoueurs maximum : 4\n");
        do
        {
            scanf("%d", &totalPlayer);
        } while ((totalPlayer <= 1) || (totalPlayer > 4));
    }
    t_player player[totalPlayer];
    if (resume)
        resumeGame(board, player, pioche);
    else
    {
        // New game case
        strcpy(pioche, "AAAAAAAAABBCCDDDEEEEEEEEEEEEEEEFFGGHHIIIIIIIIJKLLLLLMMMNNNNNNOOOOOOPPQRRRRRRSSSSSSTTTTTTUUUUUUVVWXYZ??"); //Init pioche
        shuffleLetters(pioche);

        createPlayer(player, totalPlayer, pioche);
        createBoard(board);
    }
    currentPlayer = turnPlayer(player);
    renderBoard(board,player[currentPlayer], pioche);

    // Game loop
    do
    {
        // Demande d'un mot
        printf("\nCommandes : /EXIT : aller au menu\t/SKIP : passer son tour\n\t    /SWAP lettres : on change ces lettres\n");
        printf("Chevalet : ");
        renderEasel(player[currentPlayer].chevalet);
        printf("\nMot :\t");
        scanf(" %[^\n]s", word->word);
        if (strcmp(word->word, "/EXIT") == 0)
            main();
        if (strncmp(word->word,"/SWAP ",5) == 0)
            changeEasel(word->word, player[currentPlayer].chevalet, pioche);

        if (strcmp(word->word, "/SKIP") == 0 || strncmp(word->word,"/SWAP ",5) == 0)
        {
            currentPlayer = nextTurnPlayer(player);
            saveGame(board, player, pioche);
            renderBoard(board, player[currentPlayer], pioche);
            continue;
        }
        printf("Ligne ? (entier) \t");
        do
        {
            scanf("%d", &word->pi);
        } while ((word->pi < 0) || (word->pi > 16));

        // Demande de la position en j
        printf("Colonne ? (lettre)\t");
        do
        {
            scanf(" %c", &word->pj);
            if (word->pj> 'a')
                word->pj +='A'-'a'; // pj devient majuscule si ce n'est pas le cas
        } while ((word->pj < '@')||(word->pj >'P'));

        // Demande de la direction
        printf("Sens ? (V | H)\t");
        do
        {
            scanf(" %c", &word->dir);
        } while ((word->dir != 'V') && (word->dir != 'H'));

        // Ajout du mot avec les parametres obtenus precedemment
        addWord(board, word, &player[currentPlayer]);
        currentPlayer = nextTurnPlayer(player);
        saveGame(board, player, pioche);
        renderBoard(board, player[currentPlayer], pioche);
    } while (notWin(player));
    return 0;
}
