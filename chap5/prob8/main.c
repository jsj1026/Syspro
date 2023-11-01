#include <stdio.h>

int main() {
    char filename[100];
    int totalLines, lineNumber;

    printf("파일명을 입력하세요: ");
    scanf("%s", filename);

    printf("토탈 라인을 입력하세요: ");
    scanf("%d", &totalLines);

    printf("찾을 줄 번호를 입력하세요: ");
    scanf("%d", &lineNumber);

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("파일을 열 수 없습니다.\n");
        return 1;
    }

    char line[256];  /

    
    int currentLine = 1;
    while (fgets(line, sizeof(line), file)) {
        if (currentLine == totalLines) {
            printf("토탈 라인 %d의 %d번째 줄: %s", totalLines, lineNumber, line);
            break;
        }
        currentLine++;
    }

    fclose(file);

    if (currentLine < totalLines) {
        printf("토탈 라인 %d을 찾을 수 없습니다.\n", totalLines);
    }

    return 0;
}
