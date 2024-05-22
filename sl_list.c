#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include "probes.h"


typedef struct _node {
    int64_t data;
    struct _node* next;
} Node;

struct pool{
	Node **free_nodes;
	int idx;
	int total_size;
};

struct pool *free_pool=NULL;

void create_pool(int size) {
	free_pool = malloc(sizeof(struct pool));
	free_pool->total_size = size;
	free_pool->idx = 0;
	free_pool->free_nodes = (Node**) malloc(sizeof(Node*)*size);

	for(int i=0;i<size;i++) {
		Node *new = (Node*) malloc(sizeof(Node));
		if (!new) {
        	printf("Memory allocation error\n");
        	exit(1);
   		}
		new->next = NULL;
		new->data = 0;
		free_pool->free_nodes[i] = new;
	}
}

Node* get_free_node(int64_t data) {
	if(!free_pool || free_pool->idx >= free_pool->total_size)
		return NULL;

	Node *free_node = free_pool->free_nodes[free_pool->idx];
	free_pool->idx++;
	
	free_node->data = data;
	free_node->next = NULL;
	return free_node;
}

Node* createNode(int64_t data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        printf("Memory allocation error\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void insertSorted(Node** head, int64_t data) {
    //Node* newNode = createNode(data);
    /* DTRACE Probes*/
    if (LISTINSERT_ENTRY_ENABLED()) {
     	LISTINSERT_ENTRY(data);
    }
    Node *newNode = get_free_node(data);

    if (*head == NULL || (*head)->data >= data) {
        newNode->next = *head;
        *head = newNode;
    } else {
        Node* current = *head;
        while (current->next != NULL && current->next->data < data) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
    if(LISTINSERT_EXIT_ENABLED()) {
    	LISTINSERT_EXIT();
    }
}

void printList(Node* head) {
    Node* current = head;
    while (current != NULL) {
        printf("%lld -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

void freeList(Node* head) {
    Node* tmp;
    while (head != NULL) {
        tmp = head;
        head = head->next;
        free(tmp);
    }
}

int main(int argc, char **argv) {
	srand(time(NULL));
	if(argc<2) {
		printf("\nusage: ll_test size");
		return -1;
	}
	Node* head = NULL;	
	int size = atoi(argv[1]);
	create_pool(size);
	for(int i=0;i<size;i++) {
		int r = rand()%size;
	    insertSorted(&head, r);
	}

//	printList(head);
    freeList(head);
    return 0;
}
