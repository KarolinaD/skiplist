#include <vector>
#include <limits>

#include "SkipList.h"

struct Node
{
  int64_t value{};
  std::vector<Node &> pointers;

  void changePointer(Node & node, uint64_t level)
  {
    if (level <= pointers.size() - 1)
    {
      pointers.at(level) = node;
    }
    else
    {
      while (pointers.size() - 1 != level)
      {
        pointers.push_back(node);
      }
    }
  }

  Node & getNext(uint64_t level)
  {
    return pointers.at(level);
  }

  int64_t getValue()
  {
    return value;
  }

  int64_t getLevels()
  {
      return pointers.size();
  }
};

Node nodeH{};
Node nodeT{};
uint64_t maxLevel{0};

Node & makeNode(int64_t value, std::vector<Node &> pointers)
{
  Node node = {value, pointers};
  return & node;
}

SkipList::SkipList(std::vector<int64_t> const & init)
{
  nodeT = makeNode(std::numeric_limits<int64_t>::infinity, std::vector<int64_t>);
  nodeH = makeNode(NULL, std::vector<int64_t>{& nodeT});
  // for each element in init, create temporary node instance,
  // randomly get its level height, create pointers for this node at each level,
  // update pointers for previous elements at each level.
  // we can't add a new level if we are maxLevel + 1
  for (int64_t element : init)
  {
    uint64_t levels = std::rand() % maxLevel + 1;
    Node & tempNode = makeNode(element, std::vector<Node &> pointers(levels));
    for (i = 0; i <= levels; i++)
    {

    }
  }
}

Node & search(Node & target)
{
  Node & temp = nodeH;
  for (int i = maxLevel; i >= 0; i--)
  {
    // nodeT MUST be infinity, nodeH MUST be -infinity.
    // Create custom comparators.
    while (temp.getNext(i) <= target)
    {
      temp = temp.getNext(i);
    }
  }
  return temp;
}

// First: Search, store found node as variable.
// If found node == inserting node, end.
// Else, update inserting node's pointers to found node's pointers,
// Update found node's pointers to inserting node.
// Returns true if node was sucessfully added, false otherwise.
boolean addNode(Node & node)
{
    Node & prevNode = search(node);
    if (prevNode == node) return false;

    for (int i = 0; i <= prevNode.getLevels(); i++)
    {
        node.changePointer(prevNode.getNext(i), i);
    }
    for (int i = prevNode.getLevels() + 1; i <= node.getLevels; i++)
    {
        node.changePointer(nodeT)
    }
}

bool operator== (const Node &n1, const Node &n2)
{
    return (n1.getValue() == n2.getValue());
}

bool operator!= (const Node &n1, const Node &n2)
{
    return !(n1 == n2);
}

bool operator< (const Node &n1, const Node &n2)
{
    if (n1 == nodeH || n2 == nodeT) return true;
    if (n2 == nodeH || n1 == nodeT) return false;
    return (n1.getValue() < n2.getValue());
}

bool operator> (const Node &n1, const Node &n2)
{
    return !(n1 < n2 || n1 == n2);
}

bool operator<= (const Node &n1, const Node &n2)
{
    return (n1 < n2 || n1 == n2);
}

bool operator>= (const Node &n1, const Node &n2)
{
    return (n1 > n2 || n1 == n2);
}
