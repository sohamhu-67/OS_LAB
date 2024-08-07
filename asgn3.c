#include <stdio.h>
#include <stdlib.h>
#include <dirent.h> 
#include <errno.h>  
#include <string.h> 
int main() {
    DIR *dir;                   
    struct dirent *entry;       
    char dir_name[256];         

    // Get directory name
    printf("Enter directory name: ");
    if (fgets(dir_name, sizeof(dir_name), stdin) == NULL) {
        perror("Failed to read directory name");
        return EXIT_FAILURE;
    }
    
    // Remove newline character from the input if present
    dir_name[strcspn(dir_name, "\n")] = '\0';

    //  Open directory
    dir = opendir(dir_name);
    if (dir == NULL) {
        fprintf(stderr, "Error opening directory '%s': %s\n", dir_name, strerror(errno));
        return EXIT_FAILURE;
    }

    //  Read content of the directory
    printf("Contents of directory '%s':\n", dir_name);
    while ((entry = readdir(dir)) != NULL) {
        printf("%s\n", entry->d_name);
    }

    // Close directory
    if (closedir(dir) == -1) {
        fprintf(stderr, "Error closing directory '%s': %s\n", dir_name, strerror(errno));
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

