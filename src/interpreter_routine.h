/*
 * interpreter_routine.h
 *
 *  Created on: 08/12/2009
 *
 */

#ifndef INTERPRETER_ROUTINE_H_
#define INTERPRETER_ROUTINE_H_

#include "class.h"
#include "interpreter_structs.h"

int start_interpreter(char *class_file_name, char *methodName, char *descriptor);
u1 read_instruction(t_frame *frame);
u1 read_u1(t_frame *frame);
short int read_u2(t_frame *frame);
long long read_u4(t_frame *frame);
int execute_iteration(t_interpreter *interpreter);

#endif /* INTERPRETER_ROUTINE_H_ */
