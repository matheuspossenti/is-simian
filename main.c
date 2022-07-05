#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define M 6
#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"

void imprimirMatriz(char**, int);
char** alocaMemoriaMatriz(int);
char* alocaMemoriaVetor(int);
void carregarMatriz(char**, int);
char* carregaVetor(char*, int, int);
int isSimian(char**, int);
int analisaLinha(char**, int, int);
int analisaColuna(char**, int, int);
int analisaDiagonalP(char**, int, int);
int analisaDiagonalS(char**, int, int);

int main () {
  char **dna;

  int tam;
  printf("Informe a quantidade de" CYN " linhas/colunas " RESET "da matriz: ");
  scanf("%d", &tam);

  dna = alocaMemoriaMatriz(tam);

  printf("\nPreencha a matriz com os caracteres " GRN "(A, T, G, C)\n" RESET);
  carregarMatriz(dna, tam);

  imprimirMatriz(dna, tam);

  int simian = 0;
  simian = isSimian(dna, tam);
  if (simian != 1) {
    printf(BLU "\nO usuário é humano\n" RESET);
  }
  printf(RED "Fim do Programa!\n" RESET);
}

// Aloca memoria para o vetor
char* alocaMemoriaVetor(int tam) {
  char *v;
  v = (char*) malloc(tam * sizeof(char));
  return v;
}

// Recebe do usuario uma sequencia de caracteres, que vai compor uma linha da matriz
char* carregaVetor(char* sequencia, int i, int tam) {
  printf("Informe a sequencia de DNA da linha " GRN "%d/%d \n" RESET, i+1 , tam);
  scanf("%s", sequencia);
}

// Recebe a linha e a coluna atual, e itera sobre as colunas, comparando se os 4 elementos são iguais
int analisaColuna(char** mat, int i, int j) {
  int c;
  for (c = j; c < j + 4; c++) {
    if (mat[i][c] == mat[i+1][c] && mat[i+1][c] == mat[i+2][c] && mat[i+2][c] == mat[i+3][c]) {
      printf(RED "Simio Detectado!\n" RESET);
      printf("Sequência de letras encontrada na coluna " RED "%d\n" RESET, c + 1);
      return 1;
    }
  }
}

// Recebe a linha e a coluna atual, e itera sobre as linhas, comparando se os 4 elementos são iguais
int analisaLinha(char** mat, int i, int j) {
  int l;
  for (l = i; l < i + 4; l++) {
    if (mat[l][j] == mat[l][j+1] && mat[l][j+1] == mat[l][j+2] && mat[l][j+2] == mat[l][j+3]) {
      printf(RED "Simio Detectado!\n" RESET);
      printf("Sequência de letras encontrada na linha " RED "%d\n" RESET, l + 1);
      return 1;
    }
  }
}

// Recebe a linha e a coluna atual e verifica se os elementos da diagonal principal são iguais
int analisaDiagonalP(char** mat, int i, int j) {
  if (mat[i][j] == mat[i+1][j+1] && mat[i+1][j+1] == mat[i+2][j+2] && mat[i+2][j+2] == mat[i+3][j+3]) {
    printf(RED "Simio Detectado!\n" RESET);
    printf("Sequência de letras encontrada na Diagonal Principal!\n");
    printf("Começando na Linha " RED "%d" RESET, i + 1);
    printf("e na Coluna " RED "%d\n" RESET, j+1);
    return 1;
  }
}

// Recebe a linha e a coluna atual e verifica se os elementos da diagonal secundaria são iguais
int analisaDiagonalS(char** mat, int i, int j) {
  if (mat[i][j+3] == mat[i+1][j+2] && mat[i+1][j+2] == mat[i+2][j+1] && mat[i+2][j+1] == mat[i+3][j]) {
    printf(RED "Simio Detectado!\n" RESET);
    printf("Sequência de letras encontrada na Diagonal Secundaria!\n");
    printf("Começando na Linha " RED "%d" RESET, i + 1);
    printf("e na Coluna " RED "%d\n" RESET, j+4);
    return 1;
  }
}

// Analisa a Matriz
int isSimian(char** mat, int tam) {
  int i, j;
  int simian = 0;
  // Como deve ser analisado uma area de 4x4, o for vai somente até coluna/linha -3
  for (i = 0; i < tam - 3; i++) {
    for (j = 0; j < tam - 3; j++) {
      simian = analisaLinha(mat, i, j);
      if (simian == 1) return 1;

      simian = analisaColuna(mat, i, j);
      if (simian == 1) return 1;

      simian = analisaDiagonalP(mat, i, j);
      if (simian == 1) return 1;
      
      simian = analisaDiagonalS(mat, i, j);
      if (simian == 1) return 1;
    }
  }
  return simian;
}

// Preenche a matriz linha por linha
void carregarMatriz(char** mat, int tam) {
  int i, j, k;
  for (i = 0; i < tam; i++) {
    char* sequencia = alocaMemoriaVetor(tam);
    carregaVetor(sequencia, i, tam);
    k = 0;
    for(j =0; j < tam; j++, k++) {
      mat[i][j] = sequencia[k];
    }
    free(sequencia);
  }
}

// Aloca memoria para a matriz
char** alocaMemoriaMatriz(int tam) {
  char **m;
  int i;
  m = (char**) malloc(sizeof(char *) * tam);
  if(m==NULL) {
     return (NULL);
  }
  for(i=0; i<tam;i++){
    m[i]=(char*) malloc(sizeof(char) * tam);
    if(m==NULL) {
     return (NULL);
    }
  }
  return(m);
}

// Imprime a matriz
void imprimirMatriz(char** mat, int tam) {
  int i, j;
  printf("\nMatriz de " GRN "DNA" RESET ":\n");
   for(i=0;i<tam;i++){
    for(j=0;j<tam;j++){
      printf("%*c|",3,mat[i][j]);
    }
    printf("\n");
  }
  printf("\n \n");
}