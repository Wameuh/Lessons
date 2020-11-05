#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/




int main()
{
    int N;
    cin >> N; cin.ignore();
    std::vector<long> ordonnees;
    long Xmin =std::numeric_limits<long>::max(); long Xmax=std::numeric_limits<long>::min();
    for (int i = 0; i < N; i++) {
        long X;
        long Y;
        cin >> X >> Y; cin.ignore();
        ordonnees.emplace_back(Y);
        if (X < Xmin)
            Xmin = X;
        if (X > Xmax)
            Xmax = X;
    }
    std::sort(ordonnees.begin(), ordonnees.end());
    long milieu = (ordonnees.size()+1)/2;
    long mediane = ordonnees[milieu-1];
    
    long long longueur = 0;
    
    for (long i : ordonnees)
        longueur += abs(mediane-i);
    
    
    longueur += Xmax - Xmin;

    // Write an answer using cout. DON'T FORGET THE "<< endl"
    // To debug: cerr << "Debug messages..." << endl;

    cout << longueur << endl;
}