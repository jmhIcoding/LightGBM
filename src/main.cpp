#include <iostream>
#include <LightGBM/application.h>
#include <stdlib.h>
#include <stdio.h>
int main(int argc, char** argv) {
	printf("Hello This is a test...\n");
	printf("Welcome!\n");
  try {
    LightGBM::Application app(argc, argv);
    app.Run();
  }
  catch (const std::exception& ex) {
    std::cerr << "Met Exceptions:" << std::endl;
    std::cerr << ex.what() << std::endl;
    exit(-1);
  }
  catch (const std::string& ex) {
    std::cerr << "Met Exceptions:" << std::endl;
    std::cerr << ex << std::endl;
    exit(-1);
  }
  catch (...) {
    std::cerr << "Unknown Exceptions" << std::endl;
    exit(-1);
  }
}
