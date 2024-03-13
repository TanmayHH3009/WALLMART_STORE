#include"walmart.h"
Item *createItem(FILE *fp){
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

Item* create_item(int id, const char* name, int quantity, const char* exp, int threshold_quantity, int price) {
    Item *new_Item = (Item*)malloc(sizeof(Item));
    if (new_Item == NULL) {
        // Handle memory allocation failure
        return NULL;
    }

    new_Item->itemId = id;
    
    strcpy(new_Item->itemName, name);

    new_Item->quantity = quantity;

   
    strcpy(new_Item->expiryDate, exp);

    new_Item->threshold_quantity = threshold_quantity;
    new_Item->price = price;
    new_Item->next = NULL;

    return new_Item;
}

void addItem(aisle a[], FILE *fp){
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

void add_Item(aisle a[],int id, const char* name, int quantity, const char* exp, int threshold_quantity, int price) {
    Item *newItem = create_item(id,name,quantity,exp,threshold_quantity,price);
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


void deleteItem(aisle a[], int id){
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


void printAisleItem(aisle a[]){
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
