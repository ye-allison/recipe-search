#ifndef q2_H
#define q2_H

//Creating struct for the function
struct Recipe{
    char name[25];
    char ingredients[45];
    char secret_ingredients[10];
    char buffer;
};

//Function headers
void menu();
void print_all(struct Recipe *element, int num);
void search_recipe(struct Recipe *element, int num);
void write_recipe(const char *filename, struct Recipe *element, int num);
void search_secret_ingredients(struct Recipe *element, int num);
void search_ingredients(struct Recipe *element, int num);
void store_recipes(struct Recipe *element, int num);

#endif