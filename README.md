# 📐 Projeto Final — Álgebra Linear + ATP2

> Programa em linguagem C para resolução de problemas de Álgebra Linear

---

## 📋 Sobre o Projeto

Este programa implementa uma biblioteca de funções para resolução de cinco categorias de problemas de Álgebra Linear, com interface de menu interativo no terminal. Além dos requisitos matemáticos, o projeto aplica integralmente os conceitos de ATP2: modularização, estruturas de dados (`struct`, `enum`, arrays de structs), manipulação de arquivos e registros.

---

## ✨ Funcionalidades

| # | Módulo | Descrição |
|---|--------|-----------|
| 1 | **Sistemas Lineares** | Resolve sistemas m×n usando Eliminação de Gauss. Detecta sistemas impossíveis, indeterminados e determinados |
| 2 | **Determinação de Bases** | Verifica se um conjunto de vetores forma base de R² ou R³ |
| 3 | **Injetividade / Sobrejetividade / Bijetividade** | Analisa transformações lineares e calcula dimensão do núcleo e da imagem |
| 4 | **Autovalores e Autovetores** | Calcula autovalores e autovetores de operadores em R² |
| 5 | **Diagonalização de Matrizes** | Verifica se uma matriz é diagonalizável em R² e exibe a matriz diagonal |
| 6 | **Histórico** | Lista, salva e carrega todos os sistemas resolvidos na sessão |

---

## 🗂️ Estrutura dos Arquivos

```
projetoAlgebraAlgoritmo/
│
├── main.c          # Programa principal: menu e chamadas das funções
├── algebra.c       # Implementação dos módulos de Álgebra Linear
├── algebra.h       # Cabeçalho: declarações de structs, enums e protótipos
├── sistema.txt     # Arquivo de exemplo de sistema linear 
├── historico.txt   # Gerado automaticamente ao salvar o histórico
└── README.md       # Este arquivo
```

---

## 🔧 Requisitos

- Sistema operacional **Linux** (testado no Ubuntu 24)
- Compilador **GCC** instalado
- Biblioteca matemática padrão `libm` 

Para verificar se o GCC está instalado:
```bash
gcc --version
```

Se não estiver instalado:
```bash
sudo apt update
sudo apt install gcc
```

---

## ⚙️ Como Compilar

Abra o terminal na pasta do projeto e execute:

```bash
gcc main.c algebra.c -o programa -lm
```

Explicação de cada parte do comando:
- `main.c algebra.c` → arquivos fonte que serão compilados juntos
- `-o programa` → nome do executável gerado (`programa`)
- `-lm` → linka a biblioteca matemática (necessária para a função `sqrt()` usada nos autovalores)

---

## ▶️ Como Executar

Após compilar, execute com:

```bash
./programa
```

O menu principal será exibido automaticamente:

```
==== MENU ====
1 - Resolver sistema linear
2 - Verificar base
3 - Verificar injetividade ou sobrejetividade ou bijetividade
4 - Autovalores e autovetores
5 - Diagonalizar matriz
6 - Listar sistemas ja feitos
7 - salvar historico no arquivo
8 - Carregar o historico do arquivo
9 - Ler e resolver sistema de arquivo
0 - sair
Escolha a opção desejada:
```

---

## 📖 Como Usar Cada Módulo

### 1️⃣ Resolver Sistema Linear

Digite o número de equações (m) e variáveis (n), depois insira os coeficientes linha por linha e o resultado de cada equação.

**Exemplo** — sistema 2×2:
```
Quantas equações? 2
Quantas variaveis? 2
Escreva os elementos
1 1
Resultado da equação 1: 5
2 -1
Resultado da equação 2: 1

Sistema possivel e determinado
Solução: x1 = 2.000000
Solução: x2 = 3.000000
```

### 2️⃣ Verificar Base

Informe a dimensão do espaço (2 para R², 3 para R³) e a quantidade de vetores. Se a quantidade for diferente da dimensão, o programa já informa que não pode ser base. Caso contrário, insira os vetores um por vez.

**Exemplo** — dois vetores em R²:
```
Qual dimensão? 2
Quantos vetores? 2
Vetor 1: 2 1
Vetor 2: 1 3
É base do espaço R2
```

### 3️⃣ Injetividade / Sobrejetividade / Bijetividade

Informe o número de linhas (dimensão do espaço de saída) e colunas (dimensão do espaço de entrada) da matriz da transformação, depois insira a matriz linha por linha.

O programa calcula e exibe:
- Dimensão do núcleo
- Dimensão da imagem
- Se é injetora, sobrejetora e/ou bijetora

### 4️⃣ Autovalores e Autovetores

Insira os 4 elementos da matriz 2×2 em uma linha só (a b c d).

**Exemplo:**
```
Digite a matriz 2X2:
3 -2.5 0 0.5

Traço = 3.500000
Determinante = 1.500000
Delta = 6.250000
Lamb1 = 3.000000
Autovetor: (1.000000, 0.000000)
Lamb2 = 0.500000
Autovetor: (1.000000, 1.000000)
```

Se não existirem autovalores reais, o programa informa claramente.

### 5️⃣ Diagonalizar Matriz

Insira os 4 elementos da matriz 2×2. O programa verifica se é diagonalizável e, se for, exibe a matriz diagonal D.

### 6️⃣ Histórico

- **Opção 6** → lista todos os sistemas resolvidos na sessão atual
- **Opção 7** → salva o histórico no arquivo `historico.txt`
- **Opção 8** → carrega o histórico de uma sessão anterior do arquivo

O histórico persiste entre execuções do programa graças à manipulação de arquivo — ao carregar, todos os registros da sessão anterior ficam disponíveis novamente.

### 9️⃣ Ler e Resolver Sistema de Arquivo

Em vez de digitar os coeficientes um a um no terminal, o programa pode ler um sistema diretamente do arquivo sistema.txt.

O arquivo deve conter o número de equações e variáveis na primeira linha, seguido pelos coeficientes da matriz aumentada (coeficientes + termo independente).

Exemplo de formato para o sistema.txt (representando um sistema 2×2):

```
2 2
1 1 5
2 -1 1
```

Como funciona no programa:
Ao selecionar a Opção 9, o programa busca o arquivo na pasta, realiza o escalonamento via Eliminação de Gauss, exibe a classificação/solução na tela e salva automaticamente o resultado no seu histórico de sessão.

---


## 👩‍💻 Autora

**Maria Eduarda**
Engenharia de Software — IFG Campus Inhumas
Projeto Final — ATP2 + Álgebra Linear — 2026
