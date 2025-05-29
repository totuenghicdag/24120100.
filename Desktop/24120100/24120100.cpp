#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cmath>
using namespace std;
struct Company {
    string name;
    string profit_tax;
    string address;
};
struct HashTable {
    vector<Company> table;
    int tableSize = 2000;
    HashTable() {
        table.resize(tableSize);
    }
};

vector<Company> readCompanyList(string file_name) {
    ifstream file(file_name);
    vector<Company> companyList;
    if (!file.is_open()) {
        cout << "Khong mo duoc file " << file_name << endl;
        return companyList;
    }
    Company c;
    while (getline(file, c.name, '|') && getline(file, c.profit_tax, '|') && getline(file, c.address)) {
        if (!c.name.empty() && !c.profit_tax.empty() && !c.address.empty()) {
            companyList.push_back(c);
        }
    }
    file.close();
    return companyList;
}

vector<Company> readCompanyListFromInput(string file_name) {
    ifstream file(file_name);
    vector<Company> companyList;
    if (!file.is_open()) {
        cout << "Khong mo duoc file " << file_name << endl;
        return companyList;
    }
    while (!file.eof()) {
        Company c;
        getline(file, c.name);
        if (c.name != "")
            companyList.push_back(c);
    }
    file.close();
    return companyList;
}
long long hashString(string company_name) {
    int length = company_name.length();
    if (length == 0) {
        cout << "Error" << endl;
        return 0;
    }
    string lastofline;
    if (length <= 20) {
        lastofline = company_name.substr(0);
    }
    else {
        lastofline = company_name.substr(length - 20);
    }
    long long hash = 0;
    long long powerofp = 1;
    for (int i = 0; i < lastofline.length(); ++i) {
        char c = lastofline[i];
        hash = (hash + (c * powerofp) % 2000) % 2000;
        powerofp = (powerofp * 31) % 2000;
    }
    return hash;
}
int linearProbe(int hashIndex, int i) {
    return (hashIndex + i) % 2000;
}
void insert(HashTable* hash_table, Company company) {
    long long hashIndex = hashString(company.name);
    int i = 0;
    while (true) {
        int index = linearProbe(hashIndex, i);
        if (hash_table->table[index].name == "") {
            hash_table->table[index] = company;
            break;
        }
        else if (hash_table->table[index].name == company.name) {
            hash_table->table[index] = company;
            break;
        }
        i++;
        if (i >= hash_table->tableSize) {
            cout << "Error" << endl;
            break;
        }
    }
}
Company* search(HashTable* hash_table, string company_name) {
    long long hashIndex = hashString(company_name);
    int i = 0;
    while (true) {
        int index = linearProbe(hashIndex, i);
        if (hash_table->table[index].name == company_name) {
            return &hash_table->table[index];
        }
        if (hash_table->table[index].name == "") {
            break;
        }
        i++;
        if (i >= hash_table->tableSize) {
            break;
        }
    }
    return nullptr;
}
HashTable* createHashTable(vector<Company> list_company) {
    HashTable* hashTable = new HashTable();
    for (int i = 0; i < list_company.size(); ++i) {
        Company company = list_company[i];
        insert(hashTable, company);
    }
    return hashTable;
}
int main() {
    vector<Company> companies = readCompanyList("MST.txt");
    HashTable* hashTable = createHashTable(companies);
    vector<Company> searchcompanies = readCompanyListFromInput("input.txt");
    ofstream op("output.txt");
    if (!op.is_open()) {
        cout << "Khong the mo file";
        return -1;
    }
    else {
        for (int i = 0; i < searchcompanies.size(); ++i) {
            string nameToSearch = searchcompanies[i].name;
            Company* foundCompany = search(hashTable, nameToSearch);
            if (foundCompany != NULL) {
                cout << foundCompany->name << " " << foundCompany->profit_tax << " " << foundCompany->address << endl;
                op << foundCompany->name << " " << foundCompany->profit_tax << " " << foundCompany->address << endl;
            }
            else {
                cout << "Khong tim thay " << nameToSearch << endl;
            }
        }
        op.close();
    }
    return 0;
}