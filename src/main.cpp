#include "../include/graph.hpp"

using namespace std;

int main()
{
    Graph<Checkpoint, Passage> sketch;
    Checkpoint* main_gate = new Checkpoint(1);
    Checkpoint* second_gate = new Checkpoint(2);
    Passage* first_passage = new Passage(17.7, 1, 20.0);
    sketch.insert(main_gate);
    sketch.insert(second_gate);

}