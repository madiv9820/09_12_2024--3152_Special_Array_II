from typing import List

class Solution:
    def isArraySpecial(self, nums: List[int], queries: List[List[int]]) -> List[bool]:
        # Initialize an empty list to store the results for each query.
        answer = []

        # Loop through each query in the 'queries' list.
        for start, end in queries:
            # Assume the subarray is special initially.
            special = True

            # Iterate through the subarray defined by the query (from 'start' to 'end-1').
            # Check if any adjacent pair of numbers has the same parity.
            for index in range(start, end):
                # Check parity of adjacent elements:
                # (nums[index] & 1) gives 1 if nums[index] is odd, 0 if even.
                # If the parity of nums[index] and nums[index+1] is the same, mark as not special.
                if (nums[index] & 1) == (nums[index + 1] & 1):
                    special = False  # Subarray is not special if parity matches.
                    break  # Exit the loop early since we already know the result for this query.

            # Append the result (True if special, False otherwise) to the answer list.
            answer.append(special)

        # Return the list of results for all queries.
        return answer