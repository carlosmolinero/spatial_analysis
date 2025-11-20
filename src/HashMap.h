#ifndef HASHMAP_H
#define HASHMAP_H
#include <unordered_map>
template <class T>
class HashMap
{
public:

    HashMap();
    virtual ~HashMap();

protected:
private:
    std::unordered_map<long, T> map;
};

#endif // HASHMAP_H
