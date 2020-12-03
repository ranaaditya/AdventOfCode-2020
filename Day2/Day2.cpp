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
    int valid_passwd = 0;
    map<char, int> mp;

    std::vector<std::string> vecOfStr;
    
    bool res = readInputFile("input.txt", [&](const std::string & str){vecOfStr.push_back(str);});
    
    if(res) {
        for(auto x : vecOfStr) {
            int index  = 0;
            int low, high, temp, len = x.size()-1;

            for(; x[index] != '-'; index++);
            
            temp = index;

            low = stoi(x.substr(0, index));

            for(; x[index] != ' '; index++);

            high = stoi(x.substr(temp+1, index-1));

            char find = x[index+1];

            x = x.substr(index+4, len);

            //cout << low << " " << high << " " << find <<  " " << x << endl;


            for( int i = 0; i < x.size(); i++)
            {
                if(mp.find(find) != mp.end())
                mp[x[i]]++;

                else mp[x[i]] = 1;
            }
            
            if(mp[find] <= high && mp[find] >= low)
            {
            //cout <<low << " " << high << " " << x << " " << find << " " <<  mp[find] << endl;
            valid_passwd++;
            }
            mp.clear();
        }
    }

    cout << valid_passwd;
    return 0;
}