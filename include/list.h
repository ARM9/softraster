#ifndef LIST_H
#define LIST_H
struct list_node {
  void *data;
  struct list_node *next;
};

typedef struct list {
  struct list_node *head;
  struct list_node *tail;
  size_t size;
} list;

#endif //LIST_H
