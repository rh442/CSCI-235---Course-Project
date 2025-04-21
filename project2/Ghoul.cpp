/*
Raymond Huang
CSCI 235
Project 2
Derived Class Ghoul - Implementation
*/
#include "Ghoul.hpp"

    /**
  Default constructor.
  Default-initializes all private members. 
  Default Category: UNDEAD
  Default decay: 0
  Default faction: NONE
  Booleans are default-initialized to False. 
*/

Ghoul::Ghoul():Creature("NAMELESS",Creature::UNDEAD){
    level_of_decay_=0;
    faction_=NONE;
    can_transform_=false;

}
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
Ghoul::Ghoul(const std::string& name, Category category, int hitpoints, int level, bool tame, int level_of_decay, Faction faction, bool can_transform)
:Creature(name,category, hitpoints, level,tame)
{
  setFaction(faction);
  setTransformation(can_transform);
  if(!setDecay(level_of_decay)){
    level_of_decay_=0;
  }
}
/**
  Getter for the level of decay.
  @return     : The level of decay (an integer)
*/
int Ghoul::getDecay() const{
    return level_of_decay_;
}
/**
  Setter for the level of decay.
  @param      : A reference to the level of decay (an integer)
  @pre        : The level of decay must be >= 0 (do nothing otherwise)
  @post       : The level of decay is set to the value of the parameter.
  @return     : true if the level of decay was set, false otherwise
*/
bool Ghoul::setDecay(const int& decay){
    if(decay>=0){
        level_of_decay_=decay;
        return true;
    }
    return false;
}
/**
  Getter for the faction.
  @return     : The faction (a string representation of the Faction enum)
*/
std::string Ghoul::getFaction() const{
    switch(faction_){
        case FLESHGORGER:
            return "FLESHGORGER";
        case SHADOWSTALKER:
            return "SHADOWSTALKER";
        case PLAGUEWEAVER:
            return "PLAGUEWEAVER";
        default:
            return "NONE";
            
    }
}
/**
  Setter for the faction.
  @param      : A reference to the faction (a Faction enum)
  @post       : The faction is set to the value of the parameter.
*/
void Ghoul::setFaction(const Faction& faction){
    faction_=faction;
}
/**
  Getter for the transformation.
  @return     : The transformation (a boolean)
*/
bool Ghoul::getTransformation() const{
    return can_transform_;
}
/**
  Setter for the transformation.
  @param      : A reference to the transformation (a boolean)
  @post       : The transformation is set to the value of the parameter.
*/
void Ghoul::setTransformation(const bool& transform){
    can_transform_=transform;
}
