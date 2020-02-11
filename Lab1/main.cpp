#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main() {
    ifstream in("input.txt");

    string fName;
    cout << "Enter name of a file: ";
    cin >> fName;

    ofstream out(fName);

    int n, m;
    bool oriented;

    in >> n >> m;

    cout << "Is graph oriented? (type 1 for true and 0 for false): ";
    cin >> oriented;

    vector<vector<int> > adjM(n, vector<int>(n, 0));
    vector<vector<int> > incM(n, vector<int>(m, 0));

    for (int i = 0; i < m; i++) {
        int x, y;
        in >> x >> y;

        adjM[x - 1][y - 1] += 1;
        incM[x - 1][i] += 1;
        if (!oriented) {
            if (y != x)
                adjM[y - 1][x - 1] += 1;
            incM[y - 1][i] += 1;
        } else {
            if (x != y)
                incM[y - 1][i] = -1;
            else
                incM[y - 1][i] += 1;
        }
    }

    out << "Adjacency matrix:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            out << adjM[i][j] << " ";
        out << "\n";
    }
    out << "==================\n";

    out << "Incidence matrix:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++)
            out << incM[i][j] << " ";
        out << "\n";
    }
    out << "==================\n";


    if (!oriented) {

        vector<int> isolated;
        vector<int> hanging;

        bool homogeneous = true;
        int prevSum = -1;

        out << "Powers of nodes:\n";
        for (int i = 0; i < n; i++) {
            out << i + 1 << ": ";
            int sum = 0;
            for (int j = 0; j < m; j++)
                sum += incM[i][j];
            out << sum << "\n";
            if (sum == 0)
                isolated.push_back(i + 1);
            if (sum == 0)
                hanging.push_back(i + 1);
            if (prevSum == -1)
                prevSum = sum;
            else if (prevSum != sum)
                homogeneous = false;
        }
        out << (homogeneous ? "Graph is homogeneous" : "Graph is not homogeneous") << "\n";
        out << "==================\n";

        out << "Isolated nodes:\n";
        for (int i : isolated)
            out << i << " ";
        out << "\n";
        out << "==================\n";

        out << "Hanging nodes:\n";
        for (int i : hanging)
            out << i << " ";
        out << "\n";
        out << "==================\n";

    } else {
        out << "Half output powers:\n";
        for (int i = 0; i < n; i++) {
            out << i + 1 << ": ";
            int countOfOutputs = 0;
            for (int j = 0; j < m; j++)
                if (incM[i][j] == 1)
                    countOfOutputs++;
                else if (incM[i][j] >= 2)
                    countOfOutputs += incM[i][j] / 2;
            out << countOfOutputs << "\n";
        }
        out << "==================\n";

        out << "Half input powers:\n";
        for (int i = 0; i < n; i++) {
            out << i + 1 << ": ";
            int countOfInputs = 0;
            for (int j = 0; j < m; j++)
                if (incM[i][j] == -1)
                    countOfInputs++;
                else if (incM[i][j] >= 2)
                    countOfInputs += incM[i][j] / 2;
            out << countOfInputs << "\n";
        }
        out << "==================\n";
    }

    in.close();
    out.close();
    return 0;
}