#ifndef PM_LIST_H
#define PM_LIST_H

typedef struct PmListNodeInt {
    int data;
    struct PmListNodeInt* next;
} PmListNodeInt;

typedef struct PmListInt {
    PmListNodeInt* head;
} PmListInt;

/// <summary>
/// Creates a list.
/// </summary>
PmListInt pm_list();

/// <summary>
/// Frees all of list items.
/// </summary>
void pm_list_dispose(PmListInt* list);

/// <summary>
/// Pushes an item to the end of the list.
/// </summary>
void pm_list_push(PmListInt* list, int data);

/// <summary>
/// Returns the string representation of the list.
/// </summary>
char* pm_list_to_string(PmListInt list);

#endif // PM_LIST_H
