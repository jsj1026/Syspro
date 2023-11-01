#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
   
    const char *filename = "test2.txt";

    
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("파일 열기 실패");
        return 1;
    }

    
    char **lines = NULL;
    int num_lines = 0;

   
    char line[256]; 
    while (fgets(line, sizeof(line), file)) {
        
        lines = (char **)realloc(lines, (num_lines + 1) * sizeof(char *));
        lines[num_lines] = strdup(line);
        num_lines++;
    }

    
    fclose(file);

    
    for (int i = num_lines - 1; i >= 0; i--) {
        printf("%s", lines[i]);
        free(lines[i]); 
    }

  
    free(lines);

    return 0;
}

