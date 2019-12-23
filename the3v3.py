#!/usr/bin/python
# -*- coding: utf-8-*-
import sys

map_path = sys.argv[1]
rules_path = sys.argv[2]
generation = int(sys.argv[3])

rules = []
with open(rules_path,'r') as rule_data:
    for rule in rule_data.readlines():
        rules.append(rule.strip())

world = []
with open(map_path,'r') as map_data:
    for line in map_data.readlines(): 
        world.append(" " + line.strip() + " ")

length_row = len(world) # Normal len it does not include first and last empty rows
length_column = len(world[-1]) # Normal len + 2 since there is empty strings

world = (" " * length_column) + "".join(world) + (" " * length_column)
length_world = len(world)

def neighbourFinder(location, maps):
    return [maps[location-length_column-1], \
        maps[location-length_column], \
        maps[location-length_column+1], \
        maps[location-1], \
        maps[location+1], \
        maps[location+length_column+1], \
        maps[location+length_column-1], \
        maps[location+length_column]]

def ruleTry(rules, species, location, maps):
    for each in rules:
        spec = each[0]
        sign = each[1]
        count = int(each[2])
        make_it = each[3]
        if species == spec:
            if sign == "=" and neighbourFinder(location, maps).count("*") == count:
                return make_it
            elif sign == "<" and neighbourFinder(location, maps).count("*") < count:
                return make_it
            elif sign == ">" and neighbourFinder(location, maps).count("*") > count:
                return make_it
            else:
                continue
        else:
            continue
    else:
        return species

def normalizer(arg):
    return arg[length_column+1:-(length_column+1)].split("  ")

def geneCreation(world, rules):
    mid_gene = ""
    for index in range(0,length_world):
        if world[index] == " ":
            mid_gene += world[index]
        else:
            mid_gene += ruleTry(rules, world[index], index, world)
    return mid_gene

def generationFinder(world, rules, generation):
    if generation != 0:
        mid_gene = geneCreation(world,rules)
        i=1
        while i < generation:
            final_version = mid_gene
            mid_gene = geneCreation(final_version, rules)
            i+=1
        return normalizer(mid_gene)
    else:
        return normalizer(world)

print "\n".join(generationFinder(world, rules, generation))