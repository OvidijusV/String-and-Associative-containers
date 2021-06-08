#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <string>
#include <iterator>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
    
    string line;
    ifstream in("text.txt");
    ofstream out("output.txt");

    map<string, int> occurences;
    map<string, vector<int>> crossRef;
    vector<string> urls;

    if(in.is_open()){
        int n = 0;
        while (!in.eof()){
            crossRef.clear();
            n++;

            getline(in, line);
            stringstream stream(line);

            string word;

            int num = 0;
            while(stream >> word){
                num++;
                transform(word.begin(), word.end(), word.begin(), ::tolower);


                if(word.find("https://") != string::npos || word.find("http://") != string::npos || word.find("www.") != string::npos){
                    if (word[word.length() - 1] == ',' || word[word.length() - 1] == '.')
                        word.resize(word.length() - 1);
                    urls.push_back(word);
                    word.clear();
                }

                for (int i = word.length() - 1; i > 0; i--){
                    if (isdigit(word[i]) || ispunct(word[i])){
                        word.resize(i);
                        i = word.length();
                    }
                }

                // Jei nerandam tokio žodžio priskiriam key 1, else jei randam padidinam vienu
                if(occurences.find(word) == occurences.end()){
                    occurences[word] = 1;
                }
                else{ 
                    occurences[word]++;
                }
                crossRef.insert({word, {0}});
                crossRef[word].push_back(num);
            }

            out << n << "-os eilutes zodziu numeriai: " << std::endl;
            for (auto cross : crossRef)
            {
                if (cross.second.size() > 1)
                    out << cross.first << " ";
                
                for (int i = 1; i < cross.second.size(); i++)
                    out << cross.second.at(i) << " ";

                out << std::endl;
            }
            out << std::endl;

        }
    } else cout << "Failas nerastas, patikrinkite ar tikrai egzistuoja text.txt failas.";

    out << "Žodžiai ir kiek kartų pasikartoja: " << endl;
    for (auto occ : occurences)
        out << occ.first << ": " << occ.second << endl;
    out << endl;

    out << "Surasti URL: " << std::endl;
        for (auto &elem : urls)
            out << elem << std::endl;

    in.close();
    out.close();
}