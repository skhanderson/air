// ConsoleApplication2.cpp : Defines the entry point for the console application.
//

#ifdef WINDOWS
#include "stdafx.h"
#endif
#include "LinkedList.h"
#include <iostream>
using namespace std;

int main()
{
	LinkedList<int> l;
	cout << "Initial empty list." << std::endl;
	// l.iterate([](int v) { cout << v << std::endl; });
	size_t size = 10;
	cout << "Creating list of size " << size << std::endl;
	for (size_t i = 1; i <= size; ++i) {
		l.push_back(i);
	}

	LinkedList<int> l2(l);

	LinkedList<int>::iterator it;
	it = l.begin();
	while (it != l.end()) {
	  cout << *it << std::endl;
	  it++;
	}

	l.reverse_iterative();
	for (auto num: l) {
	  cout << num << std::endl;
	}

	size_t count = 0;
	for (auto &num: l) {
	  num = ++count;
	}

	for (auto num: l) {
	  cout << num << std::endl;
	}

	it = l.end();
	try {
	  *it = 5;
	} catch (LinkedListError e) {
	  cout << "Caught the error." << std::endl;
	}



	exit(1);
	//l.iterate([](int v) { cout << v << std::endl; });
	cout << "Reversing iteratively." << std::endl;
	l.reverse_iterative();
	size_t expected = size;
	for (auto v: l) {
	  if (v !=  expected) {
	    cout << "Mismatch: " << v << ", " << expected << std::endl;
	    exit(1);
	  }
	  --expected;
	}
	cout << "Reversing iteratively." << std::endl;
	l.reverse_iterative();
	expected = 1;
	for (auto v: l) {
	  if (v !=  expected) {
	    cout << "Mismatch: " << v << ", " << expected << std::endl;
	    exit(1);
	  }
	  ++expected;
	}

	cout << "Reversing recursively." << std::endl;
	l.reverse_recursive();
	//l.iterate([](int v) { cout << v << std::endl; });
	cout << "Exiting." << std::endl;
}

