#ifndef LIST_H
#define LIST_H

struct ListNode {
    void *data;
    struct ListNode *next;
};

typedef struct List {
    struct ListNode *head;
    struct ListNode *tail;
    size_t size;
} List;

#endif //LIST_H
