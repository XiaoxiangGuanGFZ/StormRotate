


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

#include "def_struct.h"
#include "Func_DataIO.h"
#include "Func_Rotate.h"
#include "Func_Raster.h"
#include "Func_Filelist.h"


int main(int argc, char * argv[])
{
    struct Para_global GP; // define the global-parameter structure
    struct Para_global *p_gp;   // give a pointer to global_parameter structure
    p_gp = &GP;

    /******* import the global parameters ***********
    * parameter from main() function, pointer array
    * argv[0]: pointing to the first string from command line (the executable file)
    * argv[1]: pointing to the second string (parameter): file path and name of global parameter file.
    ***********/
    import_global(*(++argv), p_gp);

    /****************************
     * detect all the .asc file in the directory
     * **************************/
    FileList fileList;
    list_asc_files(p_gp->FP_data, &fileList);
    if (fileList.count == 0)
    {
        printf("No .asc file detected in %s:\n", p_gp->FP_data);
        exit(0);
    }
    printf("Detected .asc files in %s:\n", p_gp->FP_data);
    for (size_t i = 0; i < fileList.count; i++) {
        printf("%s\n", fileList.filenames[i]);
    }
    
    char FP_file[MAXCHAR];
    FP_file[0] = '\0';
    
    /****************************
     * derive the mapping between raw and rotated raster
     * based on one data file
     * **************************/
    strcat(strcat(FP_file, p_gp->FP_data), fileList.filenames[0]); // the first ASCII raster file 
    printf("%s\n", FP_file);

    ST_Header HD; // the first 6 lines in ASCII raster file
    int *rdata;
    if (FP_file[0] != '\0')
    {
        Import_data(FP_file, &rdata, &HD, 1);
    }
    // Raster_view(rdata, HD);

    // detect the coordinates of the grids: two dimensions
    double *coor_x, *coor_y;  // coor_x: from east to west (left-to-right); coor_y: from north to south (up-to-bottom)
    coor_gene(&coor_x, &coor_y, HD);

    int *rdata_mask;
    Rotate_mask(&rdata_mask, coor_x, coor_y, HD, GP); // the valid boundary for rotated raster

    // Raster_view(rdata_mask, HD);

    // derive the remapping between raw and rotated 2D raster
    ST_Rotate Rotate_para;
    ST_Rotate *p_Rotate;
    p_Rotate = &Rotate_para;
    Rotate_init(p_Rotate, GP);

    int *rdata_map;
    Rotate_mapping(&rdata_map, rdata_mask, coor_x, coor_y, p_Rotate, &HD, &GP);

    /**************************************
     *     raster rotate: reassign
     * ************************************/
    int *rdata_out;
    char FP_output[MAXCHAR];
    FP_output[0] = '\0';

    for (int i = 0; i < fileList.count; i++)
    {
        printf("%s: ", fileList.filenames[i]);
        FP_file[0] = '\0'; FP_output[0] = '\0';
        strcat(strcat(FP_file, p_gp->FP_data), fileList.filenames[0]);
        strcat(strcat(FP_output, p_gp->FP_out), fileList.filenames[0]);
        if (FP_file[0] != '\0')
        {
            Import_data(FP_file, &rdata, &HD, 0);
        }
        Rotate_reassign(rdata, &rdata_out, rdata_map, rdata_mask, &HD);

        // Raster_view(rdata_out, HD);
        Export_data(rdata_out, HD, FP_output);
        printf("Done!\n");
    }
    
    // Free allocated memory
    free_file_list(&fileList);

    return 1;
}

