#include"core.h"
#include"flip_flop.h"
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

void add_test(){
	int _a[32] = {0, 0, 0, 0, 1, 1, 0, 1, \
	              0, 0, 0, 0, 0, 0, 0, 0, \
	              0, 0, 0, 0, 0, 0, 0, 0, \
	              0, 0, 0, 0, 0, 0, 0, 0};
	int _b[32] = {1, 0, 1, 1, 1, 1, 1, 1, \
	              0, 0, 0, 0, 0, 0, 0, 0, \
	              0, 0, 0, 0, 0, 0, 0, 0, \
	              0, 0, 0, 0, 0, 0, 0, 0};
	
	BUF_t* a = new_buffer(32);
	BUF_t* b = new_buffer(32);
	BUF_t* out = new_buffer(32);
	W* carry_in = mk_wire();
	W* flow = mk_wire();
	ADDER_t* adder = new_adder(a, b, out, carry_in, flow, 32);

	TASK_q* queue = task_queue_init();
	set_wire(queue, carry_in, 1);
	set_new_buffer(queue, a, _a, 32);
	set_new_buffer(queue, b, _b, 32);
	run_task_queue(queue);
	printf("%d\n", buf_to_signed_i(out));
}

void rs_test(){
	W* r = mk_wire();
	W* s = mk_wire();
	W* q = mk_wire();
	W* _q = mk_wire();
	RS_t* rs = r_s_flip_flop(r, s, q, _q);
	
	TASK_q* queue = task_queue_init();
	set_wire(queue, s, 1);
	run_task_queue(queue);

	printf("%d\n", get_status(q));

	set_wire(queue, r, 1);
	run_task_queue(queue);
	printf("%d\n", get_status(q));
}

int main(void){
	rs_test();
}
