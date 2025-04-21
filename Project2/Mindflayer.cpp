/*
Raymond Huang
CSCI 235
Project 2
Derived Class Mindflayer - Implementation
*/
#include "Mindflayer.hpp"




 /**
        Default constructor.
         Default-initializes all private members. 
         Default Category: ALIEN
        Default summoning: False
        */
Mindflayer::Mindflayer():Creature("Nameless",Creature::ALIEN){
    summoning_=false;

}
/*Parameterized constructor.
  @param      : A reference to the name of the Mindflayer (a string)
  @param      : The category of the Mindflayer (a Category enum) with default value ALIEN
  @param      : The Mindflayer's hitpoints (an integer), with default value 1 if not provided, or if the value provided is 0 or negative
  @param      : The Mindflayer's level (an integer), with default value 1 if not provided, or if the value provided is 0 or negative
  @param      : A flag indicating whether the Mindflayer is tame, with default value False
  @param      : The projectiles (a vector of Projectile structs), with default value an empty vector if not provided
  @param      : A flag indicating whether the Mindflayer can summon, with default value False
  @param      : The affinities (a vector of Variant enums), with default value an empty vector if not provided
  @post       : The private members are set to the values of the corresponding parameters.
  Hint: Notice the default arguments in the parameterized constructor.
*/
Mindflayer::Mindflayer(const std::string& name,Category category,int hitpoints,int level,bool tame,std::vector<Projectile> proj,bool summon,std::vector<Variant> var)
:Creature(name,category, hitpoints, level,tame)
{
    
    setProjectiles(proj);
    setAffinities(var);
    setSummoning(summon);
}
/**
  Getter for the projectiles.
  @return     : The projectiles (a vector of Projectile structs)
*/
std::vector<Mindflayer::Projectile> Mindflayer::getProjectiles() const{
    return projectiles_;
}
/**
  Setter for the projectiles.
  @param      : A reference to the projectiles (a vector of Projectile structs)
  @post       : The projectiles are set to the value of the parameter. There should not be any duplicate projectiles in Mindflayer's projectiles vector.
        : For example, if the vector in the given parameter contains the following Projectiles: {{PSIONIC, 2}, {TELEPATHIC, 1}, {PSIONIC, 1}, {ILLUSIONARY, 3}}, 
        : the projectiles vector should be set to contain the following Projectiles: {{PSIONIC, 3}, {TELEPATHIC, 1}, {ILLUSIONARY, 3}}.
        : If the quantity of a projectile is 0 or negative, it should not be added to the projectiles vector. 
        : Note the order of the projectiles in the vector.
*/
void Mindflayer::setProjectiles(const std::vector< Projectile>&proje){
  std::vector<Projectile> proj = proje;
    int size=proj.size();
    for(int i=0;i<size;i++){
       if(proj[i].quantity_<=0){
            proj.erase(proj.begin()+i);
            size--;
            i=i-1;
          }
    }
    

    for(int i=0;i<size;i++){
        for(int j=i+1;j<size;j++){
         
            if(proj[i].type_==proj[j].type_){
                proj[i].quantity_=proj[i].quantity_+proj[j].quantity_;
                proj.erase(proj.begin()+j);
                size--;
            }
        }

        
    }
    projectiles_=proj;


}

/**
  Getter for the summoning.
  @return     : The summoning (a boolean)
*/
bool Mindflayer::getSummoning() const{
  return summoning_;
}
/**
  Setter for the summoning.
  @param      : A reference to the summoning (a boolean)
  @post       : The summoning is set to the value of the parameter.
*/
void Mindflayer::setSummoning(const bool& sum){
  summoning_=sum;

}
/**
  Getter for the affinities.
  @return     : The affinities (a vector of Variant enums)
*/
std::vector<Mindflayer::Variant> Mindflayer::getAffinities() const{
  return affinities_;
}
/**
  Setter for the affinities.
  @param      : A reference to the affinities (a vector of Variant enums)
  @post       : The affinities are set to the value of the parameter.
        : There should not be any duplicate affinities in Mindflayer's affinities vector. 
        : For example, if the vector in the given parameter contains the following affinities: {PSIONIC, TELEPATHIC, PSIONIC, ILLUSIONARY}, 
        : the affinities vector should be set to contain the following affinities: {PSIONIC, TELEPATHIC, ILLUSIONARY}.
        : Note the order of the affinities in the vector.
*/
void Mindflayer::setAffinities( const std::vector< Variant>&afini){
  std::vector<Variant> afin = afini;
  int siz=afin.size();
  for(int i=0;i<siz;i++){
        for(int j=i+1;j<siz;j++){
            if(afin[i]==afin[j]){
                afin.erase(afin.begin()+j);
                siz--;
            }
        }

        
    }

affinities_=afin;
}
/**
  @param       : A reference to the Variant 
  @return      : The string representation of the variant
*/
std::string Mindflayer::variantToString(const Variant& var){
    switch(var){
      case PSIONIC:
        return "PSIONIC";
      case TELEPATHIC:
        return "TELEPATHIC";
      case ILLUSIONARY:
        return "ILLUSIONARY";
    }
}



