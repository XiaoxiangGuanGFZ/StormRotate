#ifndef FUNC_ROTATE
#define FUNC_ROTATE

void Rotate_coordinate(
    double x1,
    double y1,
    double x2,
    double y2,
    double *R_x2,
    double *R_y2,
    ST_Rotate *p_Rotate
);

void Rotate_init(
    ST_Rotate *p_Rotate,
    struct Para_global GP
);

void Rotate_mapping(
    int **rdata_map,
    int *rdata_mask,
    double *coor_x,
    double *coor_y,
    ST_Rotate *p_Rotate,
    ST_Header *p_HD,
    struct Para_global *p_GP
);

int Nearest_Cell_id(
    double coor_x, // target cell
    double coor_y,
    double *coor_x_rotate,
    double *coor_y_rotate,
    ST_Rotate *p_Rotate,
    ST_Header *p_HD
);

void Rotate_reassign(
    int *rdata,
    int **rdata_out,
    int *rdata_map,
    int *rdata_mask,
    ST_Header * p_HD
);

#endif
