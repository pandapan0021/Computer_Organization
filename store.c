#include"store.h"

RS_STORE_t* rs_store(W* clock, W* data, W* q){
	W* reset_out = mk_wire();
	W* set_out = mk_wire();
	W* invert_data = mk_wire();
	W* _q = mk_wire();
	RS_STORE_t* bit = (RS_STORE_t*)\
			  malloc(sizeof(RS_STORE_t));
	if(!bit){
		perror("create rs store failed!");
		exit(-1);
	}

	bit->data = data;
	bit->clock = clock;
	bit->q = q;

	mk_invert(data, invert_data);
	mk_and(clock, invert_data, reset_out);
	mk_and(clock, data, set_out);

	RS_t* rs = r_s_flip_flop(reset_out, set_out, \
			q, _q);

	bit->r_s = rs;
	
	return bit;
}

/* ***************************************************************
 * WHEN select = 1 SELECT B, select = 0 SELECT A.
 * *************************************************************/
BIT_SELECT_t* bit_selector(W* a, W* b, W* out, W* s){
	W* a_out = mk_wire();
	W* b_out = mk_wire();
	W* a_s_out = mk_wire();

	BIT_SELECT_t* b_s = (BIT_SELECT_t*)\
			    malloc(sizeof(BIT_SELECT_t));
	if(!b_s){
		perror("create bit selector failed!");
		exit(-1);
	}

	b_s -> a = a;
	b_s -> b = b;
	b_s -> s = s;
	b_s -> out = out;

	mk_invert(s, a_s_out);
	mk_and(b, s, b_out);
	mk_and(a, a_s_out, a_out);
	mk_or(a_out, b_out, out);

	return b_s;
}

WORD_SELECT_t* word_selector(BUF_t* A, BUF_t* B, \
		BUF_t* OUT, W* s, int size){
	int i;

	W** A_wires = A->_buf;
	W** B_wires = B->_buf;
	W** OUT_wires = OUT->_buf;

	WORD_SELECT_t* selector = (WORD_SELECT_t*)\
				  malloc(sizeof(WORD_SELECT_t));
	if(!selector){
		perror("create word selector failed!");
		exit(-1);
	}
	selector->bit_selector = (BIT_SELECT_t**)\
				 malloc(size*sizeof(BIT_SELECT_t*));
	if(!(selector->bit_selector)){
		perror("create bit selector holder failed!");
		exit(-1);
	}
	selector->size = size;
	selector->A = A;
	selector->B = B;
	selector->OUT = OUT;
	selector->s= s;

	for(i=0; i<size; i++){
		(selector->bit_selector)[i] = bit_selector(A_wires[i],\
				B_wires[i], OUT_wires[i], s);
	}

	return selector;
}
