#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <map>
#include <string>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

int main(){
    
    string line;
    ifstream in("text.txt");
    ofstream out("output.txt");

    vector<string> urls;
    map<string, pair<set<int>, int>> words;

    // ----- Reading and assigning -----

    if(in.is_open()){
        int n = 0;
        while (!in.eof()){
            n++;

            getline(in, line);
            stringstream stream(line);

            string word;

            int num = 0;
            while(stream >> word){
                num++;
                transform(word.begin(), word.end(), word.begin(), ::tolower);


                if(word.find("https://") != string::npos || word.find("http://") != string::npos || word.find("www.") != string::npos || word.find(".lt") != string::npos || word.find(".com") != string::npos){
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
                if(!word.empty()){
                    words[word].first.insert(n);// Eilutės numeris
                    words[word].second++; // Pasikartojimų skaičius
                }
            }
        }
    } else cout << "Failas nerastas, patikrinkite ar tikrai egzistuoja text.txt failas.";

    // ----- Output -----

    out << "Surasti URL: " << std::endl;
        for (auto &elem : urls)
            out << elem << std::endl;
    out << endl;

                
    out << std::left << std::setw(18) << "Žodis" << std::setw(14)
         << "Pasikartoja" << std::setw(15) << "Šiose eilutėse" << "\n";
    out << "---------------------------------------------------------------------------------------";
    for (const auto& word : words)
        if (word.second.second >= 2) {
            out << "\n" << std::setw(18) << word.first // Žodis
                 << std::setw(14) << word.second.second; // Kiek kartų pasikartoja
            unsigned int i = 0;
            for (auto whichLine : word.second.first) {// Kurioje eilutėje
                if (i > 12) {
                    i = 0;
                    out << std::endl << std::left << std::setw(32) << " ";
                } else {
                    i++;
                }
                out << std::left << std::setw(4) << whichLine; // eilutė
            }
        }

    in.close();
    out.close();
}