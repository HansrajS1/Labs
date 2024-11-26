#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024 

void createFile(const char *filename);
void readFile(const char *filename);
void writeFile(const char *filename);
void updateFile(const char *filename);

int main() {
    const char *filename = "app.txt";
    int choice;

    createFile(filename);

    while (1) {
        printf("\nFile Operations Menu:\n");
        printf("1. Read file\n");
        printf("2. Write to file\n");
        printf("3. Update (append) file\n");
        printf("4. Close file and exit\n");
        printf("Enter your choice (1-4): ");
        
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number between 1 and 4.\n");
            while (getchar() != '\n'); 
            continue;
        }
        while (getchar() != '\n'); 
        
        switch (choice) {
            case 1:
                readFile(filename);
                break;
            case 2:
                writeFile(filename);
                break;
            case 3:
                updateFile(filename);
                break;
            case 4:
                printf("Exiting program.\n");
                exit(EXIT_SUCCESS);
            default:
                printf("Invalid choice. Please enter a number between 1 and 4.\n");
                break;
        }
    }
}

void createFile(const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error creating file");
        exit(EXIT_FAILURE);
    }
    fclose(file);
    printf("File '%s' created successfully.\n", filename);
}

void readFile(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file for reading");
        exit(EXIT_FAILURE);
    }

    char buffer[BUFFER_SIZE];
    printf("File contents:\n");
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        printf("%s", buffer);
    }

    fclose(file);
}

void writeFile(const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file for writing");
        exit(EXIT_FAILURE);
    }
    char input[BUFFER_SIZE];
    printf("Enter the text to write to the file (end with an empty line):\n");
    
    
    while (fgets(input, sizeof(input), stdin) != NULL) {
        if (input[0] == '\n') break; 
        fprintf(file, "%s", input);
    }

    fclose(file);
    printf("Text written to file '%s'.\n", filename);
}



void updateFile(const char *filename) {
    FILE *file = fopen(filename, "a");
    if (file == NULL) {
        perror("Error opening file for appending");
        exit(EXIT_FAILURE);
    }
    
    char input[BUFFER_SIZE];
    printf("Enter the text to append to the file (end with an empty line):\n");
    
    while (fgets(input, sizeof(input), stdin) != NULL) {
        if (input[0] == '\n') break;
        fprintf(file, "%s", input);
    }

    fclose(file);
    printf("Text appended to file '%s'.\n", filename);
}

