#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zip.h>
#include <sys/stat.h>

void extract_zip(const char *zip_path, const char *dest_dir) {
    int err = 0;
    struct zip *zip_archive = zip_open(zip_path, 0, &err);
    if (!zip_archive) {
        fprintf(stderr, "Error opening zip file: %d\n", err);
        return;
    }

    int num_files = zip_get_num_entries(zip_archive, 0);
    for (int i = 0; i < num_files; i++) {
        struct zip_stat st;
        zip_stat_init(&st);
        zip_stat_index(zip_archive, i, 0, &st);

        struct zip_file *zf = zip_fopen_index(zip_archive, i, 0);
        if (!zf) {
            fprintf(stderr, "Error opening file in zip: %s\n", zip_strerror(zip_archive));
            continue;
        }

        char dest_file[512];
        snprintf(dest_file, sizeof(dest_file), "%s/%s", dest_dir, st.name);

        // Create directory if it does not exist
        char *dir = strdup(dest_file);
        char *last_slash = strrchr(dir, '/');
        if (last_slash) {
            *last_slash = '\0';
            mkdir(dir, 0755);
        }
        free(dir);

        FILE *f = fopen(dest_file, "wb");
        if (!f) {
            fprintf(stderr, "Error opening destination file: %s\n", dest_file);
            zip_fclose(zf);
            continue;
        }

        char buf[4096];
        zip_uint64_t sum = 0;
        while (sum != st.size) {
            zip_int64_t len = zip_fread(zf, buf, sizeof(buf));
            if (len < 0) {
                fprintf(stderr, "Error reading file in zip: %s\n", zip_file_strerror(zf));
                break;
            }
            fwrite(buf, 1, len, f);
            sum += len;
        }
        fclose(f);
        zip_fclose(zf);
    }

    zip_close(zip_archive);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <zipfile> <destination>\n", argv[0]);
        return 1;
    }

    const char *zip_path = argv[1];
    const char *dest_dir = argv[2];

    extract_zip(zip_path, dest_dir);

    printf("Installation completed successfully.\n");
    return 0;
}
