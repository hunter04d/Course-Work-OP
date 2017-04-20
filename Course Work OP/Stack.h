#pragma once

template <typename T>
class Stack
{
	struct list
	{
		T value;
		list* next_ptr;
	} *head = nullptr;
	size_t F_size = 0;
public:
	void push(const T& value)
	{
		++F_size;
		list *temp = new list;
		temp->value = value;
		temp->next_ptr = head;
		head = temp;
	}

	T pop()
	{
		--F_size;
		T val(head->value);
		list *temp = head;
		head = temp->next_ptr;
		delete temp;
		return val;
	}
	const T& top() const
	{
		return head->value;
	}

	size_t size() const
	{
		return F_size;
	}

	bool empty() const
	{
		return (F_size == 0);
	}

	~Stack()
	{
		while (F_size--)
		{
			list *temp = head;
			head = temp->next_ptr;
			delete temp;
		}
	}

};
