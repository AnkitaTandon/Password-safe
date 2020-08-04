#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include <sys/stat.h>
int main(){
   
    char a[10];
    scanf("%s",a);
    strcat(a,".txt");
    struct stat buffer;
    int exist = stat(a,&buffer);
    if(exist)
        printf("1");
    else // -1
       printf("0") ;
}