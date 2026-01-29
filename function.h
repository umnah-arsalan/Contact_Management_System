#ifndef FUNCTION_H
#define FUNCTION_H

#define FILE_NAME "contacts.dat"

struct Contact {
    char name[50];
    char contact[15];
    char email[30];
};

void Current_time();
int contact_check(const char *contact);
void sort_contacts(void);
void add_contact(void);
void view_contacts(void);
void search_contact(void);
void update_contact(void);
void delete_contact(void);

#endif