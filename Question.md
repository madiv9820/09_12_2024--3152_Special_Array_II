# [3152. Special Array II](https://leetcode.com/problems/special-array-ii)

**Type:** Medium <br>
**Topics:** Array, Binary Search, Prefix Sum <br>
**Companies:** National Payments Corporation of India, Amazon, Google
<hr>

An array is considered **special** if every pair of its adjacent elements contains two numbers with different parity.

You are given an array of integer `nums` and a 2D integer matrix `queries`, where for <code>queries[i] = [from<sub>i</sub>, to<sub>i</sub>]</code> your task is to check that subarray (A **subarray** is a contiguous sequence of elements within an array.) <code>nums[from<sub>i</sub>..to<sub>i</sub>]</code> is **special** or not.

Return an array of booleans `answer` such that `answer[i]` is `true` if <code>nums[from<sub>i</sub>..to<sub>i</sub>]</code> is special.
<hr>

### Examples:
- **Example 1:** <br>
**Input:** nums = [3,4,1,2,6], queries = [[0,4]] <br>
**Output:** [false] <br>
**Explanation:** <br>
The subarray is `[3,4,1,2,6]`. 2 and 6 are both even.

- **Example 2:** <br>
**Input:** nums = [4,3,1,6], queries = [[0,2],[2,3]] <br>
**Output:** [false,true] <br>
**Explanation:** <br> 1. The subarray is `[4,3,1]`. 3 and 1 are both odd. So the answer to this query is `false`. <br> 2. The subarray is `[1,6]`. There is only one pair: `(1,6)` and it contains numbers with different parity. So the answer to this query is `true`.
<hr>

### Constraints:
- <code>1 <= nums.length <= 10<sup>5</sup></code>
- <code>1 <= nums[i] <= 10<sup>5</sup></code>
- <code>1 <= queries.length <= 10<sup>5</sup></code>
- <code>queries[i].length == 2</code>
- <code>0 <= queries[i][0] <= queries[i][1] <= nums.length - 1</code>
<hr>

### Hints:
- Try to split the array into some non-intersected continuous special subarrays.
- For each query check that the first and the last elements of that query are in the same subarray or not.