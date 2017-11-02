// (c) Daniel Bortfeld 2016 - 2017
#ifndef MAP_H
#define MAP_H

#include <vector>
using std::vector;

template<class KeyType, class ValueType>
struct TPair
{
	KeyType Key;
	ValueType Value;

	TPair()
	{
	}

	TPair(KeyType const& key, ValueType const& value) : Key(key), Value(value)
	{
	}

	~TPair()
	{
	}
};

template<typename KeyType, typename ValueType>
class TMap
{
private:

	vector<TPair<KeyType, ValueType>*> pairs;

public:

	TMap();
	~TMap();

	ValueType& Add(KeyType const& key);
	ValueType& Add(KeyType const& key, ValueType const& value);

	void Remove(KeyType const& key);
	void Clear();

	bool Contains(KeyType const& key) const;
	int Size() const;

	ValueType* Find(KeyType const& key);
	ValueType& FindOrAdd(KeyType const& key);
	ValueType& operator[](KeyType const& Key);

	auto begin() { return pairs.begin(); }
	auto end() { return pairs.end(); }
	auto begin() const { return pairs.begin(); }
	auto end() const { return pairs.end(); }

private:

	int FindId(KeyType const& key) const;
	TPair<KeyType, ValueType> FindPair(KeyType const& key) const;
	bool IsValidId(int const& id) const;
};

template<typename KeyType, typename ValueType>
inline TMap<KeyType, ValueType>::TMap()
{
	pairs = vector<TPair<KeyType, ValueType>*>();
}

template<typename KeyType, typename ValueType>
inline TMap<KeyType, ValueType>::~TMap()
{
	if (pairs.empty())
	{
		return;
	}

	for (auto iter = pairs.begin(); iter != pairs.end(); ++iter)
	{
		delete *iter;
	}
	pairs.clear();
}

template<typename KeyType, typename ValueType>
inline ValueType & TMap<KeyType, ValueType>::Add(KeyType const& key)
{
	return Add(key, ValueType());
}

template<typename KeyType, typename ValueType>
inline ValueType& TMap<KeyType, ValueType>::Add(KeyType const& key, ValueType const& value)
{
	int id = FindId(key);
	if (IsValidId(id))
	{
		pairs[id]->Value = value;
	}
	else
	{
		pairs.push_back(new TPair<KeyType, ValueType>(key, value));
	}

	return *Find(key);
}

template<typename KeyType, typename ValueType>
inline bool TMap<KeyType, ValueType>::Contains(KeyType const& key) const
{
	return IsValidId(FindId(key));
}

template<typename KeyType, typename ValueType>
inline ValueType * TMap<KeyType, ValueType>::Find(KeyType const& key)
{
	if (pairs.empty())
	{
		return nullptr;
	}

	for (auto& pair : pairs)
	{
		if (pair->Key == key)
		{
			return &pair->Value;
		}
	}

	return nullptr;
}

template<typename KeyType, typename ValueType>
inline ValueType & TMap<KeyType, ValueType>::FindOrAdd(KeyType const& key)
{
	if (auto* value = Find(key))
	{
		return *value;
	}

	return Add(key);
}

template<typename KeyType, typename ValueType>
inline void TMap<KeyType, ValueType>::Remove(KeyType const& key)
{
	int id = FindId(key);
	if (IsValidId(id))
	{
		auto iter = pairs.begin();
		for (int i = 0; i < id; ++i)
		{
			++iter;
		}
		pairs.erase(iter);
	}
}

template<typename KeyType, typename ValueType>
inline void TMap<KeyType, ValueType>::Clear()
{
	pairs.clear();
}

template<typename KeyType, typename ValueType>
inline int TMap<KeyType, ValueType>::Size() const
{
	return pairs.size();
}

template<typename KeyType, typename ValueType>
inline ValueType & TMap<KeyType, ValueType>::operator[](KeyType const & Key)
{
	return FindOrAdd(Key);
}

template<typename KeyType, typename ValueType>
inline int TMap<KeyType, ValueType>::FindId(KeyType const& key) const
{
	for (int Index = 0; Index < pairs.size(); ++Index)
	{
		if (pairs[Index]->Key == key)
		{
			return Index;
		}
	}
	return -1;
}

template<typename KeyType, typename ValueType>
inline TPair<KeyType, ValueType> TMap<KeyType, ValueType>::FindPair(KeyType const& key) const
{
	int id = FindId(key);
	if (id != -1)
	{
		return pairs[id];
	}

	return default(TPair<KeyType, ValueType>);
}

template<typename KeyType, typename ValueType>
inline bool TMap<KeyType, ValueType>::IsValidId(int const& id) const
{
	return id != -1;
}

#endif // !MAP_H
