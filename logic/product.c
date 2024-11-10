#include "../helpers/helpers.h"

#define MAX_PRODUTOS 100

int checkProductExists(Produto newProduct) {
    FILE *fptr = OPEN_FILE_HELPER(productStoreFilePath, "r");
    if (fptr == NULL) {
        fclose(fptr);
        return 0;
    }

    char line[1000];
    char id[10];
    char descricao[100];
    while (fgets(line, sizeof(line), fptr)) {
        // extraindo o valor da ID na linha
        if (sscanf(line, "ID: %s", id) == 1) {
            if (strcmp(id, newProduct.ID) == 0) {
                printf("Produto com esse ID ja foi cadastrado.\n");
                fclose(fptr);
                return 1;
            }
        }

        // extraindo o valor da descrição na linha
        if (sscanf(line, "descricao: %s", descricao) == 1) {
            if (strcmp(descricao, newProduct.descricao) == 0) {
                printf("Produto com essa descricao ja foi cadastrado.\n");
                fclose(fptr);
                return 1;
            }
        }
    }
}

int insertProduct(Produto newProduct) {
    FILE *fptr = OPEN_FILE_HELPER(productStoreFilePath, "a+");
    if (fptr == NULL) {
        fptr = OPEN_FILE_HELPER(productStoreFilePath, "w");
        if (fptr == NULL) {
            return 0;
        }
    }

    fprintf(fptr, "ID: %s, descricao: %s, quantidade: %d, preco: %.2f\n",
        newProduct.ID,
        newProduct.descricao,
        newProduct.quantidadeNoEstoque,
        newProduct.precoUnitario
    );

    fclose(fptr);

    return 1;
}

void createProduct() {
    int productsCount = getFileLinesCountHelper(productStoreFilePath);

    if (productsCount < MAX_PRODUTOS) {
        Produto novoProduto;
        char code[3];
        sprintf(code, "%d", newProductIDHelper());

        strcpy(novoProduto.ID, code);

        if (checkProductExistsByIDHelper(novoProduto.ID)) {
            printf("Produto ja cadastrado.");
            return;
        }

        printf("Digite a descricao do produto: ");
        scanf(" %[^\n]", novoProduto.descricao);

        printf("Digite qual a quantidade desse produto no estoque: ");
        scanf("%d", &novoProduto.quantidadeNoEstoque);

        printf("Digite o preco da unidade desse produto: ");
        scanf("%f", &novoProduto.precoUnitario);

        if (!validateProductHelper(novoProduto)) {
            printf("Produto invalido! Especifique descrição, quantidade e preco da unidade corretamente\n");
            return;
        }
        
        if (insertProduct(novoProduto)) {
            printf("Produto cadastrado com sucesso!\n");
        } else {
            printf("Nao foi possivel cadastrar esse produto.\n");
        }
    } else {
        printf("Nao foi possivel cadastrar esse produto pois o limite de produtos cadastrados (100) foi atingido.\n");
    }
}

int readProductByCode(IDProduto code) {
    FILE *fptr = OPEN_FILE_HELPER(productStoreFilePath, "r");
    if (fptr == NULL) {
        fclose(fptr);
        return 0;
    }

    char line[1000];
    while (fgets(line, sizeof(line), fptr)) {
        // checa se na linha contém o código especificado
        if (strstr(line, code) != NULL) {
            printf("%s", line);
            fclose(fptr);
            return 1;
        }
    }

    fclose(fptr);
    printf("Produto nao encontrado!\n");
    return 0;
}

void readProduct() {
    char code[3];
    printf("Digite o codigo do produto: ");
    scanf("%s", code);

    readProductByCode(code);    
}

void readProducts() {
    FILE *fptr = OPEN_FILE_HELPER(productStoreFilePath, "r");
    if (fptr == NULL) {
        fclose(fptr);
        return;
    }

    char line[1000];
    while (fgets(line, sizeof(line), fptr)) {
        printf("%s", line);
    }

    fclose(fptr);
}