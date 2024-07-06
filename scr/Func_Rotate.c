
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "def_struct.h"
#include "Func_Rotate.h"
#include "Func_Raster.h"

void Rotate_coordinate(
    double x1,
    double y1,
    double x2,
    double y2,
    double *R_x2,
    double *R_y2,
    ST_Rotate *p_Rotate
)
{
    double COS, SIN;
    *R_x2 = x1 + (x2 - x1) * p_Rotate->angle_cos + (y2 - y1) * p_Rotate->angle_sin;
    *R_y2 = y1 - (x2 - x1) * p_Rotate->angle_sin + (y2 - y1) * p_Rotate->angle_cos;
}

void Rotate_init(
    ST_Rotate *p_Rotate,
    struct Para_global GP
)
{
    p_Rotate->angle = GP.ROTATE_ANGLE;
    p_Rotate->angle_cos = cos(p_Rotate->angle * PI / 180);
    p_Rotate->angle_sin = sin(p_Rotate->angle * PI / 180);
    p_Rotate->CENTER_X = GP.ROTATE_CENTER_X;
    p_Rotate->CENTER_Y = GP.ROTATE_CENTER_Y;
}

void Rotate_mapping(
    int **rdata_map,
    int *rdata_mask,
    double *coor_x,
    double *coor_y,
    ST_Rotate *p_Rotate,
    ST_Header *p_HD,
    struct Para_global *p_GP
)
{
    int raster_size;
    raster_size = p_HD->ncols * p_HD->nrows;
    *rdata_map = (int *)malloc(sizeof(int) * raster_size);

    /************************
     *  derive the coordinates after rotation
     * **********************/
    double *coor_x_rotate, *coor_y_rotate;
    coor_x_rotate = (double *)malloc(sizeof(double) * raster_size);
    coor_y_rotate = (double *)malloc(sizeof(double) * raster_size);

    int i, j, cell_id;
    for (i = 0; i < p_HD->nrows; i++)
    {
        for (j = 0; j < p_HD->ncols; j++)
        {
            cell_id = j + i * p_HD->ncols;
            Rotate_coordinate(
                p_Rotate->CENTER_X,
                p_Rotate->CENTER_Y,
                *(coor_x + j),
                *(coor_y + i),
                coor_x_rotate + cell_id,
                coor_y_rotate + cell_id,
                p_Rotate);
        }
    }

    /************************
     *  mapping between raw and rotated raster
     * **********************/
    for (i = 0; i < p_HD->nrows; i++)
    {
        for (j = 0; j < p_HD->ncols; j++)
        {
            cell_id = j + i * p_HD->ncols;
            if (*(rdata_mask + cell_id) == 0)
            {
                *(*rdata_map + cell_id) = -1;
            } else {
                *(*rdata_map + cell_id) = Nearest_Cell_id(
                    *(coor_x + j),
                    *(coor_y + i),
                    coor_x_rotate,
                    coor_y_rotate,
                    p_Rotate,
                    p_HD);
            }
        }
    }
}

int Nearest_Cell_id(
    double coor_x, // target cell
    double coor_y,
    double *coor_x_rotate,
    double *coor_y_rotate,
    ST_Rotate *p_Rotate,
    ST_Header *p_HD
)
{
    int i;
    int raster_size;
    raster_size = p_HD->ncols * p_HD->nrows;
    double dis_nearest = 0;
    int id_nearest = 0;
    double dis_i = 0;
    for (i = 0; i < raster_size; i++)
    {
        dis_i = Distance_Euclidean(coor_x, coor_y, *(coor_x_rotate + i), *(coor_y_rotate + i));
        if (i == 0)
        {
            dis_nearest = dis_i; id_nearest = 0;
        } else {
            if (dis_i < dis_nearest)
            {
                dis_nearest = dis_i;
                id_nearest = i;
            }
        }
    }
    return id_nearest;
}

void Rotate_reassign(
    int *rdata,
    int **rdata_out,
    int *rdata_map,
    int *rdata_mask,
    ST_Header * p_HD
)
{
    int i, j, cell_id;
    int raster_size;
    raster_size = p_HD->ncols * p_HD->nrows;
    *rdata_out = (int *)malloc(sizeof(int) * raster_size);

    for (i = 0; i < p_HD->nrows; i++)
    {
        for (j = 0; j < p_HD->ncols; j++)
        {
            cell_id = j + i * p_HD->ncols;
            if (*(rdata_mask + cell_id) == 0)
            {
                *(*rdata_out + cell_id) = p_HD->NODATA_value;
            } else {
                *(*rdata_out + cell_id) = *(rdata + *(rdata_map + cell_id));
            }
        }
    }
}

