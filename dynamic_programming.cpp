#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <numeric>
#include <cmath>
#include <deque>
// Problème 1
std::vector<int> sum_values;

void startup(const std::vector<int> &values)
{
    // condition : values doit contenir des valeurs;
    if (values.size()==0)
        return ;
    
    // initialisation
    sum_values.emplace_back(values[0]);

    // sum_values[i] -> la somme des toutes les valeurs jusqu'à la valeur i incluse
    for (int i =1; i < values.size(); i++)
    {
        sum_values.emplace_back(sum_values.back() + values[i]);
    }
}

int sum_partial(int i, int j) // sum(values[i], values[i+1] ... + values[j])
{
    if (i >= sum_values.size() || j >= sum_values.size() || i <0 || j<0 || i > j)
        return 0;
    
    if (i==0)
        return sum_values[j];

    return sum_values[j]-sum_values[i-1]; // on utilise i-1 car values[i] doit être incluse
}


// Problème 1.1
std::vector<std::vector<int>> sum_matrix; // sum_matrix[i][j] -> somme de la matrice 0->i 0->j
void startup_1_1(const std::vector<std::vector<int>> &matrix_values)
{
    sum_matrix[0][0]=matrix_values[0][0];
    
    for (int i = 0; i < matrix_values.size(); i++)
    {
        if (i+1 > matrix_values.size())
            continue;
        sum_matrix[i+1][0] = sum_matrix[i][0]+matrix_values[i+1][0];
    }
    
    for (int j = 0; j < matrix_values[0].size(); j++)
    {
        if (j+1 > matrix_values[0].size())
            continue;
        sum_matrix[0][j+1] = sum_matrix[0][j]+matrix_values[0][j+1];
    }
    
    for (int i = 1; i < matrix_values.size(); i++)
    {
        for (int j = 1; j < matrix_values[i].size(); j++)
        {
              if (i+1 > matrix_values.size() || j+1 > matrix_values[i].size())
                  continue;
              sum_matrix[i][j+1] = 
                  matrix_values[i][j+1]
                + sum_matrix[i][j]
                + sum_matrix[i-1][j+1]
                - sum_matrix[i-1][j-1];
        }
    }
}

int sum_partial_1_1(int i1, int i2, int j1, int j2)
{
    int max_i = sum_matrix.size()-1;
    int max_j = sum_matrix[0].size()-1;
    i1 = std::clamp(i1, 0, max_i);
    i2 = std::clamp(i2, 0, max_i);
    j1 = std::clamp(j1, 0, max_j);
    j2 = std::clamp(j2, 0, max_j);
    if (i1 > i2) std::swap(i1,i2);
    if (j1 > j2) std::swap(j1,j2);

    if (i1==0)
    {
        if (j1==0)
            return sum_matrix[i2][j2];
        return sum_matrix[i2][j2]- sum_matrix[i2][j1-1];
    }
    if (j1==0)
        return sum_matrix[i2][j2] - sum_matrix[i1-1][j2];
    return sum_matrix[i2][j2] - sum_matrix[i1-1][j2] - sum_matrix[i2][j1-1] - sum_matrix[i1-1][j1-1];
}


//probleme 2

int optimum_repartition(std::vector<int> word_length, int line_witdth)
{
    std::deque<int> deque;
    for (int i : word_length)
        deque.emplace_back(i);
    return optimum_repartition_deque(deque, line_witdth);
}

int optimum_repartition_deque(std::deque<int> word_length, int line_witdth)
{
    int line_size =0 ;
    int square_sum = std::numeric_limits<int>::max();
    for (int i=0; i < line_witdth; i++)
    {
        if (line_size > line_witdth)
            continue;
        if (i >= word_length.size())
            continue;

        line_size += word_length[0]+1;
        word_length.pop_front();

        int sum_reste = optimum_repartition_deque(word_length, line_witdth);
        if (sum_reste+pow(line_size,2) < square_sum)
            square_sum = sum_reste+pow(line_size,2);
    }
    
    return square_sum;
    
}


int dyn_optimum_repartition(std::vector<int> word_length, int line_width)
{
// matrice : mat[i][j] correspond à la longueur des mots entre i et i+j
    std::vector<std::vector<int>> matrix(word_length.size(), std::vector<int> (word_length.size(), std::numeric_limits<int>::max()));
    int line_size =0;
    matrix[0][0] = word_length[0];
    for (int i=0; i < word_length.size()-1; i++)
    {
        for (int j=0; j < word_length.size()-i-1; j++)
        {
            if (i==0 && j==0)
                continue;
            matrix[i][j+1] = matrix[i][j]+word_length[i+j]+1;
            matrix[i+1][j] = matrix[i][j+1]-word_length[i]+1;
        }
    }
    std::vector<int> c;
    c.emplace_back(0);
    for (int i=0; i < word_length.size(); i++)
    {
        int c_temp = std::numeric_limits<int>::max();
        for (int j=0 ; j < i ; j++)
        {
            if (matrix[i-j][j] > line_width)
                continue;
            int cout = c[i-j-1]+(line_width - matrix[i-j-1][j])*(line_width - matrix[i-j-1][j]);
            c_temp = std::min(c_temp, cout);
        }
        c.emplace_back(c_temp);
    }

    return c.back();

}   
