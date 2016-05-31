#include <stdlib.h>
#include <stdio.h>
#include <mntent.h>

void find_path(char *path);
void gen_random(char *s, const int len);
int mem_selector(size_t len);
void* auto_malloc(size_t len);
void* ssd_malloc(size_t len);
void* sdmalloc(size_t len, int flag);
