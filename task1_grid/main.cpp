#ifndef PCH_H
#define PCH_H

// TODO: add headers that you want to pre-compile here

#endif //PCH_H

#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

struct operators {
	char type;
	int row;
	int col;
	int size;
};
struct operators operatorsArray[100];

int checkBorder(struct operators *operatorsArray, int berror, int n, int m) {
	if (operatorsArray->type == '-') {
		for (int i = 0; i < operatorsArray->size + 1; i++) {
			if (operatorsArray->col - i <= 0 || operatorsArray->col + i > m) {
				berror = 1;
				return berror;
			}
		}
	}
	else if(operatorsArray->type == '+' || operatorsArray->type == 'x' || operatorsArray->type == '/') {
		for (int i = 0; i < operatorsArray->size + 1; i++) {
			if (operatorsArray->row - i <= 0 || operatorsArray->row + i > n || operatorsArray->col - i <= 0 || operatorsArray->col + i > m) {
				berror = 1;
				return berror;
			}
		}
	}
	berror = 0;
	return berror;
}

int checkConflict(struct operators *operatorsArray, int **grid, int cerror, int n, int m) {

	int centerrow = operatorsArray->row - 1;
	int centercol = operatorsArray->col - 1;

	if (operatorsArray->type == '-') {
		for (int i = 0; i < operatorsArray->size + 1; i++) {
			if (grid[centerrow][centercol - i] != -1)cerror = 1;
			if (centercol - i - 1 < 0)break;
		}
		for (int i = 0; i < operatorsArray->size + 1; i++) {
			if (grid[centerrow][centercol + i] != -1)cerror = 1;
			if (centercol + i + 1 >= m - 1)break;
		}
	}

	if (operatorsArray->type == '+') {
		for (int i = 0; i < operatorsArray->size + 1; i++) {
			if (grid[centerrow][centercol - i] != -1)cerror = 1;
			if (centercol - i - 1 < 0)break;
		}
		for (int i = 0; i < operatorsArray->size + 1; i++) {
			if (grid[centerrow][centercol + i] != -1)cerror = 1;
			if (centercol + i + 1 >= m - 1)break;
		}
		for (int i = 0; i < operatorsArray->size + 1; i++) {
			if (grid[centerrow - i][centercol] != -1)cerror = 1;
			if (centerrow - i - 1 < 0)break;
		}
		for (int i = 0; i < operatorsArray->size + 1; i++) {
			if (grid[centerrow + i][centercol] != -1)cerror = 1;
			if (centerrow + i + 1 >= n - 1)break;
		}
	}

	if (operatorsArray->type == 'x') {
		for (int i = 0; i < operatorsArray->size + 1; i++) {
			if (grid[centerrow - i][centercol - i] != -1)cerror = 1;
			if (centerrow - i - 1 < 0 || centercol - i - 1 < 0)break;
		}
		for (int i = 0; i < operatorsArray->size + 1; i++) {
			if (grid[centerrow + i][centercol + i] != -1)cerror = 1;
			if (centerrow + i + 1 >= n - 1 || centercol + i + 1 >= m - 1)break;
		}
		for (int i = 0; i < operatorsArray->size + 1; i++) {
			if (grid[centerrow - i][centercol + i] != -1)cerror = 1;
			if (centerrow - i - 1 < 0 || centercol + i + 1 >= m - 1)break;
		}
		for (int i = 0; i < operatorsArray->size + 1; i++) {
			if (grid[centerrow + i][centercol - i] != -1)cerror = 1;
			if (centerrow + i + 1 >= n - 1 || centercol - i - 1 < 0)break;
		}
	}

	if (operatorsArray->type == '/') {
		for (int i = 0; i < operatorsArray->size + 1; i++) {
			if (grid[centerrow - i][centercol + i] != -1)cerror = 1;
			if (centerrow - i - 1 < 0 || centercol + i + 1 >= m - 1)break;
		}
		for (int i = 0; i < operatorsArray->size + 1; i++) {
			if (grid[centerrow + i][centercol - i] != -1)cerror = 1;
			if (centerrow + i + 1 >= n - 1 || centercol - i - 1 < 0)break;
		}
	}

	//RESULT
	if (cerror == 1)return cerror;
	else {
		cerror = 0;
		return cerror;
	}
}

void placeOp(struct operators *operatorsArray, int **grid, int opnum) {

	int centerrow = operatorsArray->row - 1;
	int centercol = operatorsArray->col - 1;

	if (operatorsArray->type == '-') {
		for (int k = 0; k < operatorsArray->size + 1; k++) {
			grid[centerrow][centercol - k] = opnum;
			grid[centerrow][centercol + k] = opnum;
		}
	}
	else if (operatorsArray->type == '+') {
		for (int k = 0; k < operatorsArray->size + 1; k++) {
			grid[centerrow - k][centercol] = opnum;
			grid[centerrow + k][centercol] = opnum;
			grid[centerrow][centercol - k] = opnum;
			grid[centerrow][centercol + k] = opnum;
		}
	}
	else if (operatorsArray->type == 'x') {
		for (int k = 0; k < operatorsArray->size + 1; k++) {
			grid[centerrow - k][centercol - k] = opnum;
			grid[centerrow + k][centercol + k] = opnum;
			grid[centerrow + k][centercol - k] = opnum;
			grid[centerrow - k][centercol + k] = opnum;
		}
	}
	else if (operatorsArray->type == '/') {
		for (int k = 0; k < operatorsArray->size + 1; k++) {
			grid[centerrow + k][centercol - k] = opnum;
			grid[centerrow - k][centercol + k] = opnum;
		}
	}
}

int main(int argc, char *argv[])
{
	/*if (argc > 1) {
		cout << "argv[1] = " << argv[1] << endl;
	}
	else {
		cout << "No file name entered. Exiting...";
		return -1;
	}
	ifstream infile(argv[1]); //open the file
	if (infile.is_open() && infile.good()) {
		cout << "File is now open!\nContains:\n";
		string line = "";
		while (getline(infile, line)) {
			cout << line << '\n';
		}
	}
	else {
		cout << "Failed to open file..";
	}*/
	
	FILE *fp1 = fopen(argv[1], "r");
	FILE *fp2 = fopen(argv[2], "r");

	int berror = 0, cerror = 0;
	int n, m;
	int counter = 0;
	int j;
	/*********************************************************                            CREATE GRID                             ***********************************************************/

	fscanf(fp1,"%d%d\n", &n, &m);

	int **grid = (int **)malloc(n * sizeof(int *));
	for (int i = 0; i < n; i++) {
		grid[i] = (int *)malloc(m * sizeof(int));
	}
	for (int i = 0; i < n; i++) {
		for (j = 0; j < m; j++) {
			grid[i][j] = -1;
		}
	}

	cout << "A grid is created: " << n << " " << m << "\n";

	/********************************************************                            PLACE OPERATORS                            ********************************************************/

	while (!feof(fp1)) {

		fscanf(fp1,"%c%d%d%d\n", &operatorsArray[counter].type, &operatorsArray[counter].row, &operatorsArray[counter].col, &operatorsArray[counter].size);
		//cout << "\n" << operatorsArray[counter].type << operatorsArray[counter].row << operatorsArray[counter].col << operatorsArray[counter].size << "\n";
		//ERROR CHECKS

		berror = checkBorder(&operatorsArray[counter], berror, n, m);
		cerror = checkConflict(&operatorsArray[counter], grid, cerror, n, m);

		if (berror == 0 && cerror == 0 && (operatorsArray[counter].type == '-' || operatorsArray[counter].type == '+' || operatorsArray[counter].type == 'x' || operatorsArray[counter].type == '/')) {
			placeOp(&operatorsArray[counter], grid, counter);
			cout << "SUCCESS: Operator " << operatorsArray[counter].type << " with size " << operatorsArray[counter].size << " is placed on (" << operatorsArray[counter].row << "," << operatorsArray[counter].col << ").\n";
		}
		if (cerror == 1)cout << "CONFLICT ERROR: Operator " << operatorsArray[counter].type << " with size " << operatorsArray[counter].size << " can not be placed on (" << operatorsArray[counter].row << "," << operatorsArray[counter].col << ").\n";
		if (berror == 1)cout << "BORDER ERROR: Operator " << operatorsArray[counter].type << " with size " << operatorsArray[counter].size << " can not be placed on (" << operatorsArray[counter].row << "," << operatorsArray[counter].col << ").\n";
		counter++;
	}
	cerror = 0;
	berror = 0;
	/*for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (grid[i][j] != -1)cout << " ";
			cout << grid[i][j];
		}
		cout << "\n";
	}*/
	fclose(fp1);

	/****************************************************                               READ INSTRUCTIONS                               *****************************************************/

	char ins[4];
	int insrow, inscolumn, move_by;
	int opNum;
	int erase = -1;
	while (!feof(fp2)) {

		fscanf(fp2, "%s%d%d%d\n", ins, &insrow, &inscolumn, &move_by);

		insrow--;
		inscolumn--;

		opNum = grid[insrow][inscolumn];

		//DELETE
		placeOp(&operatorsArray[opNum], grid, erase);

		if (ins[2] == 'U')operatorsArray[opNum].row = operatorsArray[opNum].row - move_by;
		else if (ins[2] == 'D')operatorsArray[opNum].row = operatorsArray[opNum].row + move_by;
		else if (ins[2] == 'R')operatorsArray[opNum].col = operatorsArray[opNum].col + move_by;
		else if (ins[2] == 'L')operatorsArray[opNum].col = operatorsArray[opNum].col - move_by;

		berror = checkBorder(&operatorsArray[opNum], berror, n, m);
		cerror = checkConflict(&operatorsArray[opNum], grid, cerror, n, m);

		if (cerror == 1) {
			if (ins[2] == 'U')cout << "CONFLICT ERROR: " << operatorsArray[opNum].type << " can not be moved from (" << operatorsArray[opNum].row + move_by << "," << operatorsArray[opNum].col << ") to (" << operatorsArray[opNum].row << "," << operatorsArray[opNum].col << ").\n";
			if (ins[2] == 'D')cout << "CONFLICT ERROR: " << operatorsArray[opNum].type << " can not be moved from (" << operatorsArray[opNum].row - move_by << "," << operatorsArray[opNum].col << ") to (" << operatorsArray[opNum].row << "," << operatorsArray[opNum].col << ").\n";
			if (ins[2] == 'R')cout << "CONFLICT ERROR: " << operatorsArray[opNum].type << " can not be moved from (" << operatorsArray[opNum].row << "," << operatorsArray[opNum].col - move_by << ") to (" << operatorsArray[opNum].row << "," << operatorsArray[opNum].col << ").\n";
			if (ins[2] == 'L')cout << "CONFLICT ERROR: " << operatorsArray[opNum].type << " can not be moved from (" << operatorsArray[opNum].row << "," << operatorsArray[opNum].col + move_by << ") to (" << operatorsArray[opNum].row << "," << operatorsArray[opNum].col << ").\n";

		}
		if (berror == 1) {
			if (ins[2] == 'U')cout << "BORDER ERROR: " << operatorsArray[opNum].type << " can not be moved from (" << operatorsArray[opNum].row + move_by << "," << operatorsArray[opNum].col << ") to (" << operatorsArray[opNum].row << "," << operatorsArray[opNum].col << ").\n";
			if (ins[2] == 'D')cout << "BORDER ERROR: " << operatorsArray[opNum].type << " can not be moved from (" << operatorsArray[opNum].row - move_by << "," << operatorsArray[opNum].col << ") to (" << operatorsArray[opNum].row << "," << operatorsArray[opNum].col << ").\n";
			if (ins[2] == 'R')cout << "BORDER ERROR: " << operatorsArray[opNum].type << " can not be moved from (" << operatorsArray[opNum].row << "," << operatorsArray[opNum].col - move_by << ") to (" << operatorsArray[opNum].row << "," << operatorsArray[opNum].col << ").\n";
			if (ins[2] == 'L')cout << "BORDER ERROR: " << operatorsArray[opNum].type << " can not be moved from (" << operatorsArray[opNum].row << "," << operatorsArray[opNum].col + move_by << ") to (" << operatorsArray[opNum].row << "," << operatorsArray[opNum].col << ").\n";

		}
		if (berror == 0 && cerror == 0) {
			placeOp(&operatorsArray[opNum], grid, opNum);
			if (ins[2] == 'U')cout << "SUCCESS: " << operatorsArray[opNum].type << " moved from (" << operatorsArray[opNum].row + move_by << "," << operatorsArray[opNum].col << ") to (" << operatorsArray[opNum].row << "," << operatorsArray[opNum].col << ").\n";
			if (ins[2] == 'D')cout << "SUCCESS: " << operatorsArray[opNum].type << " moved from (" << operatorsArray[opNum].row - move_by << "," << operatorsArray[opNum].col << ") to (" << operatorsArray[opNum].row << "," << operatorsArray[opNum].col << ").\n";
			if (ins[2] == 'R')cout << "SUCCESS: " << operatorsArray[opNum].type << " moved from (" << operatorsArray[opNum].row << "," << operatorsArray[opNum].col - move_by << ") to (" << operatorsArray[opNum].row << "," << operatorsArray[opNum].col << ").\n";
			if (ins[2] == 'L')cout << "SUCCESS: " << operatorsArray[opNum].type << " moved from (" << operatorsArray[opNum].row << "," << operatorsArray[opNum].col + move_by << ") to (" << operatorsArray[opNum].row << "," << operatorsArray[opNum].col << ").\n";
		}
		else {

			if (ins[2] == 'U')operatorsArray[opNum].row = operatorsArray[opNum].row + move_by;
			else if (ins[2] == 'D')operatorsArray[opNum].row = operatorsArray[opNum].row - move_by;
			else if (ins[2] == 'R')operatorsArray[opNum].col = operatorsArray[opNum].col - move_by;
			else if (ins[2] == 'L')operatorsArray[opNum].col = operatorsArray[opNum].col + move_by;

			placeOp(&operatorsArray[opNum], grid, opNum);
		}
		cerror = 0;
		berror = 0;
		ins[2] = '0';
	}
	fclose(fp2);
	return 0;
}
