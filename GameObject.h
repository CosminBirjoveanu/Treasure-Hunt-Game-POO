#ifndef GameObject_H
#define GameObject_H

#include <iostream>
#include <stdlib.h>
#include <string>
#include <time.h>
#include <assert.h>

class GameObject {
protected:
    int x, y;  /// coordonate
    std::string type; /// Explored, Seeker, Treasure, Unexplored
public:
    GameObject(int abs, int ord, std::string str): x(abs), y(ord), type(str) {};
    virtual ~GameObject() = 0;
    const int getX();
    const int getY();
    const std::string getType();
    friend class Treasure;
};

class Seeker:public GameObject {
public:
    Seeker(int n, int edge, int abs, int ord, std::string str):GameObject(abs, ord, str) {
        assert(1 <= edge && edge <= 4);
        switch (edge) {
            case 1:
                x = 1; y = 1;
                break;
            case 2:
                x = n; y = 1;
                break;
            case 3:
                x = 1; y = n;
                break;
            case 4:
                x = n; y = n;
        }
    }
    ~Seeker();
    const void won(std::string rank);
    virtual int nextStep();
};

class SeekerStraight:public Seeker {
private:
    int counter;
public:
    SeekerStraight(int n, int edge, int counter_initial, int abs, int ord, std::string str):Seeker(n, edge, abs, ord, str), counter(counter_initial) {};
    ~SeekerStraight();
    const int nextStep(std::string** M);
};

class SeekerDiagonal:public Seeker {
private:
    int counter;
public:
    SeekerDiagonal(int n, int edge, int counter_initial, int abs, int ord, std::string str):Seeker(n, edge, abs, ord, str), counter(counter_initial) {};
    ~SeekerDiagonal();
    const int nextStep(std::string** M);
};

class SeekerSegment:public Seeker {
private:
    int counter;
public:
    SeekerSegment(int n, int edge, int counter_initial, int abs, int ord, std::string str):Seeker(n, edge, abs, ord, str), counter(counter_initial) {};
    ~SeekerSegment();
    const int nextStep(std::string** M);
};

class SeekerZigzag: public Seeker {
    int counter;
public:
    SeekerZigzag(int n, int edge, int counter_initial, int abs, int ord, std::string str):Seeker(n, edge, abs, ord, str), counter(counter_initial) {};
    ~SeekerZigzag();
    const int nextStep(std::string** M);
};


const int nr_of_cases = 4;
const int nr_of_edges = 4;
const int n = 15;

class Treasure;

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

void runGame();


#endif // GameObject_H
