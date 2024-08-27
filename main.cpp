#include <stdio.h>
#include <string.h>
#include "abb.h"

int main() {
    char key[21];
    int choice;
    BTreeNode* result;

    while (1) {
        printf("1. Inserir\n");
        printf("2. Exibir\n");
        printf("3. Buscar\n");
        printf("4. Destruir\n");
        printf("5. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Digite a chave a ser inserida: ");
                scanf("%20s", key); // Limitar entrada a 20 caracteres
                insertNode(key);
                break;
            case 2:
                displayNode(root);
                printf("\n");
                break;
            case 3:
                printf("Digite a chave a ser buscada: ");
                scanf("%20s", key); // Limitar entrada a 20 caracteres
                result = searchNode(root, key);
                if (result) {
                    printf("Chave %s encontrada.\n", key);
                } else {
                    printf("Chave %s nao encontrada.\n", key); // Adicione a chave para a mensagem correta
                }
                break;
            case 4:
                destroyNode(root);
                root = NULL;
                printf("Arvore destruida.\n");
                break;
            case 5:
                return 0;
            default:
                printf("Opcao invalida.\n");
                break;
        }
    }
    return 0;
}
