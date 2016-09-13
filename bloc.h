#ifndef BLOC_H
#define BLOC_H

#include "element.h"

using namespace std;

class bloc {
public:
	bloc();
	bloc(bool ext);
	~bloc();

	/*
	* Initialise les deux pointeurs d'inodes d'un dossier
	* Premier argument dossier parent, deuxième argument dossier lui même
	*/
	void init_nodes(void *parent, void *self);

	/*
	* Ajouter un répertoire à la liste d'élément du bloc
	* Retourne un pointeur vers l'élément ajouté, NULL si non
	*/
	element *ajouter_repertoire(string nom);

	/*
	* Ajoute un fichier au bloc du répertoire courrant
	* Retourne un pointeur vers l'élément ajouté, NULL si non
	*/
	element *ajouter_fichier(string nom);

	/*
	* Modifie le pointeur suivant vers le pointeur passé en paramètre.
	*/
	void set_suivant(bloc *next)
	{
		suivant = next;
	}

	/*
	* Lister les elements sous un rep
	*/
	void listerElements();

	/*
	* Lister les elements sous un rep en detail
	*/
	void listerElementsEnDetail();

	void rm(string fichier);

	void rmdir(string name);

	element *getElement(int i) { return liste[i]; }

private:
	int nb_element;
	int nb;
	element *liste[6] = { NULL, NULL, NULL, NULL, NULL, NULL };
	bloc *suivant;

};

#endif