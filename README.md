Projet de Manipulation de Graphes en C
Ce projet implémente un graphe non orienté en utilisant une liste chaînée de sommets, chacun ayant une liste chaînée de voisins. Il inclut plusieurs fonctionnalités permettant la création, la manipulation et la suppression de sommets et d’arêtes pour explorer les propriétés du graphe, comme la détection de boucles et la fusion de sommets.

Structure des données
sommet : représente un sommet du graphe, incluant son identifiant, un pointeur vers le sommet suivant et une liste chaînée de voisins.
voisin : représente un voisin d’un sommet, c'est-à-dire une arête vers un autre sommet.

Fonctionnalités
Le projet propose les fonctions suivantes :
creerGraphe : initialise un graphe vide.
creerSommet : ajoute un nouveau sommet avec un identifiant donné dans le graphe en maintenant l’ordre.
rechercherSommet : recherche un sommet dans le graphe par son identifiant.
ajouterArete : ajoute une arête entre deux sommets, avec une vérification pour éviter les doublons.
ajouter_voisin : ajoute un voisin pour un sommet donné, en conservant l'ordre.
construireGraphe : construit un graphe en demandant à l’utilisateur d’entrer les indices des sommets et les arêtes.
afficherGraphe : affiche le graphe avec chaque sommet et ses voisins.
rechercherDegre : retourne le degré maximal parmi les sommets du graphe.
supprimerSommet : supprime un sommet et toutes les arêtes le reliant à d'autres sommets.
predSommet : retourne le prédécesseur d’un sommet donné dans le graphe.
contientBoucle et recherche_boucle : détectent les cycles dans le graphe en parcourant les arêtes.
fusionnerSommet : fusionne deux sommets en un seul, en combinant leurs voisins.
viderBuffer : vide le buffer d'entrée pour éviter les erreurs de saisie.
