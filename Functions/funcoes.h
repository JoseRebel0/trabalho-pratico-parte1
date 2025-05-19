/**
 * @file funcoes.h
 * @author José Rebelo
 * @brief Ficheiro com as definições das funções do menu
*/

#include "../Data/dados.h"


#pragma region Funções do menu
/**
 * @brief Função de criar novas antenas
 */
Antena* criarAntena(int x, int y, char frequencia);


/**
 * @brief Função de remover as antenas do ficheiro e da lista
 */
Antena* removerAntena(Antena* lista, int x, int y);



/**
 * @brief Função de carregar as antenas do ficheiro
 */
Antena* carregarAntenasDoFicheiro(const char* caminhoFicheiro);

/**
 * @brief Função de listar as antenas
 */
 char* listarAntenas(Antena* lista, Nefasto* listaNefasto);

#pragma endregion

/**
 * @brief Função de dedução de efeito nefasto
 */
Nefasto* deduzirNefasto(Nefasto* listaNefasto, Antena* lista); 

/**
 * @brief Função de criar grafos
 */
GR* criarGrafo(Antena* lista);

/**
 * @brief Função de criar arestas
 */
Aresta* criarAresta(Antena* origem, Antena* destino);

/**
 * @brief Função de listar as arestas
 */
char* listarArestas(GR* grafo);

/**
 * @brief Função de procura em profundidade
*/
GR* procuraProfundo(GR* grafo, int x, int y);