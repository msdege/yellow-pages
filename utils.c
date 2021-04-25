#include "utils.h"
#include <string.h>
#include <stdio.h> //temp

void upper (char str[])
{
    int i;
    int offset = 'a' - 'A';

    for (i=0;i<strlen(str);i++){       
        if (str[i] >= 'a' && str[i] <= 'z' ){ //lowercase
            str[i] = str[i] - offset;
        }  
    }     
}
