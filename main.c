#include <stdio.h>
#include <stdlib.h>
#include "tp3.h"
#include "tp3.c"

int main() {

    char choix[10];
    int nb_sommets, id, id1, id2, degre_max, id_sup, id_fus1, id_fus2;
    graphe* g = NULL;
    while (1){  //on fait boucler infiniment pour afficehr le menu plusieurs fois
        printf("Entrez votre choix :\n\t"
               "1 : Creer un graphe vide\n\t"
               "2 : Construire un graphe de N sommets\n\t"
               "3 : Ajouter un sommet\n\t"
               "4 : Ajouter une arete\n\t"
               "5 : Afficher un graphe\n\t"
               "6 : Donner le degré maximal du graphe\n\t"
               "7 : Supprimer un sommet\n\t"
               "8 : Vérifier si le graphe contient une boucle\n\t"
               "9 : fusionner deux sommets\n\t"
               "10 : Quitter\n");
        fgets(choix, sizeof(choix), stdin);
        int choix_entier = atoi(choix);  //convertion de choix en entier
        switch(choix_entier){
            case 1:
                printf("création d'un graphe vide\n");
                if (g != NULL) free(g);
                g = creerGraphe();
                break;
            case 2:
                printf("Nombre de sommets : \n");
                scanf("%d", &nb_sommets);
                viderBuffer();
                g = construireGraphe(nb_sommets);
                break;
            case 3:
                printf("Entrez l'indice du sommet : \n");
                scanf("%d", &id);
                creerSommet(g, id);
                break;
            case 4:
                printf("Entrer les indices des 2 sommets : \n");
                scanf("%d %d", &id1, &id2);
                ajouterArete(g, id1, id2);
                break;
            case 5:
                afficherGraphe(*g);
                break;
            case 6:
                degre_max = rechercherDegre(*g);
                printf("degré du graphe : %d", degre_max);
                break;
            case 7:
                printf("Entrez l'indice du sommet à supprimer : ");
                scanf("%d", &id_sup);
                supprimerSommet(g, id_sup);
                break;
            case 8:
                if (contientBoucle(*g) == 1){
                    printf("le graphe contient une boucle\n");
                }
                else printf("le graphe ne contient pas de boucle\n");
                break;
            case 9:
                printf("Entrez les 2 sommets à fusionner : \n");
                scanf("%d %d", &id_fus1, &id_fus2);
                fusionnerSommet(g, id_fus1, id_fus2);
                break;
            case 10:
                printf("Fin du programme");
                free(g);
                exit(0);
            default:
                printf("La valeur n'est pas accepté, Réeassayez\n");
        }
        printf("Appuyez sur n'importe quelle touche\n");
        viderBuffer();
    }
    return 0;
}