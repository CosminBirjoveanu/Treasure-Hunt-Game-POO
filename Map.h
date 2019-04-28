#ifndef Map_H
#define Map_H

#include "Treasure.h"
#include "GameObject.h"
#include <iostream>

const int nr_of_cases = 4;
const int nr_of_edges = 4;
const int n = 15;

class Map {
protected:
    const int size;
    std::string **Matrix;
public:
    Map(int n):size(n) {
        Matrix = new std::string*[n + 1];
        for (int i = 0; i <= n; i++) {
            Matrix[i] = new std::string[n + 1];
        }
        for (int i = 0; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                Matrix[i][j] = "unexplored";
            }
        }
    };
    ~Map() {
        for (int i = 0; i <= n; i++) {
            delete[] Matrix[i];
        }
        delete[] Matrix;
    };
    const int getSize();
    std::string** getMatrix();
    const void setMatrix(int x, int y, std::string type);
    friend std::ostream &operator<< (std::ostream &out, Map &m);
    friend void runGame();
    friend class Treasure;
    friend class SeekerStraight;
    friend class SeekerDiagonal;
    friend class SeekerSegment;
    friend class SeekerZigzag;
};

void runGame();

#endif // Map_H
