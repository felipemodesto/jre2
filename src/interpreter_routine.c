/**
 * @brief interpreter_routine
 * Possui funcioes para tratamento da rotina do interpretador, tais como
 * inicializacao do interpretador, execucao da iteracao, e leitura
 * de elementos do PC.
 *
 * @version 1.0
 *
 * @date 29/09/2009
 *
 **/

#include "interpreter_structs.h"
#include "class_reader.h"
#include "class_printer.h"
#include "interpreter_basic.h"
#include "instructions.h"
#include <string.h>

/**
 * Le uma instrucao do PC e incrementa.
 * @param frame variavel do frame
 */
u1 read_instruction(t_frame *frame) {

	u1 instruction;
	instruction = *(frame->pc);
	(frame->pc)++;
	(frame->pc_address)++;

	return instruction;
}

/**
 * Le um byte do PC.
 * @param frame a variavel do frame atual
 */
u1 read_u1(t_frame *frame) {
	u1 value;
	value = *(frame->pc);
	(frame->pc)++;
	(frame->pc_address)++;

	return value;
}

/**
 * Le dois bytes do PC.
 * @param frame a variavel do frame atual
 */
short int read_u2(t_frame *frame) {
	unsigned char high, low;
	int value;
	high = *(frame->pc);

	low = *(frame->pc +1);
	(frame->pc)++;
	(frame->pc)++;

	frame->pc_address += 2;

	value = (signed short int)((((unsigned short int)high << sizeof(u1)*8)) | (unsigned short int)low);
	
	return value;
}

/**
 * Le quatro bytes do PC.
 * @param frame a variavel do frame atual
 */
int read_u4(t_frame *frame) {
	unsigned char high, mid_high, mid_low, low;
	long int value;
	high = *(frame->pc);
	(frame->pc)++;
	mid_high = *(frame->pc);
	(frame->pc)++;
	mid_low = *(frame->pc);
	(frame->pc)++;
	low = *(frame->pc);
	(frame->pc)++;
	
	frame->pc_address += 4;
	
    value = (((signed int)high << 3*sizeof(u1)*8) | ((signed int)mid_high << 2*sizeof(u1)*8) | ((signed int)mid_low << 1*sizeof(u1)*8) | (signed int)low);	
	return value;
}

/**
 * Executa uma iteracao. Responsavel por fazer um loop infinito
 * das iteracoes. Sai apenas quando houver um return 0 na funcao,
 * ou seja, quando houver uma chamada de metodo RETURN e a pilha
 * de frames estiver vazia.
 *
 * @param interpreter a variavel do itnerpretador
 */
int execute_iteration(t_interpreter *interpreter) {
	u1 valor_u1;
	short int valor_u2;
	u4 valor_u4;
	
	
	unsigned char instruction;
	while(1) {
		
		
		
		instruction = (unsigned char)read_instruction(interpreter->current_frame);
		switch(instruction) {
			case ACONST_NULL:
				aconst_null(interpreter);
				break;
			case ICONST_M1:
				iconst(interpreter, -1);
				break;
			case ICONST_0:
				iconst(interpreter, 0);
				break;
			case ICONST_1:
				iconst(interpreter, 1);
				break;
			case ICONST_2:
				iconst(interpreter, 2);
				break;
			case ICONST_3:
				iconst(interpreter, 3);
				break;
			case ICONST_4:
				iconst(interpreter, 4);
				break;
			case ICONST_5:
				iconst(interpreter, 5);
				break;
			case LCONST_0:
				lconst(interpreter, 0);
				break;
			case LCONST_1:
				lconst(interpreter, 1);
				break;
			case FCONST_0:
				fconst(interpreter, 0);
				break;
			case FCONST_1:
				fconst(interpreter, 1);
				break;
			case FCONST_2:
				fconst(interpreter, 2);
				break;
			case DCONST_0:
				dconst(interpreter, 0);
				break;
			case DCONST_1:
				dconst(interpreter, 1);
				break;
				
			case BIPUSH:
				valor_u1 = read_u1(interpreter->current_frame);
				bipush(interpreter, valor_u1);
				break;
			case SIPUSH:
				valor_u2 = read_u2(interpreter->current_frame);
				sipush(interpreter, valor_u2);
				break;
			case LDC:
				valor_u1 = read_u1(interpreter->current_frame);
				ldc(interpreter, (unsigned char)valor_u1);
				break;
			case LDC_W:
				valor_u2 = read_u2(interpreter->current_frame);
				ldc(interpreter, (unsigned short int)valor_u2);
				break;
			case LDC2_W:
				/* obs.: usando a mesma do LDC_W, pois tambem pusha long e double */
				valor_u2 = read_u2(interpreter->current_frame);
				ldc(interpreter, valor_u2);
				break;
			case LLOAD:
				valor_u1 = read_u1(interpreter->current_frame);
				lload(interpreter, valor_u1);
				break;
			case LLOAD_0:
				lload(interpreter, 0);
				break;
			case LLOAD_1:
				lload(interpreter, 1);
				break;
			case LLOAD_2:
				lload(interpreter, 2);
				break;
			case LLOAD_3:
				lload(interpreter, 3);
				break;
			case ILOAD:
				valor_u1 = read_u1(interpreter->current_frame);
				iload(interpreter, valor_u1);
				break;
			case FLOAD:
				valor_u1 = read_u1(interpreter->current_frame);
				fload(interpreter, valor_u1);
				break;
			case DLOAD:
				valor_u1 = read_u1(interpreter->current_frame);
				dload(interpreter, valor_u1);
				break;
			case DLOAD_0:
				dload(interpreter, 0);
				break;
			case DLOAD_1:
				dload(interpreter, 1);
				break;
			case DLOAD_2:
				dload(interpreter, 2);
				break;
			case DLOAD_3:
				dload(interpreter, 3);
				break;
			case FLOAD_0:
				fload(interpreter, 0);
				break;
			case FLOAD_1:
				fload(interpreter, 1);
				break;
			case FLOAD_2:
				fload(interpreter, 2);
				break;
			case FLOAD_3:
				fload(interpreter, 3);
				break;
			case ILOAD_0:
				iload(interpreter, 0);
				break;
			case ILOAD_1:
				iload(interpreter, 1);
				break;
			case ILOAD_2:
				iload(interpreter, 2);
				break;
			case ILOAD_3:
				iload(interpreter, 3);
				break;
			case ISTORE:
				valor_u1 = read_u1(interpreter->current_frame);
				istore(interpreter, valor_u1);
				break;
			case FSTORE:
				valor_u1 = read_u1(interpreter->current_frame);
				fstore(interpreter, valor_u1);
				break;
			case FSTORE_0:
				fstore(interpreter, 0);
				break;
			case FSTORE_1:
				fstore(interpreter, 1);
				break;
			case FSTORE_2:
				fstore(interpreter, 2);
				break;
			case FSTORE_3:
				fstore(interpreter, 3);
				break;
			case LSTORE:
				valor_u1 = read_u1(interpreter->current_frame);
				lstore(interpreter, valor_u1);
				break;
			case LSTORE_0:
				lstore(interpreter, 0);
				break;
			case LSTORE_1:
				lstore(interpreter, 1);
				break;
			case LSTORE_2:
				lstore(interpreter, 2);
				break;
			case LSTORE_3:
				lstore(interpreter, 3);
				break;
			case DSTORE:
				valor_u1 = read_u1(interpreter->current_frame);
				dstore(interpreter, valor_u1);
				break;
			case DSTORE_0:
				dstore(interpreter, 0);
				break;
			case DSTORE_1:
				dstore(interpreter, 1);
				break;
			case DSTORE_2:
				dstore(interpreter, 2);
				break;
			case DSTORE_3:
				dstore(interpreter, 3);
				break;
			case ISTORE_0:
				istore(interpreter, 0);
				break;
			case ISTORE_1:
				istore(interpreter, 1);
				break;
			case ISTORE_2:
				istore(interpreter, 2);
				break;
			case ISTORE_3:
				istore(interpreter, 3);
				break;
			case IADD:
				iadd(interpreter);
				break;
			case I2D:
				i2d(interpreter);
				break;
			case L2I:
				l2i(interpreter);
				break;
			case F2L:
				f2l(interpreter);
				break;
			case D2I:
				d2i(interpreter);
				break;
			case ALOAD:
				valor_u1 = read_u1(interpreter->current_frame);
				aload(interpreter, valor_u1);
				break;
			case ALOAD_0:
				aload(interpreter, 0);
				break;
			case ALOAD_1:
				aload(interpreter, 1);
				break;
			case ALOAD_2:
				aload(interpreter, 2);
				break;
			case ALOAD_3:
				aload(interpreter, 3);
				break;
			case POP:
				pop(interpreter);
				break;
			case POP2:
				pop2(interpreter);
				break;
			case D2F:
				d2f(interpreter);
				break;
			case D2L:
				d2l(interpreter);
				break;
			case F2D:
				f2d(interpreter);
				break;
			case F2I:
				f2i(interpreter);
				break;
			case I2B:
				i2b(interpreter);
				break;
			case I2C:
				i2c(interpreter);
				break;
			case I2F:
				i2f(interpreter);
				break;
			case I2L:
				i2l(interpreter);
				break;
			case I2S:
				i2s(interpreter);
				break;
			case L2D:
				l2d(interpreter);
				break;
			case L2F:
				l2f(interpreter);
				break;
			case DMUL:
				dmul(interpreter);
				break;
			case FMUL:
				fmul(interpreter);
				break;
			case IMUL:
				imul(interpreter);
				break;
			case LMUL:
				lmul(interpreter);
				break;
			case INVOKEVIRTUAL:
				valor_u2 = read_u2(interpreter->current_frame);
				invokevirtual(interpreter, valor_u2);
				break;
			case GETSTATIC:
				valor_u2 = read_u2(interpreter->current_frame);
				getstatic(interpreter, valor_u2);
				break;
			case DADD:
				dadd(interpreter);
				break;
			case DSUB:
				dsub(interpreter);
				break;
			case FADD:
				fadd(interpreter);
				break;
			case FSUB:
				fsub(interpreter);
				break;
			case ISUB:
				isub(interpreter);
				break;
			case LADD:
				ladd(interpreter);
				break;
			case LSUB:
				lsub(interpreter);
				break;
			case IAND:
				iand(interpreter);
				break;
			case IOR:
				ior(interpreter);
				break;
			case IXOR:
				ixor(interpreter);
				break;
			case INEG:
				ineg(interpreter);
				break;
			case LAND:
				land(interpreter);
				break;
			case LOR:
				lor(interpreter);
				break;
			case LXOR:
				lxor(interpreter);
				break;
			case LNEG:
				lneg(interpreter);
				break;
			case DNEG:
				dneg(interpreter);
				break;
			case ASTORE:
				valor_u1 = read_u1(interpreter->current_frame);
				astore(interpreter, valor_u1);
				break;
			case ASTORE_0:
				astore(interpreter, 0);
				break;
			case ASTORE_1:
				astore(interpreter, 1);
				break;
			case ASTORE_2:
				astore(interpreter, 2);
				break;
			case ASTORE_3:
				astore(interpreter, 3);
				break;
			case LDIV:
				ldiv_(interpreter);
				break;
				
			case LCMP:
				lcmp(interpreter);
				break;
			case FCMPL:
				fcmpl(interpreter);
				break;
			case FCMPG:
				fcmpg(interpreter);
				break;
				
			case FREM:
				frem(interpreter);
				break;
			case DREM:
				drem_(interpreter);
				break;
			case LREM:
				frem(interpreter);
				break;				
			case ISHL:
				ishl(interpreter);
				break;
			case ISHR:
				ishr(interpreter);
				break;
			case IUSHR:
				iushr(interpreter);
				break;
			case LSHL:
				lshl(interpreter);
				break;
			case LSHR:
				lshr(interpreter);
				break;
			case LUSHR:
				lushr(interpreter);
				break;
			case SWAP:
				swap(interpreter);
				break;				
				
			case DUP:
				dup(interpreter);
				break;
			case DUP_X1:
				dup_x1(interpreter);
				break;
			case DUP_X2:
				dup_x2(interpreter);
				break;
			case DUP2:
				dup2(interpreter);
				break;
			case DUP2_X1:
				dup2_x1(interpreter);
				break;
			case DUP2_X2:
				dup2_x2(interpreter);
				break;
				
			case GOTO:
				valor_u2 = read_u2(interpreter->current_frame);
				goto_(interpreter,valor_u2);
				break;
			case GOTO_W:
				valor_u4 = read_u4(interpreter->current_frame);
				goto_w(interpreter,valor_u4);
				break;
				
			case JSR:
				valor_u2 = read_u2(interpreter->current_frame);
				jsr(interpreter,valor_u2);
				break;
			case JSR_W:
				valor_u4 = read_u4(interpreter->current_frame);
				jsr_w(interpreter,valor_u4);
				break;
				
			case IINC:
				valor_u1 = read_u1(interpreter->current_frame);
				iinc(interpreter , valor_u1, read_u1(interpreter->current_frame) );
				break;
			case NEWARRAY:
				valor_u1 = read_u1(interpreter->current_frame);
				newarray(interpreter, valor_u1);
				break;
			case AALOAD:
				aaload(interpreter);
				break;
			case IALOAD:
				iaload(interpreter);
				break;
			case AASTORE:
				aastore(interpreter);
				break;
			case IASTORE:
				iastore(interpreter);
				break;
			case IDIV:
				idiv_(interpreter);
				break;
			case IREM:
				irem(interpreter);
				break;
				
				
			case IF_ACMPEQ:
				valor_u2 = read_u2(interpreter->current_frame);
				if_acmpeq(interpreter, valor_u2);
				break;
			case IF_ACMPNE:
				valor_u2 = read_u2(interpreter->current_frame);
				if_acmpne(interpreter, valor_u2);
				break;
			case IF_ICMPEQ:
				valor_u2 = read_u2(interpreter->current_frame);
				if_icmpeq(interpreter, valor_u2);
				break;
			case IF_ICMPNE:
				valor_u2 = read_u2(interpreter->current_frame);
				if_icmpne(interpreter, valor_u2);
				break;
			case IF_ICMPLT:
				valor_u2 = read_u2(interpreter->current_frame);
				if_icmplt(interpreter, valor_u2);
				break;
			case IF_ICMPLE:
				valor_u2 = read_u2(interpreter->current_frame);
				if_icmple(interpreter, valor_u2);
				break;
			case IF_ICMPGT:
				valor_u2 = read_u2(interpreter->current_frame);
				if_icmpgt(interpreter, valor_u2);
				break;
			case IF_ICMPGE:
				valor_u2 = read_u2(interpreter->current_frame);
				if_icmpge(interpreter, valor_u2);
				break;
			case IFEQ:
				valor_u2 = read_u2(interpreter->current_frame);
				ifeq(interpreter, valor_u2);
				break;
			case IFNE:
				valor_u2 = read_u2(interpreter->current_frame);
				ifne(interpreter, valor_u2);
				break;
			case IFLT:
				valor_u2 = read_u2(interpreter->current_frame);
				iflt(interpreter, valor_u2);
				break;
			case IFLE:
				valor_u2 = read_u2(interpreter->current_frame);
				ifle(interpreter, valor_u2);
				break;
			case IFGT:
				valor_u2 = read_u2(interpreter->current_frame);
				ifgt(interpreter, valor_u2);
				break;
			case IFGE:
				valor_u2 = read_u2(interpreter->current_frame);
				ifge(interpreter, valor_u2);
				break;
				
			case BALOAD:
				baload(interpreter);
				break;
			case BASTORE:
				bastore(interpreter);
				break;
			case CALOAD:
				caload(interpreter);
				break;
			case CASTORE:
				castore(interpreter);
				break;
			case LALOAD:
				laload(interpreter);
				break;
			case LASTORE:
				lastore(interpreter);
				break;
			case DASTORE:
				dastore(interpreter);
				break;
			case DALOAD:
				daload(interpreter);
				break;
			case SALOAD:
				saload(interpreter);
				break;
			case SASTORE:
				sastore(interpreter);
				break;
			case FALOAD:
				faload(interpreter);
				break;
			case FASTORE:
				fastore(interpreter);
				break;
				
			case ARRAYLENGTH:
				arraylength(interpreter);
				break;
				
			case ANEWARRAY:
				valor_u2 = read_u2(interpreter->current_frame);
				anewarray(interpreter,valor_u2);
				break;
				
			case MULTIANEWARRAY:
				valor_u2 = read_u2(interpreter->current_frame);
				valor_u1 = read_u1(interpreter->current_frame);
				multianewarray(interpreter, valor_u2, valor_u1);
				break;
				
			case RETURN:
				if(return0(interpreter) == -1) return 0;
				break;
			case IRETURN:
				return1(interpreter);
				break;
			case LRETURN:
				return1(interpreter);
				break;
			case DRETURN:
				return1(interpreter);
				break;
			case FRETURN:
				return1(interpreter);
				break;
			case ARETURN:
				return1(interpreter);
				break;
				
			case ATHROW:
				athrow(interpreter);
				break;
			case NOP:
				fprintf(stderr,"Instrução NOP executado.\n");
				break;
			default:
				fprintf(stderr,"Instrucao nao reconhecida: %d\n", (unsigned char)instruction);
				exit(1);
				break;
				
			case NEW:
				valor_u2 = read_u2(interpreter->current_frame);
				new_(interpreter, valor_u2);
				break;
			case PUTFIELD:
				valor_u2 = read_u2(interpreter->current_frame);
				putfield(interpreter, valor_u2);
				break;
			case GETFIELD:
				valor_u2 = read_u2(interpreter->current_frame);
				getfield(interpreter, valor_u2);
				break;
				
			case WIDE:
				valor_u1 = read_u1(interpreter->current_frame);
				valor_u2 = read_u2(interpreter->current_frame);
				wide(interpreter,valor_u1,valor_u2);
				break;
				
			case FDIV:
				fdiv(interpreter);
				break;
			case DDIV:
				ddiv(interpreter);
				break;
			case FNEG:
				fneg(interpreter);
				break;
				
			case DCMPG:
				dcmpg(interpreter);
				break;
			case DCMPL:
				dcmpl(interpreter);
				break;
				
			case RET:
				valor_u1 = read_u1(interpreter->current_frame);
				ret(interpreter, (int)valor_u1);
				break;
			case INVOKESTATIC:
				valor_u2 = read_u2(interpreter->current_frame);
				invokestatic(interpreter, valor_u2);
				break;
			case INVOKESPECIAL:
				valor_u2 = read_u2(interpreter->current_frame);
				invokespecial(interpreter, valor_u2);
				break;
			case CHECKCAST:
				valor_u2 = read_u2(interpreter->current_frame);
				checkcast(interpreter, valor_u2);
				break;
			case INSTANCEOF:
				valor_u2 = read_u2(interpreter->current_frame);
				instanceof(interpreter, valor_u2);
				break;
			case PUTSTATIC:
				valor_u2 = read_u2(interpreter->current_frame);
				putstatic(interpreter, valor_u2);
				break;
			case IFNONNULL:
				valor_u2 = read_u2(interpreter->current_frame);
				ifnonnull(interpreter, valor_u2);
				break;
			case IFNULL:
				valor_u2 = read_u2(interpreter->current_frame);
				ifnull(interpreter, valor_u2);
				break;
				
			case TABLESWITCH: {
				int bytepads;
				u4 highbyte, lowbyte;
				u4 defaultbyte;
				bytepads = (4 - (interpreter->current_frame->pc - interpreter->current_frame->pc_inicial)%4)%4;
				interpreter->current_frame->pc += bytepads;
				defaultbyte = read_u4(interpreter->current_frame);
				lowbyte = read_u4(interpreter->current_frame);
				highbyte = read_u4(interpreter->current_frame);
				tableswitch(interpreter,highbyte,lowbyte,defaultbyte, bytepads);
			}
				break;
				
			case LOOKUPSWITCH: {
				int bytepads;
				u4 npairs;
				u2 defaultbyte;
				bytepads = (4 - (interpreter->current_frame->pc - interpreter->current_frame->pc_inicial)%4)%4;
				interpreter->current_frame->pc += bytepads;
				defaultbyte = read_u4(interpreter->current_frame);
				npairs = read_u4(interpreter->current_frame);
				lookupswitch(interpreter,npairs,defaultbyte, bytepads);
			}
				break;
				
				
		}
		
		
		/* TODO: execucao */
		
	}
}

/**
 * Inicia um interpretador em uma determinada classe, e em um determinado metodo.
 * @param class_file_name nome da classe a iniciar o interpretador
 * @param methodName nome do metodo a iniciar o interpretador
 * @param descriptor descritor do metodo a iniciar o interpretador
 */
int start_interpreter(char *class_file_name, char *methodName, char *descriptor) {
	t_interpreter *interpreter;

	interpreter = malloc(sizeof(t_interpreter));
	interpreter->classfile_list = NULL;
	interpreter->current_frame = NULL;
	interpreter->frame_stack = NULL;

	jump(interpreter, class_file_name, methodName, descriptor, 0);

	interpreter->current_frame->opstack = NULL;
	
	execute_iteration(interpreter);
	
	return 0;
}
