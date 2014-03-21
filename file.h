
/*
 
 file.h
 
 Created by Simon Hubert on 05/10/12.
 Copyright (c) 2012 __MyCompanyName__. All rights reserved.
 
 */

#ifndef _File_h
#define _File_h

typedef struct {    
    enum { t_long_int , t_long_double , t_pointer, t_error, t_void
    } type ;
    union {
        long int val_long_int ;
        long double val_long_double ;
        void * val_pointer ;
    } value ;
} answer ;

extern const answer answer_void ;
extern const answer answer_error ;
extern answer answer_long_int ( long int ) ;
extern long int answer_get_long_int ( answer ) ;
extern answer answer_long_double ( long double ) ;
extern long double answer_get_long_double ( answer ) ;
extern answer answer_pointer ( void * ) ;
extern void * answer_get_pointer ( answer ) ;

#endif

typedef void * file ;

void * init () ;

int is_empty ( file f ) ;

int is_try ( file f, int inverse ) ;

int comparer_tete ( file f1 , file f2 ) ;

int comparer_tete_queue ( file f1 , file f2 ) ;

int enfiler ( char * s, file f ) ;

char * defiler ( file f ) ;

int transfert ( file f1 , file f2 ) ;

void afficher ( file f ) ;

void vider ( file f ) ;

