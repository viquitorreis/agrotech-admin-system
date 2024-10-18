#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char name[50];
    char description[100];
} product;

int id = 0;
const char productsJsonPath[] = "products.json";

void writeProductToFile(product *prod);

int main() {
    product prod;
    printf("Digite o nome produto: ");
    scanf("%s", prod.name);
    printf("Digite a descrição do produto: ");
    scanf("%s", prod.description);

    writeProductToFile(&prod);
    printf("Cabou\n");

    return 0;
}

void writeProductToFile(product *prod) {
    FILE *fptr = fopen(productsJsonPath, "w");
    if (fptr == NULL) {
        printf("Erro ao abrir arquivo\n");
        return;
    }

    fprintf(fptr, "{\n");
    fprintf(fptr, "    \"name\": \"%s\",\n",prod->name);
    fprintf(fptr, "    \"description\": \"%s\"\n",prod->description);
    fprintf(fptr, "},\n");

    fclose(fptr);
}