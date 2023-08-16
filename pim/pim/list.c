#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "strings.h"

const char* _LIST_DELIMETER_HEAD = "[";
const char* _LIST_DELIMETER_TAIL = "]";

PmListNodeInt* _list_node(int data);

PmListInt pm_list() {
    PmListInt list;
    list.head = NULL;
    return list;
}

void pm_list_push(PmListInt* list, int data) {
    PmListNodeInt* new_node = _list_node(data);

    if (list->head == NULL) {
        list->head = new_node;
        return;
    }

    PmListNodeInt* current_node = list->head;

    while (current_node->next != NULL) {
        current_node = current_node->next;
    }

    current_node->next = new_node;
}

PmListNodeInt* _list_node(int data) {
    PmListNodeInt* node = (PmListNodeInt*)malloc(sizeof(PmListNodeInt));

    if (node == NULL) {
        return NULL; // TODO How to handle errors?
    }

    node->data = data;
    node->next = NULL;
    return node;
}

char* pm_list_to_string(PmListInt list) {
    PmStringBuilder sb = pm_str_builder();
    pm_str_builder_append(&sb, _LIST_DELIMETER_HEAD);
    pm_str_builder_append(&sb, " ");

    PmListNodeInt* current_node = list.head;

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

    pm_str_builder_append(&sb, _LIST_DELIMETER_TAIL);

    return pm_str_builder_to_string(sb);
}
