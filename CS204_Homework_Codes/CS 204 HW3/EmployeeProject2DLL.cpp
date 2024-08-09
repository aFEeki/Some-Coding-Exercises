#include "EmployeeProject2DLL.h"
bool EmployeeProject2DLL::isEmployeeAssignedToProject(string employeeName,string projectName)
{
    EmployeeNode* currentEmployee = head;
    while (currentEmployee) //iterates thorugh each employee ancd checks if it is assigned to the given project name by comparing their names. Gives a boolean value accordingly.
    {
        if (currentEmployee -> employee_name == employeeName)
        {
            ProjectNode* currentProject = currentEmployee -> head;
            while (currentProject)
            {
                if (currentProject -> project_name == projectName)
                {
                    return true;
                }
                currentProject = currentProject -> next;
            }
        }
        currentEmployee = currentEmployee -> down;
    }
    return false;
}
bool EmployeeProject2DLL::assignEmployeeToProject(string employeeName, string projectName, int priority)
{
    EmployeeNode* currentEmployee = head;
    while (currentEmployee) //just as usual iterates through every employee
    {
        if (currentEmployee ->employee_name == employeeName) //once it finds the same employee it enters into the function itself.
        {
            ProjectNode* currentProject = currentEmployee -> head;
            while (currentProject) //checks for the existence of a project with the same priority
            {
                if (currentProject -> project_priority == priority)
                {
                    cout << "The project has not been added because there is another project with the same priority." << endl;
                    return false;
                }
                currentProject = currentProject -> next;
            }
            ProjectNode* newProject = new ProjectNode(projectName, priority);
            if (!currentEmployee -> head) //if the list is empty it creates one.
            {
                currentEmployee -> head = newProject;
                currentEmployee -> tail = newProject;
            }
            else //if it isn't empty it inserts the new object alphabetically.
            {
                currentProject = currentEmployee -> head;
                while (currentProject && (currentProject -> project_priority < priority))
                {
                    currentProject = currentProject -> next;
                }
                if (!currentProject) //for the case where there isnt any project.
                {
                    currentEmployee -> tail -> next = newProject;
                    newProject -> prev = currentEmployee -> tail;
                    currentEmployee -> tail = newProject;
                }
                else if(!currentProject -> prev) //for the case where the project is the head
                {
                    newProject -> next = currentEmployee -> head;
                    currentEmployee -> head -> prev = newProject;
                    currentEmployee -> head = newProject;
                }
                else
                {
                    newProject -> next = currentProject;
                    newProject -> prev = currentProject -> prev;
                    currentProject -> prev -> next = newProject;
                    currentProject -> prev = newProject;
                }
            }
            return true;
        }
        currentEmployee = currentEmployee -> down;
    }
    EmployeeNode* newEmployee = new EmployeeNode(employeeName); //creates a new employee node
    ProjectNode* newProject = new ProjectNode(projectName, priority); //creates a new project node
    newEmployee -> head = newProject;
    newEmployee -> tail = newProject;
    EmployeeNode* prevEmployee = nullptr;
    currentEmployee = head;
    while (currentEmployee && (newEmployee -> employee_name > currentEmployee -> employee_name)) //iteration and comparison to find the suitable place to add the new employee
    {
        prevEmployee = currentEmployee;
        currentEmployee = currentEmployee -> down;
    }
    if (!prevEmployee)
    {
        newEmployee -> down = head;
        head = newEmployee;
    }
    else
    {
        newEmployee -> down = prevEmployee -> down;
        prevEmployee -> down = newEmployee;
    }
    return true;
}
void EmployeeProject2DLL::withdrawEmployeeFromProject(string employeeName, string projectName, int& priority)
{
    EmployeeNode* currentEmployee = head;
    EmployeeNode* prevEmployee = nullptr;
    while (currentEmployee -> employee_name != employeeName) //finds the employee to be withdrewn
    {
        prevEmployee = currentEmployee;
        currentEmployee = currentEmployee -> down;
    }
    ProjectNode* currentProject = currentEmployee -> head;
    while (currentProject -> project_name != projectName) //finds the project to be withdrewn
    {
        currentProject = currentProject -> next;
    }
    priority = currentProject -> project_priority;
    if (currentProject -> prev)
    {
        currentProject -> prev -> next = currentProject -> next;
    }
    else
    {
        currentEmployee -> head = currentProject -> next;
    }
    if (currentProject ->next)
    {
        currentProject -> next -> prev = currentProject -> prev;
    }
    else
    {
        currentEmployee -> tail = currentProject -> prev;
    }
    if (currentEmployee -> head == nullptr)
    {
        if (currentEmployee == head)
        {
            head = currentEmployee -> down;
        }
        else
        {
            EmployeeNode* temporary = head;
            while (temporary -> down != currentEmployee)
            {
                temporary = temporary -> down;
            }
            temporary -> down = currentEmployee -> down;
        }
        delete currentEmployee;
    }
}
bool EmployeeProject2DLL::updateProjectPriority(string employeeName, string projectName, int& priority)
{
    EmployeeNode* currentEmployee = head;
    while (currentEmployee && (currentEmployee -> employee_name != employeeName))
    {
        currentEmployee = currentEmployee -> down;
    }
    ProjectNode* currentProject = currentEmployee -> head;
    while (currentProject) //iterates through the projects
    {
        if (currentProject -> project_priority == priority  && currentProject -> project_name == projectName)
        {
            cout << "The project priority is already the same as the new priority." << endl;
            return false;
        }
        else if (currentProject -> project_priority == priority && currentProject -> project_name != projectName)
        {
            cout << "The project priority has not been updated because there is another project with the same priority." << endl;
            return false;
        }
        else if (currentProject -> project_name == projectName && currentProject -> project_priority != priority) //the ones we want to be added or modified
        {
            int prevpriority = currentProject -> project_priority; //stores the previous priority
            currentProject -> project_priority = priority;
            if (priority < prevpriority)
            {
                while (currentProject -> prev && (currentProject -> prev -> project_priority > priority)) //goes to the left
                {
                    currentProject = currentProject -> prev;
                }
                if (currentProject->prev)
                {
                    currentProject->prev->next = currentProject;
                }
                else
                {
                    currentEmployee->head = currentProject;
                }
                if (currentProject -> next)
                {
                    currentProject->next->prev = currentProject;
                }
                else
                {
                    currentEmployee->tail = currentProject;
                }
                return true;
            }
            else
            {
                while (currentProject -> next && (currentProject -> next -> project_priority < priority)) //goes to the right
                {
                    currentProject = currentProject -> next;
                }
                if (currentProject->next)
                {
                    currentProject->next->prev = currentProject;
                }
                else
                {
                    currentEmployee->tail = currentProject;
                }
                if (currentProject -> prev)
                {
                    currentProject -> prev -> next = currentProject;
                }
                else
                {
                    currentEmployee -> head = currentProject;
                }
                return true;
            }
        }
        currentProject = currentProject -> next;
    }
    return true;
}
void EmployeeProject2DLL::printTheEntireList()
{
    if (!head)
    {
        cout << "The list is empty." << endl;
        return;
    }
    EmployeeNode* currentEmployee = head;
    while (currentEmployee) //iterates the list and then prints it out
    {
        cout << currentEmployee -> employee_name << ":";
        ProjectNode* currentProject = currentEmployee -> head;
        while (currentProject)
        {
            cout << " (" << currentProject -> project_name << ", " << currentProject -> project_priority << ")";
            currentProject = currentProject -> next;
        }
        cout << endl;
        currentEmployee = currentEmployee -> down;
    }
}
void EmployeeProject2DLL::printEmployeeProjects(string employeeName, int order)
{
    if (!head)
    {
        cout << "There are no employees in the list." << endl;
        return;
    }
    EmployeeNode* currentEmployee = head;
    while (currentEmployee && (currentEmployee -> employee_name != employeeName)) //checks for the employee we need.
    {
        currentEmployee = currentEmployee -> down;
    }
    if (!currentEmployee)
    {
        cout << "The employee is not in the list." << endl;
        return;
    }
    if (order == 1) //order if clauses
    {
        ProjectNode* currentProject = currentEmployee -> head;
        while (currentProject)
        {
            cout << "(" << currentProject -> project_name << ", " << currentProject -> project_priority << ")";
            currentProject = currentProject -> next;
            if (currentProject)
            {
                cout << " ";
            }
        }
    }
    else if (order == 0)
    {
        ProjectNode* currentProject = currentEmployee -> tail;
        while (currentProject)
        {
            cout << "(" << currentProject -> project_name << ", " << currentProject -> project_priority << ")";
            currentProject = currentProject -> prev;
            if (currentProject)
            {
                cout << " ";
            }
        }
    }
    else
    {
        cout << "Invalid number.";
    }
    cout << endl;
}
void EmployeeProject2DLL::undo(char selection, string employeeName, string projectName, int priority)
{
    if (selection == 'a') //cheks the character, if case
    {
        withdrawEmployeeFromProject(employeeName, projectName, priority);
        cout << "Undoing the assignment of a project." << endl;
    }
    else if (selection == 'w')
    {
        assignEmployeeToProject(employeeName, projectName, priority);
        cout << "Undoing the withdrawal of a project." << endl;
    }
    else if (selection == 'u')
    {
        updateProjectPriority(employeeName, projectName, priority);
        cout << "Undoing the update of a project priority." << endl;
    }
}
void EmployeeProject2DLL::clear() //clears out dynamically allocated memories
{
    while (head)
    {
        EmployeeNode* tempEmployee = head;
        head = head->down; //goes down for each employee, clears them out one by one.
        ProjectNode* tempProject = tempEmployee->head;
        while (tempProject)
        {
            ProjectNode* nextProject = tempProject->next;
            delete tempProject;
            tempProject = nextProject;
        }
        delete tempEmployee;
    }
}
/*
 #include "EmployeeProject2DLL.h"
 bool EmployeeProject2DLL::isEmployeeAssignedToProject(string employeeName,string projectName)
 {
     EmployeeNode* currentEmployee = head;
     while (currentEmployee)
     {
         if (currentEmployee -> employee_name == employeeName)
         {
             ProjectNode* currentProject = currentEmployee -> head;
             while (currentProject)
             {
                 if (currentProject -> project_name == projectName)
                 {
                     return true;
                 }
                 currentProject = currentProject -> next;
             }
         }
         currentEmployee = currentEmployee -> down;
     }
     return false;
 }
 bool EmployeeProject2DLL::assignEmployeeToProject(string employeeName, string projectName, int priority)
 {
     EmployeeNode* currentEmployee = head;
     while (currentEmployee)
     {
         if (currentEmployee ->employee_name == employeeName)
         {
             ProjectNode* currentProject = currentEmployee -> head;
             while (currentProject)
             {
                 if (currentProject -> project_priority == priority)
                 {
                     cout << "The project has not been added because there is another project with the same priority." << endl;
                     return false;
                 }
                 currentProject = currentProject -> next;
             }
             ProjectNode* newProject = new ProjectNode(projectName, priority);
             if (!currentEmployee -> head)
             {
                 currentEmployee -> head = newProject;
                 currentEmployee -> tail = newProject;
             }
             else
             {
                 currentProject = currentEmployee -> head;
                 while (currentProject && (currentProject -> project_priority < priority))
                 {
                     currentProject = currentProject -> next;
                 }
                 if (!currentProject)
                 {
                     currentEmployee -> tail -> next = newProject;
                     newProject -> prev = currentEmployee -> tail;
                     currentEmployee -> tail = newProject;
                 }
                 else if(!currentProject -> prev)
                 {
                     newProject -> next = currentEmployee -> head;
                     currentEmployee -> head -> prev = newProject;
                     currentEmployee -> head = newProject;
                 }
                 else
                 {
                     newProject -> next = currentProject;
                     newProject -> prev = currentProject -> prev;
                     currentProject -> prev -> next = newProject;
                     currentProject -> prev = newProject;
                 }
             }
             return true;
         }
         currentEmployee = currentEmployee -> down;
     }
     EmployeeNode* newEmployee = new EmployeeNode(employeeName);
     ProjectNode* newProject = new ProjectNode(projectName, priority);
     newEmployee -> head = newProject;
     newEmployee -> tail = newProject;
     EmployeeNode* prevEmployee = nullptr;
     currentEmployee = head;
     while (currentEmployee && (newEmployee -> employee_name > currentEmployee -> employee_name))
     {
         prevEmployee = currentEmployee;
         currentEmployee = currentEmployee -> down;
     }
     if (!prevEmployee)
     {
         newEmployee -> down = head;
         head = newEmployee;
     }
     else
     {
         newEmployee -> down = prevEmployee -> down;
         prevEmployee -> down = newEmployee;
     }
     return true;
 }
 void EmployeeProject2DLL::withdrawEmployeeFromProject(string employeeName, string projectName, int& priority)
 {
     EmployeeNode* currentEmployee = head;
     EmployeeNode* prevEmployee = nullptr;
     while (currentEmployee -> employee_name != employeeName)
     {
         prevEmployee = currentEmployee;
         currentEmployee = currentEmployee -> down;
     }
     ProjectNode* currentProject = currentEmployee -> head;
     while (currentProject -> project_name != projectName)
     {
         currentProject = currentProject -> next;
     }
     priority = currentProject -> project_priority;
     if (currentProject -> prev)
     {
         currentProject -> prev -> next = currentProject -> next;
     }
     else
     {
         currentEmployee -> head = currentProject -> next;
     }
     if (currentProject ->next)
     {
         currentProject -> next -> prev = currentProject -> prev;
     }
     else
     {
         currentEmployee -> tail = currentProject -> prev;
     }
     if (currentEmployee -> head == nullptr)
     {
         if (currentEmployee == head)
         {
             head = currentEmployee -> down;
         }
         else
         {
             EmployeeNode* temporary = head;
             while (temporary -> down != currentEmployee)
             {
                 temporary = temporary -> down;
             }
             temporary -> down = currentEmployee -> down;
         }
         delete currentEmployee;
     }
 }
 bool EmployeeProject2DLL::updateProjectPriority(string employeeName, string projectName, int& priority)
 {
     EmployeeNode* currentEmployee = head;
     while (currentEmployee -> employee_name != employeeName)
     {
         currentEmployee = currentEmployee -> down;
     }
     ProjectNode* currentProject = currentEmployee -> head;
     while (currentProject)
     {
         if (currentProject -> project_priority == priority  && currentProject -> project_name == projectName)
         {
             cout << "The project priority is already the same as the new priority." << endl;
             return false;
         }
         else if (currentProject -> project_priority == priority && currentProject -> project_name != projectName)
         {
             cout << "The project priority has not been updated because there is another project with the same priority." << endl;
             return false;
         }
         else
         {
             int prevpriority = currentProject -> project_priority;
             currentProject -> project_priority = priority;
             if (priority < prevpriority)
             {
                 while (currentProject -> prev -> project_priority > priority)
                 {
                     currentProject = currentProject -> prev;
                 }
                 if (currentProject->prev)
                 {
                     currentProject->prev->next = currentProject;
                 }
                 else
                 {
                     currentEmployee->head = currentProject;
                 }
                 if (!currentProject -> next)
                 {
                     currentEmployee -> tail = currentProject;
                 }
                 return true;
             }
             else
             {
                 while (currentProject -> next -> project_priority < priority)
                 {
                     currentProject = currentProject -> next;
                 }
                 if (currentProject->next)
                 {
                     currentProject->next->prev = currentProject;
                 }
                 else
                 {
                     currentEmployee->tail = currentProject;
                 }
                 if (!currentProject -> prev)
                 {
                     currentEmployee -> head = currentProject;
                 }
                 return true;
             }
         }
     }
     return true;
 }
 void EmployeeProject2DLL::printTheEntireList()
 {
     if (!head)
     {
         cout << "The list is empty." << endl;
         return;
     }
     EmployeeNode* currentEmployee = head;
     while (currentEmployee)
     {
         cout << currentEmployee -> employee_name << ":";
         ProjectNode* currentProject = currentEmployee -> head;
         while (currentProject)
         {
             cout << " (" << currentProject -> project_name << ", " << currentProject -> project_priority << ")";
             currentProject = currentProject -> next;
         }
         cout << endl;
         currentEmployee = currentEmployee -> down;
     }
 }
 void EmployeeProject2DLL::printEmployeeProjects(string employeeName, int order)
 {
     if (!head)
     {
         cout << "There are no employees in the list." << endl;
         return;
     }
     EmployeeNode* currentEmployee = head;
     while (currentEmployee && (currentEmployee -> employee_name != employeeName))
     {
         currentEmployee = currentEmployee -> down;
     }
     if (!currentEmployee)
     {
         cout << "The employee is not in the list." << endl;
         return;
     }
     if (order == 1)
     {
         ProjectNode* currentProject = currentEmployee -> head;
         while (currentProject)
         {
             cout << "(" << currentProject -> project_name << ", " << currentProject -> project_priority << ")";
             currentProject = currentProject -> next;
             if (currentProject)
             {
                 cout << " ";
             }
         }
     }
     else if (order == 0)
     {
         ProjectNode* currentProject = currentEmployee -> tail;
         while (currentProject)
         {
             cout << "(" << currentProject -> project_name << ", " << currentProject -> project_priority << ")";
             currentProject = currentProject -> prev;
         }
         if (currentProject)
         {
             cout << " ";
         }
     }
     else
     {
         cout << "Invalid number.";
     }
     cout << endl;
 }
 void EmployeeProject2DLL::undo(char selection, string employeeName, string projectName, int priority)
 {
     if (selection == 'a')
     {
         withdrawEmployeeFromProject(employeeName, projectName, priority);
         cout << "Undoing the assignment of a project." << endl;
     }
     else if (selection == 'w')
     {
         assignEmployeeToProject(employeeName, projectName, priority);
         cout << "Undoing the withdrawal of a project." << endl;
     }
     else if (selection == 'u')
     {
         updateProjectPriority(employeeName, projectName, priority);
         cout << "Undoing the update of a project priority." << endl;
     }
 }
 void EmployeeProject2DLL::clear()
 {
     while (head)
     {
         EmployeeNode* tempEmployee = head;
         head = head->down;
         // Deallocate memory for each project node within the employee node
         ProjectNode* tempProject = tempEmployee->head;
         while (tempProject)
         {
             ProjectNode* nextProject = tempProject->next;
             delete tempProject;
             tempProject = nextProject;
         }
         delete tempEmployee;
     }
 }
 */
/*
 else if (currentProject -> project_name == projectName && currentProject -> project_priority != priority)
 {
     int prevpriority = currentProject -> project_priority;
     currentProject -> project_priority = priority;
     if (priority < prevpriority)
     {
         while (currentProject -> prev && (currentProject -> prev -> project_priority > priority))
         {
             currentProject = currentProject -> prev;
         }
         if (currentProject->prev)
         {
             currentProject->prev->next = currentProject;
         }
         else
         {
             currentEmployee->head = currentProject;
         }
         if (!currentProject -> next)
         {
             currentEmployee -> tail = currentProject;
         }
         return true;
     }
     else
     {
         while (currentProject -> next && (currentProject -> next -> project_priority < priority))
         {
             currentProject = currentProject -> next;
         }
         if (currentProject->next)
         {
             currentProject->next->prev = currentProject;
         }
         else
         {
             currentEmployee->tail = currentProject;
         }
         if (!currentProject -> prev)
         {
             currentEmployee -> head = currentProject;
         }
         return true;
     }
 }
 */
/*
 bool EmployeeProject2DLL::updateProjectPriority(string employeeName, string projectName, int& priority)
 {
     EmployeeNode* currentEmployee = head;
     while (currentEmployee && (currentEmployee -> employee_name != employeeName))
     {
         currentEmployee = currentEmployee -> down;
     }
     ProjectNode* currentProject = currentEmployee -> head;
     while (currentProject)
     {
         if (currentProject -> project_priority == priority  && currentProject -> project_name == projectName)
         {
             cout << "The project priority is already the same as the new priority." << endl;
             return false;
         }
         else if (currentProject -> project_priority == priority && currentProject -> project_name != projectName)
         {
             cout << "The project priority has not been updated because there is another project with the same priority." << endl;
             return false;
         }
         else if (currentProject -> project_name == projectName && currentProject -> project_priority != priority)
         {
             int prevpriority = currentProject -> project_priority;
             currentProject -> project_priority = priority;
             if (priority < prevpriority)
             {
                 while (currentProject -> prev && (currentProject -> prev -> project_priority > priority))
                 {
                     currentProject = currentProject -> prev;
                 }
                 if (currentProject->prev)
                 {
                     currentProject->prev->next = currentProject;
                 }
                 else
                 {
                     currentEmployee->head = currentProject;
                 }
                 if (currentProject -> next)
                 {
                     currentProject->next->prev = currentProject;
                 }
                 else
                 {
                     currentEmployee->tail = currentProject;
                 }
                 return true;
             }
             else
             {
                 while (currentProject -> next && (currentProject -> next -> project_priority < priority))
                 {
                     currentProject = currentProject -> next;
                 }
                 if (currentProject->next)
                 {
                     currentProject->next->prev = currentProject;
                 }
                 else
                 {
                     currentEmployee->tail = currentProject;
                 }
                 if (currentProject -> prev)
                 {
                     currentProject -> prev -> next = currentProject;
                 }
                 else
                 {
                     currentEmployee -> head = currentProject;
                 }
                 return true;
             }
         }
     }
     return true;
 }
 */
/*
 if (currentProject -> next)
 {
     currentProject->next->prev = currentProject;
 }
 else
 {
     currentEmployee->tail = currentProject;
 }
 */
/*
 #include "EmployeeProject2DLL.h"
 bool EmployeeProject2DLL::isEmployeeAssignedToProject(string employeeName,string projectName)
 {
     EmployeeNode* currentEmployee = head;
     while (currentEmployee) //iterates thorugh each employee ancd checks if it is assigned to the given project name by comparing their names. Gives a boolean value accordingly.
     {
         if (currentEmployee -> employee_name == employeeName)
         {
             ProjectNode* currentProject = currentEmployee -> head;
             while (currentProject)
             {
                 if (currentProject -> project_name == projectName)
                 {
                     return true;
                 }
                 currentProject = currentProject -> next;
             }
         }
         currentEmployee = currentEmployee -> down;
     }
     return false;
 }
 bool EmployeeProject2DLL::assignEmployeeToProject(string employeeName, string projectName, int priority)
 {
     EmployeeNode* currentEmployee = head;
     while (currentEmployee) //just as usual iterates through every employee
     {
         if (currentEmployee ->employee_name == employeeName) //once it finds the same employee it enters into the function itself.
         {
             ProjectNode* currentProject = currentEmployee -> head;
             while (currentProject) //checks for the existence of a project with the same priority
             {
                 if (currentProject -> project_priority == priority)
                 {
                     cout << "The project has not been added because there is another project with the same priority." << endl;
                     return false;
                 }
                 currentProject = currentProject -> next;
             }
             ProjectNode* newProject = new ProjectNode(projectName, priority);
             if (!currentEmployee -> head) //if the list is empty it creates one.
             {
                 currentEmployee -> head = newProject;
                 currentEmployee -> tail = newProject;
             }
             else //if it isn't empty it inserts the new object alphabetically.
             {
                 currentProject = currentEmployee -> head;
                 while (currentProject && (currentProject -> project_priority < priority))
                 {
                     currentProject = currentProject -> next;
                 }
                 if (!currentProject)
                 {
                     currentEmployee -> tail -> next = newProject;
                     newProject -> prev = currentEmployee -> tail;
                     currentEmployee -> tail = newProject;
                 }
                 else if(!currentProject -> prev)
                 {
                     newProject -> next = currentEmployee -> head;
                     currentEmployee -> head -> prev = newProject;
                     currentEmployee -> head = newProject;
                 }
                 else
                 {
                     newProject -> next = currentProject;
                     newProject -> prev = currentProject -> prev;
                     currentProject -> prev -> next = newProject;
                     currentProject -> prev = newProject;
                 }
             }
             return true;
         }
         currentEmployee = currentEmployee -> down;
     }
     EmployeeNode* newEmployee = new EmployeeNode(employeeName);
     ProjectNode* newProject = new ProjectNode(projectName, priority);
     newEmployee -> head = newProject;
     newEmployee -> tail = newProject;
     EmployeeNode* prevEmployee = nullptr;
     currentEmployee = head;
     while (currentEmployee && (newEmployee -> employee_name > currentEmployee -> employee_name))
     {
         prevEmployee = currentEmployee;
         currentEmployee = currentEmployee -> down;
     }
     if (!prevEmployee)
     {
         newEmployee -> down = head;
         head = newEmployee;
     }
     else
     {
         newEmployee -> down = prevEmployee -> down;
         prevEmployee -> down = newEmployee;
     }
     return true;
 }
 void EmployeeProject2DLL::withdrawEmployeeFromProject(string employeeName, string projectName, int& priority)
 {
     EmployeeNode* currentEmployee = head;
     EmployeeNode* prevEmployee = nullptr;
     while (currentEmployee -> employee_name != employeeName)
     {
         prevEmployee = currentEmployee;
         currentEmployee = currentEmployee -> down;
     }
     ProjectNode* currentProject = currentEmployee -> head;
     while (currentProject -> project_name != projectName)
     {
         currentProject = currentProject -> next;
     }
     priority = currentProject -> project_priority;
     if (currentProject -> prev)
     {
         currentProject -> prev -> next = currentProject -> next;
     }
     else
     {
         currentEmployee -> head = currentProject -> next;
     }
     if (currentProject ->next)
     {
         currentProject -> next -> prev = currentProject -> prev;
     }
     else
     {
         currentEmployee -> tail = currentProject -> prev;
     }
     if (currentEmployee -> head == nullptr)
     {
         if (currentEmployee == head)
         {
             head = currentEmployee -> down;
         }
         else
         {
             EmployeeNode* temporary = head;
             while (temporary -> down != currentEmployee)
             {
                 temporary = temporary -> down;
             }
             temporary -> down = currentEmployee -> down;
         }
         delete currentEmployee;
     }
 }
 bool EmployeeProject2DLL::updateProjectPriority(string employeeName, string projectName, int& priority)
 {
     EmployeeNode* currentEmployee = head;
     while (currentEmployee && (currentEmployee -> employee_name != employeeName))
     {
         currentEmployee = currentEmployee -> down;
     }
     ProjectNode* currentProject = currentEmployee -> head;
     while (currentProject)
     {
         if (currentProject -> project_priority == priority  && currentProject -> project_name == projectName)
         {
             cout << "The project priority is already the same as the new priority." << endl;
             return false;
         }
         else if (currentProject -> project_priority == priority && currentProject -> project_name != projectName)
         {
             cout << "The project priority has not been updated because there is another project with the same priority." << endl;
             return false;
         }
         else if (currentProject -> project_name == projectName && currentProject -> project_priority != priority)
         {
             int prevpriority = currentProject -> project_priority;
             currentProject -> project_priority = priority;
             if (priority < prevpriority)
             {
                 while (currentProject -> prev && (currentProject -> prev -> project_priority > priority))
                 {
                     currentProject = currentProject -> prev;
                 }
                 if (currentProject->prev)
                 {
                     currentProject->prev->next = currentProject;
                 }
                 else
                 {
                     currentEmployee->head = currentProject;
                 }
                 if (currentProject -> next)
                 {
                     currentProject->next->prev = currentProject;
                 }
                 else
                 {
                     currentEmployee->tail = currentProject;
                 }
                 return true;
             }
             else
             {
                 while (currentProject -> next && (currentProject -> next -> project_priority < priority))
                 {
                     currentProject = currentProject -> next;
                 }
                 if (currentProject->next)
                 {
                     currentProject->next->prev = currentProject;
                 }
                 else
                 {
                     currentEmployee->tail = currentProject;
                 }
                 if (currentProject -> prev)
                 {
                     currentProject -> prev -> next = currentProject;
                 }
                 else
                 {
                     currentEmployee -> head = currentProject;
                 }
                 return true;
             }
         }
         currentProject = currentProject -> next;
     }
     return true;
 }
 void EmployeeProject2DLL::printTheEntireList()
 {
     if (!head)
     {
         cout << "The list is empty." << endl;
         return;
     }
     EmployeeNode* currentEmployee = head;
     while (currentEmployee)
     {
         cout << currentEmployee -> employee_name << ":";
         ProjectNode* currentProject = currentEmployee -> head;
         while (currentProject)
         {
             cout << " (" << currentProject -> project_name << ", " << currentProject -> project_priority << ")";
             currentProject = currentProject -> next;
         }
         cout << endl;
         currentEmployee = currentEmployee -> down;
     }
 }
 void EmployeeProject2DLL::printEmployeeProjects(string employeeName, int order)
 {
     if (!head)
     {
         cout << "There are no employees in the list." << endl;
         return;
     }
     EmployeeNode* currentEmployee = head;
     while (currentEmployee && (currentEmployee -> employee_name != employeeName))
     {
         currentEmployee = currentEmployee -> down;
     }
     if (!currentEmployee)
     {
         cout << "The employee is not in the list." << endl;
         return;
     }
     if (order == 1)
     {
         ProjectNode* currentProject = currentEmployee -> head;
         while (currentProject)
         {
             cout << "(" << currentProject -> project_name << ", " << currentProject -> project_priority << ")";
             currentProject = currentProject -> next;
             if (currentProject)
             {
                 cout << " ";
             }
         }
     }
     else if (order == 0)
     {
         ProjectNode* currentProject = currentEmployee -> tail;
         while (currentProject)
         {
             cout << "(" << currentProject -> project_name << ", " << currentProject -> project_priority << ")";
             currentProject = currentProject -> prev;
             if (currentProject)
             {
                 cout << " ";
             }
         }
     }
     else
     {
         cout << "Invalid number.";
     }
     cout << endl;
 }
 void EmployeeProject2DLL::undo(char selection, string employeeName, string projectName, int priority)
 {
     if (selection == 'a')
     {
         withdrawEmployeeFromProject(employeeName, projectName, priority);
         cout << "Undoing the assignment of a project." << endl;
     }
     else if (selection == 'w')
     {
         assignEmployeeToProject(employeeName, projectName, priority);
         cout << "Undoing the withdrawal of a project." << endl;
     }
     else if (selection == 'u')
     {
         updateProjectPriority(employeeName, projectName, priority);
         cout << "Undoing the update of a project priority." << endl;
     }
 }
 void EmployeeProject2DLL::clear()
 {
     while (head)
     {
         EmployeeNode* tempEmployee = head;
         head = head->down;
         // Deallocate memory for each project node within the employee node
         ProjectNode* tempProject = tempEmployee->head;
         while (tempProject)
         {
             ProjectNode* nextProject = tempProject->next;
             delete tempProject;
             tempProject = nextProject;
         }
         delete tempEmployee;
     }
 }



 */
