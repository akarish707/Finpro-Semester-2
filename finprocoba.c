#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

typedef struct Node{
    char name[255];
    int ID;
    int heavy;
    int number;
    char adress[255];
    struct Node *left,*right;
}n;

void getch();
n* search(n*root, int id)
{
    if(root==NULL || root->ID==id){
        return root;
    }else if(id>root->ID){ 
        return search(root->right, id);
    }else{ 
        return search(root->left,id);
    }
}

n*createNode(int id,char nama[],int berat,int no, char alamat[]){
    n*newNode = (n*)malloc(sizeof(n));
    newNode->ID = id;
    strcpy(newNode->name,nama);
    newNode->heavy = berat;
    newNode->number = berat;
    strcpy(newNode->adress,alamat);
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

n*insert(n*root, int id, char nama[],int berat,int no, char alamat[]){
    
}

int main(){
    int option = 0;
    char nama[255],alamat[255];
    int berat,id,no,choice;
    n*hasil;
    n*root=NULL;
    char x;
        
    while (option < 5 ) {
    printf("Oo=======================oO\n");
    printf("\tSelf Laundry\n");
    printf("Oo=======================oO\n");
    printf("[1] View Laundry List\n");
    printf("[2] Add New Laundry List\n");
    printf("[3] Search Laundry List\n");
    printf("[4] Take Laundry\n");
    printf("[5] Sort Laundry List\n");
    printf("[6] Exit Program\n");
    printf("Input Your Choice >> "); scanf("%d", &option);
    if(option==1){
        printf("\nPlease Enter To Continue...");
        getch();
        system("CLEAR || CLS");
    }else if(option==2){
        while(1){
            getchar();
            printf("\n\t>> Input Order ID L[1-9][0-9]: ");
            scanf("%c%d",&x,&id);
            if(x!='L' || (id<10 || id>99)){
                printf("\n\t--- ID doesn't exist ---\n");
            }else if (search(root,id)!=NULL){
                printf("\n\t--- Add New Data Failure--\n");
		        printf("\tId is already Exist\n");
		        break;
            }else{
                while(1){
                    printf("\t>> Input customer name [3-25]: ");
			        scanf(" %[^\n]",nama);
                    if(strlen(nama)<3 ||strlen(nama)>25){
			            printf("\n\t--- Must Between 3 and 25 characters ---");
			        }else{
                    while(1){
                        printf("\t>> Input Weight [1-15]Kg: ");
                        scanf("%d",&berat);
                        if(berat<1 || berat>15){
                            printf("\n\t--- Must Between 1 and 15 Kg ---");
                        }else{
                            while(1){
                                printf("\t>> Input Number Telephone [11-13]: ");
                                scanf("%d",&no);
                                if(no<11 && no>13){
                                    printf("\n\t--- No Telephone Must Between 11 and 13 ---");
                                }else{
                                while(1){
                                printf("\n\tChoose Take Delivery Way :\n");
                                printf("\t[1] Self Pick Up\n");
                                printf("\t[2] Delivery\n");
                                printf("\t>> ");
                                scanf("%d",&choice);
                                if(choice==1){
                                   //error gamau balik ke program awal ehe :v
                                   break;
                                }else{
                                   printf("\t>> Input Adress [7-100]: ");
                                   scanf(" %[^\n]",alamat);
                                }
                               }
                              }
                            }
                        }
                    }
                  }
                }
            }
        }
        printf("\nPlease Enter To Continue...");
        getch();
        system("CLEAR || CLS");
    }else if(option==3){
        printf("\nPlease Enter To Continue...");
        getch();
        system("CLEAR || CLS");
    }else if(option==4){
        
        printf("\n\nPlease Enter To Continue...");
        getch();
        system("CLEAR || CLS");
    }else if(option==5){
        printf("\n\nPlease Enter To Continue...");
        getch();
        system("CLEAR || CLS");
    }
  }
  printf("\nThank You For Using The Application ^_^\n");
}
