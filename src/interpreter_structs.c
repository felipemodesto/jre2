/*
 * interpreter_structs.c
 *
 *  Created on: 02/12/2009
 *
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>

#include "interpreter_structs.h"

/**
 * Inicializa a pilha de frames.
 */
t_frame_stack *frame_stack_init() {
	return NULL;
}

/**
 * Verifica se a pilha de frames estç fazia.
 * @param frame_stack pilha de frames
 */
int frame_stack_is_empty(t_frame_stack *frame_stack) {
	return frame_stack == NULL ? 1 :0;

}

/**
 * Realiza um push da pilha de frames.
 * @param frame_stack pilha de frames
 * @param frame frame a ser colocado na pilha
 */
void frame_stack_push(t_frame_stack **frame_stack, t_frame *frame) {
	t_frame_stack *p1;

	if((*frame_stack) == NULL) {
		(*frame_stack) = malloc(sizeof(t_frame_stack));
		(*frame_stack)->frame = frame;
		(*frame_stack)->next = NULL;
	} else {
		p1 = malloc(sizeof(t_frame_stack));
		p1->frame = frame;
		p1->next = (*frame_stack);
		(*frame_stack) = p1;
	}

}

/**
 *  Desempelha um frame da pilha de frames e retorna-o.
 *  @param frame_stack a pilha de frames.
 *
 *  @return frame retornado
 */
t_frame *frame_stack_pop(t_frame_stack **frame_stack) {
	t_frame *popped_frame;

	popped_frame = (*frame_stack)->frame;
	(*frame_stack) = (*frame_stack)->next;

	return popped_frame;
}

/**
 *  Inicializa a pilha de operandos.
 *
 */
t_opstack *opstack_frame_init() {
	return NULL;
}

/**
 * Verifica se a pilha de operandos esta vazia.
 * @param opstack a pilha de operandos
 *
 * @return 1 se estiver vazia, 0 caso contrario
 */
int opstack_is_empty(t_opstack *opstack) {
	return opstack == NULL ? 1 :0;
}


/**
 * Empilha um valor na pilha de operandos.
 *
 *
 * @param opstack a pilha de operandos
 * @param type o tipo do valor a ser passado ("I", "Z", "F", etc..)
 * @param data o valor a ser passado
 * No caso de uma referencia, passar sem o '&', no resto, usar o '&'
 * Para obter um objeto, fazer casting do tipo (t_object*)
 */
void opstack_push(t_opstack **opstack, char *type, void *data) {
	t_opstack *p1;

	if((*opstack) == NULL) {
		(*opstack) = malloc(sizeof(t_opstack));

		p1 = (*opstack);
		p1->next = NULL;
	} else {

		p1 = malloc(sizeof(t_opstack));
		p1->next = (*opstack);
		(*opstack) = p1;
	}

	if(type[0] == 'B') {
		p1->data.data_byte = *((char *)data);
	} else if(type[0] == 'C') {
		p1->data.data_char = *((unsigned char *)data);
	} else if(type[0] == 'D') {
		p1->data.data_double = *((double*)data);
	} else if(type[0] == 'F') {
		p1->data.data_float= *((float*)data);
	} else if(type[0] == 'I') {
		p1->data.data_int = *((int*)data);
	} else if(type[0] == 'J') {
		p1->data.data_long = *((long long*)data);
	} else if(type[0] == 'L') {
		p1->data.data_reference = data;
	} else if(type[0] == 'S') {
		p1->data.data_short = *((short*)data);
	} else if(type[0] == 'Z') {
		p1->data.data_boolean = *((char*)data);
	} else if(type[0] == '[') {
		p1->data.data_reference = data;
	} else if(type[0] == 'r') {
		p1->data.data_return_adress = ((char*)data);
	}


	p1->type = type;



}

/**
 * Empilha um valor na pilha de operandos, diretamente do valor "data"
 * da union "t_data_union"
 *
 * @param opstack a pilha de operandos
 * @param type o tipo do valor
 * @param data o valor a ser passado (na union data)
 */
void opstack_push_data(t_opstack **opstack, char *type, t_data_union data) {
	t_opstack *p1;

	if((*opstack) == NULL) {
		(*opstack) = malloc(sizeof(t_opstack));

		p1 = (*opstack);
		p1->next = NULL;
	} else {

		p1 = malloc(sizeof(t_opstack));
		p1->next = (*opstack);
		(*opstack) = p1;
	}

	p1->data = data;


	p1->type = type;


}

/**
 * Desempilha um valor da pilha de operandos.
 * @param opstack pilha de operandos
 *
 * @return uma structure contendo um elemento da pilha de operandos,
 * o que contem a union "data" e o tipo "type".
 */
t_opstack *opstack_pop(t_opstack **opstack) {
	t_opstack *popped_data;

	popped_data = (*opstack);
	if (popped_data == NULL){
		fprintf(stderr,"Erro em 'opstack_pop', pilha vazia.\n");
		exit(1);
	}
	(*opstack) = (*opstack)->next;

	popped_data->next = NULL;

	return popped_data;
}


/**
 * Transfere um valor da pilha de operandos para a lista de variaveis locais.
 * Utilizado em instrucoes do tipo "store" como "fstore", "istore", "astore", etc.
 *
 * @param opstack pilha de operandos
 * @param localvar lista de variaveis locais
 * @param index posicao da lista de variaveis locais onde sera inserido o valor
 *
 */
void transfer_opstack_to_localvar(t_opstack **opstack, t_local_variable_list **localvar, int index) {
	t_opstack *valor_pilha;
	char *type;
	valor_pilha = *opstack;
	opstack_pop(opstack);
	type = valor_pilha->type;
	if(type[0] == 'B') {
		(*localvar)[index].data.data_byte = valor_pilha->data.data_byte;
	} else if(type[0] == 'C') {
		(*localvar)[index].data.data_char = valor_pilha->data.data_char;
	} else if(type[0] == 'D') {
		(*localvar)[index].data.data_double = valor_pilha->data.data_double;
	} else if(type[0] == 'F') {
		(*localvar)[index].data.data_float= valor_pilha->data.data_float;
	} else if(type[0] == 'I') {
		(*localvar)[index].data.data_int = valor_pilha->data.data_int;
	} else if(type[0] == 'J') {
		(*localvar)[index].data.data_long = valor_pilha->data.data_long;
	} else if(type[0] == 'L') {
		(*localvar)[index].data.data_reference = valor_pilha->data.data_reference;
	} else if(type[0] == 'S') {
		(*localvar)[index].data.data_short = valor_pilha->data.data_short;
	} else if(type[0] == 'Z') {
		(*localvar)[index].data.data_boolean = valor_pilha->data.data_boolean;
	} else if(type[0] == '[') {
		(*localvar)[index].data.data_reference = valor_pilha->data.data_reference;
	} else if(type[0] == 'r') {
		(*localvar)[index].data.data_return_adress = valor_pilha->data.data_return_adress;
	}

	(*localvar)[index].data = valor_pilha->data;
	(*localvar)[index].type = type;
	(*localvar)[index].next = NULL;


}

/**
 * Transfere o valor das variçveis locais para a pilha de operandos.
 * Utilizado em muitas instrucoes do tipo "load", como "iload", "aload", etc.
 * @param localvar lista de variaveis locais
 * @param index posicao da lista de variaveis locais na qual o dado sera tirado
 * @param opstack pilha de operandos
 */
void transfer_localvar_to_opstack(t_local_variable_list **localvar, int index, t_opstack **opstack) {
	opstack_push_data(opstack, (*localvar)[index].type, (*localvar)[index].data);
}



/**
 * Inicia uma estrutura de array (que aqui e' tratada como lista)
 *
 * @param type tipo dos elementos
 * @param n numero de elementos
 *
 * @return referencia para a lista
 */
t_array_list *array_init_structure(char *type, int n) {
	t_array_list *array_list, *p1, *p2;
	int i;
	if(n > 0) {
		array_list = malloc(sizeof(t_array_list));
		array_list->type = type;
		array_list->next = NULL;
		p1 = array_list;
		for(i = 1; i < n; i++) {
			p2 = malloc(sizeof(t_array_list));
			p2->type = type;
			p2->next = NULL;
			p1->next = p2;
			p1 = p2;
		}
	} else {
		fprintf(stderr,"Erro no localvar_init_structure\n");
		exit(1);
	}

	return array_list;
}

/**
 * Obtem o valor de um array.
 * @param array referencia para o array
 * @param pos a posicao a ser obtida
 *
 * @return elemento de um array (como estrutura de array)
 */
t_array_list *array_get_value(t_array_list **array, int pos) {
	t_array_list *p1;
	int count;
	p1 = *array;

	for(count = 0; count < pos; count++){
		p1 = p1->next;	
	}
	
	return p1;
}

/**
 * Insere um elemento no array em uma determinada posicao.
 * @param array referencia para o array
 * @param pos posicao a ser inserido o elemento
 * @param data valor a ser inserido
 */
void array_add_value(t_array_list **array, int pos, char *type, void *data) {
	t_array_list *p1;
	int count;
	p1 = *array;

	for(count = 0; count < pos; count++ ) {
		p1 = p1->next;
	}

	if(type[0] == 'B') {
		p1->data.data_byte = *((char *)data);
	} else if(type[0] == 'C') {
		p1->data.data_char = *((unsigned char *)data);
	} else if(type[0] == 'D') {
		p1->data.data_double = *((double*)data);
	} else if(type[0] == 'F') {
		p1->data.data_float= *((float*)data);
	} else if(type[0] == 'I') {
		p1->data.data_int = *((int*)data);
	} else if(type[0] == 'J') {
		p1->data.data_long = *((long long*)data);
	} else if(type[0] == 'L') {
		p1->data.data_reference = data;
	} else if(type[0] == 'S') {
		p1->data.data_short = *((short*)data);
	} else if(type[0] == 'Z') {
		p1->data.data_boolean = *((char*)data);
	} else if(type[0] == '[') {
		p1->data.data_reference = data;
	} else if(type[0] == 'r') {
		p1->data.data_return_adress = ((char*)data);
	}

	p1->type = type;
	
}

/**
 * Conta os elementos do array.
 * @param array referencia para o array
 *
 * @return contagem de elementos
 */
int array_count(t_array_list *array) {
	t_array_list *p1;
	int count = 0;

	p1 = array;
	while(p1 != NULL) {
		count++;
		p1 = p1->next;
	}

	return count;
}
/**
 * Inicializa a lista de class_files.
 */
t_classfile_list  *classfile_list_init() {
	return NULL;
}

/**
 * Adiciona um elemento na lista.
 * @param classfile_list a lista de classes
 * @param classfile a class_file a ser adicionada
 * @param static_fields uma instancia do objeto contendo seus fields estaticos
 * @param class_path o nome da classe (e seu caminho)
 */
void classfile_list_add(t_classfile_list **classfile_list, t_class_file *classfile, t_object *static_fields, char *class_path) {
	t_classfile_list *p1, *p2;

	if((*classfile_list) == NULL) {
		(*classfile_list) = malloc(sizeof(t_classfile_list));
		p1 = (*classfile_list);
	} else {
		p2 = (*classfile_list);
		while(p2->next != NULL) {
			p2 = p2->next;
		}

		p1 = malloc(sizeof(t_classfile_list));
		p2->next = p1;
	}

	p1->next = NULL;
	p1->classfile = classfile;
	p1->static_fields = static_fields;
	p1->class_path = class_path;


}



/**
 * Aloca um array de um certo tipo, dimensões e tamanhos de cada uma das dimensoes.
 * @param type o tipo dos elementos do array
 * @param dimensions numero de dimensoes
 * @param tamamhos array com os tamanhos das dimensoes.
 */
t_array_list* allocate_array__(char* type, int dimensions, int *tamanhos) {
	t_array_list *arr, *p1;
	int i, *sub_tamanhos;


	if(dimensions == 1) {
		arr = array_init_structure(type, tamanhos[0]);
	} else {
		arr = array_init_structure("[", tamanhos[0]);

		sub_tamanhos = calloc(dimensions-1, sizeof(int));
		for(i= 1; i < dimensions; i++) {
			sub_tamanhos[i-1] = tamanhos[i];
		}
		for(p1 = arr, i=0; i< tamanhos[0]; i++, p1 = p1->next) {
			p1->data.data_reference = allocate_array__(type, dimensions-1, sub_tamanhos);
		}
	}


	return arr;

}

/**
 * Faz a mesma coisa que allocate_array__, mas usa va_args, ajudando a manipulacao.
 */
t_array_list* array_allocate(char *type, int dimensions, ...) {
	t_array_list *arr;
	int count, *tamanhos, *p1;
	va_list argptr;

	tamanhos = calloc(dimensions, sizeof(int));

	va_start(argptr, dimensions);

	if(dimensions == 0) {
		arr = NULL;
		return arr;
	}

	for(count = 0, p1 = tamanhos; count < dimensions; count++, p1++) {
		*p1 = va_arg(argptr, int);
	}

	arr = allocate_array__(type, dimensions, tamanhos);


	return arr;
}

/**
 * Conta os argumentos de um descritor de um metodo.
 * Utilizado nos invokes.
 * @param descritor o descritor de um metodo
 *
 * @return numero de argumentos
 */
int arguments_count(char *descriptor) {
	char *p1;
	int count;
	int add_counter;
	count = 0;

	add_counter = 0;

	p1 = descriptor;
	while(*p1 != '\0') {
		switch(*p1) {
		case 'B' :
			if(add_counter)
				count++;
			break;
		case 'C':
			if(add_counter)
				count++;
			break;
		case 'D':
			if(add_counter)
				count++;
			break;
		case 'F':
			if(add_counter)
				count++;
			break;
		case 'I':
			if(add_counter)
				count++;
			break;
		case 'J':
			if(add_counter)
				count++;
			break;
		case 'L':
			if(add_counter) {
				count++;
				add_counter = 0;
			}
			break;
		case 'S':
			if(add_counter)
				count++;
			break;
		case 'Z':
			if(add_counter)
				count++;
			break;
		case '[':
			break;
		case '(':
			add_counter = 1;
			break;
		case ')':
			add_counter = 0;
			break;
		case ';':
			add_counter = 1;
			break;

		default:
			break;
		}
		p1++;

	}

	return count;

}

/**
 * Obtem um field de um objeto.
 * @param object instancia do objeto
 * @param nomefield nome do field
 *
 * @return o field. retorna NULL se nao tiver achado o field.
 */
t_field* object_get_field(t_object *object, char *nomefield) {
	t_field *p1;
	int count, i;
	count = object->fields_count;


	for(i=0, p1 = object->fields; i<count; i++, p1++) {
		if(strcmp(p1->name, nomefield) == 0) {
			return p1;
		}
	}



	return NULL;
}

/**
 * Insere um elemento em uma field de um objeto.
 * @param objeto objeto a ter a field inserida
 * @param nomefield o nome do field
 * @param type o tipo do valor a ser inserido
 * @para data o valor
 *
 * @return codigo de erro (-1 se nao tiver achado o field)
 */
int object_set_field_data(t_object *object, char *nomefield, char *type, t_data_union data) {
	t_field *p1;
	int count, i;
	count = object->fields_count;

	for(i=0, p1 = object->fields; i < count; i++, p1++) {
		if(strcmp(p1->name, nomefield) == 0) {
			p1->type = type;
			if(type[0] == 'B') {
				p1->data.data_byte = data.data_byte;
			} else if(type[0] == 'C') {
				p1->data.data_char = data.data_char;
			} else if(type[0] == 'D') {
				p1->data.data_double = data.data_double;
			} else if(type[0] == 'F') {
				p1->data.data_float= data.data_float;
			} else if(type[0] == 'I') {
				p1->data.data_int = data.data_int;
			} else if(type[0] == 'J') {
				p1->data.data_long = data.data_long;
			} else if(type[0] == 'L') {
				p1->data.data_reference = data.data_reference;
			} else if(type[0] == 'S') {
				p1->data.data_short = data.data_short;
			} else if(type[0] == 'Z') {
				p1->data.data_boolean = data.data_boolean;
			} else if(type[0] == '[') {
				p1->data.data_reference = data.data_reference;
			} else if(type[0] == 'r') {
				p1->data.data_return_adress = data.data_return_adress;
			}

			return 1;
		}
	}



	return -1;
}

