from math import log2, ceil

class Segment_Tree:
    def __init__(self, arr):
        curr_res = log2(len(arr))
        desired_length = pow(2, ceil(curr_res))

        while len(arr) != desired_length:
            arr.append(0)

        self.size = desired_length
        for i in range(desired_length - 1):
            arr.insert(0, 0)
        arr.insert(0, -1)
        self.arr = arr
        self.build_tree()

    def get_element_at_index(self, idx):
        return self.arr[idx + self.size - 1]

    def build_tree(self):
        start_idx = self.size - 1
        while (start_idx != 0):
            self.arr[start_idx] = self.arr[start_idx * 2] + self.arr[start_idx * 2 + 1]
            start_idx -= 1

    def overlap(self, want, curr):
        return curr[0] >= want[0] and want[1] >= curr[1]

    def get_sum_in_range(self, want_low, want_high, curr_node_idx=1, curr_low=1, curr_high=None):
        if want_low > want_high:
            print("Error: First index has to be less than second index")
            return None

        if curr_high is None:
            curr_high = self.size

        if self.overlap([want_low, want_high], [curr_low, curr_high]):
            return self.arr[curr_node_idx]

        if curr_low == curr_high:
            return 0

        middle = (curr_low + curr_high) // 2

        left_child_curr_low = curr_low
        left_child_curr_high = middle

        right_child_curr_low = middle+1
        right_child_curr_high = curr_high

        return self.get_sum_in_range(want_low, want_high, 2 * curr_node_idx, left_child_curr_low,
                                     left_child_curr_high) + \
            self.get_sum_in_range(want_low, want_high, 2 * curr_node_idx + 1, right_child_curr_low,
                                  right_child_curr_high)

    def print_raw_arr(self):
        for idx, ele in enumerate(self.arr):
            print(idx, ele)

    def get_array(self):
        return self.arr
