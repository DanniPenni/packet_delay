#include <stdio.h>
#include <stdlib.h>
#include "constants.h"

void take_input(int* numPack, int* numLinks, int* packets, int *(*(*links)), char hosts[2]) {
    printf("Please enter your start-point (1 capital letter): \n");
    scanf(" %c", (hosts));
    printf("Please enter your end-point (1 capital letter): \n");
    scanf(" %c", (hosts + 1));

    printf("Please enter the number of links between %c and %c\n", hosts[0], hosts[1]);
    scanf(" %d", numLinks);

    *links = (int**) malloc(sizeof(int *) * (*numLinks));
    // links[0] = (int*) malloc(sizeof(int) * 3);
    // links[0][0] = 2;

    for (int i = 0; i < *numLinks; ++i) {
        printf("--- Link %d ---\n", i);
        *links[i] = (int*) malloc(sizeof(int) * 3);
        printf("Please enter the propogation speed across this link (m/s): ");
        scanf(" %d", &(*links)[i][0]);
        printf("Please enter the length of this link (m): ");
        scanf(" %d", &(*links)[i][1]);
        printf("Please enter the bandwidth (b/s): ");
        scanf("%d", &(*links)[i][2]);
    }

    printf("%d\n", (*links)[0][0]);
}
