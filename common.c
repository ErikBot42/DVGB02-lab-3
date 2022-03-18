#include "common.h"


/*
start:
0 1 3 7
1 0 1 -
3 1 0 2
7 - 2 0


slut:
0 1 2 4
1 0 1 3
2 1 0 2
4 3 2 0


node 0:
0 1 -
1 0 2
- 2 0


node 1:
0 2
2 0
4 2

node 2:
0 1 3
1 0 3
4 3 0

node 3:
0 2
1 1
2 0

 * */

// costs[TO][FROM]

void makeAndSendPacket(int from, int to, int costs[4][4])
{
    struct rtpkt pkt;
    pkt.sourceid = from;
    pkt.destid = to;

    pkt.mincost[0] = costs[0][from];
    pkt.mincost[1] = costs[1][from];
    pkt.mincost[2] = costs[2][from];
    pkt.mincost[3] = costs[3][from];

    tolayer2(pkt);
}

void printMatrix(int costs[4][4], int node)
{
    printf("\n   D%d |    0    1    2    3 \n", node);
    printf("------|---------------------\n", node);
    printf("     0|  %3d  %3d  %3d  %3d \n", costs[0][0], costs[0][1], costs[0][2], costs[0][3]);
    printf("     1|  %3d  %3d  %3d  %3d \n", costs[1][0], costs[1][1], costs[1][2], costs[1][3]);
    printf("     2|  %3d  %3d  %3d  %3d \n", costs[2][0], costs[2][1], costs[2][2], costs[2][3]);
    printf("     3|  %3d  %3d  %3d  %3d \n", costs[3][0], costs[3][1], costs[3][2], costs[3][3]);
}


// row: dest 
// col: source
// rval: costs have changed
bool updateCosts(int (*costs)[4][4], const int update_col) {
    bool rval = false;
    for (int i = 0; i<vert; i++) {
        for (int j = 0; j<vert; j++) {
            const int k = update_col;
            const int d = (*costs)[i][k];
            const int d_new = (*costs)[i][j] + (*costs)[j][k];
            if (d_new < d) {
                (*costs)[i][k] = d_new;
                rval = true;
            }
        }
    }
    return rval;
}

bool check_symmetric(int (*costs)[4][4]) {
    for (int i = 0; i<vert; i++) {
        for (int j = 0; j<vert; j++) {
            if ((*costs)[i][j] != (*costs)[j][i]) {
                if ((*costs)[i][j] > (*costs)[j][i]) {
                    (*costs)[i][j]=(*costs)[j][i];
                }
                else {
                    (*costs)[j][i]=(*costs)[i][j];

                }

                return false;
            }
        }
    }
    return true;
}

bool rtupdate_all(struct rtpkt *pkt, int (*costs)[4][4], const int node_id) {
    if (pkt->destid!=node_id) {printf("invalid recived id"); exit(1);}  
    if (pkt->sourceid==node_id) {printf("sent packet to self"); exit(1);}  
    

    bool rval = false;
    for (int i = 0; i<vert; i++) {
        const int new = pkt->mincost[i];
        const int old = (*costs)[pkt->sourceid][i];

        if (new > old) {
            rval = true;
            //printf("cost was increased for node %d (from %d to %d) with packet from %d to %d", node_id, old, new, pkt->sourceid, pkt->destid);
            //exit(1);
        }
        if (new < old) {
            (*costs)[pkt->sourceid][i] = pkt->mincost[i];
            rval = true;
        }
    }
    updateCosts(costs, node_id);
    check_symmetric(costs);
    return rval;
}







