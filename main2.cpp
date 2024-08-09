//written by Alp Demir Ekinci 31935
#include <iostream>
#include <string>
#include <fstream>
using namespace std;
struct NodeLike
{
    string subject;
    string object;
    NodeLike *next;
};
struct NodeTaken
{
    string name;
    NodeTaken *next;
};
bool isintaken (NodeTaken* head, string name) //checks if the name is already in the taken list.
{
    NodeTaken* temp = head;
    while (temp != nullptr)
    {
        if (temp -> name == name)
        {
            return true; //name is already in the list.
        }
        temp = temp -> next;
    }
    return false; //name is not in the list.
}
bool redundant (NodeLike* head, string subject, string object) //checks if the subject - object combination is already in the likes list or not.
{
    NodeLike* temp = head;
    while (temp != nullptr)
    {
        if (temp -> subject == subject && temp -> object == object)
        {
            return true; //there is already this node
        }
        temp = temp -> next;
    }
    return false;
}
void deletion(NodeLike* tobedeleted, NodeLike*& head) //deletes the nodes that contain any one of the subject or object. (after there is a match)
{
    NodeLike* current = head;
    NodeLike* prev = nullptr;
    while (current != nullptr) {
        if (current == tobedeleted || current -> subject == tobedeleted -> subject || current -> object == tobedeleted -> object||current -> subject == tobedeleted -> object||current -> object == tobedeleted -> subject) //check if it should be deleted
        {
            if (prev == nullptr) //if the node is the head.
            {
                head = current -> next;
                current = head;
            }
            else
            {
                prev->next = current -> next;
                current = prev -> next;
            }
        }
        else
        {
            prev = current;
            current = current -> next;
        }
    }
}
void addintotaken (NodeTaken* &takenhead, string name) //adds the subject and object that got matched into the taken list.
{
    NodeTaken* newtaken = new NodeTaken;
    newtaken -> name = name;
    newtaken -> next = nullptr;
    if (takenhead == nullptr)
    {
        takenhead = newtaken;
    }
    else if (name < takenhead -> name && takenhead != nullptr)
    {
        newtaken -> next = takenhead;
        takenhead = newtaken;
    }
    else
    {
        NodeTaken* current = takenhead;
        while (current -> next != nullptr && current -> next -> name < name)
        {
            current = current -> next;
        }
        newtaken -> next = current -> next;
        current -> next = newtaken;
    }
}
void matchandadd(NodeLike*& likeshead, NodeTaken*& takenhead, string subject, string object, bool& printitout) //general function. Matches the subject and object.
{
    NodeLike* likestemp = likeshead;
    printitout = true;
    while (likestemp != nullptr)
    {
        if (likestemp->subject == object && likestemp->object == subject)
        {
            cout << "Match found: " << subject << " likes " << object << " and " << object << " likes " << subject << "." << endl;
            addintotaken (takenhead, subject);
            cout << "Added to taken list: " << subject << endl;
            addintotaken (takenhead, object);
            cout << "Added to taken list: " << object << endl;
            deletion (likestemp, likeshead);
            cout << "Any node that has " << subject << " or " << object << " or both in it is removed from the likes list." << endl;
            printitout = false;
        }
        likestemp = likestemp->next;
    }
}
void printlinkedlists (NodeLike* likeshead, NodeTaken* takenhead) //does as its name suggests :D
{
    cout << "Likes list:";
    while (likeshead != nullptr)
    {
        cout << " (" << likeshead -> subject << ", " << likeshead -> object << ")";
        likeshead = likeshead -> next;
    }
    cout << endl;
    cout << "Taken list:";
    while (takenhead != nullptr)
    {
        cout << " " << takenhead -> name;
        takenhead = takenhead -> next;
    }
    cout << endl << endl;
}
int main()
{
    string filename;
    cout << "Please enter the file name:" << endl;
    cin >> filename;
    ifstream inputfile(filename);
    while (!inputfile.is_open()) //classic file check.
    {
        inputfile.clear();
        cout << "Could not open the file. Please enter a valid file name:" <<endl;
        cin >> filename;
        inputfile.open(filename);
    }
    string subject;
    string object;
    string likes;
    bool printitout = true;
    NodeLike* likeshead = nullptr;
    NodeTaken* takenhead = nullptr;
    int counter = 0;
    while (inputfile >> subject >> likes >> object) //reads the file line by line.
    {
        counter++;
        cout << "Read line number (" << counter << "): " << subject << " likes " << object << endl;
        if (isintaken(takenhead, subject)||isintaken(takenhead, object)) //does what the cout says in if.
        {
            cout << "Either " << subject << " or " << object << " or both is/are already taken, so the like relation is not added." << endl;
            printlinkedlists(likeshead, takenhead);
        }
        else if (redundant(likeshead, subject, object) == true) //does what cout says in else if.
        {
            cout << subject << " likes " << object << " relation already exists in the likes list, so it is not added to it." << endl;
            printlinkedlists(likeshead, takenhead);
        }
        else
        {
            NodeLike* newNode = new NodeLike;
            newNode -> subject = subject;
            newNode -> object = object;
            newNode -> next = nullptr;
            if (likeshead == nullptr)
            {
                likeshead = newNode;
            }
            else
            {
                NodeLike* temp = likeshead;
                NodeLike* lastSubjectNode = nullptr;
                while (temp != nullptr)
                {
                    if (temp -> subject == subject)
                    {
                        lastSubjectNode = temp; //store the last occurrence of the subject
                    }
                    temp = temp->next;
                }

                if (lastSubjectNode != nullptr) //if a node has been found
                {
                    newNode -> next = lastSubjectNode -> next;
                    lastSubjectNode -> next = newNode;
                }
                else
                {
                    temp = likeshead;
                    while (temp -> next != nullptr)
                    {
                        temp = temp -> next;
                    }
                    temp -> next = newNode;
                }
            }
            matchandadd(likeshead, takenhead, subject, object, printitout);
            if (printitout == true) //this is to handle the arrangement of the print.
            {
                cout << subject << " likes " << object << " relation has been added to the likes list." << endl;
            }
            printlinkedlists(likeshead, takenhead);
        }
    }
    inputfile.close();
    NodeLike* currentdeletelike = likeshead; //from here to the end is to delete the remaining nodes to clear memory space.
    while (currentdeletelike != nullptr)
    {
        NodeLike* nextdeletelike = currentdeletelike -> next;
        delete currentdeletelike;
        currentdeletelike = nextdeletelike;
    }
    likeshead = nullptr;
    delete likeshead;
    NodeTaken* currentdeletetaken = takenhead;
    while (currentdeletetaken != nullptr)
    {
        NodeTaken* nextdeletetaken = currentdeletetaken -> next;
        delete currentdeletetaken;
        currentdeletetaken = nextdeletetaken;
    }
    takenhead = nullptr;
    delete takenhead;
    cout << "Lists are deleted and the program ends successfully." << endl;
    return 0;
}
