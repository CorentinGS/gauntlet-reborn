#include "menu.h"

int menuprincipal(int *level)
{
    int choix, tmp, lev;
    printf(" __________________________________________________________\n");
    printf("|                                                         |\n");
    printf("|                                                         |\n");
    printf("|     1. jouer                                            |\n");
    printf("|     2. choisir niveau                                   |\n");
    printf("|     3. Afficher les 10 meilleurs scores                 |\n");
    printf("|     4. quitter                                          |\n");
    printf("|                                                         |\n");
    printf("|_________________________________________________________|\n");

    scanf("%d", &choix);

    switch (choix)
    {
    case 1:
        tmp = 1;
        break;
    case 2:
        tmp = sousmenu(&lev);
        *level = lev;
        break;
    case 3:
        Scoreboard tab[10];
        readScoreboard("data/scoreboard.dat", tab);

        printf("-----    voici les 10 meilleurs scores !    -----\n");
        printf("  pseudo                score            niveau  \n");
        printf("-------------------------------------------------\n");
        for (int cpt = 0; cpt < 9; cpt++)
        {
            printf(" %s %d %d\n", tab[cpt].playerName, tab[cpt].score, tab[cpt].level);
        }
        break;
    case 4:
        exit(0);
        break;
    default:
        printf("saisie invalide\n");
        break;
    }

    return tmp;
}

int sousmenu(int *level)
{
    int choix, tmp;

    printf(" __________________________________________________________\n");
    printf("|                                                         |\n");
    printf("|                                                         |\n");
    printf("|   1. niveau 1                                           |\n");
    printf("|   2. niveau 2                                           |\n");
    printf("|   3. niveau 3                                           |\n");
    printf("|   4. retour                                             |\n");
    printf("|                                                         |\n");
    printf("|_________________________________________________________|\n");

    scanf("%d", &choix);

    switch (choix)
    {
    case 1:
        *level = 1;
        tmp = 1;
        break;
    case 2:
        *level = 2;
        tmp = 1;
        break;
    case 3:
        *level = 3;
        tmp = 1;
        break;
    case 4:
        break;
    default:
        printf("saisie invalide\n");
        break;
    }
    return tmp;
}