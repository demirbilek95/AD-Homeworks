#include "total_orders.h"
#include "array.h"

int leq_float(const void *a, const void *b)
{
  return *((float*)a)<=*((float*)b);
}

int leq_int(const void *a, const void *b)
{
  return *((int*)a)<=*((int*)b);
}

int geq_int(const void *a, const void *b)
{
  return *((int*)a)>=*((int*)b);
}

int leq_node(const void *a, const void *b)
{
  Node *node1 = (Node*) a;
  Node *node2 = (Node*) b;
  return leq_int((void*)&(node1->d),(void*)&(node2->d));
}