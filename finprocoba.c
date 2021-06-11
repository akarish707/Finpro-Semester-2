#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

typedef struct Node{
    char name[25];
    int ID;
    int heavy;
    int price;
    char number[13];
    char adress[25];
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

n *createNode(int id, char nama[], int berat, int harga, char no[], char alamat[]){
    n*newNode = (n*)malloc(sizeof(n));
    
    newNode->ID = id;
    newNode->heavy = berat;
    newNode->price = harga;
    strcpy(newNode->name, nama);
    strcpy(newNode->number, no);
    strcpy(newNode->adress, alamat);
    
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

n *insert(n*root, int id, char nama[], int berat, int harga, char no[], char alamat[], int level){
    if(level<35)
	{
	    if(!root)
	      return createNode(id, nama, berat, harga, no, alamat);
	    while(level<35)
		{
			if(id < root->ID)
				root->left = insert(root->left, id, nama, berat, harga, no, alamat, level+1);
			else
				root->right = insert(root->right, id, nama, berat, harga, no, alamat, level+1);
			break;
		}
  	}
	else
		printf("\n    --- Cannot input data, maximum Tree level is 35 ---\n\n");
  	
  return root;
}

void showlist(n *root, int no)
{
	n *temp = root;
	
	if(root == NULL)
		return;
//											17									225000  |
	printf("    | %2d. |   L%4d   |  %-25s  |    %-13s  | %-25s |   %2d Kg   |  Rp %6d  |\n", no, temp->ID, temp->name, temp->number, temp->adress, temp->heavy, temp->price);
	printf("    +-----+------------+-------------------------+----------------+-------------------------+-----------+-------------+\n" );	
//	  printf("    | No. |  Customer ID  |      Customer Name      |  Phone Number  |          Adress         |   Heavy   |    Harga    |\n");
	showlist(root->left, no+1);
	showlist(root->right, no+1);
}


n* find_minimum(n*root)
{
    if(root == NULL)
        return NULL;
    else if(root->left != NULL) // node with minimum value will have no left child
        return find_minimum(root->left); // left most element will be minimum
    return root;
}

n* delete(n *root, int id)
{
    
    if(root==NULL)
        return NULL;
    if (id>root->ID)
        root->right = delete(root->right, id);
    else if(id<root->ID)
        root->left = delete(root->left, id);
    else
    {
        //No Children
        if(root->left==NULL && root->right==NULL)
        {
            free(root);
            return NULL;
        }

        //One Child
        else if(root->left==NULL || root->right==NULL)
        {
            n *temp;
            if(root->left==NULL)
                temp = root->right;
            else
                temp = root->left;
            free(root);
            return temp;
        }

        //Two Children
        else
        {
            n *temp = find_minimum(root->right);
            strcpy(root->name,temp->name);
            root->ID = temp->ID;
            root->right = delete(root->right, temp->ID);
        }
    }
    return root;
}

int main(){
	
    int option = 0;
    char nama[255], no[255], alamat[255];
    int berat, id, harga, choice;
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
	    printf("   [3] Cancel Laundry\n");
	    printf("   [4] Take Laundry\n");
	    printf("   [5] Sort Laundry List\n");
	    printf("   [6] Exit Program\n");
	    printf("\n >> Input Your Choice: "); scanf("%d", &option);
	    
	    
	    if(option==1)
		{
			printf("\n                                            --- Laundry List ---\n");
			printf("\n    +-----+------------+-------------------------+----------------+-------------------------+-----------+-------------+\n" );
			  printf("    | No. |     ID     |      Customer Name      |  Phone Number  |          Adress         |   Heavy   |    Harga    |\n");
			  printf("    +-----+------------+-------------------------+----------------+-------------------------+-----------+-------------+\n" );
			showlist(root, 1);
			  printf("    +-----+------------+-------------------------+----------------+-------------------------+-----------+-------------+\n" );	
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
				
				//hitung harga
				harga = berat*15000;
				
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
                    
                    if(choice < 1 || choice > 2)
                    	printf("    --- Input not valid ---\n");
                    else
                    {
                    	if(choice == 1)
						{
							printf("\n\n    Total price : %d\n", harga);
	                       	printf("\n    --- Laundry will be self picked up ---\n");
						   	strcpy(alamat, "     ( Self Pick Up )    ");
	                    }
						else if(choice == 2)
						{
							//validasi alamat
							while(1)
							{
								getchar();
								printf("\n    >> Input Adress [7-25]: ");
		                        scanf("%[^\n]", alamat);
		                        l = strlen(alamat);
		                        if( l < 7 || l > 25 )
						            printf("      --- Must Between 7 and 25 characters ---\n");
								else
									break;
							}
							printf("\n\n    Total price : %d\n", harga);
							printf("\n    --- Laundry will be delivered to %s ---\n", alamat);
	                    }
	                    
	                    root = insert(root, id, nama, berat, harga, no, alamat, 0);
							break;
					}
				}
			}
	    }
		else if (option==3)
		{
			while(1){
				getchar();
				printf("\n   >> Input Order ID L[1-9][0-9]: ");
				scanf("%c%d", &x, &id);
				n*temp = search(root,id);
				if(x!='L' || (id<10 || id>99))
	                printf("      --- ID doesn't exist ---\n");
	            else if(temp!=NULL)
				{
					int pilih;
					printf("\n\t<L%2d> %-14s %2d KG   %-13s   %-23s\n",temp->ID,temp->name,temp->heavy, temp->number, temp->adress);
					printf("\n\tData With ID L%2d Is Found You Want to Cancel It?\n",temp->ID);
					printf("\t[1] Yes\n");
					printf("\t[2] No\n");
					printf("\t>> ");
					scanf("%d",&pilih);
					if(pilih==1)
					{
						printf("\n\tData With ID L%2d Is Deleted\n",temp->ID);
						root = delete(root,id);
						break;
					}
					else
						break;
					
				}
				else{
					printf("\n      --- ID Is Not Found ---\n");
					break;
				}
			}
	    }
	    
		else if (option==4)
		{
			while(1){
				getchar();
				printf("\tInput Order ID L[1-9][0-9]: "); 
          		scanf("%c%d",&x, &id); 
          		n*temp = search(root,id);
				if(x!='L' || (id<10 || id>99)){
			        printf("\n\t--- ID doesn't exist ---\n\n");
		     	}else if(temp==NULL){
		   	      	printf("\n\t--- Member ID is not found ---\n");
		    	}else if(temp!=NULL){
              		printf("\tL%2d - %-14s  %2d KG %-13s %-23s \n\tHas Been Sucessfully Taken\n",temp->ID,temp->name,temp->heavy,temp->number,temp->adress);
				    root=delete(root,id);
				    break;
		    	}
			}
	    }
		else if (option==5){
	        
	    }
	    
	    printf("\n\nPlease Enter To Continue...");
        getch();
        system("CLEAR || CLS");
  }
  printf("\nThank You For Using The Application ^_^\n");
}



/*

2
L30
Celine
2
0812222210
1

2
L20
cheryl
2
08122222911
2
Jl. ya disana itu

2
L15
Kunti
2
08122222913
1

2
L10
askadi
2
081225222112
1

2
L26
dime
2
08122222911
2
Jl. depan warunk

2
L60
mega
2
08122222913
1

2
L12
bapak sudirman
2
08122222913
1

2
L44
mbok je
2
081225298712
1

2
L23
kang nggojek
2
08122558911
2
Jl. depan mekdi

2
L98
megah kalik saya
2
08129962913
1
*/

