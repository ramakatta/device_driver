#include <dirent.h>
#include <stdio.h>
/* List all files in directory 'dirPath' */
static void listFiles(const char *dirpath)
{
  DIR *dirp;
  struct dirent *dp;
  int isCurrent;
  int errno = 0;
  /* True if 'dirpath' is "." */
  isCurrent = strcmp(dirpath, ".") == 0;
  dirp = opendir(dirpath);
  if (dirp == NULL) {
    printf("opendir failed on '%s'", dirpath);
    return;
  }
  /* For each entry in this directory, print directory + filename */
  for (;;) {
    dp = readdir(dirp);
    if (dp == NULL)
       break;
    /* To distinguish error from end-of-directory */
    if (strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0)
       continue;
   /* Skip . and .. */
   if (!isCurrent)
      printf("%s/", dirpath);
     printf("%s\n", dp->d_name);
   }
   if (errno != 0)
      perror("readdir");
   if (closedir(dirp) == -1)
      perror("closedir");
}
int main(int argc, char *argv[])
{
  if (argc > 1 && strcmp(argv[1], "--help") == 0)
     printf("%s [dir...]\n", argv[0]);
  if (argc == 1)
     listFiles(".");
  else {
    for (argv++; *argv; argv++)
       listFiles(*argv);
  }
  /* No arguments - use current directory */
}
