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
    typedef typename G::P Passage;
    
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
    delete [] _checkpoint;
}


template<class G>
struct CNode
{

public:

    typedef typename G::Edge Edge;
    typedef typename G::C Checkpoint;

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

template<class _N, class _E>
struct Graph
{
    
public:

    typedef _N C;
    typedef _E P;
    typedef Graph<_N,_E> G;
    typedef CEdge<G> Edge;
    typedef CNode<G> Node;

    std::vector<Node*> nodes;
    
    bool find(Node*, Node*, Edge*&) const;
    bool find(Checkpoint*, Node*&) const;

    bool insert(Passage*, Node*, Node*) const;
    bool insert(Checkpoint*);

    void print();

private:



};

template<class _N, class _E>
bool Graph<_N, _E>::find(Node* source, Node* destiny, Edge*& p) const
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

template<class _N, class _E>
bool Graph<_N, _E>::find(Checkpoint* checkpoint, Node*& p) const
{
    for(auto it = nodes.begin(); it != nodes.end(); ++it)
    {
        if((*it)->_checkpoint->get_name() == checkpoint->get_name())
        {
            p = *it;
            return true;
        }
    }
    return false;
}

template<class _N, class _E>
bool Graph<_N, _E>::insert(Checkpoint* checkpoint)
{
    Node* p = nullptr;
    if(find(checkpoint, p)) return 0;
    Node* to_push = new Node(checkpoint);
    nodes.push_back(to_push);
    return true;
}

template<class _N, class _E>
bool Graph<_N, _E>::insert(Passage* passage, Node* source, Node* destiny) const
{
    Node *a = nullptr, *b = nullptr;
    if(!(find(source->_checkpoint, a) && find(destiny->_checkpoint, b))) return false;
    Edge go = Edge(passage, a, b);
    Edge back = Edge(passage, b, a);
    a->_branches.push_back(go);
    b->_branches.push_back(back);
    return true;
}

template<class _N, class _E>
void Graph<_N, _E>::print()
{
    for(size_t i = 0; i < nodes.size(); i++)
    {
        std::cout << nodes[i]._checkpoint->get_name() << ": ";
        for(auto it = nodes[i]->_branches.begin(); it != nodes[i]->_branches.end(); ++it)
        {
            std::cout << " <-> ";
            std::cout << (*it)->_checkpoint[1]->get_name() << std::left << std::setw(2) << (*it)->_passage->_distance << " | ";
        }
        std::cout << "\n";
    }
}

