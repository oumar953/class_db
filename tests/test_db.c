// tests/test_db.c
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "../src/database.h"

int main() {
    Table table;
    init_table(&table);

    insert_row(&table, 1, "Alice");
    insert_row(&table, 2, "Bob");

    assert(table.row_count == 2);
    assert(table.rows[0].id == 1);
    assert(strcmp(table.rows[1].name, "Bob") == 0);

    printf("All tests passed!\n");
    return 0;
}
