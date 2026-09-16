#include <impl/includes.hxx>

int main()
{
	c_cpu cpu{};
	cpu.reset();
	cpu.execute(2);
	return 0;
}