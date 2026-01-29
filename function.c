#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include "function.h"

void Current_time() {
    time_t t;
    struct tm *time_info;

    time(&t);
    time_info = localtime(&t);

    printf("Time: %02d-%02d-%04d  %02d:%02d:%02d\n\n",
        time_info->tm_mday, time_info->tm_mon + 1, time_info->tm_year + 1900,
        time_info->tm_hour, time_info->tm_min, time_info->tm_sec);
}

int contact_check(const char *contact) {
    struct Contact c;

    FILE *fp = fopen(FILE_NAME, "rb");
    if(!fp)
        return 0;
    
    while(fread(&c, sizeof(struct Contact), 1, fp)) {
        if (strcmp(contact, c.contact) == 0) {
            printf("\nContact number already exists!\n\n");
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    return 0;
}

void sort_contacts() {
    struct Contact contacts[100], temp;
    FILE *fp = fopen(FILE_NAME, "rb");
    int count = 0, i, j;

    if (!fp) {
        printf("\nNo contacts to print!\n\n");
        return;
    }

    while (fread(&contacts[count], sizeof(struct Contact), 1, fp))
        count++;
    fclose(fp);

    for (i = 0; i < count - 1; i++) {
        for (j = 0; j < count - i - 1; j++) {
            if (strcmp(contacts[j].name, contacts[j + 1].name) > 0) {
                temp = contacts[j];
                contacts[j] = contacts[j + 1];
                contacts[j + 1] = temp;
            }
        }
    }

    for (i = 0; i < count; i++) {
        printf("%-15s %-15s %s\n", contacts[i].name, contacts[i].contact, contacts[i].email);
    }
}

void add_contact() {
    struct Contact c;
    char contact[15];

    FILE *fp = fopen(FILE_NAME, "ab");
    FILE *text = fopen("contacts.txt", "a");

    printf("\nEnter name: ");
    scanf(" %[^\n]", c.name);

    printf("Enter contact number: ");
    scanf("%s", contact);

    while (contact_check(contact) != 0) {
        printf("Enter contact number: ");
        scanf("%s", contact);
    }
    strcpy(c.contact, contact);

    printf("Enter email address: ");
    scanf("%s", c.email);

    fwrite(&c, sizeof(struct Contact), 1, fp);

    printf("\nContact created successfully!\n");
    Current_time();
    
    fprintf(text, "%-15s %-15s %s\n", c.name, c.contact, c.email);

    fclose(fp);
}

void view_contacts() {
    printf("\nName\t\tPhone\t\tEmail\n");
    printf("-----------------------------------------------\n");

    sort_contacts();
    printf("\n");
}

void search_contact() {
    struct Contact c;
    char name[50], found = 0;

    FILE *fp = fopen(FILE_NAME, "rb");
    if (!fp) {
        printf("\nFile not found.\n\n");
        return;
    }

    printf("\nEnter contact name: ");
    scanf(" %[^\n]", name);

    while (fread(&c, sizeof(struct Contact), 1, fp)) {
        if (strcmp(name, c.name) == 0) {
            printf("\nContact(s) found\n\n");
            printf("Contact name: %s\n", c.name);
            printf("Contact number: %s\n", c.contact);
            printf("Email address: %s\n", c.email);
            found++;
        }
    }
    printf("\n");

    if (!found) 
        printf("\nContact not found.\n\n");

    fclose(fp);
}

void update_contact() {
    struct Contact c;
    FILE *fp = fopen(FILE_NAME, "rb");
    FILE *temp = fopen("temp.dat", "wb");
    char contact[15];
    int found = 0;

    if(!fp || !temp) {
        printf("\nFile error!\n\n");
        return;
    }

    printf("\nEnter contact number: ");
    scanf("%s", contact);

    while (fread(&c, sizeof(struct Contact), 1, fp)) {
        if (strcmp(contact, c.contact) == 0) {
            printf("\nEnter new name: ");
            scanf(" %[^\n]", c.name);

            printf("Enter new contact number: ");
            scanf("%s", c.contact);

            while (contact_check(c.contact) != 0) {
                printf("Enter new contact number: ");
                scanf("%s", c.contact);
            }

            printf("Enter new email address: ");
            scanf("%s", c.email);

            found++;
        }
        fwrite(&c, sizeof(struct Contact), 1, temp);
    }

    fclose(fp);
    fclose(temp);

    remove(FILE_NAME);
    rename("temp.dat", FILE_NAME);

    if (found) {
        printf("\nContact updated successfully!\n\n");
    } else {
        printf("\nContact not found!\n\n");
    }
}

void delete_contact() {
    struct Contact c;
    FILE *fp = fopen(FILE_NAME, "rb");
    FILE *temp = fopen("temp.dat", "wb");
    int found = 0;
    char contact[15];

    if (!fp || !temp) {
        printf("\nFile error!\n\n");
        return;
    }

    printf("\nEnter contact number to delete: ");
    scanf("%s", contact);

    while (fread(&c, sizeof(struct Contact), 1, fp)) {
        if (strcmp(contact, c.contact) != 0) {
            fwrite(&c, sizeof(struct Contact), 1, temp);
        } else {
            found++;
        }
    }

    fclose(fp);
    fclose(temp);

    remove(FILE_NAME);
    rename("temp.dat", FILE_NAME);

    if (found) {
        printf("\nContact deleted successfully!\n\n");
    } else {
        printf("\nContact not found!\n\n");
    }
}