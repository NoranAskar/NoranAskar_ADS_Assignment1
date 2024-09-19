// TowersOfHanoi.h
#ifndef TOWERSOFHANOI_H
#define TOWERSOFHANOI_H

#include "Stackt.h"

class TowersOfHanoi {
private:
    Stackt<int> pegA;
    Stackt<int> pegB;
    Stackt<int> pegC;
    int numDisks;
    int moveCount;

    void moveDisks(int N, Stackt<int>& source, Stackt<int>& target, Stackt<int>& auxiliary);

public:
    TowersOfHanoi(int N);
    void solve();
    void displayPegs();
};

#endif // TOWERSOFHANOI_H