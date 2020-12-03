/**
* @author: ranaaditya
*/

#include<iostream>
#include<vector>
#include<functional>
#include<fstream>
#include<string>
#include<map>

using namespace std;


bool readInputFile(std::string fileName, std::function<void (const std::string & )> callback)
{
    std::ifstream in(fileName.c_str());

    if(!in)
    {
        std::cerr << "Cannot open the File : "<<fileName<<std::endl;
        return false;
    }

    std::string str;
    
    while (std::getline(in, str))
    {
        callback(str);
    }

    in.close();
    
    return true;
}

int main() {
    map<int, int> mp;

    std::vector<std::string> vecOfStr;
    
    bool res = readInputFile("input.txt", [&](const std::string & str){vecOfStr.push_back(str);});

    if(res) {
        for(auto x : vecOfStr)
        mp[stoi(x)] = stoi(x);
    }

    for(auto x : mp) {
        if(mp.find(2020 - x.first) != mp.end())
        {
        cout << x.first * (2020 - x.first);
        break;
        }
    }

    return 0;
}