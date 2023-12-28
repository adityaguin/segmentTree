# EVERYTHING IS ONE INDEXED HERE
from segment_tree import Segment_Tree
def main():
    test = Segment_Tree([3,2,4,5,1,1,5,3])
    print(test.get_sum_in_range(2,4))
    print(test.get_sum_in_range(5,6))
    print(test.get_sum_in_range(1,8))
    print(test.get_sum_in_range(3,3))

if __name__ == "__main__":
    main()