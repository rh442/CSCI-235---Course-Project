/*
Raymond Huang
CSCI 235
Project 2
Derived Class Dragon - Interface
*/

#ifndef Dragon_HPP
#define Dragon_HPP
#include <iostream>
#include "Creature.hpp"


class Dragon:public Creature{
    public:
    enum Element {NONE,FIRE,WATER,EARTH,AIR};
    /**
  Default constructor.
  Default-initializes all private members. 
  Default Category: MYSTICAL
  Default element: NONE
  Default number of head(s): 1
  Booleans are default-initialized to False. 
*/
Dragon();
/**
  Parameterized constructor.
  @param      : The name of the Dragon (a reference to string)
  @param      : The category of the Dragon (a Category enum) with default value MYSTICAL
  @param      : The Dragon's hitpoints (an integer), with default value 1 if not provided, or if the value provided is 0 or negative
  @param      : The Dragon's level (an integer), with default value 1 if not provided, or if the value provided is 0 or negative
  @param      : A flag indicating whether the Dragon is tame, with default value False
  @param      : The element (an Element enum), with default value NONE if not provided
  @param      : The number of heads (an integer), with default value 1 if not provided, or if the value provided is 0 or negative
  @param      : A flag indicating whether the Dragon can fly, with default value False
  @post       : The private members are set to the values of the corresponding parameters.
  Hint: Notice the default arguments in the parameterized constructor.
*/
Dragon(const std::string& name, Category category=MYSTICAL, int hitpoints=1, int level=1, bool tame=false, Element element=NONE, int num_head=1, bool can_fly=false);
/**
  Getter for the element.
  @return     : The element (a string representation of the Element enum)
*/
std::string getElement() const;
/**
  Setter for the element.
  @param      : A reference to the element (an Element enum)
  @post       : The element is set to the value of the parameter.
*/
void setElement(const Element& ele) ;
/**
  Getter for the number of heads.
  @return     : The number of heads (an integer)
*/
int getNumberOfHeads() const;
/**
  Setter for the number of heads.
  @param      : A reference to the number of heads (an integer)
  @pre        : The number of heads is > 0. Do nothing for invalid values.
  @post       : The number of heads is set to the value of the parameter.
  @return     : True if the number of heads is set, false otherwise.
*/
bool setNumberOfHeads(const int& num_head);
/**
  Getter for the flight flag.
  @return     : The flight flag (a boolean)
*/
bool getFlight() const;
/**
  Setter for the flight flag.
  @param      : A reference to the flight flag (a boolean)
  @post       : The flight flag is set to the value of the parameter.
*/
void setFlight(const bool& flight);



private:
        //An Element representing their affinity
        Element affinity_;
        // An integer representing the number of heads
        int num_heads_;
        //A boolean indicating if they can fly
        bool can_fly_;

};


#endif