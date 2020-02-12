#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct Edge {
    int src, dest;
};

class Graph {
public:
    vector<vector<int> > adjMatrix;
    vector<vector<int> > incMatrix;
    bool oriented;

    ofstream out;

    Graph(vector<Edge> const &edges, int n, bool oriented) {
        this->adjMatrix.assign(n, vector<int>(n, 0));
        this->incMatrix.assign(n, vector<int>(edges.size(), 0));
        this->oriented = oriented;
        this->out.open("output.txt");

        if (oriented) {
            for (int i = 0; i < edges.size(); i++) {
                adjMatrix[edges[i].src - 1][edges[i].dest - 1] += 1;
                if (edges[i].src == edges[i].dest)
                    incMatrix[edges[i].src - 1][i] = 2;
                else {
                    incMatrix[edges[i].src - 1][i] = 1;
                    incMatrix[edges[i].dest - 1][i] = -1;
                }
            }
        } else {
            for (int i = 0; i < edges.size(); i++) {
                adjMatrix[edges[i].src - 1][edges[i].dest - 1] += 1;
                if (edges[i].src != edges[i].dest)
                    adjMatrix[edges[i].dest - 1][edges[i].src - 1] += 1;
                if (edges[i].src == edges[i].dest)
                    incMatrix[edges[i].src - 1][i] = 2;
                else {
                    incMatrix[edges[i].src - 1][i] = 1;
                    incMatrix[edges[i].dest - 1][i] = 1;
                }
            }
        }
    }

    void printPowersOfNodes() {
        bool isHomogeneous = true;
        int prevPower = -1;
        vector<int> powers;
        for (int i = 0; i < incMatrix.size(); i++) {
            int countOfOnes = 0;
            int countOfMOnes = 0;
            int countOfTwos = 0;
            for (int j : incMatrix[i]) {
                if (j == 1)
                    countOfOnes++;
                if (j == -1)
                    countOfMOnes++;
                if (j == 2)
                    countOfTwos++;
            }
            int halfInputPower = countOfMOnes + countOfTwos;
            int halfOutputPower = countOfOnes + countOfTwos;
            int power = halfInputPower + halfOutputPower;
            if (prevPower != -1 && prevPower != power)
                isHomogeneous = false;
            else
                prevPower = power;
            if (!oriented) {
                out << "Power of node " << i + 1 << " -> " << power << endl;
                powers.push_back(power);
            } else {
                out << "Half output power of node " << i + 1 << " -> " << halfOutputPower << endl;
                out << "Half input power of node " << i + 1 << " -> " << halfInputPower << endl;
            }
        }
        if (!oriented && isHomogeneous) {
            out << "Graph is homogeneous, power is " << prevPower << endl;
        } else if (!oriented) {
            out << "Graph not is homogeneous\n";
        }
        out << "==========\n";
        if (!oriented) {
            out << "Isolated nodes: ";
            for (int i = 0; i < powers.size(); i++) {
                if (powers[i] == 0)
                    out << i + 1 << " ";
            }
            out << "\n";
            out << "==========\n";
            out << "Hanging nodes: ";
            for (int i = 0; i < powers.size(); i++) {
                if (powers[i] == 1)
                    out << i + 1 << " ";
            }
            out << "\n";
            out << "==========\n";
        }
    }

    void printAdjMatrix() {
        out << "Adjacency matrix\n";
        for (auto &i : adjMatrix) {
            for (int j : i)
                out << j << " ";
            out << endl;
        }
        out << "==========\n";
    }

    void printIncMatrix() {
        out << "Incidence matrix\n";
        for (auto &i : incMatrix) {
            for (int j : i)
                out << j << " ";
            out << endl;
        }
        out << "==========\n";
    }

    ~Graph() {
        out.close();
    }
};

int main() {

    ifstream in("input.txt");

    int n, m;
    in >> n >> m;

    vector<Edge> edges(m);

    for (int i = 0; i < m; i++)
        in >> edges[i].src >> edges[i].dest;

    int oriented;
    cout << "Is graph oriented? ";
    cin >> oriented;
    cout << "\n";

    Graph *graph = new Graph(edges, n, oriented);

    graph->printAdjMatrix();
    graph->printIncMatrix();

    graph->printPowersOfNodes();

    return 0;
}