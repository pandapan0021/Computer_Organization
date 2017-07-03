#ifndef __FLIP_FLOP_H__
#define __FLIP_FLOP_H__

#include"wire.h"
#include"gate.h"
#include<stdlib.h>
#include<stdio.h>

typedef struct r_s RS_t;

RS_t* r_s_flip_flop(W*, W*, W*, W*);


struct r_s{
	W* r;
	W* s;
	W* q;
	W* _q;
	G* rq_nor;
	G* s_q_nor;
};

#endif
