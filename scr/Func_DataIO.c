


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "def_struct.h"
#include "Func_DataIO.h"

void import_global(
    char fname[], struct Para_global *p_gp)
{
    /**************
     * import the global parameters into memory for disaggregation algorithm
     *
     * -- Parameters:
     *      fname: a string (1-D character array), file path and name of the global parameters
     * -- Output:
     *      return a structure containing the key fields
     * ********************/

    /***** initializae *****/

    char row[MAXCHAR];
    FILE *fp;
    char *token;
    char *token2;
    int i;

    if ((fp = fopen(fname, "r")) == NULL)
    {
        printf("cannot open global parameter file: %s\n", fname);
        exit(1);
    }
    
    while (fgets(row, MAXCHAR, fp) != NULL)
    {
        // the fgets() function comes from <stdbool.h>
        // Reads characters from stream and stores them as a C string

        /***
         * removeLeadingSpaces():
         * remove all the leading white spaces in the string if exist,
         * otherwise do nothing!
         */
        removeLeadingSpaces(row);

        if (row != NULL && strlen(row) > 1)
        {
            /*non-empty row(string)*/
            if (row[0] != '#')
            {
                /* the first character of row should not be # */
                for (i = 0; i < strlen(row); i++)
                {
                    /* remove (or hide) all the characters after # */
                    if (row[i] == '#')
                    {
                        row[i] = '\0';
                        break;
                    }
                }
                /* assign the values to the parameter structure: key-value pairs */
                token = strtok(row, ",");       // the first column: key
                token2 = strtok(NULL, ",\r\n"); // the second column: value
                /*******
                 * file path and names
                 * *****/
                if (strncmp(token, "FP_data", 7) == 0)
                {
                    strcpy(p_gp->FP_data, token2);
                }
                else if (strncmp(token, "FP_out", 6) == 0)
                {
                    strcpy(p_gp->FP_out, token2);
                }
                else if (strncmp(token, "ROTATE_ANGLE", 12) == 0)
                {
                    p_gp->ROTATE_ANGLE = atof(token2); // indicate the variable type: temperature,rhu, wind, ...
                }
                else if (strncmp(token, "ROTATE_CENTER_X", 15) == 0)
                {
                    p_gp->ROTATE_CENTER_X = atof(token2);
                }
                else if (strncmp(token, "ROTATE_CENTER_Y", 15) == 0)
                {
                    p_gp->ROTATE_CENTER_Y = atof(token2);
                }
                else if (strncmp(token, "ROTATE_RADIUS", 13) == 0)
                {
                    p_gp->ROTATE_RADIUS = atof(token2);
                }
                else
                {
                    printf(
                        "Error in opening global parameter file: unrecognized parameter field! %s", token);
                    exit(1);
                }
            }
        }
    }
    fclose(fp);    
}

void removeLeadingSpaces(char *str)
{
    if (str != NULL)
    {
        int i, j = 0;
        int len = strlen(str);
        // Find the first non-space character
        for (i = 0; i < len && isspace(str[i]); i++)
        {
            // Do nothing, just iterate until the first non-space character is found
        }
        // Shift the string to remove leading spaces
        for (; i < len; i++)
        {
            str[j++] = str[i];
        }
        // Null-terminate the modified string
        str[j] = '\0';
    }
}

/********************************
 * read ASCII raster data
 * ******************************/

int Header_read(
    FILE *fp_geo,
    ST_Header *HD,
    int display)
{
    /*******************************************
     * import the header lines in an ASCII
     * file containg geodata, which usually has 6 rows:
     * - ncols
     * - nrows
     * - xllcorner
     * - yllcorner
     * - cellsize
     * - NODATA_value
    */
    char row[MAXCHAR];
    char s1[MAXCHAR];

    if (fgets(row, MAXCHAR, fp_geo) != NULL)
    {
        sscanf(row, "%s %d", s1, &HD->ncols);
        if (display == 1)
        {
            printf("%s: %d\n", s1, HD->ncols);
        }
        if (fgets(row, MAXCHAR, fp_geo) != NULL)
        {
            sscanf(row, "%s %d", s1, &HD->nrows);
            if (display == 1)
            {
                printf("%s: %d\n", s1, HD->nrows);
            }
            if (fgets(row, MAXCHAR, fp_geo) != NULL)
            {
                sscanf(row, "%s %lf", s1, &HD->xllcorner);
                if (display == 1)
                {
                    printf("%s: %.12lf\n", s1, HD->xllcorner);
                }
                if (fgets(row, MAXCHAR, fp_geo) != NULL)
                {
                    sscanf(row, "%s %lf", s1, &HD->yllcorner);
                    if (display == 1)
                    {
                        printf("%s: %.12lf\n", s1, HD->yllcorner);
                    }
                    if (fgets(row, MAXCHAR, fp_geo) != NULL)
                    {
                        sscanf(row, "%s %lf", s1, &HD->cellsize);
                        if (display == 1)
                        {
                            printf("%s: %.12lf\n", s1, HD->cellsize);
                        }
                        if (fgets(row, MAXCHAR, fp_geo) != NULL)
                        {
                            sscanf(row, "%s %d", s1, &HD->NODATA_value);
                            if (display == 1)
                            {
                                printf("%s: %d\n", s1, HD->NODATA_value);
                            }
                        }
                        else
                        {
                            printf("reading the 5th row in DEM data file failed!\n");
                            exit(0);
                        }
                    }
                    else
                    {
                        printf("reading the 5th row in DEM data file failed!\n");
                        exit(0);
                    }
                }
                else
                {
                    printf("reading the 4th row in DEM data file failed!\n");
                    exit(0);
                }
            }
            else
            {
                printf("reading the 3rd row in DEM data file failed!\n");
                exit(0);
            }
        }
        else
        {
            printf("reading the 2nd row in DEM data file failed!\n");
            exit(0);
        }
    }
    else
    {
        printf("reading the first row in DEM data file failed!\n");
        exit(0);
    }
    return 1;
}

void Import_raster(
    int *rdata,
    FILE *fp_geo,
    int ncols,
    int nrows
)
{
    /********************************************
     * import the 2D array (gridded data)
     * the data part from an ASCII file, excluding 
     * the header rows
    */
    if (rdata == NULL)
    {
        printf("Error allocating memory");
        exit(-1);
    }
    int i, j;
    j = 0;
    char row[MAXCHAR];
    for (j = 0; j < nrows; j++)
    {
        for (i = 0; i < ncols; i++)
        {
            if (fscanf(fp_geo, "%d", rdata + j * ncols + i) != 1)
            {
                fprintf(stderr, "Error reading integer in %d th row from file.\n", j);
                exit(-2);
            }
        }
    }
}

int Import_data(
    char FP[],
    int **rdata,
    ST_Header *fp_header,
    int display
)
{
    /*********************************************
     * import the full data (both headers and 2D aray) 
     * from an ASCII geodata file
    */
    FILE *fp;
    int IO_status;
    // first, open the file given its path and filename
    if ((fp = fopen(FP, "r")) == NULL)
    {
        printf("failed to open %s!\n", FP);
        exit(0);
    }

    // import the header rows 
    IO_status = Header_read(fp, fp_header, display);
    if (IO_status == 1)
    {
        // if the header rows are imported successfully,
        // import the data part (2D raster array)
        *rdata = (int *)malloc(sizeof(int) * fp_header->ncols * fp_header->nrows);
        Import_raster(*rdata, fp, fp_header->ncols, fp_header->nrows);
    }
    fclose(fp); // close the ASCII file
    return 1;
}

/********************************
 * write ASCII raster data
 * ******************************/
void Export_raster(
    int *rdata,
    FILE *fp_geo,
    int ncols,
    int nrows
)
{
    /************************
     * write the raster/gridded data in to ASCII text file
     * rdata locates the first value of a sequence data
     ************************/
    int i, j;
    for (i = 0; i < nrows; i++)
    {
        for (j = 0; j < ncols; j++)
        {
            fprintf(fp_geo, "%d ", *(rdata + i * ncols + j));
        }
        fprintf(fp_geo, "\n");
    }
}

void Export_header(
    FILE *fp_geo,
    ST_Header HD
)
{
    /*******************************
     * write the header info into text file
     *******************************/
    fprintf(fp_geo, "%-14s%d\n", "ncols", HD.ncols);
    fprintf(fp_geo, "%-14s%d\n", "nrows", HD.nrows);
    fprintf(fp_geo, "%-14s%-.12f\n", "xllcorner", HD.xllcorner);
    fprintf(fp_geo, "%-14s%-.12f\n", "yllcorner", HD.yllcorner);
    fprintf(fp_geo, "%-14s%-.12f\n", "cellsize", HD.cellsize);
    fprintf(fp_geo, "%-14s%-d\n", "NODATA_value", HD.NODATA_value);
}

void Export_data(
    int *rdata,
    ST_Header HD,
    char FP[]
)
{
    FILE *fp_out;
    if ((fp_out = fopen(FP, "w")) == NULL)
    {
        printf("Program terminated: cannot create or open output file %s\n", FP);
        exit(0);
    }
    Export_header(fp_out, HD);
    Export_raster(rdata, fp_out, HD.ncols, HD.nrows);
    fclose(fp_out);
    free(rdata);
}




