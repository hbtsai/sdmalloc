#include "sdmalloc.h"

/*
 * interact with SDMAD (Software Defined Memory Allocator daemon),
 */



/*
 * socket client to find candidate memory device to allocate memory
 */
void find_candidate()
{

}

void* auto_malloc(size_t len)
{
  void* ptr = NULL;
  return ptr;
}

void gen_random(char *s, const int len) {

    static const char alphanum[] =     "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

        int i;
    for (i = 0; i < len; ++i) {
                s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
            }

    s[len] = 0;
}

void find_path(char *path)
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
      fprintf(stderr, "%s:%d fsname=%s dir=%s\n", __FILE__, __LINE__, ent->mnt_fsname, ent->mnt_dir);
      if(strcmp(ent->mnt_fsname, "sdmalloc")==0)
        {
          strcpy(path, ent->mnt_dir);
        }
    }
  endmntent(a);
}


void* ssd_malloc(size_t len)
{
  void* ptr = NULL;
  int fd = 0;
  // find a mount point name "sdmalloc"
  char path[128]={'\0'};
  find_path(path);
  fprintf(stderr, "%s:%d path=%s\n", __FILE__, __LINE__, path);

  // generate a random file name
  char fname[16]={'\0'};
  char mem_file[128]={'\0'};
  gen_random(fname, 8);
  sprintf(mem_file, "%s/%s", path, fname);
  fprintf(stderr, "%s:%d path=%s\n", __FILE__, __LINE__, mem_file);

  fd = open(mem_file, O_CREAT | O_RDWR, 0600);
  fallocate(fd, 0, 0, len);
  close(fd);

  // fallocate a random file at ssd mount point

  // mmap the file



  return ptr;
}

int mem_selector(size_t len)
{
  return 0;
}

void* sdmalloc(size_t len, int flag)
{
  void* ptr=NULL;
  switch(flag)
    {
    case 0:
      ptr = malloc(len);
      break;
    case 1:
      ptr = auto_malloc(len); // main memory preferred, else ssd
      break;
    case 2:
      ptr = ssd_malloc(len); // ssd.
      break;
    default:
      ptr = malloc(len);
      break;
    }

  return ptr;
}
