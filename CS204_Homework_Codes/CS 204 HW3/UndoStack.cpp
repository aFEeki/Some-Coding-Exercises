//Alp Demir Ekinci
#include "UndoStack.h"

void UndoStack::push(char operation, const string employeeName, string projectName, int priority) //puts the node on top
{
    StackNode* newNode = new StackNode(operation, employeeName, projectName, priority);
    newNode -> next = top;
    top = newNode;
}
void UndoStack::pop(char &operation, string &employeeName, string &projectName, int &priority) //takes the popped nodes values and gives them to the references
{
    operation = top -> operation;
    employeeName = top -> employee_name;
    projectName = top -> project_name;
    priority = top -> project_priority;
    StackNode* tempnode = top;
    top = top-> next;
    delete tempnode;
}
bool UndoStack::isEmpty() //checks if it is empty or not pretty simple
{
    if (!top)
    {
        return true;
    }
    else
    {
        return false;
    }
}
void UndoStack::clear()
{
    StackNode* current = top;
    while (current != nullptr)
    {
        StackNode* temp = current;
        current = current->next;
        delete temp; // Deallocate memory for the current node
    }
    top = nullptr; // Reset the firstNode pointer to nullptr after clearing the stack
}

