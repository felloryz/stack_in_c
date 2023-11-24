#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct payload {
    struct payload *next_head;
    char emp_name[50];
    bool is_married;
    double salary;
} payload;

void print_menu(void);
void push(payload **stack_head, char emp_name[50], bool is_married, double salary);
void pop(payload **stack_head);
void pop_all(payload **stack_head);
void list(payload *stack_head);

int main(void)
{
    payload *stack_head = NULL;
    int command;
    char emp_name[50] = {0};
    char is_married_ans = 'n';
    bool is_married = false;
    double salary;

    while(1)
    {
        print_menu();
        printf("Select an option: ");
        scanf("%d", &command);
        getchar();

        switch (command)
        {
            case 1: // separate case into a function
                printf("\nEmployee name: ");
                fgets(emp_name, sizeof(emp_name), stdin);
                printf("Is married (y/n): ");
                scanf("%c", &is_married_ans); // use single variable
                if (is_married_ans == 'y')
                    is_married = true;
                else
                    is_married = false;
                printf("Salary: ");
                scanf("%lf", &salary);
                push(&stack_head, emp_name, is_married, salary);
                break;
            case 2:
                pop(&stack_head);
                break;
            case 3:
                pop_all(&stack_head);
                break;
            case 4:
                list(stack_head);
                break;
            case 5:
                // clear all memory
                return 0;
            default:
                break;
        }
    }

    return 0;
}

void print_menu(void)
{
    printf("\nWhat do you want to do?\n"
            "1) Push node to the stack\n"
            "2) Pop node from the stack\n"
            "3) Pop all nodes from the stack\n"
            "4) List all stack nodes\n"
            "5) Exit\n");
}

void push(payload **stack_head, char emp_name[50], bool is_married, double salary)
{
    payload *tmp = (payload *)calloc(sizeof(payload), 1);

    strcpy(tmp->emp_name, emp_name);
    tmp->is_married = is_married;
    tmp->salary = salary;
    tmp->next_head = *stack_head;
    *stack_head = tmp;
}

void pop(payload **stack_head)
{
    if (*stack_head == NULL) return;

    printf("\nEmployee name: %s"
            "Is married: %s\n"
            "Salary: %f\n\n",
            (*stack_head)->emp_name,
            (*stack_head)->is_married ? "Yes" : "No", 
            (*stack_head)->salary);

    payload *previous_head = *stack_head;
    *stack_head = (*stack_head)->next_head;
    free(previous_head);
}

void pop_all(payload **stack_head)
{
    while (*stack_head != NULL)
        pop(stack_head);
}

void list(payload *stack_head)
{
    while (stack_head != NULL)
    {
        printf("\nEmployee name: %s"
                "Is married: %s\n"
                "Salary: %f\n\n", 
                stack_head->emp_name, 
                stack_head->is_married ? "Yes" : "No", 
                stack_head->salary);
        stack_head = stack_head->next_head;
    }
}
