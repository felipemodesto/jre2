/**
 * @brief main.c
 *
 * @date 29/09/2009
 *
 * @file
 * @version 1.0
 *
 *
 * @include
 */

/*Includes*/
#include <stdio.h>
#include <stdlib.h>
#include "class.h"
#include "class_reader.h"
#include "class_printer.h"
#include "search_functions.h"
#include "interpreter_structs.h"
#include "interpreter_routine.h"

/**
 * Função main
 * @argc numero de argumentos oriundos da entrada
 * @argv ponteiro para a lista de argumentos
 */
int main(int argc, char * argv[]){

	char *fileName = "Test2";
	
	/* Avaliação dos argumentos para passagem de outras coisas */
	if ( (argc == 2) ){
		fileName = argv[1];
	}

	start_interpreter(fileName, "main", "([Ljava/lang/String;)V");
	
	/* testes - Status: opstack funcionando, framestack funcionando, localvar funcionando */
	
	getchar();
	
	return(0);
}
