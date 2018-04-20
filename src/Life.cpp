#include "Life.h"

/**
 * \brief construtor simple sem nenhum parâmetro
 */
Life::Life() {
    this->nLin = 0;
    this->nCol = 0;
}

/**
 * \brief construtor com alguns parametros
 * \param nLin, número de linhas do grid
 * \param nCol, número de colunos do grid
 */
Life::Life(int nLin, int nCol) {
    this->nLin = nLin;
    this->nCol = nCol;
}

/**
 * \brief método para setar o número de linhas
 * \param nLin, número de linhas
 */
void Life::setnLin(int nLin) {
    this->nLin = nLin;
}

/**
 * \brief método para setar o número de colunas
 * \param nCol, número de colunas do grid
 */
void Life::setnCol(int nCol) {
    this->nCol = nCol;
}

/**
 * \brief método para setar o caracter
 * \param caracter, caracter que será utilizado para identificar as células vivas no arquivo.
 */
void Life::setCaracter(char caracter) {
    this->caracter = caracter;
}

/**
 * \brief método para setar no objeto o grid
 * \param grid, seta o grid no objeto
 */
void Life::setGrid(bool **grid) {
    this->grid = grid;
}

/**
 * \brief método para recuperar o número de linhas do grid
 * \return retorna o número de linhas do grid
 */
int Life::getnLin() const {
    return this->nLin;
}

/**
 * \brief método para recuperar o número de colunas do grid
 * \return retorna o número de colunas do grid
 */
int Life::getnCol() const {
    return this->nCol;
}

/**
 * \brief método para recuperar o caracter
 * \return retorna o caracter
 */
char Life::getCaracter() const {
    return this->caracter;
}

/**
 * \brief método para recuperar o grid
 * \return retorna o grid
 */
bool** Life::getGrid() const {
    return this->grid;
}

/**
 * \brief verifica se a geração foi extinta
 */
bool Life::extinct() {
    for(int i = 0; i < this->getnLin(); i++) {
        for(int j = 0; j < this->getnCol(); j++) {
            if(this->getGrid()[i][j]) {
                return false;
            }
        }
    }
    return true;
}

/**
 * \brief método para fazer a copia do grid
 * \return retorna o grid copiado
 */
bool** Life::copyGrid() const {
    bool **grid = new bool*[this->getnLin()];
    for(int i = 0; i < this->getnLin(); i++) {
        grid[i] = new bool[this->getnCol()];
        for(int j = 0; j < this->getnCol(); j++) {
            grid[i][j] = this->getGrid()[i][j];
        }
    }
    return grid;
}

/**
 * \brief aplica a evolução de acordo com as regras
 */
void Life::update() {
    bool **auxGrid = this->copyGrid();
    for(int i = 1; i < this->getnLin() - 1; i++) {
        for(int j = 1; j < this->getnCol() - 1; j++) {
            int vivo = 0;
            for(int a = -1; a <= 1; a++) {
                for(int b = -1; b <= 1; b++) {
                    if(!(a == 0 && b == 0)) {
                        if(auxGrid[i + a][j + b]) {
                            vivo++;
                        }
                    }
                }
            }
            if(vivo < 2 || vivo > 3) {
                this->getGrid()[i][j] = false;
            } else if(vivo == 3) {
                this->getGrid()[i][j] = true;
            }
        }
    }
}

/**
 * \brief Compara dois grid e retorna se são iguais ou não
 * \param grid1, primeiro grid que será utilizado na comparação.
 * \param grid2, segundo grid que será utilizado na comparação
 * \return retorna true se forem iguais e false caso contrário.
 */
bool Life::compareGrid(bool **grid1, bool **grid2) {
    for(int i = 0; i < this->getnLin(); i++) {
        for(int j = 0; j < this->getnCol(); j++) {
            if(grid1[i][j] != grid2[i][j]) {
                return false;
            }
        }
    }
    return true;
}

/**
 * \brief verifica se as gerações estão mantendo um padrão
 * \param geracoes, vector com todas as gerações do sistema.
 * \return retorna se a geração se tornou estável.
 */
bool Life::stable(vector<bool **> geracoes) {
    for(unsigned int i = 0; i < geracoes.size(); i++) {
        for(unsigned int j = 0; j < geracoes.size(); j++) {
            if(i == j) continue;
            if(this->compareGrid(geracoes[i], geracoes[j])) {
                return true;
            }
        }
    }
    return false;
}

/**
 * \brief realizar o overload do operador <<, facilitando a impressão do objeto em um stream.
 * \param output, stream onde será impresso o objeto
 * \param life, objeto que será impresso em um stream
 */
std::ostream &operator<<(std::ostream &output, const Life &life) {
    for(int i = 0; i < life.getnLin(); i++) {
        output << "[";
        for(int j = 0; j < life.getnCol(); j++) {
            if(life.getGrid()[i][j] == 0) {
                output << " ";
            } else {
                output << life.getCaracter();
            }
        }
        output << "]" << endl;
    }
    return output;
}