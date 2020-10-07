/*
 * This file contains the definition of the interface for a priority queue.
 * You will implement the structures and functiond declared here in pq.c.
 */

#ifndef __PQ_H
#define __PQ_H

struct pq;

struct pq* pq_create();
void pq_free(struct pq* pq);
int pq_isempty(struct pq* pq);
void pq_insert(struct pq* pq, void* data, int priority);
void* pq_max(struct pq* pq);
int pq_max_priority(struct pq* pq);
void* pq_max_dequeue(struct pq* pq);

#endif
