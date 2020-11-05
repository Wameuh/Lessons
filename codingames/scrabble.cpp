#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
int calcul_point(char lettre)
{
    if (lettre=='q' ||lettre=='z')
        return 10;
    if (lettre=='j' ||lettre=='x')
        return 8;
    if (lettre=='k')
        return 5;
    if (lettre=='f' ||lettre=='h'||lettre=='v'||lettre=='w'||lettre=='y')
        return 4;
    if (lettre=='b' ||lettre=='c'||lettre=='m'||lettre=='p')
        return 3;
    if (lettre=='d' ||lettre=='g')
        return 2;
    
    return 1; 
}

std::pair<bool, int> recherche(std::string k, std::vector<char> lettres)
{
    bool possible = true;
    int points = 0;
    for (char L : k)
    {
        if (lettres.empty())
        {
            possible = false;
            continue;
        }

        auto emplacement = std::find(lettres.begin(), lettres.end(), L);
        
        if (emplacement == lettres.end())
        {
            possible = false;
            continue;
        }

        lettres.erase(emplacement);
        points += calcul_point(L);

    }
    return {possible, points};
}

int main()
{
    int N;
    cin >> N; cin.ignore();
    std::vector<std::string> dict;
    for (int i = 0; i < N; i++) {
        std::string W;
        getline(cin, W);
        if (W.size() > 7)
            continue;
        dict.emplace_back(W);
    }
    std::string LETTERS;
    getline(cin, LETTERS);
    std::vector<char> lettres;
    for (int i=0; i < LETTERS.size(); i++)    
    {
        lettres.emplace_back(LETTERS[i]);
    }
    std::pair<string, int> retval = {"", 0};
    for (std::string k : dict)
    {
        std::pair<bool, int> resultat_recherche = recherche(k, lettres);
        if (!resultat_recherche.first || resultat_recherche.second <= retval.second)
            continue;
        
        retval.first = k;
        retval.second = resultat_recherche.second;  
    }
    // Write an answer using cout. DON'T FORGET THE "<< endl"
    // To debug: cerr << "Debug messages..." << endl;

    std::cout << retval.first << endl;
}
