# yellow-pages
This C project takes contact information from an excel spreadsheet and implements it into a dynamically allocated, alphabetic, and searchable list.

It utilizes a pre-defined structure and dynamically allocated memory for the contact nodes. Each node is separeted alpahbetically and put into a linked list based on the
first character of the last name of the individual. Each linked list is a part of a larger 26 index-long bucket list.

In order to use this program, download all 8 files including the addr.csv file
The code can be compiled using this command: "gcc main.c contact.c contact_list.c utils.c -o cl"
and run using this command: "cl addr.csv" where addr.csv is the excel spreadsheet containing the contact information.
