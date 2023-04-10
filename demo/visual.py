from graphviz import Digraph


class Graph:
    def __init__(self, name, nodes, edges):
        self.name = name
        self.nodes = []
        self.edges = []
        node2id = dict.fromkeys(nodes)
        for i in range(len(nodes)):
            node2id[nodes[i]] = i
        for node in nodes:
            self.nodes.append(node2id[node])
        for edge in edges:
            t = [str(node2id[edge[0]]), str(node2id[edge[2]]), edge[1]]
            self.edges.append(t)
        

def buildGraph(graph):
    g = Digraph(graph.name, engine='dot')
    for node in graph.nodes:
        if node == 0:
            g.node(str(node), str(node), color='blue')
        else:
            g.node(str(node), str(node))
    for edge in graph.edges:
        g.edge(edge[0], edge[1], edge[2])
    return g


if __name__ == '__main__':
    n = int(input(""))
    DFAs = []
    for _ in range(n):
        name = input("")
        node_n = int(input(""))
        nodes = []
        for __ in range(node_n):
            t = input("")
            nodes.append(t)
        edges = []
        edge_n = int(input(""))
        for __ in range(edge_n):
            t = input("")
            tt = t.split(" ")
            edges.append(tt)
        g = Graph(name, nodes, edges)
        g = buildGraph(g)
        DFAs.append(g)
    for g in DFAs:
        g.view(g.name, "./pics/dfa/")
