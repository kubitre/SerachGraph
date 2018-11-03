//
// Created by kubitre on 9/10/18.
//

#ifndef STEPGRAPH_GRAPHNODE_H
#define STEPGRAPH_GRAPHNODE_H


class GraphNode {
private:
    int numberNode;
    GraphNode *relation;

public:
    GraphNode(int numberNode);
    void setUpRelation(GraphNode *relation);
};

#endif //STEPGRAPH_GRAPHNODE_H
