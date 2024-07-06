

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "def_struct.h"
#include "Func_Raster.h"

void coor_gene(
    double **coor_x,
    double **coor_y,
    ST_Header HD
)
{

    *coor_x = (double *)malloc(sizeof(double) * HD.ncols);
    *coor_y = (double *)malloc(sizeof(double) * HD.nrows);
    for (int i = 0; i < HD.ncols; i++)
    {
        *(*coor_x + i) = HD.cellsize * i + HD.xllcorner;
        // printf("%9.3f ", *(*coor_x + i));
    }
    // printf("\n");
    for (int i = 0; i < HD.nrows; i++)
    {
        *(*coor_y + i) = HD.cellsize * (HD.nrows - 1 - i) + HD.yllcorner;
        // printf("%8.1f ", *(*coor_y + i));
    }
    // printf("\n");

}

void Rotate_mask(
    int **rdata_mask,
    double *coor_x,
    double *coor_y,
    ST_Header HD,
    struct Para_global GP
)
{
    int i, j;
    int cell_id;
    double distance;
    *rdata_mask = (int *)malloc(sizeof(int) * HD.ncols * HD.nrows);
    for (i = 0; i < HD.nrows; i++)
    {
        for (j = 0; j < HD.ncols; j++)
        {
            cell_id = j + i * HD.ncols;
            distance = Distance_Euclidean(
                GP.ROTATE_CENTER_X, GP.ROTATE_CENTER_Y,
                *(coor_x + j), *(coor_y + i)
            );
            if (distance <= GP.ROTATE_RADIUS)
            {
                *(*rdata_mask + cell_id) = 1;
            } else {
                *(*rdata_mask + cell_id) = 0;
            }
        }
    }
}

double Distance_Euclidean(
    double x1, 
    double y1,
    double x2,
    double y2
)
{
    double dis;
    dis = pow(x1 - x2, 2) + pow(y1 - y2, 2);
    dis = sqrt(dis);
    return(dis);
}

void Raster_view(
    int *rdata,
    ST_Header HD
)
{
    int i, j, cell_id;
    for (i = 0; i < HD.nrows; i++)
    {
        for (j = 0; j < HD.ncols; j++)
        {
            cell_id = j + i * HD.ncols;
            printf("%5d ", *(rdata + cell_id));
        }
        printf("\n");
    }
}

