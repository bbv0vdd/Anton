#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>
#include <errno.h>
#include <utime.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(const int argc, char** argv)
{
    const struct option long_option[] =
    {
        {"help", no_argument, NULL, 'h'},
        {"verbose", no_argument, NULL, 'v'}, 
        {"interactive", no_argument, NULL, 'i'},
        {"force", no_argument, NULL, 'f'},
        {"preserv", no_argument, NULL, 'p'},
        {NULL, no_argument, NULL, 0}
    };

    int opt, long_index;
    const char short_option[] = "hvifp";
    int flag_h = 0, flag_v = 0, flag_i = 0, flag_f = 0, flag_p = 0;
    while((opt = getopt_long(argc, argv, short_option, long_option, &long_index)) != -1)
    {
        switch(opt)
        {
        case 'h': flag_h = 1;
            break;
        case 'v': flag_v = 1;
            break;
        case 'i': flag_i = 1;
            break;
        case 'f': flag_f = 1;
            break;
        case 'p': flag_p = 1;
            break;;
        }
    }
    char copy_file[255];
    char dest_file[255];
    if(argc - optind == 2)
    {
        strcpy(copy_file, argv[optind]);
        strcpy(dest_file, argv[optind + 1]);
    }
    else if(argc == optind && argc != 1){}

    else
    {
        printf("dodik, not this command\n");
        flag_v = 0;
        return 0;
    }
    
    FILE* f1 = fopen(copy_file, "r");
    FILE* f2 = fopen(dest_file, "w");
    char* str = (char*)calloc(1000, sizeof(char));
    
    if(flag_h)
        printf("instruction\n");

    char answer[10];
    if(flag_i)
    {
        if(f2)
        {
            printf("Are you sure?\n");
            scanf("%s", answer);
        }
        if(strcmp(answer, "yes") == 0)
        {
            while(fgets(str, 1000, f1))
                fprintf(f2, "%s", str);
        }
        else if(strcmp(answer, "no") == 0)
        {
            free(str);
            fclose(f1);
            fclose(f2);
            return 0;
        }
    }
    else
    {
        while(fgets(str, 10, f1))
            fprintf(f2, "%s", str);
    }

    if(flag_f)
    {
        while(fgets(str, 10, f1))
            fprintf(f2, "%s", str);
        if(errno == 9)
        {
            remove(dest_file);
            fseek(f1, 0, SEEK_SET);
            f2 = fopen(dest_file, "w");
        }
        while(fgets(str, 10, f1))
            fprintf(f2, "%s", str);
    }
    if(flag_p)
    {
        struct stat copy_file_buff;
        stat(copy_file, &copy_file_buff);

        struct utimbuf copy_file_meta_data;
        
        copy_file_meta_data.actime = copy_file_buff.st_atim.tv_sec;
        copy_file_meta_data.modtime = copy_file_buff.st_ctim.tv_sec;
        utime(dest_file, &copy_file_meta_data);
        chmod(dest_file, copy_file_buff.st_mode);
        chown(dest_file, copy_file_buff.st_uid, copy_file_buff.st_gid);
    }
    if(flag_v && errno != 9)
        printf("%s > %s\n", copy_file, dest_file);



    fclose(f1);
    fclose(f2);
    free(str);
    return 0;
}
//---------------------------------------------------------------------
