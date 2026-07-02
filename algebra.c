#include "algebra.h" //importa as structs da sua propria biblioteca

//devolve a struct sistema toda preenchida 
struct Sistema lerSistema(){ //essa struct  le quantas equações, variaveis mais o resultado de cada equação
    struct Sistema s; //variavel do tipo sistema que vai ser preenchida e depois retornada 

        printf("Quantas equações?");
        scanf("%d", &s.linhas); //salva na propriedade linhas do sistema s
        printf("Quantas variaveis?");
        scanf("%d", &s.colunas); //mesma coisa so que para coluna

        printf("Escreva os elementos\n");

        for(int i = 0; i < s.linhas; i++){ //percorre cada linha (equação) da matriz
            for(int j = 0; j < s.colunas; j++){// percore cada coluna, coef de cada variav da equação atual
                scanf("%lf", &s.matriz[i][j]); //le o coef e guarda na posição que esta
            }
            printf("Resultado da equação %d:", i + 1); //pede o termo independente da equação
            scanf("%lf", &s.matriz[i][s.colunas]);//resultado da equacao, fica na ultima coluna da linha [s.colunas]
        }

        return s; //retorna a estrutura preenchida commos dados do sistema
}
struct Sistema resolverSistema(struct Sistema s){ //função de eliminaçãao de gauss para escalonar sistema
    int col; //variavel usada para iterar sobre as colunas
    int i; //variavel usada para iterar sobre as linhas
    int pivo;//é a linha que tem o pivo da coluna atual
    double aux;//usada na troca de linha
    int j; //variavel que percorre colunas durate operações em linhas
    double fator; //multiplicador usado pra zerar os elementos abaixo do pivo 
    

    s.qtdPivos = 0;//cont de pivos inicializada

    for( col = 0; col < s.colunas; col++ ){//percorre cada col(variavel) para encontrar pivos

        pivo = -1;//nada de pivo ainda para a coluna

        for( i = col; i < s.linhas; i++){ //procura da linha atual para baixo um elemento com valor diferente de 0 na col
            if(pivo == -1){//so verifica se ainda nao achou um pivo nessa coluna
                if(s.matriz[i][col] != 0){ //verifica se elemento atual é != 0 
                    pivo = i; //se for, guarda primeira linha encontrada como linha do pivo
                }
            }
        }

        if(pivo != -1){ //verifica se na coluna realmente tem um pivo
            s.qtdPivos = s.qtdPivos + 1; //conta mais um pivo encontrado da struct s 
            if(pivo != col){ //se pivo não esta na linha da col atual, troca as duas linhas
                for(j = 0; j < s.colunas + 1; j++) { //percorre todos elementos da linha (+1 = coluna resultado)
                    aux = s.matriz[col][j];//salva valor da linha da col no aux
                    s.matriz[col][j] = s.matriz[pivo][j]; //substitui valor da linha col pelo do pivo
                    s.matriz[pivo][j] = aux; //cooca valor salvo em aux na limha do pivo
                }
            }

            for(i = col + 1; i < s.linhas; i++){ //percorre todas as linhas abaixo da linha do pivo atual
                if(s.matriz[i][col] != 0){ //so vale a pena zerar se ja nao for zero
                    fator = s.matriz[i][col] / s.matriz[col][col]; //fator = elemento a zerar dividido pelo pivo
                    for (j = 0; j < s.colunas + 1; j++){//aplicar operção em todos os elementos
                        s.matriz[i][j] = s.matriz[i][j] - fator * s.matriz[col][j]; //linha i = linha i - fator * linha pivo (col por col)
                    }
                }
            }
        }
    }
        
    return s; //devolve ja escalonada e a qtd de pivos 

}
enum Classificacao classificarSistema(struct Sistema s){ //função que classifica o sistema e resolve se for possivel e determinado
    int i;
    int j;
    int verificarZero; //para saber se todos coef da linha  é 0
    int impossivel; //para saber se o sistema é impossivel, se sim 1 e se não 0
    int determinado; //saber se é determinado
    double verificarVariavel[10]; //vetor que guarda o valor de cada variavel calculada
    double soma; //acumula a soma das variaveis ja resolvidas ao fazer a substituição reversa
    enum Classificacao resultado; //gaurda a classificação para retornar

    impossivel = 0; //assume que o sistema é possivel inicialmente

    for(i=0; i<s.linhas; i++){ //percorre todas linhas da matriz
        verificarZero = 1; //paraa cada linha assume que todos coef são 0 
        for(j=0;j<s.colunas;j++){ //percorredo as colunas das variaveis
            if(s.matriz[i][j] != 0){ //se achou algum coeficiente diferente de zero
                verificarZero = 0; //se encontrou muda para 0, indicando que a linha não é toda nula
            }
        }

        if(verificarZero == 1){ //se os coeficientes sao tudo zero
            if(s.matriz[i][s.colunas] != 0){ //verifica se o resultado não é 0 
                impossivel = 1;//se for diferente de zero mas os coef tudo for 0 então é impossivel
            }
        }
    }

    if(impossivel == 1){ //se o sistema é impossivel
        printf("Sistema impossivel\n");
        resultado = IMPOSSIVEL; //se for impossivel imprime na tela e guarda em resulatdo
    }
    if(impossivel == 0){ //se não for impossivel começa assumindo determinado como indeterminado (=0)
        determinado = 0; 
        if(s.qtdPivos == s.colunas){ //se numero de pivo bate com num de variaveis, cada variavel tem dono (unica solucao)
            determinado = 1;//entao determinado recebe 1
        }
        if(determinado == 0){ //se nao bate e tb não for impossivel é indeterminado 
            printf("Sistema possivel e indeterminado\n");
            resultado = INDETERMINADO; //classificando como indeterminado
        }
        if(determinado == 1){ //se bateu a qtd de pivo com o numero de variaveis
            for(i = s.colunas - 1; i>= 0; i--){ //calculamos as variaveis de baixo pra cima, pq a ultima linha escalonada não tem muitas variaveis mistruradas
                soma = 0;//inicializa como 0 que vai acumular valores das variaveis que ja descobrimos
                for(j = i + 1; j<s.colunas; j++){ //percorre os termos das variaveis a direira da diag. principal
                    soma = soma + s.matriz[i][j] * verificarVariavel[j];//multiplica o coef pelo valor da variavel descoberta e soma
                }
                verificarVariavel[i] = (s.matriz[i][s.colunas] - soma) / s.matriz[i][i];//isola a variavel atual: (resultado - soma ja descoberta) / coeficiente dela
            }

            printf("Sistema possivel e determinado\n");
            for(i = 0; i<s.colunas; i++){ //percorre todos valores das variaveis encontradas
                printf("Solução: x%d = %f\n", i + 1, verificarVariavel[i]); //imprime a variavel como por ex x1 = valor
            }
            resultado= DETERMINADO;//classificando a função como determinado
        }
    }
    return resultado; //retorna o valor final do enum
}

int adiconarHistorico(struct Registro historico[], int contHistorico, struct Sistema s, enum Classificacao c) { //função que insere um sistema resolvido no array de historico
    if(contHistorico < 50){ //verifica se ainda tem espaço no vetor
        historico[contHistorico].sistema = s; //copia a struct sistema s para a posição atual do historico
        historico[contHistorico].resultado = c; //copia a classificacao c do sistema para o historico
        contHistorico = contHistorico + 1; //incrementa a qtd de salvos ja
    }

    if(contHistorico >= 50){ //verifica se historico ta cheio
        printf("Histórico cheio. Registro não foi salvo\n"); //se esta cheio não vai ser salvo
    }
    return contHistorico; //retorna cont atualizado 
}

void listarHistorico(struct Registro historico[], int contHistorico){ //função para mostrar os sistemas ja guardados
    if(contHistorico == 0){ //verifica se não foi guardado nada ainda
        printf("Nenhum sistema foi resolvido ainda\n"); //se não foi, imprime
        return;//encerra a função aqui mesmo
    }   
    while (getchar() != '\n');// limpando buffer 
    for(int i = 0; i<contHistorico; i++){ //percorre todos registros salvos 
        printf("Registro %d: sistema %d X %d - ", i + 1, historico[i].sistema.linhas, historico[i].sistema.colunas); //imprime o a ordem e o tamanho(LxC) do sistema
        if(historico[i].resultado == IMPOSSIVEL){ //verifica se é imp
            printf("Impossivel\n"); //se for imprime
        }
        if(historico[i].resultado == INDETERMINADO){ //mesma coisa
            printf("Indeterminado\n");//...
        }
        if(historico[i].resultado == DETERMINADO){//...
            printf("Determinado\n");//...
        }
        if((i + 1) % 10 == 0 && (i + 1) != contHistorico){//se for multipla de 10 e não for o ultimo registro vamos para a proxima pagina
            printf("Motrando %d de %d, pressione enter para proxima pagina\n", i + 1, contHistorico );
            getchar();//pausa e espera usuario apertar enter
        }
    }

    printf("Fim da lista, pressione enter para voltar ao menu");//para voltar ao menu
    getchar();
}

void salvarHistorico(struct Registro historico[], int contHistorico){ //agora vamos pegar o historico e gravar em um arquivo txt
    FILE *arquivo; //declara ponteiro de arquivo chamado arquivo
    arquivo = fopen("historico.txt", "w"); //abre ou cria o arquivo no modo escrita

    if(arquivo == NULL){ //se o ponteiro for null houve algum erro ao tentar abrir o arquivo
        printf("Erro ao abrir arquivo\n"); 
    }
    if(arquivo != NULL){ //se não for, ele abriu
        fprintf(arquivo, "%d\n", contHistorico); //grava qtd de registros na primeira linha do arquivo
        for(int i = 0; i<contHistorico; i++){ //percorre todos registros guardados no historico
            fprintf(arquivo, "%d %d\n", historico[i].sistema.linhas, historico[i].sistema.colunas);//grava qtd de linhas e colunas do sistema atual
            for(int j=0; j<historico[i].sistema.linhas; j++){ //percorre as linhas da matriz do sistema
                for(int k = 0; k<historico[i].sistema.colunas + 1; k++){ //percorre as colunas da matriz do sistema + resultado
                    fprintf(arquivo, "%f ", historico[i].sistema.matriz[j][k]); //grava cada coef no arquivo
                }
                fprintf(arquivo, "\n"); //quebra de linha depois de passar por cada linha
            }

            fprintf(arquivo, "%d\n", historico[i].resultado); //grava classificacao 
        }

        fclose(arquivo);//fecha arquivo
        printf("Histórico salvo!\n");
    }
}

int carregarHistorico(struct Registro historico[]){ //função que le arquivo txt para carregar os registros para o vetor
    FILE * arquivo; //declara ponteiro do arquivo
    int contHistorico; //qtd de registros do arquivo
    int valor; //oque vai ler a classificacao

    arquivo = fopen("historico.txt", "r"); //abre arquivo no modo leitura

    contHistorico = 0; //inicializa cont como 0

    if(arquivo == NULL){ //verifica se não exite ou não abre
        printf("Nenhum histórico salvo\n");
    }
    if(arquivo!= NULL){//verifica se foi aberto
        fscanf(arquivo, "%d", &contHistorico);//le o primeiro num do arquivo

        for(int i = 0; i<contHistorico; i++){ //percorre cada registro salvo
            fscanf(arquivo, "%d %d", &historico[i].sistema.linhas, &historico[i].sistema.colunas);//leitura de cada registro, le e guarda dimensoes do sistema

            for(int j=0; j< historico[i].sistema.linhas; j++){//percorre e carrega as linhas da matriz do sistema no arquivo
                for(int k=0; k<historico[i].sistema.colunas + 1; k++){//percorre as colunas + resultado
                    fscanf(arquivo, "%lf", &historico[i].sistema.matriz[j][k]); //le e armazena na posição da matriz do historico
                }
            }    

            fscanf(arquivo, "%d", &valor); //le a classificacao e salva em valor
            historico[i].resultado = valor;//atribui a class lida a struct de registro 
        }

        fclose(arquivo);//fecha ponteiro de arquivo
        printf("Histórico carregado!\n");

    }

    return contHistorico;//retorna a qtd de registros 

}

void verificarBase(){ //função para ver se um conj de vetores formam base R2 ou R3
    int dimensao; //guarda se é R2 ou R3
    int qtdVetores;
    struct Sistema s; //declara struct sistema para usarmos o escalonamento ja feito

    printf("Qual dimensão? Escreva 2 para R2, e 3 para R3:\n");
    scanf("%d", &dimensao);
    printf("Quantos vetores quer testar?\n");
    scanf("%d", &qtdVetores);

    if(qtdVetores == dimensao){ //para ser base o numero de vetores deve ser igual a dimensão
        s.linhas = qtdVetores;//as linhas serão vetores
        s.colunas = dimensao;//colunas serão as coordenadas 

        printf("Digite os vetores:\n");
        for(int i = 0; i<s.linhas; i++){//percorre cada vetor
            printf("Vetor %d:", i+1);
            for(int j = 0; j<s.colunas; j++){//percorre cada coordenada
                scanf("%lf", &s.matriz[i][j]);//le e guarda a coordenada na matriz do sistema
            }
            s.matriz[i][s.colunas]=0; //iguala resultado a 0 para verificar se são dependentes ou independentes
        }

        s = resolverSistema(s); //usando função de escalonamento para verificar dependencia

        if(s.qtdPivos == s.colunas){ //verifica se num de pivos é igual num de coluna
            printf("É base do espaço R%d\n", dimensao);//se sim, são linearmente independentes, então é base
        }
        if(s.qtdPivos != s.colunas){ //se são diferentes significa que tem vetores dependentes
            printf("Não é base do espaço R%d\n", dimensao);//logo, não forma base
        }
    }
    if(qtdVetores != dimensao){//se a qtd de vetores não bate com dimensão nunca pode ser base
        printf("Não é base do espaço R%d: quantidade de vetores %d diferente da dimensão %d\n", dimensao, qtdVetores, dimensao);
    }
}

void verificarTransformacao(){ //função que verifica as propriedades se são injetora.... 
    int linhas; //guardara a imagem (espaço chegada)
    int colunas; //guardara o dominio (espaço partida)
    struct Sistema s; //struct para usar escalonamento na matriz
    int nucleo; //dimensão do nucleo da transf
    int imagem;//dimen da imagem da transf
    int injetora;//se for injetora
    int sobrejetora;//se for sobrejetora

    printf("A dimensão do espaço de saída é o tanto de numero de linhas e a dimensão do espaço de entrada é o mesmo tanto de colunas(variaveis)!\n");
    printf("Escreva o tanto de linhas e o tanto de colunas respectivamente:");
    scanf("%d", &linhas); //le imagem 
    scanf("%d", &colunas); //le dominio

    s.linhas = linhas; //define qtd de linhas na struct
    s.colunas = colunas; //define qtd de colunas na struct
    
    printf("Digite a matriz da transformação:\n");
    for(int i = 0; i < s.linhas; i++){//percorre as linhas
        for(int j = 0; j < s.colunas; j++){//percorre as colunas
            scanf("%lf", &s.matriz[i][j]);//le e guarda os coef
        }
        s.matriz[i][s.colunas] = 0;//iguala o resultado a 0 para poder calcular o nucleo
    }
    s = resolverSistema(s);//escalonamento da matriz para encontrar qtd de pivo (que sera nossa dimensão da imagem)

    imagem = s.qtdPivos;//imagem igual ao posto da matriz
    nucleo = s.colunas - s.qtdPivos;//dim(nucleo) + dim(imagem) = dim(dominio) entao nucleo = colunas - imagem

    printf("Dimensão do nucleo: %d\n", nucleo); 
    printf("Dimensão da imagem: %d\n", imagem);

    injetora = 0; //inicialmente assume que não é injetora
    if(nucleo == 0){//só é injetora se nucleo tiver apenas dimensão 0
        injetora = 1;//se é, então é injetora
    }
    sobrejetora = 0;//inicialmente assume que não é sobrejetora
    if(imagem == s.linhas ){//só é sobrejetora se a dim da imagem for igual a dim do contra dominio(linhas)       
        sobrejetora = 1;//se é, então é sobrejetora
    }
    if(injetora == 1){
        if(sobrejetora == 1){ //se ela é injetora e sobrejetora, então ela é bijetora
            printf("A transormação é bijetora\n");
        }
    }
    if(injetora == 1){
        printf("A transformação é injetora\n");
    }
    if(sobrejetora == 1){
        printf("A transformação é sobrejetora\n");
    }
}

void calcularAutoVetor(double a, double b, double c, double d, double autovalor){ //função que calcula autovetor para 2x2 associado a um autovalor
    double A; //diagonal a
    double D; //diagonal d
    double x, y; //coordenadas do autovetor 

    A = a - autovalor;//subtrai o autovalor do primeiro elemento da diag principal 
    D = d - autovalor;//subtrai autovalor do ultimo elemento da diag principal 

    if(A != 0){ //verifica se a primeira equação não zerou coef do x
        y = 1; //inicializa y para um valor não nulo
        x = (-b * y) / A;//isola x com a equação: A*x + b*y = 0, A*x = -b*y, x = -b*y / A
    }
    if(A == 0){//se zerou, significa que o coef de A é 0 
        if(b != 0){//verifica se o coef de y não é 0 
            y = 0;//se não é, entao para a equação ser verdadeira, y tem que ser 0
            x = 1;//como y é 0, x fica livre 
        }
        if(b == 0){//se os dois são 0, a primeira linha anulou 
            if(c != 0) {//então usamos a segunda equação, se coef de x não zerou
                y = 1;//inicialmente y = 1
                x = (-D * y) / c; //isolamos x na segunda equação igual com a primeira
            }
            if(c == 0){//se c tb zerou entao (a= 0, b = 0 e c= 0)
                x = 1;//a matriz já é multiplo de identidade, x e y ficam livres
                y = 0;
            }
        }
    }

    printf("Autovetor: (%f, %f)\n", x, y);

}

void autoValoresAutoVetores(){//função calculo polinomio para matriz 2X2
    double a, b, c, d; //posições da matriz 2x2
    double somaDiagPrinc;//guarda a soma a+d (traço da matriz)
    double determinante;//guarda (a*d - b*c) (determinante)
    double delta;//usado para equação de segundo grau
    double raizDelta;//guarda a raiz quadrada do delta
    double autoValor1;//primeira raiz
    double autoValor2;//segunda raiz

    printf("Digite a matriz 2X2:\n");
    scanf("%lf %lf %lf %lf", &a, &b, &c, &d); 

    somaDiagPrinc = a + d; //calculo do traço da matriz
    determinante = (a * d) - (b * c); //calcula determinante 

    printf("Traço = %f\n", somaDiagPrinc);
    printf("Determinante = %f\n", determinante);

    delta = (somaDiagPrinc * somaDiagPrinc) - (4 * determinante);//formula de bhaskara para delta (b² - 4ac)
    printf("Delta = %f\n", delta);

    if(delta>0){//se delta for positivo temos duas raizes
        raizDelta = sqrt(delta);//calculo da raiz do delta
        autoValor1 = (somaDiagPrinc + raizDelta) / 2;//formula de bhaskara para ver a raiz 1: (-(-traço)+raizdelta)/2a
        autoValor2 = (somaDiagPrinc - raizDelta) / 2;//formula da raiz 2: (-(-traço) - raizdelta) /2a
        printf("Lamb1 = %f\n", autoValor1);
        calcularAutoVetor(a, b, c, d, autoValor1);//chama a função passando o autovalor para encontrar o autovetor
        printf("Lamb2 = %f\n", autoValor2);
        calcularAutoVetor(a, b, c, d, autoValor2);//chama a função passando o autovalor pra encontrar seu atovetor
    }
    if(delta == 0){//se delta é 0 temos duas raizes iguais
        autoValor1 = somaDiagPrinc / 2;//calcula a unica raiz
        printf("Lamb = %f\n", autoValor1);
        calcularAutoVetor(a, b, c, d, autoValor1);//chama a função para achar seu autovetor 
    }
    if(delta<0){//se delta for negativo não existe autovalores reais 
        printf("Nao existem autovalores reais na matriz\n");
    }
}

void diagonalizarMatriz(){ //função que verifica se pode ser diagonalizada 
    double a, b, c, d;//componentes da matriz
    double somaDiagPrinc, determinante, delta, raizDelta;
    double autovalor1, autovalor2;
    int diagonalizavel;//variavel que determina a diagonalização quando tem autovalores repetidos

    printf("Digite a matriz 2x2:\n");
    scanf("%lf %lf %lf %lf", &a, &b, &c, &d);

    somaDiagPrinc = a + d;
    determinante = (a * d) - (b * c);
    delta = (somaDiagPrinc * somaDiagPrinc) - (4 * determinante);

    if(delta > 0){
        raizDelta = sqrt(delta);
        autovalor1 = (somaDiagPrinc + raizDelta) / 2;
        autovalor2 = (somaDiagPrinc - raizDelta) / 2;

        printf("Matriz é diagonalizavel\n");//se uma matriz tem autovalores distintos reais, ela sempre é diagonalizavel
        printf("Matriz diagonal:\n");
        printf("%f 0\n", autovalor1);//primeira linha da matriz autovalor 1 e 0 
        printf("0 %f\n", autovalor2);//segunda linha 0 e autovalor 2
    }

    if(delta == 0){//se tiver apenas um autovalor 
        autovalor1 = somaDiagPrinc / 2;//pega o autovalor 
        diagonalizavel = 0;//se tem raiz repetida assumimos 0 inicialmente

        if(a == autovalor1){ //uma matriz so com um autovalor só é diagonalizavel se ela ja for multiplo da matriz identidade
            if(d == autovalor1){//verifica se a é autovalor e d tambem 
                if(b == 0){//verifica se fora da diag principal é 0 
                    if(c == 0){
                        diagonalizavel = 1;//se for tudo isso, ela é diagonalizavel
                    }
                }
            }
        }

        if(diagonalizavel == 1){//verifica se é 
            printf("Matriz é diaginalizavel\n");
            printf("Matriz diagonal:\n");
            printf("%f 0\n", autovalor1);
            printf("0 %f\n", autovalor1);
        }
        if( diagonalizavel == 0){//se delta 0 mas não é multiplo de id então:
            printf("Matriz não é diagonalizavel, faltam autovetores independentes\n"); //não existe 2 autovetores
        }
    }
    
    if(delta < 0){ //se delta é negativo entao:
        printf("Matriz não é diagonalizavel, não tem autovalores reais\n");
    }
}

struct Sistema lerSistemaArquivo(int *lido){//função para ler o sistema de um arquivo txt
    struct Sistema s;//variavel s para guardar o sistema
    FILE *arquivo;//ponteiro para arquivo

    arquivo = fopen("sistema.txt", "r");//abrindo arquivo no modo leitura
    if(arquivo == NULL){//se ponteiro for nulo então rquivo não existe
        printf("Arquivo não encontrado");
        *lido = 0;//a leitura deu errado então recebe 0
    }else {
        fscanf(arquivo, "%d", &s.linhas);//qtd de equações
        fscanf(arquivo, "%d", &s.colunas);//qtd de variaveis
        for(int i = 0;i<s.linhas; i++){ //percorrendo linhas
            for(int j = 0; j<s.colunas; j++){//percorrendo colunas
                fscanf(arquivo, "%lf", &s.matriz[i][j]);//le o coeficiente 
            }
            fscanf(arquivo, "%lf", &s.matriz[i][s.colunas]);//le o resultado de  cada linha
        }

        fclose(arquivo);//fecha arquivo
        *lido = 1;//avisa que foi lido
        printf("Sistema do arquivo pronto\n");
    }

    return s;//retorna a struct

}

