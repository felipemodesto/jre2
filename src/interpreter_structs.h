/*
 * interpreter_structs.h
 *
 *  Created on: 01/12/2009
 *
 */

#ifndef INTERPRETER_STRUCTS_H_
#define INTERPRETER_STRUCTS_H_

#include "class.h"

typedef union data_union {
	char data_byte;
	unsigned char data_char;
	double data_double;
	float data_float;
	int data_int;
	long long data_long;
	short data_short;
	char data_boolean;
	void *data_reference;
	char *data_return_adress;

} t_data_union;

typedef struct array {
	int count;
	char *type;
	void **arr;


} t_array;

/* ====== VARIAVEIS DA INSTANCIA DO OBJETO ====== */
typedef struct field_list {
	char *name;
	char *type;
	t_data_union data;
} t_field;


/**
 * Instancia do objeto. Contém seus fields.
 */
typedef struct object {
	char *classPath;
	int fields_count;
	t_field *fields;

} t_object;



/**
 * Pilha de operandos (também serve para a lista de variaveis
 * locais)
 */
typedef struct opstack {
	char *type;
	t_data_union data;
	struct opstack *next;
} t_opstack,  t_local_variable_list, t_array_list;


/**
 * Struct para o metodo. Contem o seu PC (program counter),
 * o max_pc (qual o maior valor do PC), sua pilha de operandos
 * e sua lista de variaveis locais.
 */
typedef struct frame {
	u1 *pc;
	u1 *pc_inicial;
	int max_pc;
	int pc_address;
	t_class_file *class_file;
	t_opstack *opstack;
	t_local_variable_list *local_variables;

} t_frame;


/**
 * Pilha de metodos (para chamadas de invokespecial e
 * invokedinamic)
 */
typedef struct frame_stack {
	t_frame *frame;
	struct frame_stack *next;

} t_frame_stack;

typedef struct classfile_list {
	char *class_path;
	t_class_file *classfile;
	t_object *static_fields;
	struct classfile_list *next;

} t_classfile_list;


/**
 * Struct do interpretador. Possui o metodo corrente
 * e a pilha de metodos.
 */
typedef struct interpreter {
	t_frame *current_frame;
	t_frame_stack *frame_stack;
	t_classfile_list *classfile_list;

} t_interpreter;

t_frame_stack *frame_stack_init();
int frame_stack_is_empty(t_frame_stack *frame_stack);
void frame_stack_push(t_frame_stack **frame_stack, t_frame *frame);
t_frame *frame_stack_pop(t_frame_stack **frame_stack);

t_opstack *opstack_frame_init();
int opstack_is_empty(t_opstack *opstack);
void opstack_push(t_opstack **opstack, char *type, void *data);
t_opstack *opstack_pop(t_opstack **opstack);

/*
t_local_variable_list *localvar_init();
void localvar_add(t_local_variable_list **local_variable_list, void *data, char *type);
t_local_variable_list* localvar_find(t_local_variable_list *local_variable_list, int index);
*/

t_classfile_list  *classfile_list_init();
void classfile_list_add(t_classfile_list **classfile_list,t_class_file *classfile, t_object *static_fields, char *class_path);

void transfer_opstack_to_localvar(t_opstack **opstack, t_local_variable_list **localvar, int index);
void transfer_localvar_to_opstack(t_local_variable_list **localvar, int index, t_opstack **opstack);

void opstack_push_data(t_opstack **opstack, char *type, t_data_union data);

t_array_list* array_allocate(char *type, int dimensions, ...);
t_array_list *array_get_value(t_array_list **array, int pos);
void array_add_value(t_array_list **array, int pos, char *type, void *data);
int array_count(t_array_list *array);
int arguments_count(char *descriptor);

t_array_list* allocate_array__(char* type, int dimensions, int *tamanhos);
int object_set_field_data(t_object *object, char *nomefield, char *type, t_data_union data);
t_field* object_get_field(t_object *object, char *nomefield);

#endif /* INTERPRETER_STRUCTS_H_ */
