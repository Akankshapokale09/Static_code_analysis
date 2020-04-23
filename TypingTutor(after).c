#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>

typedef struct stack {
    char word[50];
    struct stack* next;
}stack;

int menu(int choice);
void startgame();
void tutor(stack* stk, int time);
void push(stack** stk, char* ch);
void display(stack* stk);
void pop(stack** stk, char* op);

void main()
{
	/*Mitigations in the comments*/

    int choice = 2;         //Initialising choice variable with default value

    /*  Shifting 32-bit value by 100000 bits is undefined behaviour so changing the value of a to 5 */
    int a = 5;
    a << a;

    /*     Deallocation of auto variable resulting in undefined behaviour, so the pointer is set to NULL before freeing the memory  */

    int* p = &a;
    *p = 10;
    p = NULL;
    free(p);

    printf("Division by one", 10/1);     //Division by zero is a vulnerability so changing 0 to 1

    /*  Null pointer dereference: storing the address of a in the pointer as a mitigation  */
    int* pointer = &a;
    *pointer = 10;

    char name[20];
    name[19] = '\0';      //Array Out of bounds mitigation: chaning index from 21 to 19

    printf("\n\t*******************************************\n");
    printf("\n\t\t\tWELCOME");
    printf("\n\n\t\t\tTO");
    printf("\n\n \t\t\tTYPING TUTOR!");
    printf("\n\n\t*******************************************\n");
    printf("\n\tPress any key to continue....");
    getch();
    system("cls");
    choice = menu(choice);
    while(1)
    {
        switch(choice)
        {
            case 1:
                        startgame();
                        system("cls");
                        break;
            case 2:
                        system("cls");
                        printf("\n\t************************\n");
                        printf("\t       INSTRUCTIONS");
                        printf("\n\t************************\n");
                        printf("\n\tN(given by the user) words will be generated on the screen\n");
                        printf("\n\tYou have to type each words and press space,and remember that you can use maximum of 2 backspaces for each word\n");
                        printf("\n\tFinally your score of correct and incorrect words will be generated along with the accuracy, \n\n\tGOOD LUCK !\n");
                        printf("\n\n\tPress any key to go to the Main Menu...");
                        getch();
                        system("cls");
                        break;
            case 3:
                        exit(0);
                        break;
            default:
                        printf("\n\tINVALID OPTION!");
                        printf("\n\tPress any key to re-enter your option...\n");
                        getch();
                        system("cls");
        }
        choice = menu(choice);
    }
}

int menu(int c)
{
    printf("\n\t\t=================================\n");
	printf("\t\t\t    TYPING TUTOR");
	printf("\n\t\t=================================");
	printf("\n\n\t\t1) Start The Game");
	printf("\n\n\t\t------------------------");
    printf("\n\n\t\t2) HOW TO PLAY");
	printf("\n\n\t\t------------------------");
	printf("\n\n\t\t3) Exit");
	printf("\n\n\t\t------------------------");
    printf("\n\n\tEnter any option: ");
    scanf("%d",&c);
    return c;
}

void startgame()
{
    system("cls");
    int i;
    printf("\n\t******** HAVE FUN ! ********\n");
    printf("\n\tHow many words you want to type: ");
    scanf("%d", &i);
    int time = i;       //Inintialising time variable with i
    char c;
    stack *stk = NULL;
    FILE *fp = fopen("sampleFICT.txt", "r");
    char* ch = (char*)calloc(sizeof(char), 50);
    while(i)
    {
        int j = 0;
        while((c = fgetc(fp)) != 32)
        {
            ch[j] = c;
            j++;
        }
        push(&stk, ch);
        i--;
    }
    free(ch);       //Freeing the dynamic allocation for memory leak vulnerability
    fclose(fp);
    display(stk);
    tutor(stk, time);
}

void tutor(stack* stk, int time)
{
    int correct, incorrect, flag, count, x;
    correct = incorrect = flag = count = x = 0;
    while(time)
    {
        int i=0;
        x = 0;
        char input[50], output[50];
        char ch;
        strcpy(input, "");
        while((ch = getche()) != ' ')
        {
            input[i]=ch;
            if(ch == '\b')
            {
                x++;
                flag++;
                i=i-2;
            }
            if(x == 3)
            {
                printf("\n\tYou broke the rules!! Try again.\n");
                getch();
                break;
            }
            i++;
        }
        if(x == 3) break;
        input[i] = '\0';
        pop(&stk, output);
        if(!strcmp(input, output)) correct++;
        else incorrect++;
        count++;
        time--;
    }
    if(x == 3) return;
    float ac = 100.0;
    if(flag != 0)
        ac = ac-(count/flag)*0.1;
    ac = ac - incorrect;
    printf("\n\nCorrect: %d\nIncorrect: %d\nAccuracy: %f\n", correct, incorrect, ac);
    if(correct > incorrect)
        printf("\nGood Job!\n");
    else
        printf("\nYou need to work on your typing skills, :(\n");
    printf("\n\n\tPress any key to go to the Main Menu...");
    getch();
}

void push(stack** stk, char* ch)
{
    stack* node = (stack*)malloc(sizeof(stack));
    strcpy(node->word, ch);
    node->next = *stk;
    (*stk)= node;
}
void display(stack* stk)
{
    printf("\n");
    stack* node = stk;
    while(node != NULL)
    {
        printf("%s ", node->word);
        node = node->next;
    }
    printf("\n");
}
void pop(stack** stk, char* op)
{
    stack* node = *stk;
    *stk = node -> next;
    strcpy(op, node -> word);
}
