from typing import List

class Solution:
    def isArraySpecial(self, nums: List[int], queries: List[List[int]]) -> List[bool]:
        # Initialize an empty list to store the results for each query.
        answer = []
        
        # Get the length of the nums array.
        n = len(nums)
        
        # Create a list to store indices where adjacent elements in the nums array have the same parity.
        violations_indices = []

        # Loop through nums array to find indices where adjacent numbers have the same parity.
        for index in range(n - 1):
            # Check if current element and next element have the same parity.
            if (nums[index] & 1) == (nums[index + 1] & 1):
                # If they do, store the index of the violation.
                violations_indices.append(index)

        # Loop through each query to check if the subarray from start to end is special.
        for start, end in queries:
            # Initially, assume the subarray is special (no violations).
            special = True
            
            # Initialize the left and right pointers for binary search.
            left, right = 0, len(violations_indices) - 1

            # Perform binary search to find any violations in the range [s, e-1].
            while left <= right:
                mid = (left + right) // 2  # Find the middle index of the violations list.
                
                # If there's a violation within the range, mark the subarray as not special.
                if start <= violations_indices[mid] <= end - 1:
                    special = False
                    break  # Exit the loop once a violation is found.
                
                # If the current violation is before the start of the range, move the left pointer to mid+1.
                elif violations_indices[mid] < start:
                    left = mid + 1
                # If the current violation is after the end of the range, move the right pointer to mid-1.
                else:
                    right = mid - 1

            # Append the result (True if no violation was found, False otherwise).
            answer.append(special)

        # Return the list of results for all queries.
        return answer