#include "board.h"
#include <stdio.h>
#include "ids.h"
#include "idastar.h"
int main()
{
    std::map<Board,int> b;
    Board board;
    board.getboard();
    int choosesolver = 0;
    board.display();
    while(choosesolver != -1)
    {
        printf("1)使用IDS 2)使用IDA* -1)退出...>");
        scanf("%d", &choosesolver);
        if(choosesolver == 1)
        {
            printf("ids:\n");
            IDS problem = IDS(board);
            problem.solve();
        }
        else if(choosesolver == 2)
        {
            printf("ida*:\n");
            IDASTAR problem = IDASTAR(board);
            problem.solve();
        }
    }

    return 0;
}
