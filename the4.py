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
    return path_list


def deneme(tree):
    if not is_leaf(tree):
        for child in tree:
            if type(child) != list and type(child) != int:
                tree.insert(1,max_Valve(tree))
            elif type(child) == list and not is_leaf(child):
                child.insert(1,max_Valve(child))
                for child_of_child in child[2:]:                        
                    if type(child_of_child) == list:
                        index = child.index(child_of_child)
                        child[index] = deneme(child_of_child)
    return tree

        


def chalchiuhtlicue(tree):
    pass


print deneme(['r', ['a', ['c', 3], ['d', 10], ['e', ['i', 8], ['j', 8]]], ['b', ['f', 1], ['g', 3], ['h', 6]]])
