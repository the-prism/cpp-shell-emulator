#ifndef INODE_H
#define INODE_H

#include <ctime>
#include "bloc.h"

using namespace std;

/*
* Classe Indirection Simple
* Constructeur et destructeur
*/
class indirection_simple {
public:
	indirection_simple() { }

	~indirection_simple() { }

	bloc *no_bloc[256];
};

/*
* Classe Indirection Double
* Constructeur et destructeur
*/
class indirection_double {
public:
	indirection_double() { }

	~indirection_double() { }

	indirection_simple *is[256];
};

/*
* Classe Indirection Triple
* Constructeur et destructeur
*/
class indirection_triple {
public:
	indirection_triple() { }

	~indirection_triple() { }

	indirection_double *id[256];
};

/*
* Classe Inode
*/
class inode {
public:
	inode();

	void init_root();

	inode(char mode, inode *parent);

	inode(int size);

	/*
	 * Liste les fichiers sous l'inode courant.
	 */
	void ls(bool mode);


	/*
	 * Retourne le utilisateur
	 */
	int getUser();

	/*
	 * Retourne l'Administrateur
	 */
	int getGroup();

	/*
	 * Retourne le mode.
	 */
	string getMode();

	/*
	 * Retourne la taille.
	 */
	int getTaille();

	/*
	 * Retourne le temps
	 */
	time_t getTemps();

	int getBlocDepart() { return bloc_depart; }

	int getBlocFin() { return bloc_fin; }

	void blc(string name);

	void rm(string fichier);



	/*
	 * Trouve le chemin du dossier
	 */
	string pwd();

	/*
	* Ajoute un dossier au dossier courant
	* Retourne un pointeur vers l'inode du nouveau dossier
	*/
	inode *ajouter_dossier(string name);


	/*
	* Ajoute un fichier dans le dossier courant.
	* Retourne un pointeur vers le dossier courant.
	*/
	inode *ajouter_fichier(string name, int size);

	/*
	* Navigation vers un dossier à partir de l'inode courant.
	* Retourne NULL si le dossier n'existe pas, si non retourne un pointeur vers l'inode du dossier.
	*/
	inode *acces_dossier(string name);

	/*
	* Destructeur de la classe inode, effectue la destruction de tous les éléments aloués dynamiquement.
	*/
	~inode();

	string name(inode *folder);

	void rmdir(string name);

	bool cd(string name);

	inode* parent() { return (inode *)(*(*premiers_bloc[0]).getElement(1)).getInode(); }

private:
	string mode;
	unsigned int nb_liens;
	int user;
	int group;
	unsigned int taille;
	time_t creation;
	time_t acces;

	time_t modification;

	bloc *premiers_bloc[11] = { NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL };

	indirection_simple *i_simple = NULL;
	indirection_double *i_double = NULL;

	indirection_triple *i_triple = NULL;

	int bloc_depart;
	int bloc_fin;
};

#endif