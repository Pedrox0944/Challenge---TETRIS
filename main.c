#include <stdio.h>
#include "functions.c"

int main()
{
    List *list = create_list();
    int choice;
    while (choice < 4)
    {
        puts("---MAIN MENU---");
        puts("Please type your choice");
        puts("[1] - Register part.");
        puts("[2] - List all parts.");
        puts("[3] - Rearranger parts.");
        puts("[4] - Quit.");
        scanf(" %d", &choice);
        
        switch (choice)
        {
            case 1:
                register_part(list);
                break;
            case 2:
                list_all(list);
                break;
            case 3:
                rearrange_list(list);
                break;
            case 4:
                break;
            default:
                puts("Error! Your choice is invalid!");
        }   
    }
    return 0;
}