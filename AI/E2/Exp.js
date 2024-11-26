const N = 3;
class Node {
    constructor(mat, x, y, level, parent) {
        this.parent = parent;      
        this.mat = mat.map(row => [...row]);      
        this.x = x;
        this.y = y;
        this.cost = Infinity;
        this.level = level;
    }
}

function printMatrix(mat) {
    for (let i = 0; i < N; i++) {
        console.log(mat[i].join(' '));
    }
    console.log('\n');
}

function newNode(mat, x, y, newX, newY, level, parent) {
    const node = new Node(mat, x, y, level, parent);    
    [node.mat[x][y], node.mat[newX][newY]] = [node.mat[newX][newY], node.mat[x][y]];
    node.x = newX;
    node.y = newY;
    return node;
}

const row = [1, 0, -1, 0];

const col = [0, -1, 0, 1];

function calculateCost(initial, final) {
    let count = 0;
    for (let i = 0; i < N; i++)
        for (let j = 0; j < N; j++)
            if (initial[i][j] && initial[i][j] !== final[i][j])
                count++;
    return count;
}
function isSafe(x, y) {
    return x >= 0 && x < N && y >= 0 && y < N;
}

function printPath(root) {
    if (!root) return;
    printPath(root.parent);
    printMatrix(root.mat);
}
class comp {
    static compare(lhs, rhs) {
        return (lhs.cost + lhs.level) > (rhs.cost + rhs.level);
    }
}

function solve(initial, x, y, final) {
    const pq = [];
    const root = newNode(initial, x, y, x, y, 0, null);
    root.cost = calculateCost(initial, final);
    pq.push(root);
    while (pq.length > 0) {
        pq.sort(comp.compare);
        const min = pq.shift();
        if (min.cost === 0) {
            printPath(min);
            return;
        }
        for (let i = 0; i < 4; i++) {
            if (isSafe(min.x + row[i], min.y + col[i])) {       
                const child = newNode(min.mat, min.x,
                    min.y, min.x + row[i],
                    min.y + col[i],
                    min.level + 1, min);
                child.cost = calculateCost(child.mat, final);
                pq.push(child);
            }
        }
    }
}
const initial = [
    [1, 2, 0],
    [3, 4, 5],
    [6, 7, 8]
];
const final = [
    [1, 4, 2],
    [3, 0, 5],
    [6, 7, 8]
];
const startX = 1, startY = 2;
solve(initial, startX, startY, final);