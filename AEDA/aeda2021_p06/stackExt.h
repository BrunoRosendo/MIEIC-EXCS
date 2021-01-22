# include <iostream>
# include <stack>

using namespace std;

template <class T>
class StackExt {
public:
	StackExt() {};
	bool empty() const; 
	T &top();
	void pop();
	void push(const T & val);
	T &findMin();
private:
    stack<T> mainStack;
    stack<T> minValues;
};

// a alterar
template <class T> 
bool StackExt<T>::empty() const
{
	return mainStack.empty();
}

//a alterar
template <class T> 
T& StackExt<T>::top()
{
    return mainStack.top();
}

//a alterar
template <class T> 
void StackExt<T>::pop()
{
    T val = mainStack.top();
    mainStack.pop();
    stack<T> removedValues;
    while (true){
        T top = minValues.top();
        if (top == val){
            minValues.pop();
            while (!removedValues.empty()) {
                minValues.push(removedValues.top());
                removedValues.pop();
            }
            break;
        }
        else{
            removedValues.push(top);
            minValues.pop();
        }
    }
}

//a alterar
template <class T> 
void StackExt<T>::push(const T & val)
{
    mainStack.push(val);
    stack<T> removedValues;
    while (true){
        if (minValues.empty() || val < minValues.top()) {
            minValues.push(val);
            while (!removedValues.empty()){
                minValues.push(removedValues.top());
                removedValues.pop();
            }
            break;
        }
        else{
            removedValues.push(minValues.top());
            minValues.pop();
        }
    }
}

//a alterar
template <class T> 
T& StackExt<T>::findMin()
{
    return minValues.top();
}

