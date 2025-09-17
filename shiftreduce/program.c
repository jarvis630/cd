#include<stdio.h>
#include<ctype.h>
#include<string.h>
char stack[15],ip_sym[15],temp[15],action[15];
int ip_ptr=0,st_ptr=0,len,l;
char gram[2][10]={"E->E+E","E->E*E"};
char ch,c;
void check();
void main()
{
	printf("\n\tSHIFT REDUCE PARSER\n");
	printf("\n GRAMMAR\n\tE->E+E\n\tE->E*E\n");
	printf("\n E->a\n");
	printf("\n ENTER the input symbol:");
	gets(ip_sym);
	printf("\n\tstack implementation\n");
	printf("stack\t\t\tinput_symbol\t\t\taction\n");
	printf("\n--\t\t\t--\t\t\t--\n");
	printf("\n %s\t\t\t%s\t\t\t\t",stack,ip_sym);
	strcpy(act,"shift");
	printf("%s",act);
	strcpy(temp,"a");
	strcat(stack,temp);
	len=strlen(ip_sym);
	for(l=0;l<len;l++)
	{
		stack[st_ptr]=ip_sym[ip_ptr];
		stack[st_ptr+1]='\0';
		ip_sym[ip_ptr]=' ';
		ip_ptr++;
		printf("\n %s\t\t\t%s\t\t\t%s",stack,ip_sym,act);
		strcpy(act,"shift");
		printf("%s",act);
		strcpy(temp,"a");
		ip_sym[ip_ptr]='\0';
		check();
		st_ptr++;
	}
	check();
}
void check()
{
	int flag=0;
	char temp[5];
	strcpy(temp,stack);
	temp[2]='\0';
	if((!strcmp(temp,"a*"))||(!strcmp(temp,"D")))
	{
		strcpy(stack,"E");
		if(!strcmp(temp,"a"))
			printf("\n %s\t\t\t%s\t\t\tREDUCE E->a",stack,ip_sym);
		else
			printf("\n %s\t\t\t%s\t\t\tREDUCE E->b",stack,ip_sym);
		flag=1;
	}
	if((!strcmp(temp,"E*"))||(!strcmp(temp,"E*E"))||(!strcmp(temp,"E+"))||(!strcmp(temp,"E+E"))||(!strcmp(stack,"E*E"))||(!strcmp(stack,"E/E"))||(!strcmp(stack,"E+E")))
	{
		strcpy(temp,stack);
		strcpy(stack,"E");
	}
	if(!strcmp(temp,"E*E"))
	{
		strcpy(stack,"E");
		st_ptr=0;
		printf("\n %s\t\t\t%s\t\t\tREDUCE E->E*E",stack,ip_sym);
		flag=1;
	}
	else if(!strcmp(temp,"E/E"))
	{
		printf("\n %s\t\t\t%s\t\t\tREDUCE E->E/E",stack,ip_sym);
		strcpy(stack,"E");
		flag=1;
	}
	else if(!strcmp(temp,"E+E"))
	{
		printf("\n %s\t\t\t%s\t\t\tREDUCE E->E+E",stack,ip_sym);
		strcpy(stack,"E");
		flag=1;
	}
	if(flag==0)
	{
		printf("\n %s\t\t\t%s\t\t\tREJECT",stack,ip_sym);
		exit(0);
	}
	if((!strcmp(stack,"E"))&&ip_ptr==len)
	{
		printf("\n %s\t\t\t%s\t\t\tACCEPT",stack,ip_sym);
		exit(0);
	}
	return;
}
