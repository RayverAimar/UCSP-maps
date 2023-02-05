#include <iostream>

using namespace std;


struct Checkpoint
{

public:

    unsigned int _floor;

    Checkpoint(const unsigned int);
    ~Checkpoint();

private:

};

Checkpoint::Checkpoint(const unsigned int floor) : _floor(floor)
{

}

Checkpoint::~Checkpoint()
{
    
}