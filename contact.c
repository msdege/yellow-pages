#include "contact.h"
#include <stdio.h>  //for printf()
#include <stdlib.h> //for malloc()
#include <string.h> //for strcpy()

CONTACT_T *create_contact (CONTACT_T *contact)
{ 
    CONTACT_T *address; //holds address from malloc()
    address = (CONTACT_T*) malloc(sizeof(CONTACT_T));
    //copy everything from contact to address
    strcpy(address->first_name, contact -> first_name);
    strcpy(address->last_name, contact -> last_name);
    strcpy(address-> co_name, contact -> co_name);
    strcpy(address-> addr, contact -> addr);
    strcpy(address-> city, contact -> city);
    strcpy(address-> county, contact -> county);
    strcpy(address-> state, contact -> state);
    strcpy(address-> zip, contact -> zip);
    strcpy(address-> phone1, contact -> phone1);
    strcpy(address-> phone2, contact -> phone2);
    strcpy(address-> email, contact -> email);
    strcpy(address-> web, contact -> web);
    address->next = NULL;
    return address;
}

void print_contact (CONTACT_T *contact, char mode)
{
    switch (mode)
    {
    case 'C':
        printf("%-18s%-18s", contact->last_name, contact->first_name);
        printf("%s   %s\n", contact->phone1, contact->email);
        break;
    
    case 'F':
        printf("Name:    %s %s\n", contact->first_name, 
            contact->last_name);
        printf("Address: %s, %s, %s %s  (%s County)\n", contact->addr, 
            contact->city, contact->state,
            contact->zip, contact->county);
        printf("Phone:   %s (primary)  %s\n", contact->phone1, 
            contact->phone2);
        printf("email:   %s\n", contact->email);
        printf("web:     %s\n\n", contact->web);
        break;
    }
}