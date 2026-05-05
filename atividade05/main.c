#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Definições de limites
#define MAX_LINHAS 1500
#define MAX_COLUNAS 512

// --- Funções de Ordenação ---

void bubble_sort(double *arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                double temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void selection_sort(double *arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx]) min_idx = j;
        }
        double temp = arr[min_idx];
        arr[min_idx] = arr[i];
        arr[i] = temp;
    }
}

void insertion_sort(double *arr, int n) {
    for (int i = 1; i < n; i++) {
        double key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}


void print_vetor(double *arr, int n) {
    for (int i = 0; i < n; i++) {
        printf("%.2f ", arr[i]);
    }
    printf("\n");
}

void test_algorithm(const char *name, void (*sort_func)(double*, int), double *original, int n) {
    double *copy = (double *)malloc(n * sizeof(double));
    memcpy(copy, original, n * sizeof(double));

    clock_t t0 = clock();
    sort_func(copy, n);
    clock_t t1 = clock();

    printf("\n%-15s: %f segundos\n", name, (double)(t1 - t0) / CLOCKS_PER_SEC);
    printf("Lista ordenada: ");
    print_vetor(copy, n);

    free(copy);
}

int main() {
    FILE *arquivo = fopen("dados.txt", "r");
    if (!arquivo) {
        printf("Erro: Certifique-se que 'dados.txt' esta na pasta do executavel.\n");
        return 1;
    }

    double *gpa_data = malloc(MAX_LINHAS * sizeof(double));
    char linha[MAX_COLUNAS];
    int count = 0;

    
    fgets(linha, MAX_COLUNAS, arquivo);

   
    while (fgets(linha, MAX_COLUNAS, arquivo) != NULL) {
       
        char *token = strtok(linha, ",");
        int coluna_atual = 1;

        while (token != NULL && coluna_atual < 7) {
            token = strtok(NULL, ",");
            coluna_atual++;
        }

        if (token != NULL) {
            gpa_data[count] = atof(token);
            count++;
        }
    }
    fclose(arquivo);

    printf("Registros carregados com sucesso: %d\n", count);
    printf("------------------------------------------\n");

    test_algorithm("Bubble Sort", bubble_sort, gpa_data, count);
    test_algorithm("Selection Sort", selection_sort, gpa_data, count);
    test_algorithm("Insertion Sort", insertion_sort, gpa_data, count);

    free(gpa_data);
    return 0;
}