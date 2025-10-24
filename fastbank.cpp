#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <string>
#include <ctime>
#include <vector>
using namespace std;

string formatWithCommas(double value) {
    // Convert double to string with fixed 2 decimals
    stringstream ss;
    ss << fixed << setprecision(2) << value;
    string s = ss.str();

    // Find decimal point
    size_t dotPos = s.find('.');

    // Integer part and fractional part
    string intPart = (dotPos == string::npos) ? s : s.substr(0, dotPos);
    string fracPart = (dotPos == string::npos) ? "" : s.substr(dotPos);

    // Insert commas in integer part
    int insertPosition = intPart.length() - 3;
    while (insertPosition > 0) {
        intPart.insert(insertPosition, ",");
        insertPosition -= 3;
    }

    return intPart + fracPart;
}
void savetime(){
    ofstream saves("data/time.csv", ios::app);
    time_t now_c = time(0);
    saves <<ctime(&now_c);
    saves.close();
}
void updatetime(vector <string> time){
    ofstream saves("data/time.csv",ios::out);
    for (int i = 0; i < time.size(); i++)
    {
        saves <<time[i] <<endl;
    }
}
void updatemoney(vector <string> money){
    ofstream saves("data/money.csv",ios::out);
    for (int i = 0; i < money.size(); i++)
    {
        saves << money[i] <<endl;
    }
    
}
void updatemoneyin(vector <string> moneyin){
    ofstream saves("data/moneyinbank.csv",ios::out);
    for (int i = 0; i < moneyin.size(); i++)
    {
        saves << moneyin[i] <<endl;
    }
    
}
void readtime(vector <string>& t){
    ifstream read("data/time.csv");
    string line,ti;
    t.clear();
    while (getline(read,line))
    {
        stringstream ss(line);
        getline(ss,ti);
        t.push_back(ti);
    }read.close();
    
}
void savemoney(double money,int option){
ofstream save("data/money.csv",ios::app);
if (option ==1)
{
    save << "+" << formatWithCommas(money) <<endl;
    save.close();
}else
save << "-"<<formatWithCommas(money) <<endl;
}
void readmoney(vector <string>& money){
    ifstream read("data/money.csv");
    string line,mon;
    money.clear();
    while(getline(read,line)){
        stringstream ss(line);
        getline(ss,mon);
        money.push_back(mon);
    }
}
void save(double money,string curr){
    ofstream save("data/save.csv", ios::out);
    save << money << "," <<curr;
    save.close();
}
void saveinbank(double moneyinbank){
ofstream save("data/moneyinbank.csv",ios::app);
save << formatWithCommas(moneyinbank) << endl;
save.close();
}
void readmoneyinbank(vector <string>& moneyin){
    ifstream read("data/moneyinbank.csv");
    string line,mon;
    while (getline(read,line))
    {
        stringstream ss(line);
        getline(ss,mon);
        moneyin.push_back(mon);
    }
}
void savestat(vector <string> time,vector<string> money,vector <string> moneyin){
    ofstream save("data/statement.csv", ios::out);
   readtime(time); readmoney(money); readmoneyinbank(moneyin);
   string mix;
   for (int i = 0; i < money.size(); i++)
   {
    mix=time[i] +" | "+money[i] + " | " + moneyin[i];
    save << mix <<endl;
   }save.close();
}
void load(){
    ifstream read("data/statement.csv");
    string line,statement;
    while (getline(read,line))
    {
        stringstream ss(line);
        getline(ss,statement,'\n');
        cout << statement << endl;
    }read.close();
}
double removeCommasAndConvertToDouble(const string& str) {
    string result;
    for (char c : str) {
        if (c != ',') {
            result += c;
        }
    }
    double doubleResult = 0.0;
    try {
        doubleResult = stod(result);
    } catch (...) {
        doubleResult = 0.0; 
    }
    return doubleResult;
}

void read(double& money,string& curr,bool& exist){
    ifstream read("data/save.csv");
    string line, strmoney;
    while (getline(read, line))
    {
        stringstream ss(line);
        getline(ss, strmoney,',');
        getline(ss,curr);
        exist=true;
    }
    read.close();
    money = removeCommasAndConvertToDouble(strmoney);
}
int main() {
    double moneyinbank, mon;
    int option = 0;
    bool exist=false;
    string p="n",curr;
    vector <string> time,money,moneyin;
    read(moneyinbank,curr,exist);
    if (!exist)
    {
        while (p != "y")
        {
            cout << "Choose the Currency you are using\n";
            cin >> curr;
            cout << "Are you sure you'd like to proceed? y/n\n";
            cin>>p;
        }save(moneyinbank,curr);
    }
    
    cout <<"You have " << formatWithCommas(moneyinbank) << " "<< curr <<" in your account\n";
    while (option != 7) {
    readmoney(money);
    readtime(time);
    savestat(time,money,moneyin);
        cout << "Would you like to:\n0-Change Currency\n1-Add\n2-Remove\n3-Statement\n4-Delete a specific Number\n5-Reset Statement\n6-Delete all Data\n7-Exit\n";
        cin >> option;
        if (option ==0)
        {
            while (p != "y")
        {
            cout << "Choose the Currency you are using\n";
            cin >> curr;
            cout << "Are you sure you'd like to proceed? y/n\n";
            cin>>p;
        }save(moneyinbank,curr);
        }else if (option == 1) {
            cout << "How much would you like to add: ";
            cin >> mon;
            savetime();
            savemoney(mon,option);
            moneyinbank += mon;
            save(moneyinbank,curr);
            cout << "Your current Balance is: " << formatWithCommas(moneyinbank) << " " << curr <<"\n";
            saveinbank(moneyinbank);
        }
        else if (option == 2) {
            cout << "How much would you like to withdraw: ";
            cin >> mon;
            if (moneyinbank-mon >= 0)
            {
            savetime();
            moneyinbank -= mon;
            savemoney(mon,option);
            save(moneyinbank,curr);
            saveinbank(moneyinbank);
            cout << "Your current Balance is: " << formatWithCommas(moneyinbank) <<" " << curr <<"\n";
        }else
        cout << "Insufficient Balance\n";
        }else if (option==3)
        {
            for (int i = 0; i < 50; i++)
            {
                cout<<"*";
            }cout << endl;
            load();
            cout<<"Your total is: " << formatWithCommas(moneyinbank)<< " " << curr <<"\n";
            for (int i = 0; i < 50; i++)
            {
                cout <<"*";
            }cout<<endl;
            
        }else if (option == 4)
        {
            if (money.empty()) {
                cout << "Amount is empty try again\n";
            } else {
            cout << "Enter the amount you want to delete: "; cin >>mon;
            for (int i = money.size()-1; i > -1; i--)
            {
                if (formatWithCommas(mon) == money[i].substr(1))
                {
                    if (money[i].substr(0,1)=="+")
                    {
                        option=1;
                        moneyinbank-=mon;
                        save(moneyinbank,curr);
                    }else if (money[i].substr(0,1)=="-")
                    {
                        option=2;
                        moneyinbank+=mon;
                        save(moneyinbank,curr);
                    }
                    money.erase(money.begin()+i);
                    time.erase(time.begin()+i);
                    moneyin.erase(moneyin.begin()+i);
                    updatetime(time);
                    updatemoney(money);
                    updatemoneyin(moneyin);
                    break;
                }else if (i == 0)
                {
                    cout << "Amount Not Found try again\n";
                    break;
                }
            }
            

        }
    }else if (option==5)
    {
        cout << "Are you sure? y/n\n";cin >>p;
        if (p=="y")
        {
            ofstream moneys("data/money.csv",ios::out);
            moneys.close();
            ofstream times("data/time.csv",ios::out);
            times.close();
            ofstream moneyins("data/moneyinbank", ios::out);
            moneyins.close();
            savemoney(moneyinbank,1);
            savetime();
            readmoney(money);
            readtime(time);
            savestat(time,money,moneyin);
            saveinbank(moneyinbank);
            readmoneyinbank(moneyin);
        }
        
    }
    
        else if (option==6)
        {
            cout<<"Are you sure? y/n\n"; cin >> p;
            if (p =="y")
            {
                ofstream money("data/money.csv" , ios::out);
                money.close();
                ofstream time("data/time.csv",ios::out);
                time.close();
                ofstream save("data/save.csv", ios::out);
                save.close();
                ofstream statement("data/statement.csv", ios::out);
                ofstream moneyin("data/moneyinbank.csv",ios::out);
                moneyin.close();
                statement.close();
                moneyinbank=0;
                cout << "All data has been cleared\n";
            }
        }
        
        else if (option == 7) {
            cout << "Exiting. Thank you!\n";
        }
        else {
            cout << "Invalid option. Please try again.\n";
        }
    }
}
