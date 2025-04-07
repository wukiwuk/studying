#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct node {
	int priority;
	char c2[30];
	struct node *next;
}node;

typedef struct SLL {
	node *head;
}SLL;

SLL *newQueue() {
	SLL *q = (SLL*)malloc(sizeof(SLL));
	q->head = NULL;
	
	return q;
}

int getPriority(const char *c3) {
	if(strcmp(c3, "Critical") == 0) return 1;
	if(strcmp(c3, "Serious") == 0) return 2;
	if(strcmp(c3, "Fair") == 0) return 3;
	return 4;
}

node *newNode(char *c2, char *c3) {
	node *newNode = (node*)malloc(sizeof(node));
	newNode->priority = getPriority(c3);
	strcpy(newNode->c2, c2);
	newNode->next = NULL;
	
	return newNode;
}

void push(SLL *q, char *c2, char *c3) {
	node *n = newNode(c2, c3);
	if(q->head == NULL || n->priority < q->head->priority) {
		n->next = q->head;
		q->head = n;
		return;
	}
	
	node *curr = q->head;
	while(curr->next != NULL && n->priority >= curr->next->priority) {
		curr = curr->next;
	}
	n->next = curr->next;
	curr->next = n;
}

void pop(SLL *q) {
	if(q->head == NULL) {
		return;
	}
	
	node *n = q->head;
	printf("%s is in the Consultation Room\n", n->c2);
	q->head = q->head->next;
	free(n);
}

void printList(SLL *q) {
	node *curr = q->head;
	printf("Waiting Room: ");
	while(curr != NULL) {
		printf("%s ", curr->c2);
		curr= curr->next;
	}
	printf("\n");
}

int main() {
	SLL *q = newQueue();
	pop(q);
	int N;
	scanf("%d", &N);
	char c1[10], c2[30], c3[10];
	for(int i = 0; i < N; i++) {
		scanf("%s", c1);
		if(strcmp(c1, "ADD") == 0) {
			scanf("%s %s", c2, c3);
			push(q, c2, c3);	
		} else {
			pop(q);
		}
	}
	printList(q);
}
