#include <iostream>
#include <vector>
using namespace std;

pair<int, int> cord;
vector<vector<char>> matrix(3, vector<char>(3, ' '));
bool draw = false;

pair<int, int> getAIMoveAttack(char user, char ai)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (matrix[i][j % 3] == ai && matrix[i][(j + 1) % 3] == ai && matrix[i][(j + 2) % 3] == ' ')
                return {i, (j + 2) % 3};
            if (matrix[j % 3][i] == ai && matrix[(j + 1) % 3][i] == ai && matrix[(j + 2) % 3][i] == ' ')
                return {(j + 2) % 3, i};
        }
    }

    for (int i = 0; i < 3; i++)
    {
        if (matrix[i % 3][i % 3] == ai && matrix[(i + 1) % 3][(i + 1) % 3] == ai && matrix[(i + 2) % 3][(i + 2) % 3] == ' ')
            return {(i + 2) % 3, (i + 2) % 3};
        if (matrix[i % 3][2 - i % 3] == ai && matrix[(i + 1) % 3][2 - (i + 1) % 3] == ai && matrix[(i + 2) % 3][2 - ((i + 2) % 3)] == ' ')
            return {(i + 2) % 3, 2 - ((i + 2) % 3)};
    }
    return {-1, -1};
}

pair<int, int> getAIMoveDefence(char user, char ai)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (matrix[i][j % 3] == user && matrix[i][(j + 1) % 3] == user && matrix[i][(j + 2) % 3] == ' ')
                return {i, (j + 2) % 3};
            if (matrix[j % 3][i] == user && matrix[(j + 1) % 3][i] == user && matrix[(j + 2) % 3][i] == ' ')
                return {(j + 2) % 3, i};
        }
    }

    for (int i = 0; i < 3; i++)
    {
        if (matrix[i % 3][i % 3] == user && matrix[(i + 1) % 3][(i + 1) % 3] == user && matrix[(i + 2) % 3][(i + 2) % 3] == ' ')
            return {(i + 2) % 3, (i + 2) % 3};
        if (matrix[i % 3][2 - i % 3] == user && matrix[(i + 1) % 3][2 - (i + 1) % 3] == user && matrix[(i + 2) % 3][2 - ((i + 2) % 3)] == ' ')
            return {(i + 2) % 3, 2 - ((i + 2) % 3)};
    }

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (matrix[1][1] == ' ')
                return {1, 1};
            else if (matrix[i][j] == ai && i < 3 && matrix[i + 1][j] == ' ')
                return {i + 1, j};
            else if (matrix[i][j] == ai && i < 3 && matrix[i][j + 1] == ' ')
                return {i, j + 1};
            else if (matrix[i][j] == ' ')
                return {i, j};
        }
    }
}
pair<int, int> getAIMoveEasy(char user, char ai)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (matrix[1][1] == ' ')
                return {1, 1};
            else if (matrix[i][j] == ai && i < 3 && matrix[i + 1][j] == ' ')
                return {i + 1, j};
            else if (matrix[i][j] == ai && i < 3 && matrix[i][j + 1] == ' ')
                return {i, j + 1};
            else if (matrix[i][j] == ' ')
                return {i, j};
        }
    }
}
bool check(char s, char r)
{
    if ((matrix[0][0] == s && matrix[2][2] == s && matrix[1][1] == s) || (matrix[2][0] == s && matrix[0][2] == s && matrix[1][1] == s) || (matrix[0][0] == r && matrix[2][2] == r && matrix[1][1] == r) || (matrix[2][0] == r && matrix[0][2] == r && matrix[1][1] == r))
        return true;

    for (int i = 0; i < 3; i++)
    {
        int k = 0, l = 0, K = 0, L = 0;
        for (int j = 0; j < 3; j++)
        {
            if (matrix[i][j] == s)
                k++;
            if (matrix[j][i] == s)
                l++;
            if (matrix[i][j] == r)
                K++;
            if (matrix[j][i] == r)
                L++;
        }
        if (k == 3 || l == 3 || K == 3 || L == 3)
            return true;
    }
    return false;
}

void setColor(char symbol)
{
    switch (symbol)
    {
    case 'X':
        cout << "\033[1;31m";
        break;
    case 'O':
        cout << "\033[1;34m";
        break;
    default:
        cout << "\033[0m";
    }
}

void print()
{
    cout << "  1 2 3" << endl;
    cout << " -------" << endl;

    for (int i = 0; i < 3; i++)
    {
        cout << i + 1 << "|";

        for (int j = 0; j < 3; j++)
        {
            setColor(matrix[i][j]);
            cout << matrix[i][j] << " ";
            cout << "\033[0m";
        }
        cout << endl;
    }

    cout << " -------" << endl;
}

int main()
{
    int a, b, input = 0;
    char zero = 'O', cross = 'X', current, opp;
    cout << "please select the game mode  \n1) easy \n2) hard " << endl;
    cin >> b;
    cout << "please input your choice \n1) zero \n2) cross " << endl;
    cin >> a;
    if (a == 1)
    {
        current = zero;
        opp = cross;
    }
    else
    {
        current = cross;
        opp = zero;
    }
    while (!draw)
    {
        int x, y;
        cout << "please input the cordinates " << endl;
        cin >> x >> y;
        if (matrix[--x][--y] != ' ')
        {
            cout << "space already occupied" << endl;
            print();
        }
        else
        {
            if (x > 3 || y > 3)
                cout << "input valid cordinates" << endl;
            else
            {
                matrix[x][y] = current;
                if (b == 2)
                {
                    cord = getAIMoveAttack(current, opp);
                    if (cord == make_pair(-1, -1))
                    {
                        cord = getAIMoveDefence(current, opp);
                    }
                }
                else
                {
                    cord = getAIMoveEasy(current, opp);
                }
                matrix[cord.first][cord.second] = opp;
                print();
                ++input;
            }
            if (check(current, opp))
            {
                cout << "\nPlay Again ?" << endl;
                return 0;
            }
            if (input > 4)
                draw = true;
        }
    }
    cout << "Game Draw" << endl;
}