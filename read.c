#include <stdio.h>
#include "helpers.h"

// vai retornar um ponteiro para todos os produtos que tiverem o nome productName
product *getProductsByName(char *productName, int *count) {
    FILE *fptr = openFileHelper(productStore, "r", __func__);
    char line[200];
    product *matchedProducts = NULL;
    *count = 0;

    // fgets vai ler uma linha do arquivo e armazenar em line
    while (fgets(line, sizeof(line), fptr)) {
        // strstr vai buscar a substring productName dentro de line (checa se existe o produto na linha)
        if (strstr(line, productName) != NULL) {
            // realoca o ponteiro para o tamanho atual + 1
            matchedProducts = (product *) realloc(matchedProducts, (*count + 1) * sizeof(product));
        
            // como o produto existe, o sscanf vai armazenar os valores dentro do ponteiro matchedProducts
            sscanf(
                line,
                "id: %d, name: %49[^,], description: %99[^,],",
                &matchedProducts[*count].id,
                matchedProducts[*count].name,
                matchedProducts[*count].description
            );
            
            (*count)++;
        }
    }

    fclose(fptr);

    return matchedProducts;
}

void readProductByName(char *productName) {
    int productCount = 0;
    product *products = getProductsByName(productName, &productCount);
    if (products == NULL || productCount == 0) {
        printf("Produto não encontrado\n");
        return;
    }

    printf("Quantidade de produtos encontrados: %d\n", productCount);

    for (int i = 0; i < productCount; i++) {
        printf("Produto encontrado: [id]: %d [name]: %s [description]: %s\n", products[i].id, products[i].name, products[i].description);
    }
    
    free(products);
}