from collections import deque
def bfs(adjList, startNode, visited):
    q = deque()
    visited[startNode] = True
    q.append(startNode)    
    while q:
        currentNode = q.popleft()
        print(currentNode, end=" ")
        for neighbor in adjList[currentNode]:
            if not visited[neighbor]:
                visited[neighbor] = True
                q.append(neighbor)
def addEdge(adjList, u, v):
    adjList[u].append(v)


def main():
    nodes = input("Enter the nodes in the graph (space-separated, e.g., 'a b c d'): ").split()
    adjList = {node: [] for node in nodes}
    edges = int(input("Enter the number of edges in the graph: "))
    print("Enter each edge as a pair of space-separated nodes (u v):")
    for _ in range(edges):
        while True:
            try:
                u, v = input().split()
                if u not in adjList or v not in adjList:
                    raise ValueError("Node values must be among the specified nodes")
                addEdge(adjList, u, v)
                break
            except ValueError as e:
                print(f"Invalid input: {e}. Please enter a valid pair of space-separated nodes (u v):")

    
    visited = {node: False for node in nodes}
    startNode = nodes[0]
    print(f"Breadth First Traversal starting from node {startNode} for a graph with {len(nodes)} nodes:", end=" ")
    bfs(adjList, startNode, visited)

if __name__ == "__main__":
    main()
