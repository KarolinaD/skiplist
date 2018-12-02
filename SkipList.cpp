#include <vector>
#include <limits>
#include <algorithm>
#include <cstdint>
#include <iterator>
#include "SkipList.h"

// header and tail nodes
Node nodeH{};
Node nodeT{};
// current max level of skiplist
uint64_t maxLevel{0};
// current number of elements in the list
uint64_t size{0};

Node SkipList::makeNode(int64_t value, std::vector<Node> pointers, char id)
{
  // value: value of an element in the list
  // pointers: a vector of 
  Node node = {value, pointers, id};
  return node;
}

uint64_t SkipList::randLevels()
{
  return std::rand() % maxLevel + 1;
}

SkipList::SkipList(std::vector<int64_t> const & init)
{
  nodeT = makeNode(0, std::vector<Node>{}, 't');
  nodeH = makeNode(0, std::vector<Node>{nodeT}, 'h');
  // for each element in init, create temporary node instance,
  // randomly get its level height, create pointers for this node at each level,
  // update pointers for previous elements at each level.
  // we can't add a new level if we are maxLevel + 1
  for (int64_t element : init)
  {
      insert(element);
  }
}

std::vector<Node> SkipList::search(Node & target)
{
  Node temp = nodeH;
  std::vector<Node> path;
  for (int i = maxLevel; i >= 0; i--)
  {
    // nodeT MUST be infinity, nodeH MUST be -infinity.
    // Create custom comparators.
    while (temp.getNext(i) <= target)
    {
      temp = temp.getNext(i);
    }
    path.push_back(temp);
  }
  return path;
}

bool SkipList::find(int64_t const x)
{
  std::vector<Node> pointers(randLevels());
  Node node = makeNode(x, pointers);
  return search(node).back() == node;
}

// First: Search, store found node as variable.
// If found node == inserting node, end.
// Else, update inserting node's pointers to found node's pointers,
// Update found node's pointers to inserting node.
// Returns true if node was sucessfully added, false otherwise.
bool SkipList::insert(int64_t const x)
{
    std::vector<Node> pointers(randLevels());
    Node node = makeNode(x, pointers);
    std::vector<Node> path = search(node);
    Node temp = path.back();
    uint64_t levelCounter = 0;
    if (temp == node) return false;

    for (int i = path.size(); i >= 0; i--)
    {
        node.changePointer(path.at(i).getNext(levelCounter), levelCounter);
        path.at(i).changePointer(node, levelCounter);
        levelCounter++;
    }
    if (node.getLevels() == maxLevel)
    {
      maxLevel++;
      nodeH.changePointer(nodeT, maxLevel);
    }
    size++;
    return true;
}

bool SkipList::remove(int64_t const x)
{
  std::vector<Node> pointers(randLevels());
  Node node = makeNode(x, pointers);
  std::vector<Node> path = search(node);
  Node temp = path.back();
  uint64_t levelCounter = 0;
  if (temp != node) return false;

  for (int i = path.size(); i >= 0; i--)
  {
    path.at(i).changePointer(temp.getNext(levelCounter), levelCounter);
    levelCounter++;
  }
  return true;
}

size_t SkipList::numElem()
{
  return size;
}
