/**
 * @brief class_reader.c
 *
 * @version 1.0
 * 
 * @date 29/09/2009
 *
 **/


/*Includes*/
#include "class_reader.h"
#include "search_functions.h"

t_attribute_info* read_attribute_info (FILE *fPtr, u2 count, t_class_file *class_file);

/**
 * Leitura das exceções
 * @fPtr Ponteiro para o arquivo .class sendo lido
 * @count numero de exceções a serem lidos
 * 
 * @return ponteiro para estrutura da lista de exceções
 */
t_exception_table* read_exception_table(FILE *fPtr, u2 count) {
	t_exception_table *exception_table, *p1;
	int i;

	exception_table = calloc(count, sizeof(t_exception_table));

	p1 = exception_table;
	for(i=0; i< count; i++, p1++) {
		freadLE(&(p1->start_pc), sizeof(u2), 1, fPtr);
		freadLE(&(p1->end_pc), sizeof(u2), 1, fPtr);
		freadLE(&(p1->handler_pc), sizeof(u2), 1, fPtr);
		freadLE(&(p1->catch_type), sizeof(u2), 1, fPtr);
	}

	return exception_table;
}

/**
 * Leitura das classes internas
 * @fPtr Ponteiro para o arquivo .class sendo lido
 * @count numero de classes internas a serem lidos
 * 
 * @return ponteiro para estrutura da lista de classes internas
 */
t_inner_class* read_inner_class(FILE *fPtr, u2 count) {
	t_inner_class *inner_class, *p1;
	int i;

	inner_class = calloc(count, sizeof(t_inner_class));

	p1 = inner_class;
	for(i=0; i< count; i++, p1++) {
		freadLE(&(p1->inner_class_info_index), sizeof(u2), 1, fPtr);
		freadLE(&(p1->outer_class_info_index), sizeof(u2), 1, fPtr);
		freadLE(&(p1->inner_name_index), sizeof(u2), 1, fPtr);
		freadLE(&(p1->inner_class_access_flags), sizeof(u2), 1, fPtr);
	}

	return inner_class;
}

/**
 * Leitura de LineNumberTables (tipo de atributo)
 * @fPtr Ponteiro para o arquivo .class sendo lido
 * @count numero de LineNumberTables a serem lidas
 * 
 * @return ponteiro para estrutura da lista de LineNumberTables
 */
t_line_number_table *read_line_number_table(FILE *fPtr, u2 count) {
	t_line_number_table *line_number_table , *p1;
	int i;

	line_number_table = calloc(count, sizeof(t_line_number_table));

	p1 = line_number_table;
	for(i=0; i < count; i++, p1++) {
		freadLE(&(p1->start_pc), sizeof(u2), 1, fPtr);
		freadLE(&(p1->line_number), sizeof(u2), 1, fPtr);
	}

	return line_number_table;
}

/**
 * Leitura de LineNumberTables (tipo de atributo)
 * @fPtr Ponteiro para o arquivo .class sendo lido
 * @count numero de LineNumberTables a serem lidas
 * 
 * @return ponteiro para estrutura da lista de LineNumberTables
 */
t_local_variable_table *read_local_variable_table(FILE *fPtr, u2 count) {
	t_local_variable_table *local_variable_table, *p1;
	int i;

	local_variable_table = calloc(count, sizeof(t_local_variable_table));

	p1 = local_variable_table;
	for(i=0; i< count; i++, p1++) {
		freadLE(&(p1->start_pc), sizeof(u2), 1, fPtr);
		freadLE(&(p1->length), sizeof(u2), 1, fPtr);
		freadLE(&(p1->name_index), sizeof(u2), 1, fPtr);
		freadLE(&(p1->descriptor_index), sizeof(u2), 1, fPtr);
		freadLE(&(p1->index), sizeof(u2), 1, fPtr);
	}

	return local_variable_table;
}

/**
 * Leitura de ConstantValues (tipo de atributo)
 * @fPtr Ponteiro para o arquivo .class sendo lido
 * @name_index indice na tabela da constantpool
 * @len tamanho do atributo
 * 
 * @return ponteiro para estrutura da lista de ConstantValues
 */
t_info_constant_value read_a_constant_value(FILE *fPtr, int name_index, int len) {
	t_info_constant_value constant_value;
	constant_value.attribute_name_index = name_index;
	constant_value.attribute_length = len;
	freadLE(&(constant_value.constantvalue_index), sizeof(u2), 1, fPtr);
	return constant_value;
}

/**
 * Leitura de codigos (tipo de atributo)
 * @fPtr Ponteiro para o arquivo .class sendo lido
 * @class_file ponteiro para o arquivo .class a ser usado na busca da constant pool
 * @name_index indice na tabela da constantpool
 * @len tamanho do atributo
 * 
 * @return ponteiro para estrutura da lista de ConstantValues
 */
t_info_code read_a_code_attribute(FILE *fPtr, t_class_file *class_file, int name_index, int len) {
	t_info_code code_attribute;
	code_attribute.attribute_name_index = name_index;
	code_attribute.attribute_length = len;
	freadLE(&(code_attribute.max_stack), sizeof(u2), 1, fPtr);
	freadLE(&(code_attribute.max_locals), sizeof(u2), 1, fPtr);
	freadLE(&(code_attribute.code_length), sizeof(u4), 1, fPtr);
	code_attribute.code = calloc(code_attribute.code_length, sizeof(u1));
	freadLE((code_attribute.code), sizeof(u1), code_attribute.code_length, fPtr);
	freadLE(&(code_attribute.exception_table_length), sizeof(u2), 1, fPtr);
	code_attribute.exception_table = read_exception_table(fPtr, code_attribute.exception_table_length);
	freadLE(&(code_attribute.attributes_count), sizeof(u2), 1, fPtr);
	code_attribute.attributes = read_attribute_info(fPtr, code_attribute.attributes_count, class_file);

	return code_attribute;


}

/**
 * Leitura de Exceptions (tipo de atributo)
 * @fPtr Ponteiro para o arquivo .class sendo lido
 * @name_index indice na tabela da constantpool
 * @len tamanho do atributo
 * 
 * @return ponteiro para estrutura da lista de Exceptions
 */
t_info_exception read_a_exception(FILE *fPtr, int name_index, int len) {
	t_info_exception exception;
	exception.attribute_name_index = name_index;
	exception.attribute_length = len;
	freadLE(&(exception.number_of_exceptions), sizeof(u2), 1, fPtr);
	freadLE(&(exception.exception_index_table), sizeof(u2), exception.number_of_exceptions, fPtr);

	return exception;
}

/**
 * Leitura de innerclasses (tipo de atributo)
 * @fPtr Ponteiro para o arquivo .class sendo lido
 * @name_index indice na tabela da constantpool
 * @len tamanho do atributo
 * 
 * @return ponteiro para estrutura da lista de innerclasses
 */
t_info_innerclasses read_a_inner_classes(FILE *fPtr, int name_index, int len) {
	t_info_innerclasses innerclasses;
	innerclasses.attribute_name_index = name_index;
	innerclasses.attribute_length = len;
	freadLE(&(innerclasses.number_of_classes), sizeof(u2), 1, fPtr);
	innerclasses.classes = read_inner_class(fPtr, innerclasses.number_of_classes);

	return innerclasses;

}

/**
 * Leitura de synthetic (tipo de atributo)
 * @fPtr Ponteiro para o arquivo .class sendo lido
 * @name_index indice na tabela da constantpool
 * @len tamanho do atributo
 * 
 * @return ponteiro para estrutura da lista de synthetic
 */
t_info_synthetic read_a_synthetic(FILE *fPtr, int name_index, int len) {
	t_info_synthetic syn;

	syn.attribute_name_index = name_index;
	syn.attribute_length = len;

	return syn;
}

/**
 * Leitura de sourcefile (tipo de atributo)
 * @fPtr Ponteiro para o arquivo .class sendo lido
 * @name_index indice na tabela da constantpool
 * @len tamanho do atributo
 * 
 * @return ponteiro para estrutura da lista de sourcefile
 */
t_info_sourcefile read_a_sourcefile(FILE *fPtr, int name_index, int len) {
	t_info_sourcefile sf;

	sf.attribute_name_index = name_index;
	sf.attribute_length = len;
	freadLE(&(sf.sourcefile_index), sizeof(u2), 1, fPtr);

	return sf;
}

/**
 * Leitura de LineNumberTable (tipo de atributo)
 * @fPtr Ponteiro para o arquivo .class sendo lido
 * @name_index indice na tabela da constantpool
 * @len tamanho do atributo
 * 
 * @return ponteiro para estrutura da lista de LineNumberTable
 */
t_info_line_number_table read_a_line_number_table(FILE *fPtr, int name_index, int len) {
	t_info_line_number_table lnt;
	lnt.attribute_name_index = name_index;
	lnt.attribute_length = len;
	freadLE(&(lnt.line_number_table_length), sizeof(u2), 1, fPtr);
	lnt.line_number_table = read_line_number_table(fPtr, lnt.line_number_table_length);

	return lnt;
}

/**
 * Leitura de LocalVariableTable (tipo de atributo)
 * @fPtr Ponteiro para o arquivo .class sendo lido
 * @name_index indice na tabela da constantpool
 * @len tamanho do atributo
 * 
 * @return ponteiro para estrutura da lista de LocalVariableTable
 */
t_info_local_variable_table read_a_local_variable_table(FILE *fPtr, int name_index, int len) {
	t_info_local_variable_table lvt;

	lvt.attribute_name_index = name_index;
	lvt.attribute_length = len;
	freadLE(&(lvt.local_variable_table_length), sizeof(u2), 1, fPtr);

	lvt.local_variable_table = read_local_variable_table(fPtr, lvt.local_variable_table_length);

	return lvt;
}

/**
 * Leitura de deprecated (tipo de atributo)
 * @fPtr Ponteiro para o arquivo .class sendo lido
 * @name_index indice na tabela da constantpool
 * @len tamanho do atributo
 * 
 * @return ponteiro para estrutura da lista de deprecated
 */
t_info_deprecated read_a_deprecated(FILE *fPtr, int name_index, int len) {
	t_info_deprecated deprecated;

	deprecated.attribute_name_index = name_index;
	deprecated.attribute_length = len;

	return deprecated;
}

/**
 * Leitura de signature (tipo de atributo)
 * @fPtr Ponteiro para o arquivo .class sendo lido
 * @name_index indice na tabela da constantpool
 * @len tamanho do atributo
 * 
 * @return ponteiro para estrutura da lista de signature
 */
t_info_signature read_a_signature(FILE *fPtr, int name_index, int len) {
	t_info_signature signature;
	signature.attribute_name_index = name_index;
	signature.attribute_length = len;
	freadLE(&(signature.signature_index), sizeof(u2), 1, fPtr);

	return signature;
}

/**
 * Leitura dos atributos de um field_info
 * @fPtr Ponteiro para o arquivo .class sendo lido
 * @count numero de elementos field_info sendo lidos
 * 
 * @return array de attribute_info contendo as cp_infos que foram lidas
 */
t_attribute_info* read_attribute_info (FILE *fPtr, u2 count, t_class_file *class_file){
	t_attribute_info *attribute_info;					/*Ponteiro para lista de attributos */
	t_attribute_info *pAttribute;						/*Ponteiro de deslocamento */
	char *name_index;
	int i;
	attribute_info = calloc(count, sizeof(t_attribute_info));
	
	/*loop de leitura*/
											/* Contador */
	pAttribute = attribute_info;
	for( i = 0; i < count ; i++, pAttribute++ ){
		/*Leitura dos elementos de um atributo*/
		freadLE( &(pAttribute->attribute_name_index), sizeof(u2), 1, fPtr );
		freadLE( &(pAttribute->attribute_length), sizeof(u4), 1, fPtr );
		name_index = find_utf8_info(class_file, pAttribute->attribute_name_index);


		if(strcmp(name_index, "ConstantValue") == 0) {
			pAttribute->_info.constant_value = read_a_constant_value(fPtr, pAttribute->attribute_name_index, pAttribute->attribute_length);

		} else if(strcmp(name_index, "Code") == 0) {
			pAttribute->_info.code = read_a_code_attribute(fPtr, class_file, pAttribute->attribute_name_index, pAttribute->attribute_length);

		} else if(strcmp(name_index, "Exceptions") == 0) {
			pAttribute->_info.exception = read_a_exception(fPtr, pAttribute->attribute_name_index, pAttribute->attribute_length);

		} else if(strcmp(name_index, "InnerClasses") == 0) {
			pAttribute->_info.innerclasses = read_a_inner_classes(fPtr, pAttribute->attribute_name_index, pAttribute->attribute_length);

		} else if(strcmp(name_index, "Synthetic") == 0) {
			pAttribute->_info.synthetic = read_a_synthetic(fPtr, pAttribute->attribute_name_index, pAttribute->attribute_length);

		} else if(strcmp(name_index, "SourceFile") == 0) {
			pAttribute->_info.sourcefile = read_a_sourcefile(fPtr, pAttribute->attribute_name_index, pAttribute->attribute_length);

		} else if(strcmp(name_index, "LineNumberTable") == 0) {
			pAttribute->_info.line_number_table = read_a_line_number_table(fPtr, pAttribute->attribute_name_index, pAttribute->attribute_length);

		} else if(strcmp(name_index, "LocalVariableTable") == 0) {
			pAttribute->_info.local_variable_table = read_a_local_variable_table(fPtr, pAttribute->attribute_name_index, pAttribute->attribute_length);

		} else if(strcmp(name_index, "Deprecated") == 0) {
			pAttribute->_info.deprecated = read_a_deprecated(fPtr, pAttribute->attribute_name_index, pAttribute->attribute_length);

		} else if(strcmp(name_index, "Signature") == 0) {
			pAttribute->_info.signature = read_a_signature(fPtr, pAttribute->attribute_name_index, pAttribute->attribute_length);
		} else {
			pAttribute->info = calloc(pAttribute->attribute_length, sizeof(u1));
			freadLE( pAttribute->info, sizeof(u1), pAttribute->attribute_length, fPtr );
		}






	}
	
	/*retorno*/
	return (attribute_info);
}

/**
 * Leitura dos valores de um field_info
 * @fPtr Ponteiro para o arquivo .class sendo lido
 * @count numero de elementos field_info sendo lidos
 * 
 * @return array de field_info contendo as cp_infos que foram lidas
 */
t_field_info* read_field_info (FILE *fPtr, u2 count, t_class_file *class_file){
	t_field_info *field_info;							/*Ponteiro para a lista de infos */
	t_field_info *pField;								/*Ponteiro de deslocamento */
	field_info = calloc(count, sizeof(t_field_info));
	
	/*loop de leitura*/
	int i;												/* Contador */
	pField = field_info;
	for( i = 0; i < count ; i++, pField++){
		/*Leitura dos elementos de um atributo*/
		freadLE( &(pField->access_flags), sizeof(u2), 1, fPtr );
		freadLE( &(pField->name_index), sizeof(u2), 1, fPtr );
		freadLE( &(pField->descriptor_index), sizeof(u2), 1, fPtr );
		freadLE( &(pField->attributes_count), sizeof(u2), 1, fPtr );
		pField->attributes = read_attribute_info(fPtr, pField->attributes_count, class_file);
	}
	
	/*retorno*/
	return (field_info);
}

/**
 * Leitura dos valores de method_info.
 * @fPtr ponteiro para o arquivo .class sendo lido
 * @count numero de method_info a serem lidos
 *
 * @return method_info array contendo todas method_info lidas
 */
t_method_info* read_method_info(FILE *fPtr, u2 count, t_class_file *class_file){
	t_method_info *method_info;
	t_method_info *pMethod;
	int i;
	
	method_info = calloc(count, sizeof(t_method_info));
	pMethod = method_info;
	for( i=0 ; i<count ; i++, pMethod++ ){
		freadLE( &(pMethod->acess_flags), sizeof(u2), 1, fPtr );
		freadLE( &(pMethod->name_index), sizeof(u2), 1, fPtr );
		freadLE( &(pMethod->descriptor_index), sizeof(u2), 1, fPtr );
		freadLE( &(pMethod->attributes_count), sizeof(u2), 1, fPtr );
		pMethod->attributes = read_attribute_info(fPtr, pMethod->attributes_count, class_file);
	}
	
	return(method_info);
}

/**
 * Realiza a leitura dos valores de cp_info.
 *
 * @fPtr ponteiro para o arquivo .class sendo lido
 * @count numero de cp_info a serem lidos
 *
 * @return cp_info array contendo todas cp_info lidas
 */
t_cp_info* read_cp_info(FILE *fPtr, u2 count) {
	t_cp_info *cp_info, *p1;
	int i;
	int result;
	
	cp_info = calloc(count, sizeof(t_cp_info));
	
	p1 = cp_info;
	for(i = 0; i < count; i++, p1++) {
		
		result = freadLE(&(p1->tag), sizeof(u1), 1,fPtr);
		switch (p1->tag) {
			case 7:
				result = freadLE(&(p1->info.class_info.name_index),sizeof(u2), 1, fPtr);
				break;
			case 9:
				result = freadLE(&(p1->info.fieldref_info.class_index),sizeof(u2), 1, fPtr);
				result = freadLE(&(p1->info.fieldref_info.name_and_type_index),sizeof(u2), 1, fPtr);
				break;
			case 10:
				result = freadLE(&(p1->info.methodref_info.class_index),sizeof(u2), 1, fPtr);
				result = freadLE(&(p1->info.methodref_info.name_and_type_index),sizeof(u2), 1, fPtr);
				break;
				
			case 11:
				result = freadLE(&(p1->info.interfacemethod_info.class_index),sizeof(u2), 1, fPtr);
				result = freadLE(&(p1->info.interfacemethod_info.name_and_type_index),sizeof(u2), 1, fPtr);
				break;
				
			case 8:
				result = freadLE(&(p1->info.string_info.string_index),sizeof(u2), 1, fPtr);
				break;
			case 3:
				result = freadLE(&(p1->info.integer_info.bytes),sizeof(u4), 1, fPtr);
				break;
			case 4:
				result = freadLE(&(p1->info.float_info.bytes),sizeof(u4), 1, fPtr);
				break;
			case 5:
				result = freadLE(&(p1->info.long_info.high_bytes),sizeof(u4), 1, fPtr);
				result = freadLE(&(p1->info.long_info.low_bytes),sizeof(u4), 1, fPtr);
				i++;
				p1++;
				p1->info.dep_info.byte = 0;
				break;
			case 6:
				result = freadLE(&(p1->info.double_info.high_bytes),sizeof(u4), 1, fPtr);
				result = freadLE(&(p1->info.double_info.low_bytes),sizeof(u4), 1, fPtr);
				i++;
				p1++;
				p1->info.dep_info.byte = 0;
				p1->tag = 99;
				break;
			case 12:
				result = freadLE(&(p1->info.nameandtype_info.name_index),sizeof(u2), 1, fPtr);
				result = freadLE(&(p1->info.nameandtype_info.descriptor_index),sizeof(u2), 1, fPtr);
				break;
			case 1:
				result = freadLE(&(p1->info.utf8_info.length),sizeof(u2), 1, fPtr);
				p1->info.utf8_info.bytes = calloc(p1->info.utf8_info.length, sizeof(u1));
				result = freadLE((p1->info.utf8_info.bytes),sizeof(u1), p1->info.utf8_info.length, fPtr);
				break;
				
		}
	}
	
	
	return cp_info;
}

/**
 * descricao
 * @fPtr ponteiro para o arquivo .class sendo lido
 *
 * @return class_file retorna class_file
 */
t_class_file* read_class_file(FILE *fPtr){
	t_class_file *class_file;
	
	class_file = malloc(sizeof(t_class_file));
	
	freadLE( &(class_file->magic), sizeof(u4), 1, fPtr );
	freadLE( &(class_file->minor_version), sizeof(u2), 1, fPtr );
	freadLE( &(class_file->major_version), sizeof(u2), 1, fPtr );
	freadLE( &(class_file->constant_pool_count), sizeof(u2), 1, fPtr );
	
	class_file->constant_pool = read_cp_info(fPtr , (class_file->constant_pool_count)-1);
	freadLE( &(class_file->acess_flags), sizeof(u2), 1, fPtr );
	freadLE( &(class_file->this_class), sizeof(u2), 1, fPtr );
	freadLE( &(class_file->super_class), sizeof(u2), 1, fPtr );
	
	freadLE( &(class_file->interfaces_count), sizeof(u2), 1, fPtr );
	class_file->interfaces = calloc(class_file->interfaces_count, sizeof(u2));
	freadLE( class_file->interfaces , sizeof(u2), class_file->interfaces_count, fPtr );
	
	freadLE( &(class_file->fields_count), sizeof(u2), 1, fPtr );
	class_file->fields = read_field_info(fPtr , class_file->fields_count, class_file);
	freadLE( &(class_file->methods_count), sizeof(u2), 1, fPtr );
	class_file->methods = read_method_info(fPtr , class_file->methods_count, class_file);
	freadLE( &(class_file->attributes_count), sizeof(u2), 1, fPtr );
	class_file->attributes = read_attribute_info(fPtr , class_file->attributes_count, class_file);
	
	return(class_file);
}

/**
 * Função de leitura de arquivo .class
 * @fileName Nome do arquivo .class
 * @class_file estrutura de classe montada e configurada
 */
t_class_file* read_dot_class(char* fileName) {
	FILE *fPtr;
	t_class_file *class_file;
	/* Abertura do arquivo */
	if(!(fPtr = fopen(fileName, "rb"))) {
		fprintf(stderr, "Error: file <%s> was not found.",fileName);
		exit(1);
	}
	/* leitura do arquivo .class */
	class_file = read_class_file(fPtr);

	/* Finalizando arquivo e retornando valor */
	fclose(fPtr);
	return(class_file);
}
