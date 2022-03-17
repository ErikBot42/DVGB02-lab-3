#include "prog3.h"
#include "common.h"

struct distance_table {
    int costs[4][4];
} dt1;


/* students to write the following two routines, and maybe some others */

void printdt1(struct distance_table *dtptr)
{
    printf("             via   \n");
    printf("   D1 |    0     2 \n");
    printf("  ----|-----------\n");
    printf("     0|  %3d   %3d\n", dtptr->costs[0][0], dtptr->costs[0][2]);
    printf("dest 2|  %3d   %3d\n", dtptr->costs[2][0], dtptr->costs[2][2]);
    printf("     3|  %3d   %3d\n", dtptr->costs[3][0], dtptr->costs[3][2]);

}

void rtinit1()
{
    for (int i = 0; i<4; i++) {
        for (int j = 0; j<4; j++) {
            dt1.costs[i][j] = 999;
        }
    }
    dt1.costs[0][1] = 1; 
    dt1.costs[1][1] = 0; 
    dt1.costs[2][1] = 1; 
    dt1.costs[3][1] = 999; 
    
    printdt1(&dt1);


    makeAndSendPacket(1, 1, dt1.costs);
    makeAndSendPacket(1, 2, dt1.costs);
    makeAndSendPacket(1, 3, dt1.costs);
}


void rtupdate1(struct rtpkt *rcvdpkt)
{
    if (rtupdate_all(rcvdpkt, &dt1.costs, 0))
    {
        makeAndSendPacket(1, 1, dt1.costs);
        makeAndSendPacket(1, 2, dt1.costs);
        makeAndSendPacket(1, 3, dt1.costs);
    }
}




/* called when cost from 1 to linkid changes from current value to newcost*/
/* You can leave this routine empty if you're an undergrad. If you want */
/* to use this routine, you'll need to change the value of the LINKCHANGE */
/* constant definition in prog3.c from 0 to 1 */
void linkhandler1(int linkid, int newcost)
{
}
