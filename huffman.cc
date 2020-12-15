#include "huffman.hh"
using namespace std;

huffman::huffman()
{
     for (size_t i = 0; i < 94; i++) // INTIALISER LE TABLEAU ALPHABET 
    {
        this->alphabet[i] = 0;
    }
    this->nbreCar = 0;
}

bool huffman::code_lettre( char car, Sommet* s , std::vector <int> * V )
{    
    if ( (s-> getGauche() == NULL && s->getDroit() == NULL ) || (s->getGauche()->getEtiquette() == -1 && s->getDroit()->getEtiquette() == -1 ) )
        return (s->getEtiquette2() == car) ;
    
    if (s->getGauche()!= NULL && code_lettre( car , s->getGauche() , V))
    {
        V->push_back(1);
        return true;
    }
  
    if(s->getDroit()!= NULL && code_lettre( car , s->getDroit() , V))
    {
        V->push_back(0);
        return true;
    }
    
    return false;          
}

void huffman::lecture_traitements()
{
     do // LECTURE DU TEXTE                          
    {
       cout<<"Veuillez entrez le texte SVP \n";
       getline(cin,this->texte);   

    } while (this->texte.size() <= 0);

    for (size_t i = 0; i < this->texte.size(); i++) // stocker le code ascii de chaque caractére du texte et incrémenter la case correspondante au caractére de 1
    {
        this->alphabet[this->texte.at(i) - 32]++;
    }
    
    this->nbreCar = 0;

    //cout<<" alphabet : "<<endl;
    for (size_t i = 0; i < 94; i++) // convertir le nombre d'ocurrence de chaque caractére en un pourcentage d'occurence par rapport au nombre de caractéres dans le texte 
    {
        if (alphabet[i] != 0)
        {
            this->alphabet[i] = (this->alphabet[i] * 100) / this->texte.size();
            //cout<<" "<<this->alphabet[i]<<" ";
            this->nbreCar++;
        }
    }
    //cout<<endl;
}

void huffman::initialiser_vecteurs_arbres()
{
    for (size_t i = 0; i < this->nbreCar; i++) // initialiser le vecteur arbres  
    {
        this->arbres.push_back(new ArbreB);
    }
    int i=0,j=0;

    while (j < 94 && i < this->arbres.size()) // assigner à chaque arbre un caractére
    {     
        if (this->alphabet[j] != 0)
        {
            this->arbres.at(i)->inserer(new Sommet(this->alphabet[j],j+32));
            i++;
        }
        j++;

    }

     
    cout<<" l'alphabet : \n";

    for ( ArbreB * elem : this->arbres) // afficher l'alphabet 
    {
        cout<<" "<<elem->getRacine()->getEtiquette2()<<" ";
    }
    cout<<endl;

}

void huffman::fusionner_arbres()
{
    int min1,min2,co1,co2;
    char tmp1;

    ArbreB * tmpArbre;
    while (arbres.size()>1)  // Fusionner les arbres du vecteur arbres jusqu'a avoir un seul arbre dans le vecteur qui auront un pourcentage = 100 
    {

        if (arbres.at(1)->getRacine()->getEtiquette() < arbres.at(0)->getRacine()->getEtiquette()) // // determiner le minimum en terme de pourcentage d'occurence 
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
        this->dechets.push_back(arbres.at(co1)); // stocker arbre qui a était fusionner dans dechets pour etre supprimer
        this->dechets.push_back(arbres.at(co2)); // stocker arbre qui a était fusionner dans dechets pour etre supprimer

        tmpArbre = new ArbreB;
        arbres.at(co1)->fusion(arbres.at(co2),tmpArbre); // faire la fusion de deux arbres et récupérer le résultat dans tmpArbre

        tmp1 = arbres.at(co2)->getRacine()->getEtiquette2(); 
   
        arbres.erase(arbres.begin() + co1); // supprimer le premier arbre fusionné du vecteur arbres


        for (size_t i = 0; i < arbres.size(); i++)  // supprimer le deuxième arbre fusionné du vecteur arbres
        {
            if(tmp1 == arbres.at(i)->getRacine()->getEtiquette2())
            {
                arbres.erase(arbres.begin() + i); 
                break;
            }
        }
        arbres.push_back(tmpArbre); // inserer l'arbre résultat de la fusion

    }
    
}

void huffman::vider()
{
      for (size_t i = 0; i < dechets.size(); i++)
    {
        delete dechets.at(i);
    }
    dechets.clear();
}

std::vector<ArbreB *> huffman::getArbres() // retourne le vecteur arbres
{
    return this->arbres;
}

void huffman::genere_code()
{
    std::vector<int> tmp_code;
    char tmp1;
    
    cout<<"Le code des lettres du texte ( Gauche = 0 et Droite = 1, sens de lecture \nde bas vers le haut -->\nde haut vers le bas <-- ) \n";
    for (size_t i = 0; i < 94 ; i++)
    {
        if (this->alphabet[i] != 0)
        {   
            tmp1 = i+32 ;

            code_lettre(i+32,this->arbres.at(0)->getRacine(),&tmp_code);

            cout<<tmp1<<"  =  ";
            
            for (int elem : tmp_code)
            {
                cout<<elem;
            }
            cout<<endl;
            tmp_code.clear();
        }
    }
    cout<<endl;


    cout<<endl<<"le code du texte (sens de lecture --> ) :      "<<endl;
    for (size_t i = 0; i < texte.size(); i++)
    {
        code_lettre(texte.at(i),arbres.at(0)->getRacine(),&tmp_code);

        for (int elem : tmp_code)
        {
            cout<<elem;
        }
        tmp_code.clear();
        
    }
    cout<<endl<<endl;
}

