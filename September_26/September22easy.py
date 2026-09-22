# This is the first approach we talked about that iterates through every possible combination.
def first_approach(bankAmountsList: list, target: int) -> bool:

    for number_one in bankAmountsList:  # for every number in the list
        for number_two in bankAmountsList:  # for every number in list
            # compare (one + two = three)
            if number_one + number_two == target:
                return True  # return if we found our target

    return False


# Sort the amounts once, then walk inward from both ends. If the two
# ends add up to too much, move the right pointer in. If they add up
# to too little, move the left pointer in. O(n log n), dominated by the sort
def second_approach(amounts: list, target: int) -> bool:

    amounts.sort()  # start by sorting all numbers
    left = 0  # left walking pointer
    right = len(amounts) - 1  # right walking pointer
    # collapse on list
    # [] [] [] [] [] [] []
    # ^ pinch the list   ^
    # [] [] [] [] [] [] []
    # ^              ^ <-
    # [] [] [] [] [] [] []
    #  -> ^           ^
    while left < right:
        total = amounts[left] + amounts[right]

        if total == target:
            return True
        elif total < target:
            left += 1
        else:
            right -= 1
    return False


# Save each number in the list if we see it, then we can just add.
def third_approach(bankAmountsList: list, target: int) -> bool:
    map = {}

    for number in bankAmountsList:
        difference = target - number
        if difference in map:
            return True
        else:
            map[difference] = True
    return False