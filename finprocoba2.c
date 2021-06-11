#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>
#define prc 15000

typedef struct Node{
    char name[25];
    int ID;
    int heavy;
    int price;
    char number[13];
    char address[25];
    struct Node *left,*right;
}n;

void getch();
int print_no = 1; // khusus untuk cetak tabel (showlist, inorder)

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

n *createNode(int id, char nama[], int berat, int harga, char no[], char alamat[])
{
    n*newNode = (n*)malloc(sizeof(n));
    
    newNode->ID = id;
    newNode->heavy = berat;
    newNode->price = harga;
    strcpy(newNode->name, nama);
    strcpy(newNode->number, no);
    strcpy(newNode->address, alamat);
    
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

n *insert(n*root, int id, char nama[], int berat, int harga, char no[], char alamat[], int level)
{
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

void showlist(n *root)
{
	n *temp = root;
	
	if(root == NULL)
		return;

	printf("    |     |           |                              |                  |                              |           |             |\n" );	
	printf("    | %2d. |   L%4d   |   %-25s  |   %-13s  |    %-25s |   %2d Kg   |  Rp %6d  |\n", print_no, temp->ID, temp->name, temp->number, temp->address, temp->heavy, temp->price);

	print_no++;
	
	showlist(root->left);
	showlist(root->right);
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

void inorder(n*root)
{
    if(root == NULL)
        return;

    //traverse the left subtree
    inorder(root->left);

    //visit the root
	printf("    |     |           |                              |                  |                              |           |             |\n" );	
	printf("    | %2d. |   L%4d   |   %-25s  |   %-13s  |    %-25s |   %2d Kg   |  Rp %6d  |\n", print_no, root->ID, root->name, root->number, root->address, root->heavy, root->price);

	print_no++;
	
    //traverse the right subtree
    inorder(root->right);
}

int id_validation(n *root, int *flag)
{
	int l, id;
	char x;
	
    while(1)
    {
    	getchar();
    	printf("\n    >> Input Order ID L[1-9][0-9]: ");
        scanf("%c%d", &x, &id);
        
		if(x!='L' || (id<10 || id>99))
		{
            printf("      --- ID doesn't exist ---\n");
        }
		else
		{
			if (search(root,id) != NULL)
			{
				*flag = 0;
                printf("\n    --- Add New Data Failure. ID is already Exsist ---\n");
            }
        
			break;
		}
	}
	return id;
}

int num_validation(int method)
{
	int temp;
	
	void check()
	{
		while(1)
		{
		    printf("\n       >> Input your choice: ");
            scanf("%d", &temp);
            
            if(temp < 1 || temp > 2)
            	printf("        --- Input not valid ---\n");
            else
				break;
		}
	}
	
	switch(method)
	{
		case 1: // validasi berat
		{
			while(1)
			{
				printf("\n    >> Input Weight [1-15]Kg: ");
                scanf("%d", &temp);
                if( temp < 1 || temp > 15 )
				{
                    printf("      --- Must Between 1 and 15 Kg ---\n");
                }
                else 
                	break;
			}
			break;
		}
		case 2: // validasi harga
		{
			printf("\n    Take Delivery Way :\n");
            printf("      [1] Self Pick Up\n");
            printf("      [2] Delivery\n");
            
			check();
			break;
		}
		case 3: // validation for y/n, cancel/delete
		{
			check();
		}
	}
	return temp;
}

const char* string_validation(int method)
{
	char temp[255];
	int l;
	
	switch(method)
	{
		case 1: //validasi nama
		{
			while(1)
			{
				getchar();
		        printf("\n    >> Input customer name [3-25]: ");
				scanf("%[^\n]", temp);
				l = strlen(temp);
                if( l < 3 || l > 25 )
				{
		            printf("      --- Must Between 3 and 25 characters ---\n");
		        }
				else
					break;
			}
			break;
		}
		case 2: //validasi no telp
		{
			while(1)
			{
				getchar();
                printf("\n    >> Input Number Telephone [10-13]: ");
                scanf("%[^\n]", temp);
                l = strlen(temp);
                if( l < 10 || l > 13 )
				{
                    printf("      --- No Telephone Must Between 11 and 13 Num Characters ---\n");
                }
				else
				{
					int i, no_check = 1;
					for(i=0; i<l; i++)
					{
						if( temp[i] < 48 || temp[i] > 57 ) //ascii angka '0' = 48, '9' = 57
						{
							no_check = 0;
							break;
						}
					}

					if(no_check == 1) //kl stringnya semua terdiri dari angka
						break;
					else
						printf("      --- No Telephone Must include Numbers Only ---\n");
				}
			}
			break;
		}
		case 3: //validasi alamat
		{
			while(1)
			{
				getchar();
				printf("\n    >> Input address [7-25]: ");
                scanf("%[^\n]", temp);
                l = strlen(temp);
                if( l < 7 || l > 25 )
		            printf("      --- Must Between 7 and 25 characters ---\n");
				else
					break;
			}
			break;	
		}
	}
	
	char *s = temp;
	return s;
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
			print_no = 1; //set var global to 1
			printf("\n                                                   --- Laundry List ---\n");
			printf("    +-----+-----------+------------------------------+------------------+------------------------------+-----------+-------------+\n" );	
		 	printf("    | No. |    ID     |        Customer Name         |   Phone Number   |            Address           |   Heavy   |    Harga    |\n");
			printf("    +-----+-----------+------------------------------+------------------+------------------------------+-----------+-------------+\n" );	

			if(root == NULL)
			{
				printf("    |                                                                                                                            |\n" );	
				printf("    |                                                      No Data Available                                                     |\n");
				printf("    |                                                                                                                            |\n" );	

			}
			else
			{
				showlist(root);
				printf("    |     |           |                              |                  |                              |           |             |\n" );	
			}
			printf("    +-----+-----------+------------------------------+------------------+------------------------------+-----------+-------------+\n" );	
		}
		else if(option==2)
		{
			int flag = 1;
			id = id_validation(root, &flag);
			
			int l;
			//klo ID blm pernah diinput
			if(flag) 
			{
				//validasi nama
				strcpy(nama, string_validation(1));

				//validasi berat
				berat = num_validation(1);
				
				//hitung harga
				harga = berat*prc;
				
				//validasi nomor telepon
				strcpy(no, string_validation(2));
				
				//validasi metode pick up
				choice = num_validation(2);
				
				if(choice == 1)
				{
					printf("\n\n    Total price : %d\n", harga);
                   	printf("\n    --- Laundry will be self picked up ---\n");
				   	strcpy(alamat, "   ( Self Pick Up )      ");
                }
				else if(choice == 2)
				{
					//validasi alamat
					strcpy(alamat, string_validation(3));
//							
					printf("\n\n    Total price : %d\n", harga);
					printf("\n    --- Laundry will be delivered to %s ---\n", alamat);
                }
                
                root = insert(root, id, nama, berat, harga, no, alamat, 0);

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
					int pilih, yesno;
//					printf("\n\t<L%2d> %-14s %2d KG   %-13s   %-23s\n",temp->ID,temp->name,temp->heavy, temp->number, temp->address);
					
					printf("\n    Data With ID L%2d Is Found.\n\n", temp->ID);
					printf("      Customer ID    : %d\n", temp->ID);
				    printf("      Customer Name  : %s\n", temp->name);
				    printf("      Contact number : %s\n", temp->number);
				    printf("      Laundry weight : %d\n", temp->heavy);
				    printf("      Address        : ");
				    if(strcmp(temp->address, "   ( Self Pick Up )      ") == 0)
				    	printf("[ Self Pick Up ]\n\n");
				    else
				    	printf("%s\n\n", temp->address);
				    
				    printf("    You want to Cancel or Delete it?\n");
				    printf("      [1] Update\n");
					printf("      [2] Cancel\n");
				    pilih = num_validation(3);
				    
				    switch(pilih)
				    {
				    	case 1:
				    	{
				    		int up_choice;
				    		printf("\n       What do you want to update?\n");
				    		printf("         [1] Berat\n");
							printf("         [2] Nama\n");
							printf("         [3] No\n");
							printf("         [4] Alamat\n");
							printf("         [5] Delivery Way\n");
							printf("         [6] All (except ID)\n\n");
				    		while(1)
							{
							    printf("\n          >> Input your choice: ");
					            scanf("%d", &up_choice);
					            
					            if(up_choice < 1 || up_choice > 6)
					            	printf("           --- Input not valid ---\n");
					            else
									break;
							}
							
							switch(up_choice)
							{
								case 1:
								{
									temp->heavy = num_validation(1);
									temp->price = temp->heavy*prc;
									break;
								}
								case 2:
								{
									strcpy(temp->name, string_validation(1));
									break;
								}	
								case 3:
								{
									strcpy(temp->number, string_validation(2));
									break;
								}
								case 4:
								{
									strcpy(temp->address, string_validation(3));
									break;
								}
								case 5:
								{
									int ch = num_validation(2);
				
									if(ch == 1)
									   	strcpy(temp->address, "   ( Self Pick Up )      ");
									else if(ch == 2)
										strcpy(temp->address, string_validation(3));
									break;
								}
								case 6:
								{
									temp->heavy = num_validation(1);
									strcpy(temp->name, string_validation(1));
									strcpy(temp->number, string_validation(2));
									
									int ch = num_validation(2);
				
									if(ch == 1)
									   	strcpy(temp->address, "   ( Self Pick Up )      ");
									else if(ch == 2)
										strcpy(temp->address, string_validation(3));
									break;
								}	
							}
							
							break;
						}
						case 2:
						{
							printf("    You Want to Cancel It?\n");
							printf("      [1] Yes\n");
							printf("      [2] No\n\n");
							printf("    >> ");
							scanf("%d",&pilih);
							if(pilih==1)
							{
			//					printf("\n\tData With ID L%2d Is Deleted\n",temp->ID);
								printf("\n\tOrder With ID L%2d Is Canceled\n",temp->ID);
								root = delete(root,id);
							}
							
							break;
						}
					}
					
				}
				else{
					printf("\n      --- ID Is Not Found ---\n");
					break;
				}
			}
	    }
	    
		else if (option==4)
		{
			while(1)
			{
				getchar();
				printf("    >> Input Order ID L[1-9][0-9]: "); 
          		scanf("%c%d",&x, &id); 
          		
          		n*temp = search(root,id);
          		
				if(x!='L' || (id<10 || id>99))
			        printf("        --- ID doesn't exist ---\n\n");
		     	else if(temp == NULL)
		   	      	printf("        --- Member ID is not found ---\n");
		    	else if(temp!=NULL)
				{
//              		printf("\n    L%2d - %-14s  %2d Kg %-13s %-23s \n\tHas Been Sucessfully Taken\n", temp->ID, temp->name, temp->heavy, temp->number, temp->address);
              		printf("\n    Order with :");
				    printf("\n      Customer ID    : %d\n", temp->ID);
				    printf("      Customer Name  : %s\n", temp->name);
				    printf("      Contact number : %s\n", temp->number);
				    printf("      Laundry weight : %d\n", temp->heavy);
				    printf("      Address        : ");
				    if(strcmp(temp->address, "   ( Self Pick Up )      ") == 0)
				    	printf("[ Self Pick Up ]\n\n");
				    else
				    	printf("%s\n\n", temp->address);
				    	
				    printf("\nHas Been Sucessfully Taken\n");	
					root = delete(root,id);
				    break;
		    	}
			}
	    }
		else if (option==5)
		{
			print_no = 1; //set var global to 1
	        printf("\n                                                   --- Laundry List ---\n");
			printf("    +-----+-----------+------------------------------+------------------+------------------------------+-----------+-------------+\n" );	
		 	printf("    | No. |    ID     |        Customer Name         |   Phone Number   |            Address           |   Heavy   |    Harga    |\n");
			printf("    +-----+-----------+------------------------------+------------------+------------------------------+-----------+-------------+\n" );	

			if(root == NULL)
			{
				printf("    |                                                                                                                            |\n" );	
				printf("    |                                                      No Data Available                                                     |\n");
				printf("    |                                                                                                                            |\n" );	

			}
			else
			{
				inorder(root);
				printf("    |     |           |                              |                  |                              |           |             |\n" );	
			}
			printf("    +-----+-----------+------------------------------+------------------+------------------------------+-----------+-------------+\n" );	
	    }
	    else if (option==6){
	        
	    }
	    else
	   		printf("\n    Sorry, your input invalid.\n");
	   		
	    printf("\n\n Please Enter To Continue...");
        getch();
        system("CLEAR || CLS");
  }
  
  printf("\n Thank You For Using The Application ^_^\n");
  
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

