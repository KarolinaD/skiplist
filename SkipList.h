#define SKIPLIST_H

struct Node
// an object representing an element in the list
{
  int64_t value{};
  std::vector<Node> pointers;
  char id{};

  void changePointer(Node node, uint64_t level)
  // add/change a pointer to <node> at <level> to this node's pointers vector
  {
    if (level <= pointers.size() - 1)
    // if a pointer we want to change is on a smaller level
    // than this node's max level
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
  uint64_t maxLevel;
  uint64_t size;

  Node makeNode(int64_t value, std::vector<Node> pointers, char id = '\0');
  uint64_t randLevels();
  std::vector<Node> search(Node & target);

public:
  bool find(int64_t const x);
  bool insert(int64_t const x);
  bool remove(int64_t const x);
  size_t numElem();

  SkipList(std::vector<int64_t> const & init);

};
// SKIPLIST_H
