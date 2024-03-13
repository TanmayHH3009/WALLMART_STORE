#include"walmart.h"


void ExpiryWithinOneWeek(aisle a[], const char* todayDate) {
    FILE* fp = fopen("_expiryOneWeek.txt", "a");
    if (fp == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    int i = 0;
    while (i < MAX_AISLE && strcmp("ready_to_eat_food", a[i].itemType) != 0) {
        i++;
    }
    i--;

    if (i >= MAX_AISLE) {
        fprintf(fp, "Aisle for 'ready_to_eat_food' not found.\n");
        fclose(fp);
        return;
    }

    if (a[i].list == NULL) {
        fprintf(fp, "No items in 'ready_to_eat_food' aisle.\n");
        fclose(fp);
        return;
    }

    Item* curr = a[i].list;
    while (curr != NULL) {
        int diff = abs(dateToInt(curr->expiryDate) - dateToInt(todayDate));
        if ((diff <= 7 && diff >= 0 )|| (diff>=73 && diff<=79) || (diff>=8870 && diff<=8876)) {
            fprintf(fp, "Item: %s, Expiry Date: %s, Expires within one week\n", curr->itemName, curr->expiryDate);
        } else {
            fprintf(fp, "Item: %s, Expiry Date: %s, Expires not in one week\n", curr->itemName, curr->expiryDate);
        }
        curr = curr->next;
    }

    fclose(fp);
}


//done
void ExpiryWithinOneDay(aisle a[], const char* todayDate) {
    FILE* fp = fopen("_expiryOneDay.txt", "w");
    if (fp == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    int i = 0;
    while (i < MAX_AISLE && strcmp("dairy_products", a[i].itemType) != 0) {
        i++;
    }
    i--;

    if (i >= MAX_AISLE) {
        fprintf(fp, "Aisle for 'dairy_products' not found.\n");
        fclose(fp);
        return;
    }

    if (a[i].list == NULL) {
        fprintf(fp, "No items in 'dairy_products' aisle.\n");
        fclose(fp);
        return;
    }

    Item* curr = a[i].list;
    while (curr != NULL) {
        int diff = abs(dateToInt(curr->expiryDate) - dateToInt(todayDate));
        if ((diff <= 1 && diff >= 0) || (diff == 72) || (diff == 71) || (diff == 70) || (diff == 8870)) {
            fprintf(fp, "Item: %s, Expiry Date: %s, Expires within one day\n", curr->itemName, curr->expiryDate);
        } else {
            fprintf(fp, "Item: %s, Expiry Date: %s, Expires not in one day\n", curr->itemName, curr->expiryDate);
        }
        curr = curr->next;
    }

    fclose(fp);
}
void checkAvailability(aisle a[], int itemId, int quantity, const char* expiryDate) {
    FILE* fp = fopen("_availability.txt", "a");
    if (fp == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    Item* reqItem = search_item(itemId, a);
    if (reqItem == NULL) {
        fprintf(fp, "Item with ID %d is not available in the store.\n", itemId);
        fclose(fp);
        return;
    }

    if (reqItem->quantity < quantity) {
        fprintf(fp, "Item with ID %d does not have enough quantity available.\n", itemId);
        fclose(fp);
        return;
    }

    if (compareDates(expiryDate, reqItem->expiryDate) <= 0) {
        fprintf(fp, "Item with ID %d has expired.\n", itemId);
        fclose(fp);
        return;
    }

    fprintf(fp, "Item with ID %d is available for the required quantity and within the expiry date.\n", itemId);
    fclose(fp);
}

void checkThreshold(aisle a[])  {
    int m=1;
    FILE *fp = fopen("_threshold_notification.txt", "w");
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