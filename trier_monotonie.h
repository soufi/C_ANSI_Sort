/*
 *  trier_monotonie.h
 *  Trieur
 *
 *  Created by Soufiane boulealf on 07/10/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */


void couper (void * f, void * coupe1, void * coupe2, int const inverse);

void fusionner (void * coupe1, void * coupe2, void * result, int inverse, int no_repeat);

void sort (void * f, int inverse, int no_repeat);