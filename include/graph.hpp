#include "./checkpoint.hpp"
#include "./passage.hpp"

#include <iostream>
#include <list>
#include <vector>
#include <iomanip>

using namespace std;

template<class G>
struct CEdge
{
public:
    
    typedef typename G::Node Node;
    
    Passage* _passage;
    Node* _checkpoint[2];

    CEdge(Passage*, Node*, Node*);
    ~CEdge();

private:

};


template <class G>
CEdge<G>::CEdge(Passage* passage, Node* source, Node* destiny)
{
    _passage = passage;
    _checkpoint[0] = source;
    _checkpoint[1] = destiny;
}

template <class G>
CEdge<G>::~CEdge()
{
    delete _passage;
    //delete [] _checkpoint;
}


template<class G>
struct CNode
{

public:

    typedef typename G::Edge Edge;

    Checkpoint* _checkpoint;
    list<Edge*> _branches;
    CNode(Checkpoint*);

private:


};

template<class G>
CNode<G>::CNode(Checkpoint* checkpoint)
{
    _checkpoint = checkpoint;
}

struct Graph
{
    
public:

    typedef CEdge<Graph> Edge;
    typedef CNode<Graph> Node;

    std::vector<Node*> nodes;
    
    bool find(Node*, Node*, Edge*&) const;
    bool find(Checkpoint*, Node*&) const;

    bool insert(Passage*, Node*, Node*) const;
    bool insert(Checkpoint*);

    void print();

private:



};

bool Graph::find(Node* source, Node* destiny, Edge*& p) const
{
    for(auto it = source->_branches.begin(); it != source->_branches.end(); ++it)
    {
        if((*it)->_checkpoint[1] == destiny)
        {
            p = *it;
            return true;
        }
    }
    return false;
}

bool Graph::find(Checkpoint* checkpoint, Node*& p) const
{
    for(auto it = nodes.begin(); it != nodes.end(); ++it)
    {
        if(((*it)->_checkpoint)->_name == checkpoint->_name)
        {
            p = *it;
            return true;
        }
    }
    return false;
}

bool Graph::insert(Checkpoint* checkpoint)
{
    Node* p = nullptr;
    if(find(checkpoint, p)) return 0;
    Node* to_push = new Node(checkpoint);
    nodes.push_back(to_push);
    return true;
}

bool Graph::insert(Passage* passage, Node* source, Node* destiny) const
{
    Node *a = nullptr, *b = nullptr;
    if(!(find(source->_checkpoint, a) && find(destiny->_checkpoint, b))) return false;
    Edge* go = new Edge(passage, a, b);
    Edge* back = new Edge(passage, b, a);
    a->_branches.push_back(go);
    b->_branches.push_back(back);
    return true;
}

void Graph::print()
{
    for(size_t i = 0; i < nodes.size(); i++)
    {
        std::cout << (nodes[i]->_checkpoint)->_name << ": ";
        for(auto it = nodes[i]->_branches.begin(); it != nodes[i]->_branches.end(); ++it)
        {
            std::cout << " <-> ";
            std::cout << ((*it)->_checkpoint[1])->_checkpoint->_name << std::left << std::setw(2) << (*it)->_passage->_distance << " | ";
        }
        std::cout << "\n";
    }
}

