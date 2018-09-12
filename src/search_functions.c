/*
 * search_functions.c
 *
 *  Created on: 01/12/2009
 *
 */

#include <stdlib.h>
#include <string.h>

#include "search_functions.h"
#include "interpreter_basic.h"
#include "auxiliar_functions.h"

/**
 * Busca uma tag na constant pool
 * @param class estrutura criada a partir de um .class
 * @param n elemento da constantpool
 */
u1 find_tag_info(t_class_file *class, int n) {
	return (class->constant_pool + n - 1)->tag;
}

/**
 * Busca uma string utf8 na constant pool.
 * @param a struct em memoria da classe
 * @param n a posicao na constant pool
 *
 * @return string utf8
 */
char *find_utf8_info(t_class_file *class, int n) {
	int len;
	u1 *content;
	char *string, *ps;
	int i;


	len = (class->constant_pool + n - 1)->info.utf8_info.length;
	content = (class->constant_pool + n - 1)->info.utf8_info.bytes;

	string = calloc(len+1, sizeof(char));
	ps = string;

	for(i=0; i< len; i++, ps++, content++) {
		*ps = *content;
	}
	ps = '\0';

	return string;

}

/**
 * Busca uma string sobre a classe na constant pool.
 * @param a struct em memoria da classe
 * @param n a posicao na constant pool
 *
 * @return string sobre a classe
 */
char *find_class_info(t_class_file *class, int n) {
	int index;
	index = (class->constant_pool + n -1)->info.class_info.name_index;

	return find_utf8_info(class, index);
}

/**
 * Busca informacao do tipo name_and_type.
 * @param a struct em memoria da classe
 * @param n a posicao na constant pool
 *
 * @return struct com as informacoes.
 */
t_name_and_type_about *find_name_and_type_info(t_class_file *class, int n) {
	int index_name, index_type;
	t_name_and_type_about *name_and_type_about;
	name_and_type_about = malloc(sizeof(t_name_and_type_about));

	index_name = (class->constant_pool + n - 1)->info.nameandtype_info.name_index;
	index_type = (class->constant_pool + n - 1)->info.nameandtype_info.descriptor_index;
	name_and_type_about->name = find_utf8_info(class, index_name);
	name_and_type_about->type = find_utf8_info(class, index_type);

	return name_and_type_about;

}

/**
 * Procura informacao sobre field na constant pool.
 * @param a struct em memoria da classe
 * @param n a posicao na constant pool
 *
 * @return informacao sobre os fields
 */
t_field_about *find_field_info(t_class_file *class, int n) {
	int class_index, name_and_type_index;
	t_field_about *field_about;
	t_name_and_type_about *name_and_type_about;

	field_about = malloc(sizeof(t_field_about));

	class_index = (class->constant_pool + n  -1)->info.fieldref_info.class_index;
	field_about->className = find_class_info(class, class_index);

	name_and_type_index = (class->constant_pool + n - 1)->info.fieldref_info.name_and_type_index;
	name_and_type_about = find_name_and_type_info(class, name_and_type_index);
	field_about->fieldName = name_and_type_about->name;
	field_about->type = name_and_type_about->type;

	return field_about;

}

/**
 * Procura informacoes sobre os metodos.
 * @param a struct em memoria da classe
 * @param n a posicao na constant pool
 *
 * @return struct contendo informacoes sobre os metodos
 */
t_method_about *find_method_info(t_class_file *class, int n) {
	t_method_about *method_about;
	int class_index, name_and_type_index;
	t_name_and_type_about *name_and_type_about;

	method_about = malloc(sizeof(t_method_about));

	class_index = (class->constant_pool + n  -1)->info.fieldref_info.class_index;
	method_about->className = find_class_info(class, class_index);

	name_and_type_index = (class->constant_pool + n - 1)->info.fieldref_info.name_and_type_index;
	name_and_type_about = find_name_and_type_info(class, name_and_type_index);
	method_about->methodName = name_and_type_about->name;
	method_about->type = name_and_type_about->type;

	return method_about;


}

/**
 * Procura uma string na constant_pool.
 * @param a struct em memoria da classe
 * @param n a posicao na constant pool
 *
 * @return a string desejada
 */
char *find_string_info(t_class_file *class, int n) {
	int index;

	index = (class->constant_pool + n - 1)->info.string_info.string_index;
	return find_utf8_info(class, index);
}

u4 find_integer_info(t_class_file *class, int n) {
	u4 integer;

	integer = (class->constant_pool + n - 1)->info.integer_info.bytes;

	return integer;
}

/**
 * Procura um valor long (int de 64 bits) na constant_pool.
 * @param a struct em memoria da classe
 * @param n a posicao na constant pool
 *
 * @return o valor do long
 */
long long find_long_info(t_class_file *class, int n) {
	long long high, low;
	long long longg;

	high = (class->constant_pool + n - 1)->info.long_info.high_bytes;
	low = (class->constant_pool + n - 1)->info.long_info.low_bytes;


	longg = 0;

	longg = (high << sizeof(u4)*8) | low;

	return longg;
}

/**
 * Procura um valor de float na constant_pool.
 * @param a struct em memoria da classe
 * @param n a posicao na constant pool
 *
 * @return o valor do float
 */
float find_float_info(t_class_file *class, int n) {
	unsigned int *inteiro;
	inteiro = malloc(sizeof(int));

	*inteiro = (class->constant_pool + n - 1)->info.float_info.bytes;

	float *f;
	f = malloc(sizeof(float));

	memcpy(f, inteiro, sizeof(int));

	return *f;
}

/**
 * Procura um valor double na constant pool.
 * @param a struct em memoria da classe
 * @param n a posicao na constant pool
 *
 * @return o valor do double
 */
double find_double_info(t_class_file *class, int n) {
	unsigned long long *inteiro_high, *inteiro_low, *longg;
	inteiro_high = malloc(sizeof(long long));
	inteiro_low = malloc(sizeof(long long));
	longg = malloc(sizeof(long long));

	*inteiro_high = (class->constant_pool + n - 1)->info.double_info.high_bytes;
	*inteiro_low = (class->constant_pool + n - 1)->info.double_info.low_bytes;
	*longg = (*inteiro_high << sizeof(u4)*8) | *inteiro_low;

	double *d;

	d = malloc(sizeof(double));

	memcpy(d, longg, sizeof(long long));

	return *d;


}

/**
 * Procura um metodo pelo seu nome e descritor. Busca tambem o metodo
 * em suas superclasses (suporte a heranca de metodos)
 * @param a struct em memoria da classe
 * @param methodName nome do metodo
 * @param descriptor descritor do metodo
 * @param interpreter a variavel do interpretador
 *
 * @return o metodo e a classe a que pertence, em uma struct
 */
t_method_and_class* find_method_by_name(t_class_file *class, char *methodName, char *descriptor, t_interpreter *interpreter) {
	t_method_info *method_list;
	t_classfile_list *classfile_list, *p1;
	t_method_and_class *metclass;
	int count, i;

	metclass = malloc(sizeof(t_method_and_class));

	method_list = class->methods;
	count = class->methods_count;

	for(i = 0; i < count; i++, method_list++) {
		if(descriptor == NULL) {
			if(strcmp(methodName, (find_utf8_info(class, method_list->name_index))) == 0) {
				metclass->method_info = method_list;
				metclass->class_file = class;
				return metclass;
			}
		} else {


			if(strcmp(methodName, (find_utf8_info(class, method_list->name_index))) == 0 &&
					strcmp(descriptor, (find_utf8_info(class, method_list->descriptor_index))) == 0) {

				metclass->method_info = method_list;
				metclass->class_file = class;
				return metclass;
			}
		}



	}

	if(class->super_class != 0) {
		classfile_list = get_super_classes(class, interpreter);
		p1 = classfile_list;
		while(p1 != NULL) {
			method_list = p1->classfile->methods;
			count = p1->classfile->methods_count;
			for(i = 0; i < count; i++, method_list++) {
				if(descriptor == NULL) {
					if(strcmp(methodName, (find_utf8_info(p1->classfile, method_list->name_index))) == 0) {
						metclass->method_info = method_list;
						metclass->class_file = p1->classfile;
						return metclass;
					}
				} else {


					if(strcmp(methodName, (find_utf8_info(p1->classfile, method_list->name_index))) == 0 &&
							strcmp(descriptor, (find_utf8_info(p1->classfile, method_list->descriptor_index))) == 0) {

						metclass->method_info = method_list;
						metclass->class_file = p1->classfile;
						return metclass;
					}
				}



			}
			p1 = p1->next;
		}

	}
	return NULL;
}

/**
 * Procura um metodo pelo seu nome e descritor. Nao leva
 * em consideracao as superclasses.
 * @param a struct em memoria da classe
 * @param methodName nome do metodo
 * @param descriptor descritor do metodo
 * @param interpreter a variavel do interpretador
 *
 * @return o metodo e a classe a que pertence, em uma struct
 */
t_method_and_class* find_method_by_name_only_this_class(t_class_file *class, char *methodName, char *descriptor, t_interpreter *interpreter) {
	t_method_info *method_list;
	t_method_and_class *metclass;
	int count, i;

	metclass = malloc(sizeof(t_method_and_class));

	method_list = class->methods;
	count = class->methods_count;

	for(i = 0; i < count; i++, method_list++) {
		if(descriptor == NULL) {
			if(strcmp(methodName, (find_utf8_info(class, method_list->name_index))) == 0) {
				metclass->method_info = method_list;
				metclass->class_file = class;
				return metclass;
			}
		} else {


			if(strcmp(methodName, (find_utf8_info(class, method_list->name_index))) == 0 &&
					strcmp(descriptor, (find_utf8_info(class, method_list->descriptor_index))) == 0) {

				metclass->method_info = method_list;
				metclass->class_file = class;
				return metclass;
			}
		}



	}

	return NULL;
}

/**
 * Procura um atributo em um metodo pelo nome.
 * @param class estrutura da classe
 * @param method_info info da cp_info sobre o metodo
 * @param attName nome do atributo
 *
 * @return info sobre o atributo
 */
t_attribute_info* find_method_attribute_by_name(t_class_file *class, t_method_info *method, char *attName) {
	t_attribute_info *p;

	int i, count;
	p = method->attributes;
	count = method->attributes_count;

	for(i=0; i< count; i++, p++) {
		if(strcmp(find_utf8_info(class, p->attribute_name_index), attName) == 0) {
			return p;
		}
	}

	return NULL;
}

/**
 * Procura fields de um objeto pelo nome. Em caso de erro retorna NULL.
 * @param class classe a ser procurada
 * @param fieldName nome do field
 *
 * @return info sobre o field
 */
t_field_info *find_field_by_name(t_class_file *class, char *fieldName) {
	t_field_info *field_list;
	int count, i;

	field_list = class->fields;
	count = class->fields_count;

	for(i = 0; i < count; i++, field_list++) {
		if(strcmp(fieldName, (find_field_info(class, field_list->name_index))->fieldName) == 0) {
			return field_list;
		}
	}

	return NULL;
}




