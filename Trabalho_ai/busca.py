
"""
In busca.py, you will implement generic search algorithms which are called by
Pacman agents (in searchAgents.py).
"""
from lib.searchProblem import SearchProblem

import lib.util as util
from lib.util import Stack, Queue, PriorityQueue
from collections import deque
'''
Uso da pilha:
stack = Stack()
stack.push(element)
l = stack.list # Lista de elementos na pilha
e = stack.pop()

Uso da fila:
queue = Queue()
queue.push(element)
l = queue.list # Lista de elementos na fila
e = queue.pop()

Uso da fila de prioridades:
queuep = PriorityQueue()
queuep.push(element, value) # Valores baixos indicam maior prioridade
queuep.update(element, value) # Atualiza o valor de prioridade  de um elemento
l = queuep.heap # Lista de elementos na fila
e = queuep.pop()
'''

def tinyMazeSearch(problem):
    """
    Returns a sequence of moves that solves tinyMaze.  For any other maze, the
    sequence of moves will be incorrect, so only use this for tinyMaze.
    """
    from game import Directions
    s = Directions.SOUTH
    w = Directions.WEST
    return  [s, s, w, s, w, w, s, w]

    
def depthFirstSearch(problem):
    """
    Search the deepest nodes in the search tree first.

    Your search algorithm needs to return a list of actions that reaches the
    goal. Make sure to implement a graph search algorithm.

    To get started, you might want to try some of these simple commands to
    understand the search problem that is being passed in:

    print "Start:", problem.getStartState()
    print "Is the start a goal?", problem.isGoalState(problem.getStartState())
    print "Start's successors:", problem.getSuccessors(problem.getStartState())
    """
    "*** YOUR CODE HERE ***"
    pilha = [(problem.getStartState(), [])]
    visitados = []
    while pilha:
        vertice = pilha.pop()
        caminho = vertice[1]
        if vertice[0] != problem.getStartState():
            nome_vertice = vertice[0][0]
        else:
            nome_vertice = vertice[0]
        if nome_vertice in visitados:
            continue
        if problem.isGoalState(nome_vertice):
            return vertice[1]
        visitados.append(nome_vertice)
        for vizinho in problem.getSuccessors(nome_vertice):
            pilha.append((vizinho, caminho + [vizinho[1]]))
    return[]

def breadthFirstSearch(problem):
    """Search the shallowest nodes in the search tree first."""
    fila = deque([(problem.getStartState(), [])])
    visitados = []
    while fila:
        vertice = fila.popleft()
        caminho = vertice[1]
        if vertice[0] != problem.getStartState():
            nome_vertice = vertice[0][0]
        else:
            nome_vertice = vertice[0]
        if nome_vertice in visitados:
            continue
        if problem.isGoalState(nome_vertice):
            return vertice[1]
        visitados.append(nome_vertice)
        for vizinho in problem.getSuccessors(nome_vertice):
            fila.append((vizinho, caminho + [vizinho[1]]))
    return[]

    

def uniformCostSearch(problem):
    """Search the node of least total cost first."""
    lista = [(problem.getStartState(), [], 0)]
    visitados = []
    while lista:
        lista.sort(key= lambda x: x[2], reverse=True)
        vertice = lista.pop()
        caminho = vertice[1]
        custo = vertice[2]
        if vertice[0] != problem.getStartState():
            nome_vertice = vertice[0][0]
        else:
            nome_vertice = vertice[0]
        if nome_vertice in visitados:
            continue
        if problem.isGoalState(nome_vertice):
            return vertice[1]
        visitados.append(nome_vertice)
        for vizinho in problem.getSuccessors(nome_vertice):
            lista.append((vizinho, caminho + [vizinho[1]],
                          custo + vizinho[2]))
    return[]


def nullHeuristic(state, problem=None):
    """
    A heuristic function estimates the cost from the current state to the nearest
    goal in the provided SearchProblem.  This heuristic is trivial.
    """
    return 0

def aStarSearch(problem, heuristic=nullHeuristic):
    """Search the node that has the lowest combined cost and heuristic first."""
    inicio = problem.getStartState()
    lista = [(inicio, [], 0, heuristic(inicio, problem=problem))]
    visitados = []
    while lista:
        lista.sort(key= lambda x: x[2] + x[3], reverse=True)
        vertice = lista.pop()
        caminho = vertice[1]
        custo = vertice[2]
        if vertice[0] != problem.getStartState():
            nome_vertice = vertice[0][0]
        else:
            nome_vertice = vertice[0]
        if nome_vertice in visitados:
            continue
        if problem.isGoalState(nome_vertice):
            return vertice[1]
        visitados.append(nome_vertice)
        for vizinho in problem.getSuccessors(nome_vertice):
            lista.append((vizinho, caminho + [vizinho[1]],
                          custo + vizinho[2],
                          heuristic(vizinho[0], problem=problem)))
    return []


# Abbreviations
bfs = breadthFirstSearch
dfs = depthFirstSearch
astar = aStarSearch
ucs = uniformCostSearch

  
