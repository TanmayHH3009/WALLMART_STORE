#include"walmart.h"



int main()
{
    char* date = liveTime();
   printf("%s ",date);
   
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
    
//     ExpiryWithinOneWeek(k,"03-03-2024");
    printAisle(k);
    
   // printAisle(k);
   printAisleItem(k);

    deleteItem(k,112);
    deleteAisle(k,2);
    
    add_Item(k,490,"burger",29,"23-03-2024",20,45);
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
