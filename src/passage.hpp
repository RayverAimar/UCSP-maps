#include <iostream>


using namespace std;

struct Passage
{
public:
    float _distance;
    unsigned int _floor;
    

    Passage(float, unsigned int, double);
    ~Passage();

    double get_time_to_pass();

private:
    double _time_to_pass;
};

Passage::Passage(float distance, unsigned int floor, double time_to_pass) : _distance(distance), _floor(floor), _time_to_pass(time_to_pass)
{
}

Passage::~Passage()
{

}