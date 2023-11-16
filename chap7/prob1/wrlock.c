#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

struct student {
    char name[50];
    int id;
    int score;
};

int main(int argc, char *argv[]) {
    int fd, id;
    struct student record;
    struct flock lock;

    if (argc < 2) {
        fprintf(stderr, "How to use : %s File \n", argv[0]);
        exit(1);
    }

    if ((fd = open(argv[1], O_RDWR)) == -1) {
        perror(argv[1]);
        exit(2);
    }

    printf("\nEnter StudentID you want to modify : ");
    while (scanf("%d", &id) == 1) {
        lock.l_type = F_WRLCK;
        lock.l_whence = SEEK_SET;
        lock.l_start = id * sizeof(record);  // Assuming id is the index, not offset
        lock.l_len = sizeof(record);

        if (fcntl(fd, F_SETLKW, &lock) == -1) { /* Write lock */
            perror(argv[1]);
            exit(3);
        }

        lseek(fd, id * sizeof(record), SEEK_SET);

        if ((read(fd, (char *) &record, sizeof(record)) > 0) && (record.id != 0)) {
            printf("Name:%s\t StuID:%d\t Score:%d\n", record.name, record.id, record.score);
            printf("Enter new score: ");
            scanf("%d", &record.score);

            lseek(fd, -sizeof(record), SEEK_CUR);
            write(fd, (char *) &record, sizeof(record));

            lock.l_type = F_UNLCK;
            fcntl(fd, F_SETLK, &lock); /* Unlock */
        } else {
            printf("No record %d \n", id);
        }

        printf("\nEnter StudentID you want to modify : ");
    }

    close(fd);
    exit(0);
}
