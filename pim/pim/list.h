#ifndef PM_LIST_H
#define PM_LIST_H

typedef struct PmListNodeInt {
    int data;
    struct PmListNodeInt* next;
} PmListNodeInt;

typedef struct PmListInt {
    PmListNodeInt* head;
} PmListInt;

PmListInt pm_list();
void pm_list_push(PmListInt* list, int data);
char* pm_list_to_string(PmListInt list);

#endif // PM_LIST_H
