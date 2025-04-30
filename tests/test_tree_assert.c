 #include "../src/database.h"
 #include <assert.h>
 #include <stdio.h>
 #include <string.h>
 int main() {
    TreeNode* root = NULL;

	// Insertion
	root = insert_node(root, 10, "Messi");
	root = insert_node(root, 20, "Ronaldo");
	root = insert_node(root, 5,  "Mbappe");

	// Vérification avec assert
	TreeNode* found = search_node(root, 10);
	assert(found != NULL);
	assert(found->id == 10);
	printf("ID=%d, name=%s\n", found->id, found->name);
	assert(strcmp(found->name, "Messi") == 0);

	found = search_node(root, 20);
	assert(found != NULL);
	assert(strcmp(found->name, "Ronaldo") == 0);

	found = search_node(root, 5);
	assert(found != NULL);
	assert(strcmp(found->name, "Mbappe") == 0);

	// Suppression
	root = delete_node(root, 10);
	found = search_node(root, 10);
	assert(found == NULL); 

	// verifie que les autre ne sont pas supprimé
	assert(search_node(root,5) != NULL);
	assert(search_node(root, 20) != NULL);
	
	free_tree(root);

	printf("Tous les tests assert ont réussi !\n");
	
	return 0;
 }
