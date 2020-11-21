#include <iostream>

using namespace std;

template<typename T>
class ForwardList {
public:
	ForwardList() : head_(nullptr) {};
	void Print();
	void PushFront(const T&);
	
	ForwardList(const ForwardList& other) {
		ListNode_ temp(T{});
		ListNode_* head = &temp;
		
		for (ListNode_* curr = other.head_; curr != nullptr; curr = curr->next) {
			head->next = new ListNode_(curr->val);
			head = head->next;
		}

		head_ = temp.next;
 	}

	~ForwardList()
	{
		while (!Isempty()) {
			PopFront();
		}
	}
	void PopFront() {
		ListNode_* temp = head_;
		head_ = head_->next;
		
		delete temp;
	}

	bool Isempty() {
		return head_ == nullptr;
	}

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
	l.PushFront(10);
	l.Print();
	l.PushFront(20);
	l.Print();
	l.PushFront(30);
	l.Print();
	
	ForwardList<int> a = l;
	a.Print();

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

template<typename T>
void ForwardList<T>::PushFront(const T& val) {
	ListNode_* temp = head_;
	head_ = new ListNode_(val);

	head_->next = temp;
}