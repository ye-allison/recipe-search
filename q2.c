//This program reads and writes files for recipes, including their name, ingredients, and secret ingregients
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "q2.h"

//Print menu for user to choose from
void menu(){
    printf("\nMENU\n");
    printf("a) Print All Records\n");
    printf("b) Search Recipe By Name\n");
    printf("c) Write Recipe To File\n");
    printf("d) Search By Secret Ingredient\n");
    printf("e) Search By Ingredient\n");
    printf("f) Store User Recipes\n");
    printf("g) Quit\n");
}

//Print all recipes from recipes.txt
void print_all(struct Recipe *element, int num){
    for (int i = 2; i < num; i++){  
        printf("ID: %2d Name: %s\n", i, element[i].name);
    }
}

//Search for recipe with name
void search_recipe(struct Recipe *element, int num){
    char input[25];

    //Ask user for recipe they want to search for
    printf("\nEnter the exact name of the recipe you want to search for: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';  // Remove the newline character

    //Pad the user's input so that it can be compared with the recipe names
    int input_length = strlen(input);
    if (input_length < 24) {
        memset(input + input_length, ' ', 24 - input_length);
    }
    input[24] = '\0'; 

    printf("\n");

    bool found = false;
    int index = 0;

    //Find the recipe by traversing through all of them
    for (int i = 0; i < num; i++) {
        if (strcmp(element[i].name, input) == 0){
            index = i;
            found = true;
            break;
        }
    }

    //If not found, return
    if (!found) {
        printf("Recipe not found\n");
        return;
    }
    //If found, print out with details
    else if(found){
        printf("Matched Recipe: \n");
        printf("\tName: %s\n", element[index].name);
        printf("\tIngredients: %s\n", element[index].ingredients);        
        printf("\tSecret Ingredients: %s\n", element[index].secret_ingredients);
    }
}


//Write a recipe to file
void write_recipe(const char *filename, struct Recipe *element, int num) {
    printf("\nEnter recipe details:\n");
    
    //Ask user for name, ingredients, and secret ingredients of the recipe
    //Add details to structure
    printf("\tName: ");
    fgets(element[num].name, sizeof(element[num].name), stdin);
    element[num].name[strcspn(element[num].name, "\n")] = '\0';

    printf("\tIngredients: ");
    fgets(element[num].ingredients, sizeof(element[num].ingredients), stdin);
    element[num].ingredients[strcspn(element[num].ingredients, "\n")] = '\0'; 

    printf("\tSecret Ingredients: ");
    fgets(element[num].secret_ingredients, sizeof(element[num].secret_ingredients), stdin);
    element[num].secret_ingredients[strcspn(element[num].secret_ingredients, "\n")] = '\0'; 

    //Return if the file cannot be opened
    FILE *fd = fopen(filename, "a");
    if (!fd) {
        printf("Error opening file for writing\n");
        return;
    }

    //Write to end of file
    fprintf(fd, "%-24s %-44s %-9s\n", element[num].name, element[num].ingredients, element[num].secret_ingredients);
    
    fclose(fd);
    printf("The recipe has been added\n");
}

//Search for a secret ingredient in recipe
void search_secret_ingredients(struct Recipe *element, int num){
    char input[10];
    //Ask user for secret ingredient to search for
    printf("Enter the secret ingredient: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';

    //Create a file for recipes with secret ingredient
    char filename[100];
    snprintf(filename, sizeof(filename), "%s.txt", input);

    //Return if the file cannot be opened
    FILE *fd = fopen(filename, "w");
    if (!fd) {
        printf("Error opening file for writing.\n");
        return;
    }

    int count = 0;

    //For all recipes with secret ingredient, write to new file
    for (int i = 0; i < num; i++) {
        char temp_secret_ingredients[100];
        strcpy(temp_secret_ingredients, element[i].secret_ingredients);

        //Search for input within secret ingredients
        char *token = strtok(temp_secret_ingredients, " ");
        while (token != NULL) {
            if (strcmp(token, input) == 0) {
                fprintf(fd, "%24s %44s %9s\n", element[i].name, element[i].ingredients, element[i].secret_ingredients);
                count++;
                break;
            }
            token = strtok(NULL, " ");
        }
    }

    fclose(fd);

    //Print count of matched records
    if (count) {
        printf("Recipes with desired secret ingredient have been stored in the file '%s.txt\n", input);
        printf("Found %d matched records in the file\n", count);
    } 
    else {
        printf("No recipes found with secret ingredient: %s\n", input);
    }
}


//Search for a secret ingredient in recipe
void search_ingredients(struct Recipe *element, int num){
    char input[45];
    //Ask user for ingredient to search for
    printf("Enter the ingredient you want to search for: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';

    //Create a file for recipes with ingredient
    char filename[100];
    snprintf(filename, sizeof(filename), "%s.txt", input);

    //Return if the file cannot be opened
    FILE *fd = fopen(filename, "w");
    if (!fd) {
        printf("Error opening file for writing.\n");
        return;
    }

    int count = 0;

    //For all recipes with ingredient, write to new file
    for (int i = 0; i < num; i++) {
        char temp[100];
        strcpy(temp, element[i].ingredients);

        //Search for input within list of ingredients
        char *token = strtok(temp, " ");
        while (token != NULL) {
            if (strcmp(token, input) == 0) {
                fprintf(fd, "%24s %44s %9s\n", element[i].name, element[i].ingredients, element[i].secret_ingredients);
                count++;
                break;
            }
            token = strtok(NULL, " ");
        }
    }

    fclose(fd);

    //Print count of matched records
    if (count) {
        printf("Recipes with desired secret ingredient have been stored in the file '%s.txt\n", input);
        printf("Found %d matched records in the file\n", count);    
    } 
    else {
        printf("No recipes found with secret ingredient: %s\n", input);
    }
}

//Store recipes in another file
void store_recipes(struct Recipe *element, int num){
    int start, end;

    //Ask user for start of ID
    printf("\nEnter the start ID of the recipe you want to store in a new file: ");
    scanf("%d", &start);
    //Check to see if in range
    if(start < 2 || start > num){
        printf("The index is out of range\n");
        if(start < 2){
            printf("Start ID: 2\n");
            start = 2;
        }
        if(start > num){
            printf("Start ID: %d\n", num);
            start = num;
        }
    }

    //Ask user for end of ID
    printf("Enter the end ID of the recipe you want to store in a new file: ");
    scanf("%d", &end);
    //Check to see if in range
    if(end < 2 || end > num){
        printf("The index is out of range\n");
        if(end < 2){
            printf("End ID: 2\n");
            end = 2;
        }
        if(end > num){
            printf("End ID: %d\n", num);
            end = num;
        }
    }

    //Return if range is out of order
    if(start > end){
        printf("Index out of range - Start ID is greater than End ID\n");
        return;
    }

    //Create a file for the recipes to be stored
    char filename[100];
    snprintf(filename, sizeof(filename), "random.txt");

    //Return if the file cannot be opened
    FILE *fd = fopen("random.txt", "w");
    if (!fd) {
        printf("Error opening file for writing.\n");
        return;
    }

    //Store all recipes in the given range in the new file
    for (int i = start; i < end; i++) {
        fprintf(fd, "%-24s %-44s %-9s\n", element[i].name, element[i].ingredients, element[i].secret_ingredients);
    }

    fclose(fd);

    printf("Found %d matched records in the file", (end - start));

}

int main(){
    struct Recipe element[100];
    int  index = 1;
    char line[300];
    
    //Return if file could not be opened
    FILE *fd;
    char filename[] = "recipes.txt";
    fd = fopen(filename, "r");
    if (!fd) {
        printf("Error: Could not open file\n");
        exit(1);
    }

    //Store all recipe details into a structure, including name, ingredients, and secret ingredients
    while (fgets(line, sizeof(line), fd)) {
        sscanf(line, "%24[^,] %44[^,] %9[^\n]", element[index].name, element[index].ingredients, element[index].secret_ingredients);
        index++;
    }

    fclose(fd);

    //Initialize choice to a false option
    char choice = 'z'; 
    while (true) {
        menu();
        //Ask user input for menu input
        printf("\nEnter your choice (a-g): ");
        scanf(" %c", &choice);
        getchar();

        //Makes sure input is between a to g
        if (choice < 'a' || choice > 'g') {
            printf("Invalid input! Enter your choice (a-g).\n");
            continue; 
        }

        //Calls function based on user input
        switch (choice) {
            case 'a':
                print_all(element, index);
                break;
            case 'b':
                search_recipe(element, index);
                break;
            case 'c':
                write_recipe(filename, element, index);
                index++;
                break;
            case 'd':
                search_secret_ingredients(element, index);
                break;
            case 'e':
                search_ingredients(element, index);
                break;
            case 'f':
                store_recipes(element, index);
                break;
            case 'g':
                printf("Program exited.\n");
                exit(0);
        }
    }

    return 0;
}