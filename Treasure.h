#ifndef Treasure_H
#define Treasure_H

#include "GameObject.h"
#include "Map.h"

class Treasure:public GameObject {
protected:
    bool found;
public:
    friend class Map;
    Treasure(std::string** M, int n, int abs, int ord, std::string str):GameObject(abs, ord, str) {
        srand (time(NULL));
        found = false;
        x = rand() % n + 1;
        y = rand() % n + 1;
        while ((M[x][y] == "treasure") || (x == 1 && y == 1)
               || (x == 1 && y == n) || (x == n && y == 1) || (x == n && y == n)) {
            x = rand() % n + 1;
            y = rand() % n + 1;
        }
    }
    ~Treasure();
    void setFound(bool ok);
    bool getFound();  ///Daca da, afara player-ul de pe casuta aia, cu tot cu comoara
};

#endif // Treasure_H
