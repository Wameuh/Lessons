#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
void DFS(int noeud, const std::vector<std::vector<int>> voisins, std::vector<int> &longueur_arc, std::vector<bool> &dejavu)
{
    dejavu[noeud] = true;
    for (int voisin : voisins[noeud])
    {
        if (!dejavu[voisin])
            longueur_arc[voisin] = std::max(longueur_arc[noeud]+1, longueur_arc[voisin]);
            DFS(voisin, voisins, longueur_arc, dejavu);
    }
    dejavu[noeud] = false;
}



int main()
{
    int n; // the number of relationships of influence
    cin >> n; cin.ignore();
    std::vector<std::vector<int>> voisins (10000);
    for (int i = 0; i < n; i++) {
        int x; // a relationship of influence between two people (x influences y)
        int y;
        cin >> x >> y; cin.ignore();
        voisins[x].emplace_back(y);
    }

    std::vector<bool> dejavu(10000, false);
    std::vector<int> longueur_arc(10000, 0);

    for (int i = 0 ; i < 10000 ; i++)
    {
        if (voisins[i].empty())
            continue;
        DFS(i, voisins, longueur_arc, dejavu);
    }
    int longueur_max = *std::max_element(longueur_arc.begin(), longueur_arc.end()) +1;

    

    // The number of people involved in the longest succession of influences
    cout << longueur_max << endl;
}
