#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// ------------------------- Structure Definitions -------------------------

// Structure to represent a File
typedef struct File {
    char *filename; 
    struct File* next;
} File;

// Structure to represent a Directory
typedef struct Directory {
    char *directoryName; 
    struct Directory* subdirectories; // Head of subdirectories linked list
    struct Directory* next;           // Next sibling directory
    File* files;                      // Head of files linked list
    struct Directory* parent;         // Pointer to parent directory
} Directory;

// Structure to represent the File System
typedef struct FileSystem {
    Directory* rootDirectory;
} FileSystem;

// ------------------------- Function Prototypes ------------------------
// File-related functions
File* create_file(const char* filename);
int add_file(Directory* dir, const char* filename);

// Directory-related functions
Directory* create_directory(const char* name);
int add_directory(Directory* parent, const char* name);
Directory* change_directory(Directory* currentDir, const char* name);
void print_directory_contents(Directory* dir);
// Directory* create_directory(const char* directoryName,Directory* parent);
Directory* add_subdirectory(Directory* dir, const char* directoryName);
// FileSystem-related functions
FileSystem* create_filesystem(const char* rootName);
void print_filesystem(FileSystem* fs);
File* find_file(FileSystem* fs,const char* filename);
File* find_file_recursively(Directory* dir,const char* filename);
Directory* find_directory_recurisve(Directory* dir,const char* directoryName);
Directory* find_directory(FileSystem *fs, const char* directoryName);
void print_filesystem(FileSystem *fs);
void print_filesystem_recursive(Directory* dir,int level);
void print_directory_contents(Directory* dir);
int isValidString(const char* str);
Directory* getDirectoryByPath(Directory* root,const char* path);
Directory* getDirectSubdirectory(Directory* parent,const char*dirName);
// Operations
void trim_newline(char* str);

// ------------------------- Function Implementations -------------------------

// Allocate memory for the file system
FileSystem* create_filesystem(const char* rootName) {
    FileSystem* fs = (FileSystem*)malloc(sizeof(FileSystem));
    fs->rootDirectory = create_directory(rootName);
    return fs;
}

// Create a file struct and return its pointer
File* create_file(const char* filename) {
    File* newFile = (File*)malloc(sizeof(File));
    newFile->filename = (char*)malloc(strlen(filename) + 1); // Allocate memory for filename
    strcpy(newFile->filename, filename);
    newFile->next = NULL;
    return newFile;
}

// Create a directory struct and return its pointer
Directory* create_directory(const char* name) {
    Directory* newDir = (Directory*)malloc(sizeof(Directory));
    newDir->directoryName = (char*)malloc(strlen(name) + 1); // Allocate memory for directory name
    strcpy(newDir->directoryName, name);
    newDir->subdirectories = NULL;
    newDir->next = NULL;
    newDir->files = NULL;
    newDir->parent = NULL;
    return newDir;
}

// Add a file of given filename to a given directory
int add_file(Directory* dir, const char* filename) {
    // Check if a file with the same name already exists
    File* currentFile = dir->files;
    while (currentFile) {
        if (strcmp(currentFile->filename, filename) == 0) {
            return 0; 
        }
        currentFile = currentFile->next;
    }

    // File does not exist, proceed to add it
    File* newFile = create_file(filename);
    newFile->next = dir->files; 
    dir->files = newFile;
    return 1; 
}

// Create a new subdirectory with given name in a given directory
int add_directory(Directory* parent, const char* name) {
    // Check if a subdirectory with the same name already exists
    Directory* currentDir = parent->subdirectories;
    while (currentDir) {
        if (strcmp(currentDir->directoryName, name) == 0) {
            return 0;
        }
        currentDir = currentDir->next;
    }

    // Subdirectory does not exist, proceed to add it
    Directory* newDir = create_directory(name);
    newDir->parent = parent; // Set parent
    newDir->next = parent->subdirectories; // Insert at the beginning
    parent->subdirectories = newDir;
    return 1; // Success
}

// Change directory
Directory* change_directory(Directory* currentDir, const char* name) {
    if (strcmp(name, "..") == 0 && currentDir->parent) 
    {
        return currentDir->parent; 
    } 
    else 
    {
        Directory* subDir = currentDir->subdirectories;
        while (subDir) {
            if (strcmp(subDir->directoryName, name) == 0) {
                return subDir; 
            }
            subDir = subDir->next;
        }
    }
    return NULL; 
}

// Print the contents of a particular directory
void print_directory_contents(Directory* dir) {
    printf("Directory: %s\n", dir->directoryName);
    // Print subdirectories
    Directory* currentDir = dir->subdirectories;
    if (currentDir) {
        printf("  Subdirectories:\n");
        while (currentDir) {
            printf("    - %s (Directory)\n", currentDir->directoryName);
            currentDir = currentDir->next;
        }
    } else {
        printf("  No subdirectories.\n");
    }

    // Print files
    File* currentFile = dir->files;
    if (currentFile) {
        printf("  Files:\n");
        while (currentFile) {
            printf("    - %s (File)\n", currentFile->filename);
            currentFile = currentFile->next;
        }
    } else {
        printf("  No files.\n");
    }
}

// Print the entire file system
void print_filesystem(FileSystem* fs) {
    if (!fs || !fs->rootDirectory) {
        printf("File system is empty.\n");
        return;
    }
    print_directory_contents(fs->rootDirectory);
}

// Trim newline character from string
void trim_newline(char* str) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

int main() {
    FileSystem* fs = create_filesystem("root");
    Directory* currentDir = fs->rootDirectory; 
    char input[256];

    printf("Welcome to the In-Memory File System!\n");
    printf("Available commands:\n");
    printf("  cd <directory_name>\n");
    printf("  mkdir <directory_name>\n");
    printf("  touch <file_name>\n");
    printf("  ls\n");
    printf("  exit\n\n");

    while (1) {
        printf(">> "); // Prompt

        // Read input from the user
        if (!fgets(input, sizeof(input), stdin)) {
            printf("Error reading input. Exiting.\n");
            break;
        }

        // Remove the trailing newline character
        trim_newline(input);

        // Check for empty input
        if (strlen(input) == 0) {
            continue;
        }

        // Tokenize the input into command and argument
        char* command = strtok(input, " ");
        char* argument = strtok(NULL, " ");

        // Handle commands
        if (strcmp(command, "cd") == 0) 
        {
            Directory* newDir = change_directory(currentDir, argument);
            if (newDir) 
            {
                currentDir = newDir; 
            } 
            else 
            {
                printf("Directory not found: %s\n", argument);
            }
        } 
        else if (strcmp(command, "mkdir") == 0) 
        {
            if (add_directory(currentDir, argument)) 
            {
                printf("Directory created: %s\n", argument);
            } 
            else 
            {
                printf("Directory already exists: %s\n", argument);
            }
        } 
        else if (strcmp(command, "touch") == 0) 
        {
            if (add_file(currentDir, argument)) 
            {
                printf("File created: %s\n", argument);
            } 
            else 
            {
                printf("File already exists: %s\n", argument);
            }
        } 
        else if (strcmp(command, "ls") == 0) 
        {
            print_directory_contents(currentDir);
        } 
        else if (strcmp(command, "exit") == 0) 
        {
            break;
        } 
        else 
        {
            printf("Unknown command: %s\n", command);
        }
    }

    return 0;
}
