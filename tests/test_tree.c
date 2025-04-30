#include "../src/database.h"
#include <stdio.h>

int main() {
    TreeNode* root = NULL;

    root = insert_node(root, 5, "Oumar");
    root = insert_node(root, 2, "messi");
    root = insert_node(root, 8, "neymar");

    printf("Contenu de l'arbre :\n");
    select_all_tree(root);

    TreeNode* found = search_node(root, 2);
    if (found) {
        printf("Trouvé : ID=%d, Nom=%s\n", found->id, found->name);
    } else {
        printf("ID non trouvé\n");
    }

    root = delete_node(root, 2);

    printf("Contenu après suppression :\n");
    select_all_tree(root);

    free_tree(root);
    return 0;
}
