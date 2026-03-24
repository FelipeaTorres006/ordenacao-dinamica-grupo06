#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//   VARIAVEIS GLOBAIS DE CONTAGEM

long long comparacoes = 0;
long long trocas      = 0;

//   UTILITARIOS

void trocar(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
    trocas++;
}

void exibir_vetor(int *v, int n) {
    printf("Estrutura atual: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", v[i]);
    }
    printf("\n");
}

void resetar_contadores(void) {
    comparacoes = 0;
    trocas      = 0;
}


//   1. BUBBLE SORT

void bubble_sort(int *v, int n) {
    resetar_contadores();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            comparacoes++;
            if (v[j] > v[j + 1]) {
                trocar(&v[j], &v[j + 1]);
            }
        }
    }
}


//   2. SELECTION SORT

void selection_sort(int *v, int n) {
    resetar_contadores();
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            comparacoes++;
            if (v[j] < v[min_idx]) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            trocar(&v[i], &v[min_idx]);
        }
    }
}


//   3. INSERTION SORT

void insertion_sort(int *v, int n) {
    resetar_contadores();
    for (int i = 1; i < n; i++) {
        int chave = v[i];
        int j     = i - 1;
        while (j >= 0) {
            comparacoes++;
            if (v[j] > chave) {
                v[j + 1] = v[j];
                trocas++;
                j--;
            } else {
                break;
            }
        }
        v[j + 1] = chave;
    }
}

//   4. QUICK SORT

int particionar(int *v, int low, int high) {
    int pivo = v[high];
    int i    = low - 1;
    for (int j = low; j < high; j++) {
        comparacoes++;
        if (v[j] <= pivo) {
            i++;
            trocar(&v[i], &v[j]);
        }
    }
    trocar(&v[i + 1], &v[high]);
    return i + 1;
}

void quick_sort_rec(int *v, int low, int high) {
    if (low < high) {
        int pi = particionar(v, low, high);
        quick_sort_rec(v, low, pi - 1);
        quick_sort_rec(v, pi + 1, high);
    }
}

void quick_sort(int *v, int n) {
    resetar_contadores();
    quick_sort_rec(v, 0, n - 1);
}

//   5. MERGE SORT

void merge(int *v, int left, int mid, int right) {
    int n1  = mid - left + 1;
    int n2  = right - mid;
    int *L  = (int *)malloc(n1 * sizeof(int));
    int *R  = (int *)malloc(n2 * sizeof(int));

    for (int i = 0; i < n1; i++) L[i] = v[left + i];
    for (int j = 0; j < n2; j++) R[j] = v[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        comparacoes++;
        if (L[i] <= R[j]) {
            v[k++] = L[i++];
        } else {
            v[k++] = R[j++];
            trocas++;
        }
    }
    while (i < n1) v[k++] = L[i++];
    while (j < n2) v[k++] = R[j++];

    free(L);
    free(R);
}

void merge_sort_rec(int *v, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        merge_sort_rec(v, left, mid);
        merge_sort_rec(v, mid + 1, right);
        merge(v, left, mid, right);
    }
}

void merge_sort(int *v, int n) {
    resetar_contadores();
    merge_sort_rec(v, 0, n - 1);
}

//   6. SHELL SORT

void shell_sort(int *v, int n) {
    resetar_contadores();
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int temp = v[i];
            int j    = i;
            while (j >= gap) {
                comparacoes++;
                if (v[j - gap] > temp) {
                    v[j] = v[j - gap];
                    trocas++;
                    j -= gap;
                } else {
                    break;
                }
            }
            v[j] = temp;
        }
    }
}

//   7. HEAP SORT

void heapify(int *v, int n, int i) {
    int maior  = i;
    int left   = 2 * i + 1;
    int right  = 2 * i + 2;

    if (left < n) {
        comparacoes++;
        if (v[left] > v[maior]) maior = left;
    }
    if (right < n) {
        comparacoes++;
        if (v[right] > v[maior]) maior = right;
    }
    if (maior != i) {
        trocar(&v[i], &v[maior]);
        heapify(v, n, maior);
    }
}

void heap_sort(int *v, int n) {
    resetar_contadores();
    for (int i = n / 2 - 1; i >= 0; i--) heapify(v, n, i);
    for (int i = n - 1; i > 0; i--) {
        trocar(&v[0], &v[i]);
        heapify(v, i, 0);
    }
}


//   MENU E FUNCAO PRINCIPAL

void exibir_menu(void) {
    printf("\n");
    printf("   ORDENACAO DINAMICA - ARVORES E GRAFOS\n");
    printf("\n");
    printf("Escolha o algoritmo:\n");
    printf("  1 - Bubble Sort\n");
    printf("  2 - Selection Sort\n");
    printf("  3 - Insertion Sort\n");
    printf("  4 - Quick Sort\n");
    printf("  5 - Merge Sort\n");
    printf("  6 - Shell Sort\n");
    printf("  7 - Heap Sort\n");
    printf("\n");
    printf("Opcao: ");
}

const char *nome_algoritmo(int opcao) {
    switch (opcao) {
        case 1: return "Bubble Sort";
        case 2: return "Selection Sort";
        case 3: return "Insertion Sort";
        case 4: return "Quick Sort";
        case 5: return "Merge Sort";
        case 6: return "Shell Sort";
        case 7: return "Heap Sort";
        default: return "Desconhecido";
    }
}

void executar_algoritmo(int opcao, int *v, int n) {
    switch (opcao) {
        case 1: bubble_sort(v, n);    break;
        case 2: selection_sort(v, n); break;
        case 3: insertion_sort(v, n); break;
        case 4: quick_sort(v, n);     break;
        case 5: merge_sort(v, n);     break;
        case 6: shell_sort(v, n);     break;
        case 7: heap_sort(v, n);      break;
    }
}

int main(void) {
    int opcao, quantidade;

    exibir_menu();
    scanf("%d", &opcao);

    if (opcao < 1 || opcao > 7) {
        printf("Opcao invalida!\n");
        return 1;
    }

    printf("\nAlgoritmo selecionado: %s\n", nome_algoritmo(opcao));
    printf("Quantos valores deseja inserir? ");
    scanf("%d", &quantidade);

    if (quantidade <= 0) {
        printf("Quantidade invalida!\n");
        return 1;
    }

    int *vetor = (int *)malloc(quantidade * sizeof(int));
    if (vetor == NULL) {
        printf("Erro ao alocar memoria!\n");
        return 1;
    }

    printf("\n");
    for (int i = 0; i < quantidade; i++) {
        printf("Digite o valor: ");
        scanf("%d", &vetor[i]);

        // Ordena apos cada insercao
        executar_algoritmo(opcao, vetor, i + 1);

        // Exibe o vetor ordenado
        exibir_vetor(vetor, i + 1);

        // Exibe os contadores
        printf("Comparacoes: %lld", comparacoes);
        if (opcao != 5) {  // Merge Sort usa movimentacoes no lugar de trocas
            printf(" | Trocas: %lld\n", trocas);
        } else {
            printf(" | Movimentacoes: %lld\n", trocas);
        }
        printf("\n");
    }

    free(vetor);
    return 0;
}