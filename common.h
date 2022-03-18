
#ifndef COMMON_H
#define COMMON_H

#include "prog3.h"
#include <stdbool.h>
#define vert 4

void makeAndSendPacket(int from, int to, int costs[4][4]);
bool updateCosts(int (*costs)[4][4], int update_col);
bool rtupdate_all(struct rtpkt *pkt, int (*costs)[4][4], int node_id);
void printMatrix(int costs[4][4], int node);

// create and send packet from given costs, source, destination
#endif //COMMON_H
