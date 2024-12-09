from Solution import Solution
import unittest
from timeout_decorator import timeout

class UnitTest(unittest.TestCase):
    def setUp(self):
        self.__testCases = {1: ([3,4,1,2,6], [[0,4]], [False]), 2: ([4,3,1,6], [[0,2],[2,3]], [False, True])}
        self.__obj = Solution()
        return super().setUp()
    
    @timeout(0.5)
    def test_case_1(self):
        nums, queries, output = self.__testCases[1]
        result = self.__obj.isArraySpecial(nums = nums, queries = queries)
        self.assertIsInstance(result, list)
        self.assertTrue(all(r == o for r, o in zip(result, output)))

    @timeout(0.5)
    def test_case_2(self):
        nums, queries, output = self.__testCases[2]
        result = self.__obj.isArraySpecial(nums = nums, queries = queries)
        self.assertIsInstance(result, list)
        self.assertTrue(all(r == o for r, o in zip(result, output)))

if __name__ == '__main__': unittest.main()