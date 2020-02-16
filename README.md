  #  <center> PROBLEMA GENERALIZADO DE ATRIBUIÇÃO </center>

O Problema Generalizado de Atribuição (PGA) é um dos mais relevantes problemas de otimização combinatória. Sua resolução consiste em atribuir um conjunto de
agentes para atender um conjunto de tarefas a um custo mínimo, sem sobrecarregar os
agentes além da sua capacidade Martello (1981). A característica NP-Difícil intrínseca
ao PGA, torna-o de difícil tratamento até a otimalidade, pois um crescimento linear do
número de variáveis do problema (agentes e tarefas) provoca um acréscimo exponencial
nos recursos dos agentes utilizados para resolvê-lo. Isso significa que, para instâncias o
bastante grandes, não há uma metodologia comprovadamente eficaz para resolvê-los até
a solução ótima.
Para encontrar boas soluções foi aplicado métodos heurísticos para construção e
refinamento, busca local e uma meta-heurística.


 

 ## Descrição do Algoritmo

- [Representação](#Representação)
- [Métodos Construtivos](#Métodos-Construtivos)
- [Heurísticas de Refinamento](#Heurísticas-de-Refinamento)
- [Busca Local](#Busca-Local)
- [Meta-Heurística](#Meta-Heurística)
- [Pertubação](#Pertubação)


## Representação

A representação da solução é dada por um vetor de inteiros em que os indices do
vetor representam as tarefas e o valor da posição, o agente que desempenha a tarefa.

```sh
            Vetor de Solução

                0 1 2 3 = Indices (tarefas)
                3 1 4 1 = Valor (agente que desempenha a tarefa)
```
No exemplo: 

- O agente **3** desempenha a tarefa **0**. 
- O agente **1** desempenha as tarefas **1 e 3**. 
- O agente **4** desempenha a tarefa **2**. 


## Métodos Construtivos
As Soluções iniciais foram criadas a partir de dois métodos, Aleatório e Guloso. 
### Aleatório
Neste método, para cada tarefa foi atribuído um agente de forma aleatória. Neste
método não é respeitada as restrições em que garante que o limite de recurso dos
agentes não seja extrapolado, pois respeitando-as, as instâncias seriam iniviáveis
### Guloso 
O método guloso foi desenvolvido pelo critério custo por recurso. As tarefas são
designadas aos agentes que possuem o menor custo/recurso para exercê-las.
## Heurísticas de Refinamento
Para refinamentos das soluções iniciais, foram aplicadas duas heurísticas. Melhor
troca (Best Improvement) e Primeira Melhor Troca (First Improvement).

### Best Improvement
Esta heurística consiste em trocar os agentes que desempenham tarefas por outros
dentro da solução, assim explorando a vizinhança. Essa troca é realizada até encontrar a
melhor solução.

### First Improvement
A heurística Primeira Melhora trabalha de forma similar a Best Improvement,
porém as iterações são interrompidas na primeira melhora da solução gerada.

## Busca Local
A busca local utilizada para o problema, foi o método V ariable
Neighborhood Descent (VND). Esta busca local permite sair de um de um ótimo local
de uma vizinha e ir para outra. Para a construção da busca, foi utilizada os dois métodos de refinamento Melhor troca e Primeira Melhor Troca. Uma estrutura de vizinhança é
utilizada até que não haja melhoras, então é chamada outra na mesma solução. Logo é
possível buscar vizinhanças cada vez mais distantes variando a função objetivo e escapando
de ótimos locais.

## Meta-Heurística 
A meta-heurística utilizada foi a Iterated Local Search (ILS). O método foi desenvolvido a partir da aplicação do VND, em seguida uma pertubação na solução para que
haja uma variação e novamente aplicado o VND. Este procedimento acontece **N** iterações
passadas por parâmetro.
## Perturbação

A Perturbação criada para variar a solução foi escolher de forma aleatória uma
tarefa da solução e trocar se possível, o agente que desempenha esta por um outro agente
que possui um menor custo.
Assim podendo variar a solução e ainda de forma inicial, diminuir a função objetivo
da solução.


# Desenvolvimento

Projeto foi desenvolvido na linguagem C.


projeto ainda em desenvolvimento em busca de melhorias. 
