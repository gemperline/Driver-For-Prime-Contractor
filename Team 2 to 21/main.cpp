#include <exception>
#include <iostream>
#include <memory>
#include <new>
#include <iostream>
#include <locale>


#include "TechnicalServices/Persistence/PersistenceHandler.hpp"
#include "UI/UserInterfaceHandler.hpp"
#include "UI/driver.hpp"

int main(/*int argc, char argv[] */)
{
  try
  {
    std::cout << "\nLibrary Inventory system initializing ...\n\n";

    // Smart pointer (for proper, exception safe memory management) to interface set to new instance of a specific implementation of
    // the interface.
    auto userInterface = UI::UserInterfaceHandler::createUI("Simple UI");
    
    std::cout << "\nInitialization completed successfully\n";

    char response;
    do
    {
      std::cout << "Ready to transition into Operational State? (Q/Y/N) ";
      std::cin >> response;
      response = std::toupper(response, std::locale());
    } while (response != 'Y' && response != 'Q');

    std::string command;
    if (response == 'Y')
      userInterface->launch();

    std::cout << "\nProgram complete, initiating shutdown\n";
  }

  catch (const std::bad_alloc &ex)
  {
    std::cerr << "Fatal:  Uncaught memory allocation exception\n\n"
              << ex.what() << '\n';
  }

  catch (const std::exception &ex)
  {
    std::cerr << "Fatal:  Uncaught standard exception\n"
              << ex.what() << '\n';
  }

  catch (...)
  {
    std::cerr << "Fatal:  Uncaught (unknown type) exception\n";
  }
}