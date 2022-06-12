#include "Vertex.h"
#include <climits>

Vertex::Vertex() {
    parent = nullptr;
    distanceFromStart = INT_MAX;
    rank = 0;
    // this->vertexNumber = vertexNumber;
}

void Vertex::addNeighbour(Vertex *start_vertex, Vertex *end_vertex, int distance) {
    this->neighboursList.AddBack({start_vertex, end_vertex, distance});
}

void Vertex::setParent(Vertex *newParent) {
    this->parent = newParent;
}

void Vertex::setDistanceFromStart(int newDistance) {
    this->distanceFromStart = newDistance;
}

Vertex *Vertex::getParent() {
    return this->parent;
}

int Vertex::getDistanceFromStart() {
    return this->distanceFromStart;
}

bool Vertex::operator<(const Vertex &r) {
    return this->distanceFromStart < r.distanceFromStart;
}

List<EdgeClass> &Vertex::getNeighboursList() {
    return this->neighboursList;
}

int Vertex::getVertexNumber() {
    return this->vertexNumber;
}

int Vertex::getRank() const {
    return rank;
}

void Vertex::setRank(int rank) {
    this->rank = rank;
}
