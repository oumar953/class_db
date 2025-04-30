// src/main.c

// CLI de la BDD
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "database.h"

 #define MAX_COMMAND_LENGTH 100
 #define DATA_FILE "data/db.dat"

 //Affiche le prompt de la base de données

 void save_tree(FILE* file, TreeNode* root);
 void load_tree(TreeNode** root, FILE* file);

 int main() {
	TreeNode* root = NULL;
	//chargement des données depuis le fichier
	FILE* f = fopen(DATA_FILE, "rb");
	if (f) {
		load_tree(&root, f);
		fclose(f);
	}


	char command[MAX_COMMAND_LENGTH];

	printf("Bienvenue dans class_db avec arbre binaire !\n");

	while (1) {
	    printf(">");
	    if (!fgets(command, sizeof(command), stdin)) break;

	    // Suprime le saut de ligne
	    command[strcspn(command, "\n")] = 0;

	    int id;
	    char name[MAX_NAME_LENGTH];

	    if (strncmp(command, "INSERT", 6) == 0) {
		if (sscanf(command + 6, "%d %s", &id, name) == 2) {
		    root = insert_node(root, id, name);
			// sauvagarde après l'insertion des donner
			FILE* f = fopen(DATA_FILE, "wb");
			if (f) {
			    save_tree(f, root);
			    fclose(f);
			}
		    } else {
			printf("Usage : INSERT <id> <name>\n");
		    }

		} else if (strncmp(command, "SELECT ALL", 10) == 0) {
		    select_all_tree(root);

		} else if (strncmp(command, "SELECT", 6) == 0) {
		    if (sscanf(command + 6, "%d", &id) == 1) {
			TreeNode* found = search_node(root, id);
			if (found) {
			    printf("ID: %d, Nom: %s\n", found->id, found->name);
			} else {
			    printf("Aucune ligne trouvée avec id=%d\n", id);
			}
		   } else {
		 	printf("Usage : SELECT <id>\n");
		   }

		} else if (strncmp(command, "DELETE", 6) == 0) {
		    if (sscanf(command + 6, "%d", &id) == 1) {
			root = delete_node(root, id);
			// Sauvegarde après suppression
			FILE* f = fopen(DATA_FILE, "wb");
			if (f) {
			   save_tree(f, root);
			   fclose(f);
			}
		} else {
		    printf("Usage : DELETE <id>\n");
		}

	    } else if (strncmp(command, "EXIT", 4) == 0 || strncmp(command, "QUIT", 4) == 0) {
		break;

	    } else {
		printf("Commande inconnue. Essayez INSERT, SELECT, DELETE, SELECT ALL OU EXIT.\n");
	    }
	}

	free_tree(root);
	printf("A bientot \n");
	return 0;
  }

 //sauvegarde récursif
 void save_tree(FILE* file, TreeNode* root) {
	 if (!root) return;
	fwrite(root, sizeof(TreeNode), 1, file);
	save_tree(file, root->left);
	save_tree(file, root->right);
 }

 // chargement récursif
 void load_tree(TreeNode** root, FILE* file) {
	TreeNode temp;
	while (fread(&temp, sizeof(TreeNode), 1, file) == 1) {
	     *root = insert_node(*root, temp.id, temp.name);
	}
 }
