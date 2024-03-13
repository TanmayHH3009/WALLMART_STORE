#include"walmart.h"


int main()
{
    bill b[5];
for(int i =0 ; i< 5; i++){
    b[i].cost=0;
    b[i].item=NULL;
}
    initialize_map();

    char* date = liveTime();
   printf("%s ",date);
   
   //printf("%d\n",m);
    FILE *fp2 = fopen("_Aisle.txt", "r");
    if (!fp2)
    {
        printf("Failed to open file.\n");
        return 1;
    }
    FILE *fp = fopen("_ItemList.txt", "r");
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
    
   
    printAisle(k);
    
  
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
    
    

    
        FILE *fp4;

    fp4 = fopen("_purchase.txt", "r");
       
    if (fp4 == NULL) {
        printf("Error opening the file.\n");
        return 1;
    }
   
     int id1, q1, id2, q2, id3, q3, id4, q4, id5, q5;
        
        int i=0;
        
        while(fscanf(fp4, "%d %d %d %d %d %d %d %d %d %d", &id1, &q1, &id2, &q2, &id3, &q3, &id4, &q4, &id5, &q5)!=EOF) {
            
            fgetc(fp4);
            
            get_item(id1, q1, k, &b[i]);
            get_item(id2, q2, k, &b[i]);
            get_item(id3, q3, k, &b[i]);
            get_item(id4, q4, k, &b[i]);
            get_item(id5, q5, k, &b[i]);

            i++;
        }

    fclose(fp4);
    
    for(int i=0; i<5; i++){
         print_bill(1234+i,&b[i]);
    }

    for(int i =0 ; i<5 ; i++){
        update_frequency(b[i].item);
    }
   

        
    FILE *fp3 = fopen("_freq.txt", "w");
    if (!fp3)
    {
        printf("Failed to open file.\n");
        return 1;
    }
    print_frequency(fp3,499);

    

    fclose(fp);
    fclose(fp2);
    return 0;
}
