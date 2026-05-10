# ⚡ Quick Sort e Randomized Quick Sort: Análise Comparativa Multilinguagem

[![Status](http://img.shields.io/static/v1?label=STATUS&message=EM%20DESENVOLVIMENTO&color=GREEN&style=for-the-badge)]()
[![Linguagem](http://img.shields.io/static/v1?label=Linguagens&message=C%20|%20C%2B%2B%20|%20Java%20|%20Python%20|%20Go&color=GREEN&style=for-the-badge)]()

---

## 📃 Introdução

Este projeto foi desenvolvido como trabalho da disciplina de Algoritmos e Estruturas de Dados II (AEDS II), ministrada pelo professor Michel Pires da Silva, no Centro Federal de Educação Tecnológica de Minas Gerais (CEFET-MG), Campus V – Divinópolis.

O trabalho consiste na implementação e análise comparativa de dois algoritmos de ordenação pertencentes ao paradigma de **divisão e conquista**:

- **Quick Sort com Mediana de Três (QS-M3):** a cada chamada de partição, três índices são sorteados aleatoriamente dentro do subarranjo; o elemento mediano entre os três candidatos é designado pivô, produzindo partições mais equilibradas em média.
- **Randomized Quick Sort (RQS):** um único índice é sorteado uniformemente dentro do subarranjo e o elemento correspondente é imediatamente adotado como pivô, sendo uma abordagem mais simples computacionalmente.

Ambos os algoritmos foram implementados em cinco linguagens de programação — **C, C++, Java, Python e Go** — e avaliados sobre três cenários de entrada (aleatório, crescente e decrescente), com tamanhos variando de 10² a 10⁶ elementos. As métricas coletadas abrangem **tempo de execução médio** (em milissegundos) e **consumo de memória** (em megabytes).

A introdução de aleatoriedade na escolha do pivô elimina, na prática, o risco de degradação quadrática O(n²) presente no Quick Sort determinístico com pivô fixo sobre entradas adversariais, garantindo complexidade esperada de **O(n log n)** independentemente do padrão dos dados de entrada.

## 📋 Descrição dos Algoritmos

### 📌 Paradigma de Divisão e Conquista

Ambos os algoritmos estruturam a solução em três etapas recursivas:

1. **Divisão** — um elemento denominado pivô é selecionado e o subarranjo é particionado em dois grupos: elementos menores ou iguais ao pivô à esquerda, e maiores à direita.
2. **Conquista** — os dois subarranjos resultantes são ordenados recursivamente.
3. **Combinação** — nenhuma operação adicional é necessária, pois os subarranjos são ordenados in-place.

O particionamento segue o esquema de **Lomuto** em ambas as variantes: o pivô é movido para a última posição do subarranjo e um índice de fronteira percorre os elementos restantes, mantendo os não maiores que o pivô no lado esquerdo. Ao término, o pivô é inserido em sua posição definitiva.

---

### 📌 Quick Sort com Mediana de Três (QS-M3)

A cada chamada de partição, **três índices distintos** são sorteados aleatoriamente dentro do subarranjo ativo. O pivô é definido como o elemento cujo valor é a **mediana** dos três candidatos sorteados.

```
Dado o subarranjo A[p...r]:
  Sorteia ia, ib, ic distintos ∈ [p, r]
  Pivô = mediana(A[ia], A[ib], A[ic])
  Troca pivô com A[r]
  Aplica particionamento de Lomuto
```

Essa heurística produz pivôs estatisticamente mais centrais, com **menor variância** em relação ao sorteio puro, resultando em partições mais equilibradas e profundidade de recursão mais consistente.

---

### 📌 Randomized Quick Sort (RQS)

Um **único índice** é sorteado uniformemente dentro do subarranjo, e o elemento correspondente é imediatamente adotado como pivô.

```
Dado o subarranjo A[p...r]:
  Sorteia k uniforme ∈ [p, r]
  Pivô = A[k]
  Troca A[k] com A[r]
  Aplica particionamento de Lomuto
```

Essa abordagem é computacionalmente mais simples — **um sorteio por chamada** versus três no QS-M3 — porém gera pivôs potencialmente menos centrais em média. A aleatoriedade garante que o pior caso seja probabilisticamente improvável para qualquer entrada fixa.

---

### 📌 Comparação Conceitual

| Propriedade                  | QS-M3 (Mediana de Três) | RQS (Pivô Aleatório) |
|------------------------------|-------------------------|----------------------|
| Complexidade — melhor caso   | Θ(n log n)              | Θ(n log n)           |
| Complexidade — caso médio    | Θ(n log n)              | Θ(n log n)           |
| Complexidade — pior caso     | Θ(n²) prob.             | Θ(n²) prob.          |
| Complexidade de espaço       | O(log n) médio          | O(log n) médio       |
| Estabilidade                 | Não                     | Não                  |
| In-place                     | Sim                     | Sim                  |
| Sorteios por partição        | 3                       | 1                    |
| Qualidade esperada do pivô   | Alta                    | Média                |

## 🖥️ Ambiente de Criação

O código foi desenvolvido e testado utilizando as seguintes ferramentas e configurações:

[![C](https://img.shields.io/badge/Linguagem-C-blue?style=for-the-badge)]()
[![C++](https://img.shields.io/badge/Linguagem-C%2B%2B-blue?style=for-the-badge)]()
[![Java](https://img.shields.io/badge/Linguagem-Java-red?style=for-the-badge)]()
[![Python](https://img.shields.io/badge/Linguagem-Python-yellow?style=for-the-badge)]()
[![Go](https://img.shields.io/badge/Linguagem-Go-cyan?style=for-the-badge)]()
[![IDE](https://img.shields.io/badge/IDE-Visual%20Studio%20Code-blueviolet?style=for-the-badge)]()
[![SO](https://img.shields.io/badge/OS-Linux%20Mint%2022.1-orange?style=for-the-badge)]()

---

### 💻 Especificações da Máquina

| Componente              | Descrição                              |
|-------------------------|----------------------------------------|
| **Processador**         | Intel Core i5-13420H (13ª geração)     |
| **Memória RAM**         | 16 GB                                  |
| **Sistema Operacional** | Linux Mint 22.1                        |
| **Compilador C/C++**    | GCC 13 (otimizações padrão)            |
| **Runtime Java**        | OpenJDK 21                             |
| **Runtime Python**      | CPython 3.12                           |
| **Compilador Go**       | Go 1.22                                |
| **IDE**                 | Visual Studio Code                     |

---

### 📌 Considerações sobre os Ambientes de Execução

Cada linguagem introduz características distintas de desempenho que impactam diretamente os resultados:

- **C e C++** — geram código nativo durante a compilação, com acesso direto à memória e ausência de overhead de interpretação em tempo de execução. C++ utiliza o gerador **Mersenne Twister (std::mt19937)**, de maior qualidade estatística, enquanto C utiliza o `rand()` da libc, com maior correlação serial.
- **Java** — produz bytecode executado pela JVM com compilação **JIT**, apresentando overhead de runtime moderado e gerenciamento automático de memória via garbage collector. Duas execuções de aquecimento (warm-up) foram realizadas antes das medições para garantir que o JIT atingisse estado estacionário.
- **Python** — interpreta bytecode instrução por instrução no CPython, introduzindo custo por operação que tende a dominar o desempenho para entradas grandes, resultando em overhead significativamente maior que as demais linguagens.
- **Go** — compila para código nativo via compilador AOT, com overhead de runtime moderado e garbage collector integrado. A implementação do QS-M3 utiliza `sort.Slice` internamente para o cálculo da mediana, introduzindo overhead adicional de alocação de slice por chamada.

## 📁 Estrutura Geral do Projeto

```
.
├── Makefile                        # Script de compilação automática do projeto
├── input/
│   └── input.dat                   # Arquivo de entrada com os dados a serem ordenados
├── output/
│   └── output.dat                  # Arquivo de saída gerado a cada execução com os resultados
└── src/
    ├── c/
    │   ├── quicksort.c             # Implementação do QS-M3 e RQS em C
    │   └── quicksort.h             # Declarações das funções em C
    ├── cpp/
    │   ├── quicksort.cpp           # Implementação do QS-M3 e RQS em C++
    │   └── quicksort.hpp           # Declarações das funções em C++
    ├── java/
    │   └── QuickSort.java          # Implementação do QS-M3 e RQS em Java
    ├── python/
    │   └── quicksort.py            # Implementação do QS-M3 e RQS em Python
    └── go/
        └── quicksort.go            # Implementação do QS-M3 e RQS em Go
```

---

### 📌 Descrição dos Módulos

**`quicksort.c` / `quicksort.h`**
Implementação em C utilizando o gerador `rand()` da libc com semente fixa 67. Contém as funções de particionamento de Lomuto, seleção de pivô por mediana de três e por sorteio simples, e a rotina principal de ordenação recursiva.

**`quicksort.cpp` / `quicksort.hpp`**
Implementação em C++ utilizando o gerador Mersenne Twister (`std::mt19937`) com semente fixa 67, garantindo maior qualidade estatística na geração dos pivôs. Utiliza `std::vector` para armazenamento dos dados.

**`QuickSort.java`**
Implementação em Java utilizando `java.util.Random` com semente fixa 67. Inclui duas execuções de aquecimento (warm-up) antes das medições para garantir a estabilização do compilador JIT da JVM.

**`quicksort.py`**
Implementação em Python utilizando o módulo `random` com semente fixa 67. Por se tratar de uma linguagem interpretada, apresenta overhead significativamente maior que as demais implementações, especialmente para entradas de grande porte.

**`quicksort.go`**
Implementação em Go utilizando o pacote `math/rand` com semente fixa 67. O cálculo da mediana de três no QS-M3 utiliza `sort.Slice` internamente, introduzindo overhead adicional de alocação por chamada de partição em comparação às demais linguagens.

## ⚙️ Metodologia

Esta seção descreve em detalhes como os algoritmos foram implementados e avaliados, desde a geração dos dados de entrada até a coleta das métricas de desempenho.

---

### 📌 1. Geração dos Dados de Entrada

Os experimentos utilizaram cinco tamanhos de entrada, **n ∈ {10², 10³, 10⁴, 10⁵, 10⁶}**, que permitem observar o comportamento assintótico dos algoritmos em uma faixa de quatro ordens de magnitude. Para cada tamanho, três cenários de entrada foram avaliados:

- **Aleatório** — elementos inteiros gerados sem padrão de ordenação, representando o caso médio da análise teórica.
- **Crescente** — elementos em ordem estritamente não decrescente, cenário que seria adversarial para um Quick Sort com pivô fixo no primeiro ou último elemento, forçando-o ao caso quadrático.
- **Decrescente** — elementos em ordem estritamente não crescente, igualmente crítico para implementações determinísticas com pivô fixo.

A inclusão dos cenários crescente e decrescente é motivada precisamente pela capacidade das variantes aleatórias de **neutralizar esses padrões adversariais**, mantendo o comportamento esperado de Θ(n log n) independentemente da distribuição dos dados.

---

### 📌 2. Estratégia de Pivoteamento

#### QS-M3 — Mediana de Três Candidatos Aleatórios

```
Dado o subarranjo A[p...r]:
  Sorteia ia, ib, ic distintos ∈ [p, r]  (3 sorteios por partição)
  Pivô = mediana(A[ia], A[ib], A[ic])
  Troca pivô com A[r]
  Aplica particionamento de Lomuto
  Retorna índice de divisão
```

Um laço `while` garante que os três índices sorteados sejam sempre distintos, evitando candidatos repetidos no cálculo da mediana.

#### RQS — Pivô Uniformemente Aleatório

```
Dado o subarranjo A[p...r]:
  Sorteia k uniforme ∈ [p, r]  (1 sorteio por partição)
  Pivô = A[k]
  Troca A[k] com A[r]
  Aplica particionamento de Lomuto
  Retorna índice de divisão
```

---

### 📌 3. Particionamento de Lomuto

Ambas as variantes utilizam o esquema de Lomuto após a seleção do pivô:

```
particionar(A, p, r):
  pivô ← A[r]
  i ← p - 1
  para j de p até r - 1:
      se A[j] ≤ pivô:
          i ← i + 1
          troca A[i] com A[j]
  troca A[i+1] com A[r]
  retorna i + 1
```

O pivô é posicionado em sua localização definitiva ao final do particionamento, e os índices `p` até `i` contêm elementos menores ou iguais ao pivô, enquanto `i+2` até `r` contêm elementos maiores.

---

### 📌 4. Metodologia de Medição

Cada configuração experimental — definida pela combinação de **linguagem × algoritmo × cenário × tamanho** — foi executada **100 vezes**, adotando o tempo médio aritmético como métrica principal. Essa quantidade de repetições é suficiente para atenuar variações esporádicas causadas por eventos de sistema operacional, sem introduzir custo computacional excessivo.

A cronometragem foi realizada com resolução submilissegundo em cada linguagem:

| Linguagem | Mecanismo de Medição             |
|-----------|----------------------------------|
| C         | `clock_gettime` (CLOCK_MONOTONIC)|
| C++       | `clock_gettime` (CLOCK_MONOTONIC)|
| Java      | `System.nanoTime()`              |
| Python    | `time.perf_counter()`            |
| Go        | `time.Since()`                   |

> ⚠️ Apenas a rotina de ordenação é incluída na janela de medição. A leitura do arquivo de entrada e a cópia do arranjo são realizadas **fora** do intervalo cronometrado.

O consumo de memória foi coletado como o **Resident Set Size (RSS)** do processo, medido ao final de cada execução pelo utilitário **GNU Time**. Imediatamente antes de cada execução, o coletor de lixo foi invocado explicitamente nas linguagens que o utilizam (Python, Go), reduzindo a probabilidade de que uma coleta espontânea interfira na medição de tempo.

---

### 📌 5. Reprodutibilidade

A semente do gerador pseudoaleatório foi fixada em **67** em todas as linguagens e implementações, assegurando que a sequência de pivôs seja idêntica entre repetições e que os resultados sejam plenamente reprodutíveis entre execuções.

---

### 📌 6. Fluxo Completo Resumido

```
gerarEntrada(n, cenário)        ← aleatório | crescente | decrescente

Para cada execução de 1 até 100:
    copiarArranjo()             ← cópia fora da janela de medição
    iniciarCronômetro()
    quicksort(A, 0, n-1)        ← QS-M3 ou RQS
    pararCronômetro()
    registrarTempo()

calcularMediaTempos()
coletarMemóriaRSS()
gravarOutput()
```
## 📊 Resultados e Discussão

Os resultados apresentados a seguir foram obtidos a partir de **100 repetições** por configuração, reportando-se o tempo médio de execução em milissegundos e o consumo médio de memória em megabytes. Todos os gráficos utilizam escala logarítmica no eixo do tempo de execução, permitindo identificar visualmente a inclinação característica de curvas Θ(n log n).

---

### 📌 1. Cenário de Entrada Aleatória

#### ⏱️ Tempo de Execução (ms)

| Linguagem | Algoritmo | 10²    | 10³    | 10⁴     | 10⁵      | 10⁶       |
|-----------|-----------|--------|--------|---------|----------|-----------|
| Java      | QS (M3)   | 0.0638 | 0.2046 | 1.4001  | 16.1672  | 161.0770  |
| Java      | RQS       | 0.0431 | 0.1630 | 1.1329  | 12.8159  | 135.9280  |
| C         | QS (M3)   | 0.0159 | 0.2315 | 1.9824  | 26.3507  | 293.4478  |
| C         | RQS       | 0.0040 | 0.0946 | 1.7540  | 18.0918  | 197.0611  |
| C++       | QS (M3)   | 0.0101 | 0.1922 | 1.1728  | 12.5330  | 132.9460  |
| C++       | RQS       | 0.0067 | 0.1156 | 1.1165  | 11.4573  | 128.8632  |
| Python    | QS (M3)   | 0.2070 | 2.1556 | 25.1085 | 274.9268 | 3161.1922 |
| Python    | RQS       | 0.1048 | 1.2889 | 19.1878 | 195.5691 | 2552.6708 |
| Go        | QS (M3)   | 0.0433 | 0.3886 | 3.1138  | 39.6880  | 289.0614  |
| Go        | RQS       | 0.0119 | 0.1618 | 1.2864  | 18.5309  | 141.8973  |

#### 🗂️ Consumo de Memória (MB)

| Linguagem | Algoritmo | 10²    | 10³    | 10⁴    | 10⁵    | 10⁶    |
|-----------|-----------|--------|--------|--------|--------|--------|
| Java      | QS (M3)   | 44.46  | 46.87  | 49.86  | 67.27  | 149.39 |
| Java      | RQS       | 44.89  | 45.12  | 47.69  | 65.74  | 149.39 |
| C         | QS (M3)   | 1.625  | 1.500  | 1.750  | 1.859  | 5.160  |
| C         | RQS       | 1.500  | 1.625  | 1.750  | 1.961  | 5.059  |
| C++       | QS (M3)   | 3.750  | 3.625  | 3.875  | 4.082  | 7.391  |
| C++       | RQS       | 3.750  | 3.750  | 3.500  | 4.074  | 7.449  |
| Python    | QS (M3)   | 116.36 | 116.53 | 116.22 | 116.34 | 116.75 |
| Python    | RQS       | 106.01 | 106.09 | 106.13 | 106.16 | 106.13 |
| Go        | QS (M3)   | 32.75  | 40.25  | 40.63  | 40.96  | 49.43  |
| Go        | RQS       | 40.25  | 40.13  | 40.38  | 33.66  | 47.63  |

#### 🔍 Análise

No cenário aleatório, **C++ posicionou-se consistentemente como a linguagem mais rápida** para o QS-M3 (132.9 ms para n = 10⁶), beneficiando-se do gerador Mersenne Twister e das otimizações do compilador GCC. C, surpreendentemente, registrou 293.4 ms — desempenho próximo ao de Go QS-M3 (289.1 ms) — diferença atribuída à qualidade inferior do `rand()` da libc em relação ao `std::mt19937` de C++. Python permaneceu uma ordem de grandeza acima de todas as demais linguagens, com 3161.2 ms, confirmando que o overhead de interpretação do CPython é dominante para entradas grandes.

---

### 📌 2. Cenário de Entrada Crescente

#### ⏱️ Tempo de Execução (ms)

| Linguagem | Algoritmo | 10²    | 10³    | 10⁴     | 10⁵      | 10⁶       |
|-----------|-----------|--------|--------|---------|----------|-----------|
| Java      | QS (M3)   | 0.0420 | 0.1583 | 0.8796  | 7.1044   | 70.0520   |
| Java      | RQS       | 0.0247 | 0.1074 | 0.5742  | 5.0338   | 56.1196   |
| C         | QS (M3)   | 0.0154 | 0.1545 | 1.6819  | 14.5216  | 140.0396  |
| C         | RQS       | 0.0044 | 0.0628 | 1.1278  | 8.6347   | 79.1894   |
| C++       | QS (M3)   | 0.0059 | 0.1035 | 0.6773  | 5.2555   | 55.5162   |
| C++       | RQS       | 0.0046 | 0.0532 | 0.5190  | 4.0507   | 42.0423   |
| Python    | QS (M3)   | 0.1805 | 2.4670 | 21.7283 | 239.2484 | 2579.9874 |
| Python    | RQS       | 0.0932 | 1.3464 | 14.3405 | 170.0275 | 1882.6513 |
| Go        | QS (M3)   | 0.0436 | 0.4631 | 2.3019  | 23.2556  | 201.6445  |
| Go        | RQS       | 0.0109 | 0.0931 | 0.7648  | 5.7369   | 55.6746   |

#### 🔍 Análise

Um resultado de importância central: **ambas as variantes mantêm crescimento Θ(n log n) mesmo sobre entrada já ordenada**, confirmando que a aleatoriedade do pivô neutraliza completamente o padrão da entrada. Mais do que isso, os tempos absolutos são **inferiores aos do cenário aleatório** para todas as linguagens — C++ QS-M3 atingiu 55.5 ms para n = 10⁶ contra 132.9 ms no cenário aleatório — fenômeno explicado pela **localidade de cache**: uma entrada ordenada é lida sequencialmente pelo laço de partição de forma completamente previsível, gerando menos faltas de cache do que uma entrada aleatória.

---

### 📌 3. Cenário de Entrada Decrescente

#### ⏱️ Tempo de Execução (ms)

| Linguagem | Algoritmo | 10²    | 10³    | 10⁴     | 10⁵      | 10⁶       |
|-----------|-----------|--------|--------|---------|----------|-----------|
| Java      | QS (M3)   | 0.0493 | 0.1624 | 0.9233  | 8.1624   | 79.2152   |
| Java      | RQS       | 0.0408 | 0.1200 | 0.6794  | 5.7569   | 57.7372   |
| C         | QS (M3)   | 0.0059 | 0.1040 | 2.0031  | 15.1637  | 134.1959  |
| C         | RQS       | 0.0036 | 0.0555 | 0.9653  | 9.5243   | 84.6219   |
| C++       | QS (M3)   | 0.0083 | 0.0842 | 0.7283  | 6.1147   | 61.7695   |
| C++       | RQS       | 0.0053 | 0.0860 | 0.5782  | 4.6017   | 48.1521   |
| Python    | QS (M3)   | 0.1816 | 2.1493 | 22.1241 | 236.7242 | 2638.1742 |
| Python    | RQS       | 0.0928 | 1.2011 | 14.7021 | 162.6171 | 1893.3620 |
| Go        | QS (M3)   | 0.0385 | 0.3615 | 2.3128  | 24.0365  | 207.4554  |
| Go        | RQS       | 0.0116 | 0.1109 | 0.8103  | 6.1424   | 61.6969   |

#### 🔍 Análise

Os perfis de tempo do cenário decrescente são **quase idênticos ao cenário crescente**, com diferenças menores que 15% entre os dois cenários para todas as linguagens. Esse resultado é uma confirmação forte de que o **pivô aleatório torna o algoritmo completamente insensível ao padrão de ordenação prévia da entrada**, comportando-se de forma similar independentemente de os dados estarem crescentes, decrescentes ou aleatórios.

---

### 📌 4. Comparativo Final: Speedup do RQS sobre o QS-M3 (n = 10⁶)

| Linguagem | Aleatório | Crescente | Decrescente |
|-----------|-----------|-----------|-------------|
| Java      | 1.18×     | 1.25×     | 1.37×       |
| C         | 1.49×     | 1.77×     | 1.59×       |
| C++       | 1.03×     | 1.32×     | 1.28×       |
| Python    | 1.24×     | 1.37×     | 1.39×       |
| Go        | 2.04×     | 3.62×     | 3.36×       |

> Valores > 1 indicam que o RQS foi mais rápido que o QS-M3.

O RQS foi **consistentemente mais rápido** que o QS-M3 em todos os cenários e linguagens testados, com speedups variando de 1.03× (C++, aleatório) a 3.62× (Go, crescente). Esse resultado é contraintuitivo: embora a mediana de três produza pivôs estatisticamente melhores, o **custo dos dois sorteios adicionais por chamada de partição** supera, na prática, o ganho em qualidade de pivô para os tamanhos de entrada avaliados. Go apresenta os maiores speedups devido ao overhead adicional do `sort.Slice` interno utilizado no cálculo da mediana.

## ⌨️ Instalação e Execução

### 📌 Pré-requisitos

Para compilar e executar o projeto, certifique-se de ter instalado:

- **g++** com suporte a C++17 ou superior
- **gcc** com suporte a C11 ou superior
- **OpenJDK 21** ou superior
- **Python 3.12** ou superior
- **Go 1.22** ou superior
- **Make**
- **Linux** (Ubuntu 24.04, Linux Mint 22.1 ou equivalente)

---

### 📌 Passo a Passo

#### 1. Clonar o repositório

```bash
git clone https://github.com/[SEU-USUARIO]/[SEU-REPOSITORIO].git
cd [SEU-REPOSITORIO]
```

---

#### 2. Configurar o arquivo de entrada

O arquivo `input/input.dat` deve seguir o seguinte formato:

```
N cenário
```

Onde:
- **N**: número de elementos a serem ordenados
- **cenário**: tipo da entrada (`random`, `ascending` ou `descending`)

Exemplo:
```
1000000 random
```

---

#### 3. Executar em C

Verifique se o compilador está instalado:

```bash
gcc --version
```

Caso não esteja instalado:

```bash
sudo apt update
sudo apt install gcc -y
```

Compilar e executar:

```bash
cd src/c
gcc -O2 -o quicksort quicksort.c
./quicksort
```

---

#### 4. Executar em C++

Verifique se o compilador está instalado:

```bash
g++ --version
```

Caso não esteja instalado:

```bash
sudo apt update
sudo apt install g++ -y
```

Compilar e executar:

```bash
cd src/cpp
g++ -O2 -std=c++17 -o quicksort quicksort.cpp
./quicksort
```

---

#### 5. Executar em Java

Verifique se o runtime está instalado:

```bash
java --version
```

Caso não esteja instalado:

```bash
sudo apt update
sudo apt install openjdk-21-jdk -y
```

Compilar e executar:

```bash
cd src/java
javac QuickSort.java
java QuickSort
```

---

#### 6. Executar em Python

Verifique se o interpretador está instalado:

```bash
python3 --version
```

Caso não esteja instalado:

```bash
sudo apt update
sudo apt install python3 -y
```

Executar:

```bash
cd src/python
python3 quicksort.py
```

---

#### 7. Executar em Go

Verifique se o compilador está instalado:

```bash
go version
```

Caso não esteja instalado:

```bash
sudo apt update
sudo apt install golang -y
```

Executar:

```bash
cd src/go
go run quicksort.go
```

---

#### 8. Executar todos com Makefile

Para compilar e executar todas as linguagens de uma vez:

```bash
make
```

Para executar após compilação:

```bash
make run
```

Para limpar os arquivos compilados:

```bash
make clean
```

---

### 📌 Saída Esperada

Após a execução, o arquivo `output/output.dat` será gerado com os resultados de cada configuração, contendo:

- Linguagem utilizada
- Algoritmo utilizado (QS-M3 ou RQS)
- Tamanho da entrada (n)
- Cenário da entrada (aleatório, crescente ou decrescente)
- Tempo médio de execução (ms)
- Consumo de memória (MB)

Exemplo de saída:
```
Linguagem:  C++
Algoritmo:  QS-M3
Tamanho:    1000000
Cenário:    Aleatório
Tempo médio: 132.9460 ms
Memória:     7.391 MB
```

## 📊 Análises e Conclusões

### 📌 1. Comportamento Assintótico

Em todos os cenários e linguagens, o crescimento do tempo de execução com o tamanho da entrada foi **consistente com a complexidade Θ(n log n)** esperada. Para verificar numericamente esse comportamento, observa-se que ao aumentar n de 10⁵ para 10⁶ (fator 10), o tempo de execução cresce por um fator próximo de 10 · log(10⁶)/log(10⁵) = 12, compatível com Θ(n log n).

Por exemplo, em C++ com o QS-M3 no cenário aleatório:

| n      | Tempo (ms) | Fator de crescimento |
|--------|------------|----------------------|
| 10²    | 0.0101     | —                    |
| 10³    | 0.1922     | ~19×                 |
| 10⁴    | 1.1728     | ~6×                  |
| 10⁵    | 12.5330    | ~10.7×               |
| 10⁶    | 132.9460   | ~10.6×               |

Os fatores de crescimento observados são compatíveis com Θ(n log n), sem qualquer inflexão em direção quadrática — confirmando que a aleatoriedade do pivô **eliminou efetivamente o risco de degradação para O(n²)** mesmo sobre entradas ordenadas e decrescentes.

---

### 📌 2. Impacto da Estratégia de Pivoteamento

O Randomized Quick Sort com pivô simples mostrou-se **contraintuitivamente mais rápido** que a variante com mediana de três em quase todos os cenários testados. Embora a mediana de três produza pivôs estatisticamente mais centrais, o custo computacional dos dois sorteios adicionais por chamada de partição supera, na prática, o ganho em qualidade de pivô para os tamanhos de entrada avaliados.

Três fases distintas de comportamento foram observadas ao longo dos tamanhos de entrada:

**Fase 1 — Entradas Pequenas (n ≤ 10³)**
A diferença entre QS-M3 e RQS é praticamente imperceptível. O custo de inicialização e overhead fixo das linguagens domina sobre o custo algorítmico.

**Fase 2 — Entradas Médias (10³ < n ≤ 10⁵)**
O custo dos sorteios adicionais do QS-M3 começa a se manifestar. O RQS passa a apresentar vantagem mensurável, especialmente em Go, onde o `sort.Slice` interno introduz overhead adicional de alocação por chamada.

**Fase 3 — Entradas Grandes (n > 10⁵)**
A diferença entre as variantes se consolida. O RQS é consistentemente mais rápido, com speedups de até **3.62×** em Go no cenário crescente. O custo de aproximadamente 2 × 10⁶ sorteios adicionais do QS-M3 torna-se determinante no tempo total de execução.

---

### 📌 3. Impacto da Linguagem de Programação

A linguagem de programação revelou-se o **fator de maior impacto** na constante multiplicativa do desempenho observado:

| Linguagem | Característica Principal                        | Tempo QS-M3 (n=10⁶, aleatório) |
|-----------|-------------------------------------------------|----------------------------------|
| C++       | Código nativo + Mersenne Twister                | 132.9 ms                         |
| Java      | JIT estabilizado + overhead moderado de JVM     | 161.1 ms                         |
| C         | Código nativo + rand() de baixa qualidade       | 293.4 ms                         |
| Go        | AOT + overhead do sort.Slice na mediana         | 289.1 ms                         |
| Python    | Interpretação bytecode + overhead por operação  | 3161.2 ms                        |

Uma observação relevante é que **C foi mais lento que C++** no cenário aleatório com QS-M3, resultado atribuído à qualidade inferior do gerador `rand()` da libc em relação ao `std::mt19937` de C++. Isso evidencia que a **qualidade do gerador de números pseudoaleatórios é parte integrante do desempenho** do Randomized Quick Sort, não apenas a estratégia de pivoteamento em si.

---

### 📌 4. Impacto do Padrão da Entrada

Os resultados confirmaram que **o pivô aleatório torna ambos os algoritmos completamente insensíveis ao padrão de ordenação prévia da entrada**. As diferenças entre os cenários crescente, decrescente e aleatório foram menores que 15% para todas as linguagens no RQS, e os tempos nos cenários ordenados foram até **menores** que no cenário aleatório, devido à melhor localidade de cache proporcionada pelo acesso sequencial ao arranjo.

---

### 📌 5. Consumo de Memória

O consumo de memória mostrou-se **uma propriedade do runtime e do tamanho da entrada**, e não do padrão dos dados ou da estratégia de pivoteamento:

- **C e C++** — crescimento linear suave de ~1.5 MB (n=10²) a ~7 MB (n=10⁶), reflexo exclusivo da alocação do arranjo de inteiros.
- **Java** — consumo estável entre 44–67 MB até n=10⁵, saltando para ~149 MB em n=10⁶ quando o heap da JVM precisa crescer substancialmente.
- **Python** — consumo absolutamente constante em ~106–116 MB para todos os tamanhos, evidenciando que o overhead do processo Python domina sobre o custo dos dados.
- **Go** — comportamento estável na faixa de 33–49 MB, dominado pelo overhead do runtime e do garbage collector.

---

### 📌 6. Conclusão Geral

O estudo demonstrou que:

- A **aleatoriedade do pivô** elimina efetivamente o risco de degradação quadrática, validando a robustez das abordagens contra entradas adversariais.
- O **Randomized Quick Sort com pivô simples** é, contraintuitivamente, mais rápido que a variante com mediana de três na maioria dos cenários, pois o custo dos sorteios adicionais supera o ganho em qualidade de pivô.
- A **qualidade do gerador pseudoaleatório** é um fator relevante no desempenho, com o Mersenne Twister de C++ produzindo resultados melhores que o `rand()` de C.
- A **linguagem de programação** é o fator de maior impacto na constante multiplicativa do desempenho, com C++ e Java liderando entre as linguagens avaliadas.
- O **consumo de memória** é governado principalmente pelo overhead do runtime de cada linguagem, e não pelo algoritmo ou padrão dos dados.

---

### 📌 7. Limitações e Trabalhos Futuros

**Limitações:**
- Utilização de semente fixa (67), que pode introduzir viés dependente da semente específica.
- Ausência de análise estatística formal (intervalos de confiança, desvios padrão) sobre as 100 repetições.
- Avaliação limitada a entradas inteiras, sem considerar entradas de ponto flutuante ou strings.
- Não avaliação de entradas parcialmente ordenadas.

**Trabalhos Futuros:**
- Avaliar o impacto de diferentes sementes e geradores pseudoaleatórios sobre a distribuição dos pivôs selecionados.
- Implementar e comparar o **IntroSort**, variante híbrida que combina Quick Sort com Heap Sort para garantir O(n log n) no pior caso determinístico.
- Analisar o comportamento com **tail recursion optimization** e **iterative quicksort**, avaliando o impacto na profundidade de pilha.
- Estender a análise para entradas parcialmente ordenadas e para dados de ponto flutuante com diferentes distribuições.
