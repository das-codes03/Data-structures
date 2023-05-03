#include <iostream>
using namespace std;

struct node
{
    int data;
    node *next;
    node(int data = 0, node *next = NULL) : data(data), next(next) {}
};
node *insertAt(node *at, int data = 0)
{
    if (at == NULL)
        throw runtime_error("NULL node exception");
    at->next = new node(data, at->next);
    return at->next;
}
node *create()
{
    cout << "Enter number of nodes" << endl;
    int n;
    cin >> n;
    if (n <= 0)
        throw runtime_error("Number of elements must be >= 1.");
    node *curr = NULL;
    node *head = NULL;
    for (int i = 0; i < n; i++)
    {
        int data = 0;
        cout << "Enter node " << (i + 1) << ": ";
        cin >> data;
        if (curr)
            curr = insertAt(curr, data);
        else
            head = curr = new node(data);
    }
    return head;
}

node *insertBeginning(node *head, int data)
{
    return new node(data, head);
}

node *insertEnd(node *head, int data)
{
    // traverse till end of list
    if (!head)
        return new node(data);
    node *curr = head;
    while (curr->next)
    {
        curr = curr->next;
    }
    insertAt(curr, data);
    return head;
}

node *insertAtPosition(node *head, int position, int data)
{
    if (position <= 0)
        throw runtime_error("Position must be >= 1.");
    if (position == 1)
        return insertBeginning(head, data);

    node *curr = head;
    for (int i = 1; i < position - 1; ++i)
    {
        if (curr)
            curr = curr->next;
        if (!curr)
            throw runtime_error("Out of bounds");
    }
    insertAt(curr, data);
    return head;
}

node *deleteEnd(node *head)
{

    if (head == NULL)
        throw runtime_error("Head node can't be NULL");
    else if (head->next == NULL) // single element only
    {
        delete (head);
        return NULL;
    }
    else
    {
        // traverse till end
        node *curr = head;
        while (curr->next->next)
        {
            curr = curr->next;
        }
        // delete the next node
        delete (curr->next);
        curr->next = NULL;
        return head;
    }
    return NULL;
}

node *deleteBeginning(node *head)
{
    if (head == NULL)
        throw runtime_error("Head cannot be NULL");
    // get next node
    node *newHead = head->next;
    delete (head);
    return newHead;
}

node *deleteAtPosition(node *head, int position)
{
    if (position == 1)
        return deleteBeginning(head);

    node *curr = head;
    for (int i = 1; i < position - 1; ++i)
    {
        curr = curr->next;
    }
    node *toDel = curr->next;
    curr->next = curr->next->next;
    delete (toDel);
    return head;
}
// a<-b c->d

//
node *reverse(node *head)
{
    node *curr = head;
    node *next = NULL;
    node *prev = NULL;
    while (curr)
    {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
        if (!curr)
            return prev;
    }
}

node *concatenate(node *head1, node *head2)
{
    // traverse till end of first list
    if (head1 == NULL)
        throw runtime_error("Head node cannot be NULL.");
    node *curr = head1;
    while (curr->next)
    {
        curr = curr->next;
    }
    curr->next = head2;
    return head1;
}

void displayList(node *head)
{
    while (head)
    {
        cout << head->data << " -> ";
        head = head->next;
    }
    cout << "NULL" << endl;
}

int main()
{
    int fn = 1;
    int data = 0;
    int pos = 0;
    node *head = NULL;
    while (fn)
    {
        cout << "1. Create linked list" << endl;
        cout << "2. Insert element at beginning." << endl;
        cout << "3. Insert element at position." << endl;
        cout << "4. Insert element at end." << endl;
        cout << "5. Delete element at beginning." << endl;
        cout << "6. Delete element at position." << endl;
        cout << "7. Delete element at end." << endl;
        cout << "8. Reverse linked list" << endl;
        cout << "9. Concatenate linked list." << endl;
        cout << "0. Exit" << endl;
        cout << "What do you want to do?" << endl;
        cin >> fn;

        switch (fn)
        {
        case 1:
            head = create();
            break;
        case 2:
            cout << "Enter data to insert at beginning: ";
            cin >> data;
            head = insertBeginning(head, data);
            break;
        case 3:
            cout << "Enter data to insert at position: ";
            cin >> data;
            cout << "Enter position to insert: ";
            cin >> pos;
            head = insertAtPosition(head, pos, data);
            break;
        case 4:
            cout << "Enter data to insert at end: ";
            cin >> data;
            head = insertEnd(head, data);
            break;
        case 5:
            head = deleteBeginning(head);
            break;
        case 6:
            cout << "Enter position to delete: ";
            cin >> pos;
            head = deleteAtPosition(head, pos);
            break;
        case 7:
            head = deleteEnd(head);
            break;
        case 8:
            head = reverse(head);
            break;
        case 9:
            cout << "First Create a linked list to concatenate: " << endl;
            head = concatenate(head, create());
            break;
        default:
            break;
        }
        displayList(head);
    }
}