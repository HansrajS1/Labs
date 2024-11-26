#include <iostream>
#include <memory>
#include <queue>
#include <vector>
#include <cstring>
#include <climits>
#include <algorithm>

const int N = 3;
int row[] = {1, 0, -1, 0};
int col[] = {0, -1, 0, 1};

struct Node {
    std::shared_ptr<Node> parent;
    int mat[N][N];
    int x, y;
    int cost;
    int level;
};

std::shared_ptr<Node> newNode(int mat[N][N], int x, int y, int newX, int newY, int level, std::shared_ptr<Node> parent) {
    auto node = std::make_shared<Node>();
    node->parent = parent;
    memcpy(node->mat, mat, sizeof node->mat);
    std::swap(node->mat[x][y], node->mat[newX][newY]);
    node->cost = INT_MAX;
    node->level = level;
    node->x = newX;
    node->y = newY;
    return node;
}

int calculateCost(int initial[N][N], int final[N][N]) {
    int count = 0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (initial[i][j] && initial[i][j] != final[i][j])
                count++;
    return count;
}

void printPath(Node* root) {
    if (root == nullptr)
        return;
    printPath(root->parent.get());
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            std::cout << root->mat[i][j] << " ";
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

struct comp {
    bool operator()(const std::shared_ptr<Node>& lhs, const std::shared_ptr<Node>& rhs) const {
        return (lhs->cost + lhs->level) > (rhs->cost + rhs->level);
    }
};

bool isSafe(int x, int y) {
    return (x >= 0 && x < N && y >= 0 && y < N);
}

void solve(int initial[N][N], int x, int y, int final[N][N]) {
    std::priority_queue<std::shared_ptr<Node>, std::vector<std::shared_ptr<Node>>, comp> pq;
    auto root = newNode(initial, x, y, x, y, 0, nullptr);
    root->cost = calculateCost(initial, final);
    pq.push(root);

    while (!pq.empty()) {
        auto min = pq.top();
        pq.pop();
        if (min->cost == 0) {
            printPath(min.get());
            return;
        }
        for (int i = 0; i < 4; i++) {
            int newX = min->x + row[i];
            int newY = min->y + col[i];
            if (isSafe(newX, newY)) {
                auto child = newNode(min->mat, min->x, min->y, newX, newY, min->level + 1, min);
                child->cost = calculateCost(child->mat, final);
                pq.push(child);
            }
        }
    }
}

int main() {
    int initial[N][N] = {{1, 2, 3}, {5, 6, 0}, {7, 8, 4}};
    int final[N][N] = {{1, 2, 3}, {5, 8, 6}, {0, 7, 4}};
    int x = 1, y = 2;
    solve(initial, x, y, final);
    return 0;
}
