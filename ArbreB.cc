#include "ArbreB.hh"
#include <iostream>
#include <queue>

using namespace std;

ArbreB::ArbreB()
{
    this->racine=NULL;
}

ArbreB::ArbreB(ArbreB &ACopier)
{
    if(ACopier.getRacine()==NULL)
        this->racine=NULL;

    queue<Sommet *> q;
    q.push(ACopier.getRacine());
    
    Sommet *r = new Sommet(ACopier.getRacine()->getEtiquette(),ACopier.getRacine()->getEtiquette2());
    this->setRacine(r);
    
    queue<Sommet *> q1;
    q1.push(this->getRacine());
    Sommet *temp;
    Sommet *temp1;
    while (!q.empty())
    {
        temp = q.front();
        temp1 = q1.front();

        q.pop();
        q1.pop();

        if(temp->getGauche() != NULL)
        {
            Sommet *s1 = new Sommet();
            s1->setEtiquette(temp->getGauche()->getEtiquette());
            s1->setEtiquette2(temp->getGauche()->getEtiquette2());
            temp1->setGauche(s1);
            
            q1.push(temp1->getGauche());
            q.push(temp->getGauche());
        }

        if(temp->getDroit()  != NULL)
        {
            Sommet *s2 = new Sommet();
            s2->setEtiquette(temp->getDroit()->getEtiquette());
            s2->setEtiquette2(temp->getDroit()->getEtiquette2());
            temp1->setDroit(s2);
            
            q1.push(temp1->getDroit());
            q.push(temp->getDroit());
        }
    }
}

ArbreB::~ArbreB()
{
    if (this->racine)
    {
        delete this->racine;
    }
}

Sommet *ArbreB::getRacine()
{
    return this->racine;
}

void ArbreB::setRacine(Sommet *r)
{
    this->racine=r;
}

void ArbreB::inserer(ArbreB **a,Sommet *s)
{
    if ( (*a)->getRacine() == NULL)
    {
        (*a)->setRacine(s);
        return;
    }
    
    queue<Sommet *> q;
    q.push((*a)->racine);
    
    while(! q.empty())
    {
        Sommet *temp = q.front();
        q.pop();
        
        if (temp->getGauche() == NULL)
        {
            temp->setGauche(s);
            return;
        }
        else
        {
            q.push(temp->getGauche());
        }

        if (temp->getDroit() == NULL)
        {
            temp->setDroit(s);
            return;
        }
        else
        {
            q.push(temp->getDroit());
        }
    }
}

Sommet *ArbreB::rechercher(double etiq)
{
    if(this->racine==NULL)
        return NULL;

    queue<Sommet *> q;
    q.push(this->racine);

    Sommet *sortie = NULL;
    Sommet *temp;
    while (!q.empty())
    {
        temp = q.front();
        q.pop();

        if(temp->getEtiquette() == etiq) sortie = temp;
        if(temp->getGauche() != NULL) q.push(temp->getGauche());
        if(temp->getDroit()  != NULL) q.push(temp->getDroit());
    }
    
    return sortie;
}

void ArbreB::supprimerProfondDroit(Sommet *profondD)
{
    queue<Sommet *> q;
    q.push(this->racine);
    Sommet *temp;

    while(!q.empty())
    {
        temp = q.front();
        q.pop();

        if (temp->getGauche() != NULL)
        {
            if (temp->getGauche() == profondD)
            {
                temp->setGauche(NULL);
                return;
            }
            else
            {
                q.push(temp->getGauche());
            }
            
            
        }

        if (temp->getDroit() != NULL)
        {
            if (temp->getDroit() == profondD)
            {
                temp->setDroit(NULL);
                return;
            }
            else
            {
                q.push(temp->getDroit());
            }
            
            
        }
        
    }
}

void ArbreB::supprimer(double etiq)
{
    Sommet *sommetASuprimer = this->rechercher(etiq);

    if (sommetASuprimer != NULL)
    {
        queue<Sommet *> q;
        q.push(this->racine);
        Sommet *temp;

        while (!q.empty())
        {
            temp = q.front();
            q.pop();

            if(temp->getGauche() != NULL)
                q.push(temp->getGauche());
            if(temp->getDroit() != NULL)
                q.push(temp->getDroit());
        }

        double etiAProfondD = temp->getEtiquette();

        supprimerProfondDroit(temp);

        sommetASuprimer->setEtiquette(etiAProfondD);
    }
}

ArbreB *ArbreB::fusion(ArbreB *a,ArbreB *b)
{
    ArbreB *c = new ArbreB();
    
    ArbreB *aCopie = new ArbreB(*a);
    ArbreB *bCopie = new ArbreB(*b);
    
    Sommet *nouvelleRacine = new Sommet(a->getRacine()->getEtiquette() + b->getRacine()->getEtiquette(),'!');

    c->setRacine(nouvelleRacine);
    c->getRacine()->setGauche(aCopie->getRacine());
    c->getRacine()->setDroit(bCopie->getRacine());


    return c;
}

void ArbreB::decomposition(ArbreB **ArbreUn,ArbreB **ArbreDeux)
{
    ArbreB *temp = new ArbreB(*this);

    (*ArbreUn)->inserer(&(*ArbreUn),temp->getRacine()->getGauche());
    (*ArbreDeux)->inserer(&(*ArbreDeux),temp->getRacine()->getDroit());
}

void affiche(ArbreB *a)
{
  affiche_sommet(a->getRacine(),1);
  cout << endl << endl;
}

void  affiche_sommet(Sommet *s, int niveau)
{
  int i;
 
  if (s)
  {
    affiche_sommet(s->getDroit(), niveau + 1);
    for (i = 0; i < niveau; i++)
    {
      cout << "        ";
    }
    //cout.precision(3);
    cout << s->getEtiquette() <<" "<< s->getEtiquette2()<<endl;
    affiche_sommet(s->getGauche(), niveau + 1);
  }
}