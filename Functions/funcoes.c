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

        // Intrução dos dados
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

        Antena* lista = NULL; // Lista vazia no inicio
        char c; // Caracter atual
        int y = 0; // Começa no 0
        int x = 0; // Começa no 0

        // Ler o ficheiro caracter a caracter
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
 * @brief Função de gcarregar grafos do ficheiro
 * @param lista lista ligada de antenas
 * @param listaArestas lista ligada de arestas
 * @param caminhoFicheiro caminho do ficheiro (mantém-se sempre o mesmo)
 */
#pragma region Carregar Grafos do Ficheiro

    GR* carregarGrafos(const char* caminhoFicheiro) {

        FILE* ficheiro = fopen(caminhoFicheiro, "r");

        GR* grafo = (GR*) malloc(sizeof(GR));

        grafo->lista = NULL; // Lista vazia no inicio
        grafo->listaArestas = NULL;

        if (ficheiro == NULL) { // Se não conseguiu abrir o ficheiro
            
            return NULL; 
        
        }

        int x = 0;
        int y = 0;
        char c;

        while((c = fgetc(ficheiro)) != EOF) {
            
            if(c == '\n' || c == '\0'){

                y++; // Muda de linha
                x = 0; // Reinicia a coluna

            }

            if(c == 'A' || c == 'O') { // Se o caracter for A ou O

                Antena* novaAntena = criarAntena(x, (y+1), c); // Cria nova antena

                if(novaAntena == NULL) { // Se a nova antena estiver vazia

                    return NULL;// FALSE
                    
                }

                else { // Se não estiver
                    
                    novaAntena->prox = grafo->lista; // Atualiza os dados da nova antena para a proxima
                    grafo->lista = novaAntena; // Atualiza a lista ligada com a nova antena

                }

            }

            x++; // Proxima coluna (carcater a caracter)
            
        }

        fclose(ficheiro); // Fecha o ficheiro
        return grafo; // Retorna o grafo
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
             (atual); // Liberta a memória da antena removida
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

    
}
#pragma endregion





/**
 * @brief Função de criar arestas
 * @param grafo grafo
 * @param lista lista ligada de arestas
 */
#pragma region Criar Aresta

    Aresta* criarAresta(GR* grafo) { // Cria nova aresta

        Antena* antenaA = grafo->lista; // Apontador para a lista de antenas

        while(antenaA != NULL){

            Antena* antenaB = antenaA->prox; 

            while(antenaB != NULL){

                if(antenaA->frequencia == antenaB->frequencia) { // Se as frequências forem iguais

                    Aresta* novaAresta = (Aresta*) malloc(sizeof(Aresta)); // Aloca memória para a nova aresta

                    novaAresta->origem = antenaA; // Apontador para a origem da aresta (vértice de origem)
                    novaAresta->destino = antenaB; // Apontador para o destino da aresta (vértice de destino)
                    novaAresta->prox = grafo->listaArestas; // Liga a lista temporária à lista principal
                    grafo->listaArestas = novaAresta; // Atualiza a lista principal

                    return novaAresta;

                }

                antenaB = antenaB->prox;

            }

            antenaA = antenaA->prox;

        }

    }

#pragma endregion