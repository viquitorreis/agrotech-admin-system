#ifndef HELPERS_H
#define HELPERS_H // define HELPERS_H para evitar redefinição

#include <stdio.h>

typedef char productName[50];
typedef char productDescription[100];

typedef struct {
    int id;
    productName name;
    productDescription description;
} product;

// ==== CAMINHOS DE ARQUIVOS ====

// local onde os produtos serão armazenados
const char productStore[] = "db/products_store.txt";

// arquivo das IDs dos produtos
const char productIDFile[] = "db/id.txt";


// ==== FUNÇÕES ====

// função openFileHelper vai abrir um arquivo e retornar um ponteiro para o arquivo
// recebe o nome do arquivo, o modo de abertura (append, read, write, etc) e o nome da função que chamou, para debugar erros
FILE *openFileHelper(const char *fileName, const char *mode, char const *callerFunctionName) {
    FILE *fptr = fopen(fileName, mode);
    if (fptr == NULL) {
        printf("Erro ao abrir arquivo. Função que chamou: %s\n", callerFunctionName);
        return NULL;
    }

    return fptr;
}

unsigned int getLastProductID() {
    FILE *fptr = openFileHelper(productIDFile, "r", __func__);
    if (fptr == NULL) {
        printf("Criando primeira id...\n");
        
        // criando o arquivo e escrevendo a primeira ID
        fptr = openFileHelper(productIDFile, "w", __func__);
        fprintf(fptr, "id: %d", 0);
        
        fclose(fptr);

        return 0;
    }

    char line[100];
    unsigned int lastID = 0;

    // pega a linha no arquivo, até o fim dele
    while (fgets(line, sizeof(line), fptr)) {
        // strstr vai buscar a substring productName dentro de line (checa se existe o produto na linha)
        if (strstr(line, "id:") != NULL) {
            // passando o número da ID depois de "id:"
            sscanf(line, "id: %u", &lastID);
            printf("Ultima id: %u\n", lastID);
            break;
        }
    }

    fclose(fptr);

    return lastID;
}

int newProductID() {
    int lastProductID = getLastProductID();
    FILE *fptr = openFileHelper(productIDFile, "w", __func__); // w modo de escrita
    if (fptr == NULL) {
        printf("Erro ao atualizar arquivo de ID\n");
        return -1;
    }
    int newProductID = lastProductID + 1;
    // escrevendo nova id no arquivo
    fprintf(fptr, "id: %u", newProductID);
    fclose(fptr);
    
    return newProductID;
}

#endif // necessário para evitar redefinição de variáveis e funções. Vai manter dentro desse escopo