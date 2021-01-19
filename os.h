//OS specific header file containing stuff which has to be ported to other operating systems
#include <sys/stat.h>

int getFileSize(char path[]) {
	struct stat st;
	stat(path, &st);
	return st.st_size;
}
