#include <stdio.h>
#include <stdlib.h>
#include "../headers/constants.h"

void take_input(int* numPackets, int* numLinks, int *(*packets), struct Link **links, char hosts[2]) {
    printf("Please enter your start-point (1 capital letter): \n");
    scanf(" %c", (hosts));
    printf("Please enter your end-point (1 capital letter): \n");
    scanf(" %c", (hosts + 1));

    printf("Please enter the number of links between %c and %c\n", hosts[0], hosts[1]);
    scanf(" %d", numLinks);

    *links = (struct Link*) malloc(sizeof(struct Link) * (*numLinks));

    for (int i = 0; i < *numLinks; ++i) {
        printf("--- Link %d ---\n", i+1);
        printf("Please enter the propogation speed across this link (m/s):\n");
        scanf(" %d", &(*links)[i].prop_speed);
        printf("Please enter the length of this link (m):\n");
        scanf(" %d", &(*links)[i].length);
        printf("Please enter the bitrate (b/s):\n");
        scanf("%d", &(*links)[i].bitrate);
    }

    printf("Please enter the number of packets being sent between %c and %c\n", hosts[0], hosts[1]);
    scanf(" %d", numPackets);

    *packets = (int*) malloc(sizeof(int) * (*numPackets));

    for (int i = 0; i < *numPackets; ++i) {
        printf("Please enter the size of Packet %d (B):\n", i+1);
        int in_bits;
        scanf(" %d", &in_bits);
        (*packets)[i] = in_bits * 8;
    }
}
