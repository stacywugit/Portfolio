#include <stdio.h>
#include <limits>
#include <vector>
#include <time.h>
#include <map>
#include <algorithm>
class IDS
{
public:
    std::vector<Board> queue;//just to check is empty or not
    std::vector<Board> ans;//final answer of ids
    std::map<Board,int> visited;//if this board is visited
    std::map<Board,int> visited2;//if this board is visited, clear in every depth
    Board start;
    IDS(Board start)//let board in
    {
        this->start = start;
        queue.push_back(start);
    }
    void solve();//solve with ids
    std::vector<Board> possibleMoves(Board b);//possible moves of board b
    Board movethesameword(Board b, char c, char move);//move all character c
    bool allcanmove(char c, Board b, char move);//check if all character c can move or not, for movethesameword() use
    int DFS(int depth,const Board b, Board *move);//DFS
};

int IDS::DFS(int depth,const Board b, Board *move)
{
    if(depth == 0)
    {
        return 0;
    }
    int max = -1;
    std::vector<Board> temp;
    temp = possibleMoves(b);
    for (auto k = std::begin(temp); k!=std::end(temp); ++k)
    {
        if(visited[*k] == 0 && visited2[*k] == 0)
        {
            visited2[*k] = 1;
            if(k->board[(b.y-1)/2][b.x-1] == 's')
            {
                ans.push_back(*k);
                return 100;
            }
            int score = DFS(depth-1,*k, nullptr);
            if(score == 100)
            {
                ans.push_back(*k);
                return 100;
            }

        }
    }
    return max;
}

void IDS::solve()
{
    clock_t starttime, finish;
    starttime = clock();
    if (queue.empty())
    {
        printf("No board exist\n");
        return;
    }
    else
    {
        Board start_copy = start;
        for(int i = 0; true; i++)
        {
            printf("level:%d\n", i+1);
            visited2.clear();
            visited[start] = 1;
            if(DFS(i, start, &start_copy) == 100)
            {
                break;
            }
            start = start_copy;
        }
        finish = clock();
        for (auto k = ans.rbegin(); k!=ans.rend(); ++k)
        {
            k->display();
        }
    }
    double duration = (double)(finish - starttime) / CLOCKS_PER_SEC;
    printf( "total time:%f seconds\n", duration);
}

std::vector<Board> IDS::possibleMoves(Board b)
{
    std::vector<Board> path;
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
            if(j > 1 && b.board[i][j-1] == '0' && b.board[i][j] != '0')//can move left
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

Board IDS::movethesameword(Board b, char c, char move)
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

bool IDS::allcanmove(char c, Board b, char move)
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
