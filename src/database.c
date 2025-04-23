// src/database.c
#include <stdio.h> //Pour les fonctions d'entrée/sortie
#include <string.h> //Pour les fonctions de manipulation de chaînes
#include <errno.h>  // Pour la gestion des erreurs
#include "database.h"

void init_table(Table *table) {
    table->row_count = 0;
}

 // " table" Pointeur vers la table
 // "id" Identifiant unique pour la nouvelle ligne
 // " name" Nom à associer à l'identifiant
 //  0 en cas de succès, -1 en cas d'erreur

 int insert_row(Table *table, int id, const char *name) {
	//verifie si la table est pleine
    if (table->row_count >= MAX_ROWS) {
        printf("Table pleine !\n");
        return -1;
	}

	//vérifie si l'ID est utiliser ou pas
	for (int i = 0; i < table->row_count; i++) {
	    if (table->rows[i].id ==id) {
		printf("ID déjà utilisé !\n");
		return -1;
	}
    }

    table->rows[table->row_count].id = id;
    strncpy(table->rows[table->row_count].name, name, MAX_NAME_LENGTH);
    table->rows[table->row_count].name[MAX_NAME_LENGTH -1] = '\0'; 
    table->row_count++;

    return 0;
}

void select_all(const Table *table) {
    for (int i = 0; i < table->row_count; i++) {
        printf("ID: %d, Nom: %s\n", table->rows[i].id, table->rows[i].name);
    }
 }

//Supprime une ligne de la table en fonction de l'ID

 int delete_row(Table* table, int id){
	//Recherche de la ligne avec l'id spécifié
	int position = -1;
	for (int i = 0; i < table->row_count; i++) {
	if (table->rows[i].id == id) {
		position = i;
		break;
	}
     }

	//si l' id n'a pas été trouvé
	if (position == -1) {
		return -1;
	}
    // Décale toutes les lignes  pour enlever le trou
    for (int i = position; i < table->row_count - 1; i++) {
        table->rows[i] = table->rows[i + 1];
}

	//Décrémente le nombre de lignes
	table->row_count--;

	return 0;
 }


  // Sauvegarde la table dans un fichier
  // table Pointeur vers la table à sauvegarder

 int save_table(Table* table, const char* filename) {
	FILE* file = fopen(filename, "wb");
	if (file == NULL) {
		perror("Cannot open file for writing");
		return -1;
	}

	fwrite(&table->row_count, sizeof(int), 1, file);

	for (int i = 0; i < table->row_count; i++) {
		fwrite(&table->rows[i], sizeof(Row), 1, file);
	}
	fclose(file);
	return 0;
 }

  //Charge une table depuis un fichier
  //"table" Pointeur vers la table à remplir

 int load_table(Table* table, const char* filename) {
 	FILE* file = fopen(filename, "rb");
 	if (file == NULL) {
 	if (errno == ENOENT) {

		table->row_count = 0;
 		return 0;
 	}
 	perror("Cannot open file for reading");
 	return -1;

     }

    //lit le nombre de lignes
    if (fread(&table->row_count, sizeof(int), 1, file) !=1) {
      if (feof(file)) {
      	  // fichier vide
      	  table->row_count = 0;
      	  fclose(file);
      	  return 0;
      }
      perror("Error reading row count");
      fclose(file);
      return -1;
   }

	// verifie  le nombre de ligne par rapport a la capacité
	if (table->row_count > MAX_ROWS) {
	     fprintf(stderr, "File contains too many rows\n");
	     fclose(file);
	     return -1;
   }

   // lit chaque ligne
   for (int i = 0; i < table->row_count; i++) {
       if (fread(&table->rows[i], sizeof(Row), 1, file) !=1) {
           perror("Error reading row");
           fclose(file);
           return -1;
        }
    }

   fclose(file);
   return 0;
  }
