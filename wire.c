#include"wire.h"
#include"gate.h"
#include<stdlib.h>
#include<stdio.h>

W* mk_wire(){
	W* w = (W*)malloc(sizeof(W));
	w->status = 0;
	G_node* head = (G_node*)malloc(sizeof(G_node));
	head->gate = NULL;
	head->next = NULL;
	w->observer = head;
	return w;
}

int add_observer(W* wire, G* gate){
	G_node* ob = (G_node*)malloc(sizeof(G_node));
	ob->gate = (G*)gate;
	G_node* head = wire->observer;
	ob->next = head->next;
	head->next = ob;
	return 1;
}

int get_status(W* w){
	if(w){
		return w->status;
	}
	return 0;
}
