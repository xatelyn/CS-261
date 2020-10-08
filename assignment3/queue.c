/*
 * This file contains the definitions of structures and functions implementing
 * a simple queue using a linked list.
 */

#include <stdlib.h>
#include <assert.h>

#include "node.h"
#include "queue.h"

/*
 * This is the definition of the queue structure.  Using a linked list to
 * implement a queue requires that we keep track of both the first and the
 * last of the queue.
 */
struct queue {
  struct node* first;
  struct node* last;
};


struct queue* queue_create() {
  struct queue* queue = malloc(sizeof(struct queue));
  assert(queue);
  queue->first = NULL;
  queue->last = NULL;
  return queue;
}


void queue_free(struct queue* queue) {
  assert(queue);

  /*
   * Here, we're assuming that queue_dequeue() handles freeing the memory
   * associated with each dequeued element.
   */
  while (!queue_isempty(queue)) {
    queue_dequeue(queue);
  }
  free(queue);
}


int queue_isempty(struct queue* queue) {
  assert(queue);
  return queue->first == NULL;
}


void queue_enqueue(struct queue* queue, int value) {
  assert(queue);
  struct node* new_node = malloc(sizeof(struct node));
  assert(new_node);

  /*
   * Fill out the new node at put it at the last of the list, which represents
   * the top of the queue.
   */
  new_node->value = value;
  new_node->next = NULL;
  if (queue->last) {
    queue->last->next = new_node;
  }
  queue->last = new_node;

  // If we didn't have a first node before, set the first to this new node, too.
  if (!queue->first) {
    queue->first = new_node;
  }
}


int queue_front(struct queue* queue) {
  assert(queue && queue->first);
  return queue->first->value;
}


int queue_dequeue(struct queue* queue) {
  assert(queue && queue->first);

  /*
   * Remove the old front element from the list and remember its value before
   * we free it.
   */
  struct node* dequeued_first = queue->first;
  int value = dequeued_first->value;
  queue->first = dequeued_first->next;

  /*
   * If the dequeued first was also the last, set the last to NULL.
   */
  if (queue->last == dequeued_first) {
    queue->last = NULL;
  }

  free(dequeued_first);
  return value;
}
