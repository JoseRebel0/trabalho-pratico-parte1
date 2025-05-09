/**
* @file dados.h
* @author José Rebelo
* @brief Ficheiro com as estruturas das antenas e do nefasto
*/

/**
 *@brief Estrutura de dados das antenas
 */
typedef struct Antena {
    int x; //posição x
    int y; //posição y
    char frequencia; //frequ�ncia (A ou O)
    struct Antena* prox; //apontador para a próxima antena
} Antena;

/**
* @brief Estrutura de dados do efeito nefasto
*/
typedef struct Nefasto{
    int x; //posição x
    int y; //posição y
    struct Nefasto* prox; // apontador para o próximo efeito
} Nefasto;