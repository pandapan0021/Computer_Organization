#ifndef __STORE_H__
#define __STORE_H__

#include"wire.h"
#include"gate.h"
#include"flip_flop.h"
#include"adder.h"
#include<stdlib.h>
#include<stdio.h>

typedef struct _rs_store RS_STORE_t;
typedef struct _2_to_1_bit_selector BIT_SELECT_t;
typedef struct _2_to_1_word_selector WORD_SELECT_t;

RS_STORE_t* rs_store(W*, W*, W*);
BIT_SELECT_t* bit_selector(W*, W*, W*, W*);
WORD_SELECT_t* word_selector(BUF_t*, BUF_t*, BUF_t*, W*, int);

struct _rs_store{
	W* data;
	W* clock;
	W* q;
	RS_t* r_s;
};

struct _byte_rs_store{
	W* w;
	W* r;
	BUF_t* data_in;
	BUF_t* data_out;
};

struct _2_to_1_bit_selector{
	W* s;
	W* a;
	W* b;
	W* out;
};

struct _2_to_1_word_selector{
	int size;
	W* s;
	BUF_t* A;
	BUF_t* B;
	BUF_t* OUT;
	BIT_SELECT_t** bit_selector;
};

#endif
