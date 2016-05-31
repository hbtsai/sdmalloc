#include "sdmalloc.h"

/*
 * interact with SDMAD (Software Defined Memory Allocator daemon),
 */

int mem_selector(size_t len, int pid)
{

	// for debug purpose, default target to 1
	int target = 2;

	return target;
}

void sdfree(void* p)
{

}

void* sdmalloc(size_t len, int pid)
{
	void *p = NULL;
	int target = mem_selector(len, pid);
	if (target < 0 )
	{
		fprintf(stderr, "ERR: cannot find candidate\n");
		exit(-1);
	}

	// 1=in-memory, 2=ssd
	switch(target)
	{
		case 1:
			p = malloc(len);
			break;
		case 2:
			p = nvm_malloc(len);
			break;
		default:
			break;
	};
}

void nvm_gen_random(char *s, const int len) {

    static const char alphanum[] =     "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

        int i;
    for (i = 0; i < len; ++i) {
                s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
            }

    s[len] = 0;
}

void nvm_find_path(char *path)
{
  struct mntent *ent;
  FILE *a;
  a = setmntent("/proc/mounts", "r");
  if(a==NULL)
    {
      perror("setmntent");
      exit(1);
    }
  while(NULL != (ent = getmntent(a)))
    {
      if(strstr(ent->mnt_dir, "sdmalloc")!=NULL)
        {
          strcpy(path, ent->mnt_dir);
		  break;
        }
    }
  endmntent(a);
}


void* nvm_malloc(size_t len)
{
  void* ptr = NULL;
  int fd = 0;
  // find a mount point name "sdmalloc"
  char path[128]={'\0'};
  nvm_find_path(path);
  
  fprintf(stderr, "%s:%d path=%s\n", __FILE__, __LINE__, path);

  // generate a random file name
  char fname[16]={'\0'};
  char mem_file[128]={'\0'};
  nvm_gen_random(fname, 8);
  sprintf(mem_file, "%s/%s", path, fname);

  fprintf(stderr, "%s:%d path=%s\n", __FILE__, __LINE__, mem_file);

  fd = open(mem_file, O_CREAT | O_RDWR, 0600);
  fallocate(fd, 0, 0, len);
  close(fd);

  // mmap the file
ptr = mmap(0, len, PROT_READ| PROT_WRITE, MAP_PRIVATE, fd, 0)


  return ptr;
}


