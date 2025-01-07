#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ESTUDANTES 100
#define MAX_FICHAS 10
#define MAX_EXERCICIOS 10
#define MAX_SUBMISSOES 10000
#define MAX_STRING 100

// Estrutura de data
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

// Funções auxiliares básicas
int tem_letra(char c) {
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

int tem_numero(char c) {
    return (c >= '0' && c <= '9');
}

int tem_alfanumerico(char c) {
    return tem_letra(c) || tem_numero(c);
}

// Validação de email básica
int validar_email(const char *email) {
    int tem_arroba = 0, tem_ponto = 0;
    int pos_arroba = -1, pos_ponto = -1;
    int len = strlen(email);
    
    if (len == 0 || len >= MAX_STRING) return 0;
    
    for (int i = 0; i < len; i++) {
        if (!tem_alfanumerico(email[i]) && email[i] != '@' && email[i] != '.' && 
            email[i] != '-' && email[i] != '_') return 0;
        if (email[i] == '@') {
            if (tem_arroba) return 0;
            tem_arroba = 1;
            pos_arroba = i;
        }
        if (email[i] == '.') {
            tem_ponto = 1;
            pos_ponto = i;
        }
    }
    
    return tem_arroba && tem_ponto && pos_arroba > 0 && 
           pos_ponto > pos_arroba + 1 && pos_ponto < len - 1;
}

void ler_email(char *email) {
    char input[MAX_STRING];
    int valido = 0;
    
    do {
        printf("\nIndique o email do estudante: ");
        if (fgets(input, MAX_STRING, stdin) != NULL) {
            input[strcspn(input, "\n")] = '\0';
            if (validar_email(input)) {
                strcpy(email, input);
                valido = 1;
            } else {
                printf("Email invalido! Formato: exemplo@dominio.pt\n");
            }
        }
    } while (!valido);
}

int validar_nome(const char *nome) {
    if (strlen(nome) == 0 || strlen(nome) >= MAX_STRING) return 0;
    for (int i = 0; nome[i] != '\0'; i++) {
        if (!tem_letra(nome[i]) && nome[i] != ' ') return 0;
    }
    return 1;
}

int ler_numero(char texto[], int min, int max) {
    char input[100];
    int valor, valido;
    
    do {
        valido = 1;
        printf("\n%s [%d-%d]--> ", texto, min, max);
        if (fgets(input, sizeof(input), stdin) != NULL) {
            input[strcspn(input, "\n")] = '\0';
            for (int i = 0; input[i] != '\0' && valido; i++) {
                if (!tem_numero(input[i])) valido = 0;
            }
            if (valido) {
                valor = atoi(input);
                if (valor < min || valor > max) valido = 0;
            }
        } else valido = 0;
        
        if (!valido) printf("\nEntrada invalida. Tente novamente.");
    } while (!valido);
    
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
        while (getchar() != '\n');
    } while (opcao < 1 || opcao > 3);
    
    switch(opcao) {
        case 1: strcpy(dificuldade, "Baixo"); break;
        case 2: strcpy(dificuldade, "Medio"); break;
        case 3: strcpy(dificuldade, "Alto"); break;
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
        while (getchar() != '\n');
    } while (opcao != 1 && opcao != 2);
    
    strcpy(tipo, (opcao == 1) ? "algoritmo" : "codigo");
}

int ler_estudante(Estudante estudantes[], int contador) {
    char input[MAX_STRING];
    int valido = 0;
    estudantes[contador].id = contador + 1;
    estudantes[contador].numero = ler_numero("Indique o numero do estudante entre", 2000000, 2999999);

    do {
        printf("\nIndique o nome do estudante: ");
        if (fgets(input, MAX_STRING, stdin) != NULL) {
            input[strcspn(input, "\n")] = '\0';
            if (validar_nome(input)) {
                strcpy(estudantes[contador].nome, input);
                valido = 1;
            } else printf("Nome invalido! Use apenas letras e espacos.\n");
        }
    } while (!valido);

    ler_email(estudantes[contador].email);
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

int ler_ficha(Ficha fichas[], int contador) {
    fichas[contador].id = contador + 1;
    char input[MAX_STRING];
    int valido = 0;
    
    do {
        printf("\nIndique o nome da ficha: ");
        if (fgets(input, MAX_STRING, stdin) != NULL) {
            input[strcspn(input, "\n")] = '\0';
            if (strlen(input) > 0 && strlen(input) < MAX_STRING) {
                strcpy(fichas[contador].nome, input);
                valido = 1;
            }
        }
    } while (!valido);

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

int ler_exercicio(Exercicio exercicios[], int contador, int id_ficha) {
    exercicios[contador].id = contador + 1;
    exercicios[contador].id_ficha = id_ficha;
    char input[MAX_STRING];
    int valido = 0;
    
    do {
        printf("\nIndique o nome do exercicio: ");
        if (fgets(input, MAX_STRING, stdin) != NULL) {
            input[strcspn(input, "\n")] = '\0';
            if (strlen(input) > 0 && strlen(input) < MAX_STRING) {
                strcpy(exercicios[contador].nome, input);
                valido = 1;
            }
        }
    } while (!valido);
    
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

int ler_submissao(Submissao submissoes[], int contador, 
                  Estudante estudantes[], int num_estudantes,
                  Ficha fichas[], int num_fichas,
                  Exercicio exercicios[], int num_exercicios) {
                      
    if (num_estudantes == 0 || num_fichas == 0 || num_exercicios == 0) {
        printf("\nNao existem dados suficientes para registrar submissao!");
        getchar(); getchar();
        return contador;
    }
    
    submissoes[contador].id = contador + 1;
    
    mostrar_estudantes(estudantes, num_estudantes);
    submissoes[contador].id_estudante = ler_numero("Indique o ID do estudante", 1, num_estudantes);
    
    mostrar_fichas(fichas, num_fichas);
    submissoes[contador].id_ficha = ler_numero("Indique o ID da ficha", 1, num_fichas);
    
    mostrar_exercicios(exercicios, num_exercicios);
    submissoes[contador].id_exercicio = ler_numero("Indique o ID do exercicio", 1, num_exercicios);
    
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

void calcular_estatisticas(Submissao submissoes[], int num_submissoes,
                          Estudante estudantes[], int num_estudantes,
                          Ficha fichas[], int num_fichas) {
    int id_estudante, total_submissoes = 0;
    float soma_classificacoes = 0, media_classificacoes, percentagem_exercicios;
    
    mostrar_estudantes(estudantes, num_estudantes);
    id_estudante = ler_numero("Indique o ID do estudante para estatisticas", 1, num_estudantes);
    
    for (int i = 0; i < num_submissoes; i++) {
        if (submissoes[i].id_estudante == id_estudante) {
            total_submissoes++;
            soma_classificacoes += submissoes[i].classificacao;
        }
    }
    
    media_classificacoes = total_submissoes > 0 ? soma_classificacoes / total_submissoes : 0;
    
    printf("\n\nEstatisticas do Estudante ID %d:", id_estudante);
    printf("\nTotal de submissoes: %d", total_submissoes);
    printf("\nMedia das classificacoes: %.2f", media_classificacoes);
    
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

void gravar_dados(Estudante estudantes[], int num_estudantes,
                 Ficha fichas[], int num_fichas,
                 Exercicio exercicios[], int num_exercicios,
                 Submissao submissoes[], int num_submissoes) {
                     
    FILE *ficheiro = fopen("dados.dat", "wb");
    
    if (ficheiro != NULL) {
        fwrite(&num_estudantes, sizeof(int), 1, ficheiro);
        fwrite(&num_fichas, sizeof(int), 1, ficheiro);
        fwrite(&num_exercicios, sizeof(int), 1, ficheiro);
        fwrite(&num_submissoes, sizeof(int), 1, ficheiro);
        
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
    
    fread(num_estudantes, sizeof(int), 1, ficheiro);
    fread(num_fichas, sizeof(int), 1, ficheiro);
    fread(num_exercicios, sizeof(int), 1, ficheiro);
    fread(num_submissoes, sizeof(int), 1, ficheiro);
    
    fread(estudantes, sizeof(Estudante), *num_estudantes, ficheiro);
    fread(fichas, sizeof(Ficha), *num_fichas, ficheiro);
    fread(exercicios, sizeof(Exercicio), *num_exercicios, ficheiro);
    fread(submissoes, sizeof(Submissao), *num_submissoes, ficheiro);
    
    fclose(ficheiro);
    printf("\nDados carregados com sucesso!");
    return 1;
}

int menu_principal() {
    int opcao;
    printf("\n\t##### MENU PRINCIPAL #####");
    printf("\n1 - Gestao de Estudantes");
    printf("\n2 - Gestao de Fichas");
    printf("\n3 - Gestao de Exercicios");
    printf("\n4 - Gestao de Submissoes");
    printf("\n5 - Estatisticas");
    printf("\n6 - Gravar Dados");
    printf("\n7 - Carregar Dados");
    printf("\n0 - Sair");
    printf("\nOpcao--> ");
    scanf("%d", &opcao);
    while (getchar() != '\n');
    return opcao;
}

int menu_estudantes() {
    int opcao;
    printf("\n\t##### MENU ESTUDANTES #####");
    printf("\n1 - Inserir novo estudante");
    printf("\n2 - Listar estudantes");
    printf("\n0 - Voltar");
    printf("\nOpcao--> ");
    scanf("%d", &opcao);
    while (getchar() != '\n');
    return opcao;
}

int menu_fichas() {
    int opcao;
    printf("\n\t##### MENU FICHAS #####");
    printf("\n1 - Inserir nova ficha");
    printf("\n2 - Listar fichas");
    printf("\n0 - Voltar");
    printf("\nOpcao--> ");
    scanf("%d", &opcao);
    while (getchar() != '\n');
    return opcao;
}

int menu_exercicios() {
    int opcao;
    printf("\n\t##### MENU EXERCICIOS #####");
    printf("\n1 - Inserir novo exercicio");
    printf("\n2 - Listar exercicios");
    printf("\n0 - Voltar");
    printf("\nOpcao--> ");
    scanf("%d", &opcao);
    while (getchar() != '\n');
    return opcao;
}

int menu_submissoes() {
    int opcao;
    printf("\n\t##### MENU SUBMISSOES #####");
    printf("\n1 - Registar nova submissao");
    printf("\n2 - Listar submissoes");
    printf("\n0 - Voltar");
    printf("\nOpcao--> ");
    scanf("%d", &opcao);
    while (getchar() != '\n');
    return opcao;
}

int main() {
    Estudante estudantes[MAX_ESTUDANTES];
    Ficha fichas[MAX_FICHAS];
    Exercicio exercicios[MAX_EXERCICIOS * MAX_FICHAS];
    Submissao submissoes[MAX_SUBMISSOES];
    
    int num_estudantes = 0;
    int num_fichas = 0;
    int num_exercicios = 0;
    int num_submissoes = 0;
    
    int opcao_principal, opcao_secundaria;
    
    do {
        system("cls");
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
                }
                getchar(); getchar();
                break;
        }
    } while (opcao_principal != 0);
    
    return 0;
}