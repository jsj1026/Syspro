#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

// 함수 선언
void list_directory(const char *path, int show_hidden, int show_long, int human_readable);

int main(int argc, char *argv[]) {
    int show_hidden = 0;
    int show_long = 0;
    int human_readable = 0;
    const char *path = ".";  // 기본 경로

    // 명령행 인수를 처리하여 옵션 설정
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-a") == 0) {
            show_hidden = 1;
        } else if (strcmp(argv[i], "-l") == 0) {
            show_long = 1;
        } else if (strcmp(argv[i], "-h") == 0) {
            human_readable = 1;
        } else {
            path = argv[i];  // 디렉토리 경로를 설정
        }
    }

    // 디렉토리 내용 출력
    list_directory(path, show_hidden, show_long, human_readable);

    return 0;
}

// 디렉토리 내용을 나열하는 함수
void list_directory(const char *path, int show_hidden, int show_long, int human_readable) {
    struct dirent *entry;
    struct stat statbuf;
    DIR *dp = opendir(path);

    if (dp == NULL) {
        perror("opendir");
        exit(1);
    }

    while ((entry = readdir(dp)) != NULL) {
        if (!show_hidden && entry->d_name[0] == '.') {
            continue;
        }

        char full_path[1024];
        snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);

        if (show_long) {
            if (stat(full_path, &statbuf) == -1) {
                perror("stat");
                exit(1);
            }

  char size_str[128]; // 충분한 크기의 버퍼 할당

if (human_readable) {
    double size_in_MB = (double)statbuf.st_size / (1024 * 1024);
    snprintf(size_str, sizeof(size_str), "%.2f MB", size_in_MB);
} else {
    snprintf(size_str, sizeof(size_str), "%lld bytes", (long long)statbuf.st_size);
}

printf("%s - Size: %s, Permissions: %o\n", entry->d_name, size_str, statbuf.st_mode & 0777);
            

            
           
        } else {
            printf("%s\n", entry->d_name);
        }
    }

    closedir(dp);
}
