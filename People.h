#include <iostream>
#include <string>
#include <exception>

using namespace std;


// gives const value names to the array indexes
enum PeopleInfo
{
    phoneNumber,
    name,
    address,
    email
};


struct People
{
    string info[4];

    People(string p = "", string n = "", string a = "", string e = "")
    {
        info[phoneNumber] = p;
        info[name] = n;
        info[address] = a;
        info[email] = e;
    }
    People(const People &p)
    {
        info[phoneNumber] = p.info[phoneNumber];
        info[name] = p.info[name];
        info[address] = p.info[address];
        info[email] = p.info[email];
    }

    friend ostream &operator<<(ostream &output, const People &p)
    {
        output << "-------------------------------------" << endl;
        output << "Phone Number: " << p.info[phoneNumber] << endl;
        output << "Name: " << p.info[name] << endl;
        output << "Address: " << p.info[address] << endl;
        output << "Email: " << p.info[email] << endl;
        return output;
    }
    friend istream &operator>>(istream &input, People &p)
    {

        do
        {
            cout << "Enter phone number (4 digits only): ";
            input >> p.info[phoneNumber];
            if (p.info[phoneNumber].length() != 4)
            {
                cout << "The phone number you entered should have the length 4" << endl;
            }

        } while (p.info[phoneNumber].length() != 4);
        
        cout << "Enter name: ";
        input.ignore();
        getline(input, p.info[name]);
        cout << "Enter address: ";
        input.ignore();
        getline(input, p.info[address]);
        cout << "Enter email address if any (if there isn't any, press enter twice): "; 
        input.ignore();
        getline(input, p.info[email]);
        // this line allows user to enter nothing as input for the email if they do not want to
        if (p.info[email].empty()) {
            return input;
        }
    
        return input;
    }
};