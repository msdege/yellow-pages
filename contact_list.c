#include "contact.h"
#include "contact_list.h"
#include <stdio.h>
#include <string.h>
#include "utils.h"  
#include <stdlib.h> //for free()

static CONTACT_T *list[26];

void init_contact_list (void)
{
    int i; 

    for (i=0;i<26;i++){ 
        list[i] = NULL; //initialize each list in the bucket list to NULL
    }
    
}

void insert_contact (CONTACT_T *contact)
{    
    int index = contact->last_name[0]-'A';
    CONTACT_T *curr;
    CONTACT_T *prev;
    CONTACT_T *temp;
    int i = 0; //determines position in LL
    
    if (list[index] == NULL){  //the list at index is initially empty
        
        list[index] = contact;

    }
    else { //list at index is occupied
        
        curr = list[index]; //set current pointer to beginning of LL
        prev = list[index]; //set prev pointer to beginning of LL

        while (curr !=NULL){
    
            if (strcmp(contact->last_name, curr->last_name) < 0){

                if (i == 0){ //at the front of the LL
                    
                    temp = list[index];
                    list[index] = contact;
                    contact->next = temp;
                    break;
                }
                else{ //not at the front of the LL
                    
                    prev->next = contact;
                    contact->next = curr;
                    break;

                }
            }

            else{ //contact should be inserted after current node

                if (curr->next == NULL){ //at the end of the LL

                    curr->next = contact; 
                    contact->next = NULL;
                    break;
                }
                //no need for else since while loop will move to next node
            }
            i++;
            prev = curr;       //this code keeps the prev pointer one
            curr = curr->next; //behind the current pointer
        }
        
    }
    
}

void print_contact_list (char mode)
{
    int i;
    int null_counter;
    CONTACT_T *curr;

    for (i=0;i<26;i++){
        curr = list[i];
        if (curr == NULL){//current LL is still NULL even after insertion
            null_counter++;
        } 

        while (curr != NULL){
            print_contact(curr, mode);
            curr = (curr->next);
        }
    }
    if (null_counter == 25){
        printf("The entire contact directory (bucket list) is empty\n");
    }
    printf("\n");
}

CONTACT_T *find_contact (NAME_T last_name, NAME_T first_name)
{
    int i;
    int index = last_name[0]-'A';
    CONTACT_T *curr;
    curr = list[index];
    char temp_name[20];

    while (curr != NULL){
        strcpy(temp_name, curr->last_name);
        upper(temp_name);
        if (strcmp(temp_name, last_name) == 0){ //found the contact
            return curr;
        }
        curr = curr->next;
    }
    return NULL;

}

CONTACT_T *get_next_contact (char letter)
{
    static CONTACT_T *curr = NULL;
    int index = letter - 'A';

    if (list[index] == NULL){ //tab letter does not match a LL
        printf("No contacts found\n");
    }
    if (curr == NULL){ //for first contact or when LL is empty
        curr = list[index];
        return curr;
    }
    else{ //in the middle of the LL
        curr = curr->next;
        return curr;
    }
}

void print_state_contacts (char state [], char mode)
{
    int i;
    int counter=0;
    CONTACT_T *curr;

    for (i=0;i<26;i++){ //loop through bucket list

        curr = list[i]; //set curr to first node in LL

        while (curr != NULL){ //loop through LL
            if (strcmp(curr->state, state) == 0){ //found match
                print_contact(curr, mode);
                counter++;
            }
            curr = curr->next; //move to next node
        }
    }
    if (counter == 0){ //no state contacts found
        printf("No contacts found\n");
    }
}

void free_contact_list (void)
{
    int i;
    int c =0;
    CONTACT_T *curr;
    CONTACT_T *prev;

    for (i=0;i<26;i++){

        curr = list[i];  //set curr and prev to 
        prev = list[i];  //beginning of each LL

        while (curr != NULL){
            prev = curr;
            curr = curr->next;
            free(prev);

        }
    }
}       