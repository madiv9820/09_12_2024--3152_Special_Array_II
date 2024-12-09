#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    vector<bool> isArraySpecial(vector<int>& nums, vector<vector<int>>& queries) {
        // Initialize a vector to store the results for each query
        vector<bool> answer;
        
        // Iterate through each query in the 'queries' vector
        for(const vector<int>& query: queries) {
            // Extract the 'start' and 'end' indices from the query
            const int &start = query[0], &end = query[1];
            
            // Assume the subarray is "special" initially
            bool special = true;
            
            // Loop through the subarray defined by the query, checking adjacent elements
            for(int index = start; index < end; ++index) {
                // Check if the current and next elements have the same parity:
                // (nums[index] & 1) gives 1 if nums[index] is odd, 0 if even.
                if((nums[index] & 1) == (nums[index + 1] & 1)) {
                    // If the parity of nums[index] and nums[index+1] is the same,
                    // the subarray is not "special."
                    special = false;
                    break; // Exit the loop early as we know the result for this query
                }
            }
            
            // Add the result (true if special, false otherwise) to the answer vector
            answer.emplace_back(special);
        }

        // Return the vector containing results for all queries
        return answer;
    }
};

int main() {
    vector<int> nums = {4,3,1,6}; vector<vector<int>> queries = {{0,2},{2,3}};
    Solution sol;

    vector<bool> answer = sol.isArraySpecial(nums, queries);
    for(const bool& ans: answer)
        cout << ((ans) ? "true":"false") << " ";
    cout << endl;
}