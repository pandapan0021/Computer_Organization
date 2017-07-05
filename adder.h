#ifndef __ADDER_H__
#define __ADDER_H__

#include "wire.h"
#include "gate.h"
#include "task.h"
#include <stdlib.h>
#include <stdio.h>

/***************************************************************
 * REFACTOR FUNDATION FUNCTION
 * ************************************************************/
typedef struct _buffer     BUF_t;
typedef struct _half_adder H_ADDER_t;
typedef struct _full_adder F_ADDER_t;
typedef struct _complement COMPLEMENT_t;
typedef struct _adder      ADDER_t;

BUF_t* new_buffer(int);
void set_new_buffer(TASK_q*, BUF_t*, int*, int);
void read_new_buffer(BUF_t*, int);
void copy_new_buffer(TASK_q*, BUF_t*, BUF_t*, int);
void zero_new_buffer(BUF_t*);
int buf_to_signed_i(BUF_t*);
H_ADDER_t* new_half_adder(W*, W*, W*, W*);
F_ADDER_t* new_full_adder(W*, W*, W*, W*, W*);
COMPLEMENT_t* new_complement(BUF_t*, BUF_t*, W*, int);
ADDER_t* new_adder(BUF_t*, BUF_t*, BUF_t*, W*, W*, int);

struct _half_adder{
	W* A_in;
	W* B_in;
	W* Sum;
	W* Carry_out;
	G* xor_gate;
	G* and_gate;
};

/* ***************************************************************
 * FULL ADDER
 *
 *                             +---------+
 * Carry In -------------------+A       S+-----------Sum Out
 *                             |   HALF  |
 *             +----------+ w_1|  ADDER  |   +--------+
 *     A In ---+A        S+----+B      CO+---+   |    |
 *             |   HALF   |    +---------+W_3|        +--Carry Out
 *             |  ADDER   |                  |        |
 *     B In ---+B       CO+------------------+        |
 *             +----------+       w_2        +--------+
 * **************************************************************/
struct _full_adder{
	W* A_in;
	W* B_in;
	W* Sum;
	W* Carry_in;
	W* Carry_out;
	W* w_1;
	W* w_2;
	W* w_3;
	G* Carry_comp;
	struct _half_adder* input_add;
	struct _half_adder* carry_add;
};

struct _complement{
	int size;
	W*  _switch;
	BUF_t* in;
	BUF_t* out;
	G** _xor_gates;
};

struct _adder{
	int size;
	G* flow_comp;
	W* add_sub_switch;
	W* flow;
	W** carry_trans;
	BUF_t* A_buffer;
	BUF_t* B_buffer;
	BUF_t* OUT_buffer;
	struct _complement* Complement;
	struct _full_adder** F_adders;
};

struct _buffer{
	int size;
	W** _buf;
};

#endif
