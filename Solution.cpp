#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    vector<bool> isArraySpecial(vector<int>& nums, vector<vector<int>>& queries) {
        // Initialize a vector to store the results for each query
        vector<bool> answer;

        // Get the size of the nums array
        int n = nums.size();

        // Create a vector to store indices where adjacent elements have the same parity
        vector<int> violation_indices;

        // Iterate through the nums array to find all violations (adjacent elements with the same parity)
        for(int index = 0; index < n-1; ++index)
            if((nums[index] & 1) == (nums[index+1] & 1))  // Check if nums[index] and nums[index + 1] have the same parity
                violation_indices.emplace_back(index);  // Store the index of the violation

        // Iterate through each query in the 'queries' vector
        for(const vector<int>& query: queries) {
            // Extract the 'start' and 'end' indices from the current query
            const int &start = query[0], &end = query[1];
            
            // Assume the subarray is "special" initially (no violations)
            bool special = true;

            // Initialize binary search range
            int left = 0, right = violation_indices.size() - 1;

            // Perform binary search to find if there's any violation within the range [start, end-1]
            while(left <= right) {
                // Find the middle index
                int mid = (left + right) / 2;
                
                // Check if the current violation falls within the query range [start, end-1]
                if(start <= violation_indices[mid] && violation_indices[mid] <= end-1) {
                    // If a violation is found, the subarray is not special
                    special = false;
                    break;  // Exit the loop as we found a violation
                }
                else if(violation_indices[mid] < start) {
                    // If the violation is before the start of the range, adjust the left pointer
                    left = mid + 1;
                }
                else {
                    // If the violation is after the end of the range, adjust the right pointer
                    right = mid - 1;
                }
            }

            // Add the result for the current query (true if special, false otherwise)
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