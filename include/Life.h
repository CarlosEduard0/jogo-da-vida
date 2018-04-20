// Life.h
#ifndef _LIFE_H_
#define _LIFE_H_

#include <iostream>
#include <vector>

using namespace std;

/**
 * Principal e única classe do programa. Ela realiza todas as operações necessárias para o sistema de grids funcionar.
 * Os métodos estão comentados no arquivo de implementação da classe.
 */
class Life {
public:
    Life();
    Life(int nLin, int nCol);
    void setnLin(int nLin);
    void setnCol(int nCol);
    void setCaracter(char caracter);
    void setGrid(bool **grid);
    int getnLin() const;
    int getnCol() const;
    char getCaracter() const;
    bool** getGrid() const;
    bool** copyGrid() const;
    void update();
    /*std::ostream& operator<<(std::ostream&, const Life&);*/
    bool stable(vector<bool **> geracoes);
    bool extinct();
    bool compareGrid(bool **grid1, bool **grid2);
private:
    int nLin;
    int nCol;
    char caracter;
    bool **grid;
};
ostream &operator<<(ostream &output, const Life &life);
#endif