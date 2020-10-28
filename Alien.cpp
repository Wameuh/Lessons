#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <numeric>

bool alien(int munition, int temps_restant,const std::vector<std::pair<int, int>> &pieces, int start, std::vector<std::vector<std::vector<int>>> &reste)
{
    if (start >= pieces.size() && munition >= 0 && temps_restant >= 0)
        return true ;
    if (munition < 0)
        return false ;
    if (temps_restant < 0)
        return false ;
    int piece_restante =  pieces.size()-start;

    if (reste.size() <= piece_restante)
        reste.resize(2*piece_restante +1);

    if (reste[piece_restante].size() <= munition)
        reste[piece_restante].resize(2*munition +1);

    if (reste[piece_restante][munition].size() <= temps_restant)
        reste[piece_restante][munition].resize(2*temps_restant+1);

    if (reste[piece_restante][munition][temps_restant] == 1)
        return true;
    else if (reste[piece_restante][munition][temps_restant] == 2)
        return false;


    if (alien(munition - pieces[start].first, temps_restant, pieces, start+1, reste))
    {
        reste[piece_restante][munition][temps_restant] = 1;
        return true;
    }
        
    else if (alien(munition, temps_restant - pieces[start].second, pieces, start+1, reste))
    {
        reste[piece_restante][munition][temps_restant] = 1;
        return true;
    }
    reste[piece_restante][munition][temps_restant] = 2;
    return false;
}

int main()
{
    bool debug = true ;
    int munition ;
    int temps ;
    int nombre_piece ; 
    std::cin >> munition >> temps >> nombre_piece;
    std::cerr << munition << ' ' << temps << ' ' << nombre_piece << std::endl;
    std::vector<std::pair<int, int>> pieces;
    for (int i=0; i < nombre_piece ; i++)
    {
        int nbr_alien ;
        int temps_contour ;
        if (debug) std::cin >> nbr_alien >> temps_contour ;
        pieces.emplace_back(nbr_alien, temps_contour);
        if (debug) std::cerr << nbr_alien << ' ' << temps_contour << std::endl;
    }
    int resultat ;
    std::vector<std::vector<std::vector<int>>> reste;
    if (alien(munition, temps, pieces, 0, reste))
        resultat = 1;
    else resultat =0;
    std::cout << resultat << std::endl ;
}