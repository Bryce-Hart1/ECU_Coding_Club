import random
from dataclasses import dataclass
from typing import List, Dict




@dataclass
class customerTransaction:
    first_name: str
    last_name: str
    transaction: int


@dataclass
class Match:
    found: bool = False
    i: int = -1
    j: int = -1


# Same first+last name, AND amounts add up to target. O(n^2): every
# transaction checked against every other transaction.
def find_customer_pair_brute(txns: List[customerTransaction], target: int) -> Match:
    n = len(txns)  # cast to int from std::size_t
    for i in range(n):
        for j in range(i + 1, n):
            # see if the firstname matches the last name.
            same_customer = (txns[i].first_name == txns[j].first_name and txns[i].last_name == txns[j].last_name)

            if same_customer and txns[i].transaction + txns[j].transaction == target:
                return Match(True, i, j)
    return Match()


# Combine first + last into one string key, per customer remember every
# amount seen so far. O(n): one pass, O(1) average lookup per transaction.
def combine_name(first: str, last: str) -> str:
    return first + " " + last


def find_customer_pair_fast(txns: List[customerTransaction], target: int) -> Match:
    seen_by_customer: Dict[str, Dict[int, int]] = {}

    for i in range(len(txns)):
        key = combine_name(txns[i].first_name, txns[i].last_name)
        complement = target - txns[i].transaction

        seen = seen_by_customer.setdefault(key, {})  # creates an empty inner map the first time this name appears
        if complement in seen:
            return Match(True, seen[complement], i)

        seen[txns[i].transaction] = i

    return Match()