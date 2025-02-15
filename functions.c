#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_PART_COLOR_SIZE 15

const char *primary_color[] = {"red", "black", "blue", "purple", "white", "green", "pink", "yellow"};

// Preferi usar enumerações para linkar com os tipos da peça
typedef enum Order_part
{
    T = 1,
    S1,
    S2,
    UI, // Quando coloquei a peça I aqui o C ficou importanto a biblioteca complex e apontando que esse I é uma constante, por isso usei o UI, não impacta em nada no codigo
    L1,
    L2,
    Q 
} Order_part;

// Criei essa ponteiro para retornar para a peça seu tipo com seu formato em char
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

// Mesma lógica usada em cima
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

// Estrutura da peça
typedef struct Part
{
    enum Order_part order_part;
    char color[MAX_PART_COLOR_SIZE];
    char part_border;
    float weight;
    float size_part;
    struct Part *next;
    struct Part *previous;
}part;

// Estrutura da lista onde vou guardar as peças
typedef struct List
{
  part *start;  
  part *end;
  int size_list;
} List;

// Ponteiro que carrega a função de criar a lista
List *create_list()
{
    List *new = malloc(sizeof(List));
    new->start = NULL;
    new->end = NULL;
    new->size_list = 0;
    return new;
}

// Ponteiro que carrega a função de criar peça
part *create_part(enum Order_part order_part, char color[MAX_PART_COLOR_SIZE], char part_border, float weight, float size_part)
{
    part *new = malloc(sizeof(part));
    new->order_part = order_part;
    strcpy(new->color, color);
    new->part_border = part_border;
    new->weight = weight;
    new->size_part = size_part;
    new->next = NULL;
    new->previous = NULL;
    return new;
}

// Função pra limpar o terminal
void clear_screen(){
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// Função de validação da cor, checa se a cor digitada pelo o user está presente na array de cores
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

// Função que registra todos os atributos da peça na lista
void register_part(List *list_parts)
{
   char color[MAX_PART_COLOR_SIZE];
   char part_border;
   int order_input;
   float order_input_temp;
   float weight, size_part;
   
   do 
   {
       clear_screen();
       puts("Please select part you want");
       printf("[1] - Part T\n[2] - Part S1\n[3] - Part S2\n[4] - Part I\n[5] - Part L1\n[6] - Part L2\n[7] - Part Q\nyour choice: ");
    
       if(scanf("%f", &order_input_temp) != 1){
        puts("Error! Please type a int number");
        while(getchar() != '\n');
        continue;
       }
       else{
        while(getchar() != '\n');
       }

       if(order_input_temp == (int)order_input_temp){
        order_input = order_input_temp;
       }
       else {
        puts("Please type a int number!");
        continue;
       }
       
       if (order_input < 1 || order_input > 7) 
        {
            clear_screen();
            puts("Error! Your choice is invalid!");
        }
   } while ((order_input < 1 || order_input > 7) || (order_input_temp != (int)order_input_temp));
   
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
            sleep(1);
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
           clear_screen();
           puts("Error! Your choice is invalid! Please type again between y or n: ");
        }
   } while (part_border != 'y' && part_border != 'n');
   
   do {
       printf("Please enter the weight of the part: ");
       if (scanf("%f", &weight) != 1) {
           clear_screen();
           puts("Error! Your type a char or string. Please, type a number");
           while(getchar() != '\n' && getchar() != EOF);
           continue;
       }
       break;
   }while (1);
   
   do {
       printf("Please enter the size of the part: ");
       if (scanf("%f", &size_part) != 1) {
           clear_screen();
           puts("Error! Your type a char or string. Please, type a number");
           while(getchar() != '\n' && getchar() != EOF);
           continue;
       }
       break;
   }while (1);
   
   part *new_part = create_part((Order_part)order_input, color, part_border, weight, size_part);
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
   clear_screen();
}

// Função de listar todas as peças
void list_all(List *list)
{
    clear_screen();
    if (list->start == NULL) 
    {
        printf("List is empty!\n");
        sleep(1);
        clear_screen();
    }
    else{
        part *assistant = list->start;
        while(assistant != NULL) {
            printf("Part: %s - Color %s - %s\n", part_type(assistant->order_part), assistant->color, border_description(assistant->part_border));
            assistant = assistant->next;
        }
        sleep(1);
    }
}

// Função de desconectar o nó da lista
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

// Função de inserir o nó anteriormente desconectado da lista
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

// Função de reorganizar a lista, preferi usar o INSERTION SORT
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

// Função de desalocar memória, desaloca todos os nós e por fim a lista.
void free_memory(List *list){
    part *assistant_free = list->start;
    part *next;
    
    if (assistant_free != NULL)
    {
        next = assistant_free->next;
        free(assistant_free);
        assistant_free = next;
    }
    free(list);
}

