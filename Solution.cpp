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

        // Create a vector to store '1' if adjacent elements have the same parity, '0' otherwise
        vector<int> violations(n-1, 0);

        // Iterate through the nums array to detect parity violations
        for(int index = 0; index < n-1; ++index)
            // If adjacent elements have the same parity, mark it as a violation (1), otherwise (0)
            violations[index] = (nums[index] & 1) == (nums[index+1] & 1);

        // Create a prefix sum array to store cumulative number of violations up to each index
        vector<int> prefix_violations(n+1, 0);

        // Iterate through the violations array to calculate the prefix sum of violations
        for(int index = 1; index < n; ++index)
            // The cumulative number of violations at index 'i' is the sum of violations up to 'i-1'
            prefix_violations[index] = prefix_violations[index-1] + violations[index-1];

        // Iterate through each query in the 'queries' vector
        for(const vector<int>& query: queries) {
            // Extract the 'start' and 'end' indices from the current query
            const int &start = query[0], &end = query[1];

            // If the number of violations in the range [start, end] is zero, the subarray is "special"
            answer.emplace_back((prefix_violations[end] - prefix_violations[start]) == 0);
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