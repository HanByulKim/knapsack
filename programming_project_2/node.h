/* Node for Priority Queue */
#pragma once
#include <limits>
class Node {
public:
	int lr;
	int level;
	int profit = 0;
	int weight = 0;
	int bound;

	Node* next;

	Node() { level = 0; bound = std::numeric_limits<int>::max(); next = NULL; }
	Node(int lev, int prof, int wei, int bnd) {
		level = lev;
		profit = prof;
		weight = wei;
		bound = bnd;
		next = NULL;
	}
	Node(int lev, int hier, int prof, int wei, int bnd) {
		level = lev;
		lr = hier;
		profit = prof;
		weight = wei;
		bound = bnd;
		next = NULL;
	}

};
