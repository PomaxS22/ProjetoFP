#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXIMO_ESTUDANTES 100
#define MAXIMO_NOME 80

// ESTRUTURA PARA A DATA DE LANCAMENTO DAS NOTAS
typedef struct
{
    int dia, mes, ano;

} T_DATA;

// ESTRUTURA PARA OS ESTUDANTES
typedef struct
{
    int id, numero, nota_final;
    char nome[MAXIMO_NOME];
    char regime[MAXIMO_NOME];
    T_DATA DATA;

} T_ESTUDANTE;

int menu_opcoes();
int ler_numero(char[], int, int);
void ler_regime(char[]);
T_DATA ler_data();
int ler_dados_estudantes(T_ESTUDANTE[], int);
void mostrar_dados(T_ESTUDANTE[], int);
void gravar_dados(T_ESTUDANTE[], int);
int ler_dados(T_ESTUDANTE[]);

T_DATA ler_data()
{
    T_DATA data;
    int meses[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    data.ano = ler_numero("Indique o ano entre:", 2023, 2024);
    data.mes = ler_numero("Indique o mes entre:", 1, 12);
    data.dia = ler_numero("Indique o dia entre:", 1, meses[data.mes - 1]);

    return data;
}

void gravar_dados(T_ESTUDANTE estudantes[], int contador)
{
    FILE *ficheiro;

    ficheiro = fopen("estudantes.dat", "wb");

    if (ficheiro != NULL)
    {
        fwrite(&contador, sizeof(int), 1, ficheiro);
        fwrite(estudantes, sizeof(T_ESTUDANTE), contador, ficheiro);
        fclose(ficheiro);
        printf("\nDados gravados com sucesso!");
    }
    else
    {
        printf("\nNao foi possivel gravar ficheiro");
    }
}

int ler_dados(T_ESTUDANTE estudantes[])
{
    int contador, contador_read;
    FILE *ficheiro = fopen("estudantes.dat", "rb");

    if (ficheiro == NULL) {
        printf("\nNao foi possivel abrir o ficheiro!");
        return 0;
    }

    size_t count_read = fread(&contador, sizeof(int), 1, ficheiro);
    
    if (count_read != 1 || contador <= 0) {
        printf("\nNao ha dados para ler!");
        fclose(ficheiro);
        return 0;
    }

    contador_read = fread(estudantes, sizeof(T_ESTUDANTE), contador, ficheiro);
    fclose(ficheiro);

    if (contador != contador_read) {
        printf("\nFicheiro corrompido!");
        return 0;
    }

    printf("\nForam carregados %d estudantes com sucesso !", contador);
    return contador;
}

void ler_regime(char regime[])
{
    int opcao;
    printf("\nIndique o Regime do estudante");
    printf("\n1 - Diurno");
    printf("\n2 - Pos-Laboral");

    do
    {
        printf("\nOpcao-->\t");
        scanf("%d", &opcao);
        if (opcao != 1 && opcao != 2)
        {
            printf("\nOpcao incorreta");
        }

    } while (opcao != 1 && opcao != 2);

    if (opcao == 1) // Fixed comparison operator
    {
        strcpy(regime, "Diurno");
    }
    else
    {
        strcpy(regime, "Pos-Laboral");
    }
}

int ler_numero(char texto[], int min, int max)
{
    int valor;

    do
    {
        printf("\n%s [%d-%d]--> ", texto, min, max);
        scanf("%d", &valor);

        if (valor < min || valor > max)
            printf("\nValor incorreto");

    } while (valor < min || valor > max);

    return valor;
}

int ler_dados_estudantes(T_ESTUDANTE estudantes[], int contador)
{
    estudantes[contador].id = contador + 1;
    estudantes[contador].numero = ler_numero("\nIndique um numero do estudante entre", 0, 1000);
    estudantes[contador].nota_final = ler_numero("\nIndique a nota final do estudante entre", 0, 20);

    printf("\nIndique o nome do estudante: ");
    scanf(" %80[^\n]s", estudantes[contador].nome);

    ler_regime(estudantes[contador].regime);

    estudantes[contador].DATA = ler_data();

    return contador + 1;
}

void mostrar_dados(T_ESTUDANTE num_estudantes[], int contador)
{
    int indice = 0;
    printf("\n##### ESTUDANTES #####");

    for (indice = 0; indice < contador; indice++)
    {
        printf("\n---------------------------------");
        printf("\nID:%d", num_estudantes[indice].id);
        printf("\nNumero:%d", num_estudantes[indice].numero);
        printf("\nNome:%s", num_estudantes[indice].nome);
        printf("\nRegime:%s", num_estudantes[indice].regime);
        printf("\nData:%d/%d/%d", num_estudantes[indice].DATA.dia, num_estudantes[indice].DATA.mes, num_estudantes[indice].DATA.ano);
        printf("\nNota Final: %d", num_estudantes[indice].nota_final);
    }

    printf("\n---------------------------------");
    printf("\nTotal de Estudantes: %d", contador);

    getchar();
    getchar();
}

int menu_opcoes()
{
    int opcao;
    printf("\n\t##### MENU #####");
    printf("\n\n1 - Inserir dados de um estudante");
    printf("\n2 - Mostrar dados dos estudantes");
    printf("\n3 - Alterar nota final");
    printf("\n4 - Estatisticas das avalicoes");
    printf("\n5 - Gravar os dados (Ficheiro)");
    printf("\n6 - Ler os dados (Ficheiro)");
    printf("\n0 - SAIR");
    printf("\nOpcao--> ");
    scanf("%d", &opcao);

    return opcao;
}

int main()
{
    int opcao;
    int contador = 0;
    T_ESTUDANTE dados_estudantes[MAXIMO_ESTUDANTES];

    do
    {
        system("cls");
        opcao = menu_opcoes();

        switch (opcao)
        {
        case 1:
            if (contador < MAXIMO_ESTUDANTES)
            {
                contador = ler_dados_estudantes(dados_estudantes, contador);
            }
            else
            {
                printf("\nLimite maximo de estudantes atingido!");
                getchar();
                getchar();
            }
            break;
        case 2:
            mostrar_dados(dados_estudantes, contador);
            break;
        case 3:
            // Alterar nota final (to be implemented)
            printf("\nFuncionalidade ainda nao implementada!");
            getchar();
            getchar();
            break;
        case 4:
            // Estatisticas das avaliacoes (to be implemented)
            printf("\nFuncionalidade ainda nao implementada!");
            getchar();
            getchar();
            break;
        case 5:
            gravar_dados(dados_estudantes, contador);
            getchar();
            getchar();
            break;
        case 6:
            contador = ler_dados(dados_estudantes);
            getchar();
            getchar();
            break;

        case 0:
            printf("\nA sair do programa...");
            getchar();
            getchar();
            break;

        default:
            printf("\nOpcao invalida!");
            getchar();
            getchar();
            break;
        }
    } while (opcao != 0);

    return 0;
}