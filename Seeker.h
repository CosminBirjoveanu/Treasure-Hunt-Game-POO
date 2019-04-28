#ifndef Seeker_H
#define Seeker_H

#include "GameObject.h"

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

#endif // Seeker_H
