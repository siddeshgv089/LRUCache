
/*

program to define LRU cache.

Using the (deque) Double ended queue to store the (K,V) elements
Using the map to store the address of the nodes to access the elements in the deque in O(1) time.

deque stores Key and value as a pair;
map stores Key and Value as the address the deque node corresponding to the given key.

deque => (1,10)->(2,20)->(3,30)

Node1 ==> (1,10) addr: 100
Node2 ==> (2,20) addr: 200
Node3 ==> (3,30) addr: 300


map :

1 -> 100
2 -> 200
3 -> 300

*/


#include <iostream>
#include<deque>
#include<map>
#include<algorithm>

class LRUCache
{
private:
	std::deque<std::pair<int, int>> list;
	std::map<int, std::deque<std::pair<int, int>>::iterator > mp;
	int capacity;

public:

	LRUCache(int capacity) : capacity(capacity) {}

	int get(int key)
	{
		std::map<int, std::deque<std::pair<int, int>>::iterator>::iterator it = mp.find(key);

		std::deque<std::pair<int, int>>::iterator iterd = mp[it->first];

		if (it == mp.end())
		{
			return -1;
		}
		else
		{
			int value = iterd->second;

			if (it->second != list.begin())
			{
				list.erase(it->second);
				list.push_front(std::pair<int, int>(key, value));

				it->second = list.begin();
			}


			return value;

		}

	}

	bool set(int key, int value)
	{

		std::map<int, std::deque<std::pair<int, int>>::iterator>::iterator it = mp.find(key);

		if (it == mp.end())
		{

			if (capacity == list.size())
			{
				std::cout << "capacity full" << std::endl;

				std::deque<std::pair<int, int>>::iterator it_end = list.end();

				if (mp.find(it_end->first) != mp.end())
					mp.erase(mp.find(it_end->first));

				list.pop_back();
			}

			list.push_front(std::pair<int, int>(key, value));
			

			mp[key] = list.begin();

			return true;

		}
		else
		{


			if (it->second != list.begin())
			{
				list.erase(it->second);
				list.push_front(std::pair<int, int>(key, value));
				it->second = list.begin();
			}
			else {
				it->second->second = value;
			}

			return true;
		}

		return false;
	}

	void printCache()
	{
		std::cout << " " << std::endl;
		for (auto i : list)
		{
			std::cout << "element = " << i.second << std::endl;
		}
	}
};


int main()
{

	LRUCache lc(3);

	lc.set(1, 10);
	lc.set(2, 20);
	lc.set(3, 30);
	lc.printCache();

	lc.get(1);
	lc.printCache();

	std::cout << lc.get(10) << std::endl;
	lc.printCache();

	lc.set(4, 40);
	lc.printCache();

	lc.set(5, 50);
	lc.printCache();



}

