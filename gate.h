#ifndef __GATE_H__
#define __GATE_H__

#define AND_GATE 1
#define OR_GATE 2
#define INVERT_GATE 3
#define XOR_GATE 4
#define NOR_GATE 5

typedef struct gate G;
typedef struct gate G_t;
typedef int (*LG_proc)(int, int);

#include "wire.h"

G* mk_and(W* input1, W* input2, W* output);
G* mk_or(W* input1, W* input2, W* output);
G* mk_invert(W* input, W* output);
G* mk_xor(W* input1, W* input2, W* output);
G* mk_nor(W* input1, W* input2, W* output);

int and_logic(int i_1, int i_2);
int or_logic(int i_1, int i_2);
int invert_logic(int i_1, int i_2);
int xor_logic(int i_1, int i_2);
int nor_logic(int i_1, int i_2);

struct gate{
	int gate_type;
	W* input_1;
	W* input_2;
	W* result;
	LG_proc logic_process;
};

#endif
