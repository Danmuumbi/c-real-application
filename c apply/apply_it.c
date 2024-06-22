#include <stdio.h>
#include <stdlib.h>

// Function prototypes
void createFile();
void readFile();
void deleteFile();

int main() {
    int choice;

    while (1) {
        printf("\nSimple File Manager\n");
        printf("1. Create File\n");
        printf("2. Read File\n");
        printf("3. Delete File\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                createFile();
                break;
            case 2:
                readFile();
                break;
            case 3:
                deleteFile();
                break;
            case 4:
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}

void createFile() {
    char filename[100];
    char content[1000];
    FILE *file;

    printf("Enter the name of the file to create: ");
    scanf("%s", filename);
    printf("Enter content for the file: ");
    getchar(); // Consume leftover newline character
    fgets(content, sizeof(content), stdin);

    file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error creating file!\n");
        return;
    }
    fprintf(file, "%s", content);
    fclose(file);
    printf("File created successfully.\n");
}

void readFile() {
    char filename[100];
    char ch;
    FILE *file;

    printf("Enter the name of the file to read: ");
    scanf("%s", filename);

    file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error reading file! Make sure the file exists.\n");
        return;
    }
    printf("File content:\n");
    while ((ch = fgetc(file)) != EOF) {
        putchar(ch);
    }
    fclose(file);
}

void deleteFile() {
    char filename[100];

    printf("Enter the name of the file to delete: ");
    scanf("%s", filename);

    if (remove(filename) == 0) {
        printf("File deleted successfully.\n");
    } else {
        printf("Error deleting file! Make sure the file exists.\n");
    }
}
