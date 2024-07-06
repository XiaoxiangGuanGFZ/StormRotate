#ifndef FUNC_IO
#define FUNC_IO

#include <stdlib.h>
#include <stdio.h>
#include "def_struct.h"

void import_global(char fname[], struct Para_global *p_gp);
void removeLeadingSpaces(char *str);

/*******************
 * ASCII raster data read and write
 * *****************/
int Import_data(
    char FP[],
    int **rdata,
    ST_Header *fp_header,
    int display
);

int Header_read(
    FILE *fp_geo,
    ST_Header *HD,
    int display
);

void Import_raster(
    int *rdata,
    FILE *fp_geo,
    int ncols,
    int nrows
);

void Export_raster(
    int *rdata,
    FILE *fp_geo,
    int ncols,
    int nrows
);

void Export_header(
    FILE *fp_geo,
    ST_Header HD
);

void Export_data(
    int *rdata,
    ST_Header HD,
    char FP[]
);


#endif