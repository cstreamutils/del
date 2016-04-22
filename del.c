#ifndef DEL_H
#define DEL_H
#include "del.h"
#endif
#include <stdio.h>

size_t init_regex(struct regex* regx, char *pattern, int flags)
{
	int i, ret;
	for (i = 0; pattern[i] != '\0'; i++);
	regx->size = i;
	regx->flags = flags;
	regcomp(&regx->pattern,pattern,flags);
	return ret;
}

int remove_from_string(char *string, int start, int end) 
{
	int i;
	for (i = 0;string[end + i] != '\0'; i++) {
		string[start + i] = string[end + i];
	}
	return end - start;
}

int main(int argc, char **argv)
{
	char in_buf[BUF_SIZE];
	int ret; 
	ssize_t num_read, num_written;
	struct regex regx;

	if (argc != 2) {
		fprintf(stderr, "usage: del <regex to remove>\n");
		return 1;
	}

	if (isatty(STDIN_FILENO)) {
		fprintf(stderr, "no data in stdin stream\n");
		return 1;
	}

	init_regex(&regx, argv[1], 0);

	while ((num_read = read(STDIN_FILENO, in_buf, BUF_SIZE)) != 0) {
		while ((ret = regexec(&regx.pattern, in_buf, 1, &regx.match, regx.flags)) == 0) {
			ret = remove_from_string(in_buf, regx.match.rm_so, regx.match.rm_eo);
			num_read -= ret;
		}
	  	num_written = write(STDOUT_FILENO, in_buf, num_read);
	}
	return 0;
}
