// src/database.h

#ifndef DATABASE_H
#define DATABASE_H

#define MAX_ROWS 100
#define MAX_NAME_LENGTH 50

typedef struct {
    int id;
    char name[MAX_NAME_LENGTH];
} Row;

typedef struct {
    Row rows[MAX_ROWS];
    int row_count;
} Table;

void init_table(Table *table);
void insert_row(Table *table, int id, const char *name);
void select_all(const Table *table);

#endif
