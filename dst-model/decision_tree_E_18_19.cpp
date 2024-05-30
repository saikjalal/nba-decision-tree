#include <chrono>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;
using namespace std::chrono;


struct Node {
    string teamName;
    double psPerGame;
    Node* left;
    Node* right;

    Node(const string& name, double ps) : teamName(name), psPerGame(ps), left(nullptr), right(nullptr) {}
};


void LoadCSV(const string& filename, vector<Node*>& teams) {
    ifstream file(filename);
    string line;
    getline(file, line); 

    while (getline(file, line)) {
        stringstream ss(line);
        string value;
        string teamName;
        double psPerGame;
        int colIndex = 0;

        while (getline(ss, value, ',')) {
            if (colIndex == 0) {
                teamName = value;
            } else if (colIndex == 5) {
                psPerGame = stod(value);
            }
            ++colIndex;
        }

        teams.push_back(new Node(teamName, psPerGame));
    }
}

Node* BuildDecisionTree(vector<Node*>& teams) {
    if (teams.size() == 1) {
        return teams[0];
    }

    auto maxPsTeam = max_element(teams.begin(), teams.end(), [](const Node* a, const Node* b) {
        return a->psPerGame < b->psPerGame;
    });

    vector<Node*> leftTeams(teams.begin(), maxPsTeam);
    size_t maxIndex = distance(teams.begin(), maxPsTeam);
    vector<Node*> rightTeams(teams.begin() + maxIndex + 1, teams.end());

    Node* root = new Node((*maxPsTeam)->teamName, (*maxPsTeam)->psPerGame);
    root->left = BuildDecisionTree(leftTeams);
    root->right = BuildDecisionTree(rightTeams);

    return root;
}

string PredictWinner(Node* root) {
    while (root->left != nullptr && root->right != nullptr) {
        if (root->left->psPerGame > root->right->psPerGame) {
            root = root->left;
        } else {
            root = root->right;
        }
    }
    return root->teamName;
}

int main() {
    vector<Node*> teams;

    auto start = high_resolution_clock::now();

    LoadCSV("../web/NBA_Team_Stats_E_2018-2019_PS_G_PA_G.csv", teams);

    Node* root = BuildDecisionTree(teams);

    string winner = PredictWinner(root);
    cout << "Predicted winner: " << winner << endl;

    auto end = high_resolution_clock::now();

    auto duration = duration_cast<milliseconds>(end - start);
    cout << "Execution time: " << duration.count() << " milliseconds" << endl;

    for (Node* team : teams) {
        delete team;
    }

    return 0;
}