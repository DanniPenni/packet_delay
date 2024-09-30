#include "inout.c"
#include "constants.h"

double packet_delay(int* packets, int* links) {
    return 0;
}

int main() {
    int numPackets, numLinks;
    int **links, *packets;
    char endhosts[2];
    
    take_input(&numPackets, &numLinks, packets, &links, endhosts);
    printf("%d\n", links[0][0]);
}