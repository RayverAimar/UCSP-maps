
#include <string>

struct Checkpoint
{

public:

    unsigned int _floor;
    
    Checkpoint(const unsigned int);
    ~Checkpoint();

    std::string get_name();
    bool set_name(std::string);

private:
    std::string _name;
};

Checkpoint::Checkpoint(const unsigned int floor) : _floor(floor)
{

}

Checkpoint::~Checkpoint()
{
    
}