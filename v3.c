/* Aplicar tabelas hash em uma aplicação real e Manipular dados textuais usando hashing.
Crie um programa que funcione como um dicionário: o usuário pode adicionar palavras e seus
significados, buscar e remover termos. Utilize uma tabela hash para organizar os dados.
--------------------------------------------------------------------------------------*/

// BIBLIOTECAS E MÓDULOS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

// DECLARAÇÃO DE CONSTANTES
#define suces "\n>> Operação realizada com sucesso.\n\n"
#define falha "\n>> Algo deu errado, tente novamente.\n\n"
#define vazio "\n>> Nenhum item cadastrado no momento.\n\n"
#define max 50

// DECLARAÇÃO DE ESTRUTURAS
typedef struct dicio{
    char palavra[max];
    char signif[max*2];
    struct dicio *prox;
} dicio;
dicio *inicio = NULL;

// ========================= PROTÓTIPOS DE FUNÇÕES ======================= //
// POSSÍVEL IMPLEMENTAÇÃO DE FUNÇÃO (NÃO OBRIGATÓRIA): CARREGAR ARQUIVO
void Cadastrar(); // SALVAR TEMPORARIAMENTE NA LISTA
void Remover(); // FUNÇÃO ONDE DEVERÁ SER IMPLEMENTADO A HASH
void Exibir(); // EXIBIR CONTÉUDO DA LISTA E DO ARQUIVO
void Liberar(); // SALVAR ANTES DE LIBERAR MEMÓRIA
   
// ================================== FUNÇÃO PRINCIPAL ================================== //
int main(){
    setlocale(LC_ALL, "");
    int opc = 0;
    printf("\n========== DICIONÁRIO DIGITAL ==========\n\n");
    while(1){
        printf("[1] Cadastrar\n[2] Remover \n[3] Exibir \n[4] Sair \n>> ");
        while(scanf("%d", &opc) != 1)
            {printf("%s", falha); setbuf(stdin, NULL);}
        setbuf(stdin, NULL);
        switch (opc){
            case 1:   Cadastrar();              break;
            case 2:     Remover();              break;
            case 3:      Exibir();              break;
            case 4:     Liberar(); return 0;    break;
            default:    printf("%s", falha);    break;
        }
    }
}

// ================================= FUNÇÕES AUXILIARES ================================= //

// TUDO SERÁ ARMAZENADO TEMPORARIAMENTE NA LISTA, FUTURAMENTE TRANSFERINDO PARA O ARQUIVO
void Cadastrar(){
    dicio *novo = malloc(sizeof(dicio));
    if(novo == NULL)
        {printf("%s", falha); return;}

    printf("Digite uma palavra. \n>> ");
    fgets(novo->palavra, max, stdin);
    novo->palavra[strcspn(novo->palavra, "\n")] = 0;
    
    printf("Digite o significado. \n>> ");
    fgets(novo->signif, max, stdin);
    novo->signif[strcspn(novo->signif, "\n")] = 0;

    novo->prox = inicio;
    inicio = novo;
    
    printf("%s", suces);
}

// AQUI DEVERÁ SER IMPLEMENTADO O ALGORITMO HASH
void Remover(){
    if(inicio == NULL) 
        {printf("%s", vazio); return;}
    
    char palvr[max] = " ";
    
    printf("Qual palavra deseja remover? \n>> ");
    fgets(palvr, max, stdin);
    palvr[strcspn(palvr, "\n")] = 0;

    dicio *atual = inicio, *anter = NULL;

    while(atual && strcmp(atual->palavra, palvr) != 0){ 
        anter = atual;
        atual = atual->prox;            
    }
    if(atual == NULL)
        {printf("\n>> Não encontrado.\n\n"); return;}
    else if(anter == NULL)
        {inicio = atual->prox;}
    else
        {anter->prox = atual->prox;}
    
    printf("%s", suces);
    free(atual);
}

// IDEIA: EXIBIR TANTO O CONTEÚDO DA LISTA, QUANTO O DO ARQUIVO COMO TODO
// IMPLEMENTAR UM ALGORITMO QUE, SE HOUVER PALAVRAS EM AMBOS, EVITAR A REPETIÇÃO
// A ESTÉTICA DE EXIBIÇÃO DOS RESULTADOS PODEM SER APRIMORADAS 
void Exibir(){
    if(inicio==NULL)
        {printf("%s", vazio); return;}
    dicio *atual = inicio;
    while(atual){
        printf("Palavra: %s\n", atual->palavra);
        printf("Significado: %s\n", atual->signif);
        printf("------------\n\n");
        atual = atual->prox;
    }
}

// A IDEIA É IMPLEMENTAR AQUI UM MÉTODO DE SALVAR NO ARQUIVO ANTES DE LIBERAR MEMÓRIA
// ISTO É, ANTES DO PROGRAMA SAIR, ELE DEVERÁ SALVAR O CONTÉUDO DA LISTA ENCADEADA NO ARQUIVO
// SÓ DEPOIS, O CONTEÚDO DA LISTA ENCADEADA SERÁ APAGADO, LIBERANDO MEMÓRIA.
// OUTRA IDEIA: SE UMA PALAVRA DA LISTA ENCADEADA FOR REMOVIDA, A MESMA NO ARQUIVO SERÁ REMOVIDO AUTOMATICAMENTE
// A LISTA ENCADEADA SERVE DE MEMÓRIA PRINCIPAL (TEMPORÁRIA) E O ARQUIVO DE MEMÓRIA SECUNDÁRIA (PERMANENTE)
void Liberar(){
    if(inicio != NULL){
        dicio *atual = inicio, *temp = NULL;
        while (atual) {
            temp = atual;
            free(atual);
            atual = atual->prox;
        }
    }
    printf("%s", suces);
}

// ==================== CODIGOS DE REFERÊNCIA COM POSSÍVEIS UTILIDADES NO FUTURO ====================

/*
FILE *arquivo = fopen("Texto.txt", "a");
if(arquivo == NULL){ printf("%s", falha); exit(1); }

fprintf(arquivo, "\n%s: ", novo->palavra);
fprintf(arquivo, "%s", novo->signif);

fclose(arquivo);

FILE *arquivo = fopen("Texto.txt", "r");
if(arquivo == NULL) { printf("%s", falha); exit(1); }
char c = fgetc(arquivo);
while(c != EOF) { printf("%c", c); c = fgetc(arquivo); }
fclose(arquivo);
printf("\n----------\n\n");*/
