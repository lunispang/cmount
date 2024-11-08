#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void usage() {
	printf("usage: cmount <file> [name]\n");
}

int main(int argc, char **argv) {
	const char *name = argv[1];

	if (argc == 1) {
		usage();
		return 1;
	}

	if (argc > 2) {
		name = argv[2];
	}

	const char *mapper = "/dev/mapper/";
	int size = strlen(mapper) + strlen(name) + 1;
	char *mount = calloc(size, 1);
	snprintf(mount, size, "%s%s", mapper, name);

	if (access(mount, F_OK)) {
		char *prefix = "cryptsetup open";
		int command_size = strlen(prefix) + strlen(argv[1]) + strlen(name) + 3;
		char *command = calloc(command_size, 1);
		snprintf(command, command_size, "%s %s %s", prefix, argv[1], name);
		printf("Running: cryptsetup open %s %s\n", argv[1], name);
		if (system(command)) {
			perror("Cryptsetup Error");
		}
	} else {
		printf("Mapped file detected, skipping cryptsetup open\n");
	}

	const char *mnt = "/mnt/";
	size = strlen(mnt) + strlen(name) + 1;
	char *mount_point = calloc(size, 1);
	snprintf(mount_point, size, "%s%s", mnt, name);

	printf("Running mount...\n");
	if (execlp("mount", "mount", "--mkdir", mount, mount_point, 0)) {
		perror("Mount Error");
		return 2;
	}

	perror("Should never be here, since exec replaces program image.\n");
	return -1;
}
