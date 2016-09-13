#include <cstdlib>
#include <vector>
#include <iostream>
#include "inode.h"
#include "CMD/parser.h"

/*
* Variables globales, inclure dans une fonction avec extern inode *root;
*/
inode *root;
inode *wd;

int max_blocs = 52224;
int max_inodes = 69137;

/*
* Jamais utilisé pour accéder aux données, sert uniquement pour l'allocation de memoire et la libération de memoire.
*/
vector<inode *> *liste_inodes = new vector<inode *> ();
vector<bloc *> *liste_blocs = new vector<bloc *> ();
vector<element *> *liste_elements = new vector<element *> ();


void vider_ram ();
 int main ()
{
  msgBienvenue ();
  menu ();
  lectureArgs ();

  vider_ram ();
  delete liste_inodes;
  delete liste_blocs;
  delete liste_elements;
  return 0;
}

void vider_ram ()
{
  for (unsigned int i = 0; i < (*liste_inodes).size (); i++)
    {
      delete (*liste_inodes)[i];
    }

  for (unsigned int i = 0; i < (*liste_blocs).size (); i++)
    {
      delete (*liste_blocs)[i];
    }

  for (unsigned int i = 0; i < (*liste_elements).size (); i++)
    {
      delete (*liste_elements)[i];
    }
}
