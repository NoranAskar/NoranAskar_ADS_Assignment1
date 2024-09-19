// TowersOfHanoi.cpp
#include "TowersOfHanoi.h"
#include "Stackt.h"
#include <iostream>

using namespace std;

//placing all disks onto pegA
TowersOfHanoi::TowersOfHanoi(int N) : pegA(N), pegB(N), pegC(N), numDisks(N), moveCount(0) {
    // Student Task: Initialize the pegs and place N disks on pegA
    // - Use a loop to push disks numbered from N down to 1 onto pegA.
    // - Each disk should be pushed in decreasing size order.
    for (int i = N; i >= 1; --i) {
        pegA.push(i);
    }
}

//solve function to refer to the moveDisks function
void TowersOfHanoi::solve() {
    // Student Task: Implement the solve function
    // - This function should initiate the solution by calling moveDisks with the correct parameters.
    // - Use 'numDisks' as the number of disks to move.
    // - Move disks from pegA (source) to pegC (target) using pegB (auxiliary).
    moveDisks(numDisks, pegA, pegC, pegB);
}

//recursive moveDisks function to show how movements are done based on the situation
void TowersOfHanoi::moveDisks(int N, Stackt<int>& source, Stackt<int>& target, Stackt<int>& auxiliary) {
    // Student Task: Implement the moveDisks function
    // - This is a recursive function that moves N disks from the source peg to the target peg using the auxiliary peg.
    // - Base case: If N is 1, move a disk directly from the source to the target.
    // - Recursive case:
    //   1. Move N-1 disks from the source to the auxiliary peg using the target peg.
    //   2. Move the Nth disk from the source to the target peg.
    //   3. Move the N-1 disks from the auxiliary peg to the target peg using the source peg.
    // - After each move, increment moveCount and call displayPegs to show the current state of pegs.
    if (N == 1) {
        target.push(source.pop());
        moveCount++;
        displayPegs();
        return;
    }
    else {
        moveDisks(N - 1, source, auxiliary, target);
        target.push(source.pop());
        moveCount++;
        displayPegs();
        moveDisks(N - 1, auxiliary, target, source);
    }
}

//displaying each move and current state of all pegs
void TowersOfHanoi::displayPegs() {
    // This function is implemented for you.
    // It prints the current state of the three pegs (A, B, C).
    cout << "Move number " << moveCount << ":" << endl;  //additional part to display each move
    cout << "Peg A: ";
    pegA.display();
    cout << "Peg B: ";
    pegB.display();
    cout << "Peg C: ";
    pegC.display();
    cout << "-------------------------" << endl;
}
