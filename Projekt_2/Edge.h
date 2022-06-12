//
// Created by Marcin on 2022-06-01.
//

#ifndef JEZYKI_SKRYPTOWE___LISTA_5_EDGE_H
#define JEZYKI_SKRYPTOWE___LISTA_5_EDGE_H

#include <iostream>

class Vertex;

class EdgeClass {
   private:
    Vertex* src;
    Vertex* dst;
    int weight;

   public:
    EdgeClass() = default;
    EdgeClass(Vertex* start_node, Vertex* end_node, int dist);

    Vertex* get_src();
    Vertex* get_dst();
    int get_weight();

    bool operator<(const EdgeClass& other) const {
        return this->weight < other.weight;
    }

    friend std::ostream& operator<<(std::ostream& out, const EdgeClass& edge) {
        out << edge.weight;
        return out;
    }
};

struct
{
    bool operator()(EdgeClass* lhs, EdgeClass* rhs) {
        return lhs->get_weight() < rhs->get_weight();
    }
} CustomCompareEdge;

class Edge {
   public:
    int src;
    int dst;
    int cst;

    bool operator<(const Edge& other) const {
        return this->cst < other.cst;
    }
};

#endif
