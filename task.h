#ifndef __TASK_H__
#define __TASK_H__

#define TASK_HEAD 0
#define SET_WIRE 1
#define FRASH_GATE 2
#define __TEST__ 3

typedef struct task TASK_t;
typedef struct task_queue TASK_q;


typedef void (*TG_proc)(TASK_q*, TASK_t*);

#include"wire.h"
#include"gate.h"

struct task{
	int task_type;
	W* w;
	G* g;
	TG_proc task_process;
	int arg;
	struct task* next;
};


struct task_queue{
	TASK_t* header;
	TASK_t* tail;
};

TASK_q* task_queue_init();
int is_empty_task_queue(TASK_q* queue);
void task_queue_push(TASK_q* q, TASK_t* task);
TASK_t* task_queue_pop(TASK_q* q);

TASK_t* mk_task(int target_type, W* w, G* g, int arg);

void set_wire(TASK_q*, W*, int);

void test_process(TASK_q* queue, TASK_t* task);
void gate_process(TASK_q* queue, TASK_t* task);
void wire_process(TASK_q* queue, TASK_t* task);

void run_task_queue(TASK_q* queue);

#endif
