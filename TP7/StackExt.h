# include <iostream>
# include <stack>

using namespace std;

template <class T>
class StackExt {
stack<T> stackorg, stackmin;
public:
	StackExt() {};
	bool empty() const;
	T& top();
	void pop();
	void push(const T& val);
	T& findMin();
};

template <class T>
bool StackExt<T>::empty() const {
	return stackorg.empty();
}

template <class T>
T& StackExt<T>::top() {
	return stackorg.top();
}

template <class T>
void StackExt<T>::pop() {
	// Check if it should be removed from the mins stack. If so, do it
	if(stackmin.top() == stackorg.top())
		stackmin.pop();
	//Poppin' from the main stack
	stackorg.pop();
}

template <class T>
void StackExt<T>::push(const T& val) {
	//Adding the element to the original stack
	stackorg.push(val);

	//In case stackmin is empty
	if(stackmin.size() == 0)
		stackmin.push(val); //T'is the first min value

	//In case val is smaller than the value in stackmin
	if(val <= stackmin.top())
		stackmin.push(val);
}

template <class T>
T& StackExt<T>::findMin() {
	stackmin.top();
}

