#include <iostream>
#include "pqueue.h"
#include <fstream>
#include <string>
#include <sstream>

inline void input1();
inline void input2();
inline void input3();
void knapsack(int* w, int** val, int n, int m, int* vals);
int max(int a, int b);
void BTknapsack(int* btval, int level, int totalProfit, int totalWeight, int& maxProfit, int m, int* w, int* p, int n);
bool Promising(int* btval, int level, int totalProfit, int totalWeight, int& maxProfit, int m, int* w, int* p, int n);
void BBknapsack(int level, int totalProfit, int totalWeight, int& maxProfit, int m, int* w, int* p, int n);
int bound(int level, int totalProfit, int totalWeight, int m, int* w, int* p, int n);

int m, n;
// 1.
int *weights_d;
int *vals_d;
int **val_d;
// 2.
int *weights;
int *btval;
int *vals;
// 3.
int *weights_t;
int *vals_t;
// result print to text
std::ofstream ofs("result.txt", std::ofstream::out);

int main() {
	int maxProfit = 0;
	ofs << "2017-2 Algorithms Programming Project 2, #21 Han-Byul Kim" << std::endl;
	ofs << "The Detail execution process is on Console." << std::endl;

	// 1. Dynamic Programming
	input1();
	std::cout << "1. Dynamic Programming(result table)" << std::endl;
	knapsack(weights_d, val_d, n, m, vals_d);
	std::cout << std::endl;

	// 2. Backtracking
	input2();
	std::cout << "2. Backtracking" << std::endl;
	BTknapsack(btval, 0, 0, 0, maxProfit, m, weights, vals, n);
	std::cout << std::endl;

	// 3. Branch & Bound(Best First Search)
	input3();
	std::cout << "3. Branch & Bound" << std::endl;
	maxProfit = 0;
	BBknapsack(0, 0, 0, maxProfit, m, weights_t, vals_t, n);

	delete[] weights_d;
	delete[] vals_d;
	for (int i = 0; i <= n; i++) delete[] val_d[i];
	delete[] val_d;
	delete[] weights;
	delete[] vals;
	delete[] btval;
	delete[] weights_t;
	delete[] vals_t;

	system("pause");

	return 0;
}

inline void input1() {
	// 1. Dynamic Knapsack variables input
	std::ifstream ifs1("1.txt", std::ifstream::in);
	std::string m_line;
	std::string n_line;
	std::string weight1;
	std::string val_1;
	int i = 0;

	// reading text input files
	std::cout << "1. Reading Dynamic Knapsack Input files..." << std::endl;
	// getting m	// weight capacity
	getline(ifs1, m_line);
	m = (int)stoi(m_line);
	std::cout << "m : " << m << std::endl;
	// getting n	// number of things
	getline(ifs1, n_line);
	n = (int)stoi(n_line);
	std::cout << "n : " << n << std::endl;
	// getting weight	// Weight values(The first zero is blank)
	getline(ifs1, weight1);
	std::istringstream iss(weight1);
	weights_d = new int[n + 1];
	weights_d[0] = 0;
	std::cout << "Weights : ";
	do {
		i++;
		std::string subs;
		iss >> subs;
		weights_d[i] = (int)stoi(subs);
		std::cout << weights_d[i] << " ";
	} while (i < n);
	std::cout << std::endl;
	i = 0;
	// getting profit values	// Priofit Values(The first zero is blank)
	getline(ifs1, val_1);
	std::istringstream iss2(val_1);
	vals_d = new int[n + 1];
	vals_d[0] = 0;
	std::cout << "Profits : ";
	do {
		i++;
		std::string subs;
		iss2 >> subs;
		vals_d[i] = (int)stoi(subs);
		std::cout << vals_d[i] << " ";
	} while (i < n);
	std::cout << std::endl;
	// making result table
	val_d = new int*[n + 1];
	for (int i = 0; i <= n; i++) val_d[i] = new int[m + 1];
	ifs1.close();
	std::cout << std::endl;
}

inline void input2() {
	// 2. BTknapsack variables input
	std::ifstream ifs1("2.txt", std::ifstream::in);
	std::string m_line;
	std::string n_line;
	std::string weight1;
	std::string val_1;
	int i = 0;

	// reading text input files
	std::cout << "2. Reading BTknapsack Input files..." << std::endl;
	// getting m	// weight capacity
	getline(ifs1, m_line);
	m = (int)stoi(m_line);
	std::cout << "m : " << m << std::endl;
	// getting n	// number of things
	getline(ifs1, n_line);
	n = (int)stoi(n_line);
	std::cout << "n : " << n << std::endl;
	// getting weight	// Weight values(The first zero is blank)
	getline(ifs1, weight1);
	std::istringstream iss(weight1);
	weights = new int[n + 1];
	weights[0] = 0;
	std::cout << "Weights : ";
	do {
		i++;
		std::string subs;
		iss >> subs;
		weights[i] = (int)stoi(subs);
		std::cout << weights[i] << " ";
	} while (i < n);
	std::cout << std::endl;
	i = 0;
	// getting profit values	// Priofit Values(The first zero is blank)
	getline(ifs1, val_1);
	std::istringstream iss2(val_1);
	vals = new int[n + 1];
	vals[0] = 0;
	std::cout << "Profits : ";
	do {
		i++;
		std::string subs;
		iss2 >> subs;
		vals[i] = (int)stoi(subs);
		std::cout << vals[i] << " ";
	} while (i < n);
	std::cout << std::endl;
	// making result table
	btval = new int[n + 1];
	ifs1.close();
	std::cout << std::endl;
}

inline void input3() {
	// 3. BBknapsack variables input
	std::ifstream ifs1("3.txt", std::ifstream::in);
	std::string m_line;
	std::string n_line;
	std::string weight1;
	std::string val_1;
	int i = 0;

	// reading text input files
	std::cout << "3. Reading BBknapsack Input files..." << std::endl;
	// getting m	// weight capacity
	getline(ifs1, m_line);
	m = (int)stoi(m_line);
	std::cout << "m : " << m << std::endl;
	// getting n	// number of things
	getline(ifs1, n_line);
	n = (int)stoi(n_line);
	std::cout << "n : " << n << std::endl;
	// getting weight	// Weight values(The first zero is blank)
	getline(ifs1, weight1);
	std::istringstream iss(weight1);
	weights_t = new int[n + 1];
	weights_t[0] = 0;
	std::cout << "Weights : ";
	do {
		i++;
		std::string subs;
		iss >> subs;
		weights_t[i] = (int)stoi(subs);
		std::cout << weights_t[i] << " ";
	} while (i < n);
	std::cout << std::endl;
	i = 0;
	// getting profit values	// Priofit Values(The first zero is blank)
	getline(ifs1, val_1);
	std::istringstream iss2(val_1);
	vals_t = new int[n + 1];
	vals_t[0] = 0;
	std::cout << "Profits : ";
	do {
		i++;
		std::string subs;
		iss2 >> subs;
		vals_t[i] = (int)stoi(subs);
		std::cout << vals_t[i] << " ";
	} while (i < n);
	std::cout << std::endl;
	ifs1.close();
	std::cout << std::endl;
}

void knapsack(int* w, int** val, int n, int m, int* vals) {
	// The first line of table
	for (int j = 0; j <= m; j++) // nothing contained
		val[0][j] = 0;

	// Calculating Values
	for (int i = 1; i <= n; i++) { // start with 1st object
		for (int j = 0; j <= w[i] - 1; j++)		// value before the weight
			val[i][j] = val[i - 1][j];

		for (int j = w[i]; j <= m; j++)		// value after the weight
			val[i][j] = max(val[i - 1][j - w[i]] + vals[i], val[i - 1][j]);	// finding maximum between combinations
	}

	// Print Elements
	for (int i = 0; i <= n; i++) {
		for (int j = 0; j <= m; j++) std::cout << val[i][j] << " ";
		std::cout << std::endl;
	}
}

int max(int a, int b) {
	if (a>b) return a;
	else return b;
}

void BTknapsack(int* btval, int level, int totalProfit, int totalWeight, int& maxProfit, int m, int* w, int* p, int n) {
	if (totalWeight <= m && level == n) { // answer
		std::cout << "Contained(1) or not(0)" << std::endl;
		for (int i = 1; i <= n; i++) std::cout << i << " | ";
		std::cout << std::endl;
		for (int i = 1; i <= n; i++) std::cout << btval[i] << " | ";
		std::cout << std::endl;
	}

	if (totalWeight <= m && totalProfit > maxProfit) maxProfit = totalProfit;	// updating max profit

	if (Promising(btval, level, totalProfit, totalWeight, maxProfit, m, w, p, n)) {
		// Left Child
		btval[level + 1] = 1;
		BTknapsack(btval, level + 1, totalProfit + p[level + 1], totalWeight + w[level + 1], maxProfit, m, w, p, n);
		// Right Child
		btval[level + 1] = 0;
		BTknapsack(btval, level + 1, totalProfit, totalWeight, maxProfit, m, w, p, n);
	}
}

bool Promising(int* btval, int level, int totalProfit, int totalWeight, int& maxProfit, int m, int* w, int* p, int n) {		// Calculate promising
	if (totalWeight >= m) return false;
	int j = level + 1;
	int upperBound = totalProfit;
	int weightLimit = totalWeight;

	while (j <= n && weightLimit + w[j] <= m) {	//calculating bounds before the limit of weight
		weightLimit += w[j];
		upperBound += p[j];
		j++;
	}
	if (j <= n) upperBound += (m - weightLimit)*p[j] / w[j];	// calculate promising

	return (upperBound > maxProfit);
}

void BBknapsack(int level, int totalProfit, int totalWeight, int& maxProfit, int m, int* w, int* p, int n) {
	PQ a;	// my own pq

			// root node
	int b = bound(level, totalProfit, totalWeight, m, w, p, n);	// bound on root
	a.insert(level, 0, totalProfit, totalWeight, b);	// add root node to pq

	while (!a.empty()) {
		int lr = 0;
		a.remove(level, lr, totalProfit, totalWeight, b);	// Popping first element on pq
		if (level == n) {	// Printing Result
			std::cout << std::endl;
			std::cout << "----------------------------------" << std::endl;
			std::cout << "result : " << std::endl;
			std::cout << "level : " << level << std::endl;
			std::cout << "totalProfit : " << totalProfit << std::endl;
			std::cout << "totalWeight : " << totalWeight << std::endl;
			std::cout << "bound : " << b << std::endl;
			return;
		}

		std::cout << "remove : " << level << " " << lr << " " << totalProfit << " " << totalWeight << " " << b << std::endl;
		if (b > maxProfit && level < n) {
			// left child
			lr = level*lr + 1;
			if (totalWeight + w[level + 1] <= m) {
				b = bound(level + 1, totalProfit + p[level + 1], totalWeight + w[level + 1], m, w, p, n);
				a.insert(level + 1, lr, totalProfit + p[level + 1], totalWeight + w[level + 1], b);	// inserting left child in queue
			}

			// right child
			lr++;
			if (totalWeight <= m) {
				b = bound(level + 1, totalProfit, totalWeight, m, w, p, n);
				a.insert(level + 1, lr, totalProfit, totalWeight, b);	//inserting right child in queue
			}
		}

		a.print();	// print elements in queue
		std::cout << "level : " << level << std::endl;
	}
}

int bound(int level, int totalProfit, int totalWeight, int m, int* w, int* p, int n) { // Calculating Upper Bounds
	int j = level + 1;
	int upperBound = totalProfit;
	int weightLimit = totalWeight;

	while (j <= n && weightLimit + w[j] <= m) {	//calculating bounds before the limit of weight
		weightLimit += w[j];
		upperBound += p[j];
		j++;
	}
	if (j <= n) upperBound += (m - weightLimit)*p[j] / w[j];	// calculate promising

	return upperBound;
}