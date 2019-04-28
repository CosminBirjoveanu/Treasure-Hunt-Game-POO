#include "GameObject.h"
#include <iostream>
#include <stdlib.h>
#include <string>
#include <time.h>
#include <assert.h>

GameObject::~GameObject() { }

const int GameObject::getX() {
    return x;
}

const int GameObject::getY() {
    return y;
}

const std::string GameObject::getType() {
    return type;
}

Treasure::~Treasure() { }

void Treasure::setFound(bool ok) {
    found = ok;
}

bool Treasure::getFound() {
    return found;
}

//Daca playerul a castigat, este rankat (first, second, third) si iese din harta
const void Seeker::won(std::string rank) {
    x = 0;
    y = 0;
    type = rank;
}

int Seeker::nextStep() {
    return 0;
}

Seeker::~Seeker() { }

//SeekerStraight incearca sa mearga cat poate in dreapta, apoi in jos, in stanga
//si, respectiv, in sus
const int SeekerStraight::nextStep(std::string** M) {

    //ok verifica daca metoda a facut un ciclu complet, de la 1 la 4,
    //iar daca da, inseamna ca functia cicleaza infinit asa ca iese din aceasta, jucatorul fiind blocat
    bool ok = false;
    //counter retine daca miscarea curenta este in dreapta (1), in jos (2),
    //in stanga (3) sau in sus (4)
    if (counter == 1) {
        ok = true;
    }
    if ((y < n) && (M[x][y+1] == "unexplored" || M[x][y+1] == "treasure") && (counter == 1)) {
        y++;
        return 1;
    }
    else if (counter == 1) {
        counter++;
    }

    if ((x < n) && (M[x+1][y] == "unexplored" || M[x+1][y] == "treasure") && (counter == 2)) {
        x++;
        return 1;
    }
    else if (counter == 2) {
        counter++;
    }

    if ((y > 1) && (M[x][y-1] == "unexplored" || M[x][y-1] == "treasure") && (counter == 3)) {
        y--;
        return 1;

    }
    else if (counter == 3) {
        counter++;
    }

    if ((x > 1) && (M[x-1][y] == "unexplored" || M[x-1][y] == "treasure") && (counter == 4)) {
        x--;
        return 1;
    }
    else if (counter == 4) {
        counter = 1;
        if (ok == true) {
            return 0;
        }
    }
    nextStep(M);
}

SeekerStraight::~SeekerStraight() { }

const int SeekerSegment::nextStep(std::string** M) {

    //ok este un vector care, odata ce verifica ca nu se intra pe niciunul dintre cazuri,
    //intrandu-se astfel intr-o bucla infinita, deoarece playerul s-a blocat
    bool *ok = new bool[nr_of_cases];
    for (int i = 0; i < nr_of_cases; i++) {
        ok[i] = false;
    }

    if ((y < n) && (M[x][y+1] == "unexplored" || M[x][y+1] == "treasure") && (counter < 3)) {
        y++;
        counter++;
        return 1;
    }
    else {
        ok[0] = true;
    }

    if ((y > 1) && (M[x][y-1] == "unexplored" || M[x][y-1] == "treasure") && (counter < 3)) {
        y--;
        counter++;
        return 1;
    }
    else {
        ok[1] = true;
    }

    if ((x < n) && (M[x+1][y] == "unexplored" || M[x+1][y] == "treasure") && (counter == 3)) {
        x++;
        counter = 1;
        return 1;
    }
    else {
        ok[2] = true;
    }

    if ((x > 1) && (M[x-1][y] == "unexplored" || M[x-1][y] == "treasure") && (counter == 3)) {
        x--;
        counter = 1;
        return 1;
    }
    else {
        ok[3] = true;
    }

    for (int i = 0; i < nr_of_cases; i++) {
        if (ok[i] == false) break;
        if (i == nr_of_cases - 1) return 0;
    }

    nextStep(M);
}

SeekerSegment::~SeekerSegment() { }

const int SeekerDiagonal::nextStep(std::string** M) {

    //Functie similara cu SeeekerStraight::nextStep, merge pe diagonala pe o directie
    //pana e obligat sa o schimbe, sau se blocheaza si iese din functie
    bool ok = false;
    if (counter == 1) {
        ok = true;
    }
    if ((x < n) && (y < n) && (M[x+1][y+1] == "unexplored" || M[x+1][y+1] == "treasure") && (counter == 1)) {
        x++;
        y++;
        return 1;
    }
    else if (counter == 1) {
        counter++;
    }

    if ((x < n) && (y > 1) && (M[x+1][y-1] == "unexplored" || M[x+1][y-1] == "treasure") && (counter == 2)) {
        x++;
        y--;
        return 1;
    }
    else if (counter == 2) {
        counter++;
    }

    if ((x > 1) && (y > 1) && (M[x-1][y-1] == "unexplored" || M[x-1][y-1] == "treasure") && (counter == 3)) {
        x--;
        y--;
        return 1;
    }
    else if (counter == 3) {
        counter++;
    }

    if ((x > 1) && (y < n) && (M[x-1][y+1] == "unexplored" || M[x-1][y+1] == "treasure") && (counter == 4)) {
        x--;
        y++;
        return 1;
    }
    else if (counter == 4) {
        counter = 1;
        if (ok == true) {
            return 0;
        }
    }
    nextStep(M);
}

SeekerDiagonal::~SeekerDiagonal() { }


const int SeekerZigzag::nextStep(std::string** M) {

    //Functie similara cu SeekerSegment::nextStep
    bool *ok = new bool[nr_of_cases];
    for (int i = 0; i < nr_of_cases; i++) {
        ok[i] =  false;
    }

    if ((x < n) && (y < n) && (M[x+1][y+1] == "unexplored" || M[x+1][y+1] == "treasure") && (counter == 1)) {
        x++;
        y++;
        counter++;
        return 1;
    }
    else {
        ok[0] = true;
    }

    if ((x > 1) && (y > 1) && (M[x-1][y-1] == "unexplored" || M[x-1][y-1] == "treasure") && (counter == 1)) {
        x--;
        y--;
        counter++;
        return 1;
    }
    else {
        ok[1] = true;
    }

    if ((x == 1 && y == n) || (x == n && y == 1)) counter++;

    if ((x > 1) && (y < n) && (M[x-1][y+1] == "unexplored" || M[x-1][y+1] == "treasure") && (counter == 2)) {
        x--;
        y++;
        counter = 1;
        return 1;
    }
    else {
        ok[2] = true;
    }

    if ((x < n) && (y > 1) && (M[x+1][y-1] == "unexplored" || M[x+1][y-1] == "treasure") && (counter == 2)) {
        x++;
        y--;
        counter = 1;
        return 1;
    }
    else {
        ok[3] = true;
    }

    for (int i = 0; i < nr_of_cases; i++) {
        if (ok[i] == false) break;
        if (i == nr_of_cases - 1) {
            return 0;
        }
    }
    nextStep(M);
}

SeekerZigzag::~SeekerZigzag() { }

const void Map::setMatrix(int x, int y, std::string type) {
    Matrix[x][y] = type;
}

std::string** Map::getMatrix() {
    return Matrix;
}

const int Map::getSize() {
    return size;
}

std::ostream& operator<< (std::ostream &out, Map &m) {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (m.getMatrix()[i][j] == "unexplored") out << "_ ";
            else if (m.getMatrix()[i][j] == "seekerA") out << "A ";
            else if (m.getMatrix()[i][j] == "seekerB") out << "B ";
            else if (m.getMatrix()[i][j] == "seekerC") out << "C ";
            else if (m.getMatrix()[i][j] == "seekerD") out << "D ";
            else if (m.getMatrix()[i][j] == "treasure") out << "T ";
            else out << "X ";
        }
        out << "\n";
    }
    return out;
}

void runGame() {
    //start_pos e un vector ce retine unde se duce fiecare dintre jucatori
    int *start_pos = new int[nr_of_edges];
    int aux, ranking = 1;
    Map map(n);
    //input retine daca utilizatorul vrea sau nu sa continue jocul
    char input;

    std::cout << "1 -> up-left\n2 -> down-left\n3 -> up-right\n4 -> down-right\n";
    for (int i = 0; i < nr_of_edges; i++) {
        std::cout << "\nPlayer " << char('A' + i) << " will be on position: ";
        std::cin >> aux;
        start_pos[i] = aux;
    }

    Treasure t1(map.getMatrix(), n, 0, 0, "treasure");
    map.setMatrix(t1.getX(), t1.getY(), t1.getType());

    Treasure t2(map.getMatrix(), n, 0, 0, "treasure");
    map.setMatrix(t2.getX(), t2.getY(), t2.getType());

    Treasure t3(map.getMatrix(), n, 0, 0, "treasure");
    map.setMatrix(t3.getX(), t3.getY(), t3.getType());

    SeekerStraight seek1(n, start_pos[0], 1, 0, 0, "seekerA");
    map.setMatrix(seek1.getX(),seek1.getY(), seek1.getType());

    SeekerSegment seek2(n, start_pos[1], 1, 0, 0, "seekerB");
    map.setMatrix(seek2.getX(),seek2.getY(), seek2.getType());

    SeekerDiagonal seek3(n, start_pos[2], 1, 0, 0, "seekerC");
    map.setMatrix(seek3.getX(),seek3.getY(), seek3.getType());

    SeekerZigzag seek4(n, start_pos[3], 1, 0, 0, "seekerD");
    map.setMatrix(seek4.getX(),seek4.getY(), seek4.getType());

    std::cout << map << "\nStart? Y/N\n";
    std::cin >> input;
    std::cout << "\n";

    bool *no_possible_moves = new bool[nr_of_cases];

    //cat timp inputul e pozitiv
    while (input == 'y' || input == 'Y')
    {
        for (int i = 0; i < nr_of_cases; i++) {
            no_possible_moves[i] = false;
        }

        int c = 0;
        int *old = new int[nr_of_old_coordinates]();

        //old e un vector ce retine vechile pozitii, pentru a observa daca jucatorii
        //se mai muta sau s-au blocat
        old[0] = seek1.getX();
        old[1] = seek1.getY();
        old[2] = seek2.getX();
        old[3] = seek2.getY();
        old[4] = seek3.getX();
        old[5] = seek3.getY();
        old[6] = seek4.getX();
        old[7] = seek4.getY();

        map.setMatrix(seek1.getX(),seek1.getY(), "x");
        if (seek1.getX() != 0) {
            seek1.nextStep(map.getMatrix());
            if (old[0] == seek1.getX() && old[1] == seek1.getY()) {
                no_possible_moves[0] = true;
            }

            if (t1.getX() == seek1.getX() && t1.getY() == seek1.getY()) {
                t1.setFound(true);
            }
            else if (t2.getX() == seek1.getX() && t2.getY() == seek1.getY()) {
                    t2.setFound(true);
                }
                else if (t3.getX() == seek1.getX() && t3.getY() == seek1.getY()) {
                        t3.setFound(true);
                    }

            if (t1.getFound() == true || t2.getFound() == true || t3.getFound() == true) {
                map.setMatrix(seek1.getX(),seek1.getY(), "x");
                if (ranking == 1) {
                    seek1.won("first "); /// Player ... is the ... one to find a treasure and win
                    ranking++;
                }
                    else if (ranking == 2) {
                        seek1.won("second ");
                        ranking++;
                    }
                        else if (ranking == 3) {
                            seek1.won("third ");
                            ranking++;
                        }
                t1.setFound(false); t2.setFound(false); t3.setFound(false);
            }
            map.setMatrix(seek1.getX(),seek1.getY(), "seekerA");
        }
        else {
            no_possible_moves[0] = true;
        }

        map.setMatrix(seek2.getX(),seek2.getY(), "x");
        if (seek2.getX() != 0) {
            seek2.nextStep(map.getMatrix());

            if (old[2] == seek2.getX() && old[3] == seek2.getY()) {
                no_possible_moves[1] = true;
            }

            if (t1.getX() == seek2.getX() && t1.getY() == seek2.getY()) {
                t1.setFound(true);
            }
            else if (t2.getX() == seek2.getX() && t2.getY() == seek2.getY()) {
                    t2.setFound(true);
                }
                else if (t3.getX() == seek2.getX() && t3.getY() == seek2.getY()) {
                        t3.setFound(true);
                    }

            if (t1.getFound() == true || t2.getFound() == true || t3.getFound() == true) {
                map.setMatrix(seek2.getX(),seek2.getY(), "x");
                if (ranking == 1) {
                    seek2.won("first "); /// Player ... is the ... one to find a treasure and win
                    ranking++;
                }
                    else if (ranking == 2) {
                        seek2.won("second ");
                        ranking++;
                    }
                        else if (ranking == 3) {
                            seek2.won("third ");
                            ranking++;
                        }
                t1.setFound(false); t2.setFound(false); t3.setFound(false);
            }
            map.setMatrix(seek2.getX(),seek2.getY(), "seekerB");
        }
        else {
            no_possible_moves[1] = true;
        }

        map.setMatrix(seek3.getX(),seek3.getY(), "x");
        if (seek3.getX() != 0) {
            seek3.nextStep(map.getMatrix());

            if (old[4] == seek3.getX() && old[5] == seek3.getY()) {
                no_possible_moves[2] = true;
            }

            if (t1.getX() == seek3.getX() && t1.getY() == seek3.getY()) {
                t1.setFound(true);
            }
            else if (t2.getX() == seek3.getX() && t2.getY() == seek3.getY()) {
                    t2.setFound(true);
                }
                else if (t3.getX() == seek3.getX() && t3.getY() == seek3.getY()) {
                        t3.setFound(true);
                    }

            if (t1.getFound() == true || t2.getFound() == true || t3.getFound() == true) {
                map.setMatrix(seek3.getX(),seek3.getY(), "x");
                if (ranking == 1) {
                    seek3.won("first "); /// Player ... is the ... one to find a treasure and win
                    ranking++;
                }
                    else if (ranking == 2) {
                        seek3.won("second ");
                        ranking++;
                    }
                        else if (ranking == 3) {
                            seek3.won("third ");
                            ranking++;
                        }
                t1.setFound(false); t2.setFound(false); t3.setFound(false);
            }
            map.setMatrix(seek3.getX(),seek3.getY(), "seekerC");
        }
        else {
            no_possible_moves[2] = true;
        }

        map.setMatrix(seek4.getX(),seek4.getY(), "x");
        if (seek4.getX() != 0) {
            seek4.nextStep(map.getMatrix());

            if (old[6] == seek4.getX() && old[7] == seek4.getY()) {
                no_possible_moves[3] = true;
            }

            if (t1.getX() == seek4.getX() && t1.getY() == seek4.getY()) {
                t1.setFound(true);
            }
            else if (t2.getX() == seek4.getX() && t2.getY() == seek4.getY()) {
                    t2.setFound(true);
                }
                else if (t3.getX() == seek4.getX() && t3.getY() == seek4.getY()) {
                        t3.setFound(true);
                    }

            if (t1.getFound() == true || t2.getFound() == true || t3.getFound() == true) {
                map.setMatrix(seek4.getX(),seek4.getY(), "x");
                if (ranking == 1) {
                    seek4.won("first "); /// Player ... is the ... one to find a treasure and win
                    ranking++;
                }
                    else if (ranking == 2) {
                        seek4.won("second ");
                        ranking++;
                    }
                        else if (ranking == 3) {
                            seek4.won("third ");
                            ranking++;
                        }
                t1.setFound(false); t2.setFound(false); t3.setFound(false);
            }
            map.setMatrix(seek4.getX(),seek4.getY(), "seekerD");
        }
        else {
            no_possible_moves[3] = true;
        }

        std::cout << map;

        if (seek1.getType() != "seekerA") {
            std::cout << "\nPlayer A is the " << seek1.getType() << "one to find the treasure and win";
        }
        else {
            std::cout << "\nPlayer A has not found the treasure yet";
        }

        if (seek2.getType() != "seekerB") {
            std::cout << "\nPlayer B is the " << seek2.getType() << "one to find the treasure and win";
        }
        else {
            std::cout << "\nPlayer B has not found the treasure yet";
        }

        if (seek3.getType() != "seekerC") {
            std::cout << "\nPlayer C is the " << seek3.getType() << "one to find the treasure and win";
        }
        else {
            std::cout << "\nPlayer C has not found the treasure yet";
        }

        if (seek4.getType() != "seekerD") {
            std::cout << "\nPlayer D is the " << seek4.getType() << "one to find the treasure and win";
        }
        else {
            std::cout << "\nPlayer D has not found the treasure yet";
        }

        bool no_moves = false;

        for (int i = 0; i < nr_of_cases; i++) {
            if (no_possible_moves[i] == false) {
                break;
            }
            if (i == nr_of_cases - 1) {
                no_moves = true;
            }
        }

        if (no_moves == true) {
            std::cout << "\n\nNo more possible moves!\n\n";
            break;
        }

        bool *winners = new bool[nr_of_cases];

        for (int i = 0; i < nr_of_cases; i++) {
            winners[i] = false;
        }

        if (seek1.getX() == 0) {
            winners[0] = true;
        }
        if (seek2.getX() == 0) {
            winners[1] = true;
        }
        if (seek3.getX() == 0) {
            winners[2] = true;
        }
        if (seek4.getX() == 0) {
            winners[3] = true;
        }

        int counter = 0;

        for (int i = 0; i < nr_of_cases; i++) {
            if (winners[i] == true) {
                counter++;
            }
        }

        if (counter == 3) {
            std::cout << "\n\nThe game has finished with 3 players having won\n\n";
            return;
        }

        int i, j;

        for (i= 1; i <= n; i++) {
            for (j = 1; j <= n; j++) {
                if (map.getMatrix()[i][j] != "x") break;
            }
            //daca s-a parcurs toata matricea si este plina
            if (i == n && j == n) {
                std::cout << "\n\nAll the spaces on the map have been filled\n\n";
                return;
            }
        }
        std::cout << "\n\nContinue? Y/N\n";
        std::cin >> input;
    }

}
