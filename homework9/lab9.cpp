#include <bits/stdc++.h>
#include <chrono>

using namespace std;

// compute longest prefix string for KMP algorithm
vector<int> computeLPS(string pattern){
    int m = pattern.size();
    vector<int> lps(m, 0);
    // i is index for text
    int i = 1;
    // prevLPS is index for pattern (present longest matching)
    int prevLPS = 0;

    while(i < m){
        if(pattern[prevLPS] == pattern[i]){
            lps[i] = ++prevLPS;
            i += 1;
        }else if(prevLPS == 0){
            lps[i] = 0;
            i += 1;
        }else{
            prevLPS = lps[prevLPS-1];
        }
    }

    return lps;
}

// Naive Matching algorithm
vector<pair<int, string>> naiveMatching(string pattern, string text, string mode){
    int n = text.size();
    int m = pattern.size();
    vector<pair<int, string>> res;
    int i; int j;

    for(i=0; i<n-m+1; i++){
        for (j=0; j<m; j++){
            // cout<<"i : "<<i<<" "<<"j :"<<j<<endl;
            if(pattern[j] != text[i+j]){
                break;
            }
        }
        if(j == m){
            // cout<<"found"<<endl;
            if(mode == "LR"){
                res.push_back(make_pair(i+1, "LR"));
            }else{
                int ori_pos = n-i;
                res.push_back(make_pair(ori_pos, "RL"));
            }
        }
    }

    return res;
}

// KMP Matching algorithm from https://www.youtube.com/watch?v=JoF0Z7nVSrA
vector<pair<int, string>> KMP(string pattern, string text, string mode){

    int n = text.size();
    int m = pattern.size();
    vector<int> lps = computeLPS(pattern);
    vector<pair<int, string>> res;
    int i = 0, j = 0;
    
    while(i < n){
        // cout<<"i : "<<i<<endl;
        // cout<<"j : "<<j<<endl;
        if(pattern[j] == text[i]){
            ++i, ++j;
        }else{
            if(j == 0){
                ++i;
            }else{
                j = lps[j-1];
            }
        }

        // if pattern is found, push it into result vector
        if(j == m){
            if(mode == "LR"){
                res.push_back(make_pair(i-m+1, "LR"));
            }else{
                int pos = i-m+1;
                int ori_pos = n-pos;
                res.push_back(make_pair(ori_pos+1, "RL"));
            }
        }
    }

    return res;
}

// search target value in vector
bool search(vector<string> setOfChar, string c){
    auto it = find(setOfChar.begin(), setOfChar.end(), c);
    if (it != setOfChar.end()) {
       return true;
    }
    return false;
}

// check if input contain any character in text which not in set of character
bool inputChecking(vector<string> setOfChar, string input){
    for(auto ch : input){
        // convert to string
        string s(1, ch);
        if(!search(setOfChar, s)){
            return false;
        }
    }
    return true;
}

void printVector(vector<int> v){
    for(auto i : v){
        cout<<i<<" ";
    }
    cout<<endl;
}

void printVector(vector<string> v){
    for(auto i : v){
        cout<<i<<" ";
    }
    cout<<endl;
}

void printVector(vector<pair<int, string>>& v){
    for(auto i : v){
        cout<<i.first<<" "<<i.second<<endl;
    }
}

// sort result with first value (index of matching position) by ascending
void sortVector(vector<pair<int, string>>& v){
    auto customComparator = [](const pair<int, string>& a, const pair<int, string>& b) {
        return a.first < b.first;
    };

    sort(v.begin(), v.end(), customComparator);
}

int main(){
    string setOfChar_input;
    vector<string> setOfChar;
    int m;
    int n;
    string pattern;
    string text;

    // input section
    getline(cin, setOfChar_input);
    cin>>m>>n;
    cin>>pattern;
    cin>>text;

    istringstream iss(setOfChar_input);
    string word;

    //split input set of characters with white space
    while (getline(iss, word, ' ')) {
         setOfChar.push_back(word);
    }

    // check correctness of pattern
    if(!inputChecking(setOfChar, pattern)){
        cout<<"The pattern is not match with set of characers"<<endl;
        return 1;
    }

    // check correctness of text input
    if(!inputChecking(setOfChar, text)){
        cout<<"The input text is not match with set of characers"<<endl;
        return 1;
    }
    
    // startTime of KMP
    auto startTime = std::chrono::high_resolution_clock::now();

    // -------KMP solution-------
    vector<int> lps = computeLPS(pattern);
    vector<pair<int, string>> res = KMP(pattern, text, "LR");
    reverse(text.begin(), text.end());
    vector<pair<int, string>> res_reverse = KMP(pattern, text, "RL");
    sortVector(res_reverse);

     // End time of KMP
    auto endTime = std::chrono::high_resolution_clock::now();
    auto elapsedTime = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime);

    //reverse text back
    reverse(text.begin(), text.end());

    // startTime of Naive
    auto startTime2 = std::chrono::high_resolution_clock::now();

    // -------Naive solution-------
    vector<pair<int, string>> res_naive = naiveMatching(pattern, text, "LR");
    reverse(text.begin(), text.end());
    vector<pair<int, string>> res_naive_reverse = naiveMatching(pattern, text, "RL");
    sortVector(res_naive_reverse);

     // End time of Naive
    auto endTime2 = std::chrono::high_resolution_clock::now();
    auto elapsedTime2 = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime2 - startTime2);

    cout<<"-------KMP solution-------"<<endl;
    printVector(lps);
    cout<<res.size()+res_reverse.size()<<endl;
    printVector(res);
    printVector(res_reverse);
    std::cout << "Elapsed time: " << elapsedTime.count() << " nanoseconds" << std::endl<<endl;
    
    cout<<"-------Naive solution-------"<<endl;
    printVector(lps);
    cout<<res_naive.size()+res_naive_reverse.size()<<endl;
    printVector(res_naive);
    printVector(res_naive_reverse);
    std::cout << "Elapsed time: " << elapsedTime2.count() << " nanoseconds" << std::endl;

}

/*
X Y
4 12
XYXY
XXYXYYXYXYXX

a b c
7 24
ababaca
abaabbabaaababacbababaca

A B C
6 35
AACCBA
AAACAACCAACCABCCAAAAACCBBAACCBAACCB

A B C D
4 46
ACDB
AAAAAACDBACDAADDABCDAACDBBCDDACCCBDCABDCACADAB
     6               22           37   41
6 LR
22 LR
37 RL
41 RL

A B C D
4 46
ACDB
AAAAAACDBACDBACDBACDBBCDDACCCBDCABDCACADABACCB
6 LR
10 LR
14 LR
18 LR
33 RL
37 RL
*/
