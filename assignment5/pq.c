/*
 * In this file, you will write the structures and functions needed to
 * implement a priority queue.  Feel free to implement any helper functions
 * you need in this file to implement a priority queue.  Make sure to add your
 * name and @oregonstate.edu email address below:
 *
 * Name: Katelyn Nguyen
 * Email: nguyeka4@oregonstate.edu
 */

#include <stdlib.h>
#include <assert.h>
#include "dynarray.h"
#include "pq.h"

/*
 * This is the structure that represents a priority queue.  You must define
 * this struct to contain the data needed to implement a priority queue.
 * in addition, you want to define an element struct with both data and priority, 
 * corresponding to the elements of the priority queue. 
 */
struct pq{
  struct dynarray* arr;
  int size;
};

struct item {
  void* data;
  int priority;
};

/*
 * This function should allocate and initialize an empty priority queue and
 * return a pointer to it.
 */
struct pq* pq_create() {
  struct pq* pq = malloc(sizeof(struct pq));
  pq->arr = dynarray_create();
  pq->size = 0;
  return pq;
}

/*
 * This function should free the memory allocated to a given priority queue.
 * Note that this function SHOULD NOT free the individual elements stored in
 * the priority queue.  That is the responsibility of the caller.
 *
 * Params:
 *   pq - the priority queue to be destroyed.  May not be NULL.
 */
void pq_free(struct pq* pq) {
  assert(pq);
  dynarray_free(pq->arr);
  free(pq);
}


/*
 * This function should return 1 if the specified priority queue is empty and
 * 0 otherwise.
 *
 * Params:
 *   pq - the priority queue whose emptiness is to be checked.  May not be
 *     NULL.
 *
 * Return:
 *   Should return 1 if pq is empty and 0 otherwise.
 */
int pq_isempty(struct pq* pq) {
  assert(pq);
  return !pq->size;
}


/*
 * This function should insert a given element into a priority queue with a
 * specified priority value.  Note that in this implementation, higher priority
 * values are given precedent, and higher place in the queue.  In other words, the
 * element in the priority queue with the highest priority value should be the
 * FIRST one returned.
 *
 * Params:
 *   pq - the priority queue into which to insert an element.  May not be
 *     NULL.
 *   data - the data value to be inserted into pq.
 *   priority - the priority value to be assigned to the newly-inserted
 *     element.  Note that in this implementation, higher priority values
 *     should correspond to the first elements.  In other words,
 *     the element in the priority queue with the highest priority value should
 *     be the FIRST one returned.
 */
void pq_insert(struct pq* pq, void* data, int priority) {
  assert(pq);
  struct item* item = malloc(sizeof(item));
  item->data = data;
  item->priority = priority;
  dynarray_insert(pq->arr, -1, item);
  pq->size++;

  int current_ind = pq->size - 1;
  int parent_ind = current_ind/2;
  int parent_priority = ((struct item*) dynarray_get(pq->arr, parent_ind))->priority;
  while(parent_priority < priority) {
  swap(pq->arr, current_ind, parent_ind);
  current_ind = parent_ind;
  parent_ind = current_ind/2;
  parent_priority = ((struct item*) dynarray_get(pq->arr, parent_ind))->priority;
  }
}


void swap(struct dynarray* arr, int current_ind, int parent_ind) {
  struct item* item1 = (struct item*) dynarray_get(arr, current_ind);
  struct item* item2 = (struct item*) dynarray_get(arr, parent_ind);
  dynarray_set(arr, current_ind, item2);
  dynarray_set(arr, parent_ind, item1);
}

/*
 * This function should return the data of the first element in a priority
 * queue, i.e. the data associated with the element with highest priority value.
 *
 * Params:
 *   pq - the priority queue from which to fetch a value.  May not be NULL or
 *     empty.
 *
 * Return:
 *   Should return the data of the first item in pq, i.e. the item with
 *   max priority value.
 */
void* pq_max(struct pq* pq) {
  assert(pq);
  struct item* max_item = dynarray_get(pq->arr, 0);
  return max_item->data;
}


/*
 * This function should return the priority value of the first item in a
 * priority queue, i.e. the item with highest priority value.
 *
 * Params:
 *   pq - the priority queue from which to fetch a priority value.  May not be
 *     NULL or empty.
 *
 * Return:
 *   Should return the priority value of the first item in pq, i.e. the item
 *   with highest priority value.
 */
int pq_max_priority(struct pq* pq) {
  assert(pq);
  struct item* max_item = dynarray_get(pq->arr, 0);
  return max_item->priority;
}


/*
 * This function should return the value of the first item in a priority
 * queue, i.e. the item with highest priority value, and then remove that item
 * from the queue.
 *
 * Params:
 *   pq - the priority queue from which to remove a value.  May not be NULL or
 *     empty.
 *
 * Return:
 *   Should return the value of the first item in pq, i.e. the item with
 *   highest priority value.
 */
void* pq_max_dequeue(struct pq* pq) {
  assert(pq);
  void *data = ((struct item*)dynarray_get(pq->arr, 0))->data;
  swap(pq->arr, 0, pq->size-1);
  dynarray_remove(pq->arr, pq->size-1);
  pq->size--;
  int current_ind = 0;
  int left_ind = 2*current_ind + 1;
  int right_ind = 2*current_ind + 2;
  int current_priority = current_ind < pq->size ? ((struct item*) dynarray_get(pq->arr, current_ind))->priority : -1;
  int left_priority = left_ind < pq->size ? ((struct item*) dynarray_get(pq->arr, left_ind))->priority : -1;
  int right_priority = right_ind < pq->size ? ((struct item*) dynarray_get(pq->arr, right_ind))->priority : -1;
  while(current_priority < left_priority || current_priority < right_priority) {
    if(left_priority > right_priority) {
      swap(pq->arr, current_ind, left_ind);
      current_ind = left_ind;
    } else {
      swap(pq->arr, current_ind, right_ind);
      current_ind = right_ind;
    }
    left_ind = 2*current_ind + 1;
    right_ind = 2*current_ind + 2;
    current_priority = ((struct item*) dynarray_get(pq->arr, current_ind))->priority;
    left_priority = left_ind < pq->size ? ((struct item*) dynarray_get(pq->arr, left_ind))->priority : -1;
    right_priority = right_ind < pq->size ? ((struct item*) dynarray_get(pq->arr, right_ind))->priority : -1;
  }
  return data;
}
