#include<stdio.h>
#include<stdlib.h>
#include "function.h"

int main() {
    int choice;

    while (1) {
        printf("-------Contact Management System-------\n\n");
        printf("1. Create contact.\n");
        printf("2. View contacts.\n");
        printf("3. Search contact.\n");
        printf("4. Update contact.\n");
        printf("5. Delete contact.\n");
        printf("6. Save and exit.\n");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                add_contact();
                break;
            case 2:
                view_contacts();
                break;
            case 3:
                search_contact();
                break;
            case 4:
                update_contact();
                break;
            case 5:
                delete_contact();
                break;
            case 6:
                exit(0);
            default:
                printf("\nInvalid option! Try again.\n\n");
        }
    }
    return 0;
}