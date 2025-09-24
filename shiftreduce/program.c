#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

char ip_sym[15], stack[15];
int ip_ptr = 0, st_ptr = 0, len;

void check() {
    int flag = 0;
    while(1) {
        flag = 0;
        if (st_ptr > 0 && (stack[st_ptr - 1] == 'a' || stack[st_ptr - 1] == 'b')) {
            char temp = stack[st_ptr - 1];
            stack[st_ptr - 1] = 'E';
            if (temp == 'a') {
                printf("\n $%s\t\t%s\t\tREDUCE E->a", stack, &ip_sym[ip_ptr]);
            } else {
                printf("\n $%s\t\t%s\t\tREDUCE E->b", stack, &ip_sym[ip_ptr]);
            }
            flag = 1;
        }

        if (st_ptr >= 3) {
            char op = stack[st_ptr - 2];
            if ((stack[st_ptr - 3] == 'E' && (op == '+' || op == '*' || op == '/') && stack[st_ptr - 1] == 'E')) {
                stack[st_ptr - 3] = 'E';
                st_ptr -= 2;
                stack[st_ptr] = '\0';

                if (op == '+')
                    printf("\n $%s\t\t%s\t\tREDUCE E->E+E", stack, &ip_sym[ip_ptr]);
                else if (op == '*')
                    printf("\n $%s\t\t%s\t\tREDUCE E->E*E", stack, &ip_sym[ip_ptr]);
                else
                    printf("\n $%s\t\t%s\t\tREDUCE E->E/E", stack, &ip_sym[ip_ptr]);
                flag = 1;
            }
        }

        if (flag == 0) {
            break;
        }
    }
}

int main() {
    printf("\n\t\t SHIFT REDUCE PARSER\n");
    printf("\n GRAMMAR\n");
    printf("\n E->E+E\n E->E/E");
    printf("\n E->E*E\n E->a|b");
    printf("\n enter the input symbol:\t");

    fgets(ip_sym, sizeof(ip_sym), stdin);
    ip_sym[strcspn(ip_sym, "\n")] = '\0';

    len = strlen(ip_sym);
    ip_sym[len] = '$';
    ip_sym[len + 1] = '\0';

    printf("\n\t stack implementation table");
    printf("\n stack\t\t input symbol\t\t action");
    printf("\n \t\t\t\t \n");

    printf("\n $\t\t%s\t\t--", ip_sym);

    while(1) {
        if (st_ptr == 1 && stack[0] == 'E' && ip_ptr == len) {
            printf("\n $%s\t\t$\t\tACCEPT\n", stack);
            break;
        }

        if (ip_ptr < len) {
            stack[st_ptr++] = ip_sym[ip_ptr++];
            stack[st_ptr] = '\0';
            printf("\n $%s\t\t%s\t\tSHIFT %c", stack, &ip_sym[ip_ptr], stack[st_ptr-1]);
        }

        check();
    }

    return 0;
}
