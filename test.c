/* Exemple d'utilisation de malloc expliquée */


// 1 ~ On veut un tableau dynamique de caractères

char temp[100];
scanf("%s",temp);

char * tab;
tab = (char *)malloc(strlen(temp)*sizeof(char));

// Ici, tab est un pointeur sur une allocation de la RAM (d'où le char *), qui va pointer sur un espace mémoire d'une taille de 
// la longueur du string donné par l'utilisateur (disons 42) donc 42 * la taille en octet d'un char : 1 octet
// => Allocation de 1 * 42 octets

// 2 ~ Tableau à deux dimensions :

char ** tab; // Pointeur de pointeur, on peut return tab car c'est un pointeur et pas un type complexe
tab = (char **)malloc(15 * sizeof(char *)); // On fait un tableau où chaque ligne est un pointeur

for (int i = 0; i < 15; i ++)
    tab[i] = (char *)malloc(15 * sizeof(char)); // Chaque ligne en suite est un pointeur où on attribue une place d'un char

// Ainsi, on vient de faire un tableau de 15 * 15 de char
// 15 * 15 * 1  = 225 octets