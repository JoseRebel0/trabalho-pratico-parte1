/**
 * @file funcoes.c
 * @author José Rebelo
 * @brief Ficheiro com as funções do menu
*/

/**
 * @brief Inclusão das bibliotecas necessárias
 */
#include "funcoes.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


/**
 * @brief Função de criar novas antenas
 * @param x posição x
 * @param y posição y
 * @param frequencia frequência (A ou O)
 * @return Antena* apontador para a nova antena
 */
#pragma region Criar Antena
    Antena* criarAntena(int x, int y, char frequencia){

        Antena* novaAntena = (Antena*) malloc(sizeof(Antena)); // Aloca memória para a nova antena

        // Introdução dos dados
        novaAntena->x = x;
        novaAntena->y = y;
        novaAntena->frequencia = frequencia;

        novaAntena->prox = NULL;

        return novaAntena;
    }
#pragma endregion



/**
 * @brief Função de carregar as antenas do ficheiro
 * @param caminhoFicheiro Caminho do ficheiro
 * @param lista Lista ligada
 * @param y Coordenada y (linhas)
 * @param x Coordenada x (colunas)
 */
#pragma region Carregar Antenas do Ficheiro

    Antena* carregarAntenasDoFicheiro(const char* caminhoFicheiro) {

        /**
         * @brief Abrir o ficheiro em modo leitura ("r -> read")
         */
        FILE* ficheiro = fopen(caminhoFicheiro, "r");

        Antena* lista = NULL;
        char c; // Caracter atual
        int y = 0; 
        int x = 0; 

        while ((c = fgetc(ficheiro)) != EOF) { // lê a linha caracter a caracter até chegar ao fim do ficheiro
            
            if(c == '\n' || c == '\0'){

                y++; // Muda de linha
                x = 0; // Reinicia a coluna

            }

            if(c == 'A' || c == 'O') { // Se o caracter for A ou O

                Antena* novaAntena = criarAntena(x, (y+1), c); // Cria nova antena

                novaAntena->prox = lista; // Atualiza os dados da nova antena para a proxima
                lista = novaAntena; // Atualiza a lista ligada com a nova antena

            }

            x++; // Proxima coluna (carcater a caracter)
            
        }

        fclose(ficheiro);
        return lista;
    }
#pragma endregion




/**
 * @brief Função de remover as antenas da lista
 * @param x posição x da antena no ficheiro
 * @param y posição y da antena no ficheiro
 */
#pragma region Remover Antena

    Antena* removerAntena(Antena* lista, int x, int y) { 

        Antena* atual = lista; // Apontador onde percorre a lista indicando a antena atual
        Antena* anterior = NULL;

        // Percorre a lista para encontrar a antena com as coordenadas (x, y) introduzidas pelo utilizador
        while (atual != NULL && (atual->x != x || atual->y != y)) { 

            anterior = atual; 
            atual = atual->prox; 
        }

        // Se encontrou a antena
        if (atual != NULL) {

            if (anterior == NULL) {
                lista = atual->prox; // Remover do início da lista
            } 
            
            // Se a antena anterior não for vazia, então só pode estar no meio ou no fim
            else {
                anterior->prox = atual->prox;
            }
            free(atual); // Liberta a memória da antena removida
        } 
        return lista;
    }
#pragma endregion




/**
 * @brief Função de dedução de efeito nefasto
 * @param lista lista ligada de antenas
 * @param listaNefasto lista ligada de efeitos nefastos
 * @param x posição x da antena no ficheiro
 * @param y posição y da antena no ficheiro
 */
#pragma region Deduzir Efeito Nefasto

    Nefasto* deduzirNefasto(Nefasto* listaNefasto,Antena* lista) {

        for(Antena* antenaA = lista; antenaA != NULL; antenaA = antenaA->prox) { // Percorre a lista para a primeira antena

            for(Antena* antenaB = antenaA->prox; antenaB != NULL; antenaB = antenaB->prox) { // Percorre para a segunda antena

                if(antenaA->x == antenaB->x && antenaA->frequencia == antenaB->frequencia) { // Se a coluna e a frequência forem iguais
                    
                    Nefasto* novoNefasto = (Nefasto*) malloc(sizeof(Nefasto)); // Aloca memória para o novo efeito nefasto

                    novoNefasto->x = antenaA->x; // Pode ser tanto de uma como de outra os x são iguais
                    novoNefasto->y = ((antenaA->y+antenaB->y)/2); // A média das duas antenas (A e B) para a coordenada y do nefasto
                    novoNefasto->frequencia = antenaB->frequencia;// Pode ser tanto de uma como de outra as frequências são iguais
                    novoNefasto->prox = listaNefasto;
                    listaNefasto = novoNefasto;

                }

            }

        }
    
        return listaNefasto;

    }

#pragma endregion




/**
 * @brief Função de listar as antenas
 * @param lista lista ligada de antenas
 * @param listaNefasto lista ligada de efeitos nefastos
 */
#pragma region Listar Antenas
char* listarAntenas(Antena* lista, Nefasto* listaNefasto) { // Função de listar as antenas
    
    printf("-------------|Antenas|------------\n"); // Imprime a lista de antenas
    printf("Posicao       |    Frequencia     \n");
    printf("--------------|-------------------\n");
    while (lista != NULL) { // Enquanto as listas não forem vazias

        printf("(%d, %d)        |      %C \n", lista->x, lista->y, lista->frequencia);
        lista = lista->prox;
    }

    printf("-----------|Nefasto|------------\n");
    printf("Posicao       |    Frequencia     \n");
    printf("--------------|-------------------\n");
    while (listaNefasto != NULL) { // Enquanto as listas não forem vazias

        printf("(%d, %d)        |      %C \n", listaNefasto->x, listaNefasto->y, listaNefasto->frequencia);
        listaNefasto = listaNefasto->prox;
    }

    return "";
    
}
#pragma endregion



/**
 * @brief Função que cria uma aresta entre duas antenas
 * @param origem Antena de origem
 * @param destino Antena de destino
 * @return Aresta* Nova aresta criada
 */
#pragma region Criar Aresta

Aresta* criarAresta(Antena* origem, Antena* destino) {

    Aresta* novaAresta = (Aresta*) malloc(sizeof(Aresta));

    novaAresta->origem = origem;
    novaAresta->destino = destino;
    novaAresta->prox = NULL;
    novaAresta->distancia = abs(origem->x - destino->x) + abs(origem->y - destino->y); // Cálculo da distância entre as antenas (peso da aresta)

    return novaAresta;
}

#pragma endregion


/**
 * @brief Função que cria um grafo com base nas antenas
 * @param lista Lista ligada de antenas
 * @param listaArestas Lista ligada de arestas
 * @return GR* Grafo criado
 */
GR* criarGrafo(Antena* lista) {

    GR* grafo = (GR*) malloc(sizeof(GR));

    grafo->antenas = lista; // Carrega as antenas da lista de antenas
    
    grafo->listaArestas = NULL;

    for (Antena* a1 = lista; a1 != NULL; a1 = a1->prox) { // Origem

        for (Antena* a2 = a1->prox; a2 != NULL; a2 = a2->prox) { // Destino

            
            if (a1->frequencia == a2->frequencia) {

                // Criar aresta a1 -> a2
                Aresta* novaAresta = criarAresta(a1, a2);
                novaAresta->prox = grafo->listaArestas;
                grafo->listaArestas = novaAresta;

                // Criar aresta a2 -> a1
                Aresta* novaAresta2 = criarAresta(a2, a1);
                novaAresta2->prox = grafo->listaArestas;
                grafo->listaArestas = novaAresta2;
            }
        }
    }

    return grafo;
}



/**
 * @brief Função de listar todas as arestas do grafo
 * @param grafo Ponteiro para o grafo
 * @param atual Aresta atual
 */
char* listarArestas(GR* grafo) {

    Aresta* atual = grafo->listaArestas;

    printf("-------------| Arestas do Grafo |------------\n");
    printf("Origem       ->  Destino     | Freq | Distancia\n");
    printf("----------------------------------------------\n");

    while (atual != NULL) {

        printf("(%d, %d) -> (%d, %d)   |   %c   |   %.2f\n",
               atual->origem->x, atual->origem->y,
               atual->destino->x, atual->destino->y,
               atual->origem->frequencia,  
               atual->distancia);

        atual = atual->prox;
    }

    return "";

}
