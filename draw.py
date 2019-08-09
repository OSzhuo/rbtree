#!/usr/bin/env python3

from graphviz import Digraph
import time

#def view(this):
#    pg = Digraph('find')
#    pg.node(str(this.key), style='filled', color=('red' if this.color == RED else 'BLACK'), fontcolor='white',
#            shape='circle')
#    pg.view()

def draw(this, graph):
    if this["color"] == 0:
        s = 'black'
    else:
        s = 'red'
    # 画出自己这个点，包括值和颜色
    graph.node(str(this["key"]), style='filled', color=s, fontcolor='white', shape='circle')
    if this["left"] is not None:
        graph.edge(str(this["key"]), str(this["left"]["key"]))
        draw(this['left'], graph)
    elif this["right"] is not None:
        graph.edge(str(this["key"]), str(this["key"]) + "N")
    if this["right"] is not None:
        graph.edge(str(this["key"]), str(this["right"]["key"]))
        draw(this['right'], graph)
    elif this["left"] is not None:
        graph.edge(str(this["key"]), str(this["key"]) + "N")

with open("/tmp/rbtree.dict", "r") as f:
    l = f.readline()
    while l:
        tree=eval(l)
        graph = Digraph("tree")
        graph.format="png"
        draw(tree, graph)
        graph.view(cleanup=True)
        time.sleep(0.4)
        l = f.readline()
