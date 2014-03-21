/*
 *  trier_monotonie.c
 *  Trieur
 *
 *  Created by Soufiane Boulealf on 07/10/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include <string.h>
#include <stdio.h> 
#include <stdlib.h>
#include "file.h"
#include "trier_monotonie.h"


#define CHAR_MAX 256

#define EG_ZERO(adr) \
		if(adr == NULL){ \
			printf("\n ***** Erreur ! : Problème d'allocation de mémoire. ******\nProgramme Quite.\n");\
			exit(0);}

#define ECHEC(x,message) \
		if(x == 0){ \
			printf("%s ", message);\
			exit(0);}


/* ce fichier contiendra toutes les fonctions nécessaire au tri d'une file par la méthode de tri fusion */

/* commençant par le sous prog qui coupe une file en deux en fonction des monotonies existantes.
 param : - la file actuelle 
		 - coupe1 : la premiere coupe
		 - coupe2 : la deuxieme coupe 
		 - inverse : pour reperer les monotonie en cas inverse
 return : un entier qui confirme si le fonctionnement s'est bien déroulé
 */
void couper (file f, file coupe1, file coupe2, int const inverse){
	int code_retour; /* le code de retour des fonctions*/
	
	/*si la file est vide on a fini*/
	if(!is_empty(f)){
		/*si les deux coupe sont vide, dans ce cas la, on vient de commencer
		 on defile directement dans une des file a priorie la coupe1 dans notre cas*/
		if(is_empty(coupe1) && is_empty(coupe2)){
			
			code_retour = transfert (f, coupe1);
			ECHEC(code_retour, "\nERREUR du transfert !\n");
			couper(f, coupe1, coupe2, inverse);
		}
		/*sinon compare la tete de la file avec l'element de la coupe1 si c'est superieur ou non pour voir si on
		 place le prochain element apres la coupe1 ou non
		 
		 NB : on alterne les deux parametres quand on trouve une monotonie*/
		else {
			if(inverse)
				code_retour = comparer_tete_queue(f, coupe1)*(-1);
			else
				code_retour = comparer_tete_queue(f, coupe1);
			
			if(code_retour >= 0){
				/*défiler f et enfiler dans "file1" */
				code_retour = transfert(f, coupe1);
				ECHEC(code_retour, "\nERREUR (trier_monotonie => coupe)  transfert  !\n");
				couper(f, coupe1, coupe2, inverse);
				
			}else {
				code_retour = transfert(f, coupe2);
				ECHEC(code_retour, "\nERREUR (trier_monotonie => coupe)  transfert  !\n");
				couper(f, coupe2, coupe1, inverse);
			}
		}
	}
	
}


/*
 fusionne deux Files trié en une seul File trié 
 Le principe et simple : on compare les deux tete de file, on défile et enfile dans la file de résultat le type le plus petit
 pour pouvoir avoir une File croissante
param :
	- coupe1, coupe2 : les deux file qu'il faudrat fusionner
	- result : le resultat de la fusion
	- inverse : si ce param est à 1 on inverse l'ordre de tri
	- no_repeat : si ce param est à 1 on supprime les occurences.
 */
void fusionner (file coupe1, file coupe2, file result, int inverse, int no_repeat){
	void * pointeur;
	int code_retour; /*pour stocker le code de retour des fonctions*/
	
	while (!is_empty(coupe1) && !is_empty(coupe2)) {
		/*
		 on compare la les deux tetes des deux liste a fusionner pour pouvoir trier
		 en fonction du prametre d'ordre de tri on regarde si on fourni un resultat direct ou inverse
		 */
		if(inverse)
			code_retour = comparer_tete(coupe1, coupe2) * (-1);
		else 
			code_retour = comparer_tete(coupe1, coupe2);
		
		/*si tete de coup1 < tete de coupe2*/
		if(code_retour <= 0){
			if(no_repeat && !is_empty(result)){
				if( comparer_tete_queue(coupe1, result) == 0)
					free(defiler(coupe1));
				else 
					code_retour = transfert(coupe1, result);
			}
			else 
				code_retour = transfert(coupe1, result);
		}
		/*si tete de coup1 > tete de coupe2*/
		else{
			if(no_repeat && !is_empty(result)){
				if(comparer_tete_queue(coupe2,result) == 0)
					free(defiler(coupe2));
				else 
					code_retour = transfert(coupe2, result);
			}
			else
				code_retour = transfert(coupe2, result);
		}
		ECHEC(code_retour, "\nERREUR lors du transfert, impossible de continuer l'operation.\n");
	}
	
	/*si l'une des files est vide on sort de la boucle, sauf qu'il ne faut pas oublier de vérifier l'autre !
	 et donc vider le reste dans la file de resultat, et puisque les files sont supposés trié, on ne compare et pas, ou vide 
	 directement !
	 */
	if(!is_empty(coupe1))
		pointeur = coupe1;
	else if(! is_empty(coupe2))
		pointeur = coupe2;
	
	while (!is_empty(pointeur)) {
		if (no_repeat && !is_empty(result)) {
			if (comparer_tete_queue(pointeur, result) == 0)
				free(defiler(pointeur));
			else {
				code_retour = transfert(pointeur, result);
				ECHEC(code_retour, "\nERREUR lors du transfert, impossible de continuer l'operation.\n");
			}
		}else {
			code_retour = transfert(pointeur, result);
			ECHEC(code_retour, "\nERREUR lors du transfert, impossible de continuer l'operation.\n");
		}
	}
}

/*
 le sous prog qui tri la file en utilisant les sous prog définit plus haut
 param : 
	- f : la file qu'il faudrat trier
	- inverse : si ce parametre est egale à 1 on trie dans l'ordre inverse, donc dans l'ordre décroissant
	- no_repeat : si ce parametre est egale à 1 on supprime les occurences.
 */
void sort  (file f, int inverse, int no_repeat){

	file coupe1;
	file coupe2;

	if(!is_empty(f))
		if(! is_try(f, inverse)){
		
			coupe1 = init();
			coupe2 = init();
			/*si on arrive pas à loué de la mémoire pour nos files de coupes, on quite le programme avec une erreur */
			EG_ZERO(coupe1);
			EG_ZERO(coupe2);
			
			/*on coupe la file en deux, ensuite on fusionne :) */
			couper(f, coupe1, coupe2, inverse);
			
			fusionner(coupe1, coupe2, f, inverse, no_repeat);
			
			free(coupe1); /*on libère la mémoire prise par la coupe1*/
			free(coupe2); /*meme chose coupe2*/
			sort (f, inverse, no_repeat);
		}
}