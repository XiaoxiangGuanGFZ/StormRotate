#ifndef STRUCT_H
#define STRUCT_H

#define PI 3.1415926
#define MAXCHAR 10000  // able to accomodate up to 3000 sites simultaneously
#define MAXrow 100000  // almost 270 years long ts
#define MAXcps 20
/******
 * the following define the structures
*/
struct Date {
    int y;
    int m;
    int d;
};

typedef struct 
{
    int ncols;         /* number of cell columns */
    int nrows;         /* number of cell rows */
    double xllcorner;  /* X-coordinate of the origin (by center or lower left corner of the cell) */
    double yllcorner;  /* Y-coordinate of the origin (by center or lower left corner of the cell) */
    double cellsize;   /* Cell size */
    int NODATA_value;  /* The input values to be NoData in the output raster */

} ST_Header;

// ncols,24
// nrows,24
// xllcorner,591987.736481999978
// yllcorner,5780746.032255999744
// cellsize,1000.000000000000
// NODATA_value,-9999

struct Para_global
    {
        /* global parameters */
        double ROTATE_ANGLE;
        double ROTATE_CENTER_X;
        double ROTATE_CENTER_Y;
        double ROTATE_RADIUS;
        char FP_data[200];     // 
        char FP_out[200];        // 

    };

typedef struct 
{
    double angle;
    double angle_cos;
    double angle_sin;
    double CENTER_X;
    double CENTER_Y;
} ST_Rotate;

#endif
