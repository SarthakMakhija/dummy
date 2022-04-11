#include "SkipListNode.h"


class SkipListInternalNode;

struct PutPosition {
    std::vector<SkipListInternalNode *> positions;
    int newLevel;
    SkipListInternalNode *internal;
};
