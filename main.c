//Michael DeGennaro--4/14/21--due Sat. April 24th--CSCI 304-02
//Description: This project reads from a contact list with various info
//             and inputs it all alphabetically into a bucket list of linked lists.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h" 
#include "contact_list.h"
#include "utils.h"

//function prototypes
void process_file (char *filename);
char print_menu (void);
char print_format_menu (void);
void find_individual (char mode);
void print_tab (char mode);
void process_state_contacts (char mode);

void main (int argc, char *argv [])
{
    FILE *fp;  //file pointer
    char str[200];  //holds contact info
    char menu_selection;  //holds menu option
    char mode='C'; //initial mode is condensed

    if (argc < 2){     //check if contact file is specified cmd line
        exit(EXIT_FAILURE);
    }

    init_contact_list();
    process_file(argv[1]);
    print_contact_list(mode);

    do{
        menu_selection = print_menu();
        switch (menu_selection){
            //print tab
            case 'T': 
                print_tab(mode);
                break;
            //change output format
            case 'C': 
                mode = print_format_menu();
                break;
            //search for individual
            case 'I':
                find_individual(mode);
                break;
            //look up by state
            case 'S':
                process_state_contacts(mode);
                break;
        }
    }while (menu_selection != 'Q');

    free_contact_list(); //free all the memory
    
}

void process_file (char *filename)
{
    FILE *fp;  //file pointer
    CONTACT_T contact; //temporary contact to hold info 
    CONTACT_T *address; //stores address from create_contact()

    fp = fopen(filename, "r"); //open addr.csv in read mode
    fscanf(fp, "%*s "); //consume the first line in fp
    
    while (fscanf(fp, "%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%s ", 
        contact.first_name, contact.last_name, contact.co_name, 
        contact.addr, contact.city, contact.county, contact.state, 
        contact.zip, contact.phone1,contact.phone2, contact.email, 
        contact.web) == 12){

        address = create_contact(&contact);
        insert_contact(address);
    }
    fclose(fp);
}

char print_menu (void)
{
    char user_input[20]; //holds user input
    char menu_selection; //holds first character in user input
    char valid_options[] = "CITSQ";
    char temp[20];

    do{
        printf("\nPlease select one of the following: \n\n");
        printf(" c  Change output format\n");
        printf(" i  Search for individual\n");
        printf(" t  Print tab\n");
        printf(" s  Look up by state\n");
        printf(" q  Quit\n\n");
        printf("Option: ");

        scanf("%s", user_input);
        printf("%s\n", user_input); //echo print

        strcpy(temp, user_input); //copy user_input to temp
        upper(user_input); 
        menu_selection = user_input[0];
        
        if (strlen(user_input)>1 || !strchr(valid_options, menu_selection)){
            printf("\nInvalid option entered\n");
        }
    }while (strlen(user_input)>1 || !strchr(valid_options, menu_selection));

    return menu_selection;
}

char print_format_menu (void)
{
    char user_input[20]; //holds user input
    char mode;

    printf("\nPlease select one of the following: \n\n");
    printf(" c  Condensed output information\n");
    printf(" f  Full output information\n\n");
    printf("Option: ");

    scanf("%s", user_input);
    printf("%s\n", user_input); //echo print

    upper(user_input);
    mode = user_input[0];

    return mode;
}

void find_individual (char mode)
{
    char user_firstname[20];
    char user_lastname[20];
    CONTACT_T *return_ptr;

    printf("\nPlease enter last name: ");
    scanf("%s", user_lastname);
    printf("%s\n", user_lastname); //echo print
    printf("Please enter first name: ");
    scanf("%s", user_firstname);
    printf("%s\n", user_firstname); //echo print
    printf("\n");

    upper(user_firstname);
    upper(user_lastname);

    return_ptr = find_contact(user_lastname, user_firstname);
    if (return_ptr == NULL){
        printf("Contact not found\n");
    }
    else{
        print_contact(return_ptr, mode);
    }
}

void print_tab (char mode)
{
    char user_input[20];
    char letter;
    CONTACT_T *cp;

    printf("\nPlease enter last name tab letter: ");
    scanf("%s", user_input);
    printf("%s\n\n", user_input); //echo print

    upper(user_input);
    letter = user_input[0];
    
    cp = get_next_contact(letter);
    while (cp != NULL){
        print_contact(cp, mode);
        cp = get_next_contact(letter);
    }
}

void process_state_contacts (char mode)
{
    char state_abbrv[20];

    printf("\nPlease enter two-letter state abbreviation: ");
    scanf("%s", state_abbrv);
    printf("%s\n\n", state_abbrv); //echo print

    upper(state_abbrv);

    print_state_contacts(state_abbrv, mode);
}