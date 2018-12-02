#define SKIPLIST_H

struct Node
// represents an element in the list
{
  int64_t value{};
  std::vector<Node> pointers;
  char id{};

  void changePointer(Node node, uint64_t level)
  // change this node's pointer at <level> to point to <node>
  {
    if (level <= pointers.size() - 1)
    // if a pointer we want to change is on a smaller level than this node's max level
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

  Node getNext(uint64_t level)
  // get this node's pointer node from <level>
  {
    return pointers.at(level);
  }

  int64_t getValue()
  {
    return value;
  }

  char getID()
  {
    return id;
  }

  uint64_t getLevels()
  // get the max level of this node
  {
      return pointers.size();
  }
  bool operator== (Node &n2)
  {
    return (this->value == n2.getValue() &&
            this->id == n2.getID());
  }

  bool operator!= (Node &n2)
  {
    return !(*this == n2);
  }

  bool operator< (Node &n2)
  {
    if (this->id == 'h' || n2.getID() == 't') return true;
    if (n2.getID() == 'h' || this->id == 't') return false;
    return (this->value < n2.getValue());
  }

  bool operator> (Node &n2)
  {
    return !(*this < n2 || *this == n2);
  }

  bool operator<= (Node &n2)
  {
    return (*this < n2 || *this == n2);
  }

  bool operator>= (Node &n2)
  {
    return (*this > n2 || *this == n2);
  }
};

class SkipList
{
private:
  Node nodeH;
  Node nodeT;
  // header and tail nodes
  uint64_t maxLevel;
  // current max level of the list
  uint64_t size;
  // current number of elements in the list

  Node makeNode(int64_t value, std::vector<Node> pointers, char id = '\0');
  // construct a node with <value>, <pointers> vector consisting of this node's
  // pointer nodes, and default id
  //uint64_t randLevels();
  // get a random number of levels (between 1 and maxLevel) for a new node
  std::vector<Node> search(Node & target);
  // get a path from header node at the highest level to our target node
  // at the lowest level (if exists)

public:
  bool find(int64_t const x);
  bool insert(int64_t const x);
  bool remove(int64_t const x);
  size_t numElem();

  SkipList(std::vector<int64_t> const & init);

};
// SKIPLIST_H
