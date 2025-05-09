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

#define X_Y 1

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
Aresta* listaArestasA = NULL; // Lista de arestas que ligam ao vértice A
Aresta* listaArestasO = NULL; // Lista de arestas que ligam ao vértice O

int main() {

    Antena* novaAntena = NULL; // Começa vazia
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


// VAI PARA TESTES  ||
//                  V

/**
 * @brief Deduzir efeito nefasto
 * @details Esta função tem como objetivo deduzir o efeito nefasto da antena
 * @param lista lista ligada
 * @param listaNefasto lista ligada de efeitos nefastos
 */
#pragma region Deduzir Efeito Nefasto

    listaNefasto = deduzirNefasto(listaNefasto, lista); // Deduz o efeito nefasto da antena

#pragma endregion



//Adicionar a função de carregar os grafos




/**
 * @brief Criar arestas
 * @details Esta função tem como objetivo criar as arestas do grafo
 * @param lista lista ligada de antenas
 * @param listaArestasA lista ligada de arestas
 */
#pragma region Criar Aresta

    // Adicionar a função de criar arestas
    

#pragma endregion




/**
 * @brief Listar antenas
 * @details Esta função tem como objetivo listar as antenas registadas na lista ligada
 * @param lista lista ligada
 */
#pragma region Listar Antenas

    listarAntenas(lista, listaNefasto); // A função aplica-se na variável da lista ligada
       
#pragma endregion



}
