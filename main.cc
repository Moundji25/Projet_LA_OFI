#include "ArbreB.hh"
#include "huffman.hh"
#include <string.h>
#include <iostream>

using namespace std;

int main()
{
    huffman H;
    H.lecture_traitements();

    
    // STOCKER LES ARBRES (les caractéres ) ET LES INITIALISER >>>> 

    H.initialiser_vecteurs_arbres();


    //  FUSIONNER LES ARBRES POUR FINALEMENT AVOIR UN SEUL ARBRE COMME RÉSULTAT >>>>>>>>>

    H.fusionner_arbres();
    
    H.vider();
    

    H.arbres.at(0)->affiche();  //                  AFFICHAGE DE L'ARBRE

    //           CODAGE DU TEXTE    >>>>>>>>>>>>>>>>>
    H.genere_code();

    //        CODAGE DU TEXTE   <<<<<<<<<<<<<<<<<<<<<<







   // cout << "           arbre a :" << endl << endl;
    /*

          11
         / \
        1   2  
       /
      5
    */

   /* ArbreB *a = new ArbreB();
    
    Sommet *s = new Sommet(11);
    Sommet *s1 = new Sommet(1);
    Sommet *s2 = new Sommet(2);
    Sommet *s3 = new Sommet(5);
    Sommet *s4 = new Sommet(6);

    a->inserer(&a,s);
    a->inserer(&a,s1);
    a->inserer(&a,s2);
    
    affiche(a);

    cout << "           insrer deux sommet dans a :"  << endl << endl;
    a->inserer(&a,s3);
    a->inserer(&a,s4);
    affiche(a);

    cout << "           supprimer le sommet dont l'etiqutte = 1 dans l'arbre a:" << endl << endl;
    a->supprimer(1);
    affiche(a);



    cout << "           arbre b :" << endl << endl;*/
    /*

           7
         /  \
        3    4

    */

    /*ArbreB *b = new ArbreB();

    Sommet *su = new Sommet(7);   
    Sommet *su1 = new Sommet(3);
    Sommet *su2 = new Sommet(4);

    b->inserer(&b,su);
    b->inserer(&b,su1);
    b->inserer(&b,su2);
    
    affiche(b);
    
    
    // FUSION DE a ET b
    cout << "           arbre c fusion de l'arbre a et l'arbre b :" << endl << endl;

    ArbreB *c = a->fusion(a,b);

    affiche(c);


    // DECOMPOSITION DE c
    cout << "            decomposition de l'arbre c à partir de la racine (la racine est supprimé) --> ( arbre d sous graphe Gauche ) , ( arbre e sous graphe Droit )" << endl << endl;

    ArbreB *d = new ArbreB();
    ArbreB *e = new ArbreB();
    
    c->decomposition(&d,&e);

    cout << "            arbre d :" << endl << endl;
    affiche(d);
    
    cout << "            arbre e :" << endl << endl;
    affiche(e);

    cout << "            rechercher dans l'arbre c le sommet dont l'etiquette = 3" << endl;
    

    if (c->rechercher(3) != NULL)
    {
        cout << "             -------> votre arbre contient l'element "<< endl  ;
    }
    else
    {
        cout << "             -------> votre arbre ne contient pas l'element 3" << endl;
    }
    */
}



