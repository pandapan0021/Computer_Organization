#include"gate.h"
#include"wire.h"
#include<stdlib.h>
#include<stdio.h>

G* mk_and(W* input1, W* input2, W* output){
	G* g = (G*)malloc(sizeof(struct gate));
	if(!g){
		perror("create and gate failed!");
		exit(-1);
	}
	if(!(input1 && input2 && output)){
		perror("all wires is null when \
				create and gate!");
		exit(-1);
	}
	g->gate_type = AND_GATE;
	g->input_1 = input1;
	g->input_2 = input2;
	g->result = output;
	g->logic_process = and_logic;
	add_observer(input1, g);
	add_observer(input2, g);
	return g;
}

G* mk_or(W* input1, W* input2, W* output){
	G* g = (G*)malloc(sizeof(struct gate));
	if(!g){
		perror("create or gate failed!");
		exit(-1);
	}
	if(!(input1 && input2 && output)){
		perror("all wires is null when \
				create or gate!");
		exit(-1);
	}
	g->gate_type = OR_GATE;
	g->input_1 = input1;
	g->input_2 = input2;
	g->result = output;
	g->logic_process = or_logic;
	add_observer(input1, g);
	add_observer(input2, g);
	return g;
}

G* mk_invert(W* input, W* output){
	G* g = (G*)malloc(sizeof(G));
	if(!g){
		perror("create invert gate failed!");
		exit(-1);
	}
	if(!(input && output)){
		perror("all wires is null when \
				create invert gate!");
		exit(-1);
	}
	g->gate_type = INVERT_GATE;
	g->input_1 = input;
	g->input_2 = NULL;
	g->result = output;
	g->logic_process = invert_logic;
	add_observer(input, g);
	return g;
}

G* mk_xor(W* input1, W* input2, W* output){
	G* g = (G*)malloc(sizeof(G));
	if(!g){
		perror("create xor gate failed!");
		exit(-1);
	}
	if(!(input1 && input2 && output)){
		perror("all wires is null when \
				create xor gate!");
		exit(-1);
	}
	g->gate_type = XOR_GATE;
	g->input_1 = input1;
	g->input_2 = input2;
	g->result = output;
	g->logic_process = xor_logic;
	add_observer(input1, g);
	add_observer(input2, g);
	return g;
}

G* mk_nor(W* input1, W* input2, W* output){
	G* g = (G*)malloc(sizeof(G));
	if(!g){
		perror("create nor gate failed!");
		exit(-1);
	}
	if(!(input1 && input2 && output)){
		perror("all wires is null when \
				create nor gate!");
		exit(-1);
	}
	g->gate_type = NOR_GATE;
	g->input_1 = input1;
	g->input_2 = input2;
	g->result = output;
	g->logic_process = nor_logic;
	add_observer(input1, g);
	add_observer(input2, g);
	return g;
}

int and_logic(int i_1, int i_2){
	return i_1 & i_2;
}

int or_logic(int i_1, int i_2){
	return i_1 | i_2;
}

int invert_logic(int i_1, int i_2){
	return i_1?0:1;
}

int xor_logic(int i_1, int i_2){
	return i_1 == i_2 ? 0:1;
}

int nor_logic(int i_1, int i_2){
	return i_1 == 0 && i_2 == 0 ? 1 : 0;
}
