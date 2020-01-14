#!/usr/bin/python
# -*- coding: utf-8-*-
import copy
import sys

map_path = sys.argv[1]
rules_path = sys.argv[2]
generation = int(sys.argv[3])

# Maps creating
maps = []
with open(map_path,'r') as map_data:
    for line in map_data.readlines(): 
        maps.append(line.strip())

# Rules Creating
rules = []
with open(rules_path,'r') as rule_data:
    for rule in rule_data.readlines(): 
        rules.append(rule.strip())

length_row = len(maps)
length_column = len(maps[-1]) 

def location(maps, row, column):
    # If 1*1 matrix
    if length_row == 1 and length_column == 1:
        return [maps[row][column]]
    # If 1*x matrix
    elif length_row == 1:
        if column == 0:
            return [maps[row][column+1]]
        elif column != 0 and column != length_column -1:
            return [maps[row][column-1], maps[row][column+1]]
        else:
            return [maps[row][column-1]]
    # If x*1 matrix
    elif length_column == 1:
        if row == 0:
            return [maps[row+1][column]]
        elif row != 0 and row != length_row -1:
            return [maps[row-1][column], maps[row+1][column]]
        else:
            return [maps[row-1][column]]
    # Top left corner
    elif row == 0 and column == 0: 
        return [maps[1][0], maps[1][1], maps[0][1]]
    # Top row edge
    elif row == 0 and (column != 0 and column != length_column -1):
        return [maps[0][column-1], maps[0][column+1], maps[1][column-1], maps[1][column], maps[1][column+1]]
    # Top right corner
    elif row == 0 and column == length_column -1:
        return [maps[0][column-1], maps[1][column-1], maps[1][column]]
    # Left edge
    elif (row != 0 and row != length_row -1) and column == 0:
        return [maps[row-1][0], maps[row+1][0], maps[row-1][1], maps[row+1][1], maps[row][1]]
    # Bottom left corner
    elif row == length_row -1 and column == 0 :
        return [maps[row-1][0], maps[row-1][1], maps[row][1]]
    # Bottom row edge 
    elif row == length_row -1 and (column != 0 and column != length_column -1):
        return [maps[row][column-1], maps[row][column+1], maps[row-1][column-1], maps[row-1][column+1], maps[row-1][column]]
    # Right bottom corner
    elif row == length_row -1 and column == length_column -1:
        return [maps[row][column-1], maps[row-1][column-1], maps[row-1][column]]
    # Right edge
    elif (row != 0 and row != length_row -1) and column == length_column -1:
        return [maps[row-1][column], maps[row+1][column], maps[row-1][column-1], maps[row+1][column-1], maps[row][column-1]]
    # If in the middle 
    else:
        return [maps[row-1][column-1], maps[row-1][column], maps[row-1][column+1], maps[row][column-1], maps[row][column+1], maps[row+1][column-1], maps[row+1][column], maps[row+1][column+1]]

# This func tries each rule to specific column and row
def rule_try(rules, species, row, column, maps): 
    for each in rules:
        spec = each[0]
        sign = each[1]
        count = int(each[2])
        make_it = each[3]
        if species == spec:
            if sign == "=" and location(maps,row,column).count("*") == count:
                return make_it
            elif sign == "<" and location(maps,row,column).count("*") < count:
                return make_it
            elif sign == ">" and location(maps,row,column).count("*") > count:
                return make_it
            else:
                continue
        else:
            continue
    else:
        return species

def change(maps, generation):
    if generation != 0:
        flip_flop = []
        for row in range(0,length_row):
            row_by_row = []
            for column in range(0,length_column):
                row_by_row.append(rule_try(rules, maps[row][column], row, column,maps))
            flip_flop.append("".join(row_by_row))

        i = 1
        while i < generation:
            maps = copy.deepcopy(flip_flop)
            flip_flop = []
            for row in range(0,length_row):
                row_by_row = []
                for column in range(0,length_column):
                    row_by_row.append(rule_try(rules, maps[row][column], row, column, maps))
                flip_flop.append("".join(row_by_row))
            i+=1
        return flip_flop
    else:
        return maps

print "\n".join(change(maps, generation))
