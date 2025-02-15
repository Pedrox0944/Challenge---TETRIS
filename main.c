#include <stdio.h>
#include <stdbool.h>
#include "functions.c"

int main()
{
    List *list = create_list();
    int choice;
    float variable_temp_choice;
    
    while (true)
    {
        puts("---MAIN MENU---");
        puts("Please type your choice");
        puts("[1] - Register part.");
        puts("[2] - List all parts.");
        puts("[3] - Rearranger parts.");
        puts("[4] - Quit.");
        printf("Type your choice: ");
        
        if (scanf("%f", &variable_temp_choice) != 1) {
            puts("Please type a int number!");
            while (getchar() != '\n');
            continue;
        }
        if (variable_temp_choice == (int)variable_temp_choice) {
            choice = variable_temp_choice;
        }
        else {
            puts("Please type a int number");
            continue;
        }
        
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
                clear_screen();
                free_memory(list);
                puts("Thank you for your precious time to test this little program from a programmer who gets caught up in life every day! hahaha.");
                return false;
                break;
            default:
                puts("Error! Your choice is invalid!");
                continue;
                break;
        }   
    }
    return 0;
}