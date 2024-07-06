
#ifndef FUNC_RASTER
#define FUNC_RASTER

void coor_gene(
    double **coor_x,
    double **coor_y,
    ST_Header HD
);

double Distance_Euclidean(
    double x1, 
    double y1,
    double x2,
    double y2
);

void Rotate_mask(
    int **rdata_mask,
    double *coor_x,
    double *coor_y,
    ST_Header HD,
    struct Para_global GP
);

void Raster_view(
    int *rdata,
    ST_Header HD
);


#endif
