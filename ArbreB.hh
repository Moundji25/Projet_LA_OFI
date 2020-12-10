#ifndef ARBREB_HH
#define ARBREB_HH
#include "Sommet.hh"

class ArbreB : public Sommet
{
	private:
		Sommet *racine; //Attribut racine de type pointeur vers un Sommet
	
	public:
		ArbreB(); //Constructeur arbre vide
		
		ArbreB(ArbreB &ACopier); //Constructeur par recopie
		
		~ArbreB(); //destructeur 
		
		Sommet *getRacine(); //retourne un pointeur vers la racine
		
		void setRacine(Sommet *r); //placer une nouvelle racine
		
		void inserer(ArbreB **a,Sommet *s); //insere dans l'arbre le sommet s en cherchant la premiere place libre (du niveau le plus petit et la priorité de la gauche )
		
		Sommet *rechercher(double etiq); // retourne un pointeur vers le sommet dont on a indiquer l'etiquette en parametre  (si deux sommet ont la meme etiquette il retourne le plus profond
																														//et si ils ont le meme niveau elle retourne celui qui se trouve a droite 
		void supprimerProfondDroit(Sommet *profondD); //supprime le sommet le plus profond a droite ( utile dans la méthode supprimer en dessous)
		
		void supprimer(double etiq); //supprime le sommet le plus profond , la priorité a la droite 
		
		ArbreB *fusion(ArbreB *a,ArbreB *b); // fusionne les deux sommets passés en paramétres et retourne un arbre 
												// dont la racine est une nouvelle qui a pour étiquette la somme des deux étiquettes des sommets passés en parametre
												// et dont le sous arbre droit est le premier parametre et le sous arbre gauche est le deuxieme parametre 
		
		void decomposition(ArbreB **ArbreUn,ArbreB **ArbreDeux); //décompose l'arbre en deux sous arbres et remplie les deux arbres passés en paramétre 
																	// le sous arbre gauche est retourner avec le premier parametre 'ArbreUn' 
																	//	le sous arbre gauche est retourner avec le premier parametre 'ArbreDeux'			
};																					

void affiche(ArbreB *a); //affiche un arbre en appelant la fonction affiche_sommet 
void  affiche_sommet(Sommet *s, int current_level); //fonction récursive qui permet l'affichage d'un arbre

#endif