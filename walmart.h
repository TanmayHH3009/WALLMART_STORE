#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<time.h>
# ifndef WALMART_H
# define WALMART_H
#define MAX_AISLE 8
#define MAX_NAME_SIZE 20
# define MAX_NAME_SIZE 20
# define DEFAULT_SIZE 10
# define MAP_SIZE 100
# define INVOICE_SIZE 10

static int billNo=1;
typedef struct Node
{
    int itemId;
    char itemName[30];
    int quantity;
    int threshold_quantity;
    char expiryDate[11];
    int price;
    struct Node *next;
} Item;
//Item k[5];
typedef struct aisle
{
    int aisleNo;
    char itemType[20];
    struct aisle *next;
    Item *list;
} aisle;

typedef struct billItem{
    int item_id;
    char* item_name;
    int quantity;
    char* expiryDate;
    int price;
    struct billItem *next;
}billItem;

typedef struct bill{
    billItem *item;
    int cost;
}bill;



typedef struct item_map{
    billItem *item;
    int count;
}item_map;

item_map map[MAP_SIZE][MAP_SIZE];

void initialize_map();

int hash_function(int item_id);

void update_frequency(billItem *head);

void print_frequency(FILE *fptr, int item_id);


//done
char* liveTime();

//done
billItem* createBillItem(int id, const char* name, int quantity, const char* expiryDate, float price);

//done
Item* searchItem(aisle a[], int itemId, int reqQuantity);
//done
void get_item(int item_id, int req_quantity, aisle a[], bill* b);


//done
void print_bill_node(billItem *node);

//done
void print_bill(int userId, bill* b);

//done
Item* search_item(int id, aisle a[]);

//done
int dateToInt(const char* date);

//done
int compareDates(const char* t1, const char* t2);

//done
void initialize(aisle a[]);

//done
Item *createItem(FILE *fp);

//done
void addItem(aisle a[], FILE *fp);

//done
aisle *createAisle(FILE *fp);

//done
void addAisle(aisle a[], FILE *fp) ;

//done
void deleteItem(aisle a[], int id);

//done
void printAisle(aisle a[]);


//done
void printAisleItem(aisle a[]);

//done
void checkThreshold(aisle a[]) ;

Item* search_item(int id, aisle a[]) ;

void add_Item(aisle a[],int id, const char* name, int quantity, const char* exp, int threshold_quantity, int price) ;

Item* create_item(int id, const char* name, int quantity, const char* exp, int threshold_quantity, int price);


void deleteAisle(aisle a[], int aisleNo);

//done
void ExpiryWithinOneWeek(aisle a[], const char* todayDate) ;

//done
void ExpiryWithinOneDay(aisle a[], const char* todayDate) ;

void checkAvailability(aisle a[], int itemId, int quantity, const char* expiryDate);

void mergeAisles(aisle a[], int a1, int a2);

# endif