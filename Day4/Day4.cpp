/**
* @author: ranaaditya
*/

#include<iostream>
#include<vector>
#include<functional>
#include<fstream>
#include<sstream>
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

struct code {
    bool byr = false;
    bool iyr = false;
    bool eyr = false;
    bool hgt = false;
    bool hcl = false;
    bool ecl = false;
    bool pid = false;
    bool cid = true;
};

void flush_code(code c) {
    c.byr = c.iyr = c.eyr = c.hgt = c.hcl = c.ecl = c.pid  = false;
    c.cid = 1;
}

vector<code>  parse_file(vector<string> v, map<string, int> mp) {
    vector<code> vc;
    int last_index = 0;
    int vc_index = 0;
    cout << "inside parse()";

    for(int i = 0; i < v.size(); i++)
    {
        cout << vc_index;
        vc[vc_index] = code();
        last_index = i;

        while(!v[i].empty() && i != v.size()-1)
        {
            stringstream ss;
            string word;
            ss.str(v[i]);
            while(ss >> word)
            {
                cout << word << "\t";
                switch(mp[word.substr(0,2)])
                {
                    case 1 : {vc[vc_index].byr = true; break;}
                    case 2:  {vc[vc_index].iyr = true; break;}
                    case 3:  {vc[vc_index].eyr = true; break;}
                    case 4:  {vc[vc_index].hgt = true; break;}
                    case 5:  {vc[vc_index].hcl = true; break;}
                    case 6:  {vc[vc_index].ecl = true; break;}
                    case 7:  {vc[vc_index].pid = true; break;}
                    case 8:  {vc[vc_index].cid = true; break;}
                    default : break;
                }
            }
            i++;
        }
        vc_index++;
    }
    return vc;
}
bool has(code x)
{
    return x.byr and x.ecl and x.eyr and  x.hcl and x.hgt and x.iyr and x.pid;
}

int check(vector<code> vc)
{
    int ans = 0;

    for(code x : vc)
    {
        if(has(x)) ans++;
    }
    return ans;
}

int main() {
    map<string, int> code_mp;
    code_mp["byr"] = 1;
    code_mp["iyr"] = 2;
    code_mp["eyr"] = 3;
    code_mp["hgt"] = 4;
    code_mp["hcl"] = 5;
    code_mp["ecl"] = 6;
    code_mp["pid"] = 7;
    code_mp["cid"] = 8;

    std::vector<std::string> vecOfStr;
    std::vector<code> vc;
    
    bool res = readInputFile("input.txt", [&](const std::string & str){vecOfStr.push_back(str);});

     vc = parse_file(vecOfStr, code_mp);
     cout << check(vc);

    return 0;
}
