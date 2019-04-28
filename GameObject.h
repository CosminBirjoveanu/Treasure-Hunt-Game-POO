#ifndef GameObject_H
#define GameObject_H

#include <iostream>
#include <stdlib.h>
#include <string>
#include <time.h>
#include <assert.h>

const int nr_of_old_coordinates = 8;
const int nr_of_cases = 4;
const int nr_of_edges = 4;
const int n = 15;

class GameObject {
protected:
    int x, y;  /// coordonate
    std::string type; // seeker, treasure, unexplored, x (explored)
public:
    GameObject(int abs, int ord, std::string str): x(abs), y(ord), type(str) {};
    virtual ~GameObject() = 0;
    const int getX();
    const int getY();
    const std::string getType();
};

class Seeker:public GameObject {
public:
    Seeker(int n, int edge, int abs, int ord, std::string str):GameObject(abs, ord, str) {
        assert(1 <= edge && edge <= 4);
        //In switch se alege pe ce colt o sa fie pus un player ce a primit un anume edge
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
    //Won scoate un jucator din harta in cazul in care a castigat
    const void won(std::string rank);
    //Virtual ce pune baza conceptului urmatoarelor subclase
    virtual int nextStep();
};

//Seeker ce cauta in linie dreapta
class SeekerStraight:public Seeker {
private:
    int counter;
public:
    SeekerStraight(int n, int edge, int counter_initial, int abs, int ord, std::string str):Seeker(n, edge, abs, ord, str), counter(counter_initial) {};
    ~SeekerStraight();
    const int nextStep(std::string** M);
};

//Seeker ce cauta in diagonala
class SeekerDiagonal:public Seeker {
private:
    int counter;
public:
    SeekerDiagonal(int n, int edge, int counter_initial, int abs, int ord, std::string str):Seeker(n, edge, abs, ord, str), counter(counter_initial) {};
    ~SeekerDiagonal();
    const int nextStep(std::string** M);
};

//Seeker ce cauta 2 patratele pe orizontala, apoi 1 pe verticala
class SeekerSegment:public Seeker {
private:
    int counter;
public:
    SeekerSegment(int n, int edge, int counter_initial, int abs, int ord, std::string str):Seeker(n, edge, abs, ord, str), counter(counter_initial) {};
    ~SeekerSegment();
    const int nextStep(std::string** M);
};

//Seeker ce cauta in zigzag, o data in sensul diagonalei principale,
// o data in sensul diagonalei secundare
class SeekerZigzag: public Seeker {
    int counter;
public:
    SeekerZigzag(int n, int edge, int counter_initial, int abs, int ord, std::string str):Seeker(n, edge, abs, ord, str), counter(counter_initial) {};
    ~SeekerZigzag();
    const int nextStep(std::string** M);
};

class Treasure;

//Clasa ce manageriaza jocul
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
    //supraincarcarea operatorului <<
    friend std::ostream &operator<< (std::ostream &out, Map &m);
    //functia ce ruleaza intregul joc
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
        //se selecteaza aleatoriu 2 coordonate si se verifica daca nu
        //se intersecteaza cu alta comoara sau cu un colt
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
    bool getFound();
};

void runGame();

#endif // GameObject_H
