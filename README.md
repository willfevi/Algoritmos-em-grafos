# Projeto de Algoritmos em Grafos

Este projeto foi desenvolvido para a disciplina de Algoritmos em Grafos, ministrada pelo Professor Victor Padilha no CEFET - Nova Friburgo. O objetivo principal do projeto é implementar e manipular diferentes algoritmos de grafos para entender melhor seus usos e funcionalidades em um contexto computacional.

## Descrição

O programa implementa um sistema de gerenciamento de grafos que permite ao usuário criar grafos direcionais ou não direcionais, ponderados ou não ponderados. O usuário pode adicionar arestas, executar algoritmos de ordenação topológica, identificar componentes fortemente conectados, calcular caminhos mínimos usando Dijkstra e encontrar caminhos eficientes com o algoritmo A*.

### Funcionalidades

- **Criação de Grafos**: Permite criar grafos com número definido de nós, configuráveis como direcionais ou não direcionais, e ponderados ou não.
- **Adição de Arestas**: Adiciona arestas com ou sem peso entre os nós.
- **Ordenação Topológica**: Aplica a ordenação topológica em grafos direcionais.
- **Componentes Fortemente Conectados**: Identifica e lista componentes fortemente conectados em grafos direcionais.
- **Dijkstra**: Calcula o caminho mínimo de um nó de origem para todos os outros nós em grafos ponderados.
- **A***: Encontra o caminho mais eficiente usando uma função heurística em grafos ponderados.

## Como Executar

### Pré-requisitos

Para compilar e executar este projeto, você precisará de um compilador C compatível, como GCC, instalado em sua máquina. O programa foi desenvolvido e testado em ambiente Windows, mas também deve funcionar em outros sistemas operacionais que suportam o GCC.

### Contribuições
Contribuições são bem-vindas. Se você encontrar algum bug ou tiver sugestões de melhorias, por favor, abra uma issue ou envie um pull request.

### Compilação e execução

Abra o terminal ou prompt de comando e navegue até o diretório onde o arquivo de código fonte (`Grafos.c`) está localizado. Compile o código com o seguinte comando:

```bash
gcc Grafos.c -o Grafos.exe
./Grafos.exe
