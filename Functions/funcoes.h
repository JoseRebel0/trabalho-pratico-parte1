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
void removerAntena(Antena** lista, const char* caminhoFicheiro, int x, int y);


/**
 * @brief Função de carregar as antenas do ficheiro
 */
Antena* carregarAntenasDoFicheiro(const char* caminhoFicheiro);



/**
 * a@brief Função de listar as antenas

void listarAntenas(Antena* lista);


/**
 * a@brief Função de adicionar nefasto

Nefasto* adicionarNefasto(int x, int y);

/**
* a@brief Função de dedução das localização

Nefasto* detetarNefasto(const char* caminhoFicheiro);

/**
 * a@brief Função de listar as antenas + nefasto

void listarAntenasNef(Antena* lista, Nefasto* listaNefastos);
*/
#pragma endregion