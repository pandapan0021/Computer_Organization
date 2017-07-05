#include"wire.h"
#include"gate.h"
#include<stdlib.h>
#include<stdio.h>

W* mk_wire(){
	W* w = (W*)malloc(sizeof(W));
	if(!w){
		perror("create wire failed!");
		exit(-1);
	}
	w->status = 0;
	G_node* head = (G_node*)malloc(sizeof(G_node));
	if(!head){
		perror("create wire observer failed!");
		exit(-1);
	}
	head->gate = NULL;
	head->next = NULL;
	w->observer = head;
	return w;
}

int add_observer(W* wire, G* gate){
	G_node* ob = (G_node*)malloc(sizeof(G_node));
	if(!ob){
		perror("add observer failed!");
		exit(-1);
	}
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
