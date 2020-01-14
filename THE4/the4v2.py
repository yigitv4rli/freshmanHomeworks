#!/usr/bin/python
# -*- coding: utf-8 -*-

def is_leaf(tree): # Looking for whether given tree is leaf or not
    if len(tree) == 2 and type(tree[1]) == int:
        return True
    else:
        return False

def max_Valve(tree): # Finds max_valve in given tree
    values = []
    while tree:
		element = tree[0]
		tree = tree[1:]
		if type(element) == list:
			tree += element
		else:
			values += [element]

    valves = []
    for number in values:
        if type(number) == int:
            valves.append(number)
        else:
            continue
    return max(valves)

# I have used N-ary Tree path finder which can be found at Nihil
def helper_path_finder(element, tree):
    if tree == []:
        return []
    return [[element] + tree[0]] + helper_path_finder(element, tree[1:])

def path_finder(tree):
    if is_leaf(tree):
        return [[tree[0],tree[1]]]
    path_list = []
    for child in tree[1:]:
       path_list.extend(helper_path_finder(tree[0], path_finder(child)))
    path_list = sorted(path_list,key=lambda x: x[-1])
    return path_list

def minimizer(arg):
    pass


def chalchiuhtlicue(tree):
    paths = path_finder(tree)
    current_time = 1
    max_time = max_Valve(tree)
    closed = []
    while current_time < max_time:
        current_closed = []
        for path in paths:
            if current_time == path[-1]:
                current_closed.append(path[-2])
            else:
                continue
        closed.append(current_closed)
        current_time +=1
    closed.append([tree[0]])
    return closed

print max_Valve(['r', ['a', ['c', 3], ['d', 10], ['e', ['i', 8], ['j', 8]]], ['b', ['f', 1], ['g', 3], ['h', 6]]])
print path_finder(['r', ['a', ['c', 3], ['d', 10], ['e', ['i', 8], ['j', 8]]], ['b', ['f', 1], ['g', 3], ['h', 6]]])
print chalchiuhtlicue(['r', ['a', ['c', 3], ['d', 10], ['e', ['i', 8], ['j', 8]]], ['b', ['f', 1], ['g', 3], ['h', 6]]])
