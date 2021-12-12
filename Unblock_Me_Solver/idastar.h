#include <stdio.h>
#include <limits>
#include <vector>
#include <time.h>
#include <queue>
#include <map>
#include <algorithm>
#include <cmath>
std::map<Board, int> cost;
class IDASTAR
{
public:
    std::vector<Board> queue;
    Board start;
    Board *ans;
    IDASTAR(Board start)
    {
        this->start = start;
        queue.push_back(start);
    }
    void solve();
    std::vector<Board> possibleMoves(Board b);
    Board movethesameword(Board b, char c, char move);
    bool found(char c, char blockfound[], int *num);
    bool allcanmove(char c, Board b, char move);
    int ASTAR(int flimit, int depth, Board b);
    int h(Board a);
    int search(Board *node,int g, int bound);
};

int IDASTAR::h(Board a)
{
    int h = 0;
    int asx, asy;
    for(int i = 0; i < a.x; i++)//find where is s
    {
        for(int j = 0; j < a.y; j++)
        {
            if(a.board[i][j] == 's')
            {
                asx = i;
                asy = j+1;
            }
        }
    }
    for(int i = asy; i < a.y; i++)
    {
        if(a.board[asx][i] == '0')
        {
            h += 1;
        }
        else
        {
            h += 2;
        }
    }
    for(int i = asy-1; i < a.y-1; i++)
    {
        if(a.board[asx][i] == '0')
        {
            h += 1;
        }
        else
        {
            h += 2;
        }
    }
    if(asx < (a.x-1)/2)
    {
        for(int i = asx; i < (a.x-1)/2; i++)
        {
            if(a.board[i][a.y-1] == '0')
            {
                h += 1;
            }
            else
            {
                h += 2;
            }
        }
        for(int i = asx; i < (a.x-1)/2; i++)
        {
            if(a.board[i][a.y-2] == '0')
            {
                h += 1;
            }
            else
            {
                h += 2;
            }
        }
    }
    else
    {
        for(int i = (a.x-1)/2; i < asx; i++)
        {
            if(a.board[i][a.y-1] == '0')
            {
                h += 1;
            }
            else
            {
                h += 2;
            }
        }
        for(int i = (a.x-1)/2; i < asx; i++)
        {
            if(a.board[i][a.y-2] == '0')
            {
                h += 1;
            }
            else
            {
                h += 2;
            }
        }
    }
    return h;
}

void IDASTAR::solve()
{
    clock_t starttime, finish;
    starttime = clock();
    int bound = h(start);
    int t;
    for(int i = 0; true; i++)
    {
        printf("layer:%d\n",i+1);
        t = search(&start, 0, bound);
        if(t == -1)break;
        bound = t;
    }
    finish = clock();
    std::vector<Board*> result;
    while(ans->preb != nullptr)
    {
        result.push_back(ans);
        ans = ans->preb;
    }
    for(int i = result.size()-1; i >= 0; i--)
    {
        result[i]->display();
    }
    double duration = (double)(finish - starttime) / CLOCKS_PER_SEC;
    printf( "total time:%f seconds\n", duration);
}

struct myclass {
  bool operator() (Board i,Board j) { return (cost[i]<cost[j]);}
} myobject;

int IDASTAR::search(Board *node,int g, int bound)
{
    int f = g + h(*node);
    if(f > bound) return f;
    if(node->board[(node->y-1)/2][node->x-1] == 's')
    {
        ans = node;
        return -1;
    }
    int min = 10000;
    std::vector<Board> temp;
    temp = possibleMoves(*node);
    for(int i = 0; i < temp.size(); i++)
    {
        cost[temp[i]] = 1 + h(temp[i]);
    }
    std::sort(temp.begin(), temp.end(), myobject);
    int t;
    for(int i = 0; i < temp.size(); i++)
    {
        temp[i].preb = node;
        t = search(&temp[i], g+h(temp[i]), bound);
        if(t == -1) return -1;
        if(t < min) min = t;
    }
    return min;
}

std::vector<Board> IDASTAR::possibleMoves(Board b)
{
    std::vector<Board> path;
    char blockfound[20];
    int numofblock = 0;
    Board tempBoard;
    for(int i = 0; i < b.x; i++)
    {
        for(int j = 0; j < b.y; j++)
        {
            if(j <= b.y-2 && b.board[i][j+1] == '0' && b.board[i][j] != '0')//can right move
            {
                tempBoard = movethesameword(b, b.board[i][j],'r');
                path.push_back(tempBoard);
            }
            if(j >= 1 && b.board[i][j-1] == '0' && b.board[i][j] != '0')//can move left
            {
                tempBoard = movethesameword(b, b.board[i][j],'l');
                path.push_back(tempBoard);
            }
            if(i >= 1 && b.board[i-1][j] == '0' && b.board[i][j] != '0')//can move up
            {
                tempBoard = movethesameword(b, b.board[i][j],'u');
                path.push_back(tempBoard);
            }
            if(i <= b.x-2 && b.board[i+1][j] == '0' && b.board[i][j] != '0')//can move down
            {
                tempBoard = movethesameword(b, b.board[i][j],'d');
                path.push_back(tempBoard);
            }
        }
    }
    for(int i = 0; i < path.size(); i++)
    {
        for(int j = path.size()-1; j > i; j--)
        {
            if(path[i].issame(path[j]))
            {
                path.erase(path.begin()+j);
            }
        }
    }
    return path;
}

Board IDASTAR::movethesameword(Board b, char c, char move)
{
    if(allcanmove(c, b, move))
    {
        if(move == 'r')
        {
            for(int i = 0; i < b.x; i++)
            {
                for(int j = b.y-2; j >= 0; j--)
                {
                    if(b.board[i][j] == c)
                    {
                        b.board[i][j+1] = b.board[i][j];
                        b.board[i][j] = '0';
                    }
                }
            }
        }
        else if(move == 'l')
        {
            for(int i = 0; i < b.x; i++)
            {
                for(int j = 0; j < b.y; j++)
                {
                    if(b.board[i][j] == c)
                    {
                        b.board[i][j-1] = b.board[i][j];
                        b.board[i][j] = '0';
                    }

                }
            }
        }
        else if(move == 'u')
        {
            for(int i = 0; i < b.x; i++)
            {
                for(int j = 0; j < b.y; j++)
                {
                    if(b.board[i][j] == c)
                    {
                        b.board[i-1][j] = b.board[i][j];
                        b.board[i][j] = '0';
                    }
                }
            }
        }
        else if(move == 'd')
        {
            for(int i = b.x-2; i >= 0; i--)
            {
                for(int j = 0; j < b.y; j++)
                {
                    if(b.board[i][j] == c)
                    {
                        b.board[i+1][j] = b.board[i][j];
                        b.board[i][j] = '0';
                    }
                }
            }
        }
    }
    return b;
}

bool IDASTAR::found(char c, char blockfound[], int *num)
{
    for(int i = 0; i < (*num); i++)
    {
        if(c == blockfound[i])
        {
            return true;
        }
    }
    blockfound[(*num)] = c;
    (*num)++;
    return false;
}

bool IDASTAR::allcanmove(char c, Board b, char move)
{
    if(move == 'r')
    {
        for(int i = 0; i < b.x; i++)
        {
            for(int j = b.y-2; j >= 0; j--)
            {
                if(b.board[i][j] == c)
                {
                    if(b.board[i][j+1] != c && b.board[i][j+1] != '0')
                        return false;
                }
            }
        }
    }
    else if(move == 'l')
    {
        for(int i = 0; i < b.x; i++)
        {
            for(int j = 0; j < b.y; j++)
            {
                if(b.board[i][j] == c)
                {
                    if(b.board[i][j-1] != c && b.board[i][j-1] != '0')
                        return false;
                }

            }
        }
    }
    else if(move == 'u')
    {
        for(int i = 0; i < b.x; i++)
        {
            for(int j = 0; j < b.y; j++)
            {
                if(b.board[i][j] == c)
                {
                    if(b.board[i-1][j] != c && b.board[i-1][j] != '0')
                        return false;
                }
            }
        }
    }
    else if(move == 'd')
    {
        for(int i = b.x-2; i >= 0; i--)
        {
            for(int j = 0; j < b.y; j++)
            {
                if(b.board[i][j] == c)
                {
                    if(b.board[i+1][j] != c && b.board[i+1][j] != '0')
                        return false;
                }
            }
        }
    }
    return true;
}

