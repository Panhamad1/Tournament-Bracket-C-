#ifndef UTILS_HPP
#define UTILS_HPP
#include "struct.hpp"

class Tournament {
private:
    Node* root;
public:
    Tournament() {
        root = nullptr;
    }

    // === BUILD ===
    void create(vector<string> players) {
        size_t totalPlayers = players.size();
        int totalLevels = 1;
        size_t temp = 1;
        while (temp < totalPlayers) {
            temp *= 2;
            totalLevels++;
        }
        while (players.size() < temp) {
            players.push_back("BYE");
        }
        size_t amountPlayerRightNow = 0;
        root = buildRecursive(1, totalLevels, players, amountPlayerRightNow);
        assignMatchIDs(root);
    }

    Node* buildRecursive(int currentLevel, int totalLevels, vector<string>& players, size_t& amountPlayerRightNow) {
        if (currentLevel == totalLevels) {
            if (amountPlayerRightNow < players.size()) {
                Node* leaf = new Node(players[amountPlayerRightNow]);
                amountPlayerRightNow++;
                return leaf;
            } else {
                return new Node("BYE");
            }
        }
        Node* node = new Node("");
        node->left = buildRecursive(currentLevel + 1, totalLevels, players, amountPlayerRightNow);
        node->right = buildRecursive(currentLevel + 1, totalLevels, players, amountPlayerRightNow);
        return node;
    }

    void assignMatchIDs(Node* root) {
        if (!root) {
            return;
        }

        queue<Node*> q;
        vector<vector<Node*>> levels;

        q.push(root);

        while (!q.empty()) {
            int n = q.size();
            vector<Node*> level;
            for (int i = 0; i < n; i++) {
                Node* cur = q.front();
                q.pop();
                if (cur->left && cur->right) {
                    level.push_back(cur);
                    q.push(cur->left);
                    q.push(cur->right);
                }
            }
            if (!level.empty()) {
                levels.push_back(level);
            }
        }
        int id = 1;
        for (int i = levels.size() - 1; i >= 0; i--) {
            for (size_t j = 0; j < levels[i].size(); j++) {
                levels[i][j]->matchId = "M" + to_string(id++);
            }
        }
    }


    // === TOURNAMENT EXECUTION ===
    void startTournament() {
        cout << "\n🎮 Starting Tournament!\n";
        queue<Node*> q;
        q.push(root);
        vector<vector<Node*>> levels;
        while (!q.empty()) {
            int n = q.size();
            vector<Node*> level;
            for (int i = 0; i < n; i++) {
                Node* cur = q.front();
                q.pop();
                if (cur->left && cur->right) {
                    level.push_back(cur);
                    q.push(cur->left);
                    q.push(cur->right);
                }
            }
            if (!level.empty()) {
                levels.push_back(level);
            }
        }
        for (int r = levels.size() - 1; r >= 0; r--) {
            if (r == levels.size() - 1) {
                cout << "\nRound 1:\n";
            } else if (r == levels.size() - 2) {
                cout << "\nSemifinal:\n";
            } else if (r == levels.size() - 3) {
                cout << "\nFinal:\n";
            }
            for (auto m : levels[r]) {
                string a = m->left->name;
                string b = m->right->name;
                m->name = randomWinner(a, b);
                cout << m->matchId << ": " << a << " vs " << b
                     << " -> Winner: " << m->name << endl;
            }
        }
        cout << "\n🏆 Champion: " << root->name << " 🎉\n";
    }

    void printFirstRound(Node* node) {
        if (!node) {
            return;
        }
        if (node->left && node->right && node->left->left == nullptr && node->right->left == nullptr) {
            cout << node->matchId << ": " << node->left->name
                 << " vs " << node->right->name << endl;
            return;
        }
        printFirstRound(node->left);
        printFirstRound(node->right);
    }

    // === QUERIES ===
    vector<string> pathToFinal(string player) {
        vector<string> path;
        findPath(root, player, path);
        return path;
    }

    bool findPath(Node* node, string player, vector<string>& path) {
        if (!node) {
            return false;
        }
        if (!node->left && !node->right) {
            return node->name == player;
        }
        if (findPath(node->left, player, path) || findPath(node->right, player, path)) {
            path.push_back(node->matchId);
            return true;
        }
        return false;
    }

    void wouldMeet(string p1, string p2) {
        Node* meet = findMeetingNode(root, p1, p2);
        int totalDepth = getDepth(root);
        int meetDepth = getDepth(meet);
        int roundNum = totalDepth - meetDepth + 1;
        cout << "\n⚔️ " << p1 << " and " << p2
             << " would meet in " << meet->matchId << " (";
        if (roundNum == 1) {
            cout << "Final Round";
        } else if (roundNum == 2) {
            cout << "Semifinal Round";
        } else if (roundNum == 3) {
            cout << "First Round";
        } else {
            cout << "Round " << roundNum;
        }
        cout << ")\n";
    }

    Node* findMeetingNode(Node* node, string p1, string p2) {
        if (!node) {
            return nullptr;
        }
        if (!node->left && !node->right) {
            return (node->name == p1 || node->name == p2) ? node : nullptr;
        }
        Node* left = findMeetingNode(node->left, p1, p2);
        Node* right = findMeetingNode(node->right, p1, p2);
        if (left && right) {
            return node;
        }
        return left ? left : right;
    }

    // === UTILITIES ===
    Node* getRoot() {
        return root;
    }

    int getDepth(Node* node) {
        if (!node) {
            return 0;
        }
        return 1 + max(getDepth(node->left), getDepth(node->right));
    }

    string randomWinner(string a, string b) {
        int r = rand() % 2;
        if (a == "BYE") {
            return b;
        } else if (b == "BYE") {
            return a;
        }
        if (r == 0) {
            return a;
        }
        return b;
    }
};

#endif
