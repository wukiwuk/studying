#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node{
	int key;
	char name[10];
	struct node *prev, *next;
}node;

typedef struct DLL {
	node *head, *tail;
}DLL;

node *newNode(const int key, const char *name){
	node *n = (node*)malloc(sizeof(node));
	n->key = key;
	strcpy(n->name, name);
	n->next = NULL;
	n->prev = NULL;
	
	return n;
}

DLL *newDLL() {
	DLL *d = (DLL*)malloc(sizeof(DLL));
	d->head = NULL;
	d->tail = NULL;
	
	return d;
}

void pushb(DLL *list, const int key, const char *name) {
	node *n = newNode(key, name);
	
	if(list->head == NULL) {
		list->head = n;
		list->tail = n;
		return;
	} else {
		list->tail->next = n;
		n->prev = list->tail;
		list->tail = n;
	}
}

void pushh(DLL *list, const int key, const char *name) {
	node *n = newNode(key, name);
	
	if(list->head == NULL) {
		list->head = n;
		list->tail = n;
		return;
	} else {
		list->head->prev = n;
		n->next = list->head;
		list->head = n;
	}
}

void pushASC(DLL*list, const int key, const char *name) {
	node *n = newNode(key, name);
	
	if(list->head==NULL) {
		list->head = n;
		list->tail = n;
		return;
	} else if(key < list->head->key) {
		n->next = list->head;
		list->head->prev = n;
		list->head = n; 
	} else if(key > list->tail->key) {
		list->tail->next = n;
		n->prev = list->tail;
		list->tail = n;
	} else {
		node *curr = list->head;
		while(curr->next!=NULL && curr->next->key < key) {
			curr = curr->next;
		}
		
		n->next = curr->next;
		n->prev = curr;	
		
		if(curr->next != NULL) {
			curr->next->prev = n;
		}
		
		curr->next = n;
	}
}

void pop(DLL *list, int key) {
	if(list->head == NULL) {
		return;
	}
	
	node *curr = list->head;
	while(curr!= NULL && key != curr->key) {
		curr = curr->next;
	}
	
	if(curr == NULL) return;
	if(curr == list->head) list->head = curr->next;
	if(curr == list->tail) list->tail = curr->prev;
	if(curr->next != NULL) curr->next->prev = curr->prev;
	if(curr->prev != NULL) curr->prev->next = curr->next;
	
	free(curr);
}

void printList(DLL *list) {
	node *c = list->head;
	
	while(c != NULL) {
		printf("%d: %s\n", c->key, c->name);
		c = c->next;
	}
}

int main() {
	DLL *list = newDLL();
	
	pushASC(list, 100, "Steve");
	pushASC(list, 123, "Oink");
	pushASC(list, 12, "Gar");
	pushASC(list, 1, "Hank");
	pushASC(list, 17, "Hubert");
	pop(list, 17);
	pop(list, 14);
	
	printList(list);
}
