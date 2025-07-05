#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>
#include<time.h>
int count=-1;
struct node{
    float amount;
    int blockno;
    char timestamp[20];
    char sender[20];
    char receiver[20];
    char data[250];
    char type[20];
    char hash[65]; 
    struct node* next;
};
struct node* start=NULL;
struct node* creategenesis(struct node*);
struct node* displayblockchain(struct node*);
struct node* deleteblockchain(struct node*);
struct node* validateblockchain(struct node*);
struct node* searchblock(struct node*);
struct node* totalamount(struct node*);
struct node* averageamount(struct node*);
struct node* displaylatestblock(struct node*);
unsigned long simple_hash(char *str) {
    unsigned long hash = 5381;
    int c;
    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; 
    return hash;
}
int main(){
    int choice;
    do{
        printf("\n==========BLOCKCHAIN MENU==========\n");
        printf("1)Genesis Block\n");
        printf("2)Add Block\n");
        printf("3)Display Blockchain\n");
        printf("4)Delete Blockchain\n");
        printf("5)Check Blockchain Validity\n");
        printf("6)Search block by block number\n");
        printf("7)Total Transaction Amount\n");
        printf("8)Average Transaction Amount\n");
        printf("9)Display Genesis Block\n");
        printf("10)Display Latest Block\n");
        printf("11)Exit\n");
        printf("enter your choice:\n");
        scanf("%d",&choice);
        switch(choice){
        case 1:
            if(start!=NULL){
                printf("Genesis Block already exists\n");
            }
            else{
                count++;
                start=creategenesis(start);
            }
            break;
        case 2:
            if(count==-1){
                printf("create genesis block first");
            }
            else{
                count++;
                start=creategenesis(start);
            }
            break;
        case 3:
            if(count==-1){
                printf("Blockchain has not been created");
            }
            else{
                start=displayblockchain(start);
            }
            break;
        case 4:
            if(count==-1){
                printf("Blockchain does not exist");
            }
            else{
                start=deleteblockchain(start);
            }
            break;
        case 5:
            if(count==-1){
                printf("Blockchain does not exist");
            }
            else{
                start=validateblockchain(start);
            }
            break;
        case 6:
            if(count==-1){
                printf("Blockchain does not exist");
            }
            else{
                start=searchblock(start);
            }
            break;
        case 7:
            if(count==-1){
                printf("Blockchain does not exist");
            }
            else if(count==0){
                printf("Total Transaction Amount: 0.0 %s",start->type);
            }
            else{
                start=totalamount(start);
            }
            break;
        case 8:
            if(count==-1){
                printf("Blockchain does not exist");
            }
            else if(count==0){
                printf("Average Transaction Amount: 0.0 %s",start->type);
            }
            else{
                start=averageamount(start);
            }
            break;
        case 9:
            if(count==-1){
                printf("Genesis Block does not exist");
            }
            else{
                printf("\n==========Genesis Block==========\n");
                printf("Block Number: %d",start->blockno);
                printf("\nBlockchain name: %s",start->type);
                printf("\nTimestamp: %s",start->timestamp);
                printf("\nHash: %s", start->hash);
            }
            break;
        case 10:
            if(count==-1){
                printf("Blockchain does not exist");
            }
            else{
                start=displaylatestblock(start);
            }
            break;
        case 11:
            printf("\nExiting...");
            break;
        default:
            printf("enter a valid choice\n");
            break;
        }
    }while(choice!=11);
    return 0;
}
struct node* creategenesis(struct node* start){
    if(count==0){
        struct node* genesisnode;
        genesisnode=(struct node*)malloc(sizeof(struct node));
        start=genesisnode;
        genesisnode->next=NULL;
        genesisnode->blockno=count;
        getchar();
        strftime(start->timestamp, sizeof(start->timestamp), "%d/%m/%Y %I:%M %p", localtime(&(time_t){time(NULL)}));
        printf("enter the Blockchain name: ");
        gets(genesisnode->type);
        printf("Genesis block successfully created!\n");
        sprintf(genesisnode->hash, "%lx", simple_hash(genesisnode->timestamp));
    }
    else{
        struct node* block;
        struct node* ptr;
        block=(struct node*)malloc(sizeof(struct node));
        ptr=start;
        while(ptr->next!=NULL){
            ptr=ptr->next;
        }
        ptr->next=block;
        block->next=NULL;
        block->blockno=count;
        getchar();
        strftime(ptr->timestamp, sizeof(ptr->timestamp), "%d/%m/%Y %I:%M %p", localtime(&(time_t){time(NULL)}));
        strcpy(block->type,start->type);
        printf("enter the amount in %s\n",start->type);
        scanf("%f",&block->amount);
        printf("enter senders name\n");
        getchar();
        gets(block->sender);
        printf("enter receivers name\n");
        gets(block->receiver);
        strcpy(block->data,block->sender);
        strcat(block->data," sent ");
        sprintf(block->data + strlen(block->data), "%.2f", block->amount);
        strcat(block->data,block->type);
        strcat(block->data," to ");
        strcat(block->data,block->receiver);
        printf("%s",block->data);
        sprintf(block->hash, "%lx", simple_hash(block->data));
    }
    return start;
}

struct node* displayblockchain(struct node* start){
    struct node* ptr=start;
    while(ptr!=NULL){
        if(ptr->blockno==0){
            printf("\n==========Genesis Block==========\n");
            printf("Block Number: %d",ptr->blockno);
            printf("\nBlockchain name: %s",ptr->type);
            printf("\nTimestamp: %s",ptr->timestamp);
            printf("\nHash: %s", ptr->hash);
            ptr=ptr->next;
        }
        else{
            printf("\n\n==========Block %d==========\n",ptr->blockno);
            printf("Block Number: %d",ptr->blockno);
            printf("\nBlockchain name: %s",ptr->type);
            printf("\nTimestamp: %s",ptr->timestamp);
            printf("\nAmount: %f %s",ptr->amount,ptr->type);
            printf("\nSenders Name: %s",ptr->sender);
            printf("\nReceivers name: %s",ptr->receiver);
            printf("\nBlockchain Transaction: %s",ptr->data);
            printf("\nHash: %s", ptr->hash);
            printf("\n");
            ptr=ptr->next;
        }
    }
    return start;
}

struct node* deleteblockchain(struct node* start){
    struct node* ptr=start;
    while(ptr->next!=NULL){
        start=start->next;
        free(ptr);
        ptr=start;
    }
    free(ptr);
    start=NULL;
    count=-1;
    printf("\nBlockchain Successfully deleted\n");
    return start;
}

struct node* validateblockchain(struct node* start) {
    struct node* ptr = start;
    while (ptr != NULL) {
        unsigned long recalculated_hash_val;
        if (ptr->blockno == 0) {
            recalculated_hash_val = simple_hash(ptr->timestamp);
        } else {
            recalculated_hash_val = simple_hash(ptr->data);
        }
        char recalculated_hash[65];
        sprintf(recalculated_hash, "%lx", recalculated_hash_val);
        if (strcmp(ptr->hash, recalculated_hash) != 0) {
            printf("Blockchain has been tampered at block number %d\n", ptr->blockno);
            return start;
        }
        ptr = ptr->next;
    }
    printf("Blockchain is valid\n");
    return start;
}


struct node* searchblock(struct node* start){
    int number;
    printf("Enter block number to be searched");
    scanf("%d",&number);
    if(number==0){
        printf("block found:\n");
        printf("\n==========Genesis Block==========\n");
        printf("Block Number: %d",start->blockno);
        printf("\nBlockchain name: %s",start->type);
        printf("\nTimestamp: %s",start->timestamp);
        return start;
    }
    struct node* ptr=start;
    while(ptr!=NULL){
        if(ptr->blockno==number){
            printf("block found:\n");
            printf("\n\n==========Block %d==========\n",ptr->blockno);
            printf("Block Number: %d",ptr->blockno);
            printf("\nBlockchain name: %s",ptr->type);
            printf("\nTimestamp: %s",ptr->timestamp);
            printf("\nAmount: %f %s",ptr->amount,ptr->type);
            printf("\nSenders Name: %s",ptr->sender);
            printf("\nReceivers name: %s",ptr->receiver);
            printf("\nBlockchain Transaction: %s",ptr->data);
            return start;
        }
        else{
            ptr=ptr->next;
        }
    }
    if(ptr==NULL){
        printf("Block of block number %d does not exist",number);
    }
    return start;
}

struct node* totalamount(struct node* start){
    float total=0.0;
    struct node* ptr=start->next;
    while(ptr!=NULL){
        total=total+ptr->amount;
        ptr=ptr->next;
    }
    printf("\nTotal Transaction Amount: %f %s\n",total,start->type);
    return start;
}

struct node* averageamount(struct node* start){
    float average=0.0;
    struct node* ptr=start->next;
    while(ptr!=NULL){
        average=average+ptr->amount;
        ptr=ptr->next;
    }
    average=average/count;
    printf("\nAverage Transaction Amount: %f %s\n",average,start->type);
    return start;
}

struct node* displaylatestblock(struct node* start){
    struct node* ptr=start;
    while(ptr->next!=NULL){
        ptr=ptr->next;
    }
    printf("\n\n==========Block %d==========\n",ptr->blockno);
    printf("Block Number: %d",ptr->blockno);
    printf("\nBlockchain name: %s",ptr->type);
    printf("\nTimestamp: %s",ptr->timestamp);
    printf("\nAmount: %f %s",ptr->amount,ptr->type);
    printf("\nSenders Name: %s",ptr->sender);
    printf("\nReceivers name: %s",ptr->receiver);
    printf("\nBlockchain Transaction: %s",ptr->data);
    return start;
}
