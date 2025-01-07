#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ESTUDANTES 100
#define MAX_FICHAS 10
#define MAX_EXERCICIOS 10
#define MAX_SUBMISSOES 10000
#define MAX_STRING 100

// Estrutura para Data
typedef struct {
    int dia, mes, ano;
} Data;

// Estruturas principais
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
    Data data_publicacao;
} Ficha;

typedef struct {
    int id;
    int id_ficha;
    char nome[MAX_STRING];
    char dificuldade[10];
    char tipo[10];
} Exercicio;

typedef struct {
    int id;
    int id_estudante;
    int id_ficha;
    int id_exercicio;
    Data data;
    int num_linhas;
    int classificacao;
} Submissao;

// Funções de Leitura de Dados Básicos
int ler_numero(char texto[], int min, int max) {
    int valor;
    do {
        printf("\n%s [%d-%d]--> ", texto, min, max);
        scanf("%d", &valor);
        if (valor < min || valor > max)
            printf("\nValor incorreto");
    } while (valor < min || valor > max);
    return valor;
}

Data ler_data() {
    Data data;
    int meses[] = {31,28,31,30,31,30,31,31,30,31,30,31};
    
    data.ano = ler_numero("Indique o ano entre", 2024, 2025);
    data.mes = ler_numero("Indique o mes entre", 1, 12);
    data.dia = ler_numero("Indique o dia entre", 1, meses[data.mes - 1]);
    
    return data;
}

void ler_dificuldade(char dificuldade[]) {
    int opcao;
    printf("\nIndique a dificuldade do exercicio");
    printf("\n1 - Baixo");
    printf("\n2 - Medio");
    printf("\n3 - Elevado");
    
    do {
        printf("\nOpcao--> ");
        scanf("%d", &opcao);
    } while (opcao < 1 || opcao > 3);
    
    switch(opcao) {
        case 1: strcpy(dificuldade, "baixo"); break;
        case 2: strcpy(dificuldade, "medio"); break;
        case 3: strcpy(dificuldade, "elevado"); break;
    }
}

void ler_tipo(char tipo[]) {
    int opcao;
    printf("\nIndique o tipo do exercicio");
    printf("\n1 - Algoritmo");
    printf("\n2 - Codigo");
    
    do {
        printf("\nOpcao--> ");
        scanf("%d", &opcao);
    } while (opcao != 1 && opcao != 2);
    
    if (opcao == 1)
        strcpy(tipo, "algoritmo");
    else
        strcpy(tipo, "codigo");
}

// MÓDULO DE ESTUDANTES
int ler_estudante(Estudante estudantes[], int contador) {
    estudantes[contador].id = contador + 1;
    estudantes[contador].numero = ler_numero("Indique o numero do estudante entre", 2000000, 2999999);
    
    printf("\nIndique o nome do estudante: ");
    scanf(" %99[^\n]s", estudantes[contador].nome);
    
    printf("\nIndique o email do estudante: ");
    scanf(" %99[^\n]s", estudantes[contador].email);
    
    return contador + 1;
}

void mostrar_estudantes(Estudante estudantes[], int contador) {
    printf("\n##### ESTUDANTES #####");
    for (int i = 0; i < contador; i++) {
        printf("\n---------------------------------");
        printf("\nID: %d", estudantes[i].id);
        printf("\nNumero: %d", estudantes[i].numero);
        printf("\nNome: %s", estudantes[i].nome);
        printf("\nEmail: %s", estudantes[i].email);
    }
    printf("\n---------------------------------");
    printf("\nTotal de Estudantes: %d", contador);
    getchar(); getchar();
}

// MÓDULO DE FICHAS
int ler_ficha(Ficha fichas[], int contador) {
    fichas[contador].id = contador + 1;
    
    printf("\nIndique o nome da ficha: ");
    scanf(" %99[^\n]s", fichas[contador].nome);
    
    fichas[contador].num_exercicios = ler_numero("Indique o numero de exercicios", 1, MAX_EXERCICIOS);
    fichas[contador].data_publicacao = ler_data();
    
    return contador + 1;
}

void mostrar_fichas(Ficha fichas[], int contador) {
    printf("\n##### FICHAS DE EXERCICIOS #####");
    for (int i = 0; i < contador; i++) {
        printf("\n---------------------------------");
        printf("\nID: %d", fichas[i].id);
        printf("\nNome: %s", fichas[i].nome);
        printf("\nNumero de Exercicios: %d", fichas[i].num_exercicios);
        printf("\nData: %d/%d/%d", 
               fichas[i].data_publicacao.dia,
               fichas[i].data_publicacao.mes,
               fichas[i].data_publicacao.ano);
    }
    printf("\n---------------------------------");
    printf("\nTotal de Fichas: %d", contador);
    getchar(); getchar();
}

// MÓDULO DE EXERCÍCIOS
int ler_exercicio(Exercicio exercicios[], int contador, int id_ficha) {
    exercicios[contador].id = contador + 1;
    exercicios[contador].id_ficha = id_ficha;
    
    printf("\nIndique o nome do exercicio: ");
    scanf(" %99[^\n]s", exercicios[contador].nome);
    
    ler_dificuldade(exercicios[contador].dificuldade);
    ler_tipo(exercicios[contador].tipo);
    
    return contador + 1;
}

void mostrar_exercicios(Exercicio exercicios[], int contador) {
    printf("\n##### EXERCICIOS #####");
    for (int i = 0; i < contador; i++) {
        printf("\n---------------------------------");
        printf("\nID: %d", exercicios[i].id);
        printf("\nID Ficha: %d", exercicios[i].id_ficha);
        printf("\nNome: %s", exercicios[i].nome);
        printf("\nDificuldade: %s", exercicios[i].dificuldade);
        printf("\nTipo: %s", exercicios[i].tipo);
    }
    printf("\n---------------------------------");
    printf("\nTotal de Exercicios: %d", contador);
    getchar(); getchar();
}

// MÓDULO DE SUBMISSÕES
int ler_submissao(Submissao submissoes[], int contador, 
                  Estudante estudantes[], int num_estudantes,
                  Ficha fichas[], int num_fichas,
                  Exercicio exercicios[], int num_exercicios) {
                      
    int id_estudante, id_ficha, id_exercicio;
    
    // Verificar se existem dados necessários
    if (num_estudantes == 0 || num_fichas == 0 || num_exercicios == 0) {
        printf("\nNao existem dados suficientes para registrar submissao!");
        getchar(); getchar();
        return contador;
    }
    
    // Preencher dados
    submissoes[contador].id = contador + 1;
    
    // Selecionar estudante
    mostrar_estudantes(estudantes, num_estudantes);
    id_estudante = ler_numero("Indique o ID do estudante", 1, num_estudantes);
    submissoes[contador].id_estudante = id_estudante;
    
    // Selecionar ficha
    mostrar_fichas(fichas, num_fichas);
    id_ficha = ler_numero("Indique o ID da ficha", 1, num_fichas);
    submissoes[contador].id_ficha = id_ficha;
    
    // Selecionar exercício
    mostrar_exercicios(exercicios, num_exercicios);
    id_exercicio = ler_numero("Indique o ID do exercicio", 1, num_exercicios);
    submissoes[contador].id_exercicio = id_exercicio;
    
    submissoes[contador].data = ler_data();
    submissoes[contador].num_linhas = ler_numero("Indique o numero de linhas", 1, 1000);
    submissoes[contador].classificacao = ler_numero("Indique a classificacao", 0, 100);
    
    return contador + 1;
}

void mostrar_submissoes(Submissao submissoes[], int contador) {
    printf("\n##### SUBMISSOES #####");
    for (int i = 0; i < contador; i++) {
        printf("\n---------------------------------");
        printf("\nID: %d", submissoes[i].id);
        printf("\nID Estudante: %d", submissoes[i].id_estudante);
        printf("\nID Ficha: %d", submissoes[i].id_ficha);
        printf("\nID Exercicio: %d", submissoes[i].id_exercicio);
        printf("\nData: %d/%d/%d", 
               submissoes[i].data.dia,
               submissoes[i].data.mes,
               submissoes[i].data.ano);
        printf("\nNumero de Linhas: %d", submissoes[i].num_linhas);
        printf("\nClassificacao: %d", submissoes[i].classificacao);
    }
    printf("\n---------------------------------");
    printf("\nTotal de Submissoes: %d", contador);
    getchar(); getchar();
}

// MÓDULO DE ESTATÍSTICAS
void calcular_estatisticas(Submissao submissoes[], int num_submissoes,
                          Estudante estudantes[], int num_estudantes,
                          Ficha fichas[], int num_fichas) {
                              
    int id_estudante, id_ficha;
    int total_submissoes;
    float media_classificacoes;
    float percentagem_exercicios;
    
    // Mostrar estudantes disponíveis
    mostrar_estudantes(estudantes, num_estudantes);
    id_estudante = ler_numero("Indique o ID do estudante para estatisticas", 1, num_estudantes);
    
    // Calcular total de submissões do estudante
    total_submissoes = 0;
    float soma_classificacoes = 0;
    for (int i = 0; i < num_submissoes; i++) {
        if (submissoes[i].id_estudante == id_estudante) {
            total_submissoes++;
            soma_classificacoes += submissoes[i].classificacao;
        }
    }
    
    // Calcular média das classificações
    media_classificacoes = total_submissoes > 0 ? soma_classificacoes / total_submissoes : 0;
    
    printf("\n\nEstatisticas do Estudante ID %d:", id_estudante);
    printf("\nTotal de submissoes: %d", total_submissoes);
    printf("\nMedia das classificacoes: %.2f", media_classificacoes);
    
    // Calcular percentagem de exercícios por ficha
    printf("\n\nPercentagem de exercicios resolvidos por ficha:");
    for (int i = 0; i < num_fichas; i++) {
        int exercicios_resolvidos = 0;
        for (int j = 0; j < num_submissoes; j++) {
            if (submissoes[j].id_estudante == id_estudante && 
                submissoes[j].id_ficha == fichas[i].id) {
                exercicios_resolvidos++;
            }
        }
        percentagem_exercicios = (float)exercicios_resolvidos / fichas[i].num_exercicios * 100;
        printf("\nFicha %d: %.2f%%", fichas[i].id, percentagem_exercicios);
    }
    
    getchar(); getchar();
}

// FUNÇÕES DE ARQUIVO
void gravar_dados(Estudante estudantes[], int num_estudantes,
                 Ficha fichas[], int num_fichas,
                 Exercicio exercicios[], int num_exercicios,
                 Submissao submissoes[], int num_submissoes) {
                     
    FILE *ficheiro = fopen("dados.dat", "wb");
    
    if (ficheiro != NULL) {
        // Gravar contadores
        fwrite(&num_estudantes, sizeof(int), 1, ficheiro);
        fwrite(&num_fichas, sizeof(int), 1, ficheiro);
        fwrite(&num_exercicios, sizeof(int), 1, ficheiro);
        fwrite(&num_submissoes, sizeof(int), 1, ficheiro);
        
        // Gravar dados
        fwrite(estudantes, sizeof(Estudante), num_estudantes, ficheiro);
        fwrite(fichas, sizeof(Ficha), num_fichas, ficheiro);
        fwrite(exercicios, sizeof(Exercicio), num_exercicios, ficheiro);
        fwrite(submissoes, sizeof(Submissao), num_submissoes, ficheiro);
        
        fclose(ficheiro);
        printf("\nDados gravados com sucesso!");
    } else {
        printf("\nErro ao gravar dados!");
    }
    getchar(); getchar();
}

int ler_dados_arquivo(Estudante estudantes[], int *num_estudantes,
                     Ficha fichas[], int *num_fichas,
                     Exercicio exercicios[], int *num_exercicios,
                     Submissao submissoes[], int *num_submissoes) {
                         
    FILE *ficheiro = fopen("dados.dat", "rb");
    
    if (ficheiro == NULL) {
        printf("\nNao foi possivel abrir o ficheiro!");
        return 0;
    }
    
    // Ler contadores
    fread(num_estudantes, sizeof(int), 1, ficheiro);
    fread(num_fichas, sizeof(int), 1, ficheiro);
    fread(num_exercicios, sizeof(int), 1, ficheiro);
    fread(num_submissoes, sizeof(int), 1, ficheiro);
    
    // Ler dados
    fread(estudantes, sizeof(Estudante), *num_estudantes, ficheiro);
    fread(fichas, sizeof(Ficha), *num_fichas, ficheiro);
    fread(exercicios, sizeof(Exercicio), *num_exercicios, ficheiro);
    fread(submissoes, sizeof(Submissao), *num_submissoes, ficheiro);
    
    fclose(ficheiro);
    printf("\nDados carregados com sucesso!");
    return 1;
}

// Menus
int ler_opcao_menu(int min, int max) {
    int opcao;
    char input[100];
    int valido;
    
    do {
        printf("\nOpcao--> ");
        scanf(" %99[^\n]", input);
        valido = 1;
        
        // Limpar o buffer do teclado
        while (getchar() != '\n');
        
        // Verificar se é um número
        for(int i = 0; input[i] != '\0'; i++) {
            if(input[i] < '0' || input[i] > '9') {
                valido = 0;
                break;
            }
        }
        
        if(valido) {
            opcao = atoi(input);
            if(opcao >= min && opcao <= max) {
                return opcao;
            }
        }
        
        printf("\nOpcao invalida! Digite um numero entre %d e %d.", min, max);
    } while(1);
}

int menu_principal() {
    printf("\n\t##### MENU PRINCIPAL #####");
    printf("\n1 - Gestao de Estudantes");
    printf("\n2 - Gestao de Fichas");
    printf("\n3 - Gestao de Exercicios");
    printf("\n4 - Gestao de Submissoes");
    printf("\n5 - Estatisticas");
    printf("\n6 - Gravar Dados");
    printf("\n7 - Carregar Dados");
    printf("\n0 - Sair");
    return ler_opcao_menu(0, 7);
}

int menu_estudantes() {
    printf("\n\t##### MENU ESTUDANTES #####");
    printf("\n1 - Inserir novo estudante");
    printf("\n2 - Listar estudantes");
    printf("\n0 - Voltar");
    return ler_opcao_menu(0, 2);
}

int menu_fichas() {
    printf("\n\t##### MENU FICHAS #####");
    printf("\n1 - Inserir nova ficha");
    printf("\n2 - Listar fichas");
    printf("\n0 - Voltar");
    return ler_opcao_menu(0, 2);
}

int menu_exercicios() {
    printf("\n\t##### MENU EXERCICIOS #####");
    printf("\n1 - Inserir novo exercicio");
    printf("\n2 - Listar exercicios");
    printf("\n0 - Voltar");
    return ler_opcao_menu(0, 2);
}

int menu_submissoes() {
    printf("\n\t##### MENU SUBMISSOES #####");
    printf("\n1 - Registar nova submissao");
    printf("\n2 - Listar submissoes");
    printf("\n0 - Voltar");
    return ler_opcao_menu(0, 2);
}

int main() {
    // Declaração das estruturas de dados
    Estudante estudantes[MAX_ESTUDANTES];
    Ficha fichas[MAX_FICHAS];
    Exercicio exercicios[MAX_EXERCICIOS * MAX_FICHAS];
    Submissao submissoes[MAX_SUBMISSOES];
    
    // Contadores
    int num_estudantes = 0;
    int num_fichas = 0;
    int num_exercicios = 0;
    int num_submissoes = 0;
    
    int opcao_principal, opcao_secundaria;
    
    do {
        system("cls");  // Limpa a tela
        opcao_principal = menu_principal();
        
        switch (opcao_principal) {
            case 1:  // Gestão de Estudantes
                do {
                    system("cls");
                    opcao_secundaria = menu_estudantes();
                    
                    switch (opcao_secundaria) {
                        case 1:  // Inserir
                            if (num_estudantes < MAX_ESTUDANTES) {
                                num_estudantes = ler_estudante(estudantes, num_estudantes);
                            } else {
                                printf("\nLimite de estudantes atingido!");
                                getchar(); getchar();
                            }
                            break;
                        case 2:  // Listar
                            mostrar_estudantes(estudantes, num_estudantes);
                            break;
                    }
                } while (opcao_secundaria != 0);
                break;
                
            case 2:  // Gestão de Fichas
                do {
                    system("cls");
                    opcao_secundaria = menu_fichas();
                    
                    switch (opcao_secundaria) {
                        case 1:  // Inserir
                            if (num_fichas < MAX_FICHAS) {
                                num_fichas = ler_ficha(fichas, num_fichas);
                            } else {
                                printf("\nLimite de fichas atingido!");
                                getchar(); getchar();
                            }
                            break;
                        case 2:  // Listar
                            mostrar_fichas(fichas, num_fichas);
                            break;
                    }
                } while (opcao_secundaria != 0);
                break;
                
            case 3:  // Gestão de Exercícios
                do {
                    system("cls");
                    opcao_secundaria = menu_exercicios();
                    
                    switch (opcao_secundaria) {
                        case 1:  // Inserir
                            if (num_exercicios < MAX_EXERCICIOS * MAX_FICHAS) {
                                if (num_fichas > 0) {
                                    mostrar_fichas(fichas, num_fichas);
                                    int id_ficha = ler_numero("Indique o ID da ficha", 1, num_fichas);
                                    num_exercicios = ler_exercicio(exercicios, num_exercicios, id_ficha);
                                } else {
                                    printf("\nNao existem fichas cadastradas!");
                                    getchar(); getchar();
                                }
                            } else {
                                printf("\nLimite de exercicios atingido!");
                                getchar(); getchar();
                            }
                            break;
                        case 2:  // Listar
                            mostrar_exercicios(exercicios, num_exercicios);
                            break;
                    }
                } while (opcao_secundaria != 0);
                break;
                
            case 4:  // Gestão de Submissões
                do {
                    system("cls");
                    opcao_secundaria = menu_submissoes();
                    
                    switch (opcao_secundaria) {
                        case 1:  // Inserir
                            if (num_submissoes < MAX_SUBMISSOES) {
                                num_submissoes = ler_submissao(submissoes, num_submissoes,
                                                             estudantes, num_estudantes,
                                                             fichas, num_fichas,
                                                             exercicios, num_exercicios);
                            } else {
                                printf("\nLimite de submissoes atingido!");
                                getchar(); getchar();
                            }
                            break;
                        case 2:  // Listar
                            mostrar_submissoes(submissoes, num_submissoes);
                            break;
                    }
                } while (opcao_secundaria != 0);
                break;
                
            case 5:  // Estatísticas
                if (num_submissoes > 0) {
                    calcular_estatisticas(submissoes, num_submissoes,
                                        estudantes, num_estudantes,
                                        fichas, num_fichas);
                } else {
                    printf("\nNao existem submissoes registradas!");
                    getchar(); getchar();
                }
                break;
                
            case 6:  // Gravar Dados
                gravar_dados(estudantes, num_estudantes,
                           fichas, num_fichas,
                           exercicios, num_exercicios,
                           submissoes, num_submissoes);
                break;
                
            case 7:  // Carregar Dados
                if (ler_dados_arquivo(estudantes, &num_estudantes,
                                    fichas, &num_fichas,
                                    exercicios, &num_exercicios,
                                    submissoes, &num_submissoes)) {
                    printf("\nDados carregados com sucesso!");
                } else {
                    printf("\nErro ao carregar dados!");
                }
                getchar(); getchar();
                break;
        }
    } while (opcao_principal != 0);
    
    return 0;
}