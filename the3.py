#!/usr/bin/python
# -*- coding: utf-8-*-

r = open("examples/rules.txt","r")
m = open("examples/map1.txt", "r")
maps = m.readlines()
rules = r.readlines()
length_row = len(maps)
length_column = len(maps[-1]) 

def location(row,column):
    # Top left corner
    if row == 0 and column == 0: 
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
        
def change(maps):
    last_version = []
    for row in range(0,length_row):
        row_by_row = []
        for column in range(0,length_column):
            if maps[row][column] == "-" and location(row,column).count("*") == 3:
                row_by_row.append("*")
            elif maps[row][column] == "*" and location(row,column).count("*") < 2:
                row_by_row.append("-")
            elif maps[row][column] == "*" and location(row,column).count("*") > 3:
                row_by_row.append("-")
            else:
                row_by_row.append(maps[row][column])
        last_version.append("".join(row_by_row)+"\n")
    return last_version

print "".join(change(maps))
