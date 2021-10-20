#include <vector>
#include <iostream>
using namespace std;

template<typename T, typename Container>
class priority_queue {
	Container _container;
	
	/**
	 * Возвращает индекс левого ребёнка по индексу родителя
	 * 2*i + 1
	 */
	int _leftChildIndex(int parentIndex);
	
	/**
	 * Возвращает индекс правого ребёнка по индексу родителя
	 * 2*i + 2
	 */
	int _rightChildIndex(int parentIndex);
	
	/**
	 * Возвращает индекс родителя по индексу ребёнка
	 * (int)(0.5 * i + 0.5) - 1
	 */
	int _parentIndex(int childIndex);
	
	/**
	 * "Просеивание" вверх
	 */
	void _siftUp(int index);
	
	/**
	 * "Просеивание" вниз
	 */
	void _siftDown(int index);

	// при необходимости просеивает вниз элементы
	void _stabilization();
	
public:
	/**
	 * Добавление элемента в очередь
	 * Реализуется через siftUp
	 */
	void push(const T& value);
	
	/**
	 * Возвращает верхний элемент очереди,
	 * НЕ удаляя его
	 *
	 * Возвращает первый элемент
	 */
	T top() const;
	
	/**
	 * Возвращает верхний элемент очереди,
	 * удаляя его
	 * 
	 * Возвращает первый элемент, удаляет его, делает siftDown
	 */
	T pop();
	
	/**
	 * Проверяет, пустая очередь или нет
	 */
	bool empty() const;
};

//////////////////////////////////////////////////////////////////////////////////////////////

template<typename T, typename Container>
int priority_queue<T, Container>::_leftChildIndex(int parentIndex) {
	return parentIndex * 2 + 1;
}

template<typename T, typename Container>
int priority_queue<T, Container>::_rightChildIndex(int parentIndex) {
	return parentIndex * 2 + 2;
}

template<typename T, typename Container>
int priority_queue<T, Container>::_parentIndex(int childIndex) {
	return int(0.5 * childIndex + 0.5) - 1;
}

template<typename T, typename Container>
void priority_queue<T, Container>::_siftUp(int index) {
	if (index == 0) {
		return;
	}
	while (_container[index] > _container[_parentIndex(index)]) {
		swap(_container[index], _container[_parentIndex(index)]);
		index = _parentIndex(index);
	}
}

template<typename T, typename Container>
void  priority_queue<T, Container>::_siftDown(int index) {
	while (((_container[index] < _container[_leftChildIndex(index)])
		|| (_container[index] < _container[_rightChildIndex(index)]))
		&& (_leftChildIndex(index) < _container.size())
		&& (_rightChildIndex(index) < _container.size()))
	{
		if (_container[index] < _container[_leftChildIndex(index)]) {
			swap(_container[index], _container[_leftChildIndex(index)]);
		}
		else if (_container[index] < _container[_rightChildIndex(index)]) {
			swap(_container[index], _container[_rightChildIndex(index)]);
		}
	}
}

template<typename T, typename Container>
void priority_queue<T, Container>::_stabilization() {
	int i = 0;
	while (i != _container.size()) {
		_siftDown(i);
		i++;
	}
}

template<typename T, typename Container>
void  priority_queue<T, Container>::push(const T& value) {
	_container.push_back(value);
	int size = _container.size() - 1;
	_siftUp(size);
}

template<typename T, typename Container>
T  priority_queue<T, Container>::top() const {
	return _container[0];
}

template<typename T, typename Container>
T  priority_queue<T, Container>::pop() {
	int size = _container.size() - 1;
	swap(_container[0], _container[size]);
	T tmp = _container[size];
	_container.pop_back();
	_siftDown(0);
	_stabilization();
	return tmp;
	
}

template<typename T, typename Container>
bool  priority_queue<T, Container>::empty() const{
	return (_container.size() == 0);

}

////////////////////////////////////////////////////////////////////////////////////////////////////

//template<typename T, typename Container>
int main() {
	priority_queue<int, vector<int>> q;
	q.push(45);
	q.push(11);
	q.push(12);
	q.push(7);
	q.push(100);
	q.push(10);
	q.push(20);
	q.push(11);
	q.push(91);

	
	cout << "empty: " << q.empty() << endl;
	cout << "pop: " << q.pop() << endl;
	cout << "top: " << q.top() << endl;

	cout << "All top:" << endl; 

	while(!q.empty()) {
		cout << q.pop() << " ";
	}
}