/**
 * @file main.c
 * @author José Rebelo
 * @brief Ficheiro principal
*/

/**
 * @brief Inclusão das bibliotecas necessárias
 */
#pragma region Inclusão de Bibliotecas

#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#pragma endregion

/**
 * @brief Declaração das listas ligadas
 * @details As antenas são de claradas vazias (NULL) porque começam vazias para serem preenchidas
 * @param lista lista ligada de antenas
 * @param listaNefasto lista ligada de efeitos nefastos
 * @param listaArestas lista ligada de arestas
 */
Antena* lista = NULL;
Nefasto* listaNefasto = NULL;
Aresta* listaArestas = NULL;


int main() {

    Antena* novaAntena = NULL; // Começa vazia
    GR* novoGrafo = NULL; // Começa vazio
    char frequencia = 'A';
    int x = X_Y, y = X_Y;

    const char* caminhoFicheiro = "./Text/dados.txt"; // Caminho para o ficheiro dos dados

/**
 * @brief Criar antena
 * @details Esta função tem como objetivo criar uma nova antena à lista ligada
 * @param x posição x (colunas)
 * @param y posição y (linhas)
 * @param frequencia frequência (A ou O)
 */
#pragma region Criar Antena

    novaAntena = criarAntena(x, y, frequencia); // Cria nova antena

    if (novaAntena != NULL) { // Se a nova antena não estiver vazia

        novaAntena->prox = lista; // Atualiza os dados da nova antena para a proxima
        lista = novaAntena; // Atualiza a lista ligada com a nova antena

    } else { // Se a nova antena estiver vazia

        return false;
    }

    listarAntenas(lista, listaNefasto); // A função aplica-se na variável da lista ligada

#pragma endregion 

/**
 * @brief Guardar dados das antenas
 * @details Esta função tem como objetivo guardar os dados das antenas do ficheiro na lista ligada
 * @param caminhoFicheiro caminho do ficheiro (mantém-se sempre o mesmo)
 * @param lista lista ligada
 * @param temp variável temporária para guardar a lista ligada
 */
#pragma region Guardar Dados Das Antenas

    Antena* listaFicheiro = carregarAntenasDoFicheiro(caminhoFicheiro); // Carrega as antenas do ficheiro

    if(caminhoFicheiro == NULL) { // Se não conseguiu abrir o ficheiro

        return false; // FALSE
    }

    // Agora junta as duas listas
    if (listaFicheiro != NULL) {

        Antena* temp = listaFicheiro; // Lista temporária que assume os valores da lista principal completa

        while (temp->prox != NULL) {

            temp = temp->prox; // Vai percorrer a lista até ao fim
        }
        temp->prox = lista;  // Liga a lista temporária à lista principal

        lista = listaFicheiro; // Atualiza a lista principal
    }

    else { // Se a lista estiver vazia

        return false; // FALSE
    }

    listarAntenas(lista, listaNefasto); // A função aplica-se na variável da lista ligada
            
#pragma endregion


/**
 * @brief Carregar grafo do ficheiro
 * @details Esta função tem como objetivo carregar o grafo do ficheiro
 * @param lista lista ligada de antenas
 */
#pragma region Criar Grafo

    novoGrafo = criarGrafo(lista);

    if (novoGrafo == NULL) { // Se o grafo estiver vazio

        return false; // FALSE
    }

    listarArestas(novoGrafo);

    procuraProfundo(novoGrafo, 10, 10);

#pragma endregion


/**
 * @brief Remover antena
 * @details Esta função tem como objetivo remover uma antena da lista ligada
 * @param caminhoFicheiro caminho do ficheiro (mantém-se sempre o mesmo)
 * @param x posição x (colunas)
 * @param y posição y (linhas)
 */
#pragma region Remover Antena

    removerAntena(lista, x, y); 

    listarAntenas(lista, listaNefasto); // A função aplica-se na variável da lista ligada
    
#pragma endregion


/**
 * @brief Deduzir efeito nefasto
 * @details Esta função tem como objetivo deduzir o efeito nefasto da antena
 * @param lista lista ligada
 * @param listaNefasto lista ligada de efeitos nefastos
 */
#pragma region Deduzir Efeito Nefasto

    listaNefasto = deduzirNefasto(listaNefasto, lista); // Deduz o efeito nefasto da antena

#pragma endregion


/**
 * @brief Carregar grafo do ficheiro
 * @details Esta função tem como objetivo carregar o grafo do ficheiro
 * @param lista lista ligada de antenas
 */
#pragma region Criar Grafo

    novoGrafo = criarGrafo(lista);

    if (novoGrafo == NULL) { // Se o grafo estiver vazio

        return false; // FALSE
    }

#pragma endregion



/**
 * @brief Listar antenas
 * @details Esta função tem como objetivo listar as antenas registadas na lista ligada
 * @param lista lista ligada
 */
#pragma region Listar Antenas

    listarAntenas(lista, listaNefasto);
       
#pragma endregion


/**
 * @brief Listar arestas
 * @details Esta função tem como objetivo listar as arestas do grafo
 * @param grafo grafo
 */
#pragma region Listar Arestas

    listarArestas(novoGrafo);

#pragma endregion



/**
 * @brief Procura em Profundidade
 * @details Esta função tem como objetivo fazer a listagem das adjacencias de cada antena (neste caso serão as antenas restantes)
 * @param listaArestas Lista de arestas
*/
#pragma region Procura em Profundidade

procuraProfundo(novoGrafo, 10, 10);

#pragma endregion

}
