#include <stdio.h>
struct Board
{
    int x = 0, y = 0, numofblocks = 0;
    char blocks[20] = {0};
    char board[20][20] = {{0}};
    void getboard();//get board from txt
    Board *preb = nullptr;//previous board
    void display()const;//display board
    void countblocks();//count how many kind of blocks
    bool checkblocks(char c);//use for countblocks
    bool issame(Board b);//if this board is same as b board
    void copy(Board b);//copy b board to this board
    bool operator < (const Board &b)const
    {
        for(int i = 0; i < x; i++)
        {
            for(int j = 0; j < y; j++)
            {
                if(board[i][j] < b.board[i][j])
                    return true;
            }
        }
        return false;
    }
    bool operator == (const Board &b)const
    {
        for(int i = 0; i < x; i++)
        {
            for(int j = 0; j < y; j++)
            {
                if(board[i][j] != b.board[i][j])
                    return false;
            }
        }
        return true;
    }
};

void Board::display()const
{
    for(int i = 0; i < y+2; i++)
        printf("=");
    printf("\n");
    for(int i = 0; i < x; i ++)
    {
        printf("|");
        for(int j = 0; j < y; j ++)
        {
            if(board[i][j] != '0')
                printf("%c", board[i][j]);
            else
                printf(" ");
        }
        if(i == x/2-1)
        {
            printf("\n");
        }
        else
        {
            printf("|\n");
        }
    }
    for(int i = 0; i < y+2; i++)
        printf("=");
    printf("\n");
}

void Board::getboard()
{
    FILE *fp = fopen("board.txt","r");
    fscanf(fp, "%d %d ", &x, &y);
    for(int i = 0; i < x; i ++)
    {
        for(int j = 0; j < y; j ++)
        {
            fscanf(fp,"%c ", &board[i][j]);
        }
    }
    countblocks();
}

void Board::countblocks()
{
    for(int i = 0; i < x; i ++)
    {
        for(int j = 0; j < y; j ++)
        {
            if(!checkblocks(board[i][j]) && board[i][j] != '0')
            {
                blocks[numofblocks] = board[i][j];
                numofblocks++;
            }
        }
    }
}

bool Board::checkblocks(char c)
{
    for(int i = 0; i < numofblocks; i++)
    {
        if(blocks[i] == c)
        {
            return true;
        }
    }
    return false;
}

bool Board::issame(Board b)
{
    for(int i = 0; i < x; i ++)
    {
        for(int j = 0; j < y; j ++)
        {
            if(b.board[i][j] != board[i][j])
            {
                return false;
            }
        }
    }
    return true;
}

void Board::copy(Board b)
{
    for(int i = 0; i < x; i ++)
    {
        for(int j = 0; j < y; j ++)
        {
            b.board[i][j] = this->board[i][j];
        }
    }
}
