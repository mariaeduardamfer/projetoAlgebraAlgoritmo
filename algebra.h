#ifndef ALGEBRA_H
#define ALGEBRA_H
#include <stdio.h>
#include <math.h> // inclui biblioteca de mat pra uso de raiz quadrada (autovalores)

struct Sistema{ //declara a estrutura que vai representar o sistema linear
    double matriz[10][11]; // matriz armazena coef 10 linhas e 10 colunas sendo um coluna para resultado (Termo ind)
    int linhas; //guarda qutd de equações
    int colunas; // qtd variaveis do sistema 
    int qtdPivos; //qtd de pivo encontrado durante escalonamento
};

enum Classificacao{ //representa o tipo de resulatdo no sistema
    IMPOSSIVEL,
    INDETERMINADO,
    DETERMINADO
};

struct Registro{ //cada vez que um sistema é resolvido, um registro é guardado no historico
    struct Sistema sistema; //variavel do tipo sistema que armazena tudo do SL
    enum Classificacao resultado; //variavel do tipo class.que armazena o tipo
};

//devolve a struct sistema toda preenchida 
struct Sistema lerSistema(); //essa struct  le quantas equações, variaveis mais o resultado de cada equação
struct Sistema resolverSistema(struct Sistema s);//função de eliminaçãao de gauss para escalonar sistema
enum Classificacao classificarSistema(struct Sistema s); //função que classifica o sistema e resolve se for possivel e determinado
int adiconarHistorico(struct Registro historico[], int contHistorico, struct Sistema s, enum Classificacao c);//função que insere um sistema resolvido no array de historico
void listarHistorico(struct Registro historico[], int contHistorico); //função para mostrar os sistemas ja guardados
void salvarHistorico(struct Registro historico[], int contHistorico);//agora vamos pegar o historico e gravar em um arquivo txt
int carregarHistorico(struct Registro historico[]);//função que le arquivo txt para carregar os registros para o vetor
void verificarBase();//função para ver se um conj de vetores formam base R2 ou R3
void verificarTransformacao();//função que verifica as propriedades se são injetora.... 
void calcularAutoVetor(double a, double b, double c, double d, double autovalor);//função que calcula autovetor para 2x2 associado a um autovalor
void autoValoresAutoVetores();//função calculo polinomio para matriz 2X2
void diagonalizarMatriz(); //função que verifica se pode ser diagonalizada 
struct Sistema lerSistemaArquivo(int *lido);//função que le o sistema de um arquivo txt

    
#endif