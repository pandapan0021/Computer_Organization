#ifndef __WIRE_H__
#define __WIRE_H__


typedef struct wire W;
typedef struct wire W_t;
typedef struct g_node G_node;

W* mk_wire();

#include"gate.h"

int add_observer(W* w, G* g);
int get_status(W* w);

struct g_node{
	G* gate;
	struct g_node* next;
};

struct wire{
	int status;
	G_node* observer;
};

#endif
