from typing import List

class Solution:
    def isArraySpecial(self, nums: List[int], queries: List[List[int]]) -> List[bool]:
        # Initialize an empty list to store the results for each query.
        answer = []
        
        # Get the length of the nums array.
        n = len(nums)
        
        # Create a list 'violations' where each element is 1 if the adjacent elements at the current index have the same parity, otherwise 0.
        violations = [1 if (nums[index] & 1) == (nums[index+1] & 1) else 0 for index in range(n-1)]

        # Create a prefix sum array to store cumulative number of violations up to each index.
        prefix_violations = [0] * (n+1)

        # Fill the prefix_violations array where each index i stores the number of violations from index 0 to i-1.
        for index in range(1, n):
            prefix_violations[index] = prefix_violations[index-1] + violations[index-1]

        # For each query, check the number of violations in the subarray [start, end]
        # by checking the difference in prefix sums for the range [start, end].
        for start, end in queries:
            # If the difference in prefix sums is 0, it means there are no violations in this range (subarray is special).
            answer.append(prefix_violations[end] - prefix_violations[start] == 0)

        # Return the list of results for all queries.
        return answer