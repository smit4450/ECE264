#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "priority_queue.h"

Node* pq_enqueue(Node** a_head, void* a_value, int (*cmp_fn)(void const*, void const*)) {
	
	if(*a_head == NULL) {
		Node* new_node = malloc(sizeof(*new_node));
		*new_node = (Node) { .a_value = a_value, .next = NULL };	
		*a_head = new_node;
	}
	else if(cmp_fn(a_value, &((*a_head) -> a_value)) < 0) {
		Node* new_tail = *a_head;
		Node* new_node = malloc(sizeof(*new_node));
		*new_node = (Node) { .a_value = a_value, .next = new_tail };	
		*a_head = new_node;
	}
	else {
		pq_enqueue(&((*a_head) -> next), a_value, cmp_fn);
	}

	return NULL;  
}


Node* pq_dequeue(Node** a_head) {
	Node *removed_node = *a_head;
	if (a_head != NULL) {
		*a_head = removed_node -> next;
		removed_node -> next = NULL;
	}

	return removed_node;
}


Node* stack_push(Node** a_head, void* a_value) {
	Node* new_node = malloc(sizeof(*new_node));
	
	new_node -> a_value = a_value;
	new_node -> next = *a_head;
	
	*a_head = new_node;	
	return new_node;
}


Node* stack_pop(Node** a_head) {
	Node *removed_node = *a_head;
	if (a_head != NULL) {
		Node *new_head = (*a_head) -> next;
		removed_node -> next = NULL;
		*a_head = new_head;
	}
	return removed_node;
}


void destroy_list(Node** a_head, void (*destroy_value_fn)(void*)) {
	if (destroy_value_fn == NULL) {
		while(*a_head != NULL) {
			Node* new_head = (*a_head) -> next;
			free(*a_head);
			*a_head = new_head;
		}
		*a_head = NULL;
	}
	else {
		while (*a_head!= NULL) {
			Node* new_head = (*a_head) -> next;
			destroy_value_fn((*a_head) -> a_value);
			free(*a_head);
			*a_head = new_head;
		}
		*a_head = NULL;
	}

}


#define Priority_Queue_C_V1

