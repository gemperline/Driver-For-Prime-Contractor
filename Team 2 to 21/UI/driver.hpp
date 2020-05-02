#pragma once

#include <memory>
#include <string>
#include <iostream>
#include <exception>
#include <iomanip>

#include "Domain/Session/Session.hpp"
#include "TechnicalServices/Persistence/PersistenceHandler.hpp"
#include "UI/UserInterfaceHandler.hpp"
using namespace std;

namespace UI
{
    class Driver : public UI::UserInterfaceHandler
    {
        public:
            using UserInterfaceHandler::UserInterfaceHandler; // inherit ctors
            Driver();

            // operations
            void launch() override;

            // abstract class destructor
            ~Driver() noexcept override;

        private:
            // smart pointers to lower architectural layers
            TechnicalServices::Persistence::PersistenceHandler &_persistentData;
    };
}
