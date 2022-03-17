#include "prog3.h"
#include "common.h"


struct distance_table {
    int costs[4][4];
} dt3;


/* students to write the following two routines, and maybe some others */

void printdt3(struct distance_table *dtptr)
{
    printf("             via     \n");
    printf("   D3 |    0     2 \n");
    printf("  ----|-----------\n");
    printf("     0|  %3d   %3d\n", dtptr->costs[0][0], dtptr->costs[0][2]);
    printf("dest 1|  %3d   %3d\n", dtptr->costs[1][0], dtptr->costs[1][2]);
    printf("     2|  %3d   %3d\n", dtptr->costs[2][0], dtptr->costs[2][2]);

}

void rtinit3()
{
    for (int i = 0; i<4; i++) {
        for (int j = 0; j<4; j++) {
            dt3.costs[i][j] = 999;
        }
    }
    dt3.costs[0][3] = 7; 
    dt3.costs[1][3] = 999; 
    dt3.costs[2][3] = 2; 
    dt3.costs[3][3] = 0; 
    printdt3(&dt3);


    makeAndSendPacket(3, 0, dt3.costs);
    makeAndSendPacket(3, 2, dt3.costs);
}


void rtupdate3(struct rtpkt *rcvdpkt)
{
    printf("\033[0;31mRTUPDATE3");
    printdt3(&dt3);
    if (rtupdate_all(rcvdpkt, &dt3.costs, 3))
    {
        makeAndSendPacket(3, 0, dt3.costs);
        makeAndSendPacket(3, 2, dt3.costs);
    }
    printdt3(&dt3);
    printf("-----\n\033[0m");
}


