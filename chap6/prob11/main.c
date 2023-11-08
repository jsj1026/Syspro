#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <time.h>
#include <grp.h>
#include <pwd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>

char type(mode_t);
char *perm(mode_t);
void printStat(char*, char*, struct stat*, bool, bool, bool);
void listDirectory(char*, bool, bool, bool, bool, bool);

int main(int argc, char **argv)
{
    int opt;
    char *dir = "."; 
    bool printDetail = false;
    bool printAll = false;
    bool printInode = false;
    bool printPermissions = false;
    bool printQuestion = false;

    
    while ((opt = getopt(argc, argv, "laiqpQ")) != -1)
    {
        switch (opt)
        {
        case 'l':
           
            printDetail = true;
            break;
        case 'a':
          
            printAll = true;
            break;
        case 'i':
         
            printInode = true;
            break;
        case 'p':
        
            printPermissions = true;
            break;
        case 'Q':
      
            printQuestion = true;
            break;
        case 'q':
         
            printDetail = false;
            printPermissions = false;
            break;
        case '?':
       
            fprintf(stderr, "Usage: %s [-l] [-a] [-i] [-p] [-Q] [-q] [directory]\n", argv[0]);
            exit(EXIT_FAILURE);
        default:
            break;
        }
    }

    if (optind < argc)
    {
        dir = argv[optind]; 
    }

    listDirectory(dir, printDetail, printAll, printInode, printPermissions, printQuestion);

    return 0;
}

void listDirectory(char *dir, bool printDetail, bool printAll, bool printInode, bool printPermissions, bool printQuestion)
{
    DIR *dp;
    struct stat st;
    struct dirent *d;
    char path[BUFSIZ + 1];

    if ((dp = opendir(dir)) == NULL) 
        perror(dir);

    while ((d = readdir(dp)) != NULL)
    { 
        if (!printAll && d->d_name[0] == '.')
        {
      
            continue;
        }

        if (printDetail)
        {
            sprintf(path, "%s/%s", dir, d->d_name); 
            if (lstat(path, &st) < 0) 
                perror(path);
            else
            {
                printStat(path, d->d_name, &st, printInode, printPermissions, printQuestion); 
	    }
        }
        else
        {
            if (printQuestion) {
                printf("'%s' ", d->d_name); 
            } else {
                printf("%s ", d->d_name); 
            }
        }
    }
    if (!printQuestion) {
        printf("\n");
    }
    closedir(dp);
}

void printStat(char *pathname, char *file, struct stat *st, bool printInode, bool printPermissions, bool printQuestion)
{
    if (printInode)
    {
        printf("%lu ", st->st_ino); 
    }

    if (printPermissions)
    {
        printf("%c%s ", type(st->st_mode), perm(st->st_mode));
    }

    
    if (printQuestion) {
        printf("'%s' ", file);
    } else {
        printf("%s ", file);
    }
    printf("%5ld ", st->st_blocks);
    printf("%3ld ", st->st_nlink);
    printf("%s %s ", getpwuid(st->st_uid)->pw_name, getgrgid(st->st_gid)->gr_name);
    printf("%9ld ", st->st_size);
    printf("%.12s ", ctime(&st->st_mtime) + 4);
    printf("\n");
}

char type(mode_t mode)
{
    if (S_ISREG(mode))
        return ('-');
    if (S_ISDIR(mode))
        return ('d');
    if (S_ISCHR(mode))
        return ('c');
    if (S_ISBLK(mode))
        return ('b');
    if (S_ISLNK(mode))
        return ('l');
    if (S_ISFIFO(mode))
        return ('p');
    if (S_ISSOCK(mode))
        return ('s');
    return ('?');
}

char *perm(mode_t mode)
{
    static char perms[10];
    strcpy(perms, "---------");

    for (int i = 0; i < 3; i++)
    {
        if (mode & (S_IRUSR >> i * 3))
            perms[i * 3] = 'r';
        if (mode & (S_IWUSR >> i * 3))
            perms[i * 3 + 1] = 'w';
        if (mode & (S_IXUSR >> i * 3))
            perms[i * 3 + 2] = 'x';
    }
    return (perms);
}
