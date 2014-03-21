
/*
 
 trier.c
 
 Created by Simon Hubert on 05/10/12.
 Copyright (c) 2012 __MyCompanyName__. All rights reserved.
 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file.h"
#include "trier_monotonie.h"

#define FIN "EOF\n"
#define CHAR_MAX 256

void read_alloc (void * f, FILE * fich_entree);

void write_remove (void *f, FILE * fich_sortie);

int main (int argc, char *argv[]) {
    /* i : permet de parcourir les éléments, inverse : boolean permettant de savoir si "-r" est choisie, no_repeat : de même que inverse pour l'option "-u" */
    int i, inverse=0, no_repeat=0;
    FILE * fich_entree = stdin ;
    FILE * fich_sortie = stdout ;
    void * file = init();
    
    /*condition permettant de valider ou non le nombre d'arguments*/
    if (argc > 6) {
        printf(" Erreur d'option : il y a trop d'arguments ");
        exit(0);
    }
    /*parcours des différents arguments */
    for (i=1; i < argc ; i++) {
        /*activation ou non de l'option "-r"*/
        if (strcmp(argv[i],"-r") == 0) {
            inverse = 1 ;
        }
        /*activation ou non de l'option "-u"*/
        else if (strcmp(argv[i],"-u") == 0) {
            no_repeat = 1 ;
        }
        /*activation ou non de l'option "-o" avec recuperation du fichier de sortie*/
        else if (strcmp(argv[i],"-o") == 0) {
            if ((fich_sortie = fopen(argv[i+1],"w")) == NULL) {
                fprintf(stderr, " Erreur : Impossible d'ecrire le fichier %s\n",argv[i+1]);
                exit(0);
            }
        }
        /*activation ou non de l'option "[fichier_entree]" avec recuperation du fichier d'entree*/
        else if (strcmp(argv[i-1],"-o") != 0) 
				if ((fich_entree = fopen(argv[i],"r")) == NULL) {
					fprintf(stderr, " Erreur : Impossible de lire dans le fichier %s\n",argv[i]);
					exit(0);
				}
    }	
	
	/*lecture et enregistrement*/
	read_alloc(file, fich_entree);  
	/*on lance le tri avec les parametre definit*/
	sort (file, inverse, no_repeat);
	
	/*Ecriture et suppression*/
	write_remove(file, fich_sortie);
	
	fclose(fich_entree);
	fclose(fich_sortie);
	free (file);
	
    return 0 ;
}

/*cette fonction permet de lire sur l'entree standard et sauvegarder les donnees dans le param
 param :
	- f : un pointeur qui va pointer vers les donnees qu'on va enregistrer
	- fich_entree : le flux sur le quel on va pouvoir recuperer des infos
 */
void read_alloc (void * f, FILE * fich_entree){
	char * s = malloc((CHAR_MAX+1)*sizeof(char));
	while (fgets(s, CHAR_MAX+1, fich_entree)) {
		enfiler(s,f);
		s = malloc((CHAR_MAX+1)*sizeof(char));
	}
	free(s);
}

/*cette fonction permet d'ecrire sur la sortie standard les donnes passer en parametre, et supprime aussi ces donnes
 param : 
	- file : un pointeur vers les donnes qu'on passer a la sortie standard et supprimer
	- fich_sortie : le flux sur le quel on va pouvoir imprimer les infos*/
void write_remove (void * file, FILE * fich_sortie){

	char * p_char; /*le pointeur sur caractere*/
	
	while (!is_empty(file)){
		p_char = defiler(file); /*on va devoir sauvegarder l'adresse de la chaine de caractere
								 pour pouvoir la supprimer apres passage vers la sortie standard*/
		fputs(p_char,fich_sortie);
		
		free(p_char);
	}	
}

