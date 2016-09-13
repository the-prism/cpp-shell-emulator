#include <cstdlib>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "../inode.h"

using namespace std;

extern inode *root;
extern inode *wd;

/*
* Menu
*/
void menu() {
	cout << "-------------------------------------------" << endl;
	cout << "------------------ MENU -------------------" << endl;
	cout << "-------------------------------------------" << endl;
	cout << "menu:                      imprimer options" << endl;
	cout << "mkdir:                  faire un repertoire" << endl;
	cout << "rmdir:              supprimer un repertoire" << endl;
	cout << "cd:                      changer repertoire" << endl;
	cout << "ls:          lister fichiers et repertoires" << endl;
	cout << "crf:      creer un fichier de taille (en k)" << endl;
	cout << "cp:                       copier un fichier" << endl;
	cout << "mv:                     Deplacer un fichier" << endl;
	cout << "rm:                      Effacer un fichier" << endl;
	cout << "blc:      Afficher numeros de blocs fichier" << endl;
	cout << "logout:                   quitter programme" << endl;
	cout << "-------------------------------------------" << endl;

}

void msgBienvenue() {
	cout << "Bienvenue dans le mini-Shell." << endl;
}

void lectureArgs() {

	root = new inode();
	(*root).init_root();

	wd = root;

	wd = (*wd).ajouter_dossier("test");
	wd = (*wd).ajouter_dossier("test2");

	string ligneEntree;
	vector<string> arguments;
	string motTemporaire;

	cout << wd->pwd() << " $> ";

	while (getline(cin, ligneEntree)) {
		arguments.clear();
		istringstream lecture(ligneEntree);

		while (lecture >> motTemporaire) {
			arguments.push_back(motTemporaire);
		}

		if (arguments.size() == 0) {
			cout << wd->pwd() << " $> ";
			continue;
		}

		else if (arguments[0] == "menu") {
			menu();
		}

		else if (arguments[0] == "mkdir") {
			if (arguments.size() == 2) {
				inode *temp;
				temp = (*wd).ajouter_dossier(arguments[1]);
				if (temp == NULL) {
					cout << "Erreur ajoute de  " << arguments[1] << endl;
				}
			}
			else if (arguments.size() == 1) {
				cout << "Pas d'arguments" << endl;
			}

		}

		else if (arguments[0] == "rmdir") {
			cout << "Vous avez choisi rmdir" << endl;

			// interpreteur de path a mettre

			if (arguments.size() == 2)
			{
				wd->rmdir(arguments[1]);
			}
			else {
				cout << "Arg count wrong" << endl;
			}
		}

		else if (arguments[0] == "cd") {
			cout << "Vous avez choisi cd" << endl;
			if (arguments.size() == 2) {
				if (arguments[1] == "/") {
					wd = root;
				}
				else if (arguments[1] == "..") {
					wd = (*wd).parent();
				}
				else if (arguments[1] == ".") {
				}
				else {

					istringstream lectureLong(arguments[1]);
					string motTempLong;
					vector<string> cheminComplet;
					while (getline(lectureLong, motTempLong, '/')) {
						cheminComplet.push_back(motTempLong);
					}


					//trouver le moyen de faire output
					int nbrElm = cheminComplet.size();
					int iter1 = 1;
					while (iter1 < nbrElm)
					{
						cout << "cd ";
						cout << cheminComplet[iter1];
						cout << endl;
						iter1++;
					}
					//-td faire des outputs avec c <nom folder> devant





					/*
					* Début CD, faudrait boucler entre tout les / dans la string et call la fonction cd sur l'inode à chaque fois.
					*/
					//					inode *temp = wd;
					//					if ((*wd).cd(arguments[1])) {
					//						// cas ok
					//					}
					//					else {
					//						// cas non ok
					//						wd = temp;
					//						cout << "Dossier inexistant" << endl;
					//					}
				}

			}
			else if (arguments.size() == 1) {
				wd = root;
			}


		}

		else if (arguments[0] == "ls") {
			cout << "Vous avez choisi ls" << endl;

			if (arguments.size() >= 2) {
				if (arguments[1] == "-l") {
					wd->ls(true);
				}
			}
			else if (arguments.size() == 1) {
				wd->ls(false);
			}
		}

		else if (arguments[0] == "crf") {
			cout << "Vous avez choisi crf" << endl;
			if (arguments.size() != 3) {
				cout << "Nb argumens invalide" << endl;
			}
			else {
				wd->ajouter_fichier(arguments[1], stoi(arguments[2]));
			}
		}

		else if (arguments[0] == "cp") {
			cout << "Vous avez choisi cp" << endl;
		}

		else if (arguments[0] == "mv") {
			cout << "Vous avez choisi mv" << endl;
		}

		else if (arguments[0] == "rm") {
			cout << "Vous avez choisi rm" << endl;
			if (arguments.size() != 2) {
				cout << "Nb argumens invalide" << endl;
			}
			else {
				wd->rm(arguments[1]);
			}
		}

		else if (arguments[0] == "blc") {
			cout << "Vous avez choisi blc" << endl;

			if (arguments.size() != 2) {
				cout << "Nb argumens invalide" << endl;
			}
			else {
				wd->blc(arguments[1]);
			}
		}

		else if (arguments[0] == "pwd") {
			cout << wd->pwd();
		}

		else if (arguments[0] == "logout") {
			cout << "Fin normale." << endl;
			break;
		}

		cout << wd->pwd() << " $> ";
	}
}


