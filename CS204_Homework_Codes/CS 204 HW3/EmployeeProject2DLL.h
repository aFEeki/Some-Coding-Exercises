//Alp Demir Ekinci
#ifndef EmployeeProject2DLL_h
#define EmployeeProject2DLL_h

#include <iostream>
#include <string>
using namespace std;
struct ProjectNode
{
    string project_name;
    int project_priority;
    ProjectNode * next;
    ProjectNode * prev;
    ProjectNode(string name, int priority) : project_name(name), project_priority(priority), next(nullptr), prev(nullptr) {}
};
struct EmployeeNode
{
    string employee_name;
    ProjectNode * head;
    ProjectNode * tail;
    EmployeeNode * down;
    EmployeeNode(string name) : employee_name(name), head(nullptr), tail(nullptr), down(nullptr) {}
};
class EmployeeProject2DLL
{
private:
    EmployeeNode* head = nullptr;
public:
    EmployeeProject2DLL(){}
    bool isEmployeeAssignedToProject(string employeeName, string projectName);
    bool updateProjectPriority(string employeeName, string projectName, int& priority);
    bool assignEmployeeToProject(string employeeName, string projectName, int priority);
    void withdrawEmployeeFromProject(string employeeName, string projectName, int& priority);
    void printTheEntireList();
    void printEmployeeProjects(string employeeName, int order);
    void undo(char selection, string employeeName, string projectName, int priority);
    void clear();
};
#endif /* EmployeeProject2DLL_h */
