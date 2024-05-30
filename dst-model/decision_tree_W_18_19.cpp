#include <chrono>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;
using namespace std::chrono;

// Structure to represent a node in the decision tree
struct Node {
    string teamName;
    double psPerGame;
    Node* left;
    Node* right;

    Node(const string& name, double ps) : teamName(name), psPerGame(ps), left(nullptr), right(nullptr) {}
};

//this function is to load the data from the csv
void LoadCSV(const string& filename, vector<Node*>& teams) {
    ifstream file(filename);
    string line;
    getline(file, line); // skip header

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

// function to build
Node* BuildDecisionTree(vector<Node*>& teams) {
    if (teams.size() == 1) {
        return teams[0];
    }

    // find the team with the highest offensive output
    auto maxPsTeam = max_element(teams.begin(), teams.end(), [](const Node* a, const Node* b) {
        return a->psPerGame < b->psPerGame;
    });

    // this will split the teams
    vector<Node*> leftTeams(teams.begin(), maxPsTeam);
    vector<Node*> rightTeams(maxPsTeam + 1, teams.end());

    // Recursively build left and right subtrees
    Node* root = new Node((*maxPsTeam)->teamName, (*maxPsTeam)->psPerGame);
    root->left = BuildDecisionTree(leftTeams);
    root->right = BuildDecisionTree(rightTeams);

    return root;
}

// Function to predict the winner of the playoffs
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

    // start the time
    auto start = high_resolution_clock::now();

    LoadCSV("../web/NBA_Team_Stats_W_2018-2019_PS_G_PA_G.csv", teams);

    // tree
    Node* root = BuildDecisionTree(teams);

    // use the predict winner
    string winner = PredictWinner(root);
    cout << "Predicted winner: " << winner << endl;

    // end measuring time
    auto end = high_resolution_clock::now();

    // return duration after ending
    auto duration = duration_cast<milliseconds>(end - start);
    cout << "Execution time: " << duration.count() << " milliseconds" << endl;

    // used for memory cleanup 
    // can also use std::unique_ptr
    for (Node* team : teams) {
        delete team;
    }

    return 0;
}