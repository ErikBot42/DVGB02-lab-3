#include "common.h"


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


// row: dest 
// col: source
// rval: costs have changed
bool updateCosts(int (*costs)[4][4], int update_col) {
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


bool rtupdate_all(struct rtpkt *pkt, int (*costs)[4][4], int node_id) {
    if (pkt->destid!=node_id) {printf("invalid recived id"); exit(1);}  
        
    for (int i = 0; i<vert; i++) {
        (*costs)[pkt->sourceid][i] = pkt->mincost[i];
    }
    return updateCosts(costs, node_id);
}







