const N =80;

function isSafe(board, row, col) {
for (let x = 0; x < col; x++) {
	if (board[row][x] == 1) {
	return false;
	}
}

for (let x = row, y = col; x >= 0 && y >= 0; x--, y--) {
	if (board[x][y] == 1) {
	return false;
	}
}

for (let x = row, y = col; x < N && y >= 0; x++, y--) {
	if (board[x][y] == 1) {
	return false;
	}
}

return true;
}

function solveNQueens(board, col) {
if (col == N) {
	for (let i = 0; i < N; i++) {
	console.log(board[i].join(" "));
	}
	console.log("\n");
	return true;
}

for (let i = 0; i < N; i++) {
	if (isSafe(board, i, col)) {
	board[i][col] = 1; 
	if (solveNQueens(board, col + 1)) {
		return true;
	}
	board[i][col] = 0; 
	}
}
return false;
}

let board = Array(N)
.fill()
.map(() => Array(N).fill(0));

if (!solveNQueens(board, 0)) {
console.log("No solution found");
}

