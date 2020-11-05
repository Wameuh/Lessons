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
std::pair<int, int> recherche(std::queue<int> &ligne)
{
    bool debug = false;
    int init = ligne.front();
    int count = 1;
    if (debug) std::cerr << "taille de la ligne : " << ligne.size() << std::endl;

    ligne.pop();
    
    while (ligne.front() == init && !ligne.empty())
    {
        count++;
        ligne.pop();
    }
    std::pair<int, int> retval = {count, init};
    if (debug) std::cerr << "retour de la recherche : " << retval.first << ' ' << retval.second << std::endl;
    return retval;
}

std::queue<int> ligne_suivante(std::queue<int> &ligne)
{
    std::queue<int> ligne_suivante;
    while (!ligne.empty())
    {
        std::pair<int, int> retval = recherche(ligne);
        ligne_suivante.push(retval.first);
        ligne_suivante.push(retval.second);
    }
    return ligne_suivante;
}




int main()
{
    int R;
    cin >> R; cin.ignore();
    int L;
    cin >> L; cin.ignore();

    int numL = 1;
    std::queue<int> ligne;
    ligne.push(R);

    while (numL != L)
    {
        ligne= ligne_suivante(ligne);
        numL++;
    }
    // Write an answer using cout. DON'T FORGET THE "<< endl"
    // To debug: cerr << "Debug messages..." << endl;

    std::cout << ligne.front() ;
    ligne.pop();
    while (!ligne.empty())
    {
        std::cout << ' ' << ligne.front() ;
        ligne.pop();
    }
    std::cout << std::endl;
}