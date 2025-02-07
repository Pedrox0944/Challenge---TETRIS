#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_PART_COLOR_SIZE 15

typedef enum Order_part
{
    T = 1,
    S1 = 2,
    S2 = 3,
    UI = 4, // O C entende o I como uma constante da lib complex, por isso fiz esse UI
    L1 = 5,
    L2 = 6,
    Q = 7
}Order_part;

const char *part_name(Order_part order_part)
{
    switch (order_part)
    {
        case T:
            return "T";
        case S1:
            return "S1";
        case S2:
            return "S2";
        case UI:
            return "I";
        case L1:
            return "L1";
        case L2:
            return "L2";
        case Q:
            return "Q";
        default:
            return "Error! Your choice is invalid!";
    }
}

typedef struct Part
{
    enum Order_part order_part;
    char color[MAX_PART_COLOR_SIZE];
    char part_edge;
    int weight;
    int size_part;
    struct Part *next;
    struct Part *previous;
}part;

const char *edge_description(char part_edge)
{
    switch (part_edge) {
        case 'y':
            return "With Edges";
        case 'n':
            return "Bordless";
        default:
            return "Error! Your choice is invalid!";
    }
}

typedef struct List
{
  part *start;  
  part *end;
  int size_list;
} List;

List *create_list()
{
    List *new = malloc(sizeof(List));
    new->start = NULL;
    new->end = NULL;
    new->size_list = 0;
    return new;
}

part *create_part(enum Order_part order_part, char color[MAX_PART_COLOR_SIZE], char part_edge)
{
    part *new = malloc(sizeof(part));
    new->order_part = order_part;
    strcpy(new->color, color);
    new->part_edge = part_edge;
    new->weight = 0;
    new->size_part = 0;
    new->next = NULL;
    new->previous = NULL;
    return new;
}

void register_part(List *list_parts)
{
   char color[MAX_PART_COLOR_SIZE];
   char part_edge;
   int order_input;
   
   puts("Plesa select part you want");
   printf("[1] - Peça T\n[2] - Peça S1\n[3] - Peça S2\n[4] - Peça I\n[5] - Peça L1\n[6] - Peça L2\n[7] - Peça Q\nyour choice: \n");
   scanf("%d", &order_input);
   
   if (order_input < 0 || order_input > 7) 
    {
        puts("Error! Your choice is invalid!");
    }
   
   printf("Enter color: ");
   scanf("%s", color);
   
   printf("Enter part edge (y or n): ");
   scanf(" %c", &part_edge);
   
   part *new_part = create_part((Order_part)order_input,color,part_edge);
   if (new_part == NULL) {
       return;
   }
   
   if (list_parts->start == NULL) {
       list_parts->start = new_part;
       list_parts->end = new_part;
   }
   else{
       list_parts->end->next = new_part;
       new_part->previous = list_parts->end;
       list_parts->end = new_part;
   }
   list_parts->size_list++;
   puts("Your part registered succesfully!");
   sleep(1);
   system("clear");
}

void list_all(List *list)
{
    system("clear");
    if (list->start == NULL) {
        printf("List is empty");
    }
    
    part *assistant = list->start;
    while(assistant != NULL) {
        printf("Part: %s - Color %s - %s\n", part_name(assistant->order_part), assistant->color, edge_description(assistant->part_edge));
        assistant = assistant->next;
    }
    sleep(2);
}

void disconnect_part_list(part *part, List *list)
{
    if (part == list->start)
    { 
        list->start = part->next;
    }
    if (part == list->end) 
    {
        list->end = part->previous;
    }
    
    if (part->previous != NULL)
    {
        part->previous->next = part->next;
    }

    if (part->next != NULL)
    {
        part->next->previous = part->previous;
    }

    if (list->start == NULL) 
    {
        list->end = NULL;
    }
}


void insert_part_list(part *assistant, part *swap, List *list)
{
    if (swap == NULL) 
    {  
        assistant->next = list->start;
        assistant->previous = NULL;
        if (list->start != NULL) 
        {
            list->start->previous = assistant;
        }
        list->start = assistant;
    } 
    else 
    {
        assistant->next = swap->next;
        assistant->previous = swap;
        
        if (swap->next != NULL) 
        {
            swap->next->previous = assistant;
        }
        swap->next = assistant;
        
        if (list->end == swap) 
        {
            list->end = assistant;
        }
    }
}

void rearrange_list(List *list)
{
    if (list->start == NULL || list->start->next == NULL) 
    {
        return;
    }
    
    part *assistant = list->start->next;
    while (assistant != NULL) 
    {
        part *next_part = assistant->next;

        if (assistant->previous != NULL && assistant->order_part < assistant->previous->order_part) 
        {
            part *swap = assistant->previous;
            disconnect_part_list(assistant, list);
            
            while (swap != NULL && assistant->order_part < swap->order_part) 
            {
                swap = swap->previous;
            }
            insert_part_list(assistant, swap, list);
        }

        assistant = next_part;
    }
    list_all(list);
}




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
                puts("please select the part you want");
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
