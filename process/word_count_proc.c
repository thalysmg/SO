#include <ctype.h>
#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <stdbool.h>

size_t wc(const char *string) {
    size_t count = 0;

    for (bool inword = false; *string; ++string) {
        if (isspace(*string)) {
            if (inword) {
                inword = false;
            }
        } else {
            if (!inword) {
                inword = true;
                ++count;
            }
        }
    }
    return count;
}

size_t wc_file(const char *filename) {
    char * file_content = 0;//how to init? 0 or null?
    long length;//what is the modern typ?

    FILE * f = fopen(filename, "rb");

    if (f) {
        fseek(f, 0, SEEK_END);
        length = ftell(f);
        fseek(f, 0, SEEK_SET);
        file_content = malloc(length);
        if (file_content) {
            fread(file_content, 1, length, f);
        }
        fclose(f);

        return wc(file_content);
    }

    return -1;
}

size_t wc_dir(const char *root_path){
    DIR* root_dir;
    struct dirent *ent;
    char filepath [1024];//unsafe

    size_t count = 0;

    root_dir = opendir(root_path);

    if (root_dir) {
        while ((ent = readdir(root_dir)) != NULL) {
            if (ent->d_type == DT_REG) {//if is regular file
                sprintf(filepath, "%s/%s", root_path, ent->d_name);
                count += wc_file(filepath);
            }
        }
        closedir(root_dir);

        return count;
    }

    return -1;
}

int main(int argc, char* argv[argc + 1]) {
    printf("%zu\n", wc_dir(argv[1]));
    return EXIT_SUCCESS;
}
