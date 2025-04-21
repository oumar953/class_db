// src/main.c
#include <stdio.h>
#include "database.h"

int main() {
    Table table;
    init_table(&table);

    insert_row(&table, 1, "Alice");
    insert_row(&table, 2, "Bob");

    printf("Contenu de la table :\n");
    select_all(&table);

    return 0;
}

