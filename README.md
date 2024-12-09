# Special Array II (All Approaches) 

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

- ## Approach 2:- Binary Search

    - ### Intuition
        The goal is to determine whether a subarray of `nums` (specified by each query) is "special." A subarray is considered "special" if every pair of adjacent elements in the subarray contains numbers with different parity (one odd and one even).

        - ### Key Observations:
            - We need to find subarrays where no two adjacent elements have the same parity. This means we need to check if any violation (i.e., adjacent elements having the same parity) exists within the query range.
            - Instead of checking each subarray directly for every query, we can precompute the indices where violations occur and use binary search to quickly check for violations within the given range for each query.

    - ### Approach
        1. **Precompute Violations:**
            - Iterate through the `nums` array and record indices where two adjacent elements have the same parity. Store these indices in the `violation_indices` array.
        
        2. **Binary Search for Each Query:**
            - For each query, perform a binary search on `violation_indices` to check if there are any violations within the range `[start, end-1]` (adjusted to the query bounds).
            - If a violation exists in this range, the subarray is not special.
            - Otherwise, the subarray is special.

        3. **Return Results:**
            - For each query, append the result (`true` if the subarray is special, `false` otherwise) to the `answer` vector.

    - ### Code Implementation
        - **Python Solution**
            ```python3 []
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
            ```

        - **C++ Solution**
            ```cpp []
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
            ```

    - ### Time Complexity
        - **Preprocessing (Identifying Violations):**
            - We loop through the `nums` array once to find all violations. This takes $O(n)$, where $n$ is the length of the `nums` array.
    
        - **Query Processing (Binary Search):**
            - For each query, we perform a binary search on the `violation_indices` array, which takes $O(\log k)$, where $k$ is the number of violations (i.e., the number of indices in `violation_indices`).

        - **Overall Time Complexity:**
            - The total time complexity is $(O(n + q \log k))$, where $q$ is the number of queries.

    - ### Space Complexity
        - We use an additional array, `violation_indices`, to store the indices of violations. The space complexity is $O(k)$, where $k$ is the number of violations found.

        - The space complexity for the result array `answer` is $O(q)$, where $q$ is the number of queries.

        - **Overall Space Complexity:**
            - The total space complexity is $O(k + q)$, where $k$ is the number of violations and $q$ is the number of queries.

- ## Approach 3:- Prefix Sum

    - ### Intuition
        The problem asks us to determine if a subarray is "special," meaning that every pair of adjacent elements in the subarray must contain numbers with different parity (one odd and one even). A naive solution would check each subarray for every query, but this approach would be inefficient for large arrays and many queries. Instead, we can optimize the solution by:

        1. **Precomputing the violations:** We create a list of violations where each element represents whether two adjacent elements in the array have the same parity.
        2. **Using a prefix sum array:** By computing the cumulative number of violations in the array, we can quickly check the number of violations in any subarray by calculating the difference in prefix sums for the range specified by the query.

        With this approach, we can efficiently determine whether each query's subarray is special without checking the entire subarray every time.

    - ### Approach
        1. **Identify Violations:** 
            - For each pair of adjacent elements in the `nums` array, check if they have the same parity (both odd or both even). Store the result (1 for violation, 0 for no violation) in the `violations` array.
        
        2. **Prefix Sum Array:** 
            - Construct a `prefix_violations` array where each element represents the cumulative sum of violations up to that index. This allows us to quickly calculate the number of violations in any subarray.

        3. **Query Processing:**
            - For each query, calculate the number of violations in the subarray using the `prefix_violations` array. If the number of violations is zero in the range `[start, end]`, then the subarray is "special"; otherwise, it's not.

        4. **Return the Results:**
            - For each query, return `true` if the subarray is special, and `false` if it is not.

    - ### Code Implementation
        
        - **Python Solution**
            ```python3 []
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
            ```

        - **C++ Solution**
            ```cpp []
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
            ```

    - ### Time Complexity
        1. **Precomputing Violations:**
            - We loop through the `nums` array once to calculate the `violations` array, which takes $O(n)$ time, where $n$ is the length of `nums`.
        
        2. **Prefix Sum Calculation:**
            - Constructing the `prefix_violations` array requires another pass through the `nums` array, which takes $O(n)$ time.

        3. **Query Processing:**
            - For each query, calculating the number of violations in the range `[start, end]` can be done in constant time $O(1)$ using the `prefix_violations` array.
            - If there are $q$ queries, processing all queries takes $O(q)$ time.

        **Total Time Complexity:**
            - $O(n + q)$, where $n$ is the length of the `nums` array and $q$ is the number of queries.

    - ### Space Complexity
        1. **Violations Array:**
            - We store a `violations` array of size $n-1$, so it takes $O(n)$ space.
        
        2. **Prefix Violations Array:**
            - We store a `prefix_violations` array of size $n+1$, so it also takes $O(n)$ space.

        3. **Answer Array:**
            - The `answer` array stores the result for each query, so it takes $O(q)$ space, where $q$ is the number of queries.

        **Total Space Complexity:**
            - $O(n + q)$, where $n$ is the size of the `nums` array and $q$ is the number of queries.