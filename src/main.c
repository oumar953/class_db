// src/main.c

// CLI de la BDD
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "database.h"

#define MAX_COMMAND_LENGTH 256
#define DATA_FILE "data/db.dat"

//Affiche le prompt de la base de données

void print_prompt() {
	printf("db > ");
}

 //Affiche l'aide avec toutes les cmnd dispo
void print_help() {
	printf("Commandes disponibles:\n");
	printf(" INSERT <id> <name> -Insère une nouvelle ligne\n");
	printf(" SELECT <id>        -Affiche la ligne avec l'id spécifié\n");
	printf(" SELECT ALL         -Affiche toutes les lignes\n");
	printf(" DELETE <id>        -Supprime la ligne avec l'id spécifié\n");
	printf(" HELP               -Affiche cette aide\n");
	printf(" EXIT, QUIT         -Quitte le programme\n");
}

//Traite une commande saisie par l'utilisateur
 // "command" Chaîne contenant la commande à traiter
 // "table" Pointeur vers la table de la BDD
void process_command(char* command, Table* table) {
   //analyse la commande
	if (strncmp(command, "INSERT", 6) == 0) {
	//format attendu: INSERT id name
	int id;
	char name[50];
	if (sscanf(command, "INSERT %d %s", &id,name) == 2) {
	   if (insert_row(table, id, name) ==0) {
		printf("Ligne insérée: id=%d, name=%s\n", id, name);
	   } else {
	    printf("Erreur: Impossible d'inserer la ligne (id déja existant ou table pleine)\n");
	   }
       } else {
	printf("Erreur de syntaxe: Attendu INSERT id name\n");
      }
   } else if (strncmp(command, "SELECT", 6) ==0) {
	// Format attendu: SELECT id (ou SELECT ALL)
	if (strncmp(command + 7, "ALL", 3) == 0) {
		if (table->row_count == 0) {
		    printf("Table vide\n");
		} else {
		    printf("ID | Name\n");
		    printf("---+------\n");
		    for (int i = 0; i < table->row_count; i++) {
			printf("%2d | %s\n", table->rows[i].id, table->rows[i].name);
		   }
		   printf("(%d ligne(s) au total)\n", table->row_count);
		}
	     } else {
		int id;
		if (sscanf(command, "SELECT %d", &id) == 1) {
		  // Recherche par ID 
		 int found = 0;
		 for (int i = 0; i < table->row_count; i++) {
			if (table->rows[i].id == id) {
			    printf("ID | Name\n");
			    printf("---+------\n");
			    printf("%2d | %s\n", id, table->rows[i].name);
			    found = 1;
			    break;
                        }
		   }
		   if (!found) {
		      printf("Aucune ligne trouvée avec id=%d\n", id);
		   }
		} else {
		    printf("Erreur de syntaxe: Attendu SELECT id ou SELECT ALL\n");
		}
	    }
    } else if (strncmp(command,"DELETE", 6) == 0) {
	int id;
	if (sscanf(command, "DELETE %d", &id) == 1) {
		//je doit faire fonction  delete row après
		int result = delete_row(table, id);
		if (result == 0) {
		   printf("Ligne avec id=%d supprimée\n", id);
		} else {
		   printf("Aucune ligne trouvée avec id=%d\n");
		}
    } else {
	printf("Erreur de syntaxe Attendu DELETE id\n");
    }
  } else if (strncmp(command, "HELP", 4) == 0) {
      print_help();
  } else if ((strncmp(command, "EXIT", 4) == 0) || (strncmp(command, "QUIT", 4) == 0)) {
	printf("Au revoir!\n");
	exit(0);
  } else {
      printf("Commande non reconnue: %s\n", command);
      printf("Tapez HELP pour voir les commandes disponible \n");
  }
}



  // Initialise la base de données, affiche le prompt
  // et traite les commandes de l'user


 int main() {

	system("mkdir -p data");
	Table table;
	init_table(&table);

	// charger la table depuis le fichier a faire plus tard
	// Load_table(&table, DATA_FILE);

	char command[MAX_COMMAND_LENGTH];
	printf("Base de données simple. Tapez HELP pour voir les commandes disponible.\n");

	//boucle principale de prgrm
	while (1) {
	   print_prompt();

	   if (fgets(command, sizeof(command), stdin) == NULL) {
	  	printf("\nFin de fichier détectée. Sortie...\n");
		break;
	}

	// supprime le saut de ligne en  fin de commande
	command[strcspn(command, "\n")] = '\0';

	//ignore les ligne vides
	if (strlen(command) > 0) {
	   process_command(command, &table);
	}
     }

	//sauvegarde la table avant de quitter  a faire apès aussi
	// save_table(&table, DATA_FILE);
	return 0;
 }

