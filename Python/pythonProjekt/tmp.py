	def add_node(self, data): 
		""" Funkcja dodaje do grafu wierzcholek """
		if len(self.nodes) == self.numberOfNodes:
			raise Exception("Nie mozna dodac kolejnego wezla")
		newNode = Node(data)
		self.nodes.append(newNode)
