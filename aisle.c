#include"walmart.h"
void initialize(aisle a[]){

    for (int i = 0; i < 5; i++)
    {
        a[i].list = NULL;
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


void addAisle(aisle a[], FILE *fp){
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

void printAisle(aisle a[]){
    int i = 1;
    while(a[i].aisleNo>0 && a[i].aisleNo<=8){
        
        printf("%d %s\n",a[i].aisleNo,a[i].itemType);
       i++;
    }

}

void mergeAisles(aisle a[], int a1, int a2){
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

void deleteAisle(aisle a[], int aisleNo) {
    if (aisleNo < 1 || aisleNo > MAX_AISLE) {
        printf("Invalid aisle number.\n");
        return;
    }

    // Free the memory of the items in the aisle's list
    Item* curr = a[aisleNo - 1].list;
    Item* next;
    while (curr != NULL) {
        next = curr->next;
        free(curr);
        curr = next;
    }

    // Set the aisle's list to NULL
    a[aisleNo - 1].list = NULL;
}
