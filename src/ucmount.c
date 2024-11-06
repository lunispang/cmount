#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char **argv) {
	char *prefix = "umount -l /mnt/";
	int size = strlen(prefix) + strlen(argv[1]) + 1;
	char *command = calloc(size, 1);
	snprintf(command, size, "%s%s", prefix, argv[1]);
	if (system(command)) {
		perror("unmount failed");
	}

	execl("/usr/bin/cryptsetup", "cryptsetup", "close", argv[1], 0);
	perror("exec failed");
	return -1;
}