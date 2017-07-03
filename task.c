#include"task.h"
#include"wire.h"
#include"gate.h"
#include<stdlib.h>
#include<stdio.h>


TASK_q* task_queue_init(){
	TASK_q* queue = (TASK_q*)malloc(sizeof(TASK_q));
	if(queue<0){
		perror("failed");
		exit(-1);
	}
	TASK_t* node = (TASK_t*)malloc(sizeof(TASK_t));
	if(node<0){
		perror("failed");
		exit(-1);
	}
	node->w = NULL;
	node->g = NULL;
	node->arg = 0;
	node->task_process = NULL;
	node->next = NULL;
	queue->header = queue->tail = node;
	return queue;
}

int is_empty_task_queue(TASK_q* queue){
	return (queue->header==queue->tail)?1:0;
}

void task_queue_push(TASK_q* q, TASK_t* task){
	q->tail->next = task;
	q->tail = task;
}

TASK_t* task_queue_pop(TASK_q* q){
	if(is_empty_task_queue(q)){
		return NULL;
	}
	TASK_t* n = q->header->next;
	if(q->header->next == q->tail){
		q->tail = q->header;
		n->next = NULL;
		return n;
	}
	q->header->next = n->next;
	n->next = NULL;
	return n;
}

TASK_t* mk_task(int task_type, W* w, G* g, int arg){
	TASK_t* task = (TASK_t*)malloc(sizeof(TASK_t));
	if(task<0){
	       perror("faild");
	       exit(-1);
	}
	if(task_type == __TEST__){
		task->w = NULL;
		task->g = NULL;
		task->arg = 0;
		task->task_type = task_type;
		task->task_process = test_process;
		task->next = NULL;
		return task;
	}
	if(task_type == SET_WIRE){
		task->w = w;
		task->g = NULL;
		task->arg = arg;
		task->task_type = task_type;
		task->task_process = wire_process;
		task->next = NULL;
		return task;
	}
	if(task_type == FRASH_GATE){
		task->w = NULL;
		task->g = g;
		task->arg = 0;
		task->task_type = task_type;
		task->task_process = gate_process;
		task->next = NULL;
		return task;
	}
}

void set_wire(TASK_q* queue, W* w, int value){
	int old_val = get_status(w);
	if(value == old_val){
		return;
	}
	TASK_t* new_task = mk_task(SET_WIRE, w, NULL, value);
	task_queue_push(queue, new_task);
}

void test_process(TASK_q* queue, TASK_t* task){
	printf("run for test");
	TASK_t* new_task = mk_task(__TEST__, NULL, NULL, 0);
	task_queue_push(queue, new_task);
	free(task);
}

void wire_process(TASK_q* queue, TASK_t* task){
	int old_val = task->w->status;
	if(old_val == task->arg){
		return;
	}
	task->w->status = task->arg;
	G_node* ob = task->w->observer->next;
	while(ob){
		G* gate = ob->gate;
		TASK_t* new_task = mk_task(FRASH_GATE, NULL, gate, 0);
		task_queue_push(queue, new_task);
		ob = ob->next;
	}

	free(task);
}

void gate_process(TASK_q* queue, TASK_t* task){
	G* s_gate = task->g;
	LG_proc logic_process = s_gate->logic_process;
	W* res = s_gate->result;
	int v_1 = get_status(s_gate->input_1);
	int v_2 = get_status(s_gate->input_2);
	int v = logic_process(v_1, v_2);
	TASK_t* new_task = mk_task(SET_WIRE, res, NULL, v);
	task_queue_push(queue, new_task);
	free(task);
}

void run_task_queue(TASK_q* queue){
	while(1){
		TG_proc process;
		TASK_t* task = task_queue_pop(queue);
		if(!task){
			printf("complete!!\n");
			return;
		}
		process = (TG_proc)task->task_process;
		process(queue, task);
	}
}
