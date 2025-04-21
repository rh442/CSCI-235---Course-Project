#include "Creature.hpp"
//Implementation of Creature class
 /**
      Default constructor.
      Default-initializes all private members. 
      Default creature name: "NAMELESS". 
      Booleans are default-initialized to False. 
      Default enum value: UNKNOWN 
      Default Hitpoints and Level: 1.
   */
  Creature::Creature(){
    name_="NAMELESS";
    category_=UNKNOWN;
    hitpoints_=1;
    level_=1;
    is_tame_=false;
}
/* Parameterized constructor.
      @param      : A reference to the name of the creature (a string). Set the creature's name to NAMELESS if the provided string contains non-alphabetic characters.
      @param      : The category of the creature (a Category enum) with default value UNKNOWN
      @param      : The creature's hitpoints (an integer) , with default value 1 if not provided, or if the value provided is 0 or negative
      @param      : The creature's level (an integer), with default value 1 if not provided, or if the value provided is 0 or negative
      @param      : A flag indicating whether the creature is tame, with default value False
      @post       : The private members are set to the values of the corresponding parameters. The name is converted to UPPERCASE if it consists of alphabetical characters only, otherwise it is set to NAMELESS.
  */

Creature::Creature(const std::string &name, const Category cat,const int hitpoint,const int level,const bool is_tame){
    if(setName(name)==false){
        name_="NAMELESS";
    }
    else{
        setName(name);
    }
    setCategory(cat);
    if(setHitpoints(hitpoint)==true){
        setHitpoints(hitpoint);
    }
    else{
        hitpoints_=1;
    }
    if(setLevel(level)==true){
        setLevel(level);
    }
    else{
        level_=1;
    }
    setTame(is_tame);
}
/**
      @return : the name of the Creature
  */
std::string Creature::getName() const{
    return name_;
}
 /**
      @return : the category of the Creature (in string form)
   */
std::string Creature::getCategory() const{
    
    switch(category_){
        case UNDEAD:
        return "UNDEAD";
        break;
        case MYSTICAL:
        return "MYSTICAL";
        break;
        case ALIEN:
        return "ALIEN";
        break;
        default:
        return "UNKNOWN";
    }
}
 /**
      @return : the value stored in hitpoints_
   */
int Creature::getHitpoints() const{
    return hitpoints_;
}
  /**
      @return : the value stored in level_
   */

int Creature::getLevel() const{
    return level_;
}
 /**
    @return true if the creature is tame, false otherwise
    Note: this is an accessor function and must follow the same convention as all accessor functions even if it is not called getTame
   */
bool Creature::isTame() const{
   return is_tame_;
}
/**
    @param : the name of the Creature, a reference to string
    @post  : sets the Creature's name to the value of the parameter in UPPERCASE. 
             (convert any lowercase character to uppercase)
             Only alphabetical characters are allowed. 
           : If the input contains non-alphabetic characters, do nothing.
    @return : true if the name was set, false otherwise
*/
bool Creature::setName(const std::string&sNAM){
    std::string dim=sNAM;
    int dum=sNAM.size();
    for(int i=0;i<dum;i++){
        if(isalpha(sNAM[i])==false){
            return false;
        }

    }
    dim="";
    for(int i=0;i<dum;i++){
        dim+=toupper(sNAM[i]);
    }
    name_=dim;
    return true;
}
/**
      @param  : a reference to Category, the category of the Creature (an enum)
      @post   : sets the Creature's category to the value of the parameter
              : If the given category was invalid, set category_ to UNKNOWN.
*/
void Creature::setCategory( const Category& sCAT){
    /*if(sCAT>=0&&sCAT<=3){
    category_=sCAT;
    }
    else{
        category_=UNKNOWN;
    }*/
    switch(sCAT){
        case UNDEAD:
        category_=UNDEAD;
        break;
        case MYSTICAL:
        category_=MYSTICAL;
        break;
        case ALIEN:
        category_=ALIEN;
        break;
        default:
        category_=UNKNOWN;
    }
}
  /**
    @param  : a reference to integer that represents the creature's hitpoints
    @pre    : hitpoints >= 0 : Characters cannot have negative hitpoints 
              (do nothing for invalid input)
    @post   : sets the hitpoints private member to the value of the parameter
    @return : true if the hitpoints were set, false otherwise
  */
 bool Creature::setHitpoints(const int&sHP){
    if(sHP>=1){
        hitpoints_=sHP;
        return true;
    }
    else{
        return false;
    }
 }
 /**
    @param  : a reference to integer level
    @pre    : level >= 0 : Characters cannot have a negative level
    @post   : sets the level private member to the value of the parameter 
             (do nothing for invalid input)
    @return : true if the level was set, false otherwise
  */
 bool Creature::setLevel(const int&sLV){
    if(sLV>=1){
        level_=sLV;
        return true;
    }
    else{
        return false;
    }
 }
 /**
      @param  : a reference to boolean value
      @post   : sets the tame flag to the value of the parameter
  */
 void Creature::setTame(const bool&sTAM){
    is_tame_=sTAM;

 }


 /**
    @post     : displays Creature data in the form:
              "[NAME]\n
               Category: [CATEGORY]\n
               Level: [LEVEL]\n
               Hitpoints: [Hitpoints]\n
               Tame: [TRUE/FALSE]"   
*/
void Creature::display() const{
    std::cout<<getName()<<std::endl;
    std::cout<<"Category: "<<getCategory()<<std::endl;
    std::cout<<"Level: "<<getLevel()<<std::endl;
    std::cout<<"Hitpoints: "<<getHitpoints()<<std::endl;
    if(isTame()==true){
        std::cout<< "Tame: TRUE"<<std::endl;
    }
    if(isTame()==false){
        std::cout<< "Tame: FALSE"<<std::endl;
    }
}

