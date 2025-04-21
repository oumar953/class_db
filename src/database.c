// src/database.c
#include <stdio.h>
#include <string.h>
#include "database.h"

void init_table(Table *table) {
    table->row_count = 0;
}

void insert_row(Table *table, int id, const char *name) {
    if (table->row_count >= MAX_ROWS) {
        printf("Table pleine !\n");
        return;
    }
    table->rows[table->row_count].id = id;
    strncpy(table->rows[table->row_count].name, name, MAX_NAME_LENGTH);
    table->row_count++;
}

void select_all(const Table *table) {
    for (int i = 0; i < table->row_count; i++) {
        printf("ID: %d, Nom: %s\n", table->rows[i].id, table->rows[i].name);
    }
}
