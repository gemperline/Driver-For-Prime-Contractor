#include "UI/driver.hpp"

using namespace std;

namespace UI
{
  // Default constructor
  Driver::Driver()
        :_persistentData(TechnicalServices::Persistence::SingletonDB::instance()) {}

  // Destructor
  Driver::~Driver() noexcept
  { }

  // Operations
  void Driver::launch()
  {
    // 1) Fetch Role legal value list

    vector<std::string> roleLegalValues = _persistentData.findRoles();
    string selectedRole;
    string userName;
    string passPhrase;
    char continueActionsChoice = 'Y';

    while (toupper(continueActionsChoice) == 'Y')
    {
      // 2) Present login screen to user and get username, password, and valid role
      do
      {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        std::cout << "Please login\n";
        std::cout << "Name: ";
        std::getline(std::cin, userName);

        std::cout << "Pass phrase: ";
        std::getline(std::cin, passPhrase);

        unsigned menuSelection;
        do
        {
          for (unsigned i = 0; i != roleLegalValues.size(); ++i)
            std::cout << std::setw(2) << i << " - " << roleLegalValues[i] << '\n';
          std::cout << "Role (0-" << roleLegalValues.size() - 1 << "): ";
          std::cin >> menuSelection;
        } while (menuSelection >= roleLegalValues.size());

        selectedRole = roleLegalValues[menuSelection];

        // 3) Validate user is authorized for this role

        if (_accounts->isAuthenticated({userName, passPhrase, {selectedRole}}))
        {
          _logger << "Login Successful for \"" + userName + "\" as role \"" + selectedRole + "\"";
          break;
        }

        std::cout << "** Login failed\n";
        _logger << "Login failure for \"" + userName + "\" as role \"" + selectedRole + "\"";

      } while (true);

      // 4) Fetch functionality options for this role
      std::unique_ptr<Domain::Sessions::SessionHandler> sessionControl = Domain::Sessions::SessionHandler::createSession(selectedRole, userName);

      std::vector<std::string> commands = sessionControl->getCommands();
      unsigned menuSelection;
      do
      {
        for (unsigned i = 0; i != commands.size(); ++i)
          std::cout << std::setw(2) << i << " - " << commands[i] << '\n';
        std::cout << "Choose Action (0-" << commands.size() - 1 << "): ";
        std::cin >> menuSelection;
      } while (menuSelection >= roleLegalValues.size());

      std::string selectedCommand = commands[menuSelection];
      _logger << "Selected command \"" + selectedCommand + "\" chosen";

      sessionControl->executeCommand(selectedCommand);

      _logger << "Logging out user.\n";

      std::cout << "Would you like to execute another actions? (Y/N) ";
      std::cin >> continueActionsChoice;
    }
  }

} // namespace UI