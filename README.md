# Trabalho 3: Sistema de Matchmaking para Jogos Online

![C++](https://img.shields.io/badge/language-C++-blue)
![Build](https://img.shields.io/badge/build-passing-brightgreen)
![Status](https://img.shields.io/badge/status-academic--project-lightgrey)

Sistema de matchmaking para jogos online desenvolvido em C++, utilizando estruturas implementadas manualmente, controle explícito de memória e algoritmos de ordenação para organizar jogadores por compatibilidade.

---

## Descrição

Este projeto simula um **sistema de matchmaking para jogos online**.

O sistema gerencia jogadores em espera e forma grupos com base na compatibilidade entre suas pontuações. Cada jogador possui:

- identificador (`id`)
- nome
- pontuação (`score`)
- timestamp

O objetivo principal é formar grupos de jogadores cujas pontuações estejam suficientemente próximas, de acordo com uma diferença máxima permitida (`delta`).

Antes da formação de grupos, os jogadores em espera podem ser ordenados por pontuação, permitindo que o sistema procure jogadores compatíveis de forma mais organizada.

---

## Organização Interna dos Dados

Os dados são armazenados em uma estrutura `Matchmaking`, que gerencia internamente um array de jogadores.

Cada jogador é representado pela classe `Player`.

### Estrutura geral

```
Matchmaking
│
├── Array de jogadores
│   ├── Player
│   ├── Player
│   └── ...
│
└── size
```

Cada `Player` armazena:

- `id`
- `name`
- `score`
- `timestamp`

O array contém os jogadores que estão atualmente aguardando para serem agrupados.

---

## Funcionamento

### Inserção de jogadores (`insert`)

Quando um novo jogador entra no sistema:

1. O jogador é inserido no final do array interno
2. O número de jogadores em espera é incrementado
3. Caso o array esteja cheio, a inserção não é realizada

---

### Remoção de jogadores (`removePlayer`)

Um jogador pode ser removido do sistema a partir de seu `id`.

O processo de remoção é feito da seguinte forma:

1. Busca linear pelo identificador do jogador
2. Deslocamento dos jogadores seguintes uma posição para a esquerda
3. Redução do número de jogadores em espera

Essa abordagem mantém o array compacto, sem espaços vazios entre os jogadores.

---

### Formação de grupos (`formGroup`)

O método `formGroup` recebe:

- o tamanho desejado do grupo
- a diferença máxima permitida entre pontuações (`delta`)
- um ponteiro usado para retornar o número real de jogadores no grupo

O método procura uma sequência de jogadores tal que:

```
maior_pontuacao - menor_pontuacao <= delta
```

Se um grupo compatível for encontrado:

1. Um novo array é alocado para armazenar o grupo
2. Os jogadores selecionados são copiados para esse array
3. Esses jogadores são removidos da lista de espera
4. O método retorna o grupo formado

Se nenhum grupo compatível for encontrado, o método retorna `nullptr`.

---

## Algoritmos de Ordenação

O projeto implementa algoritmos de ordenação para organizar os jogadores por pontuação.

O critério de ordenação é:

```
menor score vem primeiro
empate → menor timestamp vem primeiro
```

Ou seja, os jogadores são ordenados principalmente pela pontuação. Em caso de empate, o jogador com menor timestamp tem prioridade.

---

### Insertion Sort

O Insertion Sort foi implementado como um algoritmo simples de ordenação por comparação.

Ele funciona mantendo uma parte inicial do array ordenada e inserindo cada novo elemento na posição correta.

Principais características:

- implementação simples
- comportamento adequado para entradas pequenas ou quase ordenadas
- usa o timestamp como critério de desempate
- possui custo quadrático no caso geral

Complexidade:

| Caso | Complexidade |
|------|-------------|
| Melhor caso | O(n) |
| Caso médio | O(n²) |
| Pior caso | O(n²) |

---

### Merge Sort

O Merge Sort foi implementado como um algoritmo recursivo baseado na estratégia de divisão e conquista.

Ele funciona da seguinte forma:

1. Divide o array em duas metades
2. Ordena recursivamente cada metade
3. Intercala as duas metades ordenadas em uma única sequência

Principais características:

- desempenho previsível
- eficiente para entradas grandes
- exige memória auxiliar durante a etapa de intercalação
- preserva o critério de ordenação por score e timestamp

Complexidade:

| Caso | Complexidade |
|------|-------------|
| Melhor caso | O(n log n) |
| Caso médio | O(n log n) |
| Pior caso | O(n log n) |

---

## Operações

As principais operações implementadas no projeto são:

- inserção de jogador (`insert`)
- remoção de jogador por id (`removePlayer`)
- formação de grupo (`formGroup`)
- consulta aos jogadores em espera (`getWaitingPlayers`)
- impressão dos jogadores em espera (`printWaitingPlayers`)
- impressão de grupos formados (`printGroup`)
- ordenação por score usando Insertion Sort
- ordenação por score usando Merge Sort
- testes de desempenho usando `<chrono>`

---

## Complexidade

| Operação | Complexidade |
|----------|-------------|
| `insert()` | O(1) |
| `removePlayer()` | O(n) |
| `formGroup()` | O(n · g) ou O(n), dependendo da implementação |
| `getWaitingPlayers()` | O(n) |
| `printWaitingPlayers()` | O(n) |
| `printGroup()` | O(n) |
| Insertion Sort | O(n²) |
| Merge Sort | O(n log n) |
| Teste de desempenho com Insertion Sort | O(n²) |
| Teste de desempenho com Merge Sort | O(n log n) |

Onde:

- `n` é o número de jogadores em espera
- `g` é o tamanho desejado do grupo

---

## Detalhes de Implementação

- Armazenamento baseado em array
- Controle explícito de memória com `new` e `delete`
- Não utilização de contêineres da STL, como `vector`
- Algoritmos de ordenação implementados manualmente
- Score usado como principal critério de compatibilidade
- Timestamp usado como critério de desempate
- Alocação dinâmica usada ao retornar grupos formados
- Verificações defensivas para grupos vazios e casos inválidos
- Medição de desempenho realizada com a biblioteca `<chrono>`

---

## Alternativas Consideradas

- Lista encadeada de jogadores  
  - remoção mais simples após encontrar o nó  
  - acesso indexado menos eficiente  
  - menos conveniente para os algoritmos de ordenação

- Array sempre ordenado  
  - formação de grupos se torna mais simples  
  - inserção passa a custar O(n)

- Ordenação apenas quando necessário  
  - inserção permanece O(1)  
  - o custo da ordenação é pago antes da formação de grupos ou dos testes

- Organização baseada em heap  
  - útil para acesso por prioridade  
  - menos adequada para encontrar grupos dentro de intervalos de score

---

## Trade-offs

- O array fornece acesso indexado simples e eficiente
- A remoção linear é simples, mas custa O(n)
- A inserção no final é rápida
- Ordenar antes do matchmaking facilita a verificação de compatibilidade
- Insertion Sort é simples, mas ineficiente para entradas grandes
- Merge Sort é mais eficiente, mas exige memória auxiliar
- O gerenciamento manual de memória oferece controle, mas exige cuidado
- Grupos retornados como arrays alocados dinamicamente devem ser liberados pelo chamador

---

## Testes de Desempenho

Além dos testes funcionais, o projeto inclui testes de desempenho usando a biblioteca `<chrono>`.

O objetivo é comparar o tempo de execução dos algoritmos de ordenação implementados para diferentes quantidades de jogadores.

Os testes medem o tempo necessário para ordenar jogadores usando:

- Insertion Sort
- Merge Sort

Os tamanhos de entrada podem incluir, por exemplo:

- 100 jogadores
- 1.000 jogadores
- 10.000 jogadores
- 50.000 jogadores

Os dados de teste são gerados criando jogadores com diferentes pontuações e timestamps.

O comportamento esperado é que:

- o Insertion Sort tenha desempenho aceitável para entradas pequenas
- o Insertion Sort fique significativamente mais lento conforme a entrada cresce
- o Merge Sort permaneça eficiente para entradas maiores
- os resultados observados estejam de acordo com os custos computacionais esperados

---

## Testes

O arquivo `main.cpp` contém cenários de teste para:

- criação de jogadores
- inserção no sistema de matchmaking
- impressão dos jogadores em espera
- remoção de jogadores por id
- formação de grupos compatíveis
- casos em que nenhum grupo pode ser formado
- ordenação por score usando Insertion Sort
- ordenação por score usando Merge Sort
- comparação de desempenho usando `<chrono>`

---

## Compilação

```bash
g++ -Wall -Wextra -Werror -Wshadow -Wpedantic -Wconversion -Wsign-conversion -Wnull-dereference -std=c++17 \
main.cpp Player.cpp Matchmaking.cpp -o matchmaking
```

---

## Execução

```bash
./matchmaking
```

---

## Exemplo de Comportamento Esperado

Após inserir jogadores no sistema, a lista de espera pode ser impressa.

Em seguida, depois de ordenar os jogadores por score, o sistema pode tentar formar um grupo cuja diferença de pontuação esteja dentro do valor de `delta` escolhido.

Se um grupo válido existir, ele é retornado e removido da lista de espera.

Se nenhum grupo válido existir, o sistema informa que nenhum grupo compatível foi encontrado.

---

## Observações

Este projeto foi desenvolvido para fins acadêmicos como parte da disciplina de Estrutura de Dados.

A implementação tem como foco:

- compreensão de estruturas baseadas em array
- prática de gerenciamento manual de memória
- implementação de algoritmos de ordenação
- análise de complexidade algorítmica
- comparação entre desempenho empírico e complexidade teórica
