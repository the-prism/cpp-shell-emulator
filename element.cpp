#include <vector>
#include "element.h"

/*
* Compteur d'éléments total
*/
int compteur_element = 0;
extern vector<element*> *liste_elements;

element::element() {
	compteur_element++;
	position = compteur_element;

	(*liste_elements).push_back(this);
}

element::element(string name, char m) {
	compteur_element++;
	position = compteur_element;

	nom = name;
	type = m;

	(*liste_elements).push_back(this);
}

element::~element() {

}

