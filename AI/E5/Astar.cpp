#include <bits/stdc++.h>
using namespace std;
#define ROW 9
#define COL 10
typedef pair<int, int> Pair;
typedef pair<double, pair<int, int>> pPair;
struct cell {
    int parent_i, parent_j;
    double f, g, h;
};

bool isValid(int row, int col) { return (row >= 0) && (row < ROW) && (col >= 0) && (col < COL); }
bool isUnBlocked(int grid[][COL], int row, int col) { return grid[row][col] == 1; }
bool isDestination(int row, int col, Pair dest) { return row == dest.first && col == dest.second; }
double calculateHValue(int row, int col, Pair dest) { return sqrt((row - dest.first) * (row - dest.first) + (col - dest.second) * (col - dest.second)); }
void tracePath(cell cellDetails[][COL], Pair dest) {
    int row = dest.first, col = dest.second;
    stack<Pair> Path;
    while (!(cellDetails[row][col].parent_i == row && cellDetails[row][col].parent_j == col)) {
        Path.push(make_pair(row, col));
        int temp_row = cellDetails[row][col].parent_i, temp_col = cellDetails[row][col].parent_j;
        row = temp_row, col = temp_col;
    }
    Path.push(make_pair(row, col));
    while (!Path.empty()) {
        printf("-> (%d,%d) ", Path.top().first, Path.top().second);
        Path.pop();
    }
}
void aStarSearch(int grid[][COL], Pair src, Pair dest) {
    if (!isValid(src.first, src.second) || !isValid(dest.first, dest.second) || !isUnBlocked(grid, src.first, src.second) || !isUnBlocked(grid, dest.first, dest.second)) {
        printf("Source or destination is invalid or blocked\n");
        return;
    }
    if (isDestination(src.first, src.second, dest)) {
        printf("We are already at the destination\n");
        return;
    }
    bool closedList[ROW][COL];
    memset(closedList, false, sizeof(closedList));
    cell cellDetails[ROW][COL];
    int i, j;
    for (i = 0; i < ROW; i++) for (j = 0; j < COL; j++) cellDetails[i][j] = { -1, -1, FLT_MAX, FLT_MAX, FLT_MAX };
    i = src.first, j = src.second;
    cellDetails[i][j] = { i, j, 0.0, 0.0, 0.0 };
    set<pPair> openList;
    openList.insert(make_pair(0.0, make_pair(i, j)));
    bool foundDest = false;
    while (!openList.empty()) {
        pPair p = *openList.begin();
        openList.erase(openList.begin());
        i = p.second.first, j = p.second.second;
        closedList[i][j] = true;
        double gNew, hNew, fNew;
        int dirs[8][2] = { {-1, 0}, {1, 0}, {0, 1}, {0, -1}, {-1, 1}, {-1, -1}, {1, 1}, {1, -1} };
        for (auto d : dirs) {
            int ni = i + d[0], nj = j + d[1];
            if (isValid(ni, nj)) {
                if (isDestination(ni, nj, dest)) {
                    cellDetails[ni][nj].parent_i = i, cellDetails[ni][nj].parent_j = j;
                    printf("The destination cell is found\n");
                    tracePath(cellDetails, dest);
                    foundDest = true;
                    return;
                } else if (!closedList[ni][nj] && isUnBlocked(grid, ni, nj)) {
                    gNew = cellDetails[i][j].g + (d[0] == 0 || d[1] == 0 ? 1.0 : 1.414);
                    hNew = calculateHValue(ni, nj, dest);
                    fNew = gNew + hNew;
                    if (cellDetails[ni][nj].f == FLT_MAX || cellDetails[ni][nj].f > fNew) {
                        openList.insert(make_pair(fNew, make_pair(ni, nj)));
                        cellDetails[ni][nj] = { i, j, fNew, gNew, hNew };
                    }
                }
            }
        }
    }
    if (!foundDest) printf("Failed to find the Destination Cell\n");
}
int main() {
    int grid[ROW][COL] = { { 1, 0, 1, 1, 1, 1, 0, 1, 1, 1 }, { 1, 1, 1, 0, 1, 1, 1, 0, 1, 1 }, { 1, 1, 1, 0, 1, 1, 0, 1, 0, 1 }, { 0, 0, 1, 0, 1, 0, 0, 0, 0, 1 }, { 1, 1, 1, 0, 1, 1, 1, 0, 1, 0 }, { 1, 0, 1, 1, 1, 1, 0, 1, 0, 0 }, { 1, 0, 0, 0, 0, 1, 0, 0, 0, 1 }, { 1, 0, 1, 1, 1, 1, 0, 1, 1, 1 }, { 1, 1, 1, 0, 0, 0, 1, 0, 0, 1 } };
    Pair src = make_pair(8, 0), dest = make_pair(0, 0);
    aStarSearch(grid, src, dest);
    return 0;
}
