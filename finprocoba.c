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

n*insert(n*root, int id, char nama[],int berat,int no, char alamat[], int level){
    if(level<35){
    if(!root){
      printf("\n\t--- Add New Data Sucess ---\n");
      return createNode(id,nama,berat,no,alamat);
    }
    while(level<35){
			if(id < root->ID){
				root->left = insert(root->left,id,nama,berat,no,alamat,level+1);
		}
			else{
				root->right = insert(root->right,id,nama,berat,no,alamat,level+1);
		}
		 break;
	  }
  }else{
		printf("\n    --- Cannot input data, maximum Tree level is 35 ---\n\n");
  }
  return root;
}


void showlist(n*root){
	int no=1;
	n*temp = root;
	if(!root){
		//tabel yg sblm no laundry list sama setelah tulisan no laundry list masih error
		printf("                                  --- Laundry List ---\n");
    	printf("\n+-----+--------------+-------------------+-----------+---------------------+-----------+\n" );
    	printf("| No. |  Customer ID |   Customer Name   |   Heavy   |   Handphone Number  |   Adress  |\n");
    	printf("+-----+--------------+-------------------+-----------+---------------------+-----------+\n" );
    	printf("|                                                               					   |\n");
    	printf("|                            --- No Laundry List Available ---                         |\n");
    	printf("|                                                               					   |\n");
    	printf("+-----+--------------+-------------------+-----------+---------------------+-----------+\n" );
	}else{
		//masih error gabisa nampil
		do{
			printf("| %2d. | L%4d | %-21s | %6d KG | %8D | %-30s |\n",no,temp->ID,temp->name,temp->heavy,temp->number,temp->adress);
			no++;
			showlist(temp->left);
			showlist(temp->right);
		}while(temp!=root && temp!=NULL);

	}
}

int main(){
	
    int option = 0;
    char nama[255], no[255], alamat[255]; //no nya kuubah jd char (bru yg di main yg kuganti :3)
    int berat, id, choice;
    n *hasil;
    n *root = NULL;
    char x;
        
    while (1) 
	{
	    printf("\n Oo=======================oO\n");
	    printf("         Self Laundry\n");
	    printf(" Oo=======================oO\n");
	    printf("   [1] View Laundry List\n");
	    printf("   [2] Add New Laundry List\n");
	    printf("   [3] Search Laundry List\n");
	    printf("   [4] Take Laundry\n");
	    printf("   [5] Sort Laundry List\n");
	    printf("   [6] Exit Program\n");
	    printf("\n >> Input Your Choice: "); scanf("%d", &option);
	    
	    
	    if(option==1)
		{
			showlist(root);
	    }
		else if(option==2)
		{
			//validasi id
			int flag = 1, l;
	        while(1)
	        {
	        	getchar();
	        	printf("\n    >> Input Order ID L[1-9][0-9]: ");
	            scanf("%c%d", &x, &id);
	            
				if(x!='L' || (id<10 || id>99))
				{
	                printf("      --- ID doesn't exist ---\n");
	            }
				else if (search(root,id) != NULL)
				{
					flag = 0;
	                printf("      --- Add New Data Failure. ID is already Exsist ---\n");
	            }
				else
					break;
			}
			
			//klo ID blm pernah diinput
			if(flag) 
			{
				//validasi nama
				while(1)
				{
					getchar();
			        printf("\n    >> Input customer name [3-25]: ");
					scanf("%[^\n]", nama);
					l = strlen(nama);
	                if( l < 3 || l > 25 )
					{
			            printf("      --- Must Between 3 and 25 characters ---\n");
			        }
					else
						break;
				}
				
				//validasi berat
				while(1)
				{
					printf("\n    >> Input Weight [1-15]Kg: ");
                    scanf("%d", &berat);
                    if( berat<1 || berat>15 )
					{
                        printf("      --- Must Between 1 and 15 Kg ---\n");
                    }
                    else 
                    	break;
				}
				
				//validasi nomor telepon
				while(1)
				{
					getchar();
                    printf("\n    >> Input Number Telephone [10-13]: ");
                    scanf("%[^\n]", no);
                    l = strlen(no);
                    if( l < 10 || l > 13 )
					{
                        printf("      --- No Telephone Must Between 11 and 13 Num Characters ---\n");
                    }
					else
					{
						int i, no_check = 1;
						for(i=0; i<l; i++)
						{
							if( no[i] < 48 || no[i] > 57 ) //ascii angka '0' = 48, '9' = 57
							{
								no_check = 0;
								break;
							}
						}
//						printf("\nno cek: %d\n", no_check);
						if(no_check == 1) //kl stringnya semua terdiri dari angka
							break;
						else
							printf("      --- No Telephone Must include Numbers Only ---\n");
					}
				}
				
				//validasi metode pick up
				printf("\n    Take Delivery Way :\n");
                printf("      [1] Self Pick Up\n");
                printf("      [2] Delivery\n");
                
				while(1)
				{
				    printf("\n    >> Input your choice: ");
                    scanf("%d", &choice);
                    
                    if(choice == 1)
					{
                       printf("\n    --- Laundry will be self picked up ---\n");
                       break;
                    }
					else if(choice == 2)
					{
						//validasi alamat
						while(1)
						{
							getchar();
							printf("\n    >> Input Adress [7-100]: ");
	                        scanf("%[^\n]", alamat);
	                        l = strlen(alamat);
	                        if( l < 7 || l > 100 )
							{
					            printf("      --- Must Between 7 and 100 characters ---\n");
					        }
							else
								break;
						}
						printf("\n    --- Laundry will be delivered to %s ---\n", alamat);
						break;
                    }
                    else
                    	printf("    --- Input not valid ---\n");
				}
			}
			
	    }
		else if (option==3)
		{
	    	
	    }
	    
		else if (option==4)
		{
	        
	      
	    }
		else if (option==5){
	        
	    }
	    
	    printf("\n\nPlease Enter To Continue...");
        getch();
        system("CLEAR || CLS");
  }
  printf("\nThank You For Using The Application ^_^\n");
}

