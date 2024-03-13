#include "walmart.h"

billItem* createBillItem(int id, const char* name, int quantity, const char* expiryDate, float price){
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


Item* searchItem(aisle a[], int itemId, int reqQuantity){
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
void print_bill_node(billItem *node){
    printf("Item ID : %d\t", node->item_id);
    printf("Item Name : %s\t", node->item_name);
    printf("Expiry Date : %s\t", node->expiryDate);
    printf("Price per quantity: %d\t", node->price);
    printf("Quantity : %d\t", node->quantity);
    printf("Total price : %d\n", (node->price)*(node->quantity));

}


void print_bill(int userId, bill* b){
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

