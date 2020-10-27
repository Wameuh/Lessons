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
#include <utility>
//objectif : trouver le chemin le plus long du graph

struct Step
{
    int cumul_distance;
    int from;
    int to;

    bool operator<(const Step &other) const
    {
        return cumul_distance > other.cumul_distance;
    }
};

int dijkstra(int indice_max_station, int station_depart, auto compute_distance, auto neighbours)
{
    std::vector<int> cumul_distances(indice_max_station, indice_max_station);
    std::vector<int> from(indice_max_station, -1);

    cumul_distances[station_depart]=0;

    std::priority_queue<Step> pq;
    pq.push(Step{0, -1, station_depart});

    while (!pq.empty())
    {
        Step top =  pq.top();
        pq.pop();

        if (top.cumul_distance > cumul_distances[top.to])
            continue;
        
        from[top.to]= top.from;
        cumul_distances[top.to] = top.cumul_distance;


        for (auto k : neighbours(top.to))
        {
            int d = compute_distance(k, top.to);
            if (d== -1)
                continue;
            pq.push(Step{top.cumul_distance + d, top.to, k});
        }
    }

    cumul_distances.erase(std::remove(cumul_distances.begin(), cumul_distances.end(), indice_max_station), cumul_distances.end());
    int chemin_max = *std::max_element(cumul_distances.begin(), cumul_distances.end()) -1;
    return chemin_max;
}



int main()
{
    bool debug = false;
    bool debug_couple = false;
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
    
    auto compute_distance = [&](int i, int j)
    {
        if (i==j)
            return -1;
        if (std::find(neighbours_matrix[i].begin(), neighbours_matrix[i].end(), j) == neighbours_matrix[i].end() )
            return -1;
        return 1;
    };

    auto neighbours = [&](int i)
    {
        return neighbours_matrix[i];
    };

    std::cout << dijkstra(nb_max_station, station_depart, compute_distance, neighbours)  << std::endl;
}