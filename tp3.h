//
// Created by hkone on 03/04/2024.
//

#ifndef TP3_TP3_H
#define TP3_TP3_H
    typedef struct sommet sommet;
    typedef struct voisin voisin;
    typedef sommet* graphe;
    graphe* creerGraphe();
    sommet* rechercherSommet(graphe g, int id);
    void creerSommet(graphe *g, int id);
    void ajouterArete(graphe *g, int id1, int id2);
    void ajouter_voisin(sommet* x, sommet* y);
    graphe* construireGraphe(int N);
    int rechercherDegre(graphe g);
    void supprimerSommet(graphe *g, int id);
    sommet* predSommet(graphe *g, int id);
    graphe* creerGraphe();
    void afficherGraphe(graphe g);
    int contientBoucle(graphe g);
    int recherche_boucle(graphe g,sommet* s,sommet * pred, graphe* sommetParcourue, graphe* sommmetVerifies);
    void viderBuffer();
    void fusionnerSommet(graphe *g, int idSommet1, int idSommet2);

#endif //TP3_TP3_H
