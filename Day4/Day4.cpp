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
#include<set>
#include<stdio.h>

using namespace std;


bool readInputFile(std::string fileName, std::function<void (const std::string & )> callback)
{
    std::ifstream in(fileName.c_str());

    if(!in)
    {
        std::cerr << "Cannot open the File : "<< fileName << std::endl;
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
    vector<code> vc(v.size());
    int fact = 0;
    int last_index = 0;
    int vc_index = 0;
    
    // set for hcl (hair colors)
    set<string> s;
    s.insert("amb");
    s.insert("blu");
    s.insert("brn");
    s.insert("gry");
    s.insert("grn");
    s.insert("hzl");
    s.insert("oth");
    
    //cout << "inside parse()";

    for(int i = 0; i < v.size(); i++)
    {
        //cout << vc_index;
        vc[vc_index] = code();
        last_index = i;

        //cout << v[i] << "\n";

        while(!v[i].empty() && i < v.size())
        {
            stringstream ss;
            string word;
            ss.str(v[i]);
            while(ss >> word)
            {
                //cout << word << "\n";
                
                switch(mp[word.substr(0,3)])
                {
                    case 1 : {  fact = stoi(word.substr(5,10));
                                vc[vc_index].byr = (fact >= 1920 && fact <= 2002);
                                break;
                                }
                                
                    case 2:  {  fact = stoi(word.substr(5,10));
                                vc[vc_index].iyr = (fact >= 2010 && fact <= 2020);
                                break;
                                }

                    case 3:  {  fact = stoi(word.substr(5,10));
                                vc[vc_index].eyr = (fact >= 2020 && fact <= 2030);
                                break;
                                }

                    case 4:  {  if(word[word.size()-1] == 'm')
                                {
                                    // cm
                                fact = stoi(word.substr(5,word.size()-2));
                                vc[vc_index].hgt = (fact >= 150 && fact <= 193);
                                }
                                else
                                {
                                    fact = stoi(word.substr(5,word.size()-2));
                                    vc[vc_index].hgt = (fact >= 59 && fact <= 76);
                                }
                                break;
                                }

                    case 5:  {
                               string w = word.substr(5,9);
                               vc[vc_index].hcl = (s.find(w) != s.end());
                               break;
                               }

                    case 6:  {
                               string w = word.substr(5,9);
                               vc[vc_index].ecl = (s.find(w) != s.end());
                               break;
                               }

                    case 7:  {
                               fact = stoi(word.substr(5,word.size()-1));
                               vc[vc_index].hgt = (fact <= 999999999);
                               break;
                               }

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
    return x.byr && x.ecl && x.eyr &&x.hcl && x.hgt && x.iyr && x.pid;
}

int check(vector<code> vc)
{
    int ans = 0;

    for(code x : vc)
    {
        if(has(x)) 
        ans++;
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

    std::vector<string> vecOfStr;
    std::vector<code> vc;
    
    bool res = readInputFile("input.txt", [&](const std::string & str){vecOfStr.push_back(str);});

     vc = parse_file(vecOfStr, code_mp);
     cout << check(vc);

    return 0;
}