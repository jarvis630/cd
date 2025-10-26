#include<stdio.h>
#include<string.h>
#include<ctype.h>

int n;
char prod[10][50];

void input(){
    printf("Enter the no of productions\t");
    scanf("%d",&n);
    printf("Enter the productions\n");
    for(int i = 0;i<n;i++){
        scanf("%s",prod[i]);
    }
}

void replace(char c,char *num,int no){
    char temp[50];
    for(int i = no+1;i<n;i++){
        for(int j = 2; prod[i][j] != '\0'; j++){
            if(prod[i][j] == c){
                strcpy(temp, prod[i] + j + 1);
                prod[i][j] = '\0';
                strcat(prod[i], num);
                strcat(prod[i], temp);
                return;
            }
        }
    }
}

void check(){
    char num[20];
    for(int i = 0;i<n;i++){
        if(isdigit(prod[i][2])){
            int j = 2, count = 0;
            while(isdigit(prod[i][j])){
                num[count++] = prod[i][j];
                j++;
            }
            num[count] = '\0';
            replace(prod[i][0], num, i);
        }
    }
}

void display(){
    printf("Optimized code is:\n");
    for(int i = 0;i<n;i++){
        printf("%s\n",prod[i]);
    }
}

void main(){
    input();
    check();
    display();
}
