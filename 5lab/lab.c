#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <errno.h>

#define MAX_AMOUNT 100  //max amount of lines in the file
#define MAX_LEN 80      //max len of the read line


void brk_error(const char *const msg) {
    if (errno == 0) {
        fprintf(stderr, "%s", msg);
    } else {
        perror(msg);
      }
    exit(1);
}

int get_line_num() {
        int line_num;
        printf("Enter line number: ");

        if (scanf("%d", &line_num) != 1) {
                line_num = MAX_AMOUNT + 1;
                while(getchar() != '\n');
        }
        return line_num;
}

int main(int argc, char **argv) {
        if (argc != 2) {
                brk_error("Usage: ./a.out file_name\n");
        }

        int fd = open(argv[1], O_RDONLY, 0); //getting file descriptor

        if (fd == -1) {
                brk_error("Error in opening file");
        }

        int table[MAX_AMOUNT] = {0}, ch_num = 0, lines = 1;
        char str[MAX_LEN] = "\0";
        int read_len = 0;

        while ((read_len = read(fd, str, MAX_LEN)) > 0) {
                for (int i = 0; i < read_len; i++) {
                        ch_num++;
                        if (str[i] == '\n') {
                                if (lines == MAX_AMOUNT) {
                                        brk_error("Too many strings!");
                                }
                                table[lines] = ch_num;
                                lines++;
                        }
                }
        }

        int line_num = 0;
        while ((line_num = get_line_num()) != 0) {
                if (line_num < 0 || lines < line_num) {
                        printf("Impossible string number!\n");
                        continue;
                }
                line_num -= 1;

                if (lseek(fd, table[line_num], SEEK_SET) == -1) {
                        brk_error("lseek error!\n");
                }

                int len = table[line_num + 1] - table[line_num];

                if (read(fd, str, len) != len) {
                        brk_error("read line error!\n");
                }

                printf("%.*s",len, str);
        }

        if (close(fd)) {
                brk_error("read file error!\n");
        }

        return 0;
}

