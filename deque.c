/* * * * * * *
 * Deque module (i.e., double ended queue) for Assignment 1
 *
 * created for COMP20007 Design of Algorithms 2019
 * template by Tobias Edwards <tobias.edwards@unimelb.edu.au>
 * implementation by <Insert Name Here>
 */

//                   WRITE YOUR IMPLEMENTATION HERE
//
// You should fill in the function definitions for
//  - new_deque()
//  - free_deque()
//  - deque_push()
//  - deque_insert()
//  - deque_pop()
//  - deque_remove()
//  - deque_size()
//
// Don't be shy to add any extra functions or types you may need.

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "deque.h"
#include "point.h"


typedef struct Node {
  struct Node* next;
  struct Node* prev;
  Point data;
} Node;

struct deque {
  Node* top;
  Node* bottom;
  int size;

};

// Create a new empty Deque and return a pointer to it
//
// DO NOT CHANGE THIS FUNCTION SIGNATURE
Deque *new_deque() {
  Deque *deque = (Deque *)malloc(sizeof(Deque));
  assert(deque);

  //Set initial values
  deque->top = NULL;
  deque->bottom = NULL;
  deque->size = 0;
  return deque;
}

Node *new_node(Point new_data) {
  Node *node = (Node *)malloc(sizeof(Node));
  assert(node);
  //Set initial values
  node->data = new_data;
  node->next = NULL;
  node->prev = NULL;

  return node;
}


// Free the memory associated with a Deque
//
// DO NOT CHANGE THIS FUNCTION SIGNATURE
void free_deque(Deque *deque) {
  Node *prev = NULL;
  Node *curr = deque->top;
  while (curr!=NULL) {
    prev = curr;
    curr = curr->next;
    free(prev);
  }
  free(deque);
}

// Add a Point to the top of a Deque
//
// Runtime: O(1)
//
// DO NOT CHANGE THIS FUNCTION SIGNATURE
void deque_push(Deque *deque, Point data) {
  Node *node = new_node(data);
  if (deque->top == NULL) {
    deque->top = node;
    deque->bottom = node;
  } else {
    node->next = deque->top;
    deque->top->prev = node;
    deque->top = node;
  }

  deque->size++;
}

// Add a Point to the bottom of a Deque
//
// Runtime: O(1)
//
// DO NOT CHANGE THIS FUNCTION SIGNATURE
void deque_insert(Deque *deque, Point data) {
  Node *node = new_node(data);
  if (deque->bottom == NULL) {
    deque->top = node;
    deque->bottom = node;
  } else {
    node->prev = deque->bottom;
    deque->bottom->next = node;
    deque->bottom = node;
  }

  deque->size++;
}

// Remove and return the top Point from a Deque
//
// Runtime: O(1)
//
// DO NOT CHANGE THIS FUNCTION SIGNATURE
Point deque_pop(Deque *deque) {
  if (deque_size(deque) <=0) {
    fprintf(stderr, "Error: Attempting to pop from empty deque");
    exit(EXIT_FAILURE);
  }
  Point point = deque->top->data;
  Node *old_top = deque->top;

  //Reassign top
  deque->top = deque->top->next;
  if (deque->top == NULL) {
    deque->bottom = NULL;
  } else {
    deque->top->prev = NULL;
  }

  free(old_top);

  deque->size--;

  return point;
}

// Remove and return the bottom Point from a Deque
//
// Runtime: O(1)
//
// DO NOT CHANGE THIS FUNCTION SIGNATURE
Point deque_remove(Deque *deque) {
  if (deque_size(deque) <=0) {
    fprintf(stderr, "Error: Attempting to remove from empty deque");
    exit(EXIT_FAILURE);
  }
  Point point = deque->bottom->data;
  Node *old_bottom = deque->bottom;

  //Reassign Bottom
  deque->bottom = deque->bottom->prev;
  if (deque->bottom == NULL) {
    deque->top = NULL;
  } else {
    deque->bottom->next = NULL;
  }

  free(old_bottom);
  deque->size--;
  return point;
}

// Return the number of Points in a Deque
//
// Runtime: O(1)
//
// DO NOT CHANGE THIS FUNCTION SIGNATURE
int deque_size(Deque *deque) {
  return deque->size;
}


void deque_print(Deque *deque) {
  Node* curr = deque->top;
  printf("TOP (push/pop side)\n");
  while (curr != NULL) {
    print_point(curr->data);
    curr = curr->next;
  }
  printf("BOTTOM (insert/remove side)\n");

  printf("REVERSE PRINT\n");
  curr = deque->bottom;
  printf("BOTTOM (insert/remove side)\n");
  while (curr != NULL) {
    print_point(curr->data);
    curr = curr->prev;
  }
  printf("TOP (push/pop side)\n");
  printf("Size: %d \n", deque_size(deque));


}

Point deque_peek_top(Deque* deq, int index) {
  int i = 0;
  Node *curr = deq->top;
  while (i < index && curr != NULL) {
    curr = curr->next;
    i++;
  }
  if (curr == NULL) {
    fprintf(stderr, "Error: Indexing deque out of bounds top");
    exit(EXIT_FAILURE);

  }
  return curr->data;
}

Point deque_peek_bottom(Deque* deq, int index) {
  int i = 0;
  Node *curr = deq->bottom;
  while (i < index && curr != NULL) {
    curr = curr->prev;
    i++;
  }

  if (curr == NULL) {
    deque_print(deq);
    fprintf(stderr, "Error: Indexing deque out of bounds bottom");
    exit(EXIT_FAILURE);

  }
  return curr->data;
}

void deque_write_to_hull(Deque* deq, Point* hull) {
  if (deque_size(deq) < 3) {
    fprintf(stderr, "Error: Deque is not big enough to write to hull");
    exit(EXIT_FAILURE);
  }
  Node* curr = deq->bottom;
  int i = 0;
  while (curr->prev != NULL) {
    hull[i] = curr->data;
    i++;
    curr = curr -> prev;
  }
}




