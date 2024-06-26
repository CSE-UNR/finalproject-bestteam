#include <stdio.h>

#define MAX_SIZE 1000

// Functions
void loadNewImage(char *filename, char image[][MAX_SIZE], int *width, int *height);
void displayImage(char image[][MAX_SIZE], int width, int height);
void dimImage(char image[][MAX_SIZE], int width, int height);
void brightenImage(char image[][MAX_SIZE], int width, int height);
void cropImage(char image[][MAX_SIZE], int *width, int *height);
void saveImage(char image[][MAX_SIZE], int width, int height, char *filename);

int main() {
    char filename[100];
    char image[MAX_SIZE][MAX_SIZE];
    int width = 0, height = 0;
    char option;

    do {
        // Displaying main menu
        printf("\nMenu:\n");
        printf("1. Load Image\n");
        printf("2. Display Image\n");
        printf("3. Edit Image\n");
        printf("4. Exit\n");
        printf("Choose an option: ");
        scanf(" %c", &option);

        switch (option) {
            case '1': // Load 
                printf("Enter the filename of the image: ");
                scanf("%s", filename);
                loadNewImage(filename, image, &width, &height);
                break;
            case '2': // Display
                printf("\nDisplayed Image:\n");
                displayImage(image, width, height);
                break;
            case '3': // Edit
                printf("\nEdit Options:\n");
                printf("1. Dim\n");
                printf("2. Brighten\n");
                printf("3. Crop\n");
                printf("4. Exit\n");
                printf("Choose an option: ");
                scanf(" %c", &option);
                switch (option) {
                    case '1':
                        dimImage(image, width, height);
                        break;
                    case '2':
                        brightenImage(image, width, height);
                        break;
                    case '3':
                        cropImage(image, &width, &height);
                        break;
                    case '4':
                        break;
                    default:
                        printf("Invalid edit option.\n");
                        break;
                }
                break;
            case '4':
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid option.\n");
                break;
        }
    } while (option != '4'); // Continue until the user chooses to exit

    char saveOption;
    printf("Would you like to save the edited image? (y/n): ");
    scanf(" %c", &saveOption);
    if (saveOption == 'y') {
        char saveFilename[100];
        printf("Enter the filename to save the image: ");
        scanf("%s", saveFilename);
        saveImage(image, width, height, saveFilename);
    }

    return 0;
}

// Function to load a new image from a file
void loadNewImage(char *filename, char image[][MAX_SIZE], int *width, int *height) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Could not open file.\n");
        return;
    }

    *width = 0;
    *height = 0;
    char c;


    // Read characters until the end of file
    // TA allowed me to use the fgetc/EOF. I learned the function in previous coding classes taken during high school. Was told to specify how I knew it in the notes section :)
    while ((c = fgetc(file)) != EOF && *height < MAX_SIZE) {
        // Height < MAX_SIZE = the loop doesn’t continue infinitely 
        if (c == '\n') {
            // Newline encountered, move to next row
            *width = 0;
            (*height)++;
        } else if (*width < MAX_SIZE) {
            // Store character in image array
            image[*height][*width] = c;
            (*width)++;
            printf("width: %d\n", *width); // For debugging, printing width
        }
    }

    printf("width: %d\n", *width);
    printf("height %d\n", *height);

    fclose(file);
    printf("Image loaded successfully.\n");
}

// Function to display the image
void displayImage(char image[][MAX_SIZE], int width, int height) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            printf("%c", image[i][j]);
        }
        printf("\n");
    }
}

// Function to dim the image
void dimImage(char image[][MAX_SIZE], int width, int height) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            switch (image[i][j]) {
                case '0':
                    image[i][j] = ' ';
                    break;
                case '1':
                    image[i][j] = ' ';
                    break;
                case '2':
                    image[i][j] = '.';
                    break;
                case '3':
                    image[i][j] = 'o';
                    break;
                case '4':
                    image[i][j] = 'O';
                    break;
            }
        }
    }
    printf("Image dimmed successfully.\n");
}

// Function to brighten the image
void brightenImage(char image[][MAX_SIZE], int width, int height) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            switch (image[i][j]) {
                case '0':
                    image[i][j] = '.';
                    break;
                case '1':
                    image[i][j] = 'o';
                    break;
                case '2':
                    image[i][j] = 'O';
                    break;
                case '3':
                    image[i][j] = '0';
                    break;
                case '4':
                    image[i][j] = '0';
                    break;
            }
        }
    }
    printf("Image brightened successfully.\n");
}

// Function to crop the image
void cropImage(char image[][MAX_SIZE], int *width, int *height) {
    int startRow, startCol, numRows, numCols;

    printf("Enter the starting row for cropping: ");
    scanf("%d", &startRow);
    printf("Enter the starting column for cropping: ");
    scanf("%d", &startCol);
    printf("Enter the number of rows for cropping: ");
    scanf("%d", &numRows);
    printf("Enter the number of columns for cropping: ");
    scanf("%d", &numCols);

    *width = numCols;
    *height = numRows;

    char croppedImage[MAX_SIZE][MAX_SIZE];
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            croppedImage[i][j] = image[startRow + i][startCol + j];
        }
    }

    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            image[i][j] = croppedImage[i][j];
        }
    }

    printf("Image cropped successfully.\n");
}

// Function to save the image to a file
void saveImage(char image[][MAX_SIZE], int width, int height, char *filename) {
    char saveOption;
    printf("Do you want to save the edited image? (y/n): ");
    scanf(" %c", &saveOption);
    if (saveOption == 'y') {
        FILE *file = fopen(filename, "w");
        if (file == NULL) {
            printf("Error: Could not open file for writing.\n");
            return;
        }

        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                fprintf(file, "%c", image[i][j]);
            }
            fprintf(file, "\n");
        }

        fclose(file);
        printf("Image saved successfully.\n");
    }
    else {
        printf("Image not saved.\n");
    }
}
