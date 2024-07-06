
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "Func_Filelist.h"



int has_asc_extension(const char *filename) {
    const char *ext = ".asc";
    size_t len_filename = strlen(filename);
    size_t len_ext = strlen(ext);

    if (len_filename >= len_ext) {
        return strcmp(filename + len_filename - len_ext, ext) == 0;
    }
    return 0;
}

void list_asc_files(const char *dirpath, FileList *fileList) {
    struct dirent *entry;
    DIR *dp = opendir(dirpath);

    if (dp == NULL) {
        perror("opendir");
        return;
    }

    fileList->count = 0;
    fileList->filenames = NULL;

    while ((entry = readdir(dp))) {
        if (entry->d_type == DT_REG && has_asc_extension(entry->d_name)) {
            fileList->filenames = realloc(fileList->filenames, (fileList->count + 1) * sizeof(char *));
            fileList->filenames[fileList->count] = strdup(entry->d_name);
            fileList->count++;
        }
    }

    closedir(dp);
}

void free_file_list(FileList *fileList) {
    for (size_t i = 0; i < fileList->count; i++) {
        free(fileList->filenames[i]);
    }
    free(fileList->filenames);
    fileList->count = 0;
}

// int main(int argc, char *argv[]) {
//     if (argc != 2) {
//         fprintf(stderr, "Usage: %s <directory>\n", argv[0]);
//         return EXIT_FAILURE;
//     }

//     FileList fileList;
//     list_asc_files(argv[1], &fileList);

//     printf("Detected .asc files:\n");
//     for (size_t i = 0; i < fileList.count; i++) {
//         printf("%s\n", fileList.filenames[i]);
//     }

//     // Use fileList for further processing...

//     // Free allocated memory
//     free_file_list(&fileList);

//     return EXIT_SUCCESS;
// }
