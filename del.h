#include <regex.h>
#include <string.h>
#include <unistd.h>

#ifndef BUF_SIZE
#define BUF_SIZE 1024
#endif

struct regex {
	regex_t pattern;
	int flags;
	size_t size;
	char re[1];
	regmatch_t match;
};

size_t init_regex(struct regex* regx, char *pattern, int flags);
int remove_from_string(char *string, int start, int end);
