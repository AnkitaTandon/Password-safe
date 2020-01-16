#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>

int top[5]= {-1,-1,-1,-1,-1};
char a[5][5],master[25];

void decrypt(char encoded[]);
void encrypt(char pwd[]);
void main();

void push(char ch,int j){
    top[j]++;
    a[top[j]][j]=ch;
}

char pop(int j){
    char ch;
        ch=a[top[j]][j];
        top[j]--;
    return ch;
}

int signup(){
    int p=1;
    char uname[20],pfor[20],pwd[25],str1[25],str2[25];
    char pd[5]=".txt";
    FILE *fd;

    printf("\nEnter the username:");
    scanf("%s",uname);
    strcat(uname,pd);

    fd=fopen(uname,"w");

     do{
        printf("Enter the new master key:");
        scanf("%s",str1);
        printf("Re-enter the master key:");
        scanf("%s",str2);
    
        if(strcmp(str1,str2)){
            printf("\nOops! They don't match\n Try again!!\n");
        }
        else{
            encrypt(str1);
            strcpy(master,str1);
            fprintf(fd,"%s",master);
            break;
        }

    }while(strcmp(str1,str2));
    
    while(p==1){
        printf("\nEnter the details-\n");
        printf("Password for:");
        scanf("%s",pfor);
        printf("Password:");
        scanf("%s",pwd);
        encrypt(pwd);      
        fprintf(fd,"\n%s %s",pfor,pwd);

        printf("\nDo you wish to add more passwords??\n 1. yes\n 2. no\nEnter your choice:");
        scanf("%d",&p);
    }

   fclose(fd);
   printf("\nGoing back to the menu page....\n\n");
   main();
   return 0;
}

int login(){ 
    int count=0,choice,p=1;    
    char uname[30],mk[20],key[20],pfor[20],pwd[20],pd[5]=".txt";
    FILE *fp;

    printf("\nEnter username:");
    scanf("%s",uname);
    strcat(uname,pd);

    fp=fopen(uname,"a+");

    if(fp==NULL){
        printf("\nSorry! This user doesn't exist\n\n          Going back to the menu page\n\n");
         main();
    }

    fscanf(fp,"%s",master);
    decrypt(master);
    
    do{
        if(count==3){
            printf("\nToo many attempts!!\nExiting for security\n\n");
            exit(0);
        }

        printf("Enter ur master key:");
        scanf("%s",mk);
        count++;

        if(!strcmp(mk,master)){
            printf("\nPassword Matched!!\n\nEnter-\n1.To append new passwords\n2.To view ur hidden passwords\n\nEnter your choice:");
            scanf("%d",&choice);
            break;
        }
        else{
            printf("\nOops! The key doesn't match\nTry again!!\n");
        }

    }while(strcmp(mk,master));

    if(choice==1){
        while(p==1){
            printf("\nEnter the details-\n");
            printf("Password for:");
            scanf("%s",pfor);
            printf("Password:");
            scanf("%s",pwd);
            encrypt(pwd); 
            fseek(fp,0,SEEK_END);     
            fprintf(fp,"\n%s %s",pfor,pwd);

            printf("\nDo you wish to add more passwords??\n 1. yes\n 2. no\nEnter your choice:");
            scanf("%d",&p);
        }   
    }  //printf("\n")
    
    else{
        printf("\nThe hidden passwords are here:\n");
    
        while(!feof(fp)){
            fscanf(fp,"%s",pfor); 
            fscanf(fp,"%s",pwd); 
            decrypt(pwd);
            printf("%s : %s\n",pfor,pwd);
        }printf("\nGoing back to the menu page....\n");
    }

    fclose(fp);
    main();
    return 0;
}

void encrypt(char pwd[]){
    int i=0,j=0,len,key,col,extr,rc;
    char c,encoded[40];
    len=strlen(pwd);

        if((len%5)!=0)
            extr = 5 - ( len % 5 );
        else
            extr=0;

        while(i<len+extr){
        
            if(i<len)
                c=pwd[i];
            else
                c= 'X';

            push(c,j);                      //here , j is column no. and c is a character
            i++;
            j=(j+1)%5;
        }

        rc=(len+extr)/5;                    //printf("%d\n", i);           // rc is the row count;
        
        for(key=13402,i=0 ; key>0 ; key/=10){
            for(j=0 ; j<rc ; i++,j++){
                col= key % 10;
                encoded[i] = pop(col);        //printf("omg\t%c",encoded[i]);
            }
        }
                                            //printf("%d\n", i);           // rc is the row count;
                                           //printf("%d\n", extr);        // rc is the row count;
        encoded[i]= extr + '0';                                          //printf("\n%c\n",encoded[i]);
        encoded[i+1]='\0';
        strcpy(pwd, encoded);
        
        //printf("\nThe encrypted pwd:%s\n",pwd);

}

void decrypt(char encoded[]){
    int i=0,j=0,len,key,k,col,extr=0,rc;
    char decoded[30], cc;
        
        len=strlen(encoded);        //encoded[len]='\0';
        cc=encoded[len-1];    
        extr=cc-'0';                // printf("\n%d\n", extr);
        rc=(len-1)/5;

        for(i=0,key=13402;key!=0;key/=10){   
            k=0;
            while(k<rc){ 
                col=key%10;             //printf("%c\n", encoded[i]);
                push(encoded[i],col);
                i++;    k++;
            }
        }
    
        len=len-extr-1;

        for(i=0,j=0;i<len;i++){
            decoded[i]=pop(j);
            j=(j+1)%5;
        }
        decoded[i]='\0';
        strcpy(encoded, decoded);


    //printf("The decoded password :%s\n",decoded);

}

void main(){
    int in;
    
    printf("\n*****************************************\n\tPASSWORD SAFE\n*****************************************\n");
    printf("Enter-\n 1. Sign in\n 2. Login\n 3. Exit\n\nEnter your choice:");
    scanf("%d",&in);
    
    if(in==1)
        signup();
    
    else if(in==2)
        login();
    
    else if (in==3)
        exit(0);
    
    else
        printf("\nInvalid Input\n");
}

