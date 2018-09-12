/*
 * interpreter_basic.h
 *
 *  Created on: 02/12/2009
 *
 */

#ifndef INTERPRETER_BASIC_H_
#define INTERPRETER_BASIC_H_

#include "interpreter_structs.h"


void jump(t_interpreter *interpreter, char *classPath, char *methodName, char *descriptor, int n_arguments);
t_class_file *leitura_class_file(t_interpreter *interpreter, char *class_path);
t_object *instanciate_object(t_class_file *class_file,  t_interpreter *interpreter);
int jumpback(t_interpreter *interpreter, int n_return);
t_classfile_list *get_super_classes(t_class_file *class_file, t_interpreter *interpreter);

#endif /* INTERPRETER_BASIC_H_ */
