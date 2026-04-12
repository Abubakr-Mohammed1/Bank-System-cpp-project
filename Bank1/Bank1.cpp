#include <iostream>
#include <string>
#include <cstdlib>
#include <iomanip>
#include <vector>
#include <cctype>
#include <fstream>

using namespace std;
const string ClientFileName = "Clients.txt";

void ShowMainMenue();

struct stClient
{
    string AccountNumber;
    string PINcode;
    string Name;
    string Phone;
    double AccountBalance;
    bool MarkToDeleteClient = false;
};

vector<string> SplitString(string S1, string Delim)
{

    vector<string> vString;

    short pos = 0;
    string sWord;

    while ((pos = S1.find(Delim)) != std::string::npos)
    {
        sWord = S1.substr(0, pos);
        if (sWord != "")
        {
            vString.push_back(sWord);
        }

        S1.erase(0, pos + Delim.length());
    }

    if (S1 != "")
    {
        vString.push_back(S1);
    }

    return vString;
}

string ReadClientAccountNumber()
{
    string AccountNumber = "";

    //cout << "\nEnter AccountNumber? ";
    cin >> AccountNumber;

    return AccountNumber;
}

stClient ReadNewClient(string AccountNumber)
{
    stClient Client;

    Client.AccountNumber = AccountNumber;

    cout << "Enter PinCode? ";
    getline(cin >> ws, Client.PINcode);

    cout << "Enter Name? ";
    getline(cin, Client.Name);

    cout << "Enter Phone? ";
    getline(cin, Client.Phone);

    cout << "Enter Account Balance? ";
    cin >> Client.AccountBalance;
    cin.ignore();

    return Client;
}

bool FindClientByAccountNumber(string AccountNumber, vector <stClient> vClients, stClient& Client)
{

    for (stClient C : vClients)
    {
        if (C.AccountNumber == AccountNumber)
        {
            Client = C;
            return true;
        }
    }
    return false;
}

string ConvertRecordToLine(stClient Client, string Seperator = "///")
{
    string stClientRecord = "";

    stClientRecord += Client.AccountNumber + Seperator;
    stClientRecord += Client.PINcode + Seperator;
    stClientRecord += Client.Name + Seperator;
    stClientRecord += Client.Phone + Seperator;
    stClientRecord += to_string(Client.AccountBalance);

    return stClientRecord;
}

void SaveClientsDataToFile(string FileName, vector <stClient> vClients)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out);

    string Line;

    if (MyFile.is_open())
    {
        for (stClient C : vClients)
        {
            if (C.MarkToDeleteClient == false)
            {
                Line = ConvertRecordToLine(C);
                MyFile << Line << endl;
            }
        }

        MyFile.close();
    }

}

stClient ChangeClientRecord(string AccountNumber)
{
    stClient Client;

    Client.AccountNumber = AccountNumber;

    cout << "\n\nEnter PinCode? ";
    getline(cin >> ws, Client.PINcode);

    cout << "Enter Name? ";
    getline(cin, Client.Name);

    cout << "Enter Phone? ";
    getline(cin, Client.Phone);

    cout << "Enter Account Balance? ";
    cin >> Client.AccountBalance;
    cin.ignore();

    return Client;
}

stClient ConvertLineToRecord(string Line, string Seperator = "///")
{
    stClient Client;
    vector<string> vClientData;

    vClientData = SplitString(Line, Seperator);

    Client.AccountNumber = vClientData[0];
    Client.PINcode = vClientData[1];
    Client.Name = vClientData[2];
    Client.Phone = vClientData[3];
    Client.AccountBalance = stod(vClientData[4]);

    return Client;

}

vector <stClient> LoadDataFormFileToVector(string FileName)
{

    vector <stClient> vClients;

    fstream MyFile;
    MyFile.open(FileName, ios::in);

    if (MyFile.is_open())
    {
        string Line;
        stClient Client;

        while (getline(MyFile, Line))
        {
            Client = ConvertLineToRecord(Line);

            vClients.push_back(Client);
        }

        MyFile.close();
    }

    return vClients;

}

void PrintClientRecord(stClient Client)
{
    cout << "| " << left << setw(15) << Client.AccountNumber;
    cout << "| " << left << setw(10) << Client.PINcode;
    cout << "| " << left << setw(40) << Client.Name;
    cout << "| " << left << setw(12) << Client.Phone;
    cout << "| " << left << setw(12) << Client.AccountBalance;
}

void PrintAllClientsData()
{
    vector <stClient> vClients = LoadDataFormFileToVector(ClientFileName);

    cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).";
    cout << "\n___________________________________________________________________________________________________\n" << endl;

    cout << "| " << left << setw(15) << "Account Number";
    cout << "| " << left << setw(10) << "Pin Code";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Phone";
    cout << "| " << left << setw(12) << "Balance";
    cout << "\n___________________________________________________________________________________________________\n" << endl;

    for (stClient& Client : vClients)
    {
        PrintClientRecord(Client);
        cout << endl;
    }

    cout << "\n___________________________________________________________________________________________________\n" << endl;

}

void PrintClientDetail(stClient Client)
{
    cout << "\n\nThe following are the client details: \n\n";

    cout << "Account Number       : " << Client.AccountNumber;
    cout << "\nPin Code           : " << Client.PINcode;
    cout << "\nName               : " << Client.Name;
    cout << "\nPhone              : " << Client.Phone;
    cout << "\nAccount Balance    : " << Client.AccountBalance;
}

bool MarkClientToDeleteByAccountNumber(string AccountNumber, vector <stClient>& vClients)
{
    for (stClient& C : vClients)
    {
        if (C.AccountNumber == AccountNumber)
        {
            C.MarkToDeleteClient = true;
            return true;
        }
    }
    return false;
}

void AddClientToFile(string FileName, string stDataLine)
{
    fstream MyFile;

    MyFile.open(FileName, ios::out | ios::app);

    if (MyFile.is_open())
    {
        MyFile << stDataLine << endl;

        MyFile.close();
    }

}

void AddNewClient()
{
    string AccountNumber;
    vector <stClient> vClients = LoadDataFormFileToVector(ClientFileName);
    stClient Client;

    cout << "\nEnter Account Number? ";

    do 
    {
        AccountNumber = ReadClientAccountNumber();

        if (FindClientByAccountNumber(AccountNumber, vClients, Client))
        {
            cout << "\nClient with [" << AccountNumber << "] already exists, Enter another Account Number? ";
        }


    } while (FindClientByAccountNumber(AccountNumber, vClients, Client));

    Client = ReadNewClient(AccountNumber);
    AddClientToFile(ClientFileName, ConvertRecordToLine(Client));

}

void AddClients()
{
    char AddMore = 'Y';

    do
    {

        cout << "Adding New Client:\n\n";

        AddNewClient();
        cout << "\nClient Added Successfully, do you want to add more clients? ";
        cin >> AddMore;
        cin.ignore();


    } while (toupper(AddMore) == 'Y');
}

bool DeleteClientByAccountNumber(string AccountNumber, vector <stClient>& vClients)
{
    stClient Client;

    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
    {
        PrintClientDetail(Client);

        char Answer = 'y';
        cout << "\n\nDo you want to delete this client? y/n ? ";
        cin >> Answer;

        if (Answer == 'Y' || Answer == 'y')
        {
            MarkClientToDeleteByAccountNumber(AccountNumber, vClients);
            SaveClientsDataToFile(ClientFileName, vClients);

            vClients = LoadDataFormFileToVector(ClientFileName);

            cout << "\n\nClient Deleted Successfully.";
            return true;
        }
    }
    else
    {
        cout << "\n\nClient with Account Number (" << AccountNumber << ") Not Found!";
        return false;
    }
}

bool UpdateClientByAccountNumber(string AccountNumber, vector <stClient>& vClients)
{
    stClient Client;

    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
    {
        PrintClientDetail(Client);

        char Answer = 'y';
        cout << "\n\nAre you sure you want delete this client? y/n ? ";
        cin >> Answer;

        if (Answer == 'Y' || Answer == 'y')
        {
            for (stClient& C : vClients)
            {
                if (C.AccountNumber == AccountNumber)
                {
                    C = ChangeClientRecord(AccountNumber);
                    break;
                }
            }

            SaveClientsDataToFile(ClientFileName, vClients);

            cout << "\n\nClient Updated Successfully.";
            return true;
        }
    }
    else
    {
        cout << "\n\nClient with Account Number (" << AccountNumber << ") Not Found!";
        return false;
    }
}

void GoBackToMainMenue()
{
    cout << "\n\nPress any key to go back to main menue...";
    system("pause>0");
    ShowMainMenue();
}

enum enMainMenueOptions { eShowClientList = 1, eAddNewClient = 2, eDeleteClient = 3,
    eUpdateClient = 4, eFindClient = 5, eExit = 6
};

void ShowingClientsList()
{
    system("cls");
    PrintAllClientsData();
    GoBackToMainMenue();
}

void ShowAddNewClientScreen()
{
    system("cls");
    cout << "\n___________________________________\n";
    cout << "\tAdd New Clients Screen";
    cout << "\n___________________________________\n\n";

    AddClients();

    GoBackToMainMenue();
}

short ReadMainMenueOption()
{
    short Choose = 0;
    cout << "Choose what do you want to do? [1 to 6]? ";
    cin >> Choose;
    return Choose;
}

void ShowMainMenue()
{
    system("cls");
    cout << "==========================================\n";
    cout << "\t\tMain Menue Screen\n";
    cout << "==========================================\n";
    cout << "\t[1] Show Client List.\n";
    cout << "\t[2] Add New Client.\n";
    cout << "\t[3] Delete Client.\n";
    cout << "\t[4] Update Client.\n";
    cout << "\t[5] Find Client.\n";
    cout << "\t[6] Exit.\n";
    cout << "==========================================\n\n";

    //PerformMainMenueOption((enMainMenueOptions)ReadMainMenueOption());

}

int main()
{
    ShowingClientsList();
    ShowAddNewClientScreen();

    system("pause>0");

    return 0;
}