#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

std::vector<std::string> lon1 = {"AH", "4H", "5D", "6D", "QC", "JS", "8S", "2D", "7D", "JD", "JC", "6C", "KS", "QS", "9D", "2C", "5S", "9S", "6S", "8H", "AD", "4D", "2H", "2S", "7S", "8C"};
std::vector<std::string> lon2 = {"10H", "4C", "6H", "3C", "KC", "JH", "10C", "AS", "5H", "KH", "10S", "9H", "9C", "8D", "5C", "AC", "3H", "4S", "KD", "7C", "3S", "QH", "10D", "3D", "7H", "QD"};
std::vector<std::string> test1 = {"10D", "9S", "8D", "KH", "7D", "5H", "6S"};
std::vector<std::string> test2 = {"10H", "7H", "5C", "QC", "2C", "4H", "6D"};
/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
int comparaison(char carte1, char carte2)
{
    // 0 si égalité, 1 si carte1 gagne, 2 si carte 2 gagne
    std::vector<char> type_carte = {'2', '3','4','5','6','7','8','9','1','J', 'Q', 'K', 'A'};
    int valeur1 = std::distance(type_carte.begin(), std::find(type_carte.begin(), type_carte.end(), carte1));
    int valeur2 = std::distance(type_carte.begin(), std::find(type_carte.begin(), type_carte.end(), carte2));

    if (valeur1 == valeur2)
        return 0;
    if (valeur1 > valeur2)
        return 1;
    return 2;
}

int WAR(string &carte1, string &carte2, std::queue<string> &tas1, std::queue<string> &tas2, std::queue<string> &p1_deck, std::queue<string> &p2_deck)
{
    bool debug = false;
    if (debug) std::cerr << "on est dans la bataille :" << carte1 << ' ' << carte2 << std::endl;
    
    tas1.push(carte1);
    tas2.push(carte2);

    for (int i=0; i<4; i++)
    {
        
        if (debug) std::cerr << "taille paquet1 :" << p1_deck.size() << std::endl;
        if (debug) std::cerr << "taille paquet2 :" << p2_deck.size() << std::endl;
        if (p1_deck.empty() || p2_deck.empty())
            return 0;
        carte1 = p1_deck.front();
        p1_deck.pop();
        tas1.push(carte1);
        carte2 = p2_deck.front();
        p2_deck.pop();
        tas2.push(carte2);
    }
    // while (!tas2.empty())
    // {
    //     tas1.push(tas2.front());
    //     tas2.pop();
    // }
    if (comparaison(carte1[0], carte2[0]) == 0)
    {
        if (debug) std::cerr << "encore égalité !!" << carte1 << ' ' << carte2 << std::endl;
        return WAR(carte1, carte2, tas1, tas2, p1_deck, p2_deck);
    }
    
    if (comparaison(carte1[0], carte2[0]) == 1)
    {
        if (debug) std::cerr << "joueur 1 gagne. cartes : " <<carte1 << carte2<< std::endl;
        return 1;
    }
        
    if (debug) std::cerr << "joueur 2 gagne. cartes : " <<carte1 << carte2<< std::endl;
    if (debug) std::cerr << "taille paquet1 :" << p1_deck.size() << std::endl;
    if (debug) std::cerr << "taille paquet2 :" << p2_deck.size() << std::endl;
    return 2;
}

void affichage(std::queue<string> queue)
{
    while (!queue.empty())
    {
        std::cerr << queue.front() << ", ";
        queue.pop();
    }
    std::cerr << std::endl;
}

int main()
{
    bool debug = false;
    bool debugwar = false;
    bool debug_suivi = false;
    std::queue<std::string> p1_deck;
    for (std::string i : lon1)
        p1_deck.push(i);
    std::queue<std::string> p2_deck;
    for (std::string i : lon2)
        p2_deck.push(i);

    std::string retval;
    int NT = 0; // the number of turns
    int n; // the number of cards for player 1
    cin >> n; cin.ignore();
    // for (int i = 0; i < n; i++) {
    //     string cardp1; // the n cards of player 1
    //     cin >> cardp1; cin.ignore();
    //     p1_deck.push(cardp1);
    // }
    // int m; // the number of cards for player 2
    // cin >> m; cin.ignore();
    // for (int i = 0; i < m; i++) {
    //     string cardp2; // the m cards of player 2
    //     cin >> cardp2; cin.ignore();
    //     p2_deck.push(cardp2);
    // }   
    

    while (!p1_deck.empty() && !p2_deck.empty())
    {
        if (debug_suivi)
        {
            affichage(p1_deck);
            affichage(p2_deck);
        }
        NT ++;
        std::string carte1 = p1_deck.front();
        p1_deck.pop();
        std::string carte2 = p2_deck.front();
        p2_deck.pop();
        int resultat = comparaison(carte1[0], carte2[0]);
        if (debug) std::cerr << "résultat de la comparaison : " << resultat << std::endl;
        if (resultat == 1)
        {
            if (debug) std::cerr << "joueur 1 gagne. cartes : " <<carte1 << carte2<< std::endl;
            p1_deck.push(carte1); p1_deck.push(carte2);
        }
        if (resultat == 2)
        {

            p2_deck.push(carte1); p2_deck.push(carte2);
            
            if (debug) std::cerr << "joueur 2 gagne. cartes : " <<carte1 << carte2<< std::endl;
        }
        if (resultat == 0)
        {
            if (debug) std::cerr << "Que la guerre commence" << std::endl;
            std::queue<string> tas1;
            std::queue<string> tas2;
            resultat = WAR(carte1, carte2, tas1, tas2, p1_deck, p2_deck);
            if (debug) std::cerr << "résultat de la guerre : " << resultat << std::endl;
            if (debug) std::cerr << "taille du paquet 1 : " << p1_deck.size() << std::endl;
            if (debug) std::cerr << "taille du paquet 2 : " << p2_deck.size() << std::endl;
            if (resultat == 0)
                retval = "PAT";
            if (resultat == 1)
            {
                if (debugwar) std::cerr << "1 à gagner on va lui rajouter des cartes " << tas1.size() << "et" << tas2.size()<< std::endl;
                if (debugwar) std::cerr << "fin de la boucle : taille du paquet 1 : " << p1_deck.size() << std::endl;
                while (!tas1.empty())
                {
                    p1_deck.push(tas1.front());
                    tas1.pop();
                }
                while (!tas2.empty())
                {
                    p1_deck.push(tas2.front());
                    tas2.pop();
                }
            }
            if (resultat == 2)
            {
                //todo c'est ici l'erreur ?
                if (debugwar) std::cerr << "2 à gagner on va lui rajouter des cartes " << tas1.size() << "et" << tas2.size()<< std::endl;
                if (debugwar) std::cerr << "fin de la boucle :  taille du paquet 2 : " << p2_deck.size() << std::endl;
                while (!tas1.empty())
                {
                    p2_deck.push(tas1.front());
                    tas1.pop();
                }
                while (!tas2.empty())
                {
                    p2_deck.push(tas2.front());
                    tas2.pop();
                }
            }
            
            if (debugwar) std::cerr << "fin de la boucle : taille du paquet 1 : " << p1_deck.size() << std::endl;
            if (debugwar) std::cerr << "fin de la boucle :  taille du paquet 2 : " << p2_deck.size() << std::endl;

        }
    }
    
    if (retval != "PAT")
    {
        if (debug) std::cerr << "taille du paquet 1 : " << p1_deck.size() << std::endl;
        if (debug) std::cerr << "taille du paquet 2 : " << p2_deck.size() << std::endl;
        if (p1_deck.empty() && !p2_deck.empty())
            retval = "2";
        else if (p2_deck.empty() && !p1_deck.empty())
            retval = "1";

        std::cout << retval << ' ' << NT << endl;
        
    }
    
    if (debugwar) std::cerr << "c'est PAT, nombre de tour :" << NT << std::endl;
    else std::cout << retval << endl;
}