#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>
#include <pwd.h>
#include <time.h>


int judge_dir(char* dir_name);
void display_mode(int mode);
void show_file_state(char * file_name,int depth);
void print_dir(char* dir_path, int depth);
void display_time(time_t tt);

int main(int argc, char* argv[]) {
    char file_name[256];
    if(argc == 1) {
        getcwd(file_name, 256);
    } else if(argc == 2){
        strcpy(file_name, argv[1]);
    } else {
        perror("wrong arguments number! Help: exp4 or exp4 <path>");
    }

    show_file_state(file_name,0);
    print_dir(file_name,1);

}

int judge_dir(char* dir_name) {
    if(strcmp(dir_name, ".")==0 || strcmp(dir_name, "..")==0) {
        return 0;
    } else {
        return 1;
    }
}

void display_mode(int mode) {

    char str[11] = {0};

    str[0] = mode & S_IFDIR ? 'd' : '-'; // directory

    str[1] = mode & S_IRUSR ? 'r' : '-'; // user
    str[2] = mode & S_IWUSR ? 'w' : '-';
    str[3] = mode & S_IXUSR ? 'x' : '-';

    str[4] = mode & S_IRGRP ? 'r' : '-'; // group
    str[5] = mode & S_IWGRP ? 'w' : '-';
    str[6] = mode & S_IXGRP ? 'x' : '-';

    str[7] = mode & S_IROTH ? 'r' : '-'; // other
    str[8] = mode & S_IWOTH ? 'w' : '-';
    str[9] = mode & S_IXOTH ? 'x' : '-';

    printf("%s", str);
}

void show_file_state(char * file_name,int depth) {
    struct stat file_state;
    stat(file_name, &file_state);

    for(int i =0; i<depth; i++) {
        printf("\t");
    }
    if(depth != 0) printf("|_ ");

    display_mode((file_state.st_mode));
    struct passwd *pwd;

    pwd = getpwuid(file_state.st_uid);
    if(pwd !=NULL) {
        printf(" %s", pwd->pw_name);
    } else {
        printf(" %s", "Null");
    }
    printf(" %d",file_state.st_size);
    display_time(file_state.st_mtime);
    printf(" %s\n", file_name);
}

void print_dir(char* dir_path, int depth) {
    DIR* cur_dir = opendir(dir_path);
    struct dirent* entry = NULL;

    if(cur_dir == NULL) {
        printf("%s\n",dir_path);
        perror("the dir_path illegal.\n");
    }

    chdir(dir_path);

    while((entry = readdir(cur_dir) )!= NULL) {
        if(entry->d_type == DT_DIR) {
            if(judge_dir(entry->d_name)==0) {
                continue;
            } else {
                show_file_state(entry->d_name,depth);
                print_dir(entry->d_name, depth+1);
            }
        } else {
            show_file_state(entry->d_name,depth);
        }
    }

    chdir("..");// too important;
    closedir(cur_dir);
}

void display_time(time_t tt) {
    struct tm *stm = localtime(&tt);
    char tmp[32];
    printf(" %04d-%02d-%02d-%2d:%2d:%02d", 1900 + stm->tm_year, 1 + stm->tm_mon, stm->tm_mday, stm->tm_hour,
            stm->tm_min, stm->tm_sec);
}