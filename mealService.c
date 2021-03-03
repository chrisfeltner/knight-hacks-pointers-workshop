#include "mealService.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void printItem(Item* item) {
    printf("\n%s: %lf", item->name, item->price);
    fflush(stdout);
}

Item* makeItem(char* name, double price)
{
    Item* item = malloc(sizeof(Item));
    item->name = strdup(name);
    item->price = price;
    return item;
}

Item** readInItems(FILE* fp, int numItems) {
    Item** items = calloc(numItems, sizeof(Item*));
    int i = 0;
    char itemName[100];
    double price = 0;
    for(i = 0; i < numItems; i++) {
        fscanf(fp, "%[^\n]s\n", itemName);
        fscanf(fp, "%lf\n", &price);
        items[i] = makeItem(itemName, price);
    }
    return items;
}

void printItems(Item** items, int numItems) {
    int i;
    for(i = 0; i < numItems; i++) {
        printItem(items[i]);
    }
}

Restaurant* makeRestaurant(char* name, Item** items)
{
    Restaurant* restaurant = malloc(sizeof(Restaurant));
    restaurant->name = strdup(name);
    restaurant->menu = items;
    return restaurant;
}

Item* getItemPointer(Item** items, char* name, int numItems)
{
    int i;
    for(int i = 0; i < numItems; i++)
    {
        char* myname = strdup(name);
        myname[strcspn(myname, "\n")] = 0;
        if(strcmp(items[i]->name, myname) == 0)
        {
            return items[i];
        }
    }
    return NULL;
}

Restaurant** readInRestaurants(FILE* fp, int numRestaurants, Item** items, int itemArraySize)
{
    Restaurant** restaurants = calloc(numRestaurants, sizeof(Restaurant*));
    int i;
    int j;
    char* name = malloc(100);
    char* itemName = malloc(100);
    int numItems;
    for(int i = 0; i < numRestaurants; i++)
    {
        restaurants[i] = malloc(sizeof(Restaurant));
        fgets(name, 100, fp);
        restaurants[i]->name = strdup(name);
        fscanf(fp, "%d\n", &numItems);
        Item** menuItems = malloc(numItems * sizeof(Item*));
        for(int j = 0; j < numItems; j++)
        {
            //match the item string with the item pointer
            fgets(name, 100, fp);
            //printf("%s", name);
            menuItems[j] = getItemPointer(items, name, itemArraySize);
        }
        restaurants[i]->menu = menuItems;
        restaurants[i]->numItems = numItems;
    }
    return restaurants;
}

void printRestaurant(Restaurant* restaurant)
{
    printf("\n%s", restaurant->name);
    printItems(restaurant->menu, restaurant->numItems);
    printf("\n");
}

void printRestaurants(Restaurant** restaurants, int numRestaurants)
{
    int i;
    for(i = 0; i < numRestaurants; i++)
    {
        printRestaurant(restaurants[i]);
    }
}

void destroyRestaurant(Restaurant* restaurant)
{
    free(restaurant->name);
    free(restaurant->menu);
    free(restaurant);
}

void destroyRestaurants(Restaurant** restaurants, int numRestaurants)
{
    int i;
    for(int i = 0; i < numRestaurants; i++)
    {
        destroyRestaurant(restaurants[i]);
    }
    free(restaurants);
}

void destroyItem(Item* item)
{
    free(item->name);
    free(item);
}

void destroyItems(Item** items, int numItems)
{
    for(int i = 0; i < numItems; i++)
    {
        destroyItem(items[i]);
    }
    free(items);
}

int main(int argc, char** argv)
{
    int numItems;
    int numRestaurants;
    int i = 0;
    FILE* fp;
    fp = fopen("data.txt", "r");
    fscanf(fp, "%d\n", &numItems);
    // Get number of foods
    // Read in foods
    Item** items = readInItems(fp, numItems);
    // Get number of restaurants
    fscanf(fp, "%d\n", &numRestaurants);
    // Read in restaurants
    Restaurant** restaurants = readInRestaurants(fp, numRestaurants, items, numItems);
    printRestaurants(restaurants, numRestaurants);
    
    destroyRestaurants(restaurants, numRestaurants);
    destroyItems(items, numItems);
}