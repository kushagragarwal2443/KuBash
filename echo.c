#include "headers.h"

void echo(char *command)
{
    long long int s = strlen(command);

    long long int quotesflag=0;
    long long int afterechoflag=0;
    long long int spaceflag=0;
    int quotestype=0;

    for(long long int a =0; a<s; a++)
    {

        if(afterechoflag==1 && quotesflag==0)
        {
            if((int)command[a]==39)
            {
                quotestype=39;
                quotesflag=1;
                spaceflag=0;
            }

            else if((int)command[a]==34)
            {
                quotestype=34;
                quotesflag=1;
                spaceflag=0;
            }

            else if((int)command[a]!=13 && (int)command[a]!=32 && (int)command[a]!=9)
            {
                printf("%c", command[a]);
                spaceflag=0;
            }

            else if((int)command[a]==13 || (int)command[a]==32 || (int)command[a]==9)
            {
                if(spaceflag == 0)
                {
                    printf(" ");
                    spaceflag=1;
                }
            }

        }

        else if(afterechoflag==1 && quotesflag==1)
        {
            if((int)command[a] == quotestype)
            {
                quotesflag=0;
                spaceflag=0;
            }

            else
            {
                printf("%c", command[a]);
            }
            
        }

        if((int)command[a-4]==101 && (int)command[a-3]==99 && (int)command[a-2] ==104 && (int)command[a-1] == 111)
        {
            afterechoflag=1;
        }
    }

    printf("\n");
}