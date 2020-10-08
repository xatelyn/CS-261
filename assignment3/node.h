/*
 * This file contains the definition of a node structure for implementing
 * singly-linked lists that contain integer values.
 */

#ifndef __NODE_H
#define __NODE_H

struct node {
  int value;
  struct node* next;
};

#endif
