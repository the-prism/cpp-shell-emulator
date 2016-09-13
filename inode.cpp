#include "inode.h"
#include <vector>
#include <iostream>

extern vector<inode *> *liste_inodes;
extern inode *root;
extern inode *wd;
extern int max_inodes;
extern int max_blocs;
extern int compteur_bloc;

inode::inode() {
	if (max_inodes == 0) {
		exit(2000);
	}
	max_inodes--;

	/* Écrit le mode du fichier, dans ce cas le dossier / "Root" */
	mode = "drwxrwxrwx";

	nb_liens = 1;
	user = 0;
	group = 0;
	taille = 0;

	/* Get timestamp and write into	*/
	time(&creation);
	time(&acces);
	time(&modification);

	premiers_bloc[0] = new bloc();
	(*liste_inodes).push_back(this);
}

void inode::init_root() {
	extern inode *root;
	(*premiers_bloc[0]).init_nodes(this, this);
	root = this;
}

/*
 * Liste les fichiers sous l'inode courant.
 */
string getMod();

inode::inode(char mode, inode *parent) {
	if (max_inodes == 0) {
		exit(2000);
	}
	max_inodes--;
	if (mode == 'd' && parent != NULL) {
		premiers_bloc[0] = new bloc();
		/* Do more stuff here */
		this->mode = "drwxrwxrwx";
		(*premiers_bloc[0]).init_nodes(parent, this);
	}
	else if (mode == 'f' && parent != NULL) {
		this->mode = "-rwxrwxrwx";
		taille = 0;
	}
	(*liste_inodes).push_back(this);
}

inode::inode(int size) {
	if (max_inodes == 0) {
		exit(2000);
	}
	max_inodes--;
	mode = "-rwxrwxrwx";
	taille = size;
	int bloc_requis = ( size / 2 );
	if (max_blocs >= bloc_requis) {
		compteur_bloc++;
		bloc_depart = compteur_bloc;
		compteur_bloc += bloc_requis;
		bloc_fin = compteur_bloc;
		max_blocs -= bloc_requis;
	}
	else {
		exit(2001);
	}
	
	
	(*liste_inodes).push_back(this);
}

inode::~inode() {
	/* Vider la memoire du tableau de bloc direct */

	/* Vider la memoire de l'indirection simple */
	if (i_simple != NULL) {
		delete i_simple;
		i_simple = NULL;
	}

	/* Vider la memoire de l'indirection double */
	if (i_double != NULL) {
		delete i_double;
		i_simple = NULL;
	}

	/* Vider la memoire de l'indirection triple */
	if (i_triple != NULL) {
		delete i_triple;
		i_triple = NULL;
	}
}

/*
* Ajoute un dossier au répertoire courrant.
* Retourne un pointeur su le dossier créé.
*/
inode *inode::ajouter_dossier(string name) {
	bool done = false;
	inode *nouveau = NULL;
	if (mode == "drwxrwxrwx") { // Fonctionne seulement si on est dans un dossier
		for (short i = 0; i < 10 && !done; i++) {
			if (premiers_bloc[i] != NULL) {
				if (premiers_bloc[i + 1] == NULL) {
					element *pt = (*premiers_bloc[i]).ajouter_repertoire(name);
					//-td initialiser linode
					pt->getInode();

					if (pt == NULL) {
						premiers_bloc[i + 1] = new bloc(true);
						(*premiers_bloc[i]).set_suivant(premiers_bloc[i + 1]);
					}
					else {
						nouveau = new inode('d', this);
						(*pt).setInode(nouveau);
						done = true;
					}
				}
			}
		}
	}
	return nouveau;
}

/*
* Ajoute un fichier dans un répertoire
* Retourne un pointeur vers l'inode du dossier courrant.
*/
inode *inode::ajouter_fichier(string name, int size) {
	bool done = false;
	inode *nouveau = NULL;
	if (mode == "drwxrwxrwx") { // Opération fonctionne seulement si on est dans un dossier.
		for (short i = 0; i < 10 && !done; i++) {
			if (premiers_bloc[i] != NULL) {
				element *pt = (*premiers_bloc[i]).ajouter_fichier(name);
				if (pt == NULL) {
					premiers_bloc[i + 1] = new bloc(true);
					(*premiers_bloc[i]).set_suivant(premiers_bloc[i + 1]);
				}
				else {
					nouveau = new inode(size);
					(*pt).setInode(nouveau);
					done = true;
				}
			}
		}
	}
	return this;
}

/*
* Fonction retourne l'inode root si la string est "/"
* La fonction navigue à partir de l'inode auquel elle est appelée.
* Retourne un pointeur vers l'inode du dossier choisit, si le dossier n'est pas trouvé, retourne NULL
*/
inode *inode::acces_dossier(string name) {
	extern inode *root;
	if (name == "/") {
		return root;
	}
	else {
		// Naviguer vers le dossier choisit
	}
	return NULL;
}

/*
 * Liste les fichiers sous l'inode courant.
 */
void inode::ls(bool mode) {
	if (mode) {
		bool done = false;
		for (short i = 0; i < 10 && !done; i++) {
			if (premiers_bloc[i] == NULL) {
				done = true;
			}
			else {
				premiers_bloc[i]->listerElementsEnDetail();
			}
		}
	}
	else {
		bool done = false;
		for (short i = 0; i < 10 && !done; i++) {
			if (premiers_bloc[i] == NULL) {
				done = true;
			}
			else {
				premiers_bloc[i]->listerElements();
			}
		}
	}
}

/*
 * Retourne le utilisateur
 */
int inode::getUser()
{
	return this->user;
}

/*
 * Retourne l'Administrateur
 */
int inode::getGroup()
{
	return this->group;
}

/*
 * Retourne le mode.
 */
string inode::getMode()
{
	return this->mode;
}

/*
 * Retourne la taille.
 */
int inode::getTaille()
{
	return this->taille;
}

time_t inode::getTemps()
{
	return this->creation;
}

/*
 * Liste le chemin actuel
 */
string inode::pwd() {

	string nameFolder = "";

	inode *temp;
	inode *temp2;
	temp = this;
	temp2 = this;

	if (temp != root) {
		//find name folder
		temp = (inode *)(*(*temp->premiers_bloc[0]).getElement(1)).getInode();
		nameFolder = (*temp).name(temp2);
		nameFolder = temp->pwd() + nameFolder;
	}

	nameFolder += "/";

	return nameFolder;
}

string inode::name(inode *folder) {
	string result = "";
	bool done = false;
	for (int i = 0; i < 10 && !done; ++i) {
		for (int j = 0; j < 6 && !done; ++j) {
			if (premiers_bloc[i] == NULL || (*premiers_bloc[i]).getElement(j) == NULL) {
				done = true;
			}
			else {
				if (folder == (*(*premiers_bloc[i]).getElement(j)).getInode()) {
					result = (*(*premiers_bloc[i]).getElement(j)).getNom();
				}
			}
		}
	}
	return result;
}

bool inode::cd(string name) {
	bool done = false;
	for (int i = 0; i < 10 && !done; ++i) {
		for (int j = 0; j < 6 && !done; ++j) {
			if (premiers_bloc[i] == NULL || (*premiers_bloc[i]).getElement(j) == NULL) {
				done = true;
				return false;
			}
			else {
				if (name == (*(*premiers_bloc[i]).getElement(j)).getNom()) {
					wd = (inode*)(*(*premiers_bloc[i]).getElement(j)).getInode();
					return true;
				}
			}
		}
	}
}

void inode::blc(string name) {
	bool done = false;
	for (int i = 0; i < 10 && !done; ++i) {
		for (int j = 0; j < 6 && !done; ++j) {
			if (premiers_bloc[i] == NULL || (*premiers_bloc[i]).getElement(j) == NULL) {
				done = true;
			}
			else {
				if (name == (*(*premiers_bloc[i]).getElement(j)).getNom()) {
					inode *pt = (inode*)(*(*premiers_bloc[i]).getElement(j)).getInode();
					for (int i = pt->bloc_depart; i <= pt->bloc_fin; i++)
					{
						cout << i << " ";
					}
					cout << endl;
					done = true;
				}
			}
		}
	}
}

void inode::rm(string fichier) {
	bool done = false;
	for (int i = 0; i < 10 && !done; ++i) {
		for (int j = 0; j < 6 && !done; ++j) {
			if (premiers_bloc[i] == NULL) {
				done = true;
			}
			else if ((*premiers_bloc[i]).getElement(j) != NULL) {
				inode *pt = (inode*)(*(*premiers_bloc[i]).getElement(j)).getInode();
				if (fichier == (*(*premiers_bloc[i]).getElement(j)).getNom()) {
					(*premiers_bloc[i]).rm(fichier);
					max_blocs += (pt->taille / 2);
					max_inodes++;
					done = true;
				}
			}
		}
	}
}

void inode::rmdir(string name) {
	bool done = false;
	for (int i = 0; i < 10 && !done; ++i) {
		for (int j = 0; j < 6 && !done; ++j) {
			if (premiers_bloc[i] == NULL) {
				done = true;
			}
			else if ((*premiers_bloc[i]).getElement(j) != NULL) {
				inode *pt = (inode*)(*(*premiers_bloc[i]).getElement(j)).getInode();
				if (name == (*(*premiers_bloc[i]).getElement(j)).getNom()) {
					(*premiers_bloc[i]).rmdir(name);
					max_inodes++;
					done = true;
				}
			}
		}
	}
}

