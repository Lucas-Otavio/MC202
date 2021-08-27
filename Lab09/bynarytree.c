#include "bynarytree.h"

//Functions that inserts: it takes the new value, creates its node and inserts it in the right place
void insert(Node **root)
{
    //Receiving the new value
    int number;
    scanf("%d", &number);

    //Creating the new node and making sure it was a success
    Node *NewNode;
    NewNode = malloc(sizeof(Node));
    if (!NewNode) exit(1);
    NewNode->value = number;
    NewNode->right = 0x0;
    NewNode->left = 0x0;

    //Empty tree case
    if (*root == 0x0)
    {
        *root = NewNode;
        NewNode->parent = 0x0;
    }

    //Ordinary case: once found the place it should be, we just change some pointers
    else
    {
        Node *branch;
        branch = *root;

        //This piece of code finds the spot
        while ((branch->value > number)? branch->left:branch->right != 0x0 && branch->value != number)
            branch = (branch->value > number)? branch->left:branch->right;

        //There can't be repeated elements and we have to make sure it isn't going on
        if (branch->value == number) return;

        //Finally, it's necessary to insert the node in the right spot
        else
        {
            NewNode->parent = branch;
            if (branch->value > number) branch->left = NewNode;
            else branch->right = NewNode;
        }
    }
}

//Recursive Function that prints the tree in preorder: first the node, then the left and right branches
void preorder(Node *branch)
{
    printf("%d ", branch->value);
    if (branch->left != 0x0)  preorder(branch->left);
    if (branch->right != 0x0) preorder(branch->right);
}

//Recursive Function that prints the tree in inorder: first the left branch, then the node, then the right branch
void inorder(Node *branch)
{
    if (branch->left != 0x0)  inorder(branch->left);
    printf("%d ", branch->value);
    if (branch->right != 0x0) inorder(branch->right);
}

//Recursive Function that prints the tree in postorder: first the left and right branches, then the node
void postorder(Node *branch)
{
    if (branch->left != 0x0)  postorder(branch->left);
    if (branch->right != 0x0) postorder(branch->right);
    printf("%d ", branch->value);
}

//Function that uses a queue to print the tree in width
void width(Node *branch)
{
    queue queue;
    queue.size = 0;
    enqueue(&queue, branch);

    while (queue.size != 0)
    {
        //printf("esse eh o valor da head: %d\n", queue.head->branch->value);
        dequeue(&queue);
    }
}

//Function that returns if a given number is or not in the tree
void search(Node *branch)
{
    int number;
    scanf("%d", &number);

    //If the tree is empty, there can't be any branch
    if (branch == 0x0) printf("%d nao pertence\n", number);

    else
    {
        //This piece of code finds the spot running through the tree to right/left
        while ((branch->value > number)? branch->left:branch->right != 0x0 && branch->value != number)
            branch = (branch->value > number)? branch->left:branch->right;

        if (branch->value == number) printf("%d pertence\n", number);
        else printf("%d nao pertence\n", number);
    }

}

//Function that removes an element from the tree and rearrange it as needed
void extract(Node **root)
{
    int number;
    scanf("%d", &number);
    Node *branch;

    branch = *root;

    //If the tree is empty, there's nothing to extract
    if (branch == 0x0) return;


    //This piece of code finds the spot
    while ((branch->value > number)? branch->left:branch->right != 0x0 && branch->value != number)
        branch = (branch->value > number)? branch->left:branch->right;


    //Don't take out anything if the number is not in the tree
    if (branch->value != number) return;

    //Basically I divided the cases into: no kid, only left, only right, both kids
    //Generally I just move some pointers and change the root pointer if the root is removed
    if (branch->right == 0x0 && branch->left == 0x0)
    {
        if (branch != *root)
        {
            Node *toDelete;
            toDelete = branch;
            branch = branch->parent;
            if (branch->left == toDelete) branch->left = 0x0;
            else branch->right = 0x0;
            free(toDelete);
        }
        else
        {
            *root = 0x0;
            free(branch);
        }
    }

    else if (branch->right == 0x0)
    {
        if (branch != *root)
        {
            Node *toDelete;
            toDelete = branch;
            branch = branch->parent;
            if (branch->left == toDelete) branch->left = toDelete->left;
            else branch->right = toDelete->left;
            toDelete->left->parent = branch;
            free(toDelete);
        }
        else
        {
            *root = branch->left;
            branch->left->parent = 0x0;
            free(branch);
        }
    }

    else if (branch->left == 0x0)
    {
        if (branch != *root)
        {
            Node *toDelete;
            toDelete = branch;
            branch = branch->parent;
            if (branch->left == toDelete) branch->left = toDelete->right;
            else branch->right = toDelete->right;
            toDelete->right->parent = branch;
            free(toDelete);
        }
        else
        {
            *root = branch->right;
            branch->right->parent = 0x0;
            free(branch);
        }
    }

    else
    {
        if (branch != *root)
        {
            Node *toDelete, *previous;
            toDelete = branch;
            previous = toDelete->left;
            while (previous->right != 0x0) previous = previous->right;
            previous->right = toDelete->right;

            if (toDelete->left != previous) previous->left = toDelete->left;
            else previous->left = 0x0;

            if (toDelete->parent->right == toDelete) toDelete->parent->right = previous;
            else toDelete->parent->left = previous;

            toDelete->right->parent = previous;
            previous->parent->right = 0x0;
            previous->parent = toDelete->parent;
            free(toDelete);
        }
        else
        {
            Node *previous;
            previous = branch->left;
            while (previous->right != 0x0) previous = previous->right;
            *root = previous;
            branch->left->parent = previous;
            branch->right->parent = previous;
            if (branch->left != previous) previous->left = branch->left;

            previous->right = branch->right;
            if (branch->left != previous) previous->parent->right = 0x0;
            previous->parent = 0x0;
            free(branch);
        }
    }
}

void cut(Node *branch)
{
    if (branch->left != 0x0) cut(branch->left);
    if (branch->right != 0x0) cut(branch->right);
    free(branch);
}

//Just a recursive debugging function
void details(Node *branch)
{
    printf(" Branch: %d ", branch->value);
    if (branch->parent != 0x0) printf(" Parent: %d ", branch->parent->value);
    else printf(" Parent: NULL ");
    if (branch->left != 0x0)  printf(" Left: %d ", branch->left->value);
    else printf(" Left: NULL ");
    if (branch->right != 0x0) printf(" Right: %d \n", branch->right->value);
    else printf(" Right: NULL \n");

    if (branch->left != 0x0)  details(branch->left);
    if (branch->right != 0x0) details(branch->right);
}


//Queue Function: inserts a new element in the head
void enqueue(queue *queue, Node *element)
{
    QueueNode *NewQueueNode;
    NewQueueNode = malloc(sizeof(QueueNode));
    NewQueueNode->branch = element;
    if (queue->size == 0) queue->head = NewQueueNode;
    else queue->tail->next = NewQueueNode;
    queue->tail = NewQueueNode;
    NewQueueNode->next = 0x0;
    (queue->size)++;
}

//Queue Function: removes the head element, but before inserts its children
void dequeue(queue *queue)
{
    if (queue->size == 0) return;
    QueueNode *toDelete;
    toDelete = queue->head;
    printf("%d ", toDelete->branch->value);
    if (toDelete->branch->left != 0x0) enqueue(queue, toDelete->branch->left);
    if (toDelete->branch->right != 0x0) enqueue(queue, toDelete->branch->right);
    queue->head = queue->head->next;
    free(toDelete);
    (queue->size)--;
}
