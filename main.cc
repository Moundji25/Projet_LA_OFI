#include "Sommet.hh"
#include "ArbreB.hh"
#include <string.h>
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

double arrondir(double val, double prec)
{
    return round(val/prec)*prec;
}

int main()
{
    // JE NE GERE PAS : 'é' 'à' 'ç'  ----> JE PARLE PAS FRANÇAIS MAIS JE PARLE TRÉS BIEN L'ANGLAIS 
    string texte ("");

    do // LECTURE DU TEXTE                                                  A REVOIR !!!!!
    {
       cout<<"Veuillez entrez le texte SVP \n";
       //cin >> texte; 
       getline(cin,texte);   

    } while (texte.size() <= 0);

    for (size_t i = 0; i < texte.size(); i++)
    {
        cout<<texte.at(i)<<endl;
    }

    double alphabet [94];

    for (size_t i = 0; i < 94; i++) // INTIALISER LE TABLEAU ALPHABET 
    {
        alphabet[i] = 0;
    }

    for (size_t i = 0; i < texte.size(); i++) // stocker le code ascii
    {
        //if (texte.at(i) != ' ')
        //{
            alphabet[texte.at(i) - 32]++;
        //}
        //else
        /*{
            cout<<" SPACE ";
            alphabet[93]++;
        }*/
        
    }
    
    cout<<endl;
    
    int nbreCar = 0;

    cout<<" alphabet : "<<endl;
    for (size_t i = 0; i < 94; i++) // convertir le nombre d'ocurrence de chaque caractére en un pourcentage d'occurence par rapport à le nombre de caractéres dans le texte 
    {
        if (alphabet[i] != 0)
        {
            alphabet[i] =arrondir((alphabet[i] * 100) / texte.size() , 0.1);
            cout<<" "<<alphabet[i]<<" ";
            nbreCar++;
        }
    }
    cout<<endl;

    std::vector<ArbreB *> arbres;
    
    // STOCKER LES ARBRES (les caractéres ) ET LES INITIALISER >>>> 

    for (size_t i = 0; i < nbreCar; i++) 
    {
        arbres.push_back(new ArbreB);
    }
    int i=0,j=0;

    while (j < 94 && i < arbres.size())
    {     
        if (alphabet[j] != 0)
        {
            arbres.at(i)->inserer(&arbres.at(i),new Sommet(alphabet[j],j+32));
            i++;
        }
        j++;

    }
    
    //   <<<<<<<<<
    
    
    cout<<" les étiquettes 2 : \n";

    for ( ArbreB * elem : arbres)
    {
        cout<<" "<<elem->getRacine()->getEtiquette2()<<" ";
    }
    cout<<endl;


    //  FUSIONNER LES ARBRES POUR FINALEMENT AVOIR UN SEUL ARBRE COMME RÉSULTAT >>>>>>>>>

    int min1,min2,co1,co2;

    /*if (arbres.at(1)->getRacine()->getEtiquette() < arbres.at(0)->getRacine()->getEtiquette())
    {
        min1 = arbres.at(1)->getRacine()->getEtiquette(); co1 = 1;
        min2 = arbres.at(0)->getRacine()->getEtiquette(); co2 = 0;
    }
    else
    {
        min1 = arbres.at(0)->getRacine()->getEtiquette(); co1 = 0;
        min2 = arbres.at(1)->getRacine()->getEtiquette(); co2 = 1;
    }*/
    
    ArbreB * tmpArbre;
    while (arbres.size()>1) 
    {

        if (arbres.at(1)->getRacine()->getEtiquette() < arbres.at(0)->getRacine()->getEtiquette())
        {
            min1 = arbres.at(1)->getRacine()->getEtiquette(); co1 = 1;
            min2 = arbres.at(0)->getRacine()->getEtiquette(); co2 = 0;
        }
        else
        {
            min1 = arbres.at(0)->getRacine()->getEtiquette(); co1 = 0;
            min2 = arbres.at(1)->getRacine()->getEtiquette(); co2 = 1;
        }


        for (size_t i = 0; i < arbres.size(); i++) // trouver les deux min et sauvgarder leurs positions 
        {
            if (arbres.at(i)->getRacine()->getEtiquette() < min1)
            {
                co1 = i;
                min1 = arbres.at(i)->getRacine()->getEtiquette();
            }
            if (arbres.at(i)->getRacine()->getEtiquette() < min2 && i != co1)
            {
                min2 = arbres.at(i)->getRacine()->getEtiquette();
                co2 = i;
            }
            
            
        }

        tmpArbre = arbres.at(co1)->fusion(arbres.at(co1) , arbres.at(co2));
        
        cout<<"          min1 "<<co1<<" min2 "<<co2<<"  taille : "<<arbres.size()<<endl;

        /*if (co1 + 1 > arbres.size())
            arbres.erase(arbres.begin() + co1-1);
        else*/
            arbres.erase(arbres.begin() + co1);


        //if (co2 + 1 >= arbres.size() )
            arbres.erase(arbres.begin() + co2-1);
        /*else
            arbres.erase(arbres.begin() + co2);*/
        
        arbres.push_back(tmpArbre);

         for (size_t i = 0; i < arbres.size(); i++)
        {
            cout<<"  "<<arbres.at(i)->getRacine()->getEtiquette()<<"  ";
        }
        cout<<endl;

        // fusionner les deux min et les supprimer du vector arbres puis finalement ajouter le résultat de la fusion  
    }

    //  >>>>>>>>>>>>
   
   
    affiche(arbres.at(0));

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


