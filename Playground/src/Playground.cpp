#include <Sesame.h>

class Playground : public Sesame::Application
{
public:
	Playground()
	{

	}

	~Playground()
	{
	}
};

Sesame::Application* Sesame::CreateApplication()
{
	return new Playground();
}