#include <stdio.h>
#include <stdlib.h>
#include "ds_list.h"
#include "strings.h"
#include "str_string_builder.h"

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
    StringBuilder sb = string_builder();
    string_builder_append(&sb, LIST_DELIMETER_HEAD);
    string_builder_append(&sb, " ");

    ListNode* current_node = list.head;

    while (current_node != NULL) {
        char* str = pm_str_to_string_int(current_node->data).data;

        // TODO handle error

        string_builder_append(&sb, str);

        if (current_node->next != NULL) {
            string_builder_append(&sb, ", ");
        } else {
            string_builder_append(&sb, " ");
        }

        current_node = current_node->next;
    }

    string_builder_append(&sb, LIST_DELIMETER_TAIL);

    return string_builder_to_string(sb);
}
