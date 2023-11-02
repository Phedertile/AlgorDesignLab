#include <iostream>
#include <vector>
using namespace std;

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

void printVector(vector<int> v){
    for (int num : v) {
        cout << num << " ";
    }
    cout<<endl;
}

int main(){
    vector<int> seq = {0, 1, 2, 3, 4};
    vector<vector<int>> perms = permute(seq);
    cout<<perms.size()<<endl;
    for(auto perm : perms){
        printVector(perm);
    }

}