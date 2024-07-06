#ifndef FUNC_FILELIST
#define FUNC_FILELIST

typedef struct {
    char **filenames;
    int count;
} FileList;

int has_asc_extension(const char *filename);
void list_asc_files(const char *dirpath, FileList *fileList);

void free_file_list(FileList *fileList);


#endif