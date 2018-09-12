/*
 * instructions.h
 *
 *  Created on: 09/12/2009
 *
 */

#ifndef INSTRUCTIONS_H_
#define INSTRUCTIONS_H_

#include "interpreter_basic.h"
#include "interpreter_structs.h"

#define NOP 0
#define ACONST_NULL 1
#define ICONST_M1 2
#define ICONST_0 3
#define ICONST_1 4
#define ICONST_2 5
#define ICONST_3 6
#define ICONST_4 7
#define ICONST_5 8
#define LCONST_0 9
#define LCONST_1 10
#define FCONST_0 11
#define FCONST_1 12
#define FCONST_2 13
#define DCONST_0 14
#define DCONST_1 15
#define BIPUSH 16
#define SIPUSH 17
#define LDC 18
#define LDC_W 19
#define LDC2_W 20
#define ILOAD 21
#define LLOAD 22
#define FLOAD 23
#define DLOAD 24
#define ALOAD 25
#define ILOAD_0 26
#define ILOAD_1 27
#define ILOAD_2 28
#define ILOAD_3 29
#define LLOAD_0 30
#define LLOAD_1 31
#define LLOAD_2 32
#define LLOAD_3 33
#define FLOAD_0 34
#define FLOAD_1 35
#define FLOAD_2 36
#define FLOAD_3 37
#define DLOAD_0 38
#define DLOAD_1 39
#define DLOAD_2 40
#define DLOAD_3 41
#define ALOAD_0 42
#define ALOAD_1 43
#define ALOAD_2 44
#define ALOAD_3 45
#define IALOAD 46
#define LALOAD 47
#define FALOAD 48
#define DALOAD 49
#define AALOAD 50
#define BALOAD 51
#define CALOAD 52
#define SALOAD 53
#define ISTORE 54
#define LSTORE 55
#define FSTORE 56
#define DSTORE 57
#define ASTORE 58
#define ISTORE_0 59
#define ISTORE_1 60
#define ISTORE_2 61
#define ISTORE_3 62
#define LSTORE_0 63
#define LSTORE_1 64
#define LSTORE_2 65
#define LSTORE_3 66
#define FSTORE_0 67
#define FSTORE_1 68
#define FSTORE_2 69
#define FSTORE_3 70
#define DSTORE_0 71
#define DSTORE_1 72
#define DSTORE_2 73
#define DSTORE_3 74
#define ASTORE_0 75
#define ASTORE_1 76
#define ASTORE_2 77
#define ASTORE_3 78
#define IASTORE 79
#define LASTORE 80
#define FASTORE 81
#define DASTORE 82
#define AASTORE 83
#define BASTORE 84
#define CASTORE 85
#define SASTORE 86
#define POP 87
#define POP2 88
#define DUP 89
#define DUP_X1 90
#define DUP_X2 91
#define DUP2 92
#define DUP2_X1 93
#define DUP2_X2 94
#define SWAP 95
#define IADD 96
#define LADD 97
#define FADD 98
#define DADD 99
#define ISUB 100
#define LSUB 101
#define FSUB 102
#define DSUB 103
#define IMUL 104
#define LMUL 105
#define FMUL 106
#define DMUL 107
#define IDIV 108
#define LDIV 109
#define FDIV 110
#define DDIV 111
#define IREM 112
#define LREM 113
#define FREM 114
#define DREM 115
#define INEG 116
#define LNEG 117
#define FNEG 118
#define DNEG 119
#define ISHL 120
#define LSHL 121
#define ISHR 122
#define LSHR 123
#define IUSHR 124
#define LUSHR 125
#define IAND 126
#define LAND 127
#define IOR 128
#define LOR 129
#define IXOR 130
#define LXOR 131
#define IINC 132
#define I2L 133
#define I2F 134
#define I2D 135
#define L2I 136
#define L2F 137
#define L2D 138
#define F2I 139
#define F2L 140
#define F2D 141
#define D2I 142
#define D2L 143
#define D2F 144
#define I2B 145
#define I2C 146
#define I2S 147
#define LCMP 148
#define FCMPL 149
#define FCMPG 150
#define DCMPL 151
#define DCMPG 152
#define IFEQ 153
#define IFNE 154
#define IFLT 155
#define IFGE 156
#define IFGT 157
#define IFLE 158
#define IF_ICMPEQ 159
#define IF_ICMPNE 160
#define IF_ICMPLT 161
#define IF_ICMPGE 162
#define IF_ICMPGT 163
#define IF_ICMPLE 164
#define IF_ACMPEQ 165
#define IF_ACMPNE 166
#define GOTO 167
#define JSR 168
#define RET 169
#define TABLESWITCH 170
#define LOOKUPSWITCH 171
#define IRETURN 172
#define LRETURN 173
#define FRETURN 174
#define DRETURN 175
#define ARETURN 176
#define RETURN 177
#define GETSTATIC 178
#define PUTSTATIC 179
#define GETFIELD 180
#define PUTFIELD 181
#define INVOKEVIRTUAL 182
#define INVOKESPECIAL 183
#define INVOKESTATIC 184
#define INVOKEINTERFACE 185
#define XXXUNUSEDXXX1 186
#define NEW 187
#define NEWARRAY 188
#define ANEWARRAY 189
#define ARRAYLENGTH 190
#define ATHROW 191
#define CHECKCAST 192
#define INSTANCEOF 193
#define MONITORENTER 194
#define MONITOREXIT 195
#define WIDE 196
#define MULTIANEWARRAY 197
#define IFNULL 198
#define IFNONNULL 199
#define GOTO_W 200
#define JSR_W 201


int bipush(t_interpreter *interpreter, int valor);
int aconst_null(t_interpreter *interpreter);
int istore(t_interpreter *interpreter, int pos);


int iload(t_interpreter *interpreter, int pos);

int iadd(t_interpreter *interpreter);

int i2d(t_interpreter *interpreter);

int dstore(t_interpreter *interpreter, int pos);

int ldc(t_interpreter *interpreter, int cp_index);

int fstore(t_interpreter *interpreter, int pos);

int fload(t_interpreter *interpreter, int pos);

int f2l(t_interpreter *interpreter);

int lstore(t_interpreter *interpreter, int pos);


int iconst(t_interpreter *interpreter, int value);

int dload(t_interpreter *interpreter, int pos);

int d2i(t_interpreter *interpreter);
int lload(t_interpreter *interpreter, int pos);

int l2i(t_interpreter *interpreter);

int lconst(t_interpreter *interpreter, long long value);

int fconst(t_interpreter *interpreter, float value);

int dconst(t_interpreter *interpreter, double value);

int sipush(t_interpreter *interpreter, int value);

int aload(t_interpreter *interpreter, int pos);

int pop(t_interpreter *interpreter);

int pop2(t_interpreter *interpreter);

int d2f(t_interpreter *interpreter);

int d2l(t_interpreter *interpreter);

int f2d(t_interpreter *interpreter);

int f2i(t_interpreter *interpreter);

int i2b(t_interpreter *interpreter);

int i2c(t_interpreter *interpreter);

int i2f(t_interpreter *interpreter);

int i2l(t_interpreter *interpreter);

int i2s(t_interpreter *interpreter);

int l2d(t_interpreter *interpreter);

int l2f(t_interpreter *interpreter);

int dmul(t_interpreter *interpreter);

int fmul(t_interpreter *interpreter);

int imul(t_interpreter *interpreter);

int lmul(t_interpreter *interpreter);

int invokevirtual(t_interpreter *interpreter, int cp_index);

int getstatic(t_interpreter *interpreter, int cp_index);

int dadd(t_interpreter *interpreter);
int dsub(t_interpreter *interpreter);
int fadd(t_interpreter *interpreter);
int fsub(t_interpreter *interpreter);
int isub(t_interpreter *interpreter);
int ladd(t_interpreter *interpreter);
int lsub(t_interpreter *interpreter);

int iand(t_interpreter *interpreter);
int ineg(t_interpreter *interpreter);
int ior(t_interpreter *interpreter);
int ixor(t_interpreter *interpreter);
int land(t_interpreter *interpreter);
int lneg(t_interpreter *interpreter);
int lor(t_interpreter *interpreter);
int lxor(t_interpreter *interpreter);
int dneg(t_interpreter *interpreter);
int fneg(t_interpreter *interpreter);

int astore(t_interpreter *interpreter, int pos);
int ldiv_(t_interpreter *interpreter);
int lrem(t_interpreter *interpreter);

int fcmpg(t_interpreter *interpreter);
int fcmpl(t_interpreter *interpreter);
int lcmp(t_interpreter *interpreter);
int frem(t_interpreter *interpreter);
int drem_(t_interpreter *interpreter);
int ishl(t_interpreter *interpreter);
int ishr(t_interpreter *interpreter);
int iushr(t_interpreter *interpreter);
int lshl(t_interpreter *interpreter);
int lshr(t_interpreter *interpreter);
int lushr(t_interpreter *interpreter);
int swap(t_interpreter *interpreter);

int dup(t_interpreter *interpreter);
int dup2(t_interpreter *interpreter);
int dup_x1(t_interpreter *interpreter);
int dup2_x2(t_interpreter *interpreter);
int dup_x2(t_interpreter *interpreter);
int dup2_x1(t_interpreter *interpreter);

int goto_(t_interpreter *interpreter, short int branchoffset);
int goto_w(t_interpreter *interpreter, int branchoffset);

int jsr(t_interpreter *interpreter, short int branchoffset);
int jsr_w(t_interpreter *interpreter, int branchoffset);

int iinc(t_interpreter *interpreter, int index, int const_);

int newarray(t_interpreter *interpreter, int type);
int aaload(t_interpreter *interpreter);
int iaload(t_interpreter *interpreter);
int aastore(t_interpreter *interpreter);
int iastore(t_interpreter *interpreter);

int idiv_(t_interpreter *interpreter);

int irem(t_interpreter *interpreter);

int if_acmpeq(t_interpreter *interpreter, int branchoffset);
int if_acmpne(t_interpreter *interpreter, int branchoffset);
int if_icmpeq(t_interpreter *interpreter, int branchoffset);
int if_icmpne(t_interpreter *interpreter, int branchoffset);
int if_icmplt(t_interpreter *interpreter, int branchoffset);
int if_icmple(t_interpreter *interpreter, int branchoffset);
int if_icmpgt(t_interpreter *interpreter, int branchoffset);
int if_icmpge(t_interpreter *interpreter, int branchoffset);
int ifeq(t_interpreter *interpreter, int branchoffset);
int ifne(t_interpreter *interpreter, int branchoffset);
int iflt(t_interpreter *interpreter, int branchoffset);
int ifle(t_interpreter *interpreter, int branchoffset);
int ifgt(t_interpreter *interpreter, int branchoffset);
int ifge(t_interpreter *interpreter, int branchoffset);
int ifnonnull(t_interpreter *interpreter, int branchoffset);
int ifnull(t_interpreter *interpreter, int branchoffset);

int fastore(t_interpreter *interpreter);
int faload(t_interpreter *interpreter);
int daload(t_interpreter *interpreter);
int dastore(t_interpreter *interpreter);
int caload(t_interpreter *interpreter);
int castore(t_interpreter *interpreter);
int laload(t_interpreter *interpreter);
int lastore(t_interpreter *interpreter);
int saload(t_interpreter *interpreter);
int sastore(t_interpreter *interpreter);
int baload(t_interpreter *interpreter);
int bastore(t_interpreter *interpreter);

int arraylength(t_interpreter *interpreter);

int return0(t_interpreter *interpreter);
int return1(t_interpreter *interpreter);

int athrow(t_interpreter *interpreter);

int ret(t_interpreter *interpreter, int index);

int multianewarray(t_interpreter *interpreter, int index, int dimensions);

int anewarray(t_interpreter *interpreter, int valor);

int wide(t_interpreter *interpreter,int opcode, int index);

int new_(t_interpreter *interpreter, int index);
int putfield(t_interpreter *interpreter, int index);
int getfield(t_interpreter *interpreter, int index);

int fdiv(t_interpreter *interpreter);
int ddiv(t_interpreter *interpreter);
int fneg(t_interpreter *interpreter);

int dcmpl(t_interpreter *interpreter);
int dcmpg(t_interpreter *interpreter);

int checkcast(t_interpreter *interpreter, int index);
int instanceof(t_interpreter *interpreter, int index);

int invokestatic(t_interpreter *interpreter, int index);
int invokespecial(t_interpreter *interpreter, int index);
int putstatic(t_interpreter *interpreter, int index);

int lookupswitch(t_interpreter *interpreter, u4 npairs, u4 defaultbyte, int padbytes);
int tableswitch(t_interpreter *interpreter, u4 highbyte, u4 lowbyte, u4 defaultbyte, int padbytes);
#endif /* INSTRUCTIONS_H_ */
