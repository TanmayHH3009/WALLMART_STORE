#include"walmart.h"
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
        if ((diff <= 7 && diff >= 0 )|| (diff>=73 && diff<=79) || (diff>=8870 && diff<=8876)) {
            printf("Item: %s, Expiry Date: %s, Expires within one week\n", curr->itemName, curr->expiryDate);
        } else {
            printf("Item: %s, Expiry Date: %s, Expires not in one week\n", curr->itemName, curr->expiryDate);
        }
        curr = curr->next;
    }
}


//done
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
        if ((diff <= 1 && diff >= 0) || (diff ==72) || (diff==71) || (diff==70) || (diff==8870) ) {
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

void checkThreshold(aisle a[])  {
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

Item* search_item(int id, aisle a[]){
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