
#include <string>

struct Checkpoint
{

public:

    unsigned int _floor;
    std::string _name;

    Checkpoint(const unsigned int, const std::string);
    ~Checkpoint();

    std::string get_name();
    bool set_name(std::string);

private:
    
};

Checkpoint::Checkpoint(const unsigned int floor, const std::string name) : _floor(floor), _name(name)
{

}

Checkpoint::~Checkpoint()
{
    
}