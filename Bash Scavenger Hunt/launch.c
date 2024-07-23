#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <libgen.h>
#include <limits.h>  // Include for realpath and PATH_MAX
#include <windows.h>

// Function prototypes
void launch(void);
void get_user_directory(char *buffer, size_t size);
char* get_current_directory(void);
void create_file(void);
int file_exists(const char* filepath);
int count_files_in_directory(const char* directory_path);

char* realpath(const char* path, char* resolved_path) {
    // Get the full path
    DWORD path_length = GetFullPathName(path, MAX_PATH, resolved_path, NULL);
    
    if (path_length == 0) {
        // Error occurred
        fprintf(stderr, "Error getting full path for '%s'\n", path);
        return NULL;
    }

    // Return the resolved path
    return resolved_path;
}

// Function to get the absolute path of a file
char* get_absolute_path(const char* filename) {
    char* abs_path = realpath(filename, NULL);
    if (abs_path == NULL) {
        perror("realpath");
        exit(EXIT_FAILURE);
    }
    return abs_path;
}

// Function to check if two files are in the same directory
int are_in_same_directory(const char* file1, const char* file2) {
    char* abs_path1 = get_absolute_path(file1);
    char* abs_path2 = get_absolute_path(file2);

    int result = strcmp(dirname(abs_path1), dirname(abs_path2)) == 0;

    free(abs_path1);
    free(abs_path2);

    return result;
}

void get_user_directory(char *buffer, size_t size) {
    // Reading a line of text
    printf("Enter the directory you put the fueling data in (Hint: Use the pwd Command): ");
    fgets(buffer, size, stdin);

    // Removing the newline character if present
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len-1] == '\n') {
        buffer[len-1] = '\0';
    }

    printf("You entered this directory: %s\n", buffer);
}

char* get_current_directory() {
    static char cwd[1024]; // Make it static so it persists after the function returns
    
    // Get the current working directory
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        return cwd;
    } else {
        perror("getcwd() error");
        exit(EXIT_FAILURE);
    }
}

void create_file() {
    // Open a new file named ".CheckLaunchOrder" for writing
    FILE *file = fopen(".CheckLaunchOrder", "w");
    
    // Check if the file was opened successfully
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    // Close the file
    fclose(file);
}

// Function definition for launch
void launch() {
    int countdown = 10;

    // Print the countdown
    for (int i = countdown; i > 0; i--) {
        printf("%d\n", i);
        fflush(stdout);  // Ensure the output is immediately printed
        sleep(1);        // Wait for 1 second
    }
    // Print launch message
    printf("Liftoff!\n");
}

int file_exists(const char* filepath) {
    struct stat buffer;
    return (stat(filepath, &buffer) == 0);
}

int count_files_in_directory(const char* directory_path) {
    DIR* dir;
    struct dirent* entry;
    int file_count = 0;

    // Open the directory
    dir = opendir(directory_path);
    if (dir == NULL) {
        perror("opendir");
        exit(EXIT_FAILURE);
    }

    // Count the files in the directory
    while ((entry = readdir(dir)) != NULL) {
        // Skip "." and ".."
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        // Check if it's a regular file using stat
        struct stat statbuf;
        char path[PATH_MAX];

        snprintf(path, sizeof(path), "%s/%s", directory_path, entry->d_name);
        if (stat(path, &statbuf) == 0 && S_ISREG(statbuf.st_mode)) {
            file_count++;
        }
    }

    // Close the directory
    closedir(dir);

    return file_count;
}

int main() {
    char dir[1000];
    get_user_directory(dir, sizeof(dir));
    const char *filename = "/.FuelUpOrderCheck"; // Added slash for proper file path
    char filepath[1024];

    // Combine directory and filename into a full path
    snprintf(filepath, sizeof(filepath), "%s%s", dir, filename);

    if (!file_exists(filepath)) {
        fprintf(stderr, "ERROR: FUEL VALIDATION NOT FOUND:\n");
        fprintf(stderr, "1. Ensure directory input is valid.\n");
        fprintf(stderr, "2. Ensure ship has been fueled up by ensuring fuel.py has been executed.\n");
        exit(EXIT_FAILURE);
    }

    else if (count_files_in_directory(get_current_directory()) != 3) {
        fprintf(stderr, "Error: Reorganize launch directory. (IN C)\n");
        exit(EXIT_FAILURE);
    }
    else {
        launch();
        create_file();
        sleep(1);
        printf("Success! Proceed to navigate.txt to see your next set of instructions.\n");
        return 0;
    }
}
