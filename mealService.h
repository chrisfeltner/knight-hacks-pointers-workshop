typedef struct Items {
    char* name;
    double price;
} Item;

typedef struct Restaurants {
    char* name;
    Item** menu;
    int numItems;
} Restaurant;