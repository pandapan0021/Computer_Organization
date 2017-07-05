#include"flip_flop.h"

RS_t* r_s_flip_flop(W* r, W* s, W* q, W* _q){
	G* _nor_1 = mk_nor(r, _q, q);
	G* _nor_2 = mk_nor(s, q, _q);
	RS_t* rs = (RS_t*)malloc(sizeof(RS_t));
	if(!rs){
		perror("create r-s flip-flop failed!");
		exit(-1);
	}
	q->status = 0;
	_q->status = 1;
	rs -> r = r;
	rs -> s = s;
	rs -> q = q;
	rs -> _q = _q;
	rs -> rq_nor = _nor_1;
	rs -> s_q_nor = _nor_2;

	return rs;
}
