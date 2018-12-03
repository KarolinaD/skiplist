#include <vector>
#include <limits>
#include <algorithm>
#include <cstdint>
#include <iterator>
#include <experimental/random>
#include <iostream>
#include "SkipList.h"

Node nodeH{};
Node nodeT{};
uint64_t maxLevel{0};
uint64_t size{0};

Node SkipList::makeNode(int64_t value, std::vector<Node> pointers, char id)
{
  Node node = {value, pointers, id};
  return node;
}

/*uint64_t SkipList::randLevels()
{
  return (std::experimental::randint(1, maxLevel);
}*/

SkipList::SkipList(std::vector<int64_t> const & init)
{
  nodeT = makeNode(0, std::vector<Node>{}, 't');
  nodeH = makeNode(0, std::vector<Node>{nodeT}, 'h');

  for (int64_t element : init)
  {
      insert(element);
  }
}

std::vector<Node> SkipList::search(Node & target)
{
  Node temp = nodeH;
  std::vector<Node> path;
  //std::cout << maxLevel << '\n';
  for (int i = maxLevel; i >= 0; i--)
  // we start searching for a target node from the highest level
  {
    std::cout << "search" << '\n';
    std::cout << i << " i search" << '\n';
    // HERE BELOW YOU CAN SEE THAT THE GETNEXT NODE IS A TAIL NODE
    // AND HAS VALUE 0, BUT IS STILL REGARDED AS SMALLER THAN TARGET NODE
    std::cout << temp.getNext(i).getID() << temp.getNext(i).getValue() << " getNext" << '\n';
    std::cout << target.getValue() << " target" << '\n';
    while (temp.getNext(i) <= target)
    // if temp node's pointer node at i-th level is smaller than target node
    {
      std::cout << "while search" << '\n';
      temp = temp.getNext(i);
    }
    path.push_back(temp);
  }
  return path;
  // path consists of nodes starting from the maxLevel to 0-th level
  // if target node is found, it is also included in the path
}

bool SkipList::find(int64_t const x)
{
  std::vector<Node> pointers(4);
  //std::vector<Node> pointers(randLevels());
  Node node = makeNode(x, pointers);
  return search(node).back() == node;
}

bool SkipList::insert(int64_t const x)
// create initial node instance for inserting node, randomly get its level height;
// get the path to the inserting node, store a node directly preceeding it;
// update inserting node's pointers to path's nodes' pointers;
// update path's nodes' pointers to inserting node;
// we can't add a new level if we are maxLevel + 1.
{
    std::vector<Node> pointers(4);
    //std::vector<Node> pointers(randLevels());
    Node node = makeNode(x, pointers);
    std::cout << "kupa" << '\n';
    std::vector<Node> path = search(node);
    Node temp = path.back();
    uint64_t levelCounter = 0;
    if (temp == node) return false;
    // if inserting node already exists in the list

    std::cout << path.size() << " path size" << '\n';
    for (int i = path.size() - 1; i >= 0; i--)
    // the last element in path is the node at the bottom - at 0th level
    {
      std::cout << "1st iteration" << '\n';
      std::cout << i << " i" << '\n';
      std::cout << levelCounter << " levelCounter" << '\n';
      std::cout << pointers.size() << " pointers size" << '\n';
      if (levelCounter < pointers.size())
      {
        //std::cout << i << levelCounter << '\n';
        node.changePointer(path.at(i).getNext(levelCounter), levelCounter);
        // change inserting node's pointer to the pointer of the i-th node
        // from the path at <levelCounter>
        path.at(i).changePointer(node, levelCounter);
        // change the pointer of i-th node from the path to point to
        // the inserting node at <levelCounter>
        levelCounter++;
      }
    }

    if (node.getLevels() >= maxLevel)
    // we always have an 'abstract' level at the top which consists of
    // header and tail nodes only; header node has a pointer to tail node
    {
      for (unsigned int i = node.getLevels() - 1; i > maxLevel; i--)
      {
        std::cout << "2nd iteration" << '\n';
        std::cout << i << " i" << '\n';
        std::cout << node.getLevels() << " node.getLevels()" << '\n';
        std::cout << maxLevel << " maxLevel" << '\n';
        nodeH.changePointer(nodeT, i);
      }
      maxLevel = node.getLevels() + 1;
      std::cout << maxLevel << " maxLevel after 2nd iteration" << '\n';
    }
    //std::cout << node.getLevels() << maxLevel << '\n';
    //std::cout << node.getLevels() << maxLevel << '\n';
    size++;
    return true;
}

bool SkipList::remove(int64_t const x)
{
  std::vector<Node> pointers(4);
  //std::vector<Node> pointers(randLevels());
  Node node = makeNode(x, pointers);
  std::vector<Node> path = search(node);
  Node temp = path.back();
  uint64_t levelCounter = 0;
  if (temp != node) return false;
  // if removing node doesn't exist in the list

  for (int i = path.size() - 1; i >= 0; i--)
  {
    path.at(i).changePointer(temp.getNext(levelCounter), levelCounter);
    // change the pointer of i-th node from the path to point to
    // the removing node at <levelCounter>
    levelCounter++;
  }
  size--;
  return true;
}

size_t SkipList::numElem()
{
  return size;
}
