#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ESTUDANTES 100
#define MAX_FICHAS 10
#define MAX_EXERCICIOS 10
#define MAX_SUBMISSOES 10000
#define MAX_STRING 100

// Estruturas de dados
typedef struct {
    int id;
    int numero;
    char nome[MAX_STRING];
    char email[MAX_STRING];
} Estudante;

typedef struct {
    int id;
    char nome[MAX_STRING];
    int num_exercicios;
    char data_publicacao[11];  // formato: dd/mm/aaaa
} Ficha;

typedef struct {
    int id;
    int id_ficha;
    char nome[MAX_STRING];
    char dificuldade[10];  // baixo, médio, elevado
    char tipo[10];         // algoritmo, código
} Exercicio;

typedef struct {
    int id;
    int id_estudante;
    int id_ficha;
    int id_exercicio;
    char data[11];        // formato: dd/mm/aaaa
    int num_linhas;
    int classificacao;    // 0-100
} Submissao;

// Estrutura para gerenciar os dados em memória
typedef struct {
    Estudante estudantes[MAX_ESTUDANTES];
    int num_estudantes;
    Ficha fichas[MAX_FICHAS];
    int num_fichas;
    Exercicio exercicios[MAX_FICHAS * MAX_EXERCICIOS];
    int num_exercicios;
    Submissao submissoes[MAX_SUBMISSOES];
    int num_submissoes;
} Sistema;

// Funções para Estudantes
int adicionar_estudante(Sistema *sys, int numero, const char *nome, const char *email) {
    if (sys->num_estudantes >= MAX_ESTUDANTES) {
        return 0;  // erro: limite atingido
    }
    
    Estudante est;
    est.id = sys->num_estudantes + 1;
    est.numero = numero;
    strncpy(est.nome, nome, MAX_STRING - 1);
    strncpy(est.email, email, MAX_STRING - 1);
    
    sys->estudantes[sys->num_estudantes] = est;
    sys->num_estudantes++;
    
    return 1;  // sucesso
}

int buscar_estudante(const Sistema *sys, int numero) {
    for (int i = 0; i < sys->num_estudantes; i++) {
        if (sys->estudantes[i].numero == numero) {
            return i;
        }
    }
    return -1;  // não encontrado
}

// Funções para Fichas
int adicionar_ficha(Sistema *sys, const char *nome, int num_exercicios, const char *data) {
    if (sys->num_fichas >= MAX_FICHAS) {
        return 0;
    }
    
    Ficha ficha;
    ficha.id = sys->num_fichas + 1;
    strncpy(ficha.nome, nome, MAX_STRING - 1);
    ficha.num_exercicios = num_exercicios;
    strncpy(ficha.data_publicacao, data, 10);
    
    sys->fichas[sys->num_fichas] = ficha;
    sys->num_fichas++;
    
    return 1;
}

// Menu principal
void mostrar_menu(void) {
    printf("\n=== Sistema de Gestão de Submissões ===\n");
    printf("1. Gestão de Estudantes\n");
    printf("2. Gestão de Fichas\n");
    printf("3. Gestão de Exercícios\n");
    printf("4. Gestão de Submissões\n");
    printf("5. Estatísticas\n");
    printf("6. Guardar Dados\n");
    printf("7. Carregar Dados\n");
    printf("0. Sair\n");
    printf("Escolha uma opção: ");
}

int main(void) {
    Sistema sys;
    // Inicialização direta das variáveis
    sys.num_estudantes = 0;
    sys.num_fichas = 0;
    sys.num_exercicios = 0;
    sys.num_submissoes = 0;
    
    int opcao;
    
    do {
        mostrar_menu();
        scanf("%d", &opcao);
        getchar();  // limpa o buffer
        
        switch (opcao) {
            case 1:
                // TODO: Implementar gestão de estudantes
                break;
            case 2:
                // TODO: Implementar gestão de fichas
                break;
            case 3:
                // TODO: Implementar gestão de exercícios
                break;
            case 4:
                // TODO: Implementar gestão de submissões
                break;
            case 5:
                // TODO: Implementar estatísticas
                break;
            case 6:
                // TODO: Implementar salvamento de dados
                break;
            case 7:
                // TODO: Implementar carregamento de dados
                break;
            case 0:
                printf("Programa encerrado.\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 0);
    
    return 0;
}