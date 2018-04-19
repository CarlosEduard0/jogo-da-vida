// Life.h
#ifndef _LIFE_H_
#define _LIFE_H_

#include <iostream>

using namespace std;

class Life {
public:
    Life(int nLin, int nCol);
    void set_alive();
    void update();
    friend ostream &operator<<(ostream &output, const Life &L);
    void stable();
    void extinct();
private:
    int nLin;
    int nCol;
};
#endif