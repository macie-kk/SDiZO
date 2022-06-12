#pragma once
#include "Edge.h"
#include "List.h"

class Vertex;

struct Neighbour {
    Vertex* neighbour;
    int distance;
};

class Vertex {
   public:
    Vertex();

    int getRank() const;

    void setRank(int rank);

    void addNeighbour(Vertex* start_vertex, Vertex* end_vertex, int distance);

    // settery
    void setParent(Vertex* newParent);
    void setDistanceFromStart(int newDistance);

    // gettery
    Vertex* getParent();
    int getDistanceFromStart();
    List<EdgeClass>& getNeighboursList();
    int getVertexNumber();

    // przeciążanie operatorów
    bool operator<(const Vertex& r);

    friend std::ostream& operator<<(std::ostream& out, const Vertex& vertex) {
        out << vertex.distanceFromStart;
        return out;
    }

   private:
    List<EdgeClass> neighboursList;
    Vertex* parent;
    int distanceFromStart;
    int vertexNumber;
    int rank;  // dla kruskala
};
