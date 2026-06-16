# Trabalho Final - Estrutura de Dados II

Projeto desenvolvido para a disciplina de **Estrutura de Dados II**, aplicando conceitos de **Teoria dos Grafos** para análise de redes de computadores a partir de arquivos de log.

---

# Compilação e Execução

## 1. Acesse o diretório do projeto

Abra o terminal e navegue até a pasta onde os arquivos estão localizados:

```bash
cd "/caminho/para/a/pasta/do/projeto"
```

## 2. Compile o código

Utilize o compilador **g++** para gerar o executável:

```bash
g++ graphroute.cpp -o graphroute
```

## 3. Execute o programa

É obrigatório informar um arquivo de log como argumento:

```bash
./graphroute input_1.log
```

---

# Funcionalidades

## Exibir Grafo Completo

Imprime toda a estrutura da rede no formato **.dot**, permitindo a visualização em ferramentas como o **Graphviz**.

---

## Encontrar Menor Caminho

Determina a rota mais curta entre um IP de origem e um IP de destino, destacando visualmente o caminho encontrado.

---

## Calcular o Diâmetro do Grafo

Calcula a maior distância possível (número máximo de saltos) entre quaisquer dois dispositivos conectados da rede.

---

## Identificar Roteadores Críticos

Exibe o **Top 5 roteadores** com maior grau de entrada (*In-degree*), identificando gargalos e hubs centrais da infraestrutura.

---

# Estrutura do Projeto

O sistema modela uma rede de computadores como um **grafo direcionado**, onde:

* Cada IP representa um vértice (nó);
* Cada comunicação registrada no log representa uma aresta;
* As conexões possuem peso uniforme (1 salto).

---

# Justificativa Técnica

As decisões arquiteturais e algorítmicas adotadas foram baseadas nos conceitos de **Teoria dos Grafos**, buscando eficiência tanto em memória quanto em tempo de execução.

---

## Representação do Grafo (Lista de Adjacência + Hash Map)

A rede foi modelada utilizando:

* **Lista de Adjacência** para armazenar as conexões;
* **std::unordered_map** para mapear rapidamente cada endereço IP ao seu respectivo nó.

### Justificativa

Redes de roteadores geralmente formam **grafos esparsos**, onde o número de conexões é muito menor que o número máximo possível.

Por esse motivo, utilizar uma **Matriz de Adjacência** resultaria em grande desperdício de memória.

O uso de `std::unordered_map` garante acesso médio em tempo constante:

```text
O(1)
```

Isso torna a construção do grafo eficiente mesmo para arquivos de log extensos.

---

## Menor Caminho e Diâmetro (Busca em Largura - BFS)

Para determinar:

* O menor caminho entre dois IPs;
* O diâmetro da rede;

foi utilizada a técnica de **Busca em Largura (Breadth-First Search - BFS)** com a estrutura `std::queue`.

### Justificativa

Como todas as conexões possuem o mesmo custo (**1 salto**), a BFS é o algoritmo mais eficiente para encontrar caminhos mínimos em grafos não ponderados.

### Complexidade

Para uma execução:

```text
O(V + E)
```

Onde:

* `V` = quantidade de vértices;
* `E` = quantidade de arestas.

No cálculo do diâmetro, a BFS é executada para todos os vértices possíveis como origem, permitindo encontrar a maior distância existente na rede.

---

##  Identificação de Roteadores Críticos (Grau de Entrada - In-degree)

Para localizar os nós mais importantes da rede, o sistema contabiliza o número de conexões recebidas por cada roteador.

### Processo

1. Percorre todas as arestas do grafo;
2. Conta as incidências de entrada para cada nó;
3. Armazena os resultados em um vetor de pares;
4. Ordena os valores em ordem decrescente.

### Justificativa

A ordenação é realizada utilizando:

```cpp
std::sort()
```

associado a uma função **Lambda**, permitindo obter rapidamente os roteadores com maior centralidade.

### Complexidade

Ordenação dos resultados:

```text
O(N log N)
```

Onde `N` representa a quantidade de roteadores da rede.

---