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
        Callback(void (*_callback)(Object*, sf::Event&))
        :callback(_callback), memberCallback(nullptr), classPointer(nullptr)
        {

        };


        ///\brief Constructor creating a callback for non-static member function
        Callback(void (*_memberCallback)(void*, Object*), void* _classPointer)
        :callback(nullptr), memberCallback(_memberCallback), classPointer(_classPointer)
        {

        };

        bool operator()(Object* obj, sf::Event& event)
        {
            if (callback)
            {
                callback(obj, event);
                return true;
            }
            if (memberCallback)
            {
                memberCallback(classPointer, obj, event);
                return true;
            }
            return false;
        };

        ///\brief Set callback for global function or static member function
        void set(void (*_callback)(Object*, sf::Event&))
        {
            callback = _callback;
            memberCallback = nullptr;
            classPointer = nullptr;
        };

        ///\brief Set callback for non-static member function
        void set(void (*_callback)(void*, Object*, sf::Event&), void* _classPointer)
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
        void* classPointer; ///<Class Pointer needed for callback to non-static member function
};

///\brief Base struct for callback system
template <class Item>
struct CallbackSystem
{
    Callback<Item> TextEntered;                 ///< A character was entered (data in event.text)
    Callback<Item> KeyPressed;                  ///< A key was pressed (data in event.key)
    Callback<Item> KeyReleased;                 ///< A key was released (data in event.key)
    Callback<Item> MouseWheelMoved;             ///< The mouse wheel was scrolled (data in event.mouseWheel)
    Callback<Item> MouseButtonPressed;          ///< A mouse button was pressed (data in event.mouseButton)
    Callback<Item> MouseButtonReleased;         ///< A mouse button was released (data in event.mouseButton)
    Callback<Item> MouseMoved;                  ///< The mouse cursor moved (data in event.mouseMove)
    Callback<Item> JoystickButtonPressed;       ///< A joystick button was pressed (data in event.joystickButton)
    Callback<Item> JoystickButtonReleased;      ///< A joystick button was released (data in event.joystickButton)
    Callback<Item> JoystickMoved;               ///< The joystick moved along an axis (data in event.joystickMove)
    Callback<Item> JoystickConnected;           ///< A joystick was connected (data in event.joystickConnect)
    Callback<Item> JoystickDisconnected;        ///< A joystick was disconnected (data in event.joystickConnect)
};

#endif // CALLBACK_HPP_INCLUDED
