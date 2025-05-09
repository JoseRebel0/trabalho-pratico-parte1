/**
 * @file menu.c
 * @author José Rebelo
 * @brief Ficheiro com as funções do menu
*/

/**
 * @brief Inclusão das bibliotecas necessárias
 */
#pragma region Inclusão de Bibliotecas

#include "menu.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#pragma endregion

Antena* lista = NULL; // Lista ligada vazia (é assim que começa)

void menu() {

    Antena* novaAntena = NULL; //Evita erros de lixo na memória
    char frequencia = 'A';
    int x = 1, y =1;
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

    if (novaAntena != NULL) {
        novaAntena->prox = lista; // Aponta para a próxima antena
        lista = novaAntena; // Atualiza a lista ligada com a nova antena
        printf("Antena criada com sucesso.\n"); // Só teste depois tira
    } 
        
    else {
        printf("Erro ao criar a antena.\n");
    }

    listarAntenas(lista); // A função aplica-se na variável da lista ligada

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

    // Agora junta as duas listas
    if (listaFicheiro != NULL) {

        Antena* temp = listaFicheiro; // Variável temporária para percorrer a lista carregada
        while (temp->prox != NULL) {

            temp = temp->prox; // Vai percorrer a lista até ao fim
        }
        temp->prox = lista;  // Liga a lista carregada à lista existente

        lista = listaFicheiro; // Atualiza a lista principal
    }

    printf("Antenas adicionadas com sucesso.\n"); // Só teste depois tira

    listarAntenas(lista); // A função aplica-se na variável da lista ligada
            
#pragma endregion

    /**
     * @brief Remover antena
     * @details Esta função tem como objetivo remover uma antena da lista ligada
     * @param caminhoFicheiro caminho do ficheiro (mantém-se sempre o mesmo)
     * @param x posição x (colunas)
     * @param y posição y (linhas)
     */
#pragma region Remover Antena      

    removerAntena(&lista, caminhoFicheiro, x, y); 

    printf("Antena removida com sucesso.\n"); // Só teste depois tira

    listarAntenas(lista); // A função aplica-se na variável da lista ligada
    
#pragma endregion

    /**
     * @brief Listar antenas
     * @details Esta função tem como objetivo listar as antenas registadas na lista ligada
     * @param lista lista ligada
     */
#pragma region Listar Antenas

    listarAntenas(lista); // A função aplica-se na variável da lista ligada
       
#pragma endregion

    /**
     * a@brief Detetar nefasto
     * a@details Esta função tem como objetivo detetar o efeito nefasto
     * a@param caminhoFicheiro caminho do ficheiro (mantém-se sempre o mesmo)
     
#pragma region Detetar Nefasto
    Nefasto* detetarNefasto(const char* caminhoFicheiro);
#pragma endregion

    /**
     * a@brief Listar antenas + nefasto
     * a@details Esta função tem como objetivo listar as antenas e o efeito nefasto
     * a@param lista lista ligada de antenas
     * a@param listaNefastos lista ligada de nefastos
     
#pragma region Listar Antenas + Nefasto
    Nefasto* listaNefastos = detetarNefasto(caminhoFicheiro); // Lista ligada de nefastos
    listarAntenasNef(lista, listaNefastos); // A função aplica-se na variável da lista ligada
#pragma endregion*/
}
