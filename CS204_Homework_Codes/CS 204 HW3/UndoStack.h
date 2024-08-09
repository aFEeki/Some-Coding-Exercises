//Alp Demir Ekinci
#ifndef UndoStack_h
#define UndoStack_h
#include <iostream>
#include <string>
using namespace std;

struct StackNode
{
    char operation;
    string employee_name;
    string project_name;
    int project_priority;
    StackNode * next;
    StackNode(char operation, string employeeName, string projectName, int priority) : operation(operation), employee_name(employeeName), project_name(projectName), project_priority(priority), next(nullptr) {}
};

class UndoStack
{
    private:
        StackNode* top = nullptr;
    public:
        UndoStack(){}
        void push(char operation, const string employeeName, string projectName, int priority);
        void pop(char& operation, string& employeeName, string& projectName, int& priority);
        bool isEmpty();
        void clear();
};
#endif
