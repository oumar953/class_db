// tests/test_db.c
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "../src/database.h"

int main() {
    Table table;
    init_table(&table);

// table du début
    insert_row(&table, 1, "Astan");
    insert_row(&table, 2, "oumar");

    assert(table.row_count == 2);
    assert(table.rows[0].id == 1);
    assert(strcmp(table.rows[1].name, "oumar") == 0);




// test pour la supression
    assert(delete_row(&table, 1) == 0);
    assert(table.row_count == 1);
    assert(table.rows[0].id == 2); // oumar devrait etre le seul restant

    // Tests pour la sauvegarde
    assert(save_table(&table, "data/test_db.dat") == 0);

    Table loaded_table;
    init_table(&loaded_table);
    assert(load_table(&loaded_table, "data/test_db.dat") == 0);
    assert(loaded_table.row_count == 1);
    assert(loaded_table.rows[0].id == 2);
    assert(strcmp(loaded_table.rows[0].name, "oumar") == 0);


        printf("Tous les tests ont réussi! \n");
    return 0;

}
