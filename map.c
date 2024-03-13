# include"walmart.h"
#define MAX_AISLE 8
#define MAX_NAME_SIZE 20
# define MAX_NAME_SIZE 20
# define DEFAULT_SIZE 10
# define MAP_SIZE 100
# define INVOICE_SIZE 10
void initialize_map() {
    for(int i=0; i<MAP_SIZE; i++) {
        for(int j=0; j<MAP_SIZE; j++) {
            map[i][j].item=NULL;
            map[i][j].count=0;
        }
    }
}

int hash_function(int item_id) {
    int ans=0;
    for(int i=5; i>=1; i--) {
        ans=ans+(i)*((item_id)%10);
        item_id=(item_id)/10;
    }
    return ans;
}

void update_frequency(billItem *head) {
    //initialize_map();
    billItem *curr=head;
    while(curr!=NULL) {
        billItem *node=head;
        int row=hash_function(curr->item_id);
        //printf("%d-----%d\n", curr->item_id, row);
        map[row][0].item=curr;
        while(node!=NULL) {
            if(node->item_id!=curr->item_id) {
                int col=hash_function(node->item_id);
                map[row][col].item=node;
                (map[row][col].count)++;
            }
            node=node->next;
        }
        curr=curr->next;
    }
}

void print_frequency(FILE *fptr, int item_id) {
    int index=hash_function(item_id);
    fprintf(fptr, "Printing for item %s -: \n", map[index][0].item->item_name);
    int maxi=INT32_MIN;
    int upper_limit=INT32_MAX;
    int flag=1;
    while(flag) {
        for(int j=1; j<MAP_SIZE ; j++) {
            if(map[index][j].count>maxi && map[index][j].count<=upper_limit) maxi=map[index][j].count;
        }
        if(maxi==INT32_MIN || maxi==0 || upper_limit==0) {
            flag=0;
        }
        else {
            for(int j=0; j<MAP_SIZE; j++) {
                if(map[index][j].count==maxi) {
                    fprintf(fptr, "Item name : %s\tItem id : %d\tFrequency : %d\n", map[index][j].item->item_name, map[index][j].item->item_id, map[index][j].count);
                }
            }
            upper_limit=maxi-1;
            maxi=INT32_MIN;
        }
    }
    fprintf(fptr, "\n\n");
}