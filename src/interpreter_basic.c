/**
 * @brief interpreter_basic.c
 *
 * @version 1.0
 *
 * @date 29/09/2009
 *
 **/

#include <string.h>
#include <stdlib.h>

#include "interpreter_basic.h"
#include "interpreter_routine.h"
#include "search_functions.h"
#include "class_reader.h"
#include "interpreter_structs.h"

/**
 * Função de jump. Função responsçvel por desviar o contexto do interpretador para outro método determinado.
 *
 * Essa função irç desviar o contexto do interpretador para outro método. Para isso, ele cria um novo frame,
 * determina seus valores com base na classPath e methodName especificados, passa os argumentos da pilha
 * de operandos do frame atual para as variçveis locais do novo frame, empilha o frame atual e coloca o frame
 * novo como o novo frame. A partir daí retorna e continua a interpretação conforme jç ocorria.
 * Caso não tenha nenhum frame na pilha de frames, este é o primeiro método a ser executado pelo interpretador.
 *
 * @param interpreter a variçvel do interpretador
 * @param classPath o caminho da classe
 * @param methodName  nome do metodo
 * @param descriptor o descritor do método
 * @param n_arguments o número de parâmetros do método
 *
 * @return void
 *
 */
void jump(t_interpreter *interpreter, char *classPath, char *methodName, char *descriptor, int n_arguments) {
	t_class_file *class_file;
	t_method_and_class *metclass;
	t_frame *frame_novo;
	int i;
	u2 mask = 0x0100;

	class_file = leitura_class_file(interpreter, classPath);
	metclass = find_method_by_name(class_file, methodName, descriptor, interpreter);
	if((metclass->method_info->acess_flags & mask) == 0x0100) {
		printf("Metodos nativos nao suportados\n");
		exit(1);
	}
	frame_novo = malloc(sizeof(t_frame));
	frame_novo->opstack = NULL;
	frame_novo->class_file = metclass->class_file;
	frame_novo->pc_address = 0;

	frame_novo->pc = find_method_attribute_by_name(metclass->class_file, metclass->method_info, "Code")->_info.code.code;
	frame_novo->pc_inicial = frame_novo->pc;
	frame_novo->local_variables = calloc(find_method_attribute_by_name(metclass->class_file, metclass->method_info, "Code")->_info.code.max_locals, sizeof(t_local_variable_list));


	frame_stack_push(&(interpreter->frame_stack), interpreter->current_frame);
	if(interpreter->current_frame != NULL) {

		for(i=(n_arguments-1); i!= -1; i--) {
			transfer_opstack_to_localvar(&(interpreter->current_frame->opstack),&(frame_novo->local_variables), i);
		}
	}

	interpreter->current_frame = frame_novo;


}

/**
 * Jumpback faz o contrçrio do jump - ele retorna o interpretador para o frame que estç no topo da pilha de frames, ou seja,
 * o frame anterior.
 *
 * A função jumpback tem como objetivo retornar o interpretador para o frame que estç no topo da pilha de frames, além de
 * passar a variçvel de retorno para o frame do topo da pilha, se houver.
 *
 * @param interpreter a variçvel do interpretador
 * @param n_return o número de retorno. Pode ser 0 ou 1 (ainda que a função seja genérica e aceite n retornos)
 */
int jumpback(t_interpreter *interpreter, int n_return) {
	int i;
	t_opstack *opstack_value;
	t_frame *frame_anterior;
	frame_anterior = interpreter->current_frame;
	if(interpreter->frame_stack != NULL) {
		interpreter->current_frame = frame_stack_pop(&(interpreter->frame_stack));
		if(interpreter->current_frame == NULL) {
			return -1;
		}
		for(i=0; i< n_return; i++) {
			opstack_value = opstack_pop((&frame_anterior->opstack));
			opstack_push_data(&(interpreter->current_frame->opstack), opstack_value->type, opstack_value->data);
		}

		return 0;
	} else {
		return -1;
	}




}

/**
 * Realiza a leitura do arquivo .class, realizando algumas verificações e ativando seus métodos <clinit> para chamada
 * de construção de atributos estçticos.
 *
 * leitura_class_file verifica na lista de classes se a leitura do .class jç foi feita. Caso positivo, obtém a estrutura
 * do arquivo, caso contrçrio lê o arquivo *.class e armazena na lista. Também cria um novo interpretador com a mesma
 * lista de class_files com o objetivo de inicializar o objeto do .class contendo os fields estçticos da classe,
 * chamando o método <clinit>.
 *
 * @param interpreter a variçvel do interpretador
 * @param class_path o caminho da classe
 */
t_class_file *leitura_class_file(t_interpreter *interpreter, char *class_path) {
	t_classfile_list  *p1;
	t_class_file *class_file;
	char *file_path;
	t_object *object_statics;
	t_interpreter *new_interpreter;
	t_method_and_class *metclass;
	t_method_about *method_about; /* TODO: Variavel nunca usada */
	char *method_name, *method_descriptor;
	int tamanho_class_path, tamanho_arquivo, i, j;

	p1 = interpreter->classfile_list;
	while(p1 != NULL) {
		if(strcmp(p1->class_path, class_path) ==0) {
			return p1->classfile;
		}
		p1 = p1->next;
	}

	tamanho_class_path = strlen(class_path);
	tamanho_arquivo = tamanho_class_path + 7;
	file_path = calloc(tamanho_arquivo, sizeof(char));

	for(i=0, j=0; i < tamanho_class_path; i++, j++) {
		file_path[j] = class_path[i];
	}
	if (!strstr(file_path,".class"))
		strcat(file_path, ".class");
	class_file = read_dot_class(file_path);

	/* TODO: substituir o valor NULL abaixo pelo objeto static instanciado */
	object_statics = instanciate_object(class_file, interpreter);
	classfile_list_add(&(interpreter->classfile_list), class_file, object_statics, class_path);

	/*interpreter->classfile_list = classfile_list; */

	new_interpreter = malloc(sizeof(t_interpreter));

	new_interpreter->classfile_list = interpreter->classfile_list;
	new_interpreter->frame_stack = NULL;
	new_interpreter->current_frame = NULL;

	if((metclass = find_method_by_name_only_this_class(class_file, "<clinit>", "()V", new_interpreter)) != NULL) {
		method_name = find_utf8_info(class_file, metclass->method_info->name_index);
		method_descriptor = find_utf8_info(class_file, metclass->method_info->descriptor_index);

		if(!(strcmp(class_path, "java/lang/Object") == 0) &&
				!(strcmp(class_path, "Object") == 0) &&
				!(strcmp(class_path, "java/lang/Class") == 0)&&
				!(strcmp(class_path, "Class") == 0) &&
				!(strcmp(class_path, "java/lang/Long") == 0)&&
				!(strcmp(class_path, "Long") == 0) &&
				!(strcmp(class_path, "java/lang/String") == 0)&&
				!(strcmp(class_path, "String") == 0)) {
			jump(new_interpreter, class_path, method_name, method_descriptor, 0);
			execute_iteration(new_interpreter);
		}

	}


	return class_file;
}


/**
 * Obtem um array de todas as superclasses da hierarquia de uma classe
 * @param class_file a classe
 * @param interpreter o interpretador
 *
 * @return a lista com todas as superclasses da hierarquia
 */
t_classfile_list *get_super_classes(t_class_file *class_file, t_interpreter *interpreter) {
	t_class_file *p1, *pant;
	t_classfile_list *superclasses;
	int count;

	count = 0;
	superclasses = NULL;
	p1 = class_file;
	while(p1->super_class != 0) {
		p1 = leitura_class_file(interpreter, find_class_info(p1, p1->super_class));
		count++;
	}

	if(count > 0) {
		superclasses = classfile_list_init();
		p1 = class_file;
		while(p1->super_class != 0) {
			pant = p1;
			p1 = leitura_class_file(interpreter, find_class_info(p1, p1->super_class));
			classfile_list_add(&superclasses, p1, NULL, find_class_info(pant, pant->super_class));

		}
	}


	return superclasses;
}

/**
 * Instancia um objeto.
 *
 * instanciate_object instancia um objeto de uma determinada classe, liberando espaço para todos
 * os fields da classe e das superclasse, exceto os fields estçticos das superclasses.
 * @param class_file a estrutura em memória do .class
 * @param interpreter a variçvel do interpretador
 */
t_object *instanciate_object(t_class_file *class_file, t_interpreter *interpreter) {
	t_object *new_object;
	t_classfile_list *superclasses, *p2;
	u2 mask = 0x0008;

	int count_fields, i;

	count_fields = class_file->fields_count;

	new_object = malloc(sizeof(t_object));

	/* verifica superclasses e soma todos os atributos delas no contador */
	superclasses = get_super_classes(class_file, interpreter);
	if(superclasses != NULL) {
		p2 = superclasses;
		while(p2 != NULL) {
			count_fields += p2->classfile->fields_count;
			p2 = p2->next;
		}
	}

	new_object->fields_count = count_fields;


	new_object->fields = calloc(count_fields, sizeof(t_field));

	new_object->classPath = find_class_info(class_file, class_file->this_class);

	/* adicionando os fields da classe */
	t_field *pfield;
	t_field_info *pfield_info;

	for(i=0, pfield = new_object->fields,
			pfield_info = class_file->fields;
			i<class_file->fields_count;
			i++, pfield++, pfield_info++) {
		pfield->name = find_utf8_info(class_file, pfield_info->name_index);
		pfield->type = find_utf8_info(class_file, pfield_info->descriptor_index);

	}


	/* verifica as superclasses e adiciona seus atributos */
	if(superclasses != NULL) {
		p2 = superclasses;
		while(p2 != NULL) {
			for(i=0, pfield_info = p2->classfile->fields;
					i<p2->classfile->fields_count; i++, pfield_info++) {
				if((pfield_info->access_flags & mask) != 8) {
					pfield->name = find_utf8_info(p2->classfile, pfield_info->name_index);
					pfield->type = find_utf8_info(p2->classfile, pfield_info->descriptor_index);
					pfield++;
				} else {
					new_object->fields_count--;
				}

			}
			p2 = p2->next;
		}
	}


	return new_object;
}
