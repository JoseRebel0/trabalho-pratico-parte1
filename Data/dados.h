/**
* @file dados.h
* @author José Rebelo
* @brief Ficheiro com as estruturas das antenas
*/

#include "stdbool.h"

#define X_Y 1

/**
 *@brief Estrutura de dados das antenas
 */
typedef struct Antena {

    int x; //posição x
    int y; //posição y
    char frequencia; //frequência (A ou O)
    struct Adjacencia* adjacencias; //apontador para a lista de adjacências
    bool visitada; //se a antena foi visitada ou não
    struct Antena* prox; //apontador para a próxima antena

} Antena;

/**
 *@brief Estrutura de dados dos efeitos nefastos
 */
typedef struct Nefasto {

    int x; //posição x
    int y; //posição y
    char frequencia; //frequência (A ou O)
    struct Nefasto* prox; //apontador para o próximo efeito nefasto

} Nefasto;

/**
 *@brief Estrutura de dados dos grafos
 */
typedef struct GR{

    struct Antena* antenas;
    struct Aresta* listaArestas;

} GR;

/**
 * @brief Estrutura de dados das adjacências
 */
typedef struct Adjacencia{

    int distancia; //distância entre as antenas

} Adjacencia;



/**
 * @brief Estrutura de dados das arestas
 */
typedef struct Aresta{

    struct Antena* origem;
    struct Antena* destino; 
    struct Aresta* prox;
    float distancia;

} Aresta;