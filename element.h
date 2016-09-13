#ifndef ELEMENT_H
#define ELEMENT_H

#include <string>

using namespace std;

class element {
public:
	element();
	element(string name, char t);
	~element();
	
	/*
	* Set le pointeur d'inode pour celui passé en argument.
	*/
	void setInode(void *node) { inode = node; }
	
	/*
	* Retourne un pointeur void sur l'inode de l'élément
	*/
	void* getInode() { return inode; }
	
	/*
	* Retourne le nom de l'élément
	*/
	string getNom() { return nom; }

	char getType() { return type; }

private:
	unsigned int position;
	string nom;
	char type;
	void *inode;
};

#endif