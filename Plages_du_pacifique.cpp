#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <set>

/*
On vous donne en paramètre un tableau d'entiers 2D, contenant uniquement des 0 ou des 1.
Les 0 correspondent à des zones remplies d'eau, et les 1 correspondent à des zones remplies de terre.
 Ce tableau contient une île unique, c'est-à-dire une zone de 1 entourée de 0.
 On peut aller de toute case de cette île à n'importe-quelle autre en se déplaçant uniquement
 sur des cases de terre, et en ne passant d'une case à l'autre que si les deux cases sont adjacentes
 (ont un côté commun).

Vous devez écrire une fonction qui calcule le nombre de plages de cette île,
c'est-à dire le nombre de cases de terre, qui touchent une case de l'océan.
Par toucher, on entend être adjacent (avoir un côté commun).

A l'intérieur de l'île peuvent se trouver des lacs, c'est-à-dire des zones d'eau entièrement
entourées de terre : on peut en faire le tour en ne se déplaçant que sur des cases de terre.
Une case de terre qui se trouve au bord du lac, mais ne touche pas l'océan ne doit pas être
considérée comme une plage.

Attention, une case d'eau qui touche une case d'océan en diagonale,
est également considérée comme une case d'océan, et non un lac :
il est impossible d'en faire le tour en ne se déplaçant qu'horizontalement et verticalement.

L'île est toujours entièrement entourée d'eau. Les cases sur le bord du tableau sont donc
toutes des cases d'eau, qui font partie de l'océan.

CONTRAINTES

1 \<= L, H \<= 100, où L et H sont la largeur et la hauteur du tableau décrivant la zone..
ENTREE

La première ligne de l'entrée contient deux nombres : L, et H : la largeur et la hauteur du
tableau décrivant la zone où se trouve l'île.

Les H lignes suivantes décrivent H lignes du tableau, sous la forme de L chiffres (0 ou 1),
sans espaces.

SORTIE

Vous devez écrire une ligne sur la sortie :

Le nombre de plages de l'île.
*/

/*
Réflexions : il faut identifier ce qui est ocean de ce qui est lac. Pour cela : on parcourt la grille et tout ce qui touche l'ocean et qui est de l'eau est ocean
(y compris en diagonal). La question : vaut-il mieux en même temps voir pour les plages ? (a priori oui car on fait des tests sur l'eau. -> en fait non car il faut revenir en arrière)


Attention : comment on fait pour éviter de compter plusieurs fois une plage ?? -> en changeant les éléments


*/


int main ()
{
    bool debug_carte = false;
    bool debug_carte_fin = true;
    bool debug_creation = false;
    int L; int H;
    std::cin >> L >> H ;
    int carte [L][H];
    // creation de la carte
    for (int i=0; i < H ; i++)
    {
        std::string ligne;
        std::cin >> ligne ;
        for (int j=0; j<L ; j++)
        {
            carte[j][i] = ligne[j] - 48;
            if (debug_creation) std::cerr << carte[j][i];
        }
        if (debug_creation) std::cerr << std::endl;
    }
    int nombre_plage = 0;
    // parcours de la carte : si océan 0 -> 3 
    carte[0][0] = 3; carte[L-1][H-1] = 3;
    bool changement=true;

    for (int i=0; i<L; i++)
    {
        for (int j=0; j<H ; j++)
        {
            if (carte[i][j] != 3) continue;
            // tests ocean
            for (int k : {-1, 0, 1})
            {
                for (int l : {-1, 0, 1})
                {
                    if (k+i >= 0 && l+j >= 0 && k+i <L && l+j < H && carte[i+k][j+l] == 0) carte[i+k][j+l] = 3;
                }
            }
        }
    }
    for (int i=L-1; i>=0; i--)
    {
        for (int j=H-1; j >=0 ; j--)
        {
            if (carte[i][j] != 3) continue;
            // tests ocean
            for (int k : {-1, 0, 1})
            {
                for (int l : {-1, 0, 1})
                {
                    if (k+i >= 0 && l+j >= 0 && k+i <L && l+j < H && carte[i+k][j+l] == 0) carte[i+k][j+l] = 3;
                }
            }
        }
    }
    carte[0][0] = 3; carte[L-1][H-1] = 3;
    for (int i=0; i<L; i++)
    {
        for (int j=0; j<H ; j++)
        {
            if (carte[i][j] != 3) continue;
            // tests ocean
            for (int k : {-1, 0, 1})
            {
                for (int l : {-1, 0, 1})
                {
                    if (k+i >= 0 && l+j >= 0 && k+i <L && l+j < H && carte[i+k][j+l] == 0) carte[i+k][j+l] = 3;
                }
            }
        }
    }
    if (debug_carte) 
    {
        for (int i=0; i<H; i++)
        {
            for (int j=0; j<L ; j++)
            {
                std::cerr << carte[j][i];
            }
            std::cerr << std::endl;
        }
    }
    // tests plages si plage 1 -> 4 et on compte.
    for (int i=0; i<L; i++)
    {
        for (int j=0; j<H ; j++)
        {
            if (carte[i][j] != 3) continue;
            if (i+1 < L && carte[i+1][j] == 1)
            {
                carte[i+1][j] = 4;
                nombre_plage +=1;
            }
            if (j+1 < H && carte[i][j+1] == 1)
            {
                carte[i][j+1] = 4;
                nombre_plage +=1;
            }
            if (i > 0 && carte[i-1][j] == 1)
            {
                carte[i-1][j] = 4;
                nombre_plage +=1;
            }
            if (j > 0 && carte[i][j-1] == 1)
            {
                carte[i][j-1] = 4;
                nombre_plage +=1;
            }
        }
    }
    if (debug_carte_fin) 
    {
        for (int i=0; i<H; i++)
        {
            for (int j=0; j<L ; j++)
            {
                std::cerr << carte[j][i];
            }
            std::cerr << std::endl;
        }
    }
    std::cout << nombre_plage << std::endl;
}


