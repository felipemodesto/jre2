/**
 * @brief class.h
 *
 * @version 1.0
 * 
 * @date 06/10/2009
 *
 **/

#ifndef CLASS_H_
#define CLASS_H_


#define Uint8 char
#define Uint16 short unsigned
#define Uint32 int unsigned

#define u4 Uint32
#define u2 Uint16
#define u1 Uint8




/**
 *
 * @struct cp_info class.h "class.h"
 * @brief Struct representando o tipo cp_info.
 * 
 * Registro variante em u_info:
 * Nome do Tipo variante		tag
 * CONSTANT_Class				7
 * CONSTANT_Fieldref	 		9
 * CONSTANT_Methodref	 		10
 * CONSTANT_InterfaceMethodref	11
 * CONSTANT_String	 			8
 * CONSTANT_Integer	 			3
 * CONSTANT_Float	 			4
 * CONSTANT_Long	 			5
 * CONSTANT_Double	 			6
 * CONSTANT_NameAndType	 		12
 * CONSTANT_Utf8	 			1
 *
 **/
typedef struct cp_info {
	u1 tag;
	union u_info {
		struct CONSTANT_Class_info {
			u2 name_index;
		} class_info;

		struct CONSTANT_Fieldref_info {
			u2 class_index;
			u2 name_and_type_index;
		} fieldref_info, methodref_info, interfacemethod_info;

		struct CONSTANT_String_info {
			u2 string_index;
		} string_info;

		struct CONSTANT_Integer_info {
			u4 bytes;
		} integer_info, float_info;

		struct CONSTANT_Long_info {
			u4 high_bytes;
			u4 low_bytes;
		} long_info, double_info;

		struct CONSTANT_NameAndType_info {
			u2 name_index;
			u2 descriptor_index;
		} nameandtype_info;

		struct Utf8_info {
			u2 length;
			u1 *bytes;
		} utf8_info;

		struct dep_info {
			u1 byte;
		} dep_info;


	} info;
} t_cp_info;

typedef struct exception_table {
	u2 start_pc;
	u2 end_pc;
	u2 handler_pc;
	u2 catch_type;
}t_exception_table;

typedef struct inner_class {
	u2 inner_class_info_index;
	u2 outer_class_info_index;
	u2 inner_name_index;
	u2 inner_class_access_flags;
} t_inner_class;

typedef struct line_number_table {
	u2 start_pc;
	u2 line_number;
} t_line_number_table;

typedef struct local_variable_table {
	u2 start_pc;
	u2 length;
	u2 name_index;
	u2 descriptor_index;
	u2 index;
} t_local_variable_table;


typedef struct ConstantValue_attribute {
			u2 attribute_name_index;
			u4 attribute_length;
			u2 constantvalue_index;
} t_info_constant_value;

typedef struct Code_attribute {
	u2 attribute_name_index;
	u4 attribute_length;
	u2 max_stack;
	u2 max_locals;
	u4 code_length;
	u1 *code;
	u2 exception_table_length;
	t_exception_table *exception_table;
	u2 attributes_count;
	struct attribute_info *attributes;
} t_info_code;

typedef struct Exceptions_attribute {
	u2 attribute_name_index;
	u4 attribute_length;
	u2 number_of_exceptions;
	u2 *exception_index_table;
} t_info_exception;

typedef struct InnerClasses_attribute {
	u2 attribute_name_index;
	u4 attribute_length;
	u2 number_of_classes;
	t_inner_class *classes;
} t_info_innerclasses;

typedef struct Synthetic_attribute {
	u2 attribute_name_index;
	u4 attribute_length;
} t_info_synthetic;

typedef struct SourceFile_attribute {
	u2 attribute_name_index;
	u4 attribute_length;
	u2 sourcefile_index;
} t_info_sourcefile;

typedef struct Signature_attribute {
	u2 attribute_name_index;
	u4 attribute_length;
	u2 signature_index;
} t_info_signature;

typedef struct LineNumberTable_attribute {
	u2 attribute_name_index;
	u4 attribute_length;
	u2 line_number_table_length;
	t_line_number_table *line_number_table;
} t_info_line_number_table;

typedef struct LocalVariableTable_attribute {
	u2 attribute_name_index;
	u4 attribute_length;
	u2 local_variable_table_length;
	t_local_variable_table *local_variable_table;
} t_info_local_variable_table;

typedef struct Deprecated_attribute {
	u2 attribute_name_index;
	u4 attribute_length;
} t_info_deprecated;

/**
 *
 * @struct attribute_info class.h "class.h"
 * @brief Struct representando o tipo attribute_info.
 * 
 *
 **/
typedef struct attribute_info {
	u2 attribute_name_index;
	u4 attribute_length;
	u1 *info;

	union u_info_att {
		t_info_constant_value constant_value;
		t_info_code code;
		t_info_exception exception;
		t_info_innerclasses innerclasses;
		t_info_synthetic synthetic;
		t_info_sourcefile sourcefile;
		t_info_line_number_table line_number_table;
		t_info_local_variable_table local_variable_table;
		t_info_deprecated deprecated;
		t_info_signature signature;

	} _info;
} t_attribute_info;

/**
 *
 * @struct constantvalue_attribute class.h "class.h"
 * @brief Struct representando o campo info de um attribute_info do tipo constantvalue_attribute
 *
 **/
typedef struct constantvalue_attribute {
	u2 access_flags;
	u2 name_index;
	u2 descriptor_index;
	u2 attributes_count;
	t_attribute_info *attributes;
}t_constantvalue_attribute;

/**
 *
 * @struct exception_table class.h "class.h"
 * @brief Struct representando o campo de excessões de um atributo do tipo code
 *
 **/


/**
 *
 * @struct code_attribute class.h "class.h"
 * @brief Struct representando o campo info de um attribute_info do tipo code_attribute
 *
 **/
typedef struct code_attribute {
	/* u2 attribute_name_index */
	/* u4 attribute_length */
	u2 max_stack;
	u2 max_locals;
	u4 code_length;
	u1 *code;
	u2 exception_table_length;
	t_exception_table *exception_table;
	u2 attributes_count;
	t_attribute_info *attributes;
}t_code_attribute;

/**
 *
 * @struct sourcefile_attribute class.h "class.h"
 * @brief Struct representando o campo info de um attribute_info do tipo sourcefile_attribute
 *
 **/
typedef struct sourcefile_attribute {
	/* Deixando sÛ os elementos dentro do info do attribute_info */
	/* u2 attribute_name_index; */
	/* u4 attribute_length; */
	u2 sourcefile_index;
}t_sourcefile_attribute;

/**
 *
 * @struct field_info class.h "class.h"
 * @brief Struct representando o tipo field_info.
 * 
 *
 **/
typedef struct field_info {
	u2 access_flags;
	u2 name_index;
	u2 descriptor_index;
	u2 attributes_count;
	t_attribute_info *attributes;
} t_field_info;

/**
 *
 * @struct method_info class.h "class.h"
 * @brief Struct representando o tipo method_info.
 * 
 *
 **/
typedef struct method_info {
	u2 acess_flags;
	u2 name_index;
	u2 descriptor_index;
	u2 attributes_count;
	t_attribute_info *attributes;
} t_method_info;

/**
 *
 * @struct class_file class.h "class.h"
 * @brief Struct representando o tipo class_file.
 * 
 **/
typedef struct class_file {
	u4 magic;
	u2 minor_version;
	u2 major_version;
	u2 constant_pool_count;
	t_cp_info *constant_pool;
	u2 acess_flags;
	u2 this_class;
	u2 super_class;
	u2 interfaces_count;
	u2 *interfaces;
	u2 fields_count;
	t_field_info *fields;
	u2 methods_count;
	t_method_info *methods;
	u2 attributes_count;
	t_attribute_info *attributes;

} t_class_file;

#endif /* CLASS_H_ */
