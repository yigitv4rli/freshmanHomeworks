def is_leaf(tree):
	if len(tree) == 2 and type(tree[1]) == int:
		return True
	else:
		return False

def max_Valve(tree):
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

def node_counter(tree):
	if not is_leaf(tree):
		for child in tree:
			if type(child) != list and type(child) != int:
				tree.insert(1,max_Valve(tree))
			elif type(child) == list and not is_leaf(child):
				child.insert(1,max_Valve(child))
				for child_of_child in child:
					if type(child_of_child) == list:
						index = child.index(child_of_child)
						child[index] = node_counter(child_of_child)
	return tree

def flatter(tree):
	flatted = []
	while tree:
		element = tree[0]
		tree = tree[1:]
		if type(element) == list:
			tree += element
		else:
			flatted += [element]
	return flatted


def deleter(tree):
	if not is_leaf(tree):
		max_tree = max_Valve(tree)
		for child in tree:
			if type(child) == list and not is_leaf(child):
				max_child = max_Valve(child)
				if max_tree == max_child:
					del child[:2]
				for child_of_child in child:
					if type(child_of_child) == list and not is_leaf(child_of_child):
							if max_Valve(child_of_child) == max_child:
								del child_of_child[:2]
								index = child.index(child_of_child)
								child[index] = deleter(child_of_child)
							else:
								index = child.index(child_of_child)
								child[index] = deleter(child_of_child)
					elif type(child_of_child) == list and is_leaf(child_of_child):
						if max_Valve(child_of_child) == max_child:
							index = child.index(child_of_child)
							child[index] = []
			elif type(child) == list and is_leaf(child):
				if max_tree == max_Valve(child):
					index = tree.index(child)
					tree[index] = []
	return tree

def chalchiuhtlicue(tree):
	tree = node_counter(tree)
	tree = deleter(tree)
	tree = flatter(tree)
	current_time = 1
	max_time = tree[1]
	result = []
	while current_time <= max_time:
		closed = []
		for i in range(0,len(tree),2):
			if current_time == tree[i+1]:
				closed.append(tree[i])
		result.append(closed)
		current_time +=1
	return result
