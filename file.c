
/*
  
 file.c

 Created by Simon Hubert on 05/10/12.
 Copyright (c) 2012 __MyCompanyName__. All rights reserved.

 */

#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include "file.h"

#define CHAR_MAX 256

typedef struct Maillon {
    char * ligne ;
    struct Maillon * suivant ;
} Maillon ;

typedef struct Chaine {
    Maillon * tete ;
    Maillon * queue ;
} Chaine ;

/*
 
 Initialise la file à NULL
    return : la file initialiser
 */

void * init () {
    
    Chaine * cop = malloc(sizeof(Chaine));
    cop->tete = NULL ;
    cop->queue = NULL ;
    return cop ;
}

/*
 
 Permet de savoir si la tete est vide
    f : la file en question
    return : la tete de la file f

 */

int is_empty (file f) {
    Chaine * cop = (Chaine *) f ;
    if (cop->tete==NULL)
        return 1 ;
    else
        return 0 ;
}

/* 
 
 Permet de savoir si la file est triée ou non, pour savoir si on a une monotonie ou pas.
    f : la file en question
    return : int de validation, 0 en cas d'echec, et 1 reussite
 
 */

int is_try (file f, int inverse) {
    Chaine * cop;
    Maillon * temp;
	
	if(! is_empty(f)){
		cop = (Chaine *) f ;
		temp = cop->tete ;
		while (temp->suivant != NULL) {
			if(inverse){
				if (strcmp(temp->ligne,temp->suivant->ligne) < 0)
					return 0;
			}
			else {
				if (strcmp(temp->ligne,temp->suivant->ligne) > 0) 
					return 0;
			}

			temp = temp->suivant ;
		}
	}
    return 1;
}

/*
 
 Permet de comparer la tete de deux files
	f1,f2 : les deux files en question
	return : int de validation, 1 si f1>f2, et 0 dans le cas inverse
 
 */

int comparer_tete (file f1, file f2) {
    
    Chaine * cop1;
    Chaine * cop2;
    
	if ( (!is_empty(f1)) && (!is_empty(f2)) ) {
		cop1 = (Chaine *) f1 ;
		cop2 = (Chaine *) f2 ;
        
		return strcmp (cop1->tete->ligne, cop2->tete->ligne);
    
    }
    
    else {
        printf("\n Erreur comparaison d'une ou deux files vide \n");
        exit(0) ;
    }

}

/*
 
 Permet de comparer la tete d'une file et la queue d'une autre
    f1 : file contenant la tete a comparer
    f2 : file contenant la queue a comparer
    return : int de validation, 1 si f1>f2, et 0 dans le cas inverse
 
 */

int comparer_tete_queue (file f1, file f2) {
    
    Chaine * cop1;
    Chaine * cop2;
    
	if ((!is_empty(f1)) && (!is_empty(f2))) {
		cop1 = (Chaine *) f1 ;
        cop2 = (Chaine *) f2 ;
		
		return strcmp(cop1->tete->ligne, cop2->queue->ligne);
    }
    
    else {
        printf("\n Erreur comparaison d'une ou deux files vide \n");
        exit(0) ;
    }
    
}

/* 
 
 Permet d'ajouter une nouvelle ligne à la File 
    ligne : la ligne a enfiler
    f : la file de lignes qui subit l'enfilement
    return : void

 */

int enfiler (char * s, file f) {
    
    Chaine * cop = (Chaine *) f ;
    Maillon * m = malloc(sizeof(Maillon));
    m->ligne = s;
    m->suivant = NULL;
    
    if (m == NULL || s == NULL){
        return 0;
    }
    if (cop->tete != NULL) {
		cop->queue->suivant = m ;
		cop->queue = m ;
    }else 
        cop->tete = cop->queue = m ;
    
    return 1 ;
    
}

/*
 
 Permet de supprimer la ligne de tete de la File 
    f : la file de lignes
    return : un pointeur sur la ligne de tete de la File
 
 */

char * defiler (file f) {
    
	Chaine * cop = (Chaine *) f ;
	Maillon * m = cop->tete;
	char * c;
	
	if (m == NULL)
		return NULL ;
	
	else{ 
		if (cop->tete == cop->queue) 
			cop->tete = cop->queue = NULL ;
		
		else 
			cop->tete = cop->tete->suivant;
		
		c = malloc((CHAR_MAX+1)*sizeof(char));
		strcpy(c, m->ligne);
		free(m);
	}
    return c ;
}

/*
 
 Transfert la tete d'une file dans une deuxieme file
    f1 : file dont la tete est transferer
    f2 : file dont on enfile la tete 
    return : int de validation
 
 */

int transfert (file f1, file f2) {
	char * c  ;
	c = defiler(f1);
	if (c == NULL){
		return 0 ;
	}
	return enfiler(c,f2);
    
}

/*
 
 Permet de savoir si il y a tant de ligne dans la file
    f : la file concerné
    i : le nombre de lignes voulu
    return : int de validation
 
 */

int there_is (file f, int i) {
    Chaine * bis = (Chaine *) f ;
    Maillon * cop = bis->tete ;
    int num ;
    for (num=0;num<i;num++) {
        if (cop==NULL){
		return 0 ;
	}
        else
            cop = cop->suivant ;
    }
    return 1 ;
}

/*
 
 Affichage de la File
    f : la File de lignes à afficher
    return : void
 
 */

void afficher (file f) {
    Chaine * cop ;
    Maillon * temp ;
    if (is_empty(f)) 
        printf("\n"); 
	else {
		cop = (Chaine *) f;
		temp = cop->tete ;
        while(temp!=NULL) {
            printf("%s",temp->ligne);
            temp = temp->suivant ;
        }
        printf("\n");
    }
}

/*
 
 Permet de vider la file et la memoire qu'elle utilise
    f : la file a vider
    return : void
 
 */

void vider (file f) {
    
    Chaine * cop = (Chaine *) f ;
    Maillon * temp = cop->tete ;
    while (temp!=NULL) {
        free(temp);
        temp = temp->suivant ;
    }
    
}


