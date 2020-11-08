#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
bool isloop(const std::vector<std::vector<std::pair<std::vector<bool>, std::string>>> &dejavu, int x, int y, std::string direction, std::vector<bool> etat)
{
    if (dejavu[x][y].first == etat && direction == dejavu[x][y].second)
        return true;
    return false;
}

std::string conversion_prio_dir(std::pair<int,int> prio)
{
    if (prio.first == 1)
        return "EAST";
    if (prio.first == -1)
        return "WEST";
    if (prio.second == 1)
        return "SOUTH";
    
    return "NORTH";
}

bool possible(std::pair<int,int> move, std::pair<int,int> blender, const std::vector<std::vector<char>> &map, bool breaker)
{
    char arrivee = map[blender.first + move.first][blender.second+move.second];
    return (arrivee != '#' && !(arrivee =='X' && !breaker));
}


void afficher(std::vector<std::vector<char>> map,std::pair<int,int> blender)
{
    map[blender.first][blender.second] = '@';
    for (int i=0; i < map[0].size(); i++)
    {
        for (int j=0; j< map.size(); j++)
            std::cerr << map[j][i] ;
        std::cerr << endl;
    }
}

int main()
{
    bool debugdebutloop = true;
    bool debugmap = false;
    int L;
    int C;
    cin >> L >> C; cin.ignore();
    std::vector<std::vector<char>> map(100, std::vector<char>(100, ' '));
    std::pair<int, int> blender;
    std::vector<std::pair<int,int>> teleport;
    for (int i = 0; i < L; i++) {
        string row;
        getline(cin, row);
        std::cerr << row << std::endl;
        for (int j=0; j< C; j++)
        {
            map[j][i] = row[j];
            if (row[j] == '@')
            {   
                blender.first = j;
                blender.second = i;
            }
            if (row[j] == 'T')
            {
                teleport.emplace_back(j,i);
            }
        }

    }
    //afficher(map, blender);
    std::vector<std::pair<int, int>> priority1 = {{0,1}, {1,0}, {0, -1}, {-1,0}};
    std::vector<std::pair<int, int>> priority2 = {{-1,0}, {0,-1}, {1,0}, {0,1}};
    std::vector<std::pair<int, int>> priority = priority1;

    std::vector<std::vector<std::pair<std::vector<bool>, string>>> dejavu (100, std::vector<std::pair<std::vector<bool>, string>> (100, std::pair<std::vector<bool>, string> {std::vector<bool> {false, false, false}, ""}));
    std::string direction = conversion_prio_dir(priority[0]);
    std::vector<string> moves;
    bool breaker = false;
    bool inverter=true;
    std::vector<bool> etat {true, breaker, inverter};
    std::pair<int, int> next_move = priority[0];

    while (!isloop(dejavu, blender.first, blender.second, direction, etat) && map[blender.first][blender.second] != '$' )
    {
        if (debugdebutloop) std::cerr << "emplacement de blender : " << blender.first << ' ' << blender.second << std::endl;
        if (debugdebutloop) std::cerr << "direction : " << direction << std::endl;
        dejavu[blender.first][blender.second].first = etat;
        dejavu[blender.first][blender.second].second = direction;
        if (!possible(next_move, blender, map, breaker))
            next_move = priority[0];
        if (!possible(next_move, blender, map, breaker))
            next_move = priority[1];
        if (!possible(next_move, blender, map, breaker))
            next_move = priority[2];
        if (!possible(next_move, blender, map, breaker))
            next_move = priority[3];

        blender.first += next_move.first;
        blender.second += next_move.second;
        direction = conversion_prio_dir(next_move);
        moves.emplace_back(direction);

        //résolution sur là où on arrive.
        if (map[blender.first][blender.second] == 'S')
            next_move = {0,1};
        if (map[blender.first][blender.second] == 'N')
            next_move = {0,-1};
        if (map[blender.first][blender.second] == 'E')
            next_move = {1,0}; 
        if (map[blender.first][blender.second] == 'W')
            next_move = {-1,0};

        if (map[blender.first][blender.second] == 'I') //inverter
            {
            inverter = !inverter;
            etat[2] = inverter;
            if (priority == priority1)
                priority = priority2 ;
            else priority = priority1;
            }

        if (map[blender.first][blender.second] == 'B') //breakermode
        {
            breaker = !breaker;
            etat[1] = breaker;
        }
        if (map[blender.first][blender.second] == 'X' && breaker) //si on casse un mur
        {
            std::cerr << "on détruit un mur en : (" << blender.first << ',' << blender.second << ")\n";
            map[blender.first][blender.second] = ' ';
            std::vector<std::vector<std::pair<std::vector<bool>, string>>> dejavu2 (100, std::vector<std::pair<std::vector<bool>, string>> (100, std::pair<std::vector<bool>, string> {std::vector<bool> {false, false, false}, ""}));
            dejavu = dejavu2; //on reinitialise dejavu car maintenant un mur a été détruit.

        }
        
        if (map[blender.first][blender.second] == 'T')        
        {
            if (blender == teleport[0])
                blender = teleport[1];
            else blender = teleport[0];
        }

        
    }
    
    if (isloop(dejavu, blender.first, blender.second, direction, etat))
    {

        std::cerr << "position de blender : " << blender.first << ' ' << blender.second << std::endl;
        std::cout << "LOOP" << std::endl;
    }

    else
    {
        for (auto i:moves)
            std::cout << i << std::endl;
    }
}