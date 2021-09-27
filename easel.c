#include "function.h"

void shuffleLetters(char * pioche)  //fonction qui melange la pioche
{
    int n, i, p1, p2;
    char swap;
    n = strlen(pioche);
    for (i=0; i<2*n; i++)
    {
        do
        {
            p1=rand()%n;
            p2=rand()%n;
        } while (p1 == p2);            // les 2 positions de doivent pas etre les meme pour melanger
        swap = pioche[p1];            // On echange les deux positions
        pioche[p1] = pioche[p2];
        pioche[p2] = swap;
    }
}

void initEasel(char pioche[103],char chevalet[7])    // fonction qui pioche les 7 lettres pour former le chevalet
{
    int p1;
    for(int i=0; i<7; i++)
    {
        p1 = rand()%strlen(pioche);
        chevalet[i] = pioche[p1];
        pioche[p1] = 0;                                              //ici on supprime les lettres de la pioche
        strcpy(pioche+p1, pioche+p1+1);
    }
}

void renderEasel(char * chevalet)
{
    int L[27][3] = {{'?','0',' '},{'A','1',' '},{'B','3',' '},{'C','3',' '},{'D','2',' '},{'E','1',' '},{'F','4',' '},{'G','2',' '},{'H','4',' '},{'I','1',' '},{'J','8',' '},{'K','1','0'},{'L','1',' '},{'M','2',' '},{'N','1',' '},{'O','1',' '},{'P','3',' '},{'Q','8',' '},{'R','1',' '},{'S','1',' '},{'T','1',' '},{'U','1',' '},{'V','4',' '},{'W','1','0'},{'X','1','0'},{'Y','1','0'},{'Z','1','0'}};
    for (int i=0;i<7;i++) // On parcours toutes les lettres du chevalet
        for (int j = 0 ; j < 27; j++) // On parcours l'ensemble de l'alphabet
            if (chevalet[i] == L[j][0])  // On verifie si on a la bonne lettre
            {
                printf(" | ");
                for (int x = 0; x < 3; x++) // On copie les deux valeurs
                    printf("%c",L[j][x]);
            }
}


void changeEasel(char * parameters, char * chevalet, char * pioche)
{
    // <-- We collect the letters to change -->
    char lettres[7];
    int len = strlen(parameters);
    printf("[%s]",parameters);
    if (len <= 6)
    {
        system("cls");
        printf("\n\n\n\n\n");
        printf("\t\t\t**********************************\n");
        printf("\t\t\t*     Ho non ! Vous n'avez       *\n");
        printf("\t\t\t*    pas donnes de parametres    *\n");
        printf("\t\t\t**********************************\n");
        printf("\n\n\n\n\n");
        sleep(3);
    } else {
        for (int i = 6; i < len; i++)
            if (parameters[i] != ' ')
                lettres[i - 6] = parameters[i];

        // <-- We check if the letters to be changed are in the easel -->
        len = strlen(lettres); // number of letters to change
        char chevaletCopy[7];
        printf("\"%s\"\n",chevaletCopy);
        strcpy(chevaletCopy,chevalet);
        printf("\"%s\"\n",chevaletCopy);
        for (int i = 0; i < len; i++)
            for (int j = 0; j < 7; j++)
                if (chevaletCopy[j] == lettres[i])
                    chevaletCopy[j] = ' ';
        printf("\"%s\"\n",lettres);
        int cptS = 0;
        for (int i = 0; i < len; i ++)
            if (chevaletCopy[i] == ' ')
                cptS++;
        printf("%d", len);
        sleep(30);
        // <-- We chose the new letters in the easel -->
        if (cptS == len)
        {
            int lenP = strlen(pioche);
            if (lenP > len)
            {
                int ran;
                char temp;
                for (int i = 0; i < 7 ; i++)
                {
                    if (chevaletCopy[i] == ' ')
                    {
                        ran = rand()%len;
                        temp = pioche[ran];
                        pioche[ran] = chevalet[i];
                        chevalet[i] = temp;
                    }
                }
            } else {
                system("cls");
                printf("\n\n\n\n\n");
                printf("\t\t\t**********************************\n");
                printf("\t\t\t*     Ho non ! Vous demandez     *\n");
                printf("\t\t\t*    a changer trop de lettres   *\n");
                printf("\t\t\t**********************************\n");
                printf("\n\n\n\n\n");
                sleep(3);
            }
        } else {
            system("cls");
            printf("\n\n\n\n\n");
            printf("\t\t\t**********************************\n");
            printf("\t\t\t*     Ho non ! Vous demandez     *\n");
            printf("\t\t\t*     a changer des lettres      *\n");
            printf("\t\t\t*      que vous n'avez pas       *\n");
            printf("\t\t\t**********************************\n");
            printf("\n\n\n\n\n");
            sleep(3);
        }
    }

}


/** usage example
    int main()
    {
        srand(time(NULL));
        char pioche[]="AAAAAAAAABBCCDDDEEEEEEEEEEEEEEEFFGGHHIIIIIIIIJKLLLLLMMMNNNNNNOOOOOOPPQRRRRRRSSSSSSTTTTTTUUUUUUVVWXYZ??"; //Init pioche
        char chaval[8][3];
        shuffleLetters(pioche);
        char chevalet[8];
        initEasel(pioche, chevalet, chaval);
        return 0;
    }
**/
