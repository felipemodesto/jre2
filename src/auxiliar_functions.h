/*
 * auxiliar_functions.h
 *
 *  Created on: 05/11/2009
 *
 */

#ifndef AUXILIAR_FUNCTIONS_H_
#define AUXILIAR_FUNCTIONS_H_

#include "class.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

t_cp_info* get_cp_info(t_class_file *class_file,int position);

void correct_class_file(t_class_file *class_file);

u2 convert_u2_little_ending(u2 i);
u4 convert_u4_little_ending(u4 i);
int freadLE(void * variable, size_t sizeOfVariable, size_t numberOfVariables, FILE *fPtr);

#endif /* AUXILIAR_FUNCTIONS_H_ */
