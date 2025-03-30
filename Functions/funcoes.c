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

        if (ficheiro == NULL) { // Se o ficheiro não existir
            
            printf("Erro ao abrir o ficheiro, ficheiro inexistente.\n");
            return NULL;
        }

        Antena* lista = NULL; // Lista vazia no inicio
        char linha[256]; // Tamanho maximo da linha, em caso de ser pretendido aumentar
        int y = 0; // Coordenada y de começo

        // Ler o ficheiro linha a linha
        while (fgets(linha, sizeof(linha), ficheiro)) { // fgets le cada linha do ficheiro e armazena na variável linha e o sizeof delimita o tamanho da linha que pode ser lido
            
            int x = 0; // Após mudar de linha x volta a 0, esta linha tem de ficar aqui dentro caso contrário a função não funciona

            // Percorrer cada caracter da linha
            while (linha[x] != '\0' && linha[x] != '\n') { // Enquanto não chegar ao fim da linha ou não encontrar o \n vai ignorar os pontos e focar apenas nas antenas
                
                if (linha[x] != '.') { // Se não for um ponto

                    Antena* novaAntena = criarAntena(x, y, linha[x]); // Cria uma nova antena

                    if (novaAntena != NULL) {
                        novaAntena->prox = lista; // Adiciona no início da lista ligada
                        lista = novaAntena;
                    }
                }
                x++;
            }
            y++; // Incrementa a coordenada Y (próxima linha)
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
    void removerAntena(Antena** lista, const char* caminhoFicheiro, int x, int y) { // ** porque a lista já é um apontador para a lista ligada

        if (*lista == NULL) { // Se a lista estiver vazia, imprime uma mensagem de erro
            printf("Lista vazia. Nenhuma antena para remover.\n");
            return;
        }

        Antena* atual = *lista; // Apontador onde percorre a lista indicando a antena atual
        Antena* anterior = NULL;

        // Percorre a lista para encontrar a antena com as coordenadas (x, y) introduzidas pelo utilizador
        while (atual != NULL && (atual->x != x || atual->y != y)) { 
            anterior = atual; 
            atual = atual->prox; 
        }

        // Se encontrou a antena, remove-a da lista ligada
        if (atual != NULL) {

            if (anterior == NULL) {
                *lista = atual->prox; // Remover do início da lista
            } 
            
            else {
                anterior->prox = atual->prox; // Remover do meio ou fim
            }
            free(atual); // Liberta a memória da antena removida
        } 
        else {
            printf("Antena não encontrada na lista ligada.\n");
            return;
        }
    }
#pragma endregion



/**
 * @brief Função de listar as antenas
 * @param lista lista ligada de antenas
 */
#pragma region Listar Antenas
void listarAntenas(Antena* lista) {

    if (lista == NULL) { // Se a lista estiver vazia, mostra a mensagem de erro

        printf("Nenhuma antena encontrada na lista.\n");
        return;
    }
    
    printf("-------------|Antenas|------------\n"); // Se a lista não estiver vazia, imprime a lista de antenas
    printf("Posicao       |    Frequencia\n");
    printf("--------------|-------------------\n");
    while (lista != NULL) {

        printf("(%d, %d)        |      %C \n", lista->x, lista->y, lista->frequencia);
        lista = lista->prox;
    }
}
#pragma endregion

/**
 * a@brief Função de adicionar o nefasto à lista ligada
 * a@param x coordenada x (colunas)
 * a@param y coordenada y (linhas)
 * a@return Nefasto* apontador para a nova estrutura Nefasto
 
#pragma region Adicionar Nefasto
Nefasto* adicionarNefasto(int x, int y) {

    Nefasto* novo = (Nefasto*)malloc(sizeof(Nefasto)); // Aloca memória para o novo nefasto

    if (novo == NULL) { // Se a alocação falhar imprime a mensagem de erro
        printf("Erro a alocar a memória.\n");
        return NULL;
    }

    novo->x = x;
    novo->y = y;
    novo->prox = NULL; // O apontador começa vazio
    return novo;
}
#pragma endregion

/**
 * a@brief Função de deduzir/detetar o efeito nefasto
 * a@param mapa array que armazena o "mapa" (ficheiro dos dados)
 
#pragma region Deducao Nefasto
Nefasto* detetarNefasto(const char* caminhoFicheiro) {

    FILE* ficheiro = fopen(caminhoFicheiro, "r"); // Abre o ficheiro em modo leitura

    if (ficheiro == NULL) { // Se o ficheiro não existir
        printf("Erro ao abrir o ficheiro.\n");
        return NULL;
    }

    char mapa[100][100]; // Matriz para armazenar o mapa pode aumentar se desejado, e onde se vai analisar o efeito nefasto
    int linhas = 0, colunas = 0; // Contadores de linhas e colunas (x,y), para as coordenadas e começa no 0
    char linha[256]; // Tamanho máximo da linha

    while (fgets(linha, sizeof(linha), ficheiro)) { // fgets lê cada linha do ficheiro e armazena na variável linha
        colunas = strlen(linha) - 1; // Removendo o '\n', o fgets lê a linha toda se chegar ao fim da linha e não atingir o limite (256), então -1 para não contar o \n
        
        for (int x = 0; x < colunas; x++) { // enquanto x for menor que o número de colunas, vai percorrer a linha correspondente à coluna
            mapa[linhas][x] = linha[x];
        }
        linhas++; // Avança de linha
    }

    fclose(ficheiro); // Fecha o ficheiro

    Nefasto* listaNefastos = NULL; // Lista de nefastos começa vazia

    // Percorrer o mapa para encontrar efeitos nefastos
    for (int y = 0; y < linhas; y++) { // Percorre as linhas
        for (int x = 0; x < colunas; x++) { // Percorre as colunas
            if (mapa[y][x] != '.' && mapa[y][x] != '#') { // Se os caracteres do "mapa" forem diferentes de "." e "#"
                // Verificar se há efeito nefasto na horizontal
                for (int dx = x + 3; dx < colunas; dx += 3) { // dx procura um efeito nefasto na horizontal (colunas)
                    if (mapa[y][dx] == mapa[y][x]) { // Se os caracteres forem iguais (mesma frequência)
                        int meioX = (x + dx) / 2; // Calcula a posição do meio entre as antenas (x e dx)
                        if (mapa[y][meioX] == '.') { // Se for um espaço vazio, ocorre o nefasto
                            mapa[y][meioX] = '#'; // Marca o espaço com #
                            Nefasto* novo = adicionarNefasto(meioX, y); // Adiciona o nefasto à lista
                            novo->prox = listaNefastos;
                            listaNefastos = novo;
                        }
                    }
                }

                // Verificar se há efeito nefasto na vertical
                for (int dy = y + 3; dy < linhas; dy += 3) {
                    if (mapa[dy][x] == mapa[y][x]) { // Frequências iguais
                        int meioY = (y + dy) / 2;
                        if (mapa[meioY][x] == '.') { // Se for um espaço vazio, ocorre o nefasto
                            mapa[meioY][x] = '#';
                            Nefasto* novo = adicionarNefasto(x, meioY); // Adiciona o nefasto à lista
                            novo->prox = listaNefastos;
                            listaNefastos = novo;
                        }
                    }
                }
            }
        }
    }

    // Escrever de volta no ficheiro com os nefastos detetados
    ficheiro = fopen(caminhoFicheiro, "w"); // Abre o ficheiro em modo escrita

    if (ficheiro == NULL) {
        printf("Erro ao abrir o ficheiro para escrita.\n");
        return listaNefastos;
    }

    for (int y = 0; y < linhas; y++) { // Percorre as linhas
        for (int x = 0; x < colunas; x++) { // Percorre as colunas
            fputc(mapa[y][x], ficheiro); // Escreve cada caracter no ficheiro
        }
        fputc('\n', ficheiro); // Escreve o fim de linha no ficheiro
    }

    fclose(ficheiro); // Fecha o ficheiro

    return listaNefastos; // Retorna a lista de nefastos
}
#pragma endregion

/**
 * a@brief Função de listar as antenas + nefasto
 * a@param lista lista ligada de antenas
 * a@param listaNefastos lista ligada de nefastos
 
#pragma region Listar Antenas Nefasto
void listarAntenasNef(Antena* lista, Nefasto* listaNefastos){

    if (lista && listaNefastos != NULL) {
        printf("-------------------| Antenas |-------------------\n");
        printf("Posicao       |    Frequencia    |    Nefasto    \n");
        printf("--------------|------------------|---------------\n");
        while (lista && listaNefastos != NULL) {
            printf("(%d, %d)        |      %C        |     (%d, %d)    \n", lista->x, lista->y, lista->frequencia, listaNefastos->x, listaNefastos->y);
            lista = lista->prox;
            listaNefastos = listaNefastos->prox;
        }
    } else {
        printf("Nenhuma antena encontrada.\n");
    }
}
#pragma endregion
*/