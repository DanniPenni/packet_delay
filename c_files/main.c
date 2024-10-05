#include "../headers/inout.h"
#include "../headers/constants.h"
#include <stdio.h>
#include <stdlib.h>

double packet_delay(int numPackets, int* packets, int numLinks, struct Link *links) {
    double packet_delay = 0;
    // Transmission delay from start-host
    for (int i = 0; i < numPackets-1; ++i) {
        double trans_delay_i = (double) packets[i] / links[0].bitrate;
        packet_delay += trans_delay_i * 1000;
    }


    // Transmission through routers
    for (int i = 0; i < numLinks; ++i) {
        double prop_delay = ((double) links[i].length / links[i].prop_speed) * 1000;
        double trans_delay = ((double) packets[numPackets-1] / links[i].bitrate) * 1000;

        double queueing_delay = 0;
        double prev_packet_trans = 0;

        // Calculate queueing delay.
        if (i != numLinks - 1) {
            for (int p = 0; p < numPackets - 1; ++p) {
                prev_packet_trans += ((double) packets[p] / links[i+1].bitrate) * 1000;
            }
        }

        queueing_delay = (trans_delay > prev_packet_trans) ? 0 : (prev_packet_trans - trans_delay);

        printf("QUEUEING DELAY: %f\n", queueing_delay);
        packet_delay += prop_delay + queueing_delay + trans_delay;
    }
    return packet_delay;
}

int main() {
    int numPackets, numLinks;
    int *packet_sizes;
    struct Link *links;
    char endhosts[2];
    
    take_input(&numPackets, &numLinks, &packet_sizes, &links, endhosts);
    printf("%.6fms\n", packet_delay(numPackets, packet_sizes, numLinks, links));
}