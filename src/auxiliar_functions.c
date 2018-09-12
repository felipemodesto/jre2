/*
 * auxiliar_class_functions.c
 *
 *  Created on: 05/11/2009
 *
 */

#include "auxiliar_functions.h"

/**
 * Convers„o para little endian u2
 * @i inteiro a ser invertido
 *
 * @return valor invetido
 */
u2 convert_u2_little_ending(u2 i) {
	return ((i>>8)&0xff)+((i << 8)&0xff00);
}

/**
 * Convers„o para little endian u4
 * @i inteiro a ser invertido
 *
 * @return valor invetido
 */
u4 convert_u4_little_ending(u4 i) {
	return((i&0xff)<<24)+((i&0xff00)<<8)+((i&0xff0000)>>8)+((i>>24)&0xff);
}

/**
 * leitura de elementos do arquivo fazendo conversıes para littleEndian
 *
 * @variable variavel que recebera os valores lidos
 * @sizeOfVariable tamanho da variavel a ser lida
 * @numberOfVariables numero de items a serem lidos
 * @fPtr ponteiro para o arquivo
 *
 * @return retorna valores lidos e invertidos
 */
int freadLE(void * variable, size_t sizeOfVariable, size_t numberOfVariables, FILE *fPtr){
	int retorno;											/* variavel de retorno */
	int i;													/* counter */
	/*leitura do arquivo*/
	retorno = fread(variable, sizeOfVariable, numberOfVariables, fPtr);
	switch(sizeOfVariable){
	case (sizeof(u1)):
		/*Nada È feito, pois nao alteramos a ordem de um byte*/
		break;
	case (sizeof(u2)):{
			u2 *p1 = variable;
			/* Loop de Invers„o */
			for (i = 0; i < numberOfVariables ; i++, p1++){
				*p1 = convert_u2_little_ending(*p1);
			}
		}
		break;
	case (sizeof(u4)):{
			u4 *p1 = variable;
			/* Loop de Invers„o */
			for (i = 0; i < numberOfVariables ; i++, p1++){
				*p1 = convert_u4_little_ending(*p1);
			}
		}
		break;
	default:
		/*Para tipos de dados desconhecidos, n„o faz nada*/
		break;
	}
	return(retorno);
}
