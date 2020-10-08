/*
 * This is the file in which you'll write a function to reverse a linked list.
 * Make sure to add your name and @oregonstate.edu email address below:
 *
 * Name:
 * Email:
 */

#include <stdio.h>

#include "list_reverse.h"

/*
 * In this function, you will be passed a pointer to the first node of a singly-linked list.
 * You should reverse the linked list and return the new "first" pointer.  The reversal
 * must be done in place, and you may not allocate any new memory in this
 * function.
 *
 * Params:
 *   first - a pointer to the first node of a singly-linked list to be reversed
 *
 * Return:
 *   Should return the new first of the reversed list.  If first is NULL, this
 *   function should return NULL.
 */
struct node* list_reverse(struct node* first) {
	struct node *prev = NULL;
	struct node *current = first;
	struct node *next = NULL;

	while (current != NULL){
		next = current -> next;
		current -> next = prev;
		prev = current;
		current = next;
	}
	first = prev;

	if (first == NULL){
		return NULL;
	}
	return first;
}
