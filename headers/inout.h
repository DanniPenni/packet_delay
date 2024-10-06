#ifndef INOUT_H
#define INOUT_H
#include "constants.h"

void take_input(int* numPackets, int* numLinks, int *(*packets), struct Link **links, char hosts[2]);
void output_matrix(int numPackets, int numLinks, double *prop_delays, double **trans_delays, double **queue_delays);

#endif