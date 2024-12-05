import aiofiles
import asyncio
import numpy as np
import time


async def main():
    page_ordering_rules = np.zeros((100, 100))
    total = 0
    incorrect_order_total = 0
    
    async with aiofiles.open('input.txt') as file:
        async for line in file:
            if line == '\n':
                break
            # 34|56
            num1, num2 = line.split('|')
            page_ordering_rules[int(num1)][int(num2)] = 1
        
        async for line in file:
            # 12,34,56,67,89
            pages = list(map(int, line.split(',')))
            if is_valid_ordering(page_ordering_rules, pages):
                # middle number
                middle = pages[len(pages) // 2]
                total += middle
            else:
                # fix the ordering
                fix_ordering(page_ordering_rules, pages)
                middle = pages[len(pages) // 2]
                incorrect_order_total += middle

    print(total)
    print(incorrect_order_total)


def is_valid_ordering(page_ordering_rules, pages):
    # 75,47,61,53,29
    for idx, page in enumerate(pages):
        # print(page, page_ordering_rules[:, page].nonzero())
        # print(pages[idx])
        
        # for each page that needs to come before the current page
        # if that page is in the list of pages that come after the current page
        # return False
        for p in page_ordering_rules[:, page].nonzero()[0]:
            if p in pages[idx:]:
                return False
    return True


def fix_ordering(page_ordering_rules, pages):
    # 75,97,47,61,53
    # 97,75,47,61,53
    
    # janky hack to make it work for all cases
    # it works for test input but not the real input
    # unless i use the while loop
    while not is_valid_ordering(page_ordering_rules, pages):
        # sort of insertion sort 
        for idx, page in enumerate(pages):
            # for each page that needs to come before the current page
            # if that page is in the list of pages that come after the current page
            # move it in front of the current page
            for p in page_ordering_rules[:, page].nonzero()[0]:
                if p in pages[idx:]:
                    pages.remove(p)
                    pages.insert(idx, p)


if __name__ == '__main__':
    t1 = time.time()
    asyncio.run(main())
    t2 = time.time()
    print(f"Execution time: {(t2-t1)*1000: .2f}ms")