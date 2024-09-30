#include "headers/inout.h"
#include "headers/constants.h"
#include <stdio.h>

int main() {
    int numPackets, numLinks;
    int *packets;
    struct Link *links;
    char endhosts[2];
    
    take_input(&numPackets, &numLinks, packets, &links, endhosts);
    printf("%d\n", links[0].prop_speed);
}