#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <vector>
#include <iostream>
#include "bloc.h"
#include "inode.h"
#include <ctime>

/*
* Compteur de bloc total.
*/
int compteur_bloc = 0;
extern vector<bloc *> *liste_blocs;

bloc::bloc()
{
	compteur_bloc++;
	nb = compteur_bloc;
	nb_element = 2;
	liste[0] = new element(".", 'd');
	liste[1] = new element("..", 'd');
	(*liste_blocs).push_back(this);
}

bloc::bloc(bool ext)
{
	compteur_bloc++;
	nb = compteur_bloc;
	if (ext)
	{

	}
	(*liste_blocs).push_back(this);
}

void bloc::init_nodes(void *parent, void *self)
{
	(*liste[0]).setInode(self);
	(*liste[1]).setInode(parent);
}

void bloc::listerElements()
{
	bool done = false;
	for (short i = 0; i < 6 && !done; i++)
	{
		if (liste[i] != NULL)
		{
			cout << liste[i]->getNom() << "  ";
		}
	}
	cout << endl;
}

void bloc::listerElementsEnDetail()
{
	bool done = false;
	for (short i = 0; i < 6 && !done; i++)
	{
		if (liste[i] != NULL)
		{
			inode* tempRef = (inode *)liste[i]->getInode();
			cout << tempRef->getMode();
			cout << " ";
			int user = tempRef->getUser();
			if (user == 0) { cout << "Usager_1"; }
			cout << " ";
			int other = tempRef->getGroup();
			if (other == 0) { cout << "Autre"; }
			cout << " ";
			cout << tempRef->getTaille();
			cout << "K ";
			time_t tempTemp = (tempRef->getTemps());
			char buff[20];
			strftime(buff, 20, "%b %d %H:%M", localtime(&tempTemp));
			cout << buff;
			cout << " ";
			cout << liste[i]->getNom();
			cout << endl;
		}
	}
}

bloc::~bloc()
{

}

element *bloc::ajouter_repertoire(string nom)
{
	bool done = false;
	element *pt = NULL;
	for (short i = 0; i < 6 && !done; i++)
	{
		if (liste[i] == NULL)
		{
			pt = new element(nom, 'd');
			liste[i] = pt;
			done = true;
		}
	}
	return pt;
}

element *bloc::ajouter_fichier(string nom)
{
	bool done = false;
	element *pt = NULL;
	for (short i = 0; i < 6 && !done; i++)
	{
		if (liste[i] == NULL)
		{
			pt = new element(nom, 'f');
			liste[i] = pt;
			done = true;
		}
	}
	return pt;
}

void bloc::rm(string fichier) {
	bool done = false;
	for (int i = 0; i < 6 && !done; i++)
	{
		if (liste[i] != NULL) {
			if (liste[i]->getNom() == fichier && liste[i]->getType() == 'f') {
				liste[i] = NULL;
			}
		}
	}
}

void bloc::rmdir(string name) {
	bool done = false;
	for (int i = 0; i < 6 && !done; i++)
	{
		if (liste[i] != NULL) {
			if (liste[i]->getNom() == name && liste[i]->getType() == 'd') {
				liste[i] = NULL;
			}
		}
	}
}