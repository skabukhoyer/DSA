#include <iostream>
#include <vector>
#include <string>
#include<algorithm>
using namespace std;

bool dfs(vector<vector<char>> grid, int r, int c, int i, int j, string word, int index)
{
    int len = word.size();
    if (index >= len)
    {
        return true;
    }

    bool var = false;
    char ch;
    if (j + 1 < c and word[index] == grid[i][j + 1])
    {
        ch = grid[i][j + 1];
        grid[i][j + 1] = '@';
        var = dfs(grid, r, c, i, j + 1, word, index + 1);
        grid[i][j + 1] = ch;
    }
    if (var)
        return true;
    if (i + 1 < r and word[index] == grid[i + 1][j])
    {
        ch = grid[i + 1][j];
        grid[i + 1][j] = '@';
        var = dfs(grid, r, c, i + 1, j, word, index + 1);
        grid[i + 1][j] = ch;
    }
    if (var)
        return true;
    if (j - 1 >= 0 and word[index] == grid[i][j - 1])
    {
        ch = grid[i][j - 1];
        grid[i][j - 1] = '@';
        var = dfs(grid, r, c, i, j - 1, word, index + 1);
        grid[i][j - 1] = ch;
    }
    if (var)
        return true;
    if (i - 1 >= 0 and word[index] == grid[i - 1][j])
    {
        ch = grid[i - 1][j];
        grid[i - 1][j] = '@';
        var = dfs(grid, r, c, i - 1, j, word, index + 1);
        grid[i - 1][j] = ch;
    }

    return var;
}
bool exist(vector<vector<char>> &grid, string word)
{
    vector<vector<int>> out;
    int c = grid[0].size();
    int r = grid.size();
    vector<int> v(2, 0);
    char ch;
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            if (grid[i][j] == word[0])
            {
                ch = grid[i][j];
                grid[i][j] = '@';
                if (dfs(grid, r, c, i, j, word, 1))
                {
                    grid[i][j] = ch;
                    return true;
                }
                grid[i][j] = ch;
            }
        }
    }
    return false;
}

int main()
{
    int row, col;
    cin >> row >> col;
    vector<vector<char>> grid(row, vector<char>(col));
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
            cin >> grid[i][j];
    }
    int x;
    cin >> x;
    vector<string> listWord(x, "");
    for (int i = 0; i < x; i++)
        cin >> listWord[i];
    sort(listWord.begin(),listWord.end());
    for(int i=0;i<x;i++){
        //cout<<listWord[i]<<endl;
        if(exist(grid,listWord[i]))
            cout<<listWord[i]<<" ";
        
    }
    return 0;
}
