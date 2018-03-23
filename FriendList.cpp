		#include<stdio.h>
		#include<stdlib.h>
		#include<string.h>
		#define FALSE 0
		#define TRUE 1
		
		//INitialization of my Struct FriendList;
		struct FriendList{
			char name[50];
			char surname[50];
			char date[11];
			char gender;
			struct FriendList *next;
		};
		//Function declarations
		void display(struct FriendList *);
		struct FriendList * initialiseFriendBook(char *);
		int findsortedposition(struct FriendList *, char *);
		void InsertFriend(struct FriendList **);
		struct FriendList* SearchFriend(struct FriendList *, char *);
		void BlockFriend(struct FriendList **, struct FriendList **);
		void insertNode(int, struct Frie/Users/rustamquliyev/Downloads/FriendList.cppndList **,struct FriendList *);
		
		
		
		
		int main(){
			int opt;
		printf("Hello to the FriendList application created by Rustam Quliyev!\n");
		char name[100];
		struct FriendList * head=NULL;//Regular Friend's Linked List
		struct FriendList * head_b=NULL;//Blocked Friend's Linked List
		do{
			printf("Please enter the name of your friendlist file\n");
			gets(name);
			head=initialiseFriendBook(name);//Initializing Friend list and assigning it to head
		}while(head==NULL);//Notice my function initialiseFriendBook will return NULL if no file is found or opened
		printf("Your FriendBook has been created\n");
		
		do{
			printf("(1)Insert a new frined\n(2)Print your frineds\n(3)Search for your frined\n(4)Block your friend\n(5)Display blocked freinds\n(6)Exit\n");
			printf("Enter your option");
			scanf("%d",&opt);
			fflush(stdin);
			
			switch(opt){
				case 1: InsertFriend(&head);break;
				case 2: printf("Your friends are listed below\n");display(head);break;
				case 3: printf("Enter the name of your friend\n");gets(name);SearchFriend(head,name);break;
				case 4: BlockFriend(&head,&head_b);break;
				case 5: printf("Your blocked friends are listed below\n");display(head_b);break;
				case 6: break;
				default: printf("Enter correct option number\n");
	
			}
		}while(opt!=6);
		
		
			
			
			
		}
		
		struct FriendList * initialiseFriendBook(char *name){
			FILE *ffile;
			struct FriendList * head=NULL;
			struct FriendList * t;
			ffile=fopen(name,"r");
			if(ffile);
			else return NULL;//If file is not opened Return NULL
			char a;
			while(a!=EOF){
				struct FriendList *tmp=(struct FriendList *)malloc(sizeof(struct FriendList));
				a=getc(ffile);
				
				while(a!='\n'){
					
					int i=0;
					while(a!=';'){
						(tmp->name)[i]=a;	
						a=getc(ffile);
						i++;	
					}
					a=getc(ffile);
					(tmp->name)[i]='\0';
					i=0;
					while(a!=';'){
						(tmp->surname)[i]=a;
						a=getc(ffile);
						
						i++;
					}
					(tmp->surname)[i]='\0';
					a=getc(ffile);
					
					tmp->gender =a;
					a=getc(ffile);
					a=getc(ffile);
					
					i=0;
					while(a!=';'){
						(tmp->date)[i]=a;
						a=getc(ffile);
						i++;
					}
					(tmp->date)[i]='\0';
				
					a=getc(ffile);
					}

				if(a==10 && (a=getc(ffile))!=EOF){
					
					fseek(ffile,-2,SEEK_CUR);
					a=getc(ffile);
					/*This part is very crusial. THe logic behind is the following: Before getting to EOF our char a will be 
					'n'. So I need to make sure that if this line is the last line i need to take one more extra character*/
				}
				if(head==NULL){
					head=tmp;
					tmp->next=NULL;
				}
				else{
					
					int pos=findsortedposition(head,tmp->name);
					insertNode(pos,&head,tmp);
					/*this if else statements are just organizing our LinkedList so if there are no elements yet it will add to the beginning.
					Else I will call my findsortedposition which finds the place where our Node should enter in the Linked List*/
				
				}
			
			
			
				
			}
			
			return head;
			
		
			
		
			
		
		}
		void display(struct FriendList *head){
			struct FriendList *t;
			if(head==NULL)printf("THE LIST IS EMPTY\n");
			else{
				printf("\t Name  Surname  Gender  Date  \n");
				for(t=head;t!=NULL;t=t->next){
					printf("\t %s %s  %c  %s  \n",t->name,t->surname,t->gender,t->date);
				}
			
		}
			printf("\n\n\n\n\n\n");
		}
		int findsortedposition(struct FriendList *head, char *name){
			int pos=1;
			if(head==NULL)return pos;/*If my List is empty if will straightly return 1 as the position since there is no toher option
			We won't need it for our normal Linked List since we have a condition in the while loop itself. But in the bloked Linked List
			I will need this statement
			*/
			int i=0;
			do{
				
				i=0;
				while((name[i]!='\0' || (head->name)[i]!='\0' )&& i!=-1 && i!=-2){
					if(name[i]>(head->name)[i]){
					pos++;
					i=-2;
					}
					if(name[i]<(head->name)[i])i=-3;
					i++;
					//This while loop checks which of 2 string is bigger. If name is larger it will move my position by 1;
				}
			}while(head->next!=NULL && (head=head->next) && i!=-2);
			
			return pos;
		}
		
		void InsertFriend(struct FriendList **head){
			struct FriendList *tmp=(struct FriendList *)malloc(sizeof(struct FriendList));
			printf("Enter the details of your friend\n");
			printf("Enter your frineds name\n");
			scanf("%s", tmp->name);
			printf("Enter your frineds surname\n");
			scanf("%s",tmp->surname);
			printf("Enter your frineds gender\n");
			fflush(stdin);
			scanf("%c",&(tmp->gender));
			fflush(stdin);
			printf("Enter your friends date of birth\n");
			scanf("%s",tmp->date);
			int pos= findsortedposition(*head,tmp->name);//Finds the proper position of the element to be inserted to not disturb the sort
		
			insertNode(pos,head,tmp);
			
			
		}
		
		void BlockFriend(struct FriendList **head,struct FriendList **head_b){
			char name[50];
			int pos;
			struct FriendList *tmp;
			struct FriendList *tmp1=*head;
			printf("Enter the name of your friend to be blocked\n");
			fflush(stdin);
			gets(name);
			fflush(stdin);
			tmp=SearchFriend(*head,name);
			
			if(tmp==NULL){return;
			}
			
			pos=findsortedposition(*head_b,name);
			
		
			while((tmp1)->next!=tmp && tmp1!=tmp){
				
				tmp1=(tmp1)->next;
			}
			
			(tmp1)->next=tmp->next;
			if(tmp1==tmp){
				tmp1=tmp->next;
			}
			insertNode(pos,head_b,tmp);
				
			
			
			
		}
		struct FriendList* SearchFriend(struct FriendList *head, char *name){
		
			int flag=TRUE;
			
			for(head;head!=NULL;head=head->next){
				if(!strcmp((head->name),name)){
					flag=FALSE;
				
					break;				
				}
				
			}
			if(flag==TRUE)printf("\tFriend has not been found\n\n");
			else{
				printf("\t%s %s %c %s\n\n",head->name,head->surname,head->gender,head->date);	
			}
			
			return head;
			
			//IF i assume that strcmp()function has a Big-Oh N then my function FriendList is actually Big-Oh N^2 which is definitely not the best option
			//
		}
		
		void insertNode(int pos, struct FriendList** head,struct FriendList *new_n){
		//I take double pointer as an input because I may need  to change my head pointer if the element is inserted to the first place
			struct FriendList *t=*head;
			if(pos==1){
				(new_n)->next=*head;
				*head=new_n;
				
				
			}
			else{
				
				int i=1;
				for(i=1;i<pos-1;i++){
					t=t->next;
					
				
				}
				if(t->next!=NULL){
					//If the is subsequent element
					new_n->next=t->next;
					t->next=new_n;
					
				}
				else{
					//If t is the last element
					t->next=new_n;
					new_n->next=NULL;
					
				}
			}
			
		};
		
		
		

