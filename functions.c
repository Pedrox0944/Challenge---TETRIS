#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_PART_COLOR_SIZE 15

const char *primary_color[] = {"red", "black", "blue", "purple", "white", "green", "pink", "yellow"};

typedef enum Order_part
{
    T = 1,
    S1 = 2,
    S2 = 3,
    UI = 4, // C understands I as a constant in the complex lib, that's why I made this UI
    L1 = 5,
    L2 = 6,
    Q = 7
} Order_part;

const char *part_type(Order_part order_part)
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

const char *border_description(char part_border)
{
    switch (part_border) 
    {
        case 'y':
            return "With borders";
        case 'n':
            return "Bordless";
        default:
            return "Error! Your choice is invalid!";       
    }
}

typedef struct Part
{
    enum Order_part order_part;
    char color[MAX_PART_COLOR_SIZE];
    char part_border;
    int weight;
    int size_part;
    struct Part *next;
    struct Part *previous;
}part;

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

part *create_part(enum Order_part order_part, char color[MAX_PART_COLOR_SIZE], char part_border)
{
    part *new = malloc(sizeof(part));
    new->order_part = order_part;
    strcpy(new->color, color);
    new->part_border = part_border;
    new->weight = 0;
    new->size_part = 0;
    new->next = NULL;
    new->previous = NULL;
    return new;
}

int valid_color(char color[MAX_PART_COLOR_SIZE])
{
    for (int i = 0; color[i] != '\0' ; i++) {
        color[i] = tolower(color[i]);
    }
    
    for (int i = 0; primary_color[i] != NULL; i++) 
    {
        if (strcmp(color, primary_color[i]) == 0) 
        {
            return 1;
        }
    }
    return 0;
}

void register_part(List *list_parts)
{
   char color[MAX_PART_COLOR_SIZE];
   char part_border;
   int order_input;
   
   do 
   {
       system("clear");
       puts("Please select part you want");
       printf("[1] - Part T\n[2] - Part S1\n[3] - Part S2\n[4] - Part I\n[5] - Part L1\n[6] - Part L2\n[7] - Part Q\nyour choice: \n");
       scanf("%d", &order_input);
       
       if (order_input < 1 || order_input > 7) 
        {
            system("clear");
            puts("Error! Your choice is invalid!");
        }
   } while (order_input < 1 || order_input > 7);
   
   do 
   {
       system("clear");
       printf("Options color: Red, Yellow, Pink, Purple, Blue, Black, White, Green\n");
       printf("Enter color: ");
       scanf("%s", color);
       
       if (strlen(color) > MAX_PART_COLOR_SIZE) 
        {
           puts("Error! Color name is too long.");
           continue;
        }
       
       if (!valid_color(color)) 
        {
            puts("Error! Invalid color. Plese type a valid color: ");
            continue;
        }
       break;
   } while (1);
   
   do 
   {
       printf("Enter part border (y or n): ");
       scanf(" %c", &part_border);
       if (part_border != 'y' && part_border != 'n') 
        {
           system("clear");
           puts("Error! Your choice is invalid! Please type again between y or n: ");
        }
   } while (part_border != 'y' && part_border != 'n');
   
   part *new_part = create_part((Order_part)order_input,color,part_border);
   if (new_part == NULL) return;
   
   if (list_parts->start == NULL) 
    {
       list_parts->start = new_part;
       list_parts->end = new_part;
    }
   else
    {
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
    if (list->start == NULL) 
    {
        printf("List is empty");
    }
    
    part *assistant = list->start;
    while(assistant != NULL) {
        printf("Part: %s - Color %s - %s\n", part_type(assistant->order_part), assistant->color, border_description(assistant->part_border));
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
    if (list->start == NULL) 
    {
        puts("List empty!");
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

