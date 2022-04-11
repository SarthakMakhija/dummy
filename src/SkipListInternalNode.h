#ifndef _SkipListInternalNode_
#define _SkipListInternalNode_

#include <string>
#include <vector>

#include "WritePosition.h"

class SkipListInternalNode {
private:
    const char* key;
    std::vector<SkipListInternalNode *> forwards;

    int generateLevel(int maxLevel, double probability);

public:
    SkipListInternalNode(const char* key, int level);

    std::pair<std::string, bool> getBy(const char* key);

    PutPosition putPositionOf(const char* key, double withProbability);

    SkipListInternalNode *
    put(const char* key, std::vector<SkipListInternalNode *> positions, int nodeLevel);

};

#endif