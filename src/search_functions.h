/*
 * search_functions.h
 *
 *  Created on: 01/12/2009
 *
 */

#ifndef SEARCH_FUNCTIONS_H_
#define SEARCH_FUNCTIONS_H_

#include <stdlib.h>
#include "class.h"
#include "interpreter_structs.h"




typedef struct method_about {
	char *className;
	char *methodName;
	char *type;

} t_method_about;

typedef struct field_about {
	char *className;
	char *fieldName;
	char *type;
} t_field_about;

typedef struct name_and_type_about {
	char *name;
	char *type;
} t_name_and_type_about;

typedef struct method_and_class {
	t_method_info *method_info;
	t_class_file *class_file;
} t_method_and_class;

u1 find_tag_info(t_class_file *class, int n);
t_method_about *find_method_info(t_class_file *class, int n);
char *find_class_info(t_class_file *class, int n);
char *find_utf8_info(t_class_file *class, int n);
t_name_and_type_about *find_name_and_type_info(t_class_file *class, int n);
t_field_about *find_field_info(t_class_file *class, int n);
char *find_string_info(t_class_file *class, int n);
u4 find_integer_info(t_class_file *class, int n);
long long int find_long_info(t_class_file *class, int n);
float find_float_info(t_class_file *class, int n);
double find_double_info(t_class_file *class, int n);
t_method_and_class* find_method_by_name(t_class_file *class, char *methodName, char *descriptor, t_interpreter *interpreter);
t_attribute_info* find_method_attribute_by_name(t_class_file *class, t_method_info *method, char *attName);
t_field_info* find_field_by_name(t_class_file *class, char *fieldName);
t_method_and_class* find_method_by_name_only_this_class(t_class_file *class, char *methodName, char *descriptor, t_interpreter *interpreter);

#endif /* SEARCH_FUNCTIONS_H_ */
