#include <ProcessComp.h>
#include <TunzalysisConfig.h>

int main(int argc, char *argv[])
{
	std::cout << "Welcome to " << argv[0] << " " << Tunzalysis_VERSION_MAJOR << "." << Tunzalysis_VERSION_MINOR << std::endl;

	startProc();		// start processing
	return 0;
}
