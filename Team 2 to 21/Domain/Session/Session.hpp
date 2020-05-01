#pragma once
#pragma once

#include <memory>  // unique_ptr
#include <string>
#include <vector>

//using namespace std;


namespace Domain::Sessions
{
    // Library Package within the Domain Layer Abstract class
    // The SessionHandler abstract class serves as the generalization of all user commands
    class SessionHandler
    {
    public:
        // Constructors and assignment operations
        SessionHandler() = default;  // default ctor
        SessionHandler(const SessionHandler& original) = default;  // copy ctor
        SessionHandler(SessionHandler&& original) = default;  // move ctor

        // Operations
        
        // both
        virtual std::vector<std::string> getAction() = 0;  // retrieves the list of actions (commands)
        virtual std::vector<std::string> logoff() = 0; // log off
        
        //student
        virtual std::vector<std::string> getAssignments(const std::string) = 0; // list available assignments 
        virtual std::vector<std::string> getAssignmentActions(const std::string) = 0; // assignment actions: Submit Assignment
        virtual std::vector<std::string> executeSubmit() = 0; //list sub action for role to select

        //teacher
        virtual std::vector<std::string> getStudentAction(const std::string) = 0; // list actions add, edit, or delete
        virtual std::vector<std::string> executeStudentAction(const std::string, const std::string) = 0; // do add, edit, or delete

       
       
        // factory code to create session for user
        static std::unique_ptr<SessionHandler> createSession(const std::string& role);

        // Destructor
        // Pure virtual destructor helps force the class to be abstract, but must still be implemented
        virtual ~SessionHandler() noexcept = 0;

    protected:
        // Copy assignment operators, protected to prevent mix derived-type assignments
        SessionHandler& operator=(const SessionHandler& rhs) = default;  // copy assignment
        SessionHandler& operator=(SessionHandler&& rhs) = default;  // move assignment

    };    // class SessionHandler

    inline SessionHandler::~SessionHandler() noexcept
    {}

} // namespace Domain::Session
