/*
 * instructions.c
 *
 *  Created on: 09/12/2009
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "interpreter_basic.h"
#include "interpreter_structs.h"
#include "instructions.h"
#include "search_functions.h"
#include "interpreter_routine.h"

int bipush(t_interpreter *interpreter, int valor) {
	opstack_push(&interpreter->current_frame->opstack, "I", (&valor));

	return 0;
}

int aconst_null(t_interpreter *interpreter) {
	opstack_push(&interpreter->current_frame->opstack, "[", NULL);

	return 0;
}

int istore(t_interpreter *interpreter, int pos) {

	transfer_opstack_to_localvar(&(interpreter->current_frame->opstack), &(interpreter->current_frame->local_variables), pos);

	return 0;
}


int iload(t_interpreter *interpreter, int pos) {
	transfer_localvar_to_opstack(&(interpreter->current_frame->local_variables), pos, &(interpreter->current_frame->opstack));

	return 0;
}

int iadd(t_interpreter *interpreter) {
	int a, b, sum;
	a = opstack_pop((&interpreter->current_frame->opstack))->data.data_int;
	b = opstack_pop((&interpreter->current_frame->opstack))->data.data_int;
	sum = a + b;

	opstack_push((&interpreter->current_frame->opstack), "I", &sum);

	return 0;
}

int i2d(t_interpreter *interpreter) {
	int a;
	double b;
	a = opstack_pop((&interpreter->current_frame->opstack))->data.data_int;
	b = (double)a;

	opstack_push((&interpreter->current_frame->opstack), "D", &b);

	return 0;

}

int dstore(t_interpreter *interpreter, int pos) {
	transfer_opstack_to_localvar(&(interpreter->current_frame->opstack), &(interpreter->current_frame->local_variables), pos);

	return 0;
}

int ldc(t_interpreter *interpreter, int cp_index) {
	char *string;
	int integer;
	float fvalue;
	long long lvalue;
	double dvalue;	
	switch((signed int)find_tag_info(interpreter->current_frame->class_file, cp_index)) {
	case 8:
		/* CONSTANT_String */

		string = find_string_info(interpreter->current_frame->class_file, cp_index);
		opstack_push(&(interpreter->current_frame->opstack), "[", string);

		break;
	case 3:
		/* CONSTANT_Integer */
		integer = find_integer_info(interpreter->current_frame->class_file, cp_index);
		opstack_push(&(interpreter->current_frame->opstack), "I", &integer);

		break;
	case 4:
		/* CONSTANT_Float */
		fvalue = find_float_info(interpreter->current_frame->class_file, cp_index);
		opstack_push(&(interpreter->current_frame->opstack), "F", &fvalue);

		break;
	case 5:
		/* CONSTANT_Long */
		lvalue = find_long_info(interpreter->current_frame->class_file, cp_index);
		opstack_push(&(interpreter->current_frame->opstack), "J", &lvalue);

		break;
	case 6:
		/* CONSTANT_Double */
		dvalue = find_double_info(interpreter->current_frame->class_file, cp_index);
		opstack_push(&(interpreter->current_frame->opstack), "D", &dvalue);

		break;

	default:
		fprintf(stderr,"Erro em 'ldc' tag: %d\n", (signed int)find_tag_info(interpreter->current_frame->class_file, cp_index));
		exit(1);
		break;
	}

	return 0;
}

int fstore(t_interpreter *interpreter, int pos) {
	transfer_opstack_to_localvar(&(interpreter->current_frame->opstack), &(interpreter->current_frame->local_variables), pos);

	return 0;
}

int fload(t_interpreter *interpreter, int pos) {
	transfer_localvar_to_opstack(&(interpreter->current_frame->local_variables), pos, &(interpreter->current_frame->opstack));

	return 0;
}

int f2l(t_interpreter *interpreter) {
	float a;
	long long b;
	a = opstack_pop(&(interpreter->current_frame->opstack))->data.data_float;
	b = (long long)a;

	opstack_push(&(interpreter->current_frame->opstack), "J", &b);

	return 0;
}

int lstore(t_interpreter *interpreter, int pos) {
	transfer_opstack_to_localvar(&(interpreter->current_frame->opstack), &(interpreter->current_frame->local_variables), pos);

	return 0;
}


int iconst(t_interpreter *interpreter, int value) {
	opstack_push(&(interpreter->current_frame->opstack), "I", &value);

	return 0;
}

int dload(t_interpreter *interpreter, int pos) {
	transfer_localvar_to_opstack(&(interpreter->current_frame->local_variables), pos, &(interpreter->current_frame->opstack));

	return 0;
}

int d2i(t_interpreter *interpreter) {
	double a;
	int b;
	a = opstack_pop(&(interpreter->current_frame->opstack))->data.data_double;
	b = (int)a;

	opstack_push(&(interpreter->current_frame->opstack), "I", &b);

	return 0;
}

int lload(t_interpreter *interpreter, int pos) {
	transfer_localvar_to_opstack(&(interpreter->current_frame->local_variables), pos, &(interpreter->current_frame->opstack));

	return 0;
}

int l2i(t_interpreter *interpreter) {
	long long a;
	int b;
	a = opstack_pop(&(interpreter->current_frame->opstack))->data.data_long;
	b = (int)a;

	opstack_push(&(interpreter->current_frame->opstack), "I", &b);

	return 0;
}

int lconst(t_interpreter *interpreter, long long value) {
	opstack_push(&(interpreter->current_frame->opstack), "J", &value);

	return 0;
}

int fconst(t_interpreter *interpreter, float value) {
	opstack_push(&(interpreter->current_frame->opstack), "F", &value);

	return 0;
}

int dconst(t_interpreter *interpreter, double value) {
	opstack_push(&(interpreter->current_frame->opstack), "D", &value);

	return 0;
}

int sipush(t_interpreter *interpreter, int value) {
	opstack_push(&(interpreter->current_frame->opstack), "I", &value);

	return 0;
}

int aload(t_interpreter *interpreter, int pos) {
	transfer_localvar_to_opstack(&(interpreter->current_frame->local_variables), pos, &(interpreter->current_frame->opstack));

	return 0;
}

int pop(t_interpreter *interpreter) {
	opstack_pop(&(interpreter->current_frame->opstack));

	return 0;
}

int pop2(t_interpreter *interpreter) {
	if((interpreter->current_frame->opstack->type)[0] == 'D' ||
			(interpreter->current_frame->opstack->type)[0] == 'J') {
		 opstack_pop(&(interpreter->current_frame->opstack));
	} else {
		 opstack_pop(&(interpreter->current_frame->opstack));
		 opstack_pop(&(interpreter->current_frame->opstack));
	}

	return 0;
}


int d2f(t_interpreter *interpreter) {
	double a;
	float b;
	a = opstack_pop(&(interpreter->current_frame->opstack))->data.data_double;
	b = (float)a;

	opstack_push(&(interpreter->current_frame->opstack), "F", &b);

	return 0;
}

int d2l(t_interpreter *interpreter) {
	double a;
	long long b;

	a = opstack_pop(&(interpreter->current_frame->opstack))->data.data_double;
	b = (long long)a;

	opstack_push(&(interpreter->current_frame->opstack), "J", &b);

	return 0;
}

int f2d(t_interpreter *interpreter) {
	float a;
	double b;

	a = opstack_pop(&(interpreter->current_frame->opstack))->data.data_float;
	b = (double)a;

	opstack_push(&(interpreter->current_frame->opstack), "D", &b);

	return 0;
}

int f2i(t_interpreter *interpreter) {
	float a;
	int b;

	a = opstack_pop(&(interpreter->current_frame->opstack))->data.data_float;
	b = (int)a;

	opstack_push(&(interpreter->current_frame->opstack), "I", &b);

	return 0;
}

int i2b(t_interpreter *interpreter) {
	int a;
	char b;

	a = opstack_pop(&(interpreter->current_frame->opstack))->data.data_int;
	b = (char)a;

	opstack_push(&(interpreter->current_frame->opstack), "B", &b);

	return 0;

}

int i2c(t_interpreter *interpreter) {
	int a;
	char b;

	a = opstack_pop(&(interpreter->current_frame->opstack))->data.data_int;
	b = (char)a;

	opstack_push(&(interpreter->current_frame->opstack), "C", &b);

	return 0;
}

int i2f(t_interpreter *interpreter) {
	int a;
	float b;

	a = opstack_pop(&(interpreter->current_frame->opstack))->data.data_int;
	b = (float)a;

	opstack_push(&(interpreter->current_frame->opstack), "F", &b);

	return 0;

}

int i2l(t_interpreter *interpreter) {
	int a;
	long long b;

	a = opstack_pop(&(interpreter->current_frame->opstack))->data.data_int;
	b = (long long)a;

	opstack_push(&(interpreter->current_frame->opstack), "J", &b);

	return 0;
}

int i2s(t_interpreter *interpreter) {
	int a;
	short b;

	a = opstack_pop(&(interpreter->current_frame->opstack))->data.data_int;
	b = (short)a;

	opstack_push(&(interpreter->current_frame->opstack), "S", &b);

	return 0;
}

int l2d(t_interpreter *interpreter) {
	long long a;
	double b;

	a = opstack_pop(&(interpreter->current_frame->opstack))->data.data_long;
	b = (double)a;

	opstack_push(&(interpreter->current_frame->opstack), "D", &b);

	return 0;
}

int l2f(t_interpreter *interpreter) {
	long long a;
	float b;

	a = opstack_pop(&(interpreter->current_frame->opstack))->data.data_long;
	b = (float)a;

	opstack_push(&(interpreter->current_frame->opstack), "F", &b);

	return 0;
}

/* estou aqui */
int dmul(t_interpreter *interpreter) {
	double a, b, mul;
	a = opstack_pop(&(interpreter->current_frame->opstack))->data.data_double;
	b = opstack_pop(&(interpreter->current_frame->opstack))->data.data_double;

	mul = a*b;

	opstack_push(&(interpreter->current_frame->opstack), "D", &mul);

	return 0;
}

int fmul(t_interpreter *interpreter) {
	float a, b, mul;
	a = opstack_pop(&(interpreter->current_frame->opstack))->data.data_float;
	b = opstack_pop(&(interpreter->current_frame->opstack))->data.data_float;

	mul = a*b;

	opstack_push(&(interpreter->current_frame->opstack), "F", &mul);

	return 0;
}

int imul(t_interpreter *interpreter) {
	int a, b, mul;
	a = opstack_pop(&(interpreter->current_frame->opstack))->data.data_int;
	b = opstack_pop(&(interpreter->current_frame->opstack))->data.data_int;

	mul = a*b;

	opstack_push(&(interpreter->current_frame->opstack), "I", &mul);

	return 0;
}

int lmul(t_interpreter *interpreter) {
	long long a, b, mul;
	a = opstack_pop(&(interpreter->current_frame->opstack))->data.data_long;
	b = opstack_pop(&(interpreter->current_frame->opstack))->data.data_long;

	mul = a*b;

	opstack_push(&(interpreter->current_frame->opstack), "J", &mul);

	return 0;
}



int invokevirtual(t_interpreter *interpreter, int cp_index) {
	/* TODO: este invoke virtual nao esta pronto. so foi feito invoke
	 * virtual de excecao para o println, apenas!
	 */
	t_method_about *method_about;
	t_opstack *data;
	char *type;
	char *string1, *string2;
	int result_strcmp;
	char *string_to_append, *string_appended, *string_append;
	
	method_about = find_method_info(interpreter->current_frame->class_file, cp_index);
	
	if(strcmp(method_about->className, "java/io/PrintStream") == 0 &&
	   (strcmp(method_about->methodName, "println") == 0 ||
		strcmp(method_about->methodName, "print") == 0)) {
		/* realiza o println */
		if ((interpreter->current_frame->opstack->type)[0] != '#'){
			data = opstack_pop(&(interpreter->current_frame->opstack));
			type = data->type;
			if(type[0] == 'B') {
				printf("%d", data->data.data_byte);
			} else if(type[0] == 'C') {
				printf("%c", (unsigned char)data->data.data_char);
			} else if(type[0] == 'D') {
				printf("%f", data->data.data_double);
			} else if(type[0] == 'F') {
				printf("%f", data->data.data_float);
			} else if(type[0] == 'I') {
				printf("%d", data->data.data_int);
			} else if(type[0] == 'J') {
				printf("%lld", data->data.data_long);
			} else if(type[0] == 'L') {
				printf("Impressao de um objeto?! Não implementado!");
			} else if(type[0] == 'S') {
				printf("%d", data->data.data_short);
			} else if(type[0] == 'Z') {
				printf("%d", data->data.data_boolean);
			} else if(type[0] == '[') {
				printf("%s", (char*)data->data.data_reference);
			} else if(type[0] == 'r') {
				printf("Impressao de uma referencia. Arrumar.");
			}
		}
		opstack_pop(&(interpreter->current_frame->opstack));
		
		if((strcmp(method_about->methodName, "println") == 0)){
			printf("\n");
		}
	} else if(strcmp(method_about->className, "java/lang/String") == 0 &&
			  strcmp(method_about->methodName, "equals") == 0) {
		string1 = (char*)opstack_pop((&interpreter->current_frame->opstack))->data.data_reference;
		string2 = (char*)opstack_pop((&interpreter->current_frame->opstack))->data.data_reference;
		
		if(strcmp(string1, string2) == 0) {
			result_strcmp = 1;
			opstack_push(&(interpreter->current_frame->opstack), "I", &result_strcmp);
			return 0;
		} else {
			result_strcmp = 0;
			opstack_push(&(interpreter->current_frame->opstack), "I", &result_strcmp);
			return 0;
		}
	} else if((strcmp(method_about->className, "java/lang/StringBuffer") == 0 || strcmp(method_about->className, "java/lang/StringBuilder") == 0) &&
			  strcmp(method_about->methodName, "append") == 0) {
		string_append = calloc(50, sizeof(char));
		data = opstack_pop(&(interpreter->current_frame->opstack));
		type = data->type;
		string_to_append = (char*)opstack_pop(&(interpreter->current_frame->opstack))->data.data_reference;
		if(type[0] == 'B') {
			sprintf(string_append, "%d", data->data.data_byte);
		} else if(type[0] == 'C') {
			sprintf(string_append,"%c", (unsigned char)data->data.data_char);
		} else if(type[0] == 'D') {
			sprintf(string_append, "%f", data->data.data_double);
		} else if(type[0] == 'F') {
			sprintf(string_append, "%f", data->data.data_float);
		} else if(type[0] == 'I') {
			sprintf(string_append, "%d", data->data.data_int);
		} else if(type[0] == 'J') {
			sprintf(string_append, "%lld", data->data.data_long);
		} else if(type[0] == 'L') {
			sprintf(string_append, "Impressao de um objeto?!");
		} else if(type[0] == 'S') {
			sprintf(string_append, "%d", data->data.data_short);
		} else if(type[0] == 'Z') {
			sprintf(string_append, "%d", data->data.data_boolean);
		} else if(type[0] == '[') {
			string_append = (char*)data->data.data_reference;
		} else if(type[0] == 'r') {
			sprintf(string_append, "Impressao de uma referencia. Arrumar.");
		}
		
		string_appended = calloc(strlen(string_append) + strlen(string_to_append) + 1, sizeof(char));
		*string_appended = '\0';
		strcat(string_appended, string_to_append);
		strcat(string_appended, string_append);
		
		opstack_push(&(interpreter->current_frame->opstack), "[C", string_appended);
		return 0;
		
	} else if((strcmp(method_about->className, "java/lang/StringBuffer") == 0 || strcmp(method_about->className, "java/lang/StringBuilder") == 0) &&
			  strcmp(method_about->methodName, "toString") == 0) {
		return 0;
	} else if(strcmp(method_about->className, "java/lang/String") == 0 &&
				  strcmp(method_about->methodName, "length") == 0) {
		int len;
		string1 = (char*)opstack_pop((&interpreter->current_frame->opstack))->data.data_reference;

		len = strlen(string1);

		opstack_push(&(interpreter->current_frame->opstack), "I", &len);

		return 0;
	} else if(strcmp(method_about->className, "java/lang/String") == 0 &&
					  strcmp(method_about->methodName, "compareTo") == 0) {
		int strcm;
		string1 = (char*)opstack_pop((&interpreter->current_frame->opstack))->data.data_reference;
		string2 = (char*)opstack_pop((&interpreter->current_frame->opstack))->data.data_reference;

		strcm = strcmp(string1, string2);

		opstack_push(&(interpreter->current_frame->opstack), "I", &strcm);

		return 0;
	} else if(strcmp(method_about->className, "java/lang/String") == 0 &&
						  strcmp(method_about->methodName, "indexOf") == 0 &&
						  strcmp(method_about->type, "(Ljava/lang/String;)I") == 0) {
		int strstr_value;
		char *strstr_char;
		string1 = (char*)opstack_pop((&interpreter->current_frame->opstack))->data.data_reference;
		string2 = (char*)opstack_pop((&interpreter->current_frame->opstack))->data.data_reference;

		strstr_char = strstr(string1, string2);
		strstr_value = strstr_char - string1;


		opstack_push(&(interpreter->current_frame->opstack), "I", &strstr_value);

		return 0;
	} else if(strcmp(method_about->className, "java/lang/String") == 0 &&
							  strcmp(method_about->methodName, "startsWith") == 0 &&
							  strcmp(method_about->type, "(Ljava/lang/String;)Z") == 0) {
		char bool_return;
		char *strstr_char;
		string1 = (char*)opstack_pop((&interpreter->current_frame->opstack))->data.data_reference;
		string2 = (char*)opstack_pop((&interpreter->current_frame->opstack))->data.data_reference;

		strstr_char = strstr(string1, string2);
		bool_return = (strstr_char - string1 == 0) ? 1:0;

		opstack_push(&(interpreter->current_frame->opstack), "Z", &bool_return);

		return 0;

	} else 	{
		t_method_about *method_about;
		int arg_count;
		
		method_about = find_method_info(interpreter->current_frame->class_file, cp_index);
		
		arg_count = arguments_count(method_about->type) + 1;
		
		jump(interpreter, method_about->className, method_about->methodName, method_about->type, arg_count);
	}
	
	return 0;
}


int dadd(t_interpreter *interpreter) {
	double a, b, sum;
	a = opstack_pop((&interpreter->current_frame->opstack))->data.data_double;
	b = opstack_pop((&interpreter->current_frame->opstack))->data.data_double;
	sum = a + b;

	opstack_push((&interpreter->current_frame->opstack), "D", &sum);

	return 0;
}

int dsub(t_interpreter *interpreter) {
	double a, b, sub;
	a = opstack_pop((&interpreter->current_frame->opstack))->data.data_double;
	b = opstack_pop((&interpreter->current_frame->opstack))->data.data_double;
	sub = b - a;

	opstack_push((&interpreter->current_frame->opstack), "D", &sub);

	return 0;
}

int fadd(t_interpreter *interpreter){
	float a, b, sum;
	a = opstack_pop((&interpreter->current_frame->opstack))->data.data_float;
	b = opstack_pop((&interpreter->current_frame->opstack))->data.data_float;
	sum = a + b;

	opstack_push((&interpreter->current_frame->opstack),"F", &sum);

	return 0;
}

int fsub(t_interpreter *interpreter) {
	float a, b, sub;
	a = opstack_pop((&interpreter->current_frame->opstack))->data.data_float;
	b = opstack_pop((&interpreter->current_frame->opstack))->data.data_float;
	sub = b - a;

	opstack_push((&interpreter->current_frame->opstack), "F", &sub);

	return 0;
}

int isub(t_interpreter *interpreter) {
	int a, b, sub;
	a = opstack_pop((&interpreter->current_frame->opstack))->data.data_int;
	b = opstack_pop((&interpreter->current_frame->opstack))->data.data_int;
	sub = b - a;

	opstack_push((&interpreter->current_frame->opstack), "I", &sub);

	return 0;
}

int ladd(t_interpreter *interpreter){
	long long a, b, sum;
	a = opstack_pop((&interpreter->current_frame->opstack))->data.data_long;
	b = opstack_pop((&interpreter->current_frame->opstack))->data.data_long;
	sum = a + b;

	opstack_push((&interpreter->current_frame->opstack),"J", &sum);

	return 0;
}

int lsub(t_interpreter *interpreter) {
	long long a, b, sub;
	a = opstack_pop((&interpreter->current_frame->opstack))->data.data_long;
	b = opstack_pop((&interpreter->current_frame->opstack))->data.data_long;
	sub = b - a;

	opstack_push((&interpreter->current_frame->opstack), "J", &sub);

	return 0;
}

int iand(t_interpreter *interpreter){
	int a, b, and;
	a = opstack_pop((&interpreter->current_frame->opstack))->data.data_int;
	b = opstack_pop((&interpreter->current_frame->opstack))->data.data_int;
	and = a & b;

	opstack_push((&interpreter->current_frame->opstack), "I", &and);

	return 0;
}


int ineg(t_interpreter *interpreter){
	int a, neg;
	a = opstack_pop((&interpreter->current_frame->opstack))->data.data_int;
	neg = -a;

	opstack_push((&interpreter->current_frame->opstack), "I", &neg);

	return 0;
}

int ior(t_interpreter *interpreter){
	int a, b, or;
	a = opstack_pop((&interpreter->current_frame->opstack))->data.data_int;
	b = opstack_pop((&interpreter->current_frame->opstack))->data.data_int;
	or = a | b;

	opstack_push((&interpreter->current_frame->opstack), "I", &or);

	return 0;
}

int ixor(t_interpreter *interpreter){
	int a, b, xor;
	a = opstack_pop((&interpreter->current_frame->opstack))->data.data_int;
	b = opstack_pop((&interpreter->current_frame->opstack))->data.data_int;
	xor = a ^ b;

	opstack_push((&interpreter->current_frame->opstack), "I", &xor);

	return 0;
}

int land(t_interpreter *interpreter){
	long long a, b, and;
	a = opstack_pop((&interpreter->current_frame->opstack))->data.data_long;
	b = opstack_pop((&interpreter->current_frame->opstack))->data.data_long;
	and = a & b;

	opstack_push((&interpreter->current_frame->opstack), "J", &and);

	return 0;
}

int lneg(t_interpreter *interpreter){
	long long a, neg;
	a = opstack_pop((&interpreter->current_frame->opstack))->data.data_long;
	neg = -a;

	opstack_push((&interpreter->current_frame->opstack), "J", &neg);

	return 0;
}

int lor(t_interpreter *interpreter){
	long long a, b, or;
	a = opstack_pop((&interpreter->current_frame->opstack))->data.data_long;
	b = opstack_pop((&interpreter->current_frame->opstack))->data.data_long;
	or = a | b;

	opstack_push((&interpreter->current_frame->opstack), "J", &or);

	return 0;
}

int lxor(t_interpreter *interpreter){
	long long a, b, xor;
	a = opstack_pop((&interpreter->current_frame->opstack))->data.data_long;
	b = opstack_pop((&interpreter->current_frame->opstack))->data.data_long;
	xor = a ^ b;

	opstack_push((&interpreter->current_frame->opstack), "J", &xor);

	return 0;
}

int dneg(t_interpreter *interpreter){
	double a, neg;
	a = opstack_pop((&interpreter->current_frame->opstack))->data.data_double;
	neg = -a;

	opstack_push((&interpreter->current_frame->opstack), "D", &neg);

	return 0;
}

int fneg(t_interpreter *interpreter){
	float a, neg;
	a = opstack_pop((&interpreter->current_frame->opstack))->data.data_float;
	neg = -a;

	opstack_push((&interpreter->current_frame->opstack), "F", &neg);

	return 0;
}

int dcmpg(t_interpreter *interpreter){
	double a, b;
	int pushval;
	b = opstack_pop((&interpreter->current_frame->opstack))->data.data_double;
	a = opstack_pop((&interpreter->current_frame->opstack))->data.data_double;
	if (a > b)
		pushval = 1;
	else if (a == b) {
		pushval = 0;
	} else if(a < b) {
		pushval = -1;
	} else {
		pushval = 1;
	}


	opstack_push((&interpreter->current_frame->opstack), "I", &pushval);
	return (0);
}

int dcmpl(t_interpreter *interpreter){
	double a, b;
	int pushval;
	b = opstack_pop((&interpreter->current_frame->opstack))->data.data_double;
	a = opstack_pop((&interpreter->current_frame->opstack))->data.data_double;
	if (a > b)
		pushval = 1;
	else if (a == b) {
		pushval = 0;
	} else if(a < b) {
		pushval = -1;
	} else {
		pushval = -1;
	}


	opstack_push((&interpreter->current_frame->opstack), "I", &pushval);
	return (0);
}


int fcmpg(t_interpreter *interpreter){
	float a, b;
	int pushval;
	b = opstack_pop((&interpreter->current_frame->opstack))->data.data_float;
	a = opstack_pop((&interpreter->current_frame->opstack))->data.data_float;
	if (a > b)
		pushval = 1;
	else if (a == b) {
		pushval = 0;
	} else if(a < b) {
		pushval = -1;
	} else {
		pushval = 1;
	}
	opstack_push((&interpreter->current_frame->opstack), "I", &pushval);
	return (0);
}

int fcmpl(t_interpreter *interpreter){
	float a, b;
	int pushval;
	b = opstack_pop((&interpreter->current_frame->opstack))->data.data_float;
	a = opstack_pop((&interpreter->current_frame->opstack))->data.data_float;
	if (a > b)
		pushval = 1;
	else if (a == b) {
		pushval = 0;
	} else if(a < b) {
		pushval = -1;
	} else {
		pushval = -1;
	}
	opstack_push((&interpreter->current_frame->opstack), "I", &pushval);
	return (0);
}

int lcmp(t_interpreter *interpreter){
	signed long long a, b;
	int pushval;
	b = opstack_pop((&interpreter->current_frame->opstack))->data.data_long;
	a = opstack_pop((&interpreter->current_frame->opstack))->data.data_long;
	if (a > b)
		pushval = 1;
	else {
		if (a == b)
			pushval = 0;
		else
			pushval = -1;
	}
	opstack_push((&interpreter->current_frame->opstack), "J", &pushval);
	return (0);
}

int astore(t_interpreter *interpreter, int pos) {
	transfer_opstack_to_localvar(&(interpreter->current_frame->opstack), &(interpreter->current_frame->local_variables), pos);
	return 0;
}

int ddiv(t_interpreter *interpreter) {
	double a, b, div;
	a = opstack_pop(&(interpreter->current_frame->opstack))->data.data_double;
	b = opstack_pop(&(interpreter->current_frame->opstack))->data.data_double;

	div = b/a;

	opstack_push(&(interpreter->current_frame->opstack), "D", &div);

	return 0;
}

int fdiv(t_interpreter *interpreter) {
	float a, b, div;
	a = opstack_pop(&(interpreter->current_frame->opstack))->data.data_float;
	b = opstack_pop(&(interpreter->current_frame->opstack))->data.data_float;

	div = b/a;

	opstack_push(&(interpreter->current_frame->opstack), "F", &div);

	return 0;
}

int idiv(t_interpreter *interpreter) {
	int a, b, div;
	a = opstack_pop(&(interpreter->current_frame->opstack))->data.data_int;
	b = opstack_pop(&(interpreter->current_frame->opstack))->data.data_int;

	div = b/a;

	opstack_push(&(interpreter->current_frame->opstack), "I", &div);

	return 0;
}

int ldiv_(t_interpreter *interpreter) {
	long long a, b, div;
	a = opstack_pop(&(interpreter->current_frame->opstack))->data.data_long;
	b = opstack_pop(&(interpreter->current_frame->opstack))->data.data_long;

	if (a == 0){
		printf("\nDivisão de long por zero requisitada, retornando valor nulo.\n");
		div = 0;
	} else {
		div = b/a;
	}

	opstack_push(&(interpreter->current_frame->opstack), "J", &div);

	return 0;
}

int lrem(t_interpreter *interpreter) {
	long long a, b, rem;
	a = opstack_pop(&(interpreter->current_frame->opstack))->data.data_long;
	b = opstack_pop(&(interpreter->current_frame->opstack))->data.data_long;

	rem = b%a;

	opstack_push(&(interpreter->current_frame->opstack), "J", &rem);

	return 0;
}

int idiv_(t_interpreter *interpreter) {
	int a, b, div;
	a = opstack_pop(&(interpreter->current_frame->opstack))->data.data_int;
	b = opstack_pop(&(interpreter->current_frame->opstack))->data.data_int;

	if (a == 0){
		printf("Divisão de int por zero!\n");
		exit(1);
	}

	div = b/a;

	opstack_push(&(interpreter->current_frame->opstack), "I", &div);

	return 0;
}

int irem(t_interpreter *interpreter) {
	int a, b, rem;
	a = opstack_pop(&(interpreter->current_frame->opstack))->data.data_int;
	b = opstack_pop(&(interpreter->current_frame->opstack))->data.data_int;

	rem = b%a;

	opstack_push(&(interpreter->current_frame->opstack), "I", &rem);

	return 0;
}


int frem(t_interpreter *interpreter) {
	float a, b, rem;
	b = opstack_pop(&(interpreter->current_frame->opstack))->data.data_float;
	a = opstack_pop(&(interpreter->current_frame->opstack))->data.data_float;
	
	rem = (float) fmod(a,b);
	
	
	opstack_push(&(interpreter->current_frame->opstack), "F", &rem);
	
	return 0;
}

int drem_(t_interpreter *interpreter) {
	double a, b, rem;
	b = opstack_pop(&(interpreter->current_frame->opstack))->data.data_double;
	a = opstack_pop(&(interpreter->current_frame->opstack))->data.data_double;
	
	rem = fmod(a,b);
	
	opstack_push(&(interpreter->current_frame->opstack), "D", &rem);
	
	return 0;
}

int ishl(t_interpreter *interpreter) {
	int a, b, mask, res;
	
	mask = 0x1F;		/* 0x1F, ou 31 seta os 5 primeiros bits como 1 */
	
	b = opstack_pop(&(interpreter->current_frame->opstack))->data.data_int;
	a = opstack_pop(&(interpreter->current_frame->opstack))->data.data_int;
	
	res = a<<(b & mask);
	
	opstack_push(&(interpreter->current_frame->opstack), "I", &res);
	
	return 0;
}

int ishr(t_interpreter *interpreter) {
	int a, b, mask, res, sign;
	
	mask = 0x1F;			/* 0x1F, ou 31 seta os 5 primeiros bits como 1 */
	sign = 0x80000000;		/* Ultimo bit setado como 1 */
	
	b = opstack_pop(&(interpreter->current_frame->opstack))->data.data_int;
	a = opstack_pop(&(interpreter->current_frame->opstack))->data.data_int;
	
	sign = sign & a;		/* pegando o sign */
	res = a>>(b & mask);
	res = res | sign;		/* devolvendo o sign */
	
	opstack_push(&(interpreter->current_frame->opstack), "I", &res);
	
	return 0;
}

int iushr(t_interpreter *interpreter) {
	int a, b, mask, res;
	
	mask = 0x1F;		/* 0x1F, ou 31 seta os 5 primeiros bits como 1 */
	
	b = opstack_pop(&(interpreter->current_frame->opstack))->data.data_int;
	a = opstack_pop(&(interpreter->current_frame->opstack))->data.data_int;
	
	if (a >= 0)
		res = a>>(b & mask);
	else
		res = (a>>(b & mask)) + (2>>(b & mask));
	
	opstack_push(&(interpreter->current_frame->opstack), "I", &res);
	
	return 0;
}

int lshl(t_interpreter *interpreter) {
	long long a, mask, res;
	int b;
	
	mask = 0x3F;		/* 0x3F, ou 63 seta os 6 primeiros bits como 1 */
	
	b = opstack_pop(&(interpreter->current_frame->opstack))->data.data_int;
	a = opstack_pop(&(interpreter->current_frame->opstack))->data.data_long;
	
	res = a<<(b & mask);
	
	opstack_push(&(interpreter->current_frame->opstack), "J", &res);
	
	return 0;
}

int lshr(t_interpreter *interpreter) {
	/*TODO: Arrumar a mascara */
	long long a, mask, res, sign;
	int b;
	
	mask = 0x3F;					/* 0x1F, ou 63 seta os 6 primeiros bits como 1 */
	sign = 0x80000000;				/* Ultimo bit setado como 1 */
	
	b = opstack_pop(&(interpreter->current_frame->opstack))->data.data_int;
	a = opstack_pop(&(interpreter->current_frame->opstack))->data.data_long;
	
	sign = sign & a;		/* pegando o sign */
	res = a>>(b & mask);
	res = res | sign;		/* devolvendo o sign */
	
	opstack_push(&(interpreter->current_frame->opstack), "J", &res);
	
	return 0;
}

int lushr(t_interpreter *interpreter) {
	long long a, mask, res;
	int b;
	
	mask = 0x3F;		/* 0x1F, ou 63 seta os 6 primeiros bits como 1 */
	
	b = opstack_pop(&(interpreter->current_frame->opstack))->data.data_int;
	a = opstack_pop(&(interpreter->current_frame->opstack))->data.data_long;
	
	if (a >= 0)
		res = a>>(b & mask);
	else
		res = (a>>(b & mask)) + (2L>>(b & mask));
	
	opstack_push(&(interpreter->current_frame->opstack), "J", &res);
	
	return 0;
}

int swap(t_interpreter *interpreter){
	t_opstack *a, *b;
	a = opstack_pop(&(interpreter->current_frame->opstack));
	b = opstack_pop(&(interpreter->current_frame->opstack));
	
	opstack_push(&(interpreter->current_frame->opstack),a->type,&(a->data));
	opstack_push(&(interpreter->current_frame->opstack),b->type,&(b->data));
	
	return 0;
}

int dup(t_interpreter *interpreter){
	
	t_opstack *a = opstack_pop((&interpreter->current_frame->opstack));
	if(( *(a->type)=='J' ) || ( *(a->type)=='D' )){
		fprintf(stderr,"Instrucao 'dup' nao permitida para valores 'double' ou 'long'.\n");
		exit(1);
	}
	
	opstack_push_data(&(interpreter->current_frame->opstack),a->type,a->data);
	opstack_push_data(&(interpreter->current_frame->opstack),a->type,a->data);
	
	return 0;
}

int dup2(t_interpreter *interpreter){
	t_opstack *a, *b;
	
	a = opstack_pop((&interpreter->current_frame->opstack));
	if(( *(a->type)=='J' ) || ( *(a->type)=='D' )){
		/*float type e double type*/
		opstack_push_data(&(interpreter->current_frame->opstack),a->type,a->data);
		opstack_push_data(&(interpreter->current_frame->opstack),a->type,a->data);
		return 0;
	}
	
	b = opstack_pop((&interpreter->current_frame->opstack));
	if(( *(b->type)=='J' ) || ( *(b->type)=='D' )){
		fprintf(stderr,"Operacao 'dup2' nao permitida para value2 'float' ou 'double' type.\n");
		exit(1);
	}
	
	opstack_push_data(&(interpreter->current_frame->opstack),b->type,b->data);
	opstack_push_data(&(interpreter->current_frame->opstack),a->type,a->data);
	opstack_push_data(&(interpreter->current_frame->opstack),b->type,b->data);
	opstack_push_data(&(interpreter->current_frame->opstack),a->type,a->data);
	return 0;
	
}

int dup_x1(t_interpreter *interpreter){
	
	t_opstack *a = opstack_pop((&interpreter->current_frame->opstack));
	t_opstack *b = opstack_pop((&interpreter->current_frame->opstack));
	if( ( strchr(b->type,'J')!=NULL ) || ( strchr(b->type,'D')!=NULL ) || ( strchr(a->type,'J')!=NULL ) || ( strchr(a->type,'D')!=NULL ) ){
		fprintf(stderr,"Instrucao 'dup_x1' nao permitida para 'float' ou 'double' type.\n");
		exit(1);
	}
	
	opstack_push_data(&(interpreter->current_frame->opstack),a->type,a->data);
	opstack_push_data(&(interpreter->current_frame->opstack),b->type,b->data);
	opstack_push_data(&(interpreter->current_frame->opstack),a->type,a->data);
	return 0;
}

int dup_x2(t_interpreter *interpreter){
	
	t_opstack *a = opstack_pop((&interpreter->current_frame->opstack));
	if(( strchr(a->type,'J')!=NULL ) || ( strchr(a->type,'D')!=NULL )){
		fprintf(stderr,"Instrucao 'dup_x2' nao permitida para 'double' ou 'long'1.\n");
		exit(1);
	}
	
	t_opstack *b = opstack_pop((&interpreter->current_frame->opstack));
	if(( strchr(b->type,'J')!=NULL ) || ( strchr(b->type,'D')!=NULL )){
		/*form 2*/
		opstack_push_data(&(interpreter->current_frame->opstack),a->type,a->data);
		opstack_push_data(&(interpreter->current_frame->opstack),b->type,b->data);
		opstack_push_data(&(interpreter->current_frame->opstack),a->type,a->data);
		return 0;
	}
	
	t_opstack *c = opstack_pop((&interpreter->current_frame->opstack));
	if(( strchr(c->type,'J')!=NULL ) || ( strchr(c->type,'D')!=NULL )){
		fprintf(stderr,"Instrucao 'dup_x2' nao permitida para 'double' ou 'long'2.\n");
		exit(1);
	}
	
	opstack_push_data(&(interpreter->current_frame->opstack),a->type,a->data);
	opstack_push_data(&(interpreter->current_frame->opstack),c->type,c->data);
	opstack_push_data(&(interpreter->current_frame->opstack),b->type,b->data);
	opstack_push_data(&(interpreter->current_frame->opstack),a->type,a->data);
	
	return 0;
}

int dup2_x1(t_interpreter *interpreter){
	
	t_opstack *a = opstack_pop((&interpreter->current_frame->opstack));
	t_opstack *b = opstack_pop((&interpreter->current_frame->opstack));
	if(( strchr(b->type,'J')!=NULL ) || ( strchr(b->type,'D')!=NULL )){
		fprintf(stderr,"Instrucao 'dup2_x1' nao permitida para value2 of 'double' ou 'float'.\n");
		exit(1);
	}
	if(( strchr(a->type,'J')!=NULL ) || ( strchr(a->type,'D')!=NULL )){
		opstack_push_data(&(interpreter->current_frame->opstack),a->type,a->data);
		opstack_push_data(&(interpreter->current_frame->opstack),b->type,b->data);
		opstack_push_data(&(interpreter->current_frame->opstack),a->type,a->data);
		return 0;
	}
	t_opstack *c = opstack_pop((&interpreter->current_frame->opstack));
	if(( strchr(c->type,'J')!=NULL ) || ( strchr(c->type,'D')!=NULL )){
		fprintf(stderr,"Instrucao 'dup2_x1' nao permitida para value3 ou 'double' ou 'float'.\n");
		exit(1);
	}
	
	opstack_push_data(&b,b->type,b->data);
	opstack_push_data(&a,a->type,a->data);
	opstack_push_data(&c,c->type,c->data);
	opstack_push_data(&b,b->type,b->data);
	opstack_push_data(&a,a->type,a->data);
	
	return 0;
}

int dup2_x2(t_interpreter *interpreter){
	
	t_opstack *a = opstack_pop((&interpreter->current_frame->opstack));
	t_opstack *b = opstack_pop((&interpreter->current_frame->opstack));
	t_opstack *c, *d;
	if( (( strchr(a->type,'J')!=NULL ) || ( strchr(a->type,'D')!=NULL )) ){
		
		if( ((strchr(b->type,'J')!=NULL) || (strchr(b->type,'D')!=NULL)) ){
			opstack_push_data(&(interpreter->current_frame->opstack),a->type,a->data);
			opstack_push_data(&(interpreter->current_frame->opstack),b->type,b->data);
			opstack_push_data(&(interpreter->current_frame->opstack),a->type,a->data);
			return 0;
		}
		
		c = opstack_pop((&interpreter->current_frame->opstack));
		if(( strchr(c->type,'J')!=NULL ) || ( strchr(c->type,'D')!=NULL )){
			fprintf(stderr,"Instrucao 'dup2_x2' nao permitida para value3 de 'double' ou 'float' e value1 de 'double' ou 'float'.\n");
			exit(1);
		}
		
		opstack_push_data(&(interpreter->current_frame->opstack),a->type,a->data);
		opstack_push_data(&(interpreter->current_frame->opstack),c->type,c->data);
		opstack_push_data(&(interpreter->current_frame->opstack),b->type,b->data);
		opstack_push_data(&(interpreter->current_frame->opstack),a->type,a->data);
		return 0;
		
	}
	
	if(( strchr(b->type,'J')!=NULL ) || ( strchr(b->type,'D')!=NULL )){
		fprintf(stderr,"Operacao 'dup2_x2' nao permitida para value1 of type 1 e value2 d tipo 'float' ou 'double'.\n");
		exit(1);
	}
	
	c = opstack_pop((&interpreter->current_frame->opstack));
	if(( strchr(c->type,'J')!=NULL ) || ( strchr(c->type,'D')!=NULL )){
		opstack_push_data(&(interpreter->current_frame->opstack),b->type,b->data);
		opstack_push_data(&(interpreter->current_frame->opstack),a->type,a->data);
		opstack_push_data(&(interpreter->current_frame->opstack),c->type,c->data);
		opstack_push_data(&(interpreter->current_frame->opstack),b->type,b->data);
		opstack_push_data(&(interpreter->current_frame->opstack),a->type,a->data);
		return 0;
	}
	
	d = opstack_pop((&interpreter->current_frame->opstack));
	if(( strchr(d->type,'J')!=NULL ) || ( strchr(d->type,'D')!=NULL )){
		fprintf(stderr,"Operacao 'dup2_x2' nao permitida para value4 do tipo 'float' ou 'double'.\n");
		exit(1);
	}
	
	opstack_push_data(&(interpreter->current_frame->opstack),b->type,b->data);
	opstack_push_data(&(interpreter->current_frame->opstack),a->type,a->data);
	opstack_push_data(&(interpreter->current_frame->opstack),d->type,d->data);
	opstack_push_data(&(interpreter->current_frame->opstack),c->type,c->data);
	opstack_push_data(&(interpreter->current_frame->opstack),b->type,b->data);
	opstack_push_data(&(interpreter->current_frame->opstack),a->type,a->data);
	
	return 0;
}

int goto_(t_interpreter *interpreter, short int branchoffset){
	interpreter->current_frame->pc += branchoffset - 3;

	return 0;
}

int goto_w(t_interpreter *interpreter, int branchoffset){
	interpreter->current_frame->pc += branchoffset - 5;
	
	return 0;
}

int jsr(t_interpreter *interpreter, short int branchoffset){
	opstack_push(&interpreter->current_frame->opstack,"returnAddress",interpreter->current_frame->pc);
	interpreter->current_frame->pc += branchoffset;
	interpreter->current_frame->pc_address += branchoffset;
	
	return 0;
}

int jsr_w(t_interpreter *interpreter, int branchoffset){
	opstack_push(&interpreter->current_frame->opstack,"returnAddress",interpreter->current_frame->pc);
	interpreter->current_frame->pc += branchoffset;
	interpreter->current_frame->pc_address += branchoffset;
	
	return 0;
}


int iinc(t_interpreter *interpreter, int index, int const_){
	
	(interpreter->current_frame->local_variables)[index].data.data_int += const_;
	
	return 0;
}

int newarray(t_interpreter *interpreter, int type) {
	int tamanho;
	t_array_list *array;
	tamanho = opstack_pop(&(interpreter->current_frame->opstack))->data.data_int;

	switch(type) {
	case 4:
		array = array_allocate("Z", 1, tamanho);
		opstack_push(&(interpreter->current_frame->opstack), "[Z", array);
		break;
	case 5:
		array = array_allocate("C", 1, tamanho);
		opstack_push(&(interpreter->current_frame->opstack), "[C", array);
		break;
	case 6:
		array = array_allocate("F", 1, tamanho);
		opstack_push(&(interpreter->current_frame->opstack), "[F", array);
		break;
	case 7:
		array = array_allocate("D", 1, tamanho);
		opstack_push(&(interpreter->current_frame->opstack), "[D", array);
		break;

	case 8:
		array = array_allocate("B", 1, tamanho);
		opstack_push(&(interpreter->current_frame->opstack), "[B", array);
		break;
	case 9:
		array = array_allocate("S", 1, tamanho);
		opstack_push(&(interpreter->current_frame->opstack), "[S", array);
		break;
	case 10:
		array = array_allocate("I", 1, tamanho);
		opstack_push(&(interpreter->current_frame->opstack), "[I", array);
		break;
	case 11:
		array = array_allocate("J", 1, tamanho);
		opstack_push(&(interpreter->current_frame->opstack), "[J", array);
		break;
	default:
		fprintf(stderr,"Problema em 'anewarray', tipo de array nao reconhecido\n");
		exit(1);
		break;
	}

	return 0;
}

int aaload(t_interpreter *interpreter) {
	int index;
	t_array_list *array;
	void *ref;
	index = opstack_pop(&(interpreter->current_frame->opstack))->data.data_int;
	array = (t_array_list*)opstack_pop(&(interpreter->current_frame->opstack))->data.data_reference;

	ref = array_get_value(&array, index)->data.data_reference;

	opstack_push(&(interpreter->current_frame->opstack), array_get_value(&array, index)->type, ref);
	return 0;
}

int iaload(t_interpreter *interpreter) {
	int integer, index;
	t_array_list *array;

	index = opstack_pop(&(interpreter->current_frame->opstack))->data.data_int;
	array = (t_array_list*)opstack_pop(&(interpreter->current_frame->opstack))->data.data_reference;

	integer = array_get_value(&array, index)->data.data_int;

	opstack_push(&(interpreter->current_frame->opstack), "I", &integer);

	return 0;
}

int aastore(t_interpreter *interpreter) {
	int index;
	void *valor;
	char *type;
	t_opstack *opvalor;
	t_array_list *array;

	opvalor = opstack_pop(&(interpreter->current_frame->opstack));
	valor = opvalor->data.data_reference;
	type = opvalor->type;
	index = opstack_pop(&(interpreter->current_frame->opstack))->data.data_int;
	array = (t_array_list*)opstack_pop(&(interpreter->current_frame->opstack))->data.data_reference;

	array_add_value(&array, index, type, opvalor->data.data_reference);

	return 0;
}

int iastore(t_interpreter *interpreter) {
	int valor, index;
	t_array_list *array;


	valor = opstack_pop(&(interpreter->current_frame->opstack))->data.data_int;
	index = opstack_pop(&(interpreter->current_frame->opstack))->data.data_int;
	array = (t_array_list*)opstack_pop(&(interpreter->current_frame->opstack))->data.data_reference;

	array_add_value(&array, index, "I", &valor);

	return 0;
}


int if_acmpeq(t_interpreter *interpreter, int branchoffset){
	void *a, *b;
	a = opstack_pop(&(interpreter->current_frame->opstack))->data.data_reference;
	b = opstack_pop(&(interpreter->current_frame->opstack))->data.data_reference;
	
	if (a == b){
		interpreter->current_frame->pc += branchoffset -3;

		interpreter->current_frame->pc_address += branchoffset -3;
	}
	
	return 0;
}

int if_acmpne(t_interpreter *interpreter, int branchoffset){
	void *a, *b;
	a = opstack_pop(&(interpreter->current_frame->opstack))->data.data_reference;
	b = opstack_pop(&(interpreter->current_frame->opstack))->data.data_reference;
	
	if (a != b){
		interpreter->current_frame->pc += branchoffset -3;

		interpreter->current_frame->pc_address += branchoffset -3;
	}
	
	return 0;
}

int if_icmpeq(t_interpreter *interpreter, int branchoffset){
	int a, b;
	b = opstack_pop(&(interpreter->current_frame->opstack))->data.data_int;
	a = opstack_pop(&(interpreter->current_frame->opstack))->data.data_int;
	
	if (a == b){
		interpreter->current_frame->pc += branchoffset -3;

		interpreter->current_frame->pc_address += branchoffset -3;
	}
	
	return 0;
}

int if_icmpne(t_interpreter *interpreter, int branchoffset){
	int a, b;
	b = opstack_pop(&(interpreter->current_frame->opstack))->data.data_int;
	a = opstack_pop(&(interpreter->current_frame->opstack))->data.data_int;
	
	if (a != b){
		interpreter->current_frame->pc += branchoffset -3;

		interpreter->current_frame->pc_address += branchoffset -3;
	}
	
	return 0;
}

int if_icmplt(t_interpreter *interpreter, int branchoffset){
	int a, b;
	b = opstack_pop(&(interpreter->current_frame->opstack))->data.data_int;
	a = opstack_pop(&(interpreter->current_frame->opstack))->data.data_int;
	
	if (a < b){
		interpreter->current_frame->pc += branchoffset -3;

		interpreter->current_frame->pc_address += branchoffset -3;
	}
	
	return 0;
}

int if_icmple(t_interpreter *interpreter, int branchoffset){
	int a, b;
	b = opstack_pop(&(interpreter->current_frame->opstack))->data.data_int;
	a = opstack_pop(&(interpreter->current_frame->opstack))->data.data_int;
	
	if (a <= b){
		interpreter->current_frame->pc += branchoffset -3;

		interpreter->current_frame->pc_address += branchoffset -3;
	}
	
	return 0;
}

int if_icmpgt(t_interpreter *interpreter, int branchoffset){
	int a, b;
	b = opstack_pop(&(interpreter->current_frame->opstack))->data.data_int;
	a = opstack_pop(&(interpreter->current_frame->opstack))->data.data_int;
	
	if (a > b){
		interpreter->current_frame->pc += branchoffset -3;

		interpreter->current_frame->pc_address += branchoffset -3;
	}
	
	return 0;
}

int if_icmpge(t_interpreter *interpreter, int branchoffset){
	int a, b;
	b = opstack_pop(&(interpreter->current_frame->opstack))->data.data_int;
	a = opstack_pop(&(interpreter->current_frame->opstack))->data.data_int;
	
	if (a >= b){
		interpreter->current_frame->pc += branchoffset -3;

		interpreter->current_frame->pc_address += branchoffset -3;
	}
	
	return 0;
}

int ifeq(t_interpreter *interpreter, int branchoffset){
	int a;
	a = opstack_pop(&(interpreter->current_frame->opstack))->data.data_int;
	
	if (a == 0){
		interpreter->current_frame->pc += branchoffset -3;

		interpreter->current_frame->pc_address += branchoffset -3;
	}
	
	return 0;
}

int ifne(t_interpreter *interpreter, int branchoffset){
	int a;
	a = opstack_pop(&(interpreter->current_frame->opstack))->data.data_int;
	
	if (a != 0){
		interpreter->current_frame->pc += branchoffset -3;
		interpreter->current_frame->pc_address += branchoffset -3;
	}
	
	return 0;
}

int iflt(t_interpreter *interpreter, int branchoffset){
	int a;
	a = opstack_pop(&(interpreter->current_frame->opstack))->data.data_int;
	
	if (a < 0){
		interpreter->current_frame->pc += branchoffset -3;

		interpreter->current_frame->pc_address += branchoffset -3;
	}
	
	return 0;
}

int ifle(t_interpreter *interpreter, int branchoffset){
	int a;
	a = opstack_pop(&(interpreter->current_frame->opstack))->data.data_int;
	
	if (a <= 0){
		interpreter->current_frame->pc += branchoffset -3;

		interpreter->current_frame->pc_address += branchoffset -3;
	}
	
	return 0;
}

int ifgt(t_interpreter *interpreter, int branchoffset){
	int a;
	a = opstack_pop(&(interpreter->current_frame->opstack))->data.data_int;
	
	if (a > 0){
		interpreter->current_frame->pc += branchoffset -3;

		interpreter->current_frame->pc_address += branchoffset -3;
	}
	
	return 0;
}

int ifge(t_interpreter *interpreter, int branchoffset){
	int a;
	a = opstack_pop(&(interpreter->current_frame->opstack))->data.data_int;
	
	if (a >= 0){
		interpreter->current_frame->pc +=branchoffset -3;
		interpreter->current_frame->pc_address += branchoffset -3;
	}
	
	return 0;
}

int ifnonnull(t_interpreter *interpreter, int branchoffset){
	void *a;
	a = opstack_pop(&(interpreter->current_frame->opstack))->data.data_reference;
	
	if (a != NULL){
		interpreter->current_frame->pc += branchoffset -3;

		interpreter->current_frame->pc_address += branchoffset -3;
	}
	
	return 0;
}

int ifnull(t_interpreter *interpreter, int branchoffset){
	void *a;
	a = opstack_pop(&(interpreter->current_frame->opstack))->data.data_reference;

	if (a == NULL){
		interpreter->current_frame->pc += branchoffset -3;

		interpreter->current_frame->pc_address += branchoffset -3;
	}
	
	return 0;
}

int faload(t_interpreter *interpreter) {
	int index;
	float valor;
	t_array_list *array;
	
	index = opstack_pop(&(interpreter->current_frame->opstack))->data.data_int;
	array = (t_array_list*)opstack_pop(&(interpreter->current_frame->opstack))->data.data_reference;
	
	valor = array_get_value(&array, index)->data.data_float;
	
	opstack_push(&(interpreter->current_frame->opstack), "F", &valor);
	
	return 0;
}

int fastore(t_interpreter *interpreter) {
	int index;
	float valor;
	t_array_list *array;
	
	
	valor = opstack_pop(&(interpreter->current_frame->opstack))->data.data_float;
	index = opstack_pop(&(interpreter->current_frame->opstack))->data.data_int;
	array = (t_array_list*)opstack_pop(&(interpreter->current_frame->opstack))->data.data_reference;
	
	array_add_value(&array, index, "F", &valor);
	
	return 0;
}

int dastore(t_interpreter *interpreter) {
	int index;
	double valor;
	t_array_list *array;
	
	
	valor = opstack_pop(&(interpreter->current_frame->opstack))->data.data_double;
	index = opstack_pop(&(interpreter->current_frame->opstack))->data.data_int;
	array = (t_array_list*)opstack_pop(&(interpreter->current_frame->opstack))->data.data_reference;
	
	array_add_value(&array, index, "D", &valor);
	
	return 0;
}

int daload(t_interpreter *interpreter) {
	int index;
	double valor;
	t_array_list *array;
	
	index = opstack_pop(&(interpreter->current_frame->opstack))->data.data_int;
	array = (t_array_list*)opstack_pop(&(interpreter->current_frame->opstack))->data.data_reference;
	
	valor = array_get_value(&array, index)->data.data_double;
	
	opstack_push(&(interpreter->current_frame->opstack), "D", &valor);
	
	return 0;
}

int castore(t_interpreter *interpreter) {
	int index;
	char valor;
	t_array_list *array;
	
	
	valor = opstack_pop(&(interpreter->current_frame->opstack))->data.data_char;
	index = opstack_pop(&(interpreter->current_frame->opstack))->data.data_int;
	array = (t_array_list*)opstack_pop(&(interpreter->current_frame->opstack))->data.data_reference;
	
	array_add_value(&array, index, "C", &valor);
	
	return 0;
}

int caload(t_interpreter *interpreter) {
	int index;
	char valor;
	t_array_list *array;
	
	index = opstack_pop(&(interpreter->current_frame->opstack))->data.data_int;
	array = (t_array_list*)opstack_pop(&(interpreter->current_frame->opstack))->data.data_reference;
	
	valor = array_get_value(&array, index)->data.data_char;
	
	opstack_push(&(interpreter->current_frame->opstack), "C", &valor);
	
	return 0;
}

int lastore(t_interpreter *interpreter) {
	int index;
	long long valor;
	t_array_list *array;
	
	
	valor = opstack_pop(&(interpreter->current_frame->opstack))->data.data_long;
	index = opstack_pop(&(interpreter->current_frame->opstack))->data.data_int;
	array = (t_array_list*)opstack_pop(&(interpreter->current_frame->opstack))->data.data_reference;
	
	array_add_value(&array, index, "J", &valor);
	
	return 0;
}

int laload(t_interpreter *interpreter) {
	int index;
	long long valor;
	t_array_list *array;
	
	index = opstack_pop(&(interpreter->current_frame->opstack))->data.data_int;
	array = (t_array_list*)opstack_pop(&(interpreter->current_frame->opstack))->data.data_reference;
	
	valor = array_get_value(&array, index)->data.data_long;
	
	opstack_push(&(interpreter->current_frame->opstack), "J", &valor);
	
	return 0;
}

int sastore(t_interpreter *interpreter) {
	int index;
	short valor;
	t_array_list *array;
	
	
	valor = opstack_pop(&(interpreter->current_frame->opstack))->data.data_short;
	index = opstack_pop(&(interpreter->current_frame->opstack))->data.data_int;
	array = (t_array_list*)opstack_pop(&(interpreter->current_frame->opstack))->data.data_reference;
	
	array_add_value(&array, index, "S", &valor);
	
	return 0;
}

int saload(t_interpreter *interpreter) {
	int index;
	short valor;
	t_array_list *array;

	index = opstack_pop(&(interpreter->current_frame->opstack))->data.data_int;
	array = (t_array_list*)opstack_pop(&(interpreter->current_frame->opstack))->data.data_reference;
	
	valor = array_get_value(&array, index)->data.data_short;
	
	opstack_push(&(interpreter->current_frame->opstack), "S", &valor);

	return 0;
}


int baload(t_interpreter *interpreter) {
	int index, val_int, val_char;
	t_array_list *array_ref;
	int zero = 0;
	int array_size = 0;

	index = opstack_pop(&(interpreter->current_frame->opstack))->data.data_int;
	array_ref = (t_array_list*)opstack_pop(&(interpreter->current_frame->opstack))->data.data_reference;

	while (array_ref->type[array_size] == '[' ){
		array_size++;
	}
	
	if((array_ref->type)[array_size] == 'B') {
		val_char = array_get_value(&(array_ref), index)->data.data_byte;
		val_int = (int)val_char;
		opstack_push(&(interpreter->current_frame->opstack), "I", &val_int);
	} else if((array_ref->type)[array_size] == 'Z') {
		val_char = array_get_value(&(array_ref), index)->data.data_boolean;
		val_int = (zero | val_char);
		opstack_push(&(interpreter->current_frame->opstack), "I", &val_int);
	} else {
		fprintf(stderr,"Problema em 'baload', tipo incorreto de dados passado.\n");
		exit(1);
	}


	return 0;
}

int bastore(t_interpreter *interpreter) {
	int value, index;
	t_array_list *array_ref;
	char value_char;
	int mask;
	int array_size = 0;
	mask = 0x00000001;
	
	value = opstack_pop(&(interpreter->current_frame->opstack))->data.data_int;
	index = opstack_pop(&(interpreter->current_frame->opstack))->data.data_int;
	array_ref = (t_array_list*)opstack_pop(&(interpreter->current_frame->opstack))->data.data_reference;

	while (array_ref->type[array_size] == '[' ){
		array_size++;
	}
	
	if((array_ref->type)[array_size] == 'B') {
		value_char = (int)value;
		array_add_value(&array_ref, index, "B", &value_char);
	} else if((array_ref->type)[array_size] == 'Z') {
		value_char = (value & mask);
		array_add_value(&array_ref, index, "Z", &value_char);
	} else {
		fprintf(stderr,"Problema em 'bastore', tipo incorreto de dados.\n");
		exit(1);
	}

	return 0;
}

int arraylength(t_interpreter *interpreter){
	/*TODO arraylength pode dar problema*/
	t_array_list *array;
	int length;
	
	array = (t_array_list*)opstack_pop(&(interpreter->current_frame->opstack))->data.data_reference;
	
	length = array_count(array);
	
	opstack_push(&(interpreter->current_frame->opstack), "I", &length);
	
	return 0;
}

/* TODO: Verificar isso aqui! */
int return0(t_interpreter *interpreter){
	int return_v;
	return_v = jumpback(interpreter, 0);
	
	return return_v;
}

int return1(t_interpreter *interpreter){
	int return_v;
	return_v = jumpback(interpreter, 1);
	

	return return_v;
}

int athrow(t_interpreter *interpreter){
	void *objectref;
	objectref = opstack_pop(&(interpreter->current_frame->opstack))->data.data_reference;
	
	if (objectref == NULL){
		fprintf(stderr,"Erro em 'athrow', NullPointerException encontrada.\n");
		exit(1);
	}
	return1(interpreter);
	
	return 0;
}

int ret(t_interpreter *interpreter, int index){
	t_local_variable_list localvar = (interpreter->current_frame->local_variables)[index];
	if ( (localvar.type)[0] != 'r'){
		fprintf(stderr,"Endereco de retorno invalido, tipo errado.\n");
		exit(1);
	}
	interpreter->current_frame->pc = localvar.data.data_return_adress;
	return 0;
}

int multianewarray(t_interpreter *interpreter, int index, int dimensions) {
	char *typex, *p1, *p2, *type;
	int count, i;
	int *tamanhos, *pi;
	t_array_list *arr;
	
	if((signed int)find_tag_info(interpreter->current_frame->class_file, index) == 7) {
		typex = find_class_info(interpreter->current_frame->class_file, index);
		p1 = typex;
		count = 0;
		while(*p1 != '[') {
			p1++;
			count++;
		}
		type = calloc(strlen(typex) - count + 2, sizeof(char));
		p2 = type;
		while(*p1 != '\0') {
			*p2 = *p1;
			p1++;
			p2++;
		}
		
		p2 = '\0';
		

		tamanhos = calloc(dimensions, sizeof(int));
		pi = tamanhos + dimensions -1 ;
		
		for(i = 0; i < dimensions; i ++ ) {
			*pi = opstack_pop(&(interpreter->current_frame->opstack))->data.data_int ;
			pi--;
		}


		arr = allocate_array__(type, dimensions, tamanhos);
		/* TODO: arrumar o type abaixo */
		opstack_push(&(interpreter->current_frame->opstack), "[", arr);
		
		
	} else {
		fprintf(stderr,"Erro em multinewarray, tipo inapropriado.\n");
		exit(1);
	}
	
	return 0;
}

int anewarray(t_interpreter *interpreter, int valor){
	int count;
	t_array_list *array;
	char *type;
	
	count = opstack_pop((&interpreter->current_frame->opstack))->data.data_int;	
	type = find_class_info(interpreter->current_frame->class_file,valor);
	
	type++;
	if(count == 0) {
		array = NULL;
	} else {
		array = array_allocate(type,1,count);
	}
	
	

	opstack_push(&(interpreter->current_frame->opstack), "[", array);
	
	return 0;
}

int wide(t_interpreter *interpreter,int opcode, int index){
	switch (opcode) {
		case ILOAD:
			iload(interpreter, index);
			break;
		case FLOAD:
			fload(interpreter, index);
			break;
		case ALOAD:
			aload(interpreter, index);
			break;
			break;
		case LLOAD:
			lload(interpreter, index);
			break;
		case DLOAD:
			dload(interpreter, index);
			break;
		case ISTORE:
			istore(interpreter, index);
			break;
		case FSTORE:
			fstore(interpreter, index);
			break;
		case ASTORE:
			astore(interpreter, index);
			break;
		case LSTORE:
			lstore(interpreter, index);
			break;
		case DSTORE:
			dstore(interpreter, index);
			break;
		case RET:
			ret(interpreter, index);
			break;
		case IINC:
			iinc(interpreter, index, read_u2(interpreter->current_frame));
		default:
			fprintf(stderr,"Erro na instrucao wide, Opcode invalido para wide.\n");
			exit(1);
			break;
	}
	
	return 0;
}

int new_(t_interpreter *interpreter, int index) {
	char *classname;
	t_class_file *class_file;
	t_object *object;
	
	if( (signed int)find_tag_info(interpreter->current_frame->class_file,index)!=7 ){
		fprintf(stderr,"Erro na instrucao 'new'.\n");
		exit(1);
	}
	
	classname = find_class_info(interpreter->current_frame->class_file, index);
	
	
	/* ajustando para o caso da StringBuffer */
	if((strcmp(classname, "java/lang/StringBuffer") == 0 || strcmp(classname, "java/lang/StringBuilder") == 0)) {
		char * strvazia;
		strvazia = calloc(1, sizeof(char));
		*strvazia = '\0';
		opstack_push(&(interpreter->current_frame->opstack), "[C", strvazia);
		return 0;
	}
	
	class_file = leitura_class_file(interpreter, classname);
	
	object = instanciate_object(class_file, interpreter);
	
	
	opstack_push(&(interpreter->current_frame->opstack), "L", object);
	
	return 0;
	
}


int putfield(t_interpreter *interpreter, int index) {
	t_field_about *field_about;
	t_object *obj;
	t_opstack *opstack_value;
	
	field_about = find_field_info(interpreter->current_frame->class_file, index);
	
	opstack_value = opstack_pop(&(interpreter->current_frame->opstack));
	obj = (t_object*)opstack_pop(&(interpreter->current_frame->opstack))->data.data_reference;
	
	object_set_field_data(obj, field_about->fieldName, opstack_value->type, opstack_value->data);
	
	return 0;
	
}

int getfield(t_interpreter *interpreter, int index) {
	t_object *obj;
	t_field_about *field_about;
	t_field *field_got;
	
	field_about = find_field_info(interpreter->current_frame->class_file, index);
	obj = (t_object*)opstack_pop(&(interpreter->current_frame->opstack))->data.data_reference;
	

	field_got = object_get_field(obj, field_about->fieldName);
	
	opstack_push_data(&(interpreter->current_frame->opstack), field_got->type, field_got->data);
	
	
	return 0;
}

int invokestatic(t_interpreter *interpreter, int index) {
	t_method_about *method_about;
	int arg_count;

	method_about = find_method_info(interpreter->current_frame->class_file, index);

	arg_count = arguments_count(method_about->type);

	if(strcmp(method_about->className, "Object") == 0 &&
			strcmp(method_about->methodName, "<init>") == 0) {
		return 0;
	}

	jump(interpreter, method_about->className, method_about->methodName, method_about->type, arg_count);


	return 0;
}

int invokespecial(t_interpreter *interpreter, int index) {
	t_method_about *method_about;
	int arg_count;
	
	method_about = find_method_info(interpreter->current_frame->class_file, index);
	
	if((strcmp(method_about->className, "java/lang/StringBuffer") == 0 || strcmp(method_about->className, "java/lang/StringBuilder") == 0) &&
	   strcmp(method_about->methodName, "<init>") == 0) {
		opstack_pop(&(interpreter->current_frame->opstack));
		return 0;
	}
	
	arg_count = arguments_count(method_about->type) + 1;
	
	jump(interpreter, method_about->className, method_about->methodName, method_about->type, arg_count);
	
	
	return 0;
}

int checkcast(t_interpreter *interpreter, int index) {
	t_opstack *ref;
	t_object *obj;
	t_array_list *arr;
	ref = opstack_pop(&(interpreter->current_frame->opstack));
	if ( (ref->type[0] != '[') || (ref->type[0] != 'L') ){
		fprintf(stderr,"Falha em 'checkcast', objeto na pilha inadequado.\n");
		exit(0);
	}
	if (ref->data.data_reference == NULL){
		return 0;
	}
	int tag = (signed int)find_tag_info(interpreter->current_frame->class_file,index);
	if (tag != 7){
		fprintf(stderr,"Falha em 'checkcast', tipo do objeto na pilha inadequado.\n");
		exit(0);
	} else {
		char *T = find_class_info(interpreter->current_frame->class_file,index);
		if (ref->type[0] == 'L'){
			obj = (t_object *) ref->data.data_reference;
			if (strcmp(T,obj->classPath) != 0){
				printf("Falha em 'checkcast', class types not compatible.\n");
				exit(1);
			}
		/* TODO: Checar tipo de subclasse  */
		} else 	if (ref->type[0] == '[') {
			arr = (t_array_list *) ref->data.data_reference;
			/* TODO: Descobrir como est o type e arrumar isso aqui!  */
			if (strcmp(T,arr->type) != 0){
				printf("Falha em 'checkcast', array class type duuh?.\n");
				exit(1);
			}
			/* TODO: Arrumar o resto daqui tambm  */
		}
	}
	opstack_push(&interpreter->current_frame->opstack,ref->type,&(ref->data));
	return 0;
}
int instanceof(t_interpreter *interpreter, int index){
	t_opstack *objref;
	t_object *obj;
	t_array_list *arr;
	int result = 0;
	char *S, *T;

	/*se objeto popado eh null, sai com erro*/
	objref = opstack_pop((&interpreter->current_frame->opstack))->data.data_reference;
	if ( objref == NULL ){
		opstack_push(&interpreter->current_frame->opstack, "I", &result);
		return 0;
	}

	/*se nao for instancia de classe, sai com erro*/
	if( (signed int)find_tag_info(interpreter->classfile_list->classfile,index)!=7 ){
		printf("Erro em 'instanceof'. Nao eh instancia de classe!\n");
		exit(1);
	}

	/*se resolver, pusha int result = 1 na opstack, senao pusha 0*/
	/*testa se nome eh igual a classe*/
	T = find_class_info(interpreter->classfile_list->classfile,index);
	S = objref->type;
	if( objref->type[0]=='L' ){
		obj = (t_object *)objref->data.data_reference;
		if( strcmp(T,obj->classPath) ){
			printf("Erro: T é da mesma classe de S.\n");
			opstack_push(&interpreter->current_frame->opstack, "I", &result);
		} /*TODO: testar se obj é subclass of T*/

	} else if ( objref->type[0]=='[' ){
		arr = (t_array_list *)objref->data.data_reference;
		if( strcmp(T, arr->type) ){
			printf("Erro: T é um array.\n");
			opstack_push(&interpreter->current_frame->opstack, "I", &result);
		}
		/*TODO: testar se T é um objeto
		 * ou
		 * Se T é um array
		 */

	}

	opstack_push(&interpreter->current_frame->opstack, "I", &result);
	return 0;
}

int putstatic(t_interpreter *interpreter, int index) {
	t_field_about *field_about;
	t_opstack *opstack_value;
	t_classfile_list *p1, *p3;
	t_classfile_list *superclasses_list, *p2;
	int error, error2;

	field_about = find_field_info(interpreter->current_frame->class_file, index);

	opstack_value = opstack_pop(&(interpreter->current_frame->opstack));

	p1 = interpreter->classfile_list;
	while(p1 != NULL) {
		if(strcmp(p1->class_path, field_about->className) == 0) {
			error = object_set_field_data(p1->static_fields, field_about->fieldName, opstack_value->type, opstack_value->data);
			if(error == -1) {
				superclasses_list = get_super_classes(p1->classfile, interpreter);
				p2 = superclasses_list;
				while(p2 != NULL) {
					p3 = interpreter->classfile_list;
					while(p3 != NULL) {
						if(strcmp(p3->class_path, p2->class_path) == 0) {
							error2 = object_set_field_data(p3->static_fields, field_about->fieldName, opstack_value->type, opstack_value->data);
							if(error2 != -1) return 0;
						}
						p3 = p3->next;
					}
					p2 = p2->next;
				}
			}
			return 0;
		}
		p1 = p1->next;
	}

	fprintf(stderr,"Falha em 'putstatic'. Nao acho o elemento buscado na lista de classes.");
	exit(1);

	return 0;
}

int getstatic(t_interpreter *interpreter, int cp_index) {
	t_field_about *field_about;
	t_field *field_got;
	t_classfile_list *p1, *p3;
	t_classfile_list *superclasses_list, *p2;


	field_about = find_field_info(interpreter->current_frame->class_file, cp_index);

	if(strcmp(field_about->className, "java/lang/System") == 0 &&
			strcmp(field_about->fieldName, "out") == 0 &&
			strcmp(field_about->type, "Ljava/io/PrintStream;") == 0) {
		/* se for a printstream, adiciona uma referencia nula. sera usada depois */
		opstack_push(&(interpreter->current_frame->opstack), "#", NULL);

	} else {
		p1 = interpreter->classfile_list;
		while(p1 != NULL) {
			if(strcmp(p1->class_path, field_about->className) == 0) {
				field_got = object_get_field(p1->static_fields, field_about->fieldName);
				if(field_got != NULL) {
					opstack_push_data(&(interpreter->current_frame->opstack), field_got->type, field_got->data);
					return 0;
				} else {
					superclasses_list = get_super_classes(p1->classfile, interpreter);
					p2 = superclasses_list;
					while(p2 != NULL) {
						p3 = interpreter->classfile_list;
						while(p3 != NULL) {
							if(strcmp(p3->class_path, p2->class_path) == 0) {
								field_got = object_get_field(p3->static_fields, field_about->fieldName);
								if(field_got != NULL) {
									opstack_push_data(&(interpreter->current_frame->opstack), field_got->type, field_got->data);
									return 0;
								}
							}
							p3 = p3->next;
						}
						p2 = p2->next;
					}
				}


			}
			p1 = p1->next;
		}
		fprintf(stderr,"Algum problema com o 'getstatic'.\n");
		exit(1);
	}

	return 0;
}


int tableswitch(t_interpreter *interpreter, u4 highbyte, u4 lowbyte, u4 defaultbyte, int padbytes){
	
	t_opstack * objref;
	int case_value;
	
	u4 switchsize = (highbyte - lowbyte + 1);
	u4 offsets[switchsize];
	int i;

	if ( switchsize < 0 ){
		fprintf(stderr,"Erro na 'tableswitch', lowbyte maior que highbyte.\n");
		exit(1);
	}
	
	for (i = 0; i < switchsize; i++) {
		offsets[i] = (u4) read_u4(interpreter->current_frame);
	}
	
	objref = opstack_pop(&(interpreter->current_frame->opstack));
	case_value = objref->data.data_int;
	
	if ( objref->type[0] != 'I'){
		printf("Falha em 'tableswitch', elemento de switch diferente de inteiro.\n");
		exit(1);
	} else {
		/* Recuando para o endereco original da funcao */
		interpreter->current_frame->pc += - ( 3*sizeof(u4) + switchsize*sizeof(u4) + 1 + padbytes);
		interpreter->current_frame->pc_address += - ( 3*sizeof(u4) + switchsize*sizeof(u4) + 1 + padbytes);
		if ( ( case_value > (int)highbyte) || ( case_value < (int)lowbyte ) ){
			interpreter->current_frame->pc += defaultbyte;
			interpreter->current_frame->pc_address += defaultbyte;
		} else {
			interpreter->current_frame->pc += offsets[objref->data.data_int - lowbyte];
			interpreter->current_frame->pc_address += offsets[objref->data.data_int - lowbyte];
		}
	}
	
	return 0;
}


int lookupswitch(t_interpreter *interpreter, u4 npairs, u4 defaultbyte, int padbytes){
	t_opstack * objref;
	int foundInPairs = 0;
	int case_value;
	
	u4 offsets[npairs][2];
	unsigned long int i;
	

	for (i = 0; i < npairs; i++) {
		offsets[i][1] = (u4) read_u4(interpreter->current_frame);
		offsets[i][2] = (u4) read_u4(interpreter->current_frame);
	}
	
	objref = opstack_pop(&(interpreter->current_frame->opstack));
	case_value = objref->data.data_int;
	
	
	if ( objref->type[0] != 'I'){
		printf("Falha em 'tableswitch', elemento de switch diferente de inteiro.\n");
		exit(1);
	} else {
		/* Recuando para o endereco original da funcao */
		interpreter->current_frame->pc += - ( 2*sizeof(u4) + npairs*sizeof(u4)*2 + 1 + padbytes);
		interpreter->current_frame->pc_address += - ( 3*sizeof(u4) + npairs*sizeof(u4)*2 + 1 + padbytes);
		for (i = 0; i < npairs ; i++) {
			if (offsets[i][1] == case_value)
				foundInPairs = i + 1;
		}
		
		if ( foundInPairs == 0 ){
			interpreter->current_frame->pc += defaultbyte;
			interpreter->current_frame->pc_address += defaultbyte;
		} else {
			interpreter->current_frame->pc += offsets[foundInPairs - 1][2];
			interpreter->current_frame->pc_address += offsets[foundInPairs - 1][2];
		}
	}
	
	return 0;
}
