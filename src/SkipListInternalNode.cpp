#include "SkipListInternalNode.h"

SkipListInternalNode::SkipListInternalNode(const char* key, int level) {
    this->key = key;

    this->forwards.resize(level);
    for (int index = 0; index < level; index++) {
        this->forwards[index] = nullptr;
    }
}

std::pair<std::string, bool> SkipListInternalNode::getBy(const char* key1) {
    SkipListInternalNode *current = this;
    for (int level = this->forwards.size() - 1; level >= 0; level--) {
        while (current->forwards[level] && current->forwards[level]->key < key1) {
            current = current->forwards[level];
        }
    }
    current = current->forwards[0];

    if (current && current->key == key1) {
        return std::make_pair(current->key, true);
    }
    return std::make_pair("", false);
}

PutPosition SkipListInternalNode::putPositionOf(const char* key1, double withProbability) {
    SkipListInternalNode *current = this;
    std::vector<SkipListInternalNode *> positions(this->forwards.size(), nullptr);

    for (int level = this->forwards.size() - 1; level >= 0; level--) {
        while (current->forwards[level] && current->forwards[level]->key < key1) {
            current = current->forwards[level];
        }
        positions[level] = current;
    }
    current = current->forwards[0];
    if (current == nullptr || current->key != key1) {
        int newLevel = generateLevel(this->forwards.size(), withProbability);
        //std::cout << "new level " << newLevel << " for key " << key1 << std::endl;
        return PutPosition{positions, newLevel, this};
    }
    return PutPosition{positions, -1, this};
}

SkipListInternalNode *SkipListInternalNode::put(const char* key1,
                                                std::vector<SkipListInternalNode *> positions,
                                                int nodeLevel) {

    SkipListInternalNode *newNode = new SkipListInternalNode(key1, nodeLevel);
    for (int level = 0; level < nodeLevel; level++) {
        newNode->forwards[level] = positions[level]->forwards[level];
        positions[level]->forwards[level] = newNode;
    }
    return newNode;
}

int SkipListInternalNode::generateLevel(int maxLevel, double probability) {
    double random = (double) rand() / RAND_MAX;
    int level = 1;

    while (random < probability && level < maxLevel) {
        level = level + 1;
        random = (double) rand() / RAND_MAX;
    }
    return level;
}
