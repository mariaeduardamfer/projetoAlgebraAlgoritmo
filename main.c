#include <stdio.h>
#include "algebra.h"//importa sua biblioteca local

int main(){//função principal

    int opcao;//variavel que o usuario vai escolher
    int menu = 1;//inicializa o menu com 1 para rodar
    struct Registro historico[50];//declara vetor do tipo registro com 50 espaços
    int contHistorico = 0;//inicializa cont com 0 

    while (menu == 1){//vai continuar o loop se a variavel permanecer em 1
        printf("==== MENU ====\n");
        printf("1 - Resolver sistema linear\n");
        printf("2 - Verificar base\n");
        printf("3 - Verificar injetividade ou sobrejetividade ou bijetividade\n");
        printf("4 - Autovalores e autovetores\n");
        printf("5 - Diagonalizar matriz\n");
        printf("6 - Listar sistemas ja feitos\n");
        printf("7 - salvar historico no arquivo\n");
        printf("8 - Carregar o historico do arquivo\n");
        printf("9 - Ler e resolver sistema de arquivo\n");
        printf("0 - sair\n");
        printf("Escolha a opcao desejada:");
        scanf("%d", &opcao);

        if(opcao == 1){

            struct Sistema s; //cria um sistema para uso na execução dessa opção
            enum Classificacao resultado;//cria a variavel para ver a classificação
            s = lerSistema(); //chama a função para o usuario informas as equações e guarda na struct
            s = resolverSistema(s); //aplica o escalonamento na struct através da chamada de função
            resultado = classificarSistema(s);//chama função para verificar se tem solução e imprime, salvando no enum resultado
            contHistorico = adiconarHistorico(historico, contHistorico, s, resultado);//manda o sistema e o enum final  para vetor do historico, atualizando o cont

        }else if(opcao == 2){
            verificarBase();//chamda de função para checar a base
        }else if(opcao == 3){
            verificarTransformacao();//chama a função para testar nucleo, imagem, etc
        }else if(opcao == 4){
            autoValoresAutoVetores();//chama a função para calculos de polinomio
        }else if(opcao == 5){
            diagonalizarMatriz();//chama a função para ver se matriz pode virar D
        }else if(opcao == 6){
            listarHistorico(historico, contHistorico);//exibe os sitemas resolvidos
        }else if(opcao == 7){
            salvarHistorico(historico, contHistorico);//grava os sistemas em arquivo de texto
        }else if(opcao == 8){
            contHistorico = carregarHistorico(historico);//reatualiza o cont geral
        }else if(opcao == 9){
            struct Sistema s;//cria um sistema vazio
            enum Classificacao resultado;//variavel para a classificacao
            int lido = 0;//variavel para saber se o arquivo existe
            s = lerSistemaArquivo(&lido);//chama função para ler arquivo, se der lido vira 1
            if(lido == 1){ //verifica se foi lido, se sim entao:
                s = resolverSistema(s);//chama função de escalonar 
                resultado= classificarSistema(s);//chama função de classificar 
                contHistorico = adiconarHistorico(historico, contHistorico, s, resultado); //manda pro historico
            }
        }else if(opcao == 0){
            menu = 0;//se usuario escolheu sair o menu vai para 0 para parar o loop
        }else{
            printf("Opcao nao existe!\n");//caso o usuario digitar uma opcao que não existe
        }
    }

    return 0;
}