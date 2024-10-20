#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "write.c"
#include "read.c"

int main() {
    // product prod;
    // printf("Digite o nome produto: ");
    // scanf("%s", prod.name);
    // printf("Digite a descrição do produto: ");
    // scanf("%s", prod.description);
    // writeProductToFile(&prod);

    product p1 = {newProductID(), "Product1", "Description1"};

    product p2 = {newProductID(), "Product2", "Description2"};

    writeProductToFile(&p1);
    writeProductToFile(&p2);

    readProductByName("Product2");

    printf("ultima id: %d\n", getLastProductID());

    printf("Cabou\n");

    return 0;
}

