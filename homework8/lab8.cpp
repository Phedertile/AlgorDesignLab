#include <bits/stdc++.h>

using namespace std;

// vector<pair<int, int>> checkSeq(vector<int> seq){
//     vector<pair<int, int>> listOfError;

//     int half = seq.size() / 2;
    
//     for (int i = 0; i < half; i++) {
//         int start = i;
//         int end = seq.size() - i - 1;
//         if ((seq[start] + seq[end]) %2 != 0) {
//             continue;
//         }

//         int x = (seq[start] + seq[end]) / 2;
//         // cout<<"x : "<<x<<endl;

//         for (int j = start+1; j < end; j++) {
//             if(seq[j] == x){
//                 listOfError.push_back(make_pair(seq[start], seq[end]));
//                 break;
//             }
//         }
//     }
    
//     return listOfError;
// }

bool validate(vector<int> seq, vector<tuple<int, int, int>> triplets)
{
    for (auto triplet : triplets)
    {
        int n1 = get<0>(triplet);
        int n2 = get<1>(triplet);
        int n3 = get<2>(triplet);

        int index_n1 = find(seq.begin(), seq.end(), n1) - seq.begin();
        int index_n2 = find(seq.begin(), seq.end(), n2) - seq.begin();
        int index_n3 = find(seq.begin(), seq.end(), n3) - seq.begin();

        // Check n2 is not in between n1 and n3
        if (index_n1 < index_n2 && index_n2 < index_n3)
        {
            // cout << n2 << " is in between " << n1 << " and " << n3 << endl;
            return false;
        }
        else if (index_n1 > index_n2 && index_n2 > index_n3)
        {
            // cout << n2 << " is in between " << n1 << " and " << n3 << endl;
            return false;
        }
    }

    return true;
}

vector<tuple<int, int, int>> generateTriplets(vector<int> seq)
{
    vector<tuple<int, int, int>> triplets;

    int n = seq.size() - 1;

    for (int i = 1; i < n; i++)
    {

        int n1_index = i - 1;
        int n3_index = i + 1;

        while (n1_index >= 0 && n3_index <= n)
        {
            int n1 = seq[n1_index];
            int n3 = seq[n3_index];

            triplets.push_back(make_tuple(n1, seq[i], n3));

            n1_index--;
            n3_index++;
        }
    }

    return triplets;
}

void printVector(vector<int> v){
    for (int num : v) {
        cout << num << " ";
    }
    cout<<endl;
}

void swap(vector<int> &seq, int i, int j){
    int temp = seq[i];
    seq[i] = seq[j];
    seq[j] = temp;
}

vector<int> merge(vector<int> v1, vector<int> v2){
    v2.insert(v2.begin(), v1.begin(), v1.end());
    return v2;
}

vector<int> divideSol(vector<int> seq){
    if (seq.size() == 2){
        return seq;
    }

    if (seq.size() == 3) {
        swap(seq, 1, 2);
        return seq;
    }
    

    vector<int> first_half;
    vector<int> second_half;
    
    
    for(int i=0; i<seq.size(); i++){
        if (i % 2 == 0) {
            first_half.push_back(seq[i]);
        }else{
            second_half.push_back(seq[i]);
        }
        
    }
    // cout<<"size : "<<seq.size()<<endl;

    vector<int> sorted_first_half = divideSol(first_half);
    vector<int> sorted_second_half = divideSol(second_half);
    vector<int> merged_seq = merge(sorted_first_half, sorted_second_half);

    // printVector(sorted_first_half);
    // printVector(sorted_second_half);
    // printVector(merged_seq);

    return merged_seq;

}

void backtrack(vector<vector<int>>& res, vector<int>& nums, vector<int>& permutation, vector<bool>& used){
    if(permutation.size() == nums.size() ) { // goal is reach
        res.push_back(permutation);
        return;
    }

    for (int i = 0; i < nums.size(); i++ ){
        if (!used[i]){ // valid choice
        // make a choice
            used[i] = true;
            permutation.push_back(nums[i]);
            backtrack(res, nums, permutation, used);
            used[i] = false;
            permutation.pop_back();
        }
    }

}

vector<vector<int>> permute(vector<int>& nums){
        vector<vector<int>> res;
        vector<bool> used(nums.size(),false);
        vector<int> permutation;
        backtrack(res, nums, permutation, used);
        return res;
}

void permutationSol(vector<int> seq,  vector<tuple<int, int, int>> triplets){
    vector<vector<int>> perms = permute(seq);
    // cout<<perms.size()<<endl;
    for(auto perm : perms){
        if(validate(perm, triplets)){
            printVector(perm);
        }
    }
}
int main() {
    int n = 10000;
    vector<int> sequence(n);

    for (int i = 0; i < n; i++) {
        sequence[i] = i;
    }

    //0, 4, 2, 1, 5, 3
    //0, 4, 2, 5, 1, 3
    // vector<int> seq = {0, 4, 2, 1, 5, 3};

    // divide and conquer approach answer
    vector<int> result = divideSol(sequence);

    // wrong triplets for checking the validation of new sequence
    vector<tuple<int, int, int>> triplets = generateTriplets(sequence);
    
    cout<<"Sequence : "<<endl;
    // printVector(sequence);

    /* 
    Comment another line to print the wanting algorithm 
    */

    cout<<"New sequence : "<<endl;

    /*Permutation Solution*/
    permutationSol(sequence, triplets);

    /*Divide and Conquer Solution*/
    printVector(result);

    /* 
    uncomment to check if the new sequence is correct or not
    */
   
    // if(validate(result, triplets)){
    //     cout<<"Correct"<<endl;
    // }else{
    //     cout<<"Wrong"<<endl;
    // }
    // vector<pair<int, int>> errors = checkSeq(sequence);
    // if (errors.size() == 0){
    //     cout<<"Correct"<<endl;
    // }else{
    //     cout<<"Wrong at :"<<endl;
    //     for (pair<int, int> p : errors){
    //         cout<<p.first<<" "<<p.second<<endl;
    // }

    // }
    
   

    return 0;
}

