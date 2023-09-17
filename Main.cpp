// C++ code to implement an ATM and
// its basic functions
#include <fstream>
#include <iostream>
#include <limits>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <cstdlib> 

#include <mariadb/mysql.h>
using namespace std;


struct connection_details {
    const char * server, *user, *password, *database;
};
MYSQL* mysql_connection_setup(struct connection_details mysql_details){
    MYSQL *connection = mysql_init(NULL);
    if(!mysql_real_connect(connection,mysql_details.server,mysql_details.user,mysql_details.password,mysql_details.database,0,NULL,0)){
        cout<<"Connection Error: "<<mysql_error(connection)<<endl;
    }
    return connection;
}

MYSQL_RES* mysql_perform_query(MYSQL *connection,const char* sql_query){
    if(mysql_query(connection,sql_query)){
        cout<<"mysql query error: "<<mysql_error(connection)<<endl;
    }
    return mysql_use_result(connection);
}

MYSQL *con;
MYSQL_RES *res;
MYSQL_ROW row;


// Class ATM to get user details
class atm {
private:
    char username[30];
    int password;
    int balance;

public:
    char* usernames(void)
    {
        // Return username
        return username;
    }

    int passwords(void)
    {
        // Return the password
        return password;
    }

    // Function to get the data
    void getData(MYSQL *con)
    {
        cin.ignore(
            numeric_limits<streamsize>::max(),
            '\n');
        cout << "\nEnter username:";

        cin.getline(username, 30);
        cout << "\nEnter 4-digit "
             << "password:";

        cin >> password;
        cin.ignore(
            numeric_limits<streamsize>::max(),
            '\n');
        cout << "\nEnter initial"
             << " balance:";

        cin >> balance;
        cin.ignore(
            numeric_limits<streamsize>::max(),
            '\n');
        string querystring = "insert into user (name,password,balance) values (\""+ string(username) + "\","+ to_string(password)+","+ to_string(balance)+ ");";
        const char *query = querystring.c_str();
        mysql_perform_query(con, query);
    }

    // Member Functions
    int adduser(MYSQL *con);
    int viewallusers();
    int deleteuser(char*,MYSQL *con);
    void updateuserasdeposit(char*,MYSQL*);
    void updateuseraswithdraw(char*,MYSQL*);
    int searchspecificuser(char*, int,MYSQL*);
    int searchallusertodisplay(char*,MYSQL*);
};

// Function to implement functionality of ATM User
void atmUser(MYSQL *con)
{
    atm a;

    char uname[30];
    int pass, ch, ch1, ch2, found = 0;

mainmenu:

    system("clear");
    cout << "\nWelcome to Vision ATM";
    cout << "\nLogin as :\n"<<
            "1. Admin\n2."
         << " User\n3. "
            "Exit\nChoose one : ";
    cin >> ch;

    switch (ch) {
    case 1:
    rerun:
        system("clear");
        cout << "\nEnter details to"
             << " login as Admin\n";
        cout << "\nEnter password:";
        cin >> pass;
        if (pass == 1234) {
        admin:
            system("clear");
            cout << "\nWelcome to"
                 << " Admin Menu";
            cout << "\n1. Add User\n2."
                 << " Delete User\n3. "
                    "View All User\n4. "
                 << "Exit";
            cout << "\nSelect one : ";
            cin >> ch1;
            switch (ch1) {
            case 1:
                a.adduser(con);
                goto admin;

            case 2:
                cout << "\nEnter the Username to be deleted : ";
                
                cin>>uname;
                a.deleteuser(uname,con);
                goto admin;

            case 3:
                a.viewallusers();
                cin.get();
                goto admin;

            case 4:
                break;
            }
        }
        else {
            cout << "\nDetails are "<< "incorrect ! Please"
                    " try again";
            cin.get();
            goto rerun;
        }
        goto mainmenu;

    case 2:
        system("clear");
        cout << "\n Enter details to"
             << " login as User\n";

        cin.ignore(
            numeric_limits<streamsize>::max(),
            '\n');
        cout << "Enter username:";
        cin.getline(uname, 30);
        cout << "\nEnter password:";

        cin >> pass;
        found = a.searchspecificuser(
            uname, pass,con);

        if (found) {
        user:
            system("clear");
            cout << "\nWelcome "
                 << uname;
            cout << "\nWelcome to"
                 << " User Menu";
            cout << "\n1. Deposit\n2."
                 << " Withdraw\n3. View "
                    "Account\n4. "
                 << "Exit\nEnter your choice:";
            cin >> ch2;

            switch (ch2) {
            case 1:
                a.updateuserasdeposit(uname,con);
                goto user;
            case 2:
                a.updateuseraswithdraw(uname,con);
                goto user;
            case 3:
                a.searchallusertodisplay(uname,con);
                cin.get();
                goto user;
            case 4:
                cout << "Thank you";
                break;
            }
        }
        else {
            cout << "\nNo account found"
                 << " with this username "
                    ":(\n\nPlease try again to continue. \n";
        }
        goto mainmenu;

    case 3:
        cout << "\nThank you for "
             << "banking with "
             << "Vision";
        cin.get();
        break;
    }
}
// Function to add user
int atm::adduser(MYSQL *con)
{
    getData(con);
    return 0;
}

// View Users
int atm::viewallusers()
{
    res = mysql_perform_query(con, "select * from user;");

    std::cout << ("Database Output:\n") << std::endl;
        cout <<" | "<<"id" << " | " << "name" << " | " << "password" << " | " << "balance"<< " | " << endl;
    while ((row = mysql_fetch_row(res)) != NULL){
        cout <<" | "<<row[0] << " | " << row[1] << " | " << row[2] << " | " << row[3] << " | " << endl;
    }

    
    return 0;
}

// Function to delete the user
int atm::deleteuser(char* uname,MYSQL *con)
{
    string qstring = "delete from user where name = \""+ string(uname) + "\";";
    const char *query = qstring.c_str();
    mysql_perform_query(con, query);
    atm a;
    return 0;
}

// Function to update user by
// depositing money
void atm::updateuserasdeposit(char* uname,MYSQL *con)
{   
    int b;
    cout<<"Enter ammount"<<endl;
    cin>>b;
    string qstring = "update user set balance = balance + "+ to_string(b) + " where name = \"" + string(uname) + "\";";
    const char *query = qstring.c_str();
    mysql_perform_query(con, query);
}
void atm::updateuseraswithdraw(char* uname,MYSQL *con)
{   
    int b;
    cout<<"Enter ammount"<<endl;
    cin>>b;
    string qstring = "update user set balance = balance - "+ to_string(b) + " where name = \"" + string(uname) + "\";";
    cout<<qstring;
    const char *query = qstring.c_str();
    mysql_perform_query(con, query);
}

int atm::searchspecificuser(char* uname, int pass,MYSQL *con){

    string qstring = "select * from user where name = \""+ string(uname) +"\" and password = "+to_string(pass)+";";
    const char *query = qstring.c_str();
    res = mysql_perform_query(con, query);
    if((row = mysql_fetch_row(res)) != NULL){
        while ((row = mysql_fetch_row(res)) != NULL){ }
        return 1;   
    }
    
    return 0;
}
int atm::searchallusertodisplay(char* uname,MYSQL *con){
    string qstring = "select * from user where name = \""+string(uname)+"\";";
    cout<<qstring;
    const char *query = qstring.c_str();
    res = mysql_perform_query(con, query);
    cout <<" | "<<"id" << " | " << "name" << " | " << "password" << " | " << "balance"<< " | " << endl;

    while ((row = mysql_fetch_row(res)) != NULL){
        cout << row[0] << " | " << row[1] << " | " << row[2] << " | " << row[3] << " | "  << endl;
        // while ((row = mysql_fetch_row(res)) != NULL){ }
    }

    return 0;
}
// Driver Code
int main()
{

    struct connection_details mysqlD;
    mysqlD.server = "localhost";  
    mysqlD.user = "root";
    mysqlD.password = "4286"; 
    mysqlD.database = "atm";	

    con = mysql_connection_setup(mysqlD);

    atmUser(con);

// g++ Main.cpp -o output -L/usr/include/mariadb/mysql -lmariadbclient && ./output

    return 0;
}
