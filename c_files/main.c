#include "../headers/inout.h"
#include "../headers/constants.h"
#include <stdio.h>
#include <stdlib.h>

double packet_delay(int numPackets, int* packets, int numLinks, struct Link *links) {
    double packet_delay = 0;
    for (int i = 0; i < numLinks; ++i) {
        double prop_delay = (double) links[i].length / links[i].prop_speed;
        double trans_delay = (double) packets[0] / links[i].bitrate;
        packet_delay += (prop_delay + trans_delay) * 1000;
    }
    return packet_delay;
}

int main() {
    int numPackets, numLinks;
    int *packet_sizes;
    struct Link *links;
    char endhosts[2];
    
    take_input(&numPackets, &numLinks, &packet_sizes, &links, endhosts);
    printf("%.6f\n", packet_delay(numPackets, packet_sizes, numLinks, links));
}