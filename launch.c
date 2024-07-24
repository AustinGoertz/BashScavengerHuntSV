#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>  // Include this for exit()
#include <dirent.h>
#include <libgen.h>

//TODO: Make the new file to check in the future step.
//TODO: Organize this file and test it for any possible errors.

//THIS BLOCK OF CODE EXECUTES ON SUCCESS

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

//THIS BLOCK OF CODE VERIFIES THAT THE C AND PYTHON DIRECTORIES ARE ORGANIZED CORRECTLY:

// Function to get the absolute path of a file
char* get_absolute_path(const char* filename) {
    char* abs_path = realpath(filename, NULL);
    if (abs_path == NULL) {
        perror("realpath");
        exit(EXIT_FAILURE);
    }
    return abs_path;
}

int file_exists(const char* filepath) {
    struct stat buffer;
    return (stat(filepath, &buffer) == 0);
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
        if (entry->d_type == DT_REG) { // Check if it's a regular file
            file_count++;
        }
    }

    // Close the directory
    closedir(dir);

    return file_count;
}

int verify_directory_structure() {
    return are_in_same_directory("launch.c", "prelaunch_checklist.txt");
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
    // Open a new file named "newfile.txt" for writing
    FILE *file = fopen(".CheckLaunchOrder", "w");
    
    // Check if the file was opened successfully
    if (file == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }

    // Close the file
    fclose(file);
}

int main() {

    // Puts the directory together for Python
    char dir[1000];
    get_user_directory(dir, sizeof(dir));
    const char *filename = "/.FuelUpOrderCheck"; // Added slash for proper file path
    char filepath[1024];

    // Combine directory and filename into a full path
    snprintf(filepath, sizeof(filepath), "%s%s", dir, filename);

    if (!file_exists(filepath)) {
        printf("ERROR: FUEL VALIDATION NOT FOUND:\n");
        printf("1. Enure directory input is valid.\n");
        printf("2. Ensure ship has been fueled up by ensuring fuel.py has been executed.\n");
        exit(1);
    }

    else if (count_files_in_directory(get_current_directory()) != 3) {
        printf("Error: Reorganize launch directory. (IN C)");
        exit(1);
    }
    else {
        launch();
        create_file();
        sleep(1);
        printf("Success! Proceeed to navigate.txt to see your next set of instructions.\n");
        return 0;
    }
}
