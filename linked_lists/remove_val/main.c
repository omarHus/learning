#include <stdio.h>
#include <stdlib.h>

struct node
{
    int val;
    struct node *next;
};
typedef struct node node_list;

// print values in the list
void print_list(node_list *head)
{
    node_list *current = head;

    while (current->next != NULL)
    {
        printf("%d\n", current->val);
        current = current->next;
    }
}

// function to add value to end of list
void push(node_list *head, int val)
{
    node_list *current = head;
    // iterate to end of list
    while (current->next != NULL)
    {
        current = current->next;
    }

    // adding val to the end of the list
    current->next = malloc(sizeof(node_list));  // create a new node at the end of the list
    current->next->val = val;       // add val to the new node
    current->next->next = NULL;     // make the new node the last node in the list
}

// remove the first item in the list
int pop(node_list **head)
{
    int out_val = 0;
    node_list *next_node = NULL;

    // in case there are no members in the list
    if(*head == NULL)
        return 0;

    /* store the next member in the list in next_node and release the memory to which *head points, then point *head to next_node */
    next_node = (*head)->next;
    out_val = (*head)->val;
    free(*head);
    *head = next_node;

    return out_val;
}

// remove an item with a specific val in the list
int remove_val(node_list **head, int val)
{
    int out_val = 0;
    node_list *current = *head;
    node_list *temp_node = NULL;

    // if removing first val then use the pop function on our list
    if (current->val == val)
        return pop(head);

    // iterate over the list
    while (current->next != NULL)
    {
        if (current->next->val == val) // if the next node has val then we can remove it
            break;

        current = current->next; // go to the next node
    }

    // remove node with val
    temp_node = current->next; // store node we will remove
    out_val = temp_node->val; // store val we will remove
    current = temp_node->next; // next node is now the node after the one we want to remove
    free(temp_node);

    return out_val;
}

int main(void)
{
    int i;
    int max = 5;
    node_list *start_list = NULL;
    node_list *current_list = NULL;
    node_list *new_list = NULL;

    for(i=0; i<max; i++)
    {
        if(i == 0)
        {
            start_list = malloc(sizeof(node_list));
            start_list->val = rand()%10;
            current_list = start_list;
        }
        else
        {
            new_list = malloc(sizeof(node_list));
            new_list->val = rand()%10;
            current_list->next = new_list;
            current_list = new_list;
        }
    }
    current_list->next = NULL;

    current_list = start_list;
    print_list(current_list);
    free(start_list);
    free(new_list);

    return 0;
}
