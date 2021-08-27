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
    NewNode->right = NewNode->left = 0x0;

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

    while (queue.size != 0) dequeue(&queue);
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

        //In this case, the tree was completely removed
        else
        {
            *root = 0x0;
            free(branch);
        }
    }

    //Just the left kid: the kid takes its place
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

    //Just the right kid: the kid takes its place
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

    //With 2 kids, the successor takes its place
    else
    {
        if (branch != *root)
        {
            Node *toDelete, *successor;
            toDelete = branch;
            successor = toDelete->right;


            //Finding the successor
            while (successor->left != 0x0) successor = successor->left;
            successor->left = toDelete->left;


            //The pointer changes depends on the successor position
            if (toDelete->right != successor)
            {
                successor->parent->left = successor->right;
                if (successor->right != 0x0) successor->right->parent = successor->parent;
                successor->right = toDelete->right;
                toDelete->right->parent = successor;
            }

            if (toDelete->parent->left == toDelete) toDelete->parent->left = successor;
            else toDelete->parent->right = successor;

            if (toDelete->left != 0x0) toDelete->left->parent = successor;
            successor->parent = toDelete->parent;
            free(toDelete);
        }
        else
        {
            if (branch->right != 0x0)
            {
                Node *successor;
                successor = branch->right;
                while (successor->left != 0x0) successor = successor->left;
                if (branch->right != successor)
                {
                    successor->parent->left = successor->right;
                    if (successor->right != 0x0) successor->right->parent = successor->parent;
                }
                *root = successor;
                branch->right->parent = successor;
                if (branch->left != 0x0) branch->left->parent = successor;
                if (branch->right != successor) successor->right = branch->right;

                successor->left = branch->left;
                successor->parent = 0x0;
                free(branch);
            }

            //In case there's no successor, the predecessor takes its place
            else
            {
                *root = branch->left;
                branch->left->parent = 0x0;
                free(branch);
            }
        }
    }
}

//Function that looks for the maximum
void maximum(Node *root)
{
    //In case the tree is empty, there's no maximum
    if (root == 0x0)
    {
        printf("vazia\n");
        return;
    }
    Node *branch;
    branch = root;

    //I look for the rightest node
    while (branch->right != 0x0) branch = branch->right;
    printf("%d\n", branch->value);
}

//Function that looks for the minimum
void minimum(Node *root)
{
    //If the tree is empty, there's no minimum
    if (root == 0x0)
    {
        printf("vazia\n");
        return;
    }
    Node *branch;
    branch = root;

    //I look for the leftest node
    while (branch->left != 0x0) branch = branch->left;
    printf("%d\n", branch->value);
}

//Function that looks for the number before the one given
void predecessor(Node *root)
{
    int number;
    scanf("%d", &number);

    Node *branch;
    branch = root;

    //If the tree is empty, there can't be any branch
    if (branch == 0x0) printf("nao ha\n");

    else
    {
        //This piece of code finds the spot running through the tree to right/left
        while ((branch->value > number)? branch->left:branch->right != 0x0 && branch->value != number)
            branch = (branch->value > number)? branch->left:branch->right;

        //If the number is not in the tree, there will be no predecessor
        if (branch->value != number) printf("nao ha\n");
        else
        {

            //If there's a left kid, the predecessor is the rightest element in the left branch
            if (branch->left != 0x0)
            {
                branch = branch->left;
                while(branch->right != 0x0) branch = branch->right;
            }

            //Otherwise, I look for the first ancestor that contains the number in the right branch
            else
            {
                //Well, if the branch is the root, there will be no ancestor
                if (branch == root)
                {
                    printf("nao ha\n");
                    return;
                }
                else if (branch->parent->right == branch) branch = branch->parent;
                else
                {
                    while(branch->parent != 0x0)
                    {
                        if (branch->parent->right == branch)
                        {
                            branch = branch->parent;
                            break;
                        }
                        branch = branch->parent;
                    }

                    if (branch->value > number)
                    {
                        printf("nao ha\n");
                        return;
                    }
                }
            }
            printf("%d\n", branch->value);
        }
    }
}

//Function that looks for the number after the one given
void successor(Node *root)
{
    int number;
    scanf("%d", &number);

    Node *branch;
    branch = root;

    //If the tree is empty, there can't be any branch
    if (branch == 0x0) printf("nao ha\n");

    else
    {
        //This piece of code finds the spot running through the tree to right/left
        while ((branch->value > number)? branch->left:branch->right != 0x0 && branch->value != number)
            branch = (branch->value > number)? branch->left:branch->right;

        //If the number is not in the tree, there will be no predecessor
        if (branch->value != number) printf("nao ha\n");
        else
        {
            //If there's a right kid, the predecessor is the leftest element in the right branch
            if (branch->right != 0x0)
            {
                branch = branch->right;
                while(branch->left != 0x0) branch = branch->left;
            }

            //Otherwise, I look for the first ancestor that contains the number in the left branch
            else
            {
                //Well, if the branch is the root, there will be no ancestor
                if (branch == root)
                {
                    printf("nao ha\n");
                    return;
                }
                else if (branch->parent->left == branch) branch = branch->parent;
                else
                {
                    while(branch->parent != 0x0)
                    {
                        if (branch->parent->left == branch)
                        {
                            branch = branch->parent;
                            break;
                        }
                        branch = branch->parent;
                    }

                    if (branch->value < number)
                    {
                        printf("nao ha\n");
                        return;
                    }
                }
            }
            printf("%d\n", branch->value);
        }
    }
}

//Recursive function that counts the amount of numbers in the given interval climbing through the tree in in-order and prints them
int search_interval(Node *branch, int n1, int n2, int cont)
{
    if (branch->left != 0x0) cont = cont + search_interval(branch->left, n1, n2, 1);
    if (branch->value >= n1 && branch->value <= n2)
    {
        cont += 1;
        printf("%d ", branch->value);
    }
    if (branch->right != 0x0) cont = cont + search_interval(branch->right, n1, n2, 1);

    //cont is an integer that makes this if only possible to be run in the first function call
    if (cont == 0) printf("nenhuma");
    return cont - 1;
}

//Function that destroys the tree
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
