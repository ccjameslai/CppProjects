#include <iostream>

using namespace std;

template<typename T>
class ForwardList {
public:
	ForwardList() : head_(nullptr) {};
	void Print();

private:
	struct ListNode_ {
		T val;
		ListNode_* next;
		ListNode_(T value) : val(value), next(nullptr){};
	};

	ListNode_* head_;
};

int main() { 
	ForwardList<int> l;
	l.Print();

	return EXIT_SUCCESS;
}

template<typename T>
void ForwardList<T>::Print() {
	cout << "[";
	for (ListNode_* curr = head_; curr != nullptr; curr = curr->next) {
		cout << curr->val;
		if (curr->next != nullptr) {
			cout << ", ";
		}
	}
	cout << "]" << endl;
}
