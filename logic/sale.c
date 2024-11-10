#include "../helpers/helpers.h"

#define MAX_VENDAS 100

const char saleStoreFilePath[] = "db/sale_store.txt";

int validateSale(Venda newSale) {
    Produto product = getProductByIDHelper(newSale.IDProduto);
    if (product.ID[0] == '\0') {
        printf("Produto nao encontrado!\n");
        return 0;
    }

    printf("Quantidade no estoque: %d\n", product.quantidadeNoEstoque);

    if (product.quantidadeNoEstoque < newSale.quantidadeComprada) {
        printf("Quantidade insuficiente no estoque!\n");
        return 0;
    }

    product.quantidadeNoEstoque -= newSale.quantidadeComprada;
    printf("Nova quantidade no estoque: %d\n", product.quantidadeNoEstoque);
    int newQuantity = newProductQuantity(product);

    printf("Venda realizada com sucesso!\n");
    printf("Nova quantidade do produto: %d\n", newQuantity);
}

void insertSale(Venda newSale) {
    if (!validateSale(newSale)) {
        return;
    }

    FILE *fptr = OPEN_FILE_HELPER(saleStoreFilePath, "a+");
    if (fptr == NULL) {
        fptr = OPEN_FILE_HELPER(saleStoreFilePath, "w");
        if (fptr == NULL) {
            return;
        }
    }

    fprintf(fptr, "cpfCliente: %s, ID do produto: %s, quantidadeComprada: %d\n",
        newSale.cpfCliente,
        newSale.IDProduto,
        newSale.quantidadeComprada
    );

    fclose(fptr);
}

void doSale() {
    int salesCount = getFileLinesCountHelper(saleStoreFilePath);

    if (salesCount < MAX_VENDAS) {
        Venda newSale;

        printf("Digite o cpf do cliente (apenas numeros): ");
        scanf("%s", newSale.cpfCliente);

        if (!checkCustomerExistsByCPFHelper(newSale.cpfCliente)) {
            printf("Cliente nao encontrado!\n");
            return;
        }

        printf("Digite a ID do produto: ");
        scanf("%s", newSale.IDProduto);

        if (!checkProductExistsByIDHelper(newSale.IDProduto)) {
            printf("Produto nao encontrado!\n");
            return;
        }

        printf("Digite a quantidade comprada: ");
        scanf("%d", &newSale.quantidadeComprada);

        insertSale(newSale);
    } else {
        printf("Nao foi possivel realizar a venda pois o limite de vendas cadastradas (100) ja foi atingido.\n");
    }
}