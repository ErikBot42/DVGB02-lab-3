#include "prog3.h"
#include "common.h"

struct distance_table {
    int costs[4][4];
} dt2;


/* students to write the following two routines, and maybe some others */

void printdt2(struct distance_table *dtptr)
{
    printMatrix(dtptr->costs, 2);
    //printf("                via     \n");
    //printf("   D2 |    0     1    3 \n");
    //printf("  ----|-----------------\n");
    //printf("     0|  %3d   %3d   %3d\n", dtptr->costs[0][0],
    //       dtptr->costs[0][1], dtptr->costs[0][3]);
    //printf("dest 1|  %3d   %3d   %3d\n", dtptr->costs[1][0],
    //       dtptr->costs[1][1], dtptr->costs[1][3]);
    //printf("     3|  %3d   %3d   %3d\n", dtptr->costs[3][0],
    //       dtptr->costs[3][1], dtptr->costs[3][3]);
}

void rtinit2()
{
    for (int i = 0; i<4; i++) {
        for (int j = 0; j<4; j++) {
            dt2.costs[i][j] = 999;
        }
    }
    dt2.costs[0][2] = 3; 
    dt2.costs[1][2] = 1; 
    dt2.costs[2][2] = 0; 
    dt2.costs[3][2] = 2; 
    printdt2(&dt2);
    makeAndSendPacket(2, 0, dt2.costs);
    makeAndSendPacket(2, 1, dt2.costs);
    makeAndSendPacket(2, 3, dt2.costs);
}


void rtupdate2(struct rtpkt *rcvdpkt)
{
    printf("\033[1;33mRTUPDATE2");
    printdt2(&dt2);

    if (rtupdate_all(rcvdpkt, &dt2.costs, 2))
    {
        makeAndSendPacket(2, 0, dt2.costs);
        makeAndSendPacket(2, 1, dt2.costs);
        makeAndSendPacket(2, 3, dt2.costs);
    }
    printdt2(&dt2);
    printf("-----\n\033[0m");
}


