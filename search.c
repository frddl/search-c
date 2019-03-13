#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <memory.h>
#include <pwd.h>
#include <grp.h>

char *argN, *argL, *argU, *argG, *argSCMP, *argSSIZE, *argW;
char *filename;
int prevlen = 0;

int comparator(const struct dirent **a, const struct dirent **b) {
  return strcmp((*a)->d_name, (*b)->d_name);
}

int updatefilename(char *a){
  prevlen = strlen(filename);
  char * new = (char *) malloc(1 + strlen(filename)+ strlen(a));
  strcpy(new, filename);
  strcat(new, a);
  filename = (char *) malloc(1+strlen(new));
  strcpy(filename, new);
}

int undofilename(){
  filename[prevlen] = '\0';
}

int list(char *a){
  struct dirent **namelist;
  int n = scandir(a, &namelist, 0, comparator);
  int p = 0;

  while (p < n){
    printf("%s\n", namelist[p]->d_name);
    p++;
  }
}

int recsearch(char *a, char *b, char *c){
  DIR* currdir = opendir(".");
  struct dirent* dir;
  struct stat fstat;
  struct stat fileStat;

  if (currdir){
    while ((dir = readdir(currdir))){
      stat(dir->d_name, &fstat);
      lstat(dir->d_name,&fileStat);
      if (S_ISDIR(fstat.st_mode) && strcmp(dir->d_name, ".") && strcmp(dir->d_name, "..")){
        chdir(dir->d_name);
        //updatefilename(dir->d_name); //ENABLE THIS TO PRINT FULL PATH
        recsearch(dir->d_name, b, c);
        chdir("..");
        //undofilename(); //ENABLE THIS TO PRINT FULL PATH
      } else {
        if (!strcmp(b, "N")){
          if (strstr(dir->d_name, c) != NULL)
            printf("%s%s\n", filename, dir->d_name);
        }

        else if (!strcmp(b, "L")){
          if ((S_ISLNK(fileStat.st_mode)))
            printf("%s%s\n", filename, dir->d_name);
        }

        else if (!strcmp(b, "U")){
          struct passwd *pw = getpwuid(fstat.st_uid);
          if (pw != 0 && !strcmp(pw->pw_name, c))
            printf("%s%s\n", filename, dir->d_name);
        }

        else if (!strcmp(b, "G")){
          struct group *gr = getgrgid(fstat.st_gid);
          if (gr != 0 && !strcmp(gr->gr_name, c))
            printf("%s%s\n", filename, dir->d_name);
        }

        else if (!strcmp(b, "SL")){
          if ((fileStat.st_size) < atoi(argSSIZE))
            printf("%s%s\n", filename, dir->d_name);
        }

        else if (!strcmp(b, "SE")){
          if ((fileStat.st_size) = atoi(argSSIZE))
            printf("%s%s\n", filename, dir->d_name);
        }

        else if (!strcmp(b, "SG")){
          if ((fileStat.st_size) > atoi(argSSIZE))
            printf("%s%s\n", filename, dir->d_name);
        }

        else if (!strcmp(b, "W")){
            FILE *file;
            char line[BUFSIZ];
            int linenumber = 0;
            file = fopen(dir->d_name, "r");
            if(file != NULL){
              while(fgets(line, sizeof(line), file)){
                if(strstr(line, argW) != NULL){
                printf("%s%s\n", filename, dir->d_name);
                break;
              }
              ++linenumber;
            }
          }
        }
      }
    }

    closedir(currdir);
  }
}

int process(int argc, char *argv[]){
  for (int i = 1; i < argc; i++){
    if (!strcmp(argv[i], "-N")){
      argN = argv[i+1];
    } else if (!strcmp(argv[i], "-L")){
      argL = "L";
    } else if (!strcmp(argv[i], "-U")){
      argU = argv[i+1];
    } else if (!strcmp(argv[i], "-G")){
      argG = argv[i+1];
    } else if (!strcmp(argv[i], "-S")){
      argSCMP = argv[i+1];
      argSSIZE = argv[i+2];
    } else if (!strcmp(argv[i], "-W")){
      argW = argv[i+1];
    }
  }
}

int main(int argc, char *argv[]) {
  filename = "";

  if (argc == 1)
    list(".");
  else if (argc > 1){
    process(argc, argv);
    if (argN != NULL){
      recsearch(".", "N", argN);
    } else if (argL != NULL){
      recsearch(".", "L", "");
    } else if (argU != NULL){
      recsearch(".", "U", argU);
    } else if (argG != NULL){
      recsearch(".", "G", argG);
    } else if (argSCMP != NULL){
      if (!strcmp(argSCMP, "L")){
        recsearch(".", "SL", argSSIZE);
      } else if (!strcmp(argSCMP, "E")){
        recsearch(".", "SE", argSSIZE);
      } else if (!strcmp(argSCMP, "G")){
        recsearch(".", "SG", argSSIZE);
      }
    } else if (argW != NULL){
      recsearch(".", "W", argW);
    }
  }

}
