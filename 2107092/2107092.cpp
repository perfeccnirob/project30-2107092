#include <iostream>
using namespace std;

class PRISONER;
class GUARD;
class MANAGEMENT;
class PRISON;
class COURT;

class PRISONER
{
    int tag;
    string name;
    int sentence;
    string crime;
    friend MANAGEMENT;
    friend COURT;
public:
    PRISONER()
    {
        cout << "Prisoner Details: "<<endl;
        cout << "Tag: "<<endl;
        cin >> tag;
        cout << "Name: "<<endl;
        cin >> name;
        cout << "Crime: "<<endl;
        cin >> crime;
        cout << "Sentence in years: "<<endl;
        cin >> sentence;
        cout << endl<<endl;

    }
    friend void display(PRISONER &s);

    ~PRISONER()
    {
        cout << "Prisoner with tag: " << tag << " has been released."<<endl;
    }
};
void display(PRISONER &s){

        cout << s.tag;
        cout << "\tName: ";
        cout << s.name;
        cout << "\tCrime: ";
        cout << s.crime;
        cout << "\tSentence: ";
        cout << s.sentence;
        cout << " Years\n";


}

class GUARD
{
    int ID;
    string name;
    char block;
    friend MANAGEMENT;
public:
    GUARD()
    {
        cout << "ID: ";
        cin >> ID;
        cout << "Name: ";
        cin >> name;
        cout << "Block: ";
        cin >> block;
        cout << endl;

    }
    void display()
    {
        cout << "ID: ";
        cout << ID;
        cout << "\tName: ";
        cout << name;
        cout << "\tBlock: ";
        cout << block;
        cout << "\n" << endl;
    }
    ~GUARD()
    {
        cout << "Guard with ID: "<< ID << " has left."<<endl;
    }

};

class MANAGEMENT
{
    PRISONER *prisoner[100];
    GUARD *guard[50];



    int prisoner_kept;
    int prisoners_released;
    int guard_kept;
    int guard_released;
    friend COURT;


public:
    MANAGEMENT()
    {
        prisoner_kept = 0;
        prisoners_released = 0;
        guard_kept = 0;
        guard_released = 0;
    }

    void add_guard()
    {
        guard[guard_kept+guard_released] = new GUARD;
        guard_kept++;
    }
    void remove_guard(int id)
    {
        for(int i = 0; i < guard_kept+guard_released; i++)
        {
            if(guard[i] == NULL) continue;
            if(guard[i]->ID  == id)
            {
                delete guard[i];
                guard_kept--;
                guard_released++;
                guard[i] = NULL;
            }
        }
    }
     void add_prisoner()
    {
        prisoner[prisoner_kept+prisoners_released] = new PRISONER;
        prisoner_kept++;
    }

    void display_guard(int id)
    {
        for(int i = 0; i < guard_kept+guard_released; i++)
        {
            if(guard[i] == NULL) continue;
            if(guard[i]->ID  == id)
            {
                guard[i]->display();
                cout << endl;
                return;
            }
        }
        cout << "No Guard with ID " << id << " found\n" << endl;
    }

    void population()
    {
        cout << "Number of Guards: " << guard_kept << endl;
        cout << "Number of Prisoners: " << prisoner_kept << endl << endl;
    }
    void display_all()
    {
        cout << "Prisoner list: \n";
        for(int i = 0; i < prisoner_kept+prisoners_released; i++)
        {
            if(prisoner[i] == NULL) continue;
                display(*prisoner[i]);
        }
        cout << endl;
        cout << "Guard list: \n";
        for(int i = 0; i < guard_kept+guard_released; i++)
        {
            if(guard[i] == NULL) continue;
            guard[i]->display();
        }
        cout << endl;
    }

    void display_prisoner(int tag)
    {
        for(int i = 0; i < prisoner_kept+prisoners_released; i++)
        {
            if(prisoner[i] == NULL) continue;
            if(prisoner[i]->tag  == tag)
            {
                display(*prisoner[i]);
                cout << endl;
                return;
            }
        }
        cout << "No prisoner with tag " << tag << " found\n" << endl;
    }

};

class COURT
{
    MANAGEMENT *manager;
public:
    COURT()
    {
    }
    COURT(MANAGEMENT &a)
    {
        manager = &a;
    }
    void increase_sentence(int tag, int n)
    {
        for(int i = 0; i < manager->prisoner_kept+manager->prisoners_released; i++)
        {
            if(manager->prisoner[i] == NULL) continue;
            if(manager->prisoner[i]->tag  == tag)
            {
                manager->prisoner[i]->sentence +=n;
                cout << "Sentence increased by " << n << "years\n";
                cout << "New sentence: " << manager->prisoner[i]->sentence << " Years\n\n";
                break;
            }
        }
    }
    void decrease_sentence(int tag, int n)
    {
        for(int i = 0; i < manager->prisoner_kept+manager->prisoners_released; i++)
        {
            if(manager->prisoner[i] == NULL) continue;
            if(manager->prisoner[i]->tag  == tag)
            {
                manager->prisoner[i]->sentence -= n;
                if(manager->prisoner[i]->sentence <= 0)
                {
                    cout << "Prisoner has completed his sentence.\n";
                    release_prisoner(tag);
                }
                else
                {
                    cout << "Sentence decreased by " << n << "years\n";
                    cout << "New sentence: " << manager->prisoner[i]->sentence << "Years\n\n";
                }
            }
        }
    }
    void release_prisoner(int tag)
    {
        for(int i = 0; i < manager->prisoner_kept+manager->prisoners_released; i++)
        {
            if(manager->prisoner[i] == NULL) continue;
            if(manager->prisoner[i]->tag  == tag)
            {
                delete manager->prisoner[i];
                manager->prisoner_kept--;
                manager->prisoners_released++;
                manager->prisoner[i] = NULL;
            }
        }
    }
};

int main()
{
    int idenitity_number, change;
    string command;
    MANAGEMENT manager;
    COURT court(manager);
    while(true)
    {
        cout << "Enter Command: ";
        cin >> command;
        if(command == "END") {break;}
        else if(command == "add_prisoner") {


                manager.add_prisoner();}

        else if(command == "add_guard") {

                manager.add_guard();
        }
        else if(command == "population") {

                manager.population();}

        else if(command == "display_all") {

                manager.display_all();
        }
        else if(command == "increase_sentence")
        {
            cout << "Prisoner Tag: ";
            cin >> idenitity_number;
            cout << "Increment in sentence: ";
            cin >> change;
            court.increase_sentence(idenitity_number,change);
        }
        else if(command == "decrease_sentence")
        {
            cout << "Prisoner Tag: ";
            cin >> idenitity_number;
            cout << "Decrement in sentence: ";
            cin >> change;
            court.decrease_sentence(idenitity_number, change);
        }
        else if(command == "release_prisoner")
        {
            cout << "Prisoner Tag: ";
            cin >> idenitity_number;
            court.release_prisoner(idenitity_number);
        }
        else if(command == "remove_guard")
        {
            cout << "Guard ID: ";
            cin >> idenitity_number;
            manager.remove_guard(idenitity_number);
        }
        else if(command == "display_prisoner")
        {
            cout << "Prisoner Tag: ";
            cin >> idenitity_number;
            manager.display_prisoner(idenitity_number);
        }
        else if(command == "display_guard")
        {
            cout << "Guard ID: ";
            cin >> idenitity_number;
            manager.display_guard(idenitity_number);
        }
    }
    return 0;
}
