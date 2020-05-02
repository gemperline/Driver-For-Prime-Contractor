#pragma once 

#include <memory>
#include <string>

namespace UI
{
    // UI layer abstract class
    class UserInterfaceHandler
    {
        private:
            /* data */
        
        public:
            // constructors
            UserInterfaceHandler()                                          = default; // defualt ctor
            UserInterfaceHandler( const UserInterfaceHandler & original )   = default; // copy ctor
            UserInterfaceHandler(       UserInterfaceHandler & original )         = default; // move ctor

            struct UIException : runtime_error 
            {
                using runtime_error::runtime_error;
            };

            struct BadUIRequest : UIException
            {
                using UIException::UIException;
            };

            // UI Factory, will throw bad request
            static unique_ptr<UserInterfaceHandler> createUI(string type);

            // operations
            virtual void launch() = 0;

            // UI destructor
            virtual ~UserInterfaceHandler() noexcept;
        
        protected:
            // copy assignment operators, protected to prevent mixing derived-type assignments
            UserInterfaceHandler & operator=( const UserInterfaceHandler  & rhs ) = default;     // copy assignment
            UserInterfaceHandler & operator=(       UserInterfaceHandler && rhs ) = default;     // move assignment

    };


    // Inline implementations
    inline UserInterfaceHandler::~UserInterfaceHandler() noexcept {};
}