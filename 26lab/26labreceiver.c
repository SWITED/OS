#include <stdio.h>
#include <ctype.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#define BUFFER_SIZE 256

int main() {
        
        char bufferArray[BUFFER_SIZE];
        int readBytesInt;

        while (1) {
            if ((readBytesInt = read(STDIN_FILENO, bufferArray, BUFFER_SIZE)) <= 0) {
                if (errno == EINTR) {
                    errno = 0;
                    continue;
                }
                else {
                    break;
                }
            }

            for (int i = 0; i < readBytesInt; i++) {
                    bufferArray[i] = toupper(bufferArray[i]);
            }

            if (write(STDOUT_FILENO, bufferArray, readBytesInt) == -1) {
                perror("Write ERROR : STR30");
		return -1;
            }
        }

        if (readBytesInt == -1) {   
            perror("read ERROR : STR16");
	    return -1;
        }
        return 0;
}
