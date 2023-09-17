#include <iostream>
#include <vector>
#include <fstream>
using namespace std;


struct Stud {
    int id, age;
    string name;
    char sex;
    float mark[3];
}s;
vector<Stud> student;

void add(){
    cout<<"Name: ";
    cin>>s.name;
    cout<<"Sex: ";
    cin>>s.sex;
    cout<<"Age: ";
    cin>>s.age;
    cout<<"ID: ";
    cin>>s.id;
    for(int i=0; i<3; i++){
        cout<<"Mark "<<i+1<<": ";
        cin>>s.mark[i];
    }
    student.push_back(s);
};
void addtoRecord(){
    ofstream outfile("student.txt", ios::out | ios::app);

    if(outfile.is_open()){
        add();
        outfile << s.name <<"\t"<< s.sex << "\t"<< s.age <<"\t"<<  s.id << "\t"<< s.mark[0]<<"\t"<< s.mark[1]<<"\t"<< s.mark[2]<<"\n";
        outfile.close();
    } else{
        cout<<"Error in opening..";
        exit(1);
    };
}

void display(){
    ifstream infile("student.txt", ios::in | ios::app);
    cout<<endl<<"NAME"<<"\t"<<"SEX"<<"\t"<<"Age"<<"\t"<<"ID"<<"\t"<<"G1"<<"\t"<<"G2"<<"\t"<<"G3"<<endl;
    if(infile.is_open()){
        infile >> s.name >> s.sex >> s.age >>  s.id >> s.mark[0]>> s.mark[1]>> s.mark[2];
        while(!infile.eof()){
            cout << s.name <<"\t"<< s.sex <<"\t"<< s.age <<"\t"<<  s.id <<"\t"<< s.mark[0]<<"\t"<< s.mark[1]<<"\t"<< s.mark[2]<<endl<<endl;
            infile >> s.name >> s.sex >> s.age >>  s.id >> s.mark[0]>> s.mark[1]>> s.mark[2];
        }
        infile.close();
        }
    else {
        cout<<"Error in finding file.";

    }
}

void Modify(){
    fstream infile("student.txt", ios::app | ios::in);
    fstream outfile("temp.txt", ios::app | ios::out);
    edit:
    int id,choice;
    bool isfound = false;
    cout<<"Enter ID";
    cin>>id;
    if(infile.is_open() && outfile.is_open()){
        infile >> s.name >> s.sex >> s.age >>  s.id >> s.mark[0]>> s.mark[1]>> s.mark[2];
        while(!infile.eof()){
            if(s.id == id){
                isfound = true;
                cout<<"What do you want to modify? "<<endl;
                cout<<"1. ID\n 2. Name\n 3. Age\n 4. Sex\n 5. 1st mark\n 6. 2nd mark\n 7. 3rd mark\n 8. exit\n";
                cout<<"choice: ";
                cin>>choice;
                switch(choice){
                    case 1:
                        cout<<"ID: ";
                        cin>>s.id;
                        break;
                    case 2:
                        cout<<"Name: ";
                        cin>>s.name;
                        break;
                    case 3:
                        cout<<"Age: ";
                        cin>>s.age;
                        break;
                    case 4:
                        cout<<"Sex: ";
                        cin>>s.sex;
                        break;
                    case 5:
                        cout<<"1st mark: ";
                        cin>>s.mark[0];
                        break;
                    case 6:
                        cout<<"2nd mark: ";
                        cin>>s.mark[1];
                        break;
                    case 7:
                        cout<<"3rd mark: ";
                        cin>>s.mark[2];
                        break;
                    case 8:
                        break;
                }

            }
            outfile << s.name <<"\t"<< s.sex << "\t"<< s.age <<"\t"<<  s.id << "\t"<< s.mark[0]<<"\t"<< s.mark[1]<<"\t"<< s.mark[2]<<"\n";
            infile >> s.name >> s.sex >> s.age >>  s.id >> s.mark[0]>> s.mark[1]>> s.mark[2];

        }
        infile.close();
        outfile.close();
        }
    else {
        cout<<"Error in finding file.";

    }
    remove("student.txt");
    rename("temp.txt","student.txt");
    cout<<"Successfully modified"<<endl;
    if(isfound == false){
        char ch;
        cout<<"\nID not found \n";
        cout<<"Do you want to try again? [Y/n]: ";
        cin>>ch;
        if (ch == 'Y' || ch == 'y'){
            goto edit;
        }
    }
}

void Search(){
    fstream infile("student.txt", ios::app | ios::in);

    edit:
    int id,choice;
    bool isfound = false;
    cout<<"Enter ID";
    cin>>id;
    cout<<endl<<"NAME"<<"\t"<<"SEX"<<"\t"<<"Age"<<"\t"<<"ID"<<"\t"<<"G1"<<"\t"<<"G2"<<"\t"<<"G3"<<endl<<endl;
    if(infile.is_open() ){
        infile >> s.name >> s.sex >> s.age >>  s.id >> s.mark[0]>> s.mark[1]>> s.mark[2];
        while(!infile.eof()){
            if(s.id == id){
                isfound = true;
                cout << s.name <<"\t"<< s.sex <<"\t"<< s.age <<"\t"<<  s.id <<"\t"<< s.mark[0]<<"\t"<< s.mark[1]<<"\t"<< s.mark[2]<<endl;
            }
            infile >> s.name >> s.sex >> s.age >>  s.id >> s.mark[0]>> s.mark[1]>> s.mark[2];

        }
        infile.close();
        }
    else {
        cout<<"Error in finding file.";

    }
    
    if(isfound == false){
        char ch;
        cout<<"\nID not found \n";
        cout<<"Do you want to try again? [Y/n]: ";
        cin>>ch;
        if (ch == 'Y' || ch == 'y'){
            goto edit;
        }
    }
}
void start(){

    start:
    int ch;
    cout<<"\n__________Menu_________";
    cout<<"\nWhat do you want to do? ";
    cout<<"\n1. Add"
        <<"\n2. Display"
        <<"\n3. Modify"
        <<"\n4. Search"
        <<"\n5. Exit";
    cout<<"\n\nChoice: ";
    cin>>ch;
    if (ch == 1 || ch == 2 || ch == 3 || ch == 4 || ch == 5){
        switch (ch)
            {
            case 1:
                addtoRecord();
                goto start;
            case 2:
                display();
                goto start;
            case 3:
                Modify();
                goto start;
            case 4:
                Search();
                goto start;
            case 5:
                break;
            default:
                break;
            }
    } else{
        cout<<"No such option. Please try again.\n\n";
        goto start;
    }
}

int main(){
    start();
}