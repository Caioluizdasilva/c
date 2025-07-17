#include <stdlib.h>
#include <time.h>
#include <math.h>

#define tamanho 150
#define define_linhas 20
#define define_colunas 20

float calculaMedia(int vet[], int t);
float calculaDesvioPadrao(int vet[], int t);
void ordenaVetorC(int vet[], int t);
void ordenaVetorD(int vet[], int t);
float calculaMediana(int vet[], int t);
int ExisteElemento(int vet[], int t, int n);
void preencheVetorSemRepetir(int vet[], int t);
void imprimeElementosComuns(int vetA[], int tA, int vetB[], int tB);

void preencheVetor(int vet[], int t, int max);
void imprimeVetor(int vet[], int t);

int main() {
    srand(time(NULL));

    int vetorPrincipal[tamanho];
    int vetorA[30];
    int vetorB[40];

    printf("--- Testando funcoes auxiliares ---\n");
    preencheVetor(vetorPrincipal, tamanho, 1000);
    printf("Vetor principal com %d elementos (aleatorios):\n", tamanho);
    imprimeVetor(vetorPrincipal, tamanho);

    printf("\n\n--- Testando funcoes do exercicio ---\n");

    float media = calculaMedia(vetorPrincipal, tamanho);
    printf("\n1. Media dos elementos do vetor: %.2f\n", media);

    float desvio = calculaDesvioPadrao(vetorPrincipal, tamanho);
    printf("\n2. Desvio Padrao dos elementos do vetor: %.2f\n", desvio);

    printf("\n3. Ordenando o vetor em ordem crescente...\n");
    ordenaVetorC(vetorPrincipal, tamanho);
    imprimeVetor(vetorPrincipal, tamanho);

    printf("\n\n4. Ordenando o vetor em ordem decrescente...\n");
    ordenaVetorD(vetorPrincipal, tamanho);
    imprimeVetor(vetorPrincipal, tamanho);
    
    ordenaVetorC(vetorPrincipal, tamanho); 

    float mediana = calculaMediana(vetorPrincipal, tamanho);
    printf("\n\n5. Mediana do vetor: %.2f\n", mediana);

    int numeroBusca = vetorPrincipal[10];
    int numeroNaoExiste = 1001;
    printf("\n6. Buscando elementos no vetor (ordenado)...\n");
    printf("Buscando o numero %d... Resultado: %s\n", numeroBusca, ExisteElemento(vetorPrincipal, tamanho, numeroBusca) ? "Encontrado (retornou 1)" : "Nao encontrado");
    printf("Buscando o numero %d... Resultado: %s\n", numeroNaoExiste, ExisteElemento(vetorPrincipal, tamanho, numeroNaoExiste) ? "Encontrado" : "Nao encontrado (retornou 0)");

    int vetorSemRepeticao[20];
    int tamVetorSR = 20;
    printf("\n\n7. Preenchendo um vetor de tamanho %d sem repeticao (numeros de 0 a 99):\n", tamVetorSR);
    preencheVetorSemRepetir(vetorSemRepeticao, tamVetorSR);
    imprimeVetor(vetorSemRepeticao, tamVetorSR);

    printf("\n\n8. Imprimindo elementos comuns entre dois vetores:\n");
    preencheVetor(vetorA, 30, 50);
    preencheVetor(vetorB, 40, 50);
    
    printf("\nVetor A:\n");
    imprimeVetor(vetorA, 30);
    printf("\nVetor B:\n");
    imprimeVetor(vetorB, 40);

    printf("\n\nElementos comuns:\n");
    imprimeElementosComuns(vetorA, 30, vetorB, 40);
    
    return 0;
}

float calculaMedia(int vet[], int t) {
    long long soma = 0;
    for (int i = 0; i < t; i++) {
        soma += vet[i];
    }
    return (float)soma / t;
}

float calculaDesvioPadrao(int vet[], int t) {
    if (t == 0) return 0.0;
    
    float media = calculaMedia(vet, t);
    float somaDiferencasQuadrado = 0;

    for (int i = 0; i < t; i++) {
        somaDiferencasQuadrado += pow(vet[i] - media, 2);
    }

    return sqrt(somaDiferencasQuadrado / t);
}

void ordenaVetorC(int vet[], int t) {
    int i, j, temp;
    for (i = 0; i < t - 1; i++) {
        for (j = 0; j < t - i - 1; j++) {
            if (vet[j] > vet[j + 1]) {
                temp = vet[j];
                vet[j] = vet[j + 1];
                vet[j + 1] = temp;
            }
        }
    }
}

void ordenaVetorD(int vet[], int t) {
    int i, j, temp;
    for (i = 0; i < t - 1; i++) {
        for (j = 0; j < t - i - 1; j++) {
            if (vet[j] < vet[j + 1]) {
                temp = vet[j];
                vet[j] = vet[j + 1];
                vet[j + 1] = temp;
            }
        }
    }
}

float calculaMediana(int vet[], int t) {
    ordenaVetorC(vet, t);

    if (t % 2 != 0) {
        return (float)vet[t / 2];
    } else {
        int meio1 = vet[(t / 2) - 1];
        int meio2 = vet[t / 2];
        return (float)(meio1 + meio2) / 2.0;
    }
}

int ExisteElemento(int vet[], int t, int n) {
    for (int i = 0; i < t; i++) {
        if (vet[i] == n) {
            return 1;
        }
    }
    return 0;
}

void preencheVetorSemRepetir(int vet[], int t) {
     if (t > 100) {
        printf("Erro: O tamanho do vetor e maior que o range de numeros unicos (0-99).\n");
        return;
    }

    int i = 0;
    while(i < t) {
        int numAleatorio = rand() % 100;
        if (!ExisteElemento(vet, i, numAleatorio)) {
            vet[i] = numAleatorio;
            i++;
        }
    }
}

void imprimeElementosComuns(int vetA[], int tA, int vetB[], int tB) {
    ordenaVetorC(vetB, tB);

    int ultimoComumImpresso = -1;

    for (int i = 0; i < tA; i++) {
        if (vetA[i] != ultimoComumImpresso && ExisteElemento(vetB, tB, vetA[i])) {
            printf("%d ", vetA[i]);
            ultimoComumImpresso = vetA[i];
        }
    }
    printf("\n");
}

void preencheVetor(int vet[], int t, int max) {
    for (int i = 0; i < t; i++) {
        vet[i] = rand() % max;
    }
}

void imprimeVetor(int vet[], int t) {
    printf("[ ");
    for (int i = 0; i < t; i++) {
        printf("%d ", vet[i]);
        if ((i + 1) % 20 == 0 && i < t -1) {
            printf("\n  ");
        }
    }
    printf("]\n");
}