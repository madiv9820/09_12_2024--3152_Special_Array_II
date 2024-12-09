- ## Approach 1:- Brute Force (Time Limit Exceed)
 
    - ### Intuition
        The problem asks us to determine if subarrays defined by queries are "special." A subarray is special if every pair of adjacent elements in it has different parity (one is odd, the other is even). The goal is to efficiently check this property for each query.

        We can directly simulate the checking process for each query by iterating through the subarray and comparing the parity of adjacent elements.

    - ### Approach
        1. **Initialization**:  
        Create an empty list, `answer`, to store the result for each query.

        2. **Processing Each Query**:  
            - For each query `[start, end]`:
                - Assume the subarray is "special" (`special = True`).
                - Iterate through the range `[start, end-1]` to compare the parity of adjacent elements:
                    - Use the bitwise operation `(num & 1)` to check parity:
                        - `num & 1 == 1` means the number is odd.
                        - `num & 1 == 0` means the number is even.
                    - If any adjacent pair has the same parity, mark the subarray as not special (`special = False`) and break out of the loop.

        3. **Add Results to Answer**:  
        After processing the subarray for the query, append the result (`True` if special, otherwise `False`) to the `answer` list.

        4. **Return Results**:  
        Once all queries are processed, return the `answer` list.

    - ### Code Implementation
        - **Python Solution**
            ```python3 []
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
            ```

            - **C++ Solution**
            ```cpp []
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
            ```

    - ### Time Complexity
        - **Outer Loop**: Iterates over all queries → $O(q)$, where $q$ is the number of queries.
        - **Inner Loop**: For each query, iterates through the range `[start, end-1]` → worst case $O(n)$, where $n$ is the length of `nums`.
            - In the worst case (all queries cover the full range), the inner loop processes $O(q \cdot n)$.
        - **Overall**:  
            - **Worst Case**: $O(q \cdot n)$.  
            - **Average Case**: Faster if subarrays are smaller or violations are found early (due to the `break` statement).

    - ### Space Complexity
        - The algorithm uses:
            - $O(q)$ space for the `answer` list to store results.
            - Constant auxiliary space for variables (`special`, `index`).
        - **Overall**: $O(q)$, where $q$ is the number of queries.