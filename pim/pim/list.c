#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "strings.h"

ListNode* _list_node(int data);

List list() {
    List list;
    list.head = NULL;
    return list;
}

void list_push(List* list, int data) {
    ListNode* new_node = _list_node(data);

    if (list->head == NULL) {
        list->head = new_node;
        return;
    }

    ListNode* current_node = list->head;

    while (current_node->next != NULL) {
        current_node = current_node->next;
    }

    current_node->next = new_node;
}

ListNode* _list_node(int data) {
    ListNode* node = (ListNode*)malloc(sizeof(ListNode));

    if (node == NULL) {
        return NULL; // TODO How to handle errors?
    }

    node->data = data;
    node->next = NULL;
    return node;
}

char* list_to_string(List list) {
    PmStringBuilder sb = pm_str_builder();
    pm_str_builder_append(&sb, LIST_DELIMETER_HEAD);
    pm_str_builder_append(&sb, " ");

    ListNode* current_node = list.head;

    while (current_node != NULL) {
        char* str = pm_str_to_string_int(current_node->data).data;

        // TODO handle error

        pm_str_builder_append(&sb, str);

        if (current_node->next != NULL) {
            pm_str_builder_append(&sb, ", ");
        } else {
            pm_str_builder_append(&sb, " ");
        }

        current_node = current_node->next;
    }

    pm_str_builder_append(&sb, LIST_DELIMETER_TAIL);

    return pm_str_builder_to_string(sb);
}
