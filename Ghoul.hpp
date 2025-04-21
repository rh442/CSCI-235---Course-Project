/*
Raymond Huang
CSCI 235
Project 2
Derived Class Ghoul - Interface
*/

#ifndef Ghoul_HPP
#define Ghoul_HPP
#include <iostream>
#include "Creature.hpp"

class Ghoul:public Creature{
    public:
    enum Faction {NONE, FLESHGORGER, SHADOWSTALKER, PLAGUEWEAVER};
    /**
  Default constructor.
  Default-initializes all private members. 
  Default Category: UNDEAD
  Default decay: 0
  Default faction: NONE
  Booleans are default-initialized to False. 
*/
Ghoul();

/**
  Parameterized constructor.
  @param      : The name of the Ghoul (a reference to string)
  @param      : The category of the Ghoul (a Category enum) with default value UNDEAD
  @param      : The Ghoul's hitpoints (an integer), with default value 1 if not provided, or if the value provided is 0 or negative
  @param      : The Ghoul's level (an integer), with default value 1 if not provided, or if the value provided is 0 or negative
  @param      : A flag indicating whether the Ghoul is tame, with default value False
  @param      : The level of decay (an integer), with default value 0 if not provided, or if the value provided is negative
  @param      : The faction (a Faction enum), with default value NONE if not provided
  @param      : A flag indicating whether the Ghoul can transform, with default value False
  @post       : The private members are set to the values of the corresponding parameters.
  Hint: Notice the default arguments in the parameterized constructor.
*/
Ghoul(const std::string& name, Category category=UNDEAD, int hitpoints=1, int level=1, bool tame=false, int level_of_decay=0, Faction faction=NONE, bool can_transform=false);
/**
  Getter for the level of decay.
  @return     : The level of decay (an integer)
*/
int getDecay() const;
/**
  Setter for the level of decay.
  @param      : A reference to the level of decay (an integer)
  @pre        : The level of decay must be >= 0 (do nothing otherwise)
  @post       : The level of decay is set to the value of the parameter.
  @return     : true if the level of decay was set, false otherwise
*/
bool setDecay(const int& decay);
/**
  Getter for the faction.
  @return     : The faction (a string representation of the Faction enum)
*/
std::string getFaction() const;
/**
  Setter for the faction.
  @param      : A reference to the faction (a Faction enum)
  @post       : The faction is set to the value of the parameter.
*/
void setFaction(const Faction& faction);
/**
  Getter for the transformation.
  @return     : The transformation (a boolean)
*/
bool getTransformation() const;
/**
  Setter for the transformation.
  @param      : A reference to the transformation (a boolean)
  @post       : The transformation is set to the value of the parameter.
*/
void setTransformation(const bool& transform);

private:
    int level_of_decay_;
    Faction faction_;
    bool can_transform_;


};

#endif