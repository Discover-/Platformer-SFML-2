#ifndef CALLBACK_HPP_INCLUDED
#define CALLBACK_HPP_INCLUDED

#include "menuitem.hpp"

///\brief Class for managing a callback function
template <class Object>
class Callback
{
    public:
        ///\brief Default constructor taking no arguments
        Callback()
        :callback(nullptr), memberCallback(nullptr), classPointer(nullptr)
        {

        };

        ///\brief Constructor creating a callback for global function or static member function
        Callback(void (*_callback)(Object*))
        :callback(_callback), memberCallback(nullptr), classPointer(nullptr)
        {

        };


        ///\brief Constructor creating a callback for non-static member function
        Callback(void (*_memberCallback)(void*, Object*), void* _classPointer)
        :callback(nullptr), memberCallback(_memberCallback), classPointer(_classPointer)
        {

        };

        void operator()(Object& obj, sf::Event& event)
        {
            if (callback)
                callback(obj, event);
            if (memberCallback)
                memberCallback(classPointer, obj, event);
        };

        ///\brief Set callback for global function or static member function
        void setCallback(void (*_callback)(Object*))
        {
            callback = _callback;
            memberCallback = nullptr;
            classPointer = nullptr;
        };

        ///\brief Set callback for non-static member function
        void setCallback(void (*_callback)(void*, Object*), void* _classPointer)
        {
            memberCallback = _callback;
            classPointer = _classPointer;
            callback = nullptr;
        };

    protected:
        ///Callback function for non-static member functions, some tricks are needed
        void (*callback)(Object*, sf::Event&);

        ///Callback function for non-static member functions, some tricks are needed
        ///Basically, a static redirect-function is given at construct, which converts classPointer into a pointer of its own type, so the non-static function can be called(see example in MainMenu(mainmenu.hpp))
        void (*memberCallback)(void*, Object*, sf::Event&);
        void* classPointer;
};

#endif // CALLBACK_HPP_INCLUDED
