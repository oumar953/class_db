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

// Initialise une table vide
void init_table(Table *table);

// montre  les erreur
int insert_row(Table *table, int id, const char *name);

// fonction de la table
int delete_row(Table *table, int id);
int save_table(Table *table, const char *filename);
int load_table(Table *table, const char *filename);


// Structure de l'arbre binaire
 typedef struct TreeNode {
	int id;
	char name[MAX_NAME_LENGTH];
	struct TreeNode* left;
	struct TreeNode* right;
} TreeNode;

 // Fonctions pour l'arbre 
 TreeNode* insert_node(TreeNode* root, int id, const char* name);
 TreeNode* search_node(TreeNode* root, int id);
 TreeNode* delete_node(TreeNode* root, int id);
 void select_all_tree(TreeNode* root);
 void free_tree(TreeNode* root);

 #endif
