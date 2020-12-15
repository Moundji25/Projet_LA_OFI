#ifndef HUFFMAN_HH
#define HUFFMAN_HH

#include "ArbreB.hh"
#include <iostream>
#include <vector>

class huffman
{
public:
    std::string texte;  // le texte entrer en entrée standard 
    double alphabet[94]; // tableau représentant le nbre d'occurence des caractéres/pourcentage d'occurence des caractéres qui varient entre code ascii (32 'espace'  ... 126 '~') 
    std::vector<ArbreB *> arbres; // vecteur necessiare à la fusion car il contenir les arbres à fusionner  
    std::vector<ArbreB *> dechets;  // vecteur necessaire à la fusion car il va contenir les arbres à supprimer 
    int nbreCar; // entier necessaire à la fusion

    huffman(); // constructeur de la classe 
    std::vector<ArbreB *> getArbres(); // retourne le vecteur arbres 
    void lecture_traitements(); // recupere le texte à traiter, initialise le vecteur arbres en stockant le code ascii de chaque caractére du texte
                                // convertir le nombre d'ocurrence de chaque caractére en un pourcentage d'occurence par rapport à la taille du texte
    
    void initialiser_vecteurs_arbres(); // initialiser le vecteur arbres, assigner à chaque arbre un caractére et son pourcentage d'occurence et afficher l'alphabet 
    void fusionner_arbres(); // Fusionner les arbres du vecteur arbres jusqu'a avoir un seul arbre dans le vecteur qui sera le résultat de la fusion de tout les arbres et aura
                            // un pourcentage = 100 
    bool code_lettre( char car, Sommet* s , std::vector <int> * ); // 
    void vider();
    void genere_code();
};

#endif