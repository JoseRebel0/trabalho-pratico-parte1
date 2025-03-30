/**
* @file dados.h
* @author Jos� Rebelo
* @brief Ficheiro com as estruturas das antenas e do nefasto
*/

/**
 *@brief Estrutura de dados das antenas
 */
typedef struct Antena {
    int x; //posi��o x
    int y; //posi��o y
    char frequencia; //frequ�ncia (A ou O)
    struct Antena* prox; //apontador para a pr�xima antena
} Antena;

/**
* @brief Estrutura de dados do efeito nefasto
*/
typedef struct Nefasto{
    int x; //posi��o x
    int y; //posi��o y
    struct Nefasto* prox; // apontador para o pr�ximo efeito
} Nefasto;