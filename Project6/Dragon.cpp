/*
CSCI235 Spring 2024
Project 4 - MycoMorsels
Georgina Woo
Dec 24 2023
Dragon.cpp implements the constructors and private and public functions of the Dragon class
*/

#include "Dragon.hpp"

Dragon::Dragon() : element_{NONE}, number_of_heads_{1}, flight_{false}
{
    setCategory(MYSTICAL); 
    
}


Dragon::Dragon(const std::string& name, Category category, int hitpoints, int level, bool tame, Element element, int number_of_heads, bool flight) : Creature(name, category, hitpoints, level, tame)
{
    element_ = element;
    if(!setNumberOfHeads(number_of_heads))
    {
        number_of_heads_ = 1;
    }
    flight_ = flight;
}

std::string Dragon::getElement() const
{
    switch(element_)
    {
        case FIRE:
            return "FIRE";
        case WATER:
            return "WATER";
        case EARTH:
            return "EARTH";
        case AIR:
            return "AIR";
        default:
            return "NONE";
    }
}

void Dragon::setElement(const Element& element)
{
    element_ = element;
}

int Dragon::getNumberOfHeads() const
{
    return number_of_heads_;
}

bool Dragon::setNumberOfHeads(const int& number_of_heads)
{
    if(number_of_heads > 0)
    {
        number_of_heads_ = number_of_heads;
        return true;
    }
    else
    {
        return false;
    }
}

bool Dragon::getFlight() const
{
    return flight_;
}

void Dragon::setFlight(const bool& flight)
{
    flight_ = flight;
}


void Dragon::display() const
{
    std::cout << "DRAGON - " << getName() << std::endl;
    std::cout << "CATEGORY: " << getCategory() << std::endl;
    std::cout << "HP: " << getHitpoints() << std::endl;
    std::cout << "LVL: " << getLevel() << std::endl;
    std::cout << "TAME: " << (isTame() ? "TRUE" : "FALSE") << std::endl;
    std::cout << "ELEMENT: " << getElement() << std::endl;
    std::cout << "HEADS: " << getNumberOfHeads() << std::endl;
    std::cout << "IT " << (getFlight() ? "CAN" : "CANNOT") << " FLY" << std::endl;
}



bool Dragon::eatMycoMorsel()
{
    if(getCategory() == "UNDEAD")
    {
        setTame(true);
        setHitpoints(getHitpoints() + 1);
        return false;
    }
    else if(getCategory() == "ALIEN")
    {
        setHitpoints(getHitpoints() + 1);
        return false;
    }
    else if(getCategory() == "MYSTICAL")
    {
        if(getElement() == "FIRE" || getElement() == "EARTH")
        {
            setHitpoints(getHitpoints() + 1);
            return false;
        }
        else if(getHitpoints() == 1)
        {
            return true;
        }
        else
        {
            setHitpoints(getHitpoints() - 1);
            setTame(false);
            return false;
        }
    }
    else
    {
        return false;
    }
}
/**
  * @param: A const reference to int corresponding to the attack to be added to the attack queue.
  * @post: Adds an attack to the attack queue based on the int parameter.
  * Here are the attacks for the Dragon:
  
* 1: Attack name: BITE
*      if ALIEN: 4 PHYSICAL
*      if MYSTICAL: 2 PHYSICAL, and additional damage of 1 [FIRE/WATER/EARTH/AIR] if the Dragon has an elemental affinity of FIRE, WATER, EARTH, or AIR)
*      if UNDEAD: 2 PHYSICAL, 1 POISON
*      if UNKNOWN: 2 PHYSICAL

* 2: Attack name: STOMP
*      if ALIEN: 2 PHYSICAL
*      if MYSTICAL: 1 PHYSICAL, and additional damage of 1 [FIRE/WATER/EARTH/AIR] if the Dragon has an elemental affinity of FIRE, WATER, EARTH, or AIR)
*      if UNDEAD: 1 PHYSICAL, 1 POISON
*      if UNKNOWN: 1 PHYSICAL

* 3: Attack name: [ELEMENTAL BREATH/BAD BREATH], where the name is ELEMENTAL BREATH if the Dragon has an elemental affinity, otherwise it is BAD BREATH
*      if ALIEN: 6 [POISON/FIRE/WATER/EARTH/AIR], where the damage type is the Dragon's elemental affinity if it has one, otherwise it is POISON
*      if MYSTICAL: 3 [POISON/FIRE/WATER/EARTH/AIR], where the damage type is the Dragon's elemental affinity if it has one, otherwise it is POISON
*      if UNDEAD: 3 [POISON/FIRE/WATER/EARTH/AIR], 1 POISON. The damage types and amount are added to the vector as two separate entries, even if both entries are POISON type.
*      if UNKNOWN: 3 [POISON/FIRE/WATER/EARTH/AIR] where the damage type is the Dragon's elemental affinity if it has one, otherwise it is POISON  
*/
void Dragon::addAttack(const int&atk){
    Attack add;
    std::string atk_name="";
    std::vector<int> qtys={};
    std::vector<std::string> elements={};
    //input is 1
    if(atk==1){
        //atk 1 is BITE
        atk_name="BITE";
        //Category::ALIEN have 4 PHYSICAL
        if(getCategory()=="ALIEN"){
            qtys.push_back(4);
            elements.push_back("PHYSICAL");
        }
        //CATEGORY MYSTICAL have 2 PHYSICAL and 1 ELEMENTAL 
        else if(getCategory()=="MYSTICAL"){
            qtys.push_back(2);
            elements.push_back("PHYSICAL");
            if(getElement()!="NONE"){
                qtys.push_back(1);
                elements.push_back(getElement());
            }
           
        }
        //CATEGORY UNDEAD 2 PHYSICAL and 1 POISON
        else if(getCategory()=="UNDEAD"){
            qtys.push_back(2);
            elements.push_back("PHYSICAL");
            qtys.push_back(1);
            elements.push_back("POISON");
        }
        //CATEGORY UNKNOWN - 2 PHYSICAL
        else{
            qtys.push_back(2);
            elements.push_back("PHYSICAL");
        }
    }
    //ATK 2 == STOMP
    else if(atk==2){
        atk_name="STOMP";
        //CATEGORY ALIEN == 2 PHYSICAL
        if(getCategory()=="ALIEN"){
            qtys.push_back(2);
            elements.push_back("PHYSICAL");
        }
        //CATEGORY MYSTICAL == 1 PHYSICAL && 1 ELEMENTAL    
        else if(getCategory()=="MYSTICAL"){
            qtys.push_back(1);
            elements.push_back("PHYSICAL");
            if(getElement()!="NONE"){
                qtys.push_back(1);
                elements.push_back(getElement());
            }
        }
        //CATEGORY UNDEAD -  1 PHYSICAL && 1 POISON
        else if(getCategory()=="UNDEAD"){
            qtys.push_back(1);
            elements.push_back("PHYSICAL");
            qtys.push_back(1);
            elements.push_back("POISON");
        }
        //UNKNOWN CATEGORY - 1 PHYSICAL
        else{
            qtys.push_back(1);
            elements.push_back("PHYSICAL");
        }


    }
    //ATK 3 BREATH ATTACK
    else if(atk==3){
        //IF IT HAS AN AFFINITY IT HAS ELEMENTAL BREATH, ELSE BAD BREATH
        if(getElement()!="NONE"){
            atk_name="ELEMENTAL BREATH";
        }
        else{
            atk_name="BAD BREATH";
        }
        //ALIEN HAS 6 ELEMENTAL DMG ,NONE ELEMENT GET POISON
        if(getCategory()=="ALIEN"){
            qtys.push_back(6);
            if(getElement()!="NONE"){
                elements.push_back(getElement());
            }
            else{
                elements.push_back("POISON");
            }
        }
        //MYSTICAL HAS 3 ELEMENTAL DMG
        else if(getCategory()=="MYSTICAL"){
            qtys.push_back(3);
            if(getElement()!="NONE"){
                elements.push_back(getElement());
            }
            else{
                elements.push_back("POISON");
            }
        }
        //UNDEAD HAS 3 ELEMENTAL DMG AND 1 POISON
        else if(getCategory()=="UNDEAD"){
            qtys.push_back(3);
            if(getElement()!="NONE"){
                elements.push_back(getElement());
            }
            else{
                elements.push_back("POISON");
            }
            qtys.push_back(1);
            elements.push_back("POISON");

        }
        //UKNOWN HAS 3 ELEMENTAL DMG
        else{
            qtys.push_back(3);
            if(getElement()!="NONE"){
                elements.push_back(getElement());
            }
            else{
                elements.push_back("POISON");
            }
        }
    }
    else{
        
    }
    add.name_=atk_name;
    add.damage_=qtys;
    add.type_=elements;
    Creature::addAttack(add);
} 

/**
  * @post:  displays the attacks of the Dragon in the form:
  *        [DRAGON] Choose an attack (1-3):\n1: BITE\t\t2: STOMP\t\t3: ELEMENTAL BREATH\n
  */
void Dragon::displayAttacks() const {
    std::cout<<"[DRAGON] Choose an attack (1-3):\n1: BITE\t\t2: STOMP\t\t3: ELEMENTAL BREATH\n";
}

