#include"core.h"
#include"flip_flop.h"
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

void wire_test(){
	W* w = mk_wire();
	TASK_q* queue = task_queue_init();
	set_wire(queue, w, 1);
	run_task_queue(queue);
	printf("%d\n", w->status);
	set_wire(queue, w, 0);
	run_task_queue(queue);
	printf("%d\n", w->status);
	set_wire(queue, w, 1);
	run_task_queue(queue);
	printf("%d\n", w->status);
}

void invert_gate_test(){
	W* in = mk_wire();
	W* out = mk_wire();
	mk_invert(in, out);

	TASK_q* queue = task_queue_init();
	set_wire(queue, in, 1);
	run_task_queue(queue);
	printf("%d\n", out->status);
	set_wire(queue, in, 0);
	run_task_queue(queue);
	printf("%d\n",out->status);
}

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

void store_test(){
	W* set = mk_wire();
	W* hold = mk_wire();
	W* q = mk_wire();

	RS_STORE_t* bit = rs_store(hold, set, q);

	TASK_q* queue = task_queue_init();
	set_wire(queue, set, 1);
	set_wire(queue, hold, 1);
	run_task_queue(queue);
	set_wire(queue, hold, 0);
	run_task_queue(queue);

	printf("%d\n", get_status(q));

	set_wire(queue, set, 0);
	set_wire(queue, hold, 1);
	run_task_queue(queue);
	set_wire(queue, hold, 0);
	run_task_queue(queue);

	printf("%d\n", get_status(q));
}

void bit_select_test(){
	W* a = mk_wire();
	W* b = mk_wire();
	W* s = mk_wire();
	W* out = mk_wire();
	BIT_SELECT_t* b_s = bit_selector(a, b, out, s);

	TASK_q* queue = task_queue_init();
	set_wire(queue, a, 1);
	set_wire(queue, b, 0);
	set_wire(queue, s, 1);
	run_task_queue(queue);

	printf("%d\n", get_status(out));

	set_wire(queue, s, 0);
	run_task_queue(queue);
	printf("%d\n", get_status(out));
}

void word_select_test(){
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
	W* s = mk_wire();
	WORD_SELECT_t* w_selector = word_selector(a, b, out, \
			s, 32);

	TASK_q* queue = task_queue_init();
	set_new_buffer(queue, a, _a, 32);
	set_new_buffer(queue, b, _b, 32);
	set_wire(queue, s, 1);
	run_task_queue(queue);
	printf("a:\n");
	read_new_buffer(a, 32);
	printf("\n");
	printf("b:\n");
	read_new_buffer(b, 32);
	printf("\n");
	read_new_buffer(out, 32);
	set_wire(queue, s, 0);
	run_task_queue(queue);
	read_new_buffer(out, 32);
}
int main(void){
	word_select_test();
}
