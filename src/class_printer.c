/**
 * @brief class_printer.c
 *
 * @version 1.0
 * 
 * @date 29/09/2009
 *
 **/

#include "class_printer.h"
#include "search_functions.h"

/* ProtÛtipos */
void print_attribute_info (t_attribute_info *attribute_info, u2 count, t_class_file *class_file);

/**
 * Impressão campo info de um attribute_info do tipo ConstantValue
 * @info Ponteiro para o attribute_info a ser impresso
 *
 */
void print_constantvalue_attribute(u1 *info, t_class_file *class_file){
	t_constantvalue_attribute *pConstantvalue_attribute;	/*Ponteiro de deslocamento dentro da estrutura info */
	pConstantvalue_attribute = (void *)info;							/*Passando o ponteiro */

	/* Imprimindo os elementos do atributo */
	printf("   >>>>access_flags: %d\n",pConstantvalue_attribute->access_flags);
	printf("   >>>>name_index: %d\n",pConstantvalue_attribute->name_index);
	printf("   >>>>descriptor_index: %d\n",pConstantvalue_attribute->descriptor_index);
	printf("   >>>>attributes_count: %d\n",pConstantvalue_attribute->attributes_count);
	printf("   >>>>attributes:\n");
}

/**
 * Impressão do codigo de um attribute_info do tipo codigo
 * @info Ponteiro para o conteudo de codigo a ser impresso
 *
 */
void print_code(t_info_code code, t_class_file *class_file) {
	int i;
	char *p;
	printf(" >>attribute_name_index: %d\n", code.attribute_name_index);
	printf(" >>max_stack: %d\n", code.max_stack);
	printf(" >>max_locals: %d\n", code.max_locals);
	printf(" >>code_length: %d\n", code.code_length);
	printf(" >>code: ");

	p = code.code;
	for(i=0; i<code.code_length; i++, p++) {
		printf("%c", *p);
	}
	printf("\n");
	printf(" >> exception table.. nao precisa.\n");
	printf(" >> attributes_count: %d\n", code.attributes_count);
	print_attribute_info(code.attributes, code.attributes_count, class_file);
}

/**
 * Impress„o dos atributos de um field_info
 * @attribute_info Ponteiro para o attribute_info a ser impresso
 * @count numero de elementos attribute_info a serem impressos
 * 
 */
void print_attribute_info (t_attribute_info *attribute_info, u2 count, t_class_file *class_file){
	t_attribute_info *pAttribute;
	char *name_index;

	int i;												/* Contador */
	pAttribute = attribute_info;
	for( i = 0; i < count ; i++, pAttribute++ ){
		name_index = find_utf8_info(class_file, pAttribute->attribute_name_index);
		printf(" >>Tipo: %s\n", name_index);


		if(strcmp(name_index, "ConstantValue") == 0) {
			printf(" >> Index: %d\n", pAttribute->_info.constant_value.attribute_name_index);


		} else if(strcmp(name_index, "Code") == 0) {
			print_code(pAttribute->_info.code, class_file);


		} else if(strcmp(name_index, "Exceptions") == 0) {


		} else if(strcmp(name_index, "InnerClasses") == 0) {


		} else if(strcmp(name_index, "Synthetic") == 0) {


		} else if(strcmp(name_index, "SourceFile") == 0) {
			printf(" >> Index: %d\n", pAttribute->_info.sourcefile.sourcefile_index);


		} else if(strcmp(name_index, "LineNumberTable") == 0) {


		} else if(strcmp(name_index, "LocalVariableTable") == 0) {


		} else if(strcmp(name_index, "Deprecated") == 0) {


		} else if(strcmp(name_index, "Signature") == 0) {
			printf(" >> Index: %d\n", pAttribute->_info.signature.signature_index);
		}

	}
}

/**
 * Impress„o dos atributos de um field_info
 * @field_info Ponteiro para o field_info a ser impresso
 * @count numero de elementos field_info a serem impressos
 * 
 */
void print_field_info (t_field_info *field_info, u2 count, t_class_file *class_file){
	t_field_info *pField;								/*Ponteiro de deslocamento */
	/*loop de impressão*/
	int i;												/* Contador */
	printf(" >FIELD INFO\n");
	for( i = 0; i < count ; i++ ){
		printf(" >element number: %d\n", i);
		pField = &field_info[i];
		printf(" >>field_flags: 0x%x\n",pField->access_flags);
		printf(" >>field_name_index: %d\n",pField->name_index);
		printf(" >>field_descriptor_index: %d\n",pField->descriptor_index);
		printf(" >>field_attribute_count: %d\n",pField->attributes_count);
		print_attribute_info(pField->attributes, pField->attributes_count, class_file);
	}
}

/**
 * Impressao do cp_info
 * @cp_info Ponteiro para o cp_info a ser impresso
 * @count numero de elementos cp_info a serem impressos
 *
 */
void print_cp_info(t_cp_info *constant_pool, u2 count, t_class_file *class_file){
	t_cp_info *p1;
	int i, k;
	printf(">CONSTANT POOL INFO\n");
	/*printf(" >>count: %d\n", count); */
	p1 = constant_pool;
	/* A constant pool começa com o valor 1 e nao 0 */
	for(i = 0; i < count - 1; i++, p1++) {
		printf(" >element number: %d\n", i+1);
		printf(" >>tag: %d\n",p1->tag);
		switch (p1->tag) {
			case 7:
				printf(" >>name_index: %d\n",p1->info.class_info.name_index);
				break;
			case 9:
				printf(" >>class_index: %d\n",p1->info.fieldref_info.class_index);
				printf(" >>name_and_type_index: %d\n",p1->info.fieldref_info.name_and_type_index);
				break;
			case 10:
				printf(" >>class_index: %d\n",p1->info.methodref_info.class_index);
				printf(" >>name_and_type_index: %d\n",p1->info.methodref_info.name_and_type_index);
				break;
			case 11:
				printf(" >>class_index: %d\n",p1->info.interfacemethod_info.class_index);
				printf(" >>name_and_type_index: %d\n",p1->info.interfacemethod_info.name_and_type_index);
				break;
			case 8:
				printf(" >>string_index: %d\n",p1->info.string_info.string_index);
				break;
			case 3:
				printf(" >>bytes: %d\n",p1->info.integer_info.bytes);
				break;
			case 4:
				printf(" >>float_info: %d\n",p1->info.float_info.bytes);
				break;
			case 5:
				printf(" >>high_bytes: %d\n",p1->info.long_info.high_bytes);
				printf(" >>low_bytes: %d\n",p1->info.long_info.low_bytes);
				break;
			case 6:
				printf(" >>high_bytes: %d\n",p1->info.double_info.high_bytes);
				printf(" >>low_bytes: %d\n",p1->info.double_info.low_bytes);
				break;
			case 12:
				printf(" >>names_index: %d\n",p1->info.nameandtype_info.name_index);
				printf(" >>descriptor_index: %d\n",p1->info.nameandtype_info.descriptor_index);
				break;
			case 1:
				printf(" >>utf8_info_length: %d\n",p1->info.utf8_info.length);
				printf(" >>utf8_info: ");
				for(k=0; k< p1->info.utf8_info.length; k++) {
					printf("%c",p1->info.utf8_info.bytes[k]);
				}
				printf("\n");

				break;
		}


	}
}

/**
 * Impressao do method_info
 * @method_info Ponteiro para o method_info a ser impresso
 * @count numero de elementos method_info a serem impressos
 *
 */
void print_method_info(t_method_info *method_info, u2 count, t_class_file *class_file){
	t_method_info *p1;					/*Ponteiro de deslocamento */
	int i;								/*Contador do loop */
	printf(" >METHOD INFO\n");
	p1 = method_info;
	/*Loop de impres‚Äûo dos elementos do metodo*/
	for( i = 0 ; i < count ; i++ , p1++ ){
		printf(" >element number: %d\n", i + 1);
		printf(" >>access_flag: 0x%x\n", p1->acess_flags);
		printf(" >>name_index: %d\n", p1->name_index);
		printf(" >>descriptor_index: %d\n", p1->descriptor_index);
		printf(" >>attributes_count: %d\n", p1->attributes_count);
		print_attribute_info(p1->attributes, p1->attributes_count, class_file);
	}
}

/**
 * Impressao dos atributos de um class_file
 * @class_file Ponteiro para o class_file a ser impresso
 *
 */
void print_class_file(t_class_file *class_file){
	printf("CLASS FILE INFO:\n");
	printf(">magic: 0x%X\n", class_file->magic);
	printf(">minor_version: %d\n", class_file->minor_version);
	printf(">major_version: %d\n", class_file->major_version);
	printf(">constant_pool_count: %d\n", class_file->constant_pool_count);
	print_cp_info(class_file->constant_pool, class_file->constant_pool_count, class_file);
	printf(">acess_flag: 0x%X\n", class_file->acess_flags);
	printf(">this_class: %d\n", class_file->this_class);
	printf(">super_class: %d\n", class_file->super_class);
	printf(">interfaces_count: %d\n", class_file->interfaces_count);
	printf(">fields_count: %d\n", class_file->fields_count);
	print_field_info(class_file->fields, class_file->fields_count, class_file);
	printf(">methods_count: %d\n", class_file->methods_count);
	print_method_info(class_file->methods, class_file->methods_count, class_file);
	printf(">attributes_count: %d\n", class_file->attributes_count);
	print_attribute_info(class_file->attributes, class_file->attributes_count, class_file);
}
