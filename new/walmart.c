#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<time.h>
#define MAX_AISLE 8
#define MAX_NAME_SIZE 20

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


char* liveTime() {
    time_t rawtime;
    struct tm *timeinfo;
    char* date_string = (char*)malloc(11 * sizeof(char)); // Allocate memory for the date string

    if (date_string == NULL) {
        printf("Memory allocation failed.\n");
        return NULL;
    }

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(date_string, 11, "%d-%m-%Y", timeinfo); // Format the date

    return date_string;
}


billItem* createBillItem(int id, const char* name, int quantity, const char* expiryDate, float price) {
    billItem* new_Item = (billItem*)malloc(sizeof(billItem));
    if (new_Item == NULL) {
        // Handle memory allocation failure
        return NULL;
    }

    new_Item->item_id = id;
    new_Item->item_name = (char*)malloc(strlen(name) + 1);
    if (new_Item->item_name == NULL) {
        // Handle memory allocation failure
        free(new_Item);
        return NULL;
    }
    strcpy(new_Item->item_name, name);

    new_Item->quantity = quantity;
    new_Item->expiryDate = (char*)malloc(strlen(expiryDate) + 1);
    new_Item->price=price;
    if (new_Item->expiryDate == NULL) {
        // Handle memory allocation failure
        free(new_Item->item_name);
        free(new_Item);
        return NULL;
    }
    strcpy(new_Item->expiryDate, expiryDate);

    new_Item->price = price;
    new_Item->next = NULL;

    return new_Item;
}


Item* searchItem(aisle a[], int itemId, int reqQuantity) {
    Item* ret_val = NULL;
     
    int index = (itemId / 100) - 1;
    Item* curr = a[index].list;
    int i=0;
    while (curr != NULL && curr->itemId != itemId) {
        curr = curr->next;
        
    }
    if (curr != NULL && curr->quantity >= reqQuantity) {
        ret_val = curr;
    }
    return ret_val;
}
void get_item(int item_id, int req_quantity, aisle a[], bill* b) {
    
    Item* retItem = searchItem(a, item_id, req_quantity);
    if (retItem != NULL) {
        
        billItem* new_item = createBillItem(retItem->itemId, retItem->itemName, req_quantity, retItem->expiryDate, retItem->price);
        if (new_item != NULL) {
       
           
            billItem* curr = b->item;
           
            if (curr == NULL) {
                b->item = new_item;
            } else {
                while (curr->next != NULL) {
                    curr = curr->next;
                }
                curr->next = new_item;
            }
            retItem->quantity -= req_quantity;
            b->cost += (retItem->price) * req_quantity;
        } else {
            printf("Failed to create bill item.\n");
        }
    } else {
        printf("Item with ID %d not found or insufficient quantity.\n", item_id);
    }
}

void print_bill_node(billItem *node) {
    printf("Item ID : %d\t", node->item_id);
    printf("Item Name : %s\t", node->item_name);
    printf("Expiry Date : %s\t", node->expiryDate);
    printf("Price per quantity: %d\t", node->price);
    printf("Quantity : %d\t", node->quantity);
    printf("Total price : %d\n", (node->price)*(node->quantity));

}

void print_bill(int userId, bill* b) {
    FILE *fp = fopen("bill.txt", "a"); // Open the file in append mode
    if (fp == NULL) {
        printf("Failed to open file for writing.\n");
        return;
    }


    fprintf(fp, "\n\n                 ***********************************************\n");
    fprintf(fp, "                                WALLMART - BILL\n");
    fprintf(fp, "                 ***********************************************\n\n");
     char* date = liveTime();
     fprintf(fp, "DATE: %s\n", date);
    fprintf(fp, "BILL No. : %d\n", billNo++);
    fprintf(fp, "USER ID : %d\n\n", userId);
    fprintf(fp, "Items bought : \n");

     fprintf(fp, "---------------------------------------------------------------------------------\n");
    fprintf(fp, "| %-10s | %-20s | %-12s | %-6s | %-8s |\n", "Item ID", "Item Name", "Expiry Date", "Price", "Quantity");
     fprintf(fp, "---------------------------------------------------------------------------------\n");
    billItem *curr = b->item;
    while(curr != NULL) {
        fprintf(fp, "| %-10d | %-20s | %-12s | %-6d | %-8d |\n", curr->item_id, curr->item_name, curr->expiryDate, curr->price, curr->quantity);
        curr = curr->next;
    }

    fprintf(fp, "---------------------------------------------------------------------------------\n");
    fprintf(fp, "\nTotal cost : %d\n\n", b->cost);
     fprintf(fp, "---------------------------------------------------------------------------------\n");
      fprintf(fp, "---------------------------------------------------------------------------------\n");

    fclose(fp);
}




Item* search_item(int id, aisle a[]) {
    int index = id / 100 - 1;
    Item* curr = a[index].list;
    while (curr != NULL && curr->itemId != id) {
        curr = curr->next;
    }

    if (curr == NULL) {
        printf("Item not found\n");
    }

    return curr;
}

int dateToInt(const char* date) {
    char temp[11];
    strcpy(temp, date);
    temp[2] = temp[5] = '\0'; // Null terminate after day and month
    return atoi(&temp[6]) * 10000 + atoi(&temp[3]) * 100 + atoi(&temp[0]);
}


int compareDates(const char* t1, const char* t2) {
    int date1 = dateToInt(t1);
    int date2 = dateToInt(t2);

    if (date1 < date2) {
        return -1;
    } else if (date1 > date2) {
        return 1;
    } else {
        return 0;
    }
}

void initialize(aisle a[])
{

    for (int i = 0; i < 5; i++)
    {
        a[i].list = NULL;
    }
}

Item *createItem(FILE *fp)
{
    Item *newItem = malloc(sizeof(Item));
    if (!newItem)
    {
        printf("Memory allocation failed.\n");
        return NULL;
    }

    if (fscanf(fp, "%d %30s %d %d %10s %d", &newItem->itemId, &newItem->itemName, &newItem->quantity, &newItem->threshold_quantity, &newItem->expiryDate, &newItem->price) == 6)
    {
        return newItem;
    }
    else
    {
        free(newItem);
        return NULL;
    }
}

void addItem(aisle a[], FILE *fp)
{
    Item *newItem = createItem(fp);
    if (newItem == NULL)
    {
        printf("Not a valid item, please enter valid information\n");
    }
    else
    {
        int index = newItem->itemId / 100;
        index = index - 1;

        Item *curr = a[index].list;
        if (curr == NULL)
        {
            a[index].list = newItem; // Update the list pointer
        }
        else
        {
            while (curr->next != NULL)
            {
                curr = curr->next;
            }
            curr->next = newItem;
        }
    }
}

aisle *createAisle(FILE *fp){
    aisle *newAisle = malloc(sizeof(aisle));
    if(!newAisle){
         printf("Memory allocation failed.\n");
        return NULL;
    }
      if (fscanf(fp, "%d %s", &newAisle->aisleNo , &newAisle->itemType) == 2)
    {
        newAisle->list=NULL;
      
        return newAisle;
    }
    else
    {
        free(newAisle);
        return NULL;
    }

}
void addAisle(aisle a[], FILE *fp) {
    aisle *newAisle = createAisle(fp);
    
    if (!newAisle) {
        printf("Failed to create aisle.\n");
        return;
    }

    int index = newAisle->aisleNo;
    if (index < 0 || index >= 8) {
        printf("Invalid aisle number.\n");
        free(newAisle);
        return;
    }

    a[index]=*newAisle;
}

void deleteItem(aisle a[], int id)
{
    int index = id / 100 - 1;
    int listCount = id % 100;
    Item *curr = a[index].list;
    Item *prev = NULL;

    // Check if the item to be deleted is the first item in the list
    if (listCount == curr->itemId % 100)
    {
        a[index].list = curr->next;
        free(curr);
        return;
    }

    while (curr != NULL && listCount != curr->itemId % 100)
    {
        prev = curr;
        curr = curr->next;
    }

    if (curr == NULL)
    {
        printf("Item not found.\n");
        return;
    }

    prev->next = curr->next;
    free(curr);
}




void printAisle(aisle a[]){
    int i = 1;
    while(a[i].aisleNo>0 && a[i].aisleNo<=8){
        
        printf("%d %s\n",a[i].aisleNo,a[i].itemType);
       i++;
    }

}

void printAisleItem(aisle a[])
{
    FILE *fp = fopen("walmartStore.txt", "a");
    if (!fp)
    {
        printf("Failed to open file for writing.\n");
        return;
    }

    for (int i = 0; i < 5; i++)
    {
        fprintf(fp, "Aisle %d:\n", i + 1); // Convert from 0-based to 1-based aisle numbering
        Item* curr = a[i].list;  // Use a temporary pointer to iterate over the list
        while (curr != NULL)
        {
            fprintf(fp, "ID: %d\nName: %s\nQuantity: %d\nPrice: %d\nthreshold Quantity: %d\nDate: %s\n", curr->itemId, curr->itemName, curr->quantity, curr->price, curr->threshold_quantity, curr->expiryDate);
            curr = curr->next;
            fprintf(fp, "--------------------------\n");
        }

        fprintf(fp, "\n");

        fprintf(fp, "--------------------------\n");
    }

    fclose(fp);
}

void checkThreshold(aisle a[]) {
    int m=1;
    FILE *fp = fopen("threshold_notification.txt", "w");
    if (!fp) {
       
        printf("Failed to open file for writing.\n");
        return;
    }
    fprintf(fp,"FOLLOWING ITEMS SHOULD BE ORDERED SOON\n");

    for (int i = 0; i < 5; i++) {
     
        Item *curr = a[i].list;
        while (curr != NULL) {
           if(curr->quantity<curr->threshold_quantity) 
             {
                fprintf(fp, "%d. %s (ID: %d) Current Quantity: %d, Threshold Quantity: %d\n",m,
                       curr->itemName, curr->itemId,  curr->quantity, curr->threshold_quantity);
                       m++;
            }
            curr = curr->next;
        }
    }
   
    fclose(fp);
}

void ExpiryWithinOneWeek(aisle a[], const char* todayDate) {
    int i = 0;
   
    while (i < MAX_AISLE && strcmp("ready_to_eat_food", a[i].itemType) != 0) {
        i++;

    }
    i--;
    

    if (i >= MAX_AISLE) {
        
        printf("Aisle for 'ready_to_eat_food' not found.\n");
        return;
    }

    if (a[i].list == NULL) {
        
        printf("No items in 'ready_to_eat_food' aisle.\n");
        return;
    }

    Item* curr = a[i].list;
    while (curr != NULL) {
         
        int diff = abs(dateToInt(curr->expiryDate) - dateToInt(todayDate));
        if (diff <= 7 && diff >= 0 || (diff>=73 && diff<=79) || (diff>=8870 && diff<=8876)) {
            printf("Item: %s, Expiry Date: %s, Expires within one week\n", curr->itemName, curr->expiryDate);
        } else {
            printf("Item: %s, Expiry Date: %s, Expires not in one week\n", curr->itemName, curr->expiryDate);
        }
        curr = curr->next;
    }
}

void ExpiryWithinOneDay(aisle a[], const char* todayDate) {
    int i = 0;
   
    while (i < MAX_AISLE && strcmp("dairy_products", a[i].itemType) != 0) {
        i++;

    }
    i--;
    
    

    if (i >= MAX_AISLE) {
        
        printf("Aisle for 'dairy_products' not found.\n");
        return;
    }

    if (a[i].list == NULL) {
        
        printf("No items in 'dairy_products' aisle.\n");
        return;
    }

    Item* curr = a[i].list;
    while (curr != NULL) {
         
        int diff = abs(dateToInt(curr->expiryDate) - dateToInt(todayDate));
        //printf("%d and %d \n",dateToInt(curr->expiryDate), dateToInt(todayDate));
        if (diff <= 1 && diff >= 0 || (diff ==72) || (diff==71) || (diff==70) || (diff==8870) ) {
            printf("Item: %s, Expiry Date: %s, Expires within one day\n", curr->itemName, curr->expiryDate);
        } else {
            printf("Item: %s, Expiry Date: %s, Expires not in one day\n", curr->itemName, curr->expiryDate);
        }
        curr = curr->next;
    }
}



void checkAvailability(aisle a[], int itemId, int quantity, const char* expiryDate) {
    Item* reqItem = search_item(itemId, a);
    if (reqItem == NULL) {
        printf("Item with ID %d is not available in the store.\n", itemId);
        return;
    }

    if (reqItem->quantity < quantity) {
        printf("Item with ID %d does not have enough quantity available.\n", itemId);
        return;
    }

    if (compareDates(expiryDate, reqItem->expiryDate) <= 0) {
        printf("Item with ID %d has expired.\n", itemId);
        return;
    }

    printf("Item with ID %d is available for the required quantity and within the expiry date.\n", itemId);
}

void mergeAisles(aisle a[], int a1, int a2) {
    a1--;a2--;
    
    if (a[a1].list == NULL) {
        a[a1].list = a[a2].list;
         
    } else {
        Item* temp = a[a1].list;
       
        int i = 0 ;
        while (temp->next != NULL) {
            temp = temp->next;
           
        }
        temp->next = a[a2].list;
    }
  
    a[a2].list = NULL;



}





int main()
{
    char* date = liveTime();
   printf("%s ",date);
   int m = compareDates("20-11-2004","20-11-2024");
   //printf("%d\n",m);
    FILE *fp2 = fopen("Aisle.txt", "r");
    if (!fp2)
    {
        printf("Failed to open file.\n");
        return 1;
    }
    FILE *fp = fopen("ItemList.txt", "r");
    if (!fp)
    {
        printf("Failed to open file.\n");
        return 1;
    }

    aisle k[8];
    initialize(k);
    while(!feof (fp2)){
        addAisle(k,fp2);
    }
    while (!feof(fp))
    {
        addItem(k, fp);
    }
    int i= 0;
//     ExpiryWithinOneWeek(k,"03-03-2024");
    printAisle(k);
    
   // printAisle(k);

    deleteItem(k,112);
    
    
    checkAvailability(k,112,5,date);
    printf("hello\n");
    checkThreshold(k);
    ExpiryWithinOneWeek(k,date);
    printf("\n");
    ExpiryWithinOneDay(k,date);
    //mergeAisles(k,1,4);
    printAisleItem(k);
    bill b;
    b.cost=0;
    
    printf("hello\n");
    get_item(101,3,k,&b);
    //print_bill(1234,&b);
    get_item(444,3,k,&b);
    get_item(499,3,k,&b);

    get_item(202,3,k,&b);
    print_bill(1234,&b);

    

    fclose(fp);
    fclose(fp2);
    return 0;
}
