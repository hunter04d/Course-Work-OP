#pragma once

/**
 *Stack realisation
 * T - values in the stack
 */
template <typename T>
class Stack
{
	/**
	 * @brief The list struct  is the underling linked list of the Stack
	 */
	struct list
	{
		T value;
		list* next_ptr;
	} *head = nullptr;
	size_t F_size = 0; //size of the stack
public:

	/**
	 * @brief push - method to push the value onto the stack
	 * @param value - pushed value
	 */
	void push(const T& value)
	{
		++F_size;
		list *temp = new list;
		temp->value = value;
		temp->next_ptr = head;
		head = temp;
	}

	/**
	 * @brief pop - method to pop the value out
	 * @return poped value
	 */
	T pop()
	{
		--F_size;
		T val(head->value);
		list *temp = head;
		head = temp->next_ptr;
		delete temp;
		return val;
	}

	/**
	 * @brief top method to access the top element
	 * @return reference to the top element
	 */
	const T& top() const
	{
		return head->value;
	}
	/**
	 * @brief size - method that returns size of the stack
	 * @return size of the stack
	 */
	size_t size() const
	{
		return F_size;
	}

	/**
	 * @brief empty - method that checkes if the stack is empty
	 * @return true if it is empty, else - false
	 */
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
