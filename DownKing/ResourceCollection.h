#pragma once
#include <vector>

template <typename Key, typename Val>
class ResourceCollection
{
public:
	ResourceCollection();
	~ResourceCollection();

	void set(Key key, Val val);
	Val get(Key key);

private:
	std::vector<Val> list;
};

template<typename Key, typename Val>
inline ResourceCollection<Key, Val>::ResourceCollection()
{
}

template<typename Key, typename Val>
inline ResourceCollection<Key, Val>::~ResourceCollection()
{
	for (auto& v : this->list) {
		if (v != nullptr) {
			delete v;
		}
	}
}

template<typename Key, typename Val>
inline void ResourceCollection<Key, Val>::set(Key key, Val val)
{
	auto idx = static_cast<int>(key);
	if (idx >= this->list.size()) {
		this->list.resize(idx + 1);
	}
	this->list[idx] = val;
}

template<typename Key, typename Val>
inline Val ResourceCollection<Key, Val>::get(Key key)
{
	auto idx = static_cast<int>(key);
	return this->list.at(idx);
}
