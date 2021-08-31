
# dict object
archetype = {"pos": [], "vel": []}
# set dict object
archetype["pos"] = [[1.5, 1.3, 1.4], [1.5, 1.3, 1.4]]
archetype["vel"] = [[1.5, 1.3, 1.4], [1.5, 1.3, 1.4]]

archetype1 = {"vel": [], "rot": [], "pos": []}
archetype1["vel"] = [[1.5, 1.3, 1.4], [1.5, 1.3, 1.4]]
archetype1["rot"] = [[1.5, 1.3, 1.4], [1.5, 1.3, 1.4]]
archetype1["pos"] = [[1.5, 1.3, 1.4], [1.5, 1.3, 1.4]]

archetype2 = {"obj": [], "rot": [], "pos": []}
archetype2["pos"] = [[2.3, 3.4, 4.5], [2.3, 3.4, 4.5], [2.3, 3.4, 4.5]]
archetype2["obj"] = [(3, "name"), (5, "jack"), (12, "person")]
archetype2["rot"] = [[2.3, 3.4, 4.5], [2.3, 3.4, 4.5], [2.3, 3.4, 4.5]]

world = []
world.append(archetype)
world.append(archetype1)
world.append(archetype2)

def archetype_match(archetype, query):
	archetype_match = True

	print(archetype.keys())
	keys = archetype.keys()

	for query_item in query:
		if query_item not in keys:
			archetype_match = False

	return archetype_match


def search(world, query):
	result = {}

	for archetype in world:
		if archetype_match(archetype, query) == True:
			print("match")
			for key in query:
				if result.get(key) == None:
					result[key] = archetype[key]
				else:
					result[key].append(archetype[key])

	return result


query = ["pos", "rot"]
result = search(world, query)

print("\nresult\n" + str(result))

print("\nentity\n")

for (pos, rot) in (result["pos"], result["rot"]):
	print(pos)
	print(rot)






