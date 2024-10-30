//
// Created by hkone on 03/04/2024.
//

#include "tp3.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct sommet
{
    int ind;
    struct sommet* suiv;
    struct voisin* v;
};

struct voisin
{
    int indSommet;
    struct voisin* eltSuiv;
};


graphe* creerGraphe(){
    graphe* g = malloc(sizeof(graphe));
    if (g!=NULL) {
        *g = NULL;
        return g;
    }else
        exit (0);
}
void creerSommet(graphe *g, int indice) {
    if (g == NULL) {
        printf("Le graphe n'est pas initialisé !\n");
        return;
    }

    sommet* nouveauSommet = malloc(sizeof(sommet));
    if (nouveauSommet == NULL) {
        printf("L'allocation de mémoire a échouée !\n");
        return;
    }
    nouveauSommet->ind = indice;
    nouveauSommet->suiv = NULL;
    nouveauSommet->v = NULL;

    if (*g == NULL || (*g)->ind > indice) {
        nouveauSommet->suiv = *g;
        *g = nouveauSommet;
    } else {
        sommet* courant = *g;
        while (courant->suiv != NULL && courant->suiv->ind < indice) {
            courant = courant->suiv;
        }
        nouveauSommet->suiv = courant->suiv;
        courant->suiv = nouveauSommet;
    }
}
sommet* rechercherSommet(graphe g, int id)
{
    sommet* x = g;
    while(x!= NULL && x->ind != id)
        x = x->suiv;
    return x;
}

void ajouterArete(graphe *g, int id1, int id2)
{
    sommet* x = rechercherSommet(*g,id1);
    sommet* y = rechercherSommet(*g,id2);
    if (x==NULL || y == NULL)
    {
        printf("%d et/ou %d n'existe pas\n");
        return;
    }
    //on verifie si il ne s'agit pas d'une arete existante
    voisin* z = x->v;
    while (z!=NULL && z->indSommet != id2)
        z= z->eltSuiv;
    if(z==NULL) {
        ajouter_voisin(x, y);
        ajouter_voisin(y, x);
    }
}


void ajouter_voisin(sommet* x, sommet* y)
{
    if(x->ind != y->ind){
    voisin* new_vois = malloc(sizeof(voisin));
    if (new_vois != NULL)
    {
        if (x->v == NULL || x->v->indSommet >= y->ind){
            new_vois->eltSuiv = x->v;
            new_vois->indSommet = y->ind;
            x->v = new_vois;
        }
        else{
            voisin* e = x->v;
            voisin* p = x->v->eltSuiv;
            while (p  != NULL && p ->indSommet < y->ind){
                e = e ->eltSuiv;
                p = p -> eltSuiv;
            }
            e->eltSuiv = new_vois;
            new_vois->eltSuiv = p;
            new_vois->indSommet = y->ind;
        }
    }
    }
}
graphe* construireGraphe(int N) {
    if (N==0)
    {
        printf("Taille invalide\n");
        return 0;
    }
    graphe *g = creerGraphe();
    int* tab_ind = malloc(sizeof(int)*N);
    char ligne[100]; // Taille arbitraire pour la ligne
    if (tab_ind != NULL){
        for (int i=0; i<N; i++){
            printf("Insérer un indice : ");
            fgets(ligne, sizeof(ligne), stdin);
            sscanf(ligne, "%d", &tab_ind[i]);
            printf("\n");
        }
        printf("\n");
        for (int i = 0; i<N; i++){
            creerSommet(g, tab_ind[i]);
        }
        for (int i = 0; i<N-1; i++){
            for (int j= i+1; j <N; j++){
                printf("Le sommet d'indice %d et %d forment-ils une arête (y) : ", tab_ind[i], tab_ind[j]);
                fgets(ligne, sizeof(ligne), stdin);
                if (ligne[0] == 'y'){
                    ajouterArete(g, tab_ind[i], tab_ind[j]);
                }
                printf("\n");
            }
        }
        free(tab_ind);
    }
    printf("graphe g créé\n");
    return g;
}
void afficherGraphe(graphe g)
{
    sommet * x = g;
    while (x!= NULL) {
        printf("Sommet %d ->", x->ind);
        voisin *v = x->v;
        while (v != NULL) {
            printf(" %d ", v->indSommet);
            v = v->eltSuiv;
        }
        x=x->suiv;
        printf("\n");
    }

}

int rechercherDegre(graphe g)
{
    int deg = 0;
    sommet* s = g;
    voisin* vois;
    int count;
    while( s != NULL) {
        vois = s->v;
        count = 0;
        while (vois!=NULL)
        {
            count++;
            vois = vois->eltSuiv;
        }
        if (deg < count)
            deg = count;
        s = s->suiv;
    }
    return deg;
}

void supprimerSommet(graphe *g, int id)//il reste à supprimer le sommete des voisinages
{
    sommet* x = rechercherSommet(*g,id);
    if (x!= NULL)
    {
        sommet * y = predSommet(g,id);
       if (y == NULL)
            *g = (*g)->suiv;
       else
            y->suiv = x->suiv;

       voisin* vois = x->v;
       sommet* z;
       voisin* vois2;

       while (vois != NULL)
       {
           z = rechercherSommet(*g, vois->indSommet);
           vois2 = z->v;

           if (vois2->indSommet ==  x->ind) {
               z->v = z->v->eltSuiv;
               free(vois2);
           }
           else {
               while (vois2 != NULL && vois2->eltSuiv->indSommet != x->ind)
                   vois2 = vois2->eltSuiv;
               if (vois2 != NULL) {
                   voisin* tmp = vois2->eltSuiv;
                   vois2->eltSuiv = vois2->eltSuiv->eltSuiv;
                   free(tmp);
               }
           }
           vois = vois->eltSuiv;
       }
    }

    free(x);
}

sommet* predSommet(graphe *g, int id)
{
    sommet* s = *g;
    if (s->ind == id)
        return NULL;
    else {
        while (s->suiv != NULL && s->suiv->ind != id)
            s = s->suiv;
        return s;
    }
}

int contientBoucle(graphe g)
{

    sommet* s = g;
    graphe* sommetsVerifies; // ont initialise une liste des sommets deja verifies pour eviter des recherche redondantes
    sommetsVerifies = creerGraphe();
    int res;
    while(s!=NULL)
    {
        if(s->v != NULL && rechercherSommet(*sommetsVerifies,s->ind) == NULL) { //on verifie  si le sommet est relié à des aretes et s'il n'a pas deja été vérifié
            graphe* sommetsParcourus;
            sommetsParcourus = creerGraphe();
            creerSommet(sommetsParcourus,s->ind);
            sommet *new_som = rechercherSommet(g, s->v->indSommet);
            res = recherche_boucle(g, new_som, s, sommetsParcourus, sommetsVerifies);
            if (res == 1) {
                free(sommetsVerifies);
                free(sommetsParcourus);
                return 1;
            }
            free(sommetsParcourus);
        }
        creerSommet(sommetsVerifies,s->ind);
        s = s->suiv;
    }
    free(sommetsVerifies);
    return 0;
}

int recherche_boucle(graphe g,sommet* s,sommet * pred, graphe* sommetParcourue, graphe* sommmetVerifies)
{
    creerSommet(sommetParcourue,s->ind);
    voisin *v ;
    v = s->v;
    int res;
    while (v != NULL) {
        if (v->indSommet != pred-> ind) {
            if (rechercherSommet(*sommetParcourue, v->indSommet) != NULL) // si le voisin appartient à la liste de sommet parcourie ont detecte une boucle
                return 1;
            creerSommet(sommetParcourue, v->indSommet);
            creerSommet(sommmetVerifies, v->indSommet);
            res = recherche_boucle(g, rechercherSommet(g, v->indSommet), s, sommetParcourue, sommmetVerifies);
            if (res == 1)
                return res;

            supprimerSommet(sommetParcourue, v->indSommet);
        }
        v = v->eltSuiv;
    }
    return 0;
}

void fusionnerSommet(graphe *g, int idSommet1, int idSommet2)
{
    sommet *x;
    sommet *y;
    if( idSommet2 > idSommet1) {
        x = rechercherSommet(*g, idSommet1);
        y = rechercherSommet(*g, idSommet2);
    }else {
        x = rechercherSommet(*g, idSommet2);
        y = rechercherSommet(*g, idSommet1);
    }
    voisin *v =  y->v;
    while ( v != NULL) {
        ajouterArete(g, x->ind, v->indSommet);
        v = v->eltSuiv;
    }
    supprimerSommet(g,y->ind);
}
void viderBuffer()
{
    int c = 0;
    while (c != '\n' && c != EOF)
    {
        c = getchar();
    }
}