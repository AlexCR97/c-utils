#ifndef DS_LIST_H
#define DS_LIST_H

#define LIST_DELIMETER_HEAD "["
#define LIST_DELIMETER_TAIL "]"

typedef struct {
    int data;
    struct ListNode* next;
} ListNode;

typedef struct {
    ListNode* head;
} List;

List list();
void list_push(List* list, int data);
char* list_to_string(List list);

#endif // DS_LIST_H