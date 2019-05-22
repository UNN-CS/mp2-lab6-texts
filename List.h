#pragma once
//Elem-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


template <class T>
class Elem {
public:
	T Val;
	Elem<T>* next;
	Elem<T>* prev;
};

//List-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


template <class T>
class list
{
	Elem<T>* first;
	Elem<T>* curr;
	Elem<T>* last;
	int last_num, curr_num;
public:
	list();
	list(list& _copy);
	Elem<T>& getElem(int num);
	bool IsEmpry();
	void push_back(T _elem);
	void pop_back();
	void pop(int num);
	void popc(int num);
	void set_curr_in_first();
	Elem<T>& set_cur(int num);
	void insert(T _elem, int pos);
	T& GoNext();
	T& Current();
	T& GoBack();
	T& operator[] (int num);
	list<T>& operator=(const list& copy);
	bool IsEnd();
	void clear();
	~list();
};
template<class T> Elem<T>& list<T>::getElem(int num)
{
	if (num<0 || num>last_num) throw "out of range";
	if (num == 0)return *first;
	if ((last_num / 2) > num)
	{
		set_curr_in_first();
		while (curr_num != num)
		{
			GoNext();
		}
	}
	else
	{
		curr = last;
		curr_num = last_num;
		while (curr_num != num)
		{
			GoBack();
		}
	}
	return *curr;
}
template <class T> list<T>::list()
{

	first = nullptr;
	last = nullptr;
	curr = first;
	last_num = curr_num=-1;
}
template <class T> list<T>::list(list<T>& _copy)
{
	if (_copy.IsEmpry())
	{
		first = nullptr;
		last = nullptr;
		curr = first;
		last_num = curr_num = -1;
	}
	else {
		list<T> * tmp = new list<T>();
		_copy.set_curr_in_first();
		tmp->push_back(_copy.Current());
		while (!(_copy.IsEnd())) tmp->push_back(_copy.GoNext());
		*this = *tmp;
	}

}
template <class T> bool list<T>::IsEmpry() {
	if (first == nullptr) return true;
	return false;
}
template <class T> void list<T>::push_back(T _elem) {
	if (IsEmpry())
	{
		Elem<T>* tmp = new Elem<T>;
		tmp->Val = _elem;
		tmp->next = nullptr;
		tmp->prev = nullptr;
		first = tmp;
		curr = first;
	}
	else
	{
		if (last == nullptr)
		{
			Elem<T>* tmp = new Elem<T>;
			tmp->Val = _elem;
			tmp->next = nullptr;
			tmp->prev = first;
			last = tmp;
			first->next = last;
			curr = last;
		}
		else
		{
			Elem<T>* tmp = new Elem<T>;
			tmp->Val = _elem;
			last->next = tmp;
			tmp->next = nullptr;
			tmp->prev = last;
			last = tmp;
			curr = last;
		}

	}
	last_num++;
	curr_num = 0;
}
template <class T> void list<T>::pop_back() {
	if (first == nullptr)
		throw - 1;
	else if (last == nullptr)
	{
		delete first;
		first = nullptr;
	}
	else if (first != last)
	{

		last = last->prev;
		delete last->next;
		last->next = nullptr;

	}
	else
	{
		delete first;
		first = nullptr;
		last = nullptr;
	}
	last_num--;
}
template<class T> void list<T>::pop(int num)
{
	if (num<0 || num>last_num) throw "out of range";
	else {
		Elem<T> *tmp;
		if (num > 0&&num!=last_num)
		{
			tmp = &getElem(num);
			tmp->prev->next = tmp->next;
			tmp->next->prev = tmp->prev;
			last_num--;
		}
		else if (num == 0)
		{
			tmp = first;
			first = first->next;
			first->prev = nullptr;
		}
		else
		{
			tmp = last;
			last = last->prev;
			last->next = nullptr;
		}
		delete tmp;
		set_curr_in_first();
	}

}
template<class T> void list<T>::popc(int num)
{
	if (num<0 || num>last_num) throw "out of range";
	else {
		Elem<T> *tmp;
		if (num > 0 && num != last_num)
		{
			tmp = &getElem(num);
			tmp->prev->next = tmp->next;
			tmp->next->prev = tmp->prev;
			last_num--;
		}
		else if (num == 0)
		{
			tmp = first;
			first = first->next;
			first->prev = nullptr;
		}
		else
		{
			tmp = last;
			last = last->prev;
			last->next = nullptr;
		}
		set_curr_in_first();
	}

}
template <class T>  void list<T>::set_curr_in_first()
{
	if (first != nullptr) {
		curr = first;
		curr_num = 0;
	}
}
template<class T> Elem<T>& list<T>::set_cur(int num)
{
	if (num<0 || num>last_num) throw "out of range";
	else {
		curr = &getElem(num);
		curr_num = num;
		return *curr;
	}

}
template<class T> void list<T>::insert(T _elem, int pos)
{
	if(pos<0) throw "out of range";
	if (pos > last_num)
	{
		list<T>::push_back(_elem);
		return;
	}
	else if(pos!= 0)
	{
		Elem<T> *tmp = new Elem<T>;
		tmp->Val = _elem;
		tmp->prev = list<T>::getElem(pos).prev;
		list<T>::getElem(pos).prev=tmp;
		tmp->next = &list<T>::getElem(pos);
		tmp->prev->next = tmp;
		curr = tmp;
		curr_num = pos;
		last_num++;
	}
	else
	{
		Elem<T> *tmp = new Elem<T>;
		tmp->Val = _elem;
		tmp->prev = list<T>::getElem(pos).prev;
		list<T>::getElem(pos).prev = tmp;
		tmp->next = &list<T>::getElem(pos);
		tmp->prev=nullptr;
		first=curr = tmp;
		curr_num = pos;
		last_num++;
	}
	set_curr_in_first();
	
	
}
template <class T> T& list<T>::GoNext()
{
	if (curr_num < last_num)
	{
		curr = curr->next;
		curr_num++;
		return curr->Val;
	}

}
template <class T> T& list<T>::Current()
{
	if (curr != nullptr) return curr->Val;
}
template <class T> T& list<T>::GoBack()
{
	if (curr_num > 0)
	{
		curr = curr->prev;
		curr_num--;
		return curr->Val;
	}

}
template <class T> T & list<T>::operator[](int num)
{
	if (num<0 || num>last_num) throw "out of range";
	if (num == 0)return first;
	if ((last_num / 2) > num)
	{
		set_curr_in_first();
		while (curr_num != num)
		{
			GoNext();
		}
	}
	else
	{
		curr = last;
		curr_num = last_num;
		while (curr_num != num)
		{
			GoBack();
		}
	}
	return curr->Val;
}
template <class T> list<T>& list<T>:: operator=(const list& copy)
{
	if (&_copy==this)
	{
		return *this;
	}
	else {
		list<T> * tmp = new list<T>(copy);
		delete this;
		return *tmp;
	}

}
template<class T> bool list<T>::IsEnd()
{
	return (curr_num==last_num);
}
template <class T> void list<T>::clear() {
	while (first != nullptr)
		pop_back();
}
template <class T> list<T>::~list()
{
	clear();
}
