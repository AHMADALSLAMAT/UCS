
#include <iostream>
#include <vector>
#include <queue>

using std::vector;
using std::priority_queue;
using std::cout;
using std::endl;

struct Node
{
  char name_;
  vector<Node*> connect_;
  vector<int> cost_;

  Node(char name)
  :name_(name), connect_(), cost_()
  {}

  void connectsTo(Node* destination, int cost)
  {
    connect_.push_back(destination);
    cost_.push_back(cost);
  }
};

struct Path
{
  int cost_;
  vector<Node*> path_;

  Path()
  :cost_(0), path_()
  {}

  Path(const Path& rhs)
  :cost_(rhs.cost_), path_()
  {
    vector<Node*>::const_iterator i;

    for (i = rhs.path_.begin(); i != rhs.path_.end(); ++i)
    {
      path_.push_back(*i);
    }
  }

  bool operator>(const Path& rhs) const
  {
    return cost_ > rhs.cost_;
  }

  void append(Node* node)
  {
    path_.push_back(node);
  }
};

void UCS(Node* start, Node* goal);
void displayPath(const Path& path);
void displayFrontier(priority_queue<Path, vector<Path>,
                     std::greater<Path>> frontier);


 // main function
int main()
{
  // add NODE
  Node* S = new Node('S');
  Node* a = new Node('a');
  Node* b = new Node('b');
  Node* c = new Node('c');
  Node* G = new Node('G');

  // COST
  S->connectsTo(a, 1);
  S->connectsTo(b, 4);
  a->connectsTo(b, 3);
  a->connectsTo(c, 6);
  a->connectsTo(G, 7);
  b->connectsTo(c, 8);
  c->connectsTo(G, 10);

  //  START AND goal state
  UCS(S, G);
}

void UCS(Node* start, Node* goal)
{
  int iter_number = 0;
  Node* current_node;
  priority_queue<Path, vector<Path>, std::greater<Path>> frontier;

  Path root;
  root.append(start);
  root.cost_ = 0;
  frontier.push(root);

  cout << "Initialisation: ";
  displayFrontier(frontier);
  cout << endl;

  vector<Node*>::iterator i;

  while (!frontier.empty())
  {
    iter_number++;

    Path current_path;
    current_node = frontier.top().path_.back();
    current_path = frontier.top();

    cout << "Iteration " << iter_number << ": ";
    displayFrontier(frontier);
    cout << endl;

    frontier.pop();

    if (current_node == goal)
    {
      cout << endl << "Solution: ";
      displayPath(current_path);
      cout << " costs " << current_path.cost_ << endl;
      return;
    }
    else
    {
      vector<int>::iterator cost_iter;
      cost_iter = current_node->cost_.begin();

      for (i = current_node->connect_.begin();
           i != current_node->connect_.end(); ++i)
      {
        Path temp_path(current_path);
        temp_path.append(*i);
        temp_path.cost_ += *cost_iter;
        cost_iter++;
        frontier.push(temp_path);
      }
    }
  }

  cout << "Solution does not exist." << endl;
}

void displayPath(const Path& path)
{
  vector<Node*>::const_iterator i;

  for (i = path.path_.begin(); i != path.path_.end(); ++i)
      cout << (*i)->name_;
}

void displayFrontier(priority_queue<Path, vector<Path>,
                     std::greater<Path>> frontier)
{
  cout << "[ {";

  while (frontier.size() > 0)
  {
    displayPath(frontier.top());
    frontier.pop();

    if (frontier.size() > 0)
      cout << "}, {";
    else
      cout << "} ]";
  }
}
