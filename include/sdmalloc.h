#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <linux/fcntl.h>
#include <mntent.h>

int mem_selector(size_t len, int pid);
void* sdmalloc(size_t len, int pid);
void nvm_find_path(char *path);
void nvm_gen_random(char *s, const int len);
void* nvm_malloc(size_t len);
