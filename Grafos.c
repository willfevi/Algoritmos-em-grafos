#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <math.h>

typedef struct Aresta {
    int destino;
    int peso;
    struct Aresta* proximo;
} Aresta;

typedef struct No {
    int id;
    Aresta* cabeca;
} No;

typedef struct Grafo {
    int numNos;
    No* nos;
    int direcional;
    int ponderado;
} Grafo;

Grafo* criarGrafo(int numNos, int direcional, int ponderado) {
    Grafo* grafo = (Grafo*) malloc(sizeof(Grafo));
    if (!grafo) return NULL;
    grafo->numNos = numNos;
    grafo->direcional = direcional;
    grafo->ponderado = ponderado;
    grafo->nos = (No*) malloc(numNos * sizeof(No));
    if (!grafo->nos) {
        free(grafo);
        return NULL;
    }
    for (int i = 0; i < numNos; i++) {
        grafo->nos[i].id = i;
        grafo->nos[i].cabeca = NULL;
    }
    return grafo;
}

void adicionarAresta(Grafo* grafo, int origem, int destino, int peso) {
    Aresta* novaAresta = (Aresta*) malloc(sizeof(Aresta));
    if (!novaAresta) return;
    novaAresta->destino = destino;
    novaAresta->peso = peso;
    novaAresta->proximo = grafo->nos[origem].cabeca;
    grafo->nos[origem].cabeca = novaAresta;

    if (!grafo->direcional) {
        Aresta* arestaReversa = (Aresta*) malloc(sizeof(Aresta));
        if (!arestaReversa) return;
        arestaReversa->destino = origem;
        arestaReversa->peso = peso;
        arestaReversa->proximo = grafo->nos[destino].cabeca;
        grafo->nos[destino].cabeca = arestaReversa;
    }
}

void imprimirGrafo(Grafo* grafo) {
    for (int i = 0; i < grafo->numNos; i++) {
        Aresta* aresta = grafo->nos[i].cabeca;
        printf("No %d:", i);
        while (aresta != NULL) {
            printf(" -> %d(%d)", aresta->destino, aresta->peso);
            aresta = aresta->proximo;
        }
        printf("\n");
    }
}

void liberarGrafo(Grafo* grafo) {
    if (!grafo) return;
    for (int i = 0; i < grafo->numNos; i++) {
        Aresta* aresta = grafo->nos[i].cabeca;
        while (aresta) {
            Aresta* tmp = aresta;
            aresta = aresta->proximo;
            free(tmp);
        }
    }
    free(grafo->nos);
    free(grafo);
}

void ordenacaoTopologicaUtil(int v, bool visitado[], int pilha[], int *indicePilha, Grafo *grafo) {
    visitado[v] = true;
    Aresta* tmp = grafo->nos[v].cabeca;
    while (tmp != NULL) {
        if (!visitado[tmp->destino])
            ordenacaoTopologicaUtil(tmp->destino, visitado, pilha, indicePilha, grafo);
        tmp = tmp->proximo;
    }
    pilha[(*indicePilha)++] = v;
}

void ordenacaoTopologica(Grafo *grafo) {
    bool *visitado = (bool *) malloc(grafo->numNos * sizeof(bool));
    int *pilha = (int *) malloc(grafo->numNos * sizeof(int));
    int indicePilha = 0;
    for (int i = 0; i < grafo->numNos; i++)
        visitado[i] = false;
    for (int i = 0; i < grafo->numNos; i++)
        if (!visitado[i])
            ordenacaoTopologicaUtil(i, visitado, pilha, &indicePilha, grafo);
    printf("Ordenacao Topologica do Grafo:\n");
    while (indicePilha)
        printf("%d -> ", pilha[--indicePilha]);
    printf("Fim\n");
    free(visitado);
    free(pilha);
}

void DFSUtil(int v, bool visitado[], Grafo *grafo) {
    visitado[v] = true;
    printf("%d ", v);
    Aresta* tmp = grafo->nos[v].cabeca;
    while (tmp != NULL) {
        if (!visitado[tmp->destino])
            DFSUtil(tmp->destino, visitado, grafo);
        tmp = tmp->proximo;
    }
}

void imprimirComponentesFC(Grafo *grafo) {
    bool *visitado = (bool *) malloc(grafo->numNos * sizeof(bool));
    for (int i = 0; i < grafo->numNos; i++)
        visitado[i] = false;
    printf("Componentes Fortemente Conectados:\n");
    for (int i = 0; i < grafo->numNos; i++) {
        if (!visitado[i]) {
            DFSUtil(i, visitado, grafo);
            printf("\n");
        }
    }
    free(visitado);
}

int minDistancia(int dist[], bool sptSet[], int numNos) {
    int min = INT_MAX, min_index;
    for (int v = 0; v < numNos; v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;
    return min_index;
}

void dijkstra(Grafo *grafo, int src) {
    int numNos = grafo->numNos;
    int dist[numNos];
    bool sptSet[numNos];

    for (int i = 0; i < numNos; i++)
        dist[i] = INT_MAX, sptSet[i] = false;

    dist[src] = 0;

    for (int count = 0; count < numNos - 1; count++) {
        int u = minDistancia(dist, sptSet, numNos);
        sptSet[u] = true;

        Aresta* tmp = grafo->nos[u].cabeca;
        while (tmp != NULL) {
            int v = tmp->destino;
            if (!sptSet[v] && dist[u] != INT_MAX && dist[u] + tmp->peso < dist[v])
                dist[v] = dist[u] + tmp->peso;
            tmp = tmp->proximo;
        }
    }

    printf("Distancias do no %d para todos os outros nos:\n", src);
    for (int i = 0; i < numNos; i++)
        if (dist[i] == INT_MAX)
            printf("No %d: sem caminho\n", i);
        else
            printf("No %d: %d\n", i, dist[i]);
}

int heuristica(int atual, int destino) {
    return abs(destino - atual);
}

void AStar(Grafo *grafo, int start, int goal) {
    int numNos = grafo->numNos;
    int dist[numNos];
    bool closedSet[numNos];
    bool openSet[numNos];

    for (int i = 0; i < numNos; i++) {
        dist[i] = INT_MAX;
        closedSet[i] = false;
        openSet[i] = false;
    }

    dist[start] = 0;
    openSet[start] = true;

    while (true) {
        int current = -1;
        for (int i = 0; i < numNos; i++)
            if (openSet[i] && (current == -1 || dist[i] + heuristica(i, goal) < dist[current] + heuristica(current, goal)))
                current = i;

        if (current == -1) {
            printf("Nao ha mais nos abertos, A* terminou sem encontrar o caminho.\n");
            return;
        }

        if (current == goal) {
            printf("Caminho encontrado, distancia total: %d\n", dist[current]);
            return;
        }

        openSet[current] = false;
        closedSet[current] = true;

        Aresta* tmp = grafo->nos[current].cabeca;
        while (tmp != NULL) {
            int v = tmp->destino;
            if (!closedSet[v]) {
                int temp_g = dist[current] + tmp->peso;
                if (!openSet[v] || temp_g < dist[v]) {
                    dist[v] = temp_g;
                    openSet[v] = true;
                }
            }
            tmp = tmp->proximo;
        }
    }
}

int main() {
    int numNos, direcional, ponderado;
    printf("Digite o número de nós do grafo: ");
    scanf("%d", &numNos);
    if (numNos <= 0) {
        printf("Número de nós deve ser maior que zero.\n");
        return 1;
    }

    printf("O grafo é direcional? (1-Sim, 0-Não): ");
    scanf("%d", &direcional);
    printf("O grafo é ponderado? (1-Sim, 0-Não): ");
    scanf("%d", &ponderado);

    Grafo* grafo = criarGrafo(numNos, direcional, ponderado);
    if (!grafo) {
        printf("Erro ao alocar memória para o grafo.\n");
        return 1;
    }

    int escolha, origem, destino, peso;
    do {
        printf("\nDigite 1 para adicionar aresta, 2 para executar algoritmos, 0 para sair: ");
        scanf("%d", &escolha);
        switch (escolha) {
            case 1:
                printf("Digite o nó de origem, destino e peso (se ponderado): ");
                scanf("%d %d %d", &origem, &destino, &peso);
                if (origem >= 0 && origem < numNos && destino >= 0 && destino < numNos) {
                    adicionarAresta(grafo, origem, destino, grafo->ponderado ? peso : 0);
                } else {
                    printf("Origem ou destino fora do intervalo válido. Tente novamente.\n");
                }
                break;
            case 2:
                if (grafo->direcional && !grafo->ponderado) {
                    ordenacaoTopologica(grafo);
                    imprimirComponentesFC(grafo);
                } else if (!grafo->direcional && grafo->ponderado) {
                    printf("Escolha o método (1-Dijkstra, 2-A*): ");
                    scanf("%d", &escolha);
                    printf("Digite o nó de origem: ");
                    scanf("%d", &origem);
                    if (origem < 0 || origem >= numNos) {
                        printf("Origem inválida.\n");
                        break;
                    }
                    if (escolha == 1) {
                        dijkstra(grafo, origem);
                    } else {
                        printf("Digite o nó de destino: ");
                        scanf("%d", &destino);
                        if (destino < 0 || destino >= numNos) {
                            printf("Destino inválido.\n");
                        } else {
                            AStar(grafo, origem, destino);
                        }
                    }
                } else {
                    printf("Configuração de grafo não suportada para algoritmos.\n");
                }
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
                break;
        }
    } while (escolha != 0);

    liberarGrafo(grafo);
    return 0;
}
