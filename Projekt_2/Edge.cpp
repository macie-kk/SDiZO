#include "Edge.h"

EdgeClass::EdgeClass(Vertex* start_node, Vertex* end_node, int dist) {
    src = start_node;
    dst = end_node;
    weight = dist;
}

Vertex* EdgeClass::get_src() {
    return this->src;
}

Vertex* EdgeClass::get_dst() {
    return this->dst;
}

int EdgeClass::get_weight() {
    return this->weight;
}
