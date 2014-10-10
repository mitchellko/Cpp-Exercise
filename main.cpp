#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stack>
#include <queue>

using namespace std;

void flush_stack( stack<int> *);
void flip_stacks( stack<int> *, int);
int find_index( stack<int>, int);
int find_index_of_largest_with_depth(stack<int>, int);
void show_stack_content( stack<int>);

stack<int> temp1, temp2;

int main () {
  string line;
  int num, num_cakes, num_cakes_sorted;
  int sub_largest_index;

  stack<int>	panstacks;

  	while ( getline(cin,line) ){
		// Readin 1 line and push into stack temp1.
    	for ( stringstream numbers(line); numbers >> num; ){
			cout << num << ' ';
			temp1.push(num); //initial top pancake at bottome of temp1;
    	}
    	cout << '\n';
    	num_cakes = temp1.size();
//    	cout << "Total Cakes:" << num_cakes << '\n';

    	//Initial panstacks to be in the real order
    	flush_stack( &panstacks);
		while ( !temp1.empty() ){
    		panstacks.push(temp1.top());
    		temp1.pop();
		}

    	num_cakes_sorted = 0;
		while ( num_cakes_sorted < num_cakes) {
//			show_stack_content( panstacks);
			sub_largest_index = find_index_of_largest_with_depth( panstacks, num_cakes - num_cakes_sorted);
//	    	cout << "sub_largest_index:" << sub_largest_index << '\n';

			if (sub_largest_index == (num_cakes_sorted + 1)) { //Lucky, no flips required in thsi iteration.
	    		num_cakes_sorted++;
	    	}
	    	else {
	    		if (sub_largest_index != num_cakes) { // sub_largest not at top, flip the sub_largest to top.
		    		cout << sub_largest_index << ' ';
					flip_stacks( &panstacks, num_cakes - sub_largest_index + 1);
	    		}
	    		// Flip the sub_largest(at top) to its fixed location.
	    		cout << num_cakes_sorted + 1 << ' ';
				flip_stacks( &panstacks, num_cakes - num_cakes_sorted);
				num_cakes_sorted++;
			}
	    }
	    cout << '0' << '\n';
    	flush_stack( &temp1);
		flush_stack( &temp2);
	}

  return 0;
}

void flush_stack( stack<int> *pstack) {
	while ( !(*pstack).empty() )
		(*pstack).pop();
}

int find_index( stack<int> stack, int num) {

	int value, index = stack.size();

	flush_stack( &temp1);

	while ( !stack.empty()) {
		value = stack.top();
		stack.pop();
		temp1.push(num);
		if (num == value) {
			break;
		}
		index--;
	}
	while ( !temp1.empty()) {
		stack.push(temp1.top());
		temp1.pop();
	}
	return index;
}

void flip_stacks( stack<int> *pstack, int top_n){

	int num, i;
	stack<int> tmp1;
	stack<int> tmp2;

//	show_stack_content( *pstack);
//	flush_stack( &temp1);
//	flush_stack( &temp2);

	for ( i=0; i<top_n; i++) {
		num = (*pstack).top();
		(*pstack).pop();
		tmp1.push(num);
	}

	for ( i=0; i<top_n; i++) {
		num = tmp1.top();
		tmp1.pop();
		tmp2.push(num);
	}

	for ( i=0; i<top_n; i++) {
		num = tmp2.top();
		tmp2.pop();
		(*pstack).push(num);
	}
}

int find_index_of_largest_with_depth(stack<int> stack, int depth){
	int num, index, largest = 0;

	flush_stack(&temp1);
	for (int i=0; i<depth; i++){
		num = stack.top();
		stack.pop();
		temp1.push(num);
		if ( num > largest) {
			largest = num;
			index = i;
		}
	}
	for (int i=0; i<depth; i++){
		stack.push( temp1.top());
		temp1.pop();
	}
	return stack.size() - index;
}

void show_stack_content( stack<int> stack){
	int num;
	flush_stack(&temp1);
	while (!stack.empty()){
		temp1.push(stack.top());
		stack.pop();
	}
	while (!temp1.empty()){
		num = temp1.top();
		stack.push(num);
		temp1.pop();
		cout << num << ' ';
	}
	cout << '\n';
}

