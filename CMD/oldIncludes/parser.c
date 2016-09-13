#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#include <errno.h>


/*
* Menu
*/
void menu (void) {
  printf ("-------------------------------------------\n");
  printf ("------------------ MENU -------------------\n");
  printf ("-------------------------------------------\n");
  printf ("menu:                      imprimer options\n");
  printf ("mkdir:                  faire un repertoire\n");
  printf ("rmdir:              supprimer un repertoire\n");
  printf ("cd:                      changer repertoire\n");
  printf ("ls:          lister fichiers et repertoires\n");
  printf ("crf:      creer un fichier de taille (en k)\n");
  printf ("cp:                       copier un fichier\n");
  printf ("mv:                     Deplacer un fichier\n");
  printf ("rm:                      Effacer un fichier\n");
  printf ("blc:      Afficher numeros de blocs fichier\n");
  printf ("logout:                   quitter programme\n");
  printf ("-------------------------------------------\n");

}



void msgBienvenue (void) {
  puts ("Bienvenue dans le mini-Shell.");
}
