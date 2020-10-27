#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <set>
#include <cassert>
#include <limits>
#include <numeric>
#include <queue>
#include <cmath>
//objectif : trouver le chemin le plus long du graph

void DFS(int noeud, int nb_max_noeud, const std::vector<std::vector<int>> graph, std::vector<int> &longueur_arc, std::vector<bool> &dejavu)
{
    
    bool debug = false ;
    dejavu[noeud] = true;
    
    if (debug)
        std::cerr << "passage à la station :" << noeud << ". longueur de l'arc : " << longueur_arc[noeud] << std::endl;
    
    for (int voisin : graph[noeud])
    {
        
        if(!dejavu[voisin])
        {
            longueur_arc[voisin] = std::max(longueur_arc[noeud] + 1,longueur_arc[voisin])  ;
            DFS(voisin, nb_max_noeud, graph, longueur_arc, dejavu);
        }
    }
    dejavu[noeud] = false;

}

int main()
{
    bool debug = false;
    bool debug_couple = true;
    int station_depart;
    std::cin >> station_depart ;
    if (debug_couple) std::cerr << "station de départ " << station_depart << std::endl;
    int nb_couple ;
    std::cin >> nb_couple;
    int nb_max_station = 1001;
    std::vector<std::vector<int>> neighbours_matrix(nb_max_station, std::vector<int>());
    if (debug) std::cerr << " on va enregistrer les couples" << std::endl;
    for (int i =0; i< nb_couple; i++)
    {
        int station_a; int station_b;
        std::cin >> station_a >> station_b ;
        if (debug) std::cerr<< "lecture du couple " << i << " . Première station :" << station_a << " . deuxième station : " << station_b << std::endl;
        if (debug_couple) std::cerr << station_a << ' ' << station_b << std::endl;
        neighbours_matrix[station_a].emplace_back(station_b) ;
        neighbours_matrix[station_b].emplace_back(station_a) ;
    }
    
    std::vector<bool> dejavu(nb_max_station, false);
    std::vector<int> longueur_arc(nb_max_station, 0);
    if (debug) std::cerr << "on va lancer le DFS." << std::endl;
    DFS(station_depart, nb_max_station, neighbours_matrix, longueur_arc, dejavu);
    int longueur_max = *std::max_element(longueur_arc.begin(), longueur_arc.end()) -1;
    std::cout << longueur_max  << std::endl;
}