#include "../headers/inout.h"
#include "../headers/constants.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double packet_matrix_and_delay(int numPackets, int *packet_sizes, int numLinks, struct Link *links, double *(*prop_delays), double *(*(*trans_delays)), double *(*(*queue_delays))) {
    *prop_delays = (double *) malloc(sizeof(double) * numLinks);
    *trans_delays = (double **) malloc(sizeof(double*) * numPackets);
    *queue_delays = (double **) malloc(sizeof(double*) * numPackets);

    // Calculating propogation delays
    for (int i = 0; i < numLinks; ++i) {
        (*prop_delays)[i] = (double) links[i].length / links[i].prop_speed;
    }

    // Calculating transmission delays
    for (int p = 0; p < numPackets; ++p) {
        (*trans_delays)[p] = (double *) malloc(sizeof(double) * numLinks);
        for (int l = 0; l < numLinks; ++l) {
            (*trans_delays)[p][l] = (double) packet_sizes[p] / links[l].bitrate;
        }
    }

    // Calculating queueing delays

    // Queueing delays for first packet are always 0.
    (*queue_delays)[0] = (double *) malloc(sizeof(double) * (numLinks - 1));
    for (int l = 0; l < numLinks - 1; ++l) {
        (*queue_delays)[0][l] = 0;
    }

    // For the rest of the packets...
    for (int p = 1; p < numPackets; ++p) {
        (*queue_delays)[p] = (double *) malloc(sizeof(double) * (numLinks - 1));
        for (int l = 0; l < numLinks - 1; ++l) {
            // The packet has to wait until the one before it is transmitted. 
            // (1) The time until the packet before it is transmitted is equal to p-1's queueing delay + it's transmission delay on the next link.
            // (2) The time for this packet to fully arrive at this node is this packet's transmission delay.
            // The difference of this value gives us the queueing delay (That's 0 if (2) > (1), since the packet arrives after the other one's already gone).
            (*queue_delays)[p][l] = ((*queue_delays)[p-1][l] + (*trans_delays)[p-1][l+1]) - (*trans_delays)[p][l];
            (*queue_delays)[p][l] = ((*queue_delays)[p][l] > 0) ? (*queue_delays)[p][l] : 0;
            // (*queue_delays)[p][l] = 0;
        }
    }

    // Final time is...
    double packet_delay = 0; // Summation variable.
    int last_packet = numPackets - 1; // Index of last packet
    int last_link = numLinks - 1;

    for (int p = 0; p < numPackets - 1; ++p) {
        packet_delay += (*trans_delays)[p][0];
    }

    for (int l = 0; l < numLinks - 1; ++l) {
        packet_delay += (*prop_delays)[l] + (*trans_delays)[last_packet][l] + (*queue_delays)[last_packet][l];
    }
    packet_delay += (*prop_delays)[last_link] + (*trans_delays)[last_packet][last_link];

    return packet_delay;
}

int main() {
    int numPackets, numLinks;
    int *packet_sizes;
    struct Link *links;
    char endhosts[2];

    double *prop_delays;
    double **trans_delays;
    double **queue_delays;
    
    take_input(&numPackets, &numLinks, &packet_sizes, &links, endhosts);
    printf("Last packet arrives in: %.6fs\n", packet_matrix_and_delay(numPackets, packet_sizes, numLinks, links, &prop_delays, &trans_delays, &queue_delays));
    output_matrix(numLinks, numPackets, prop_delays, trans_delays, queue_delays);
}