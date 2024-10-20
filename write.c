#include <stdio.h>
#include "helpers.h"

void writeProductToFile(product *prod);

void writeProductToFile(product *prod) {
    FILE *fptr = openFileHelper(productStore, "a+", __func__);
    fprintf(fptr, "id: %d, name: %s, description: %s,\n", prod->id, prod->name, prod->description);
    // fechando arquivo
    fclose(fptr);
}