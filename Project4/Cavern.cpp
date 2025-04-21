/*
CSCI235 Spring 2024
Project 3 - Cavern Class
Georgina Woo
Dec 24 2023
Taven.cpp declares the Cavern class along with its private and public members
*/
#include "Cavern.hpp"


Cavern::Cavern() : ArrayBag<Creature*>(), level_sum_{0}, tame_count_{0} {
}
Cavern::Cavern(const std::string &csvfile){
  std::ifstream fin(csvfile);
    if(fin.fail()){
        std::cerr<<"file cannot be opened for reading."<<std::endl;
        exit(1);
    }
    std::string junk;
    std::getline(fin,junk);
    //TYPE NAME CATEGORY HP LEVEL TAME ELEMENT/FACTION HEAD FLIGHT/TRANSFORM/SUMMONING DECAY AFFINITY PROJ
    while(fin.good()){
      // read data into strings
      std::string junk,type,name,category,hp,level,tame,ele_fac,head,special,decay,affin,proj;
      std::getline(fin,type,',');
      std::getline(fin,name,',');
      std::getline(fin,category,',');
      std::getline(fin,hp,',');
      std::getline(fin,level,',');
      std::getline(fin,tame,',');
      std::getline(fin,ele_fac,',');
      std::getline(fin,head,',');
      std::getline(fin,special,',');
      std::getline(fin,decay,',');
      std::getline(fin,affin,',');
      std::getline(fin,proj,'\n');
      //string cat to Category cat
      Creature::Category p_cat;
      if(category=="UNDEAD"){
        p_cat=Creature::UNDEAD;
      }
      else if(category=="MYSTICAL"){
        p_cat=Creature::MYSTICAL;
      }
      else if(category=="ALIEN"){
        p_cat=Creature::ALIEN;
      }
      else{
        p_cat=Creature::UNKNOWN;
      }
      //string hp to int hp
      int p_hp;
      p_hp=std::stoi(hp);
      
      //string level to int level
      int p_level;
      p_level=std::stoi(level);

      bool p_tame;
      p_tame=std::stoi(tame);

      //string ele_fac to either type ELement or type FACTION
      Dragon::Element p_ele;
      Ghoul::Faction p_fac;
      if(ele_fac=="FIRE"){
        p_ele=Dragon::FIRE;
        p_fac=Ghoul::NONE;
      }
      else if(ele_fac=="WATER"){
        p_ele=Dragon::WATER;
        p_fac=Ghoul::NONE;
      }
      else if(ele_fac=="EARTH"){
        p_ele=Dragon::EARTH;
        p_fac=Ghoul::NONE;
      }
      else if(ele_fac=="AIR"){
        p_ele=Dragon::AIR;
        p_fac=Ghoul::NONE;
      }
      else if(ele_fac=="FLESHGORGER"){
        p_fac=Ghoul::FLESHGORGER;
        p_ele=Dragon::NONE;
      }
      else if(ele_fac=="SHADOWSTALKER"){
        p_fac=Ghoul::SHADOWSTALKER;
        p_ele=Dragon::NONE;
      }
      else if(ele_fac=="PLAGUEWEAVER"){
        p_fac=Ghoul::PLAGUEWEAVER;
        p_ele=Dragon::NONE;
      }
      else{
        p_ele=Dragon::NONE;
        p_fac=Ghoul::NONE;
      }

    

    //string head to type int
    int p_head;
    p_head=std::stoi(head);

    //string to boolean for special
    bool p_special;
    p_special=std::stoi(special);

    //string decay to int
    int p_decay;
    p_decay=std::stoi(decay);

    //afinity manip
    std::vector<Mindflayer::Variant> p_affins;
    Mindflayer::Variant p_var;
    std::stringstream ss(affin);
    int count=0;
    for(int i=0;i<affin.size();i++){
      //checks how many semicolon there. # of affinity = # of semicolons - 1
      if(affin[i]==';'){
      count++;
      }
    }
    if(count==0&&affin.size()!=4){
      std::string first;
      std::getline(ss,first);
      if(first=="PSIONIC"){
        p_var=Mindflayer::PSIONIC;
      }
      else if(first=="TELEPATHIC"){
        p_var=Mindflayer::TELEPATHIC;
      }
      else if(first=="ILLUSIONARY"){
        p_var=Mindflayer::ILLUSIONARY;
      }
      p_affins.push_back(p_var);
    }
    else if(count==1){
      std::string first,second;
      std::getline(ss,first,';');
      if(first=="PSIONIC"){
        p_var=Mindflayer::PSIONIC;
      }
      else if(first=="TELEPATHIC"){
        p_var=Mindflayer::TELEPATHIC;
      }
      else if(first=="ILLUSIONARY"){
        p_var=Mindflayer::ILLUSIONARY;
      }
      p_affins.push_back(p_var);
      
      std::getline(ss,second);
      if(second=="PSIONIC"){
        p_var=Mindflayer::PSIONIC;
      }
      else if(second=="TELEPATHIC"){
        p_var=Mindflayer::TELEPATHIC;
      }
      else if(second=="ILLUSIONARY"){
        p_var=Mindflayer::ILLUSIONARY;
      }
      p_affins.push_back(p_var);
    }
    else if(count==2){
      std::string first,second,third;
      std::getline(ss,first,';');
      if(first=="PSIONIC"){
        p_var=Mindflayer::PSIONIC;
      }
      else if(first=="TELEPATHIC"){
        p_var=Mindflayer::TELEPATHIC;
      }
      else if(first=="ILLUSIONARY"){
        p_var=Mindflayer::ILLUSIONARY;
      }
      p_affins.push_back(p_var);
      std::getline(ss,second,';');
      if(second=="PSIONIC"){
        p_var=Mindflayer::PSIONIC;
      }
      else if(second=="TELEPATHIC"){
        p_var=Mindflayer::TELEPATHIC;
      }
      else if(second=="ILLUSIONARY"){
        p_var=Mindflayer::ILLUSIONARY;
      }
      p_affins.push_back(p_var);

      std::getline(ss,third);
      if(third=="PSIONIC"){
        p_var=Mindflayer::PSIONIC;
      }
      else if(third=="TELEPATHIC"){
        p_var=Mindflayer::TELEPATHIC;
      }
      else if(third=="ILLUSIONARY"){
        p_var=Mindflayer::ILLUSIONARY;
      }
      p_affins.push_back(p_var);
    }
    
    std::vector<Mindflayer::Projectile> p_proj;
    Mindflayer::Variant p;
    std::stringstream ssp(proj);
    int ct=0;
    for(int i=0;i<proj.size();i++){
      if(proj[i]==';'){
      ct++;
      }
    }
    if(ct==0&&proj.size()!=4){
      std::string v1="",i1="";
      int pnum1=0;
      std::getline(ssp,v1,'-');
      ssp>>pnum1;
      if(v1=="PSIONIC"){
        p=Mindflayer::PSIONIC;
      }
      else if(v1=="TELEPATHIC"){
        p=Mindflayer::TELEPATHIC;
      }
      else if(v1=="ILLUSIONARY"){
        p=Mindflayer::ILLUSIONARY;
      }
      //pnum1=std::stoi(i1);
      p_proj.push_back({p,pnum1});
    }
     if(ct==1){
      std::string v1="",i1="",v2="",i2="";
      int pnum1=0,pnum2=0;
      std::getline(ssp,v1,'-');
      if(v1=="PSIONIC"){
        p=Mindflayer::PSIONIC;
      }
      else if(v1=="TELEPATHIC"){
        p=Mindflayer::TELEPATHIC;
      }
      else if(v1=="ILLUSIONARY"){
        p=Mindflayer::ILLUSIONARY;
      }
      std::getline(ssp,i1,';');
      pnum1=std::stoi(i1);
      p_proj.push_back({p,pnum1});

       std::getline(ssp,v2,'-');
      if(v2=="PSIONIC"){
        p=Mindflayer::PSIONIC;
      }
      else if(v2=="TELEPATHIC"){
        p=Mindflayer::TELEPATHIC;
      }
      else if(v2=="ILLUSIONARY"){
        p=Mindflayer::ILLUSIONARY;
      }
      ssp>>pnum2;
      //pnum2=std::stoi(i2);
      p_proj.push_back({p,pnum2});
    }
       if(ct==2){
      std::string v1,i1,v2,i2,v3,i3;
      int pnum1,pnum2,pnum3;
      std::getline(ssp,v1,'-');
      if(v1=="PSIONIC"){
        p=Mindflayer::PSIONIC;
      }
      else if(v1=="TELEPATHIC"){
        p=Mindflayer::TELEPATHIC;
      }
      else if(v1=="ILLUSIONARY"){
        p=Mindflayer::ILLUSIONARY;
      }
      ssp>>pnum1;
      //pnum1=std::stoi(i1);
      p_proj.push_back({p,pnum1});

       std::getline(ssp,v2,'-');
      if(v2=="PSIONIC"){
        p=Mindflayer::PSIONIC;
      }
      else if(v2=="TELEPATHIC"){
        p=Mindflayer::TELEPATHIC;
      }
      else if(v2=="ILLUSIONARY"){
        p=Mindflayer::ILLUSIONARY;
      }
      ssp>>pnum2;
      //pnum2=std::stoi(i2);
      p_proj.push_back({p,pnum2});

       std::getline(ssp,v3,'-');
      if(v2=="PSIONIC"){
        p=Mindflayer::PSIONIC;
      }
      else if(v2=="TELEPATHIC"){
        p=Mindflayer::TELEPATHIC;
      }
      else if(v2=="ILLUSIONARY"){
        p=Mindflayer::ILLUSIONARY;
      }
      ssp>>pnum3;
      //pnum3=std::stoi(i3);
      p_proj.push_back({p,pnum3});
    }
    if(type=="DRAGON"){
       Creature * dragon = new Dragon (name,p_cat,p_hp,p_level,p_tame,p_ele,p_head,p_special);
      enterCavern(dragon);
      //delete dragon;
      //dragon=nullptr;
    }
    else if(type=="GHOUL"){
       Creature * ghoul =new Ghoul(name,p_cat,p_hp,p_level,p_tame,p_decay,p_fac,p_special);
      enterCavern(ghoul);
      //delete ghoul;
      //ghoul = nullptr;
    }
    else if(type=="MINDFLAYER"){
      Creature * mindflayer = new Mindflayer (name,p_cat,p_hp,p_level,p_tame,p_proj,p_special,p_affins);
      enterCavern(mindflayer);
      //delete mindflayer;
      //mindflayer=nullptr;
    }
    
         /*while(fin.good()){
      std::getline(fin,type,',');
      if(type=="DRAGON"){
        std::getline(fin,name,',');
        std::getline(fin,category,',');
              if(category=="ALIEN"){
                category_category=Creature::ALIEN;
              }
              else if(category=="MYSTICAL"){
                category_category=Creature::MYSTICAL;
              }
              else if(category=="UNDEAD"){
                category_category=Creature::UNDEAD;
              }
              else{
                category_category=Creature::UNKNOWN;
              }
        std::getline(fin,hp,',');
              int_hp =std::stoi(hp);
        std::getline(fin,level,',');
              int_level = std::stoi(level);
        std::getline(fin,tame,',');
              bool_tame=std::stoi(tame);
        std::getline(fin,element,',');
              if(element=="FIRE"){
                element_element=Dragon::FIRE;
              }
              else if(element=="WATER"){
                element_element=Dragon::WATER;
              }
              else if(element=="EARTH"){
                element_element=Dragon::EARTH;
              }
              else if(element=="AIR"){
                element_element=Dragon::AIR;
              }
              else{
                element_element=Dragon::NONE;
              }
        std::getline(fin,heads,',');
              int_heads=std::stoi(heads);
        std::getline(fin,special,',');
              bool_flight=std::stoi(special);
        std::getline(fin,junk,'\n');
        //Dragon A(name,category_category,int_hp,int_level,bool_tame,element_element,int_heads,bool_special);
        Creature* cA = new Dragon(name,category_category,int_hp,int_level,bool_tame,element_element,int_heads,bool_flight);
        enterCavern(cA);
        delete cA;
        cA = nullptr;
      }
      if(type=="GHOUL"){
        std::getline(fin,name,',');
        std::getline(fin,category,',');
              if(category=="ALIEN"){
                category_category=Creature::ALIEN;
              }
              else if(category=="MYSTICAL"){
                category_category=Creature::MYSTICAL;
              }
              else if(category=="UNDEAD"){
                category_category=Creature::UNDEAD;
              }
              else{
                category_category=Creature::UNKNOWN;
              }
        std::getline(fin,hp,',');
              int_hp =std::stoi(hp);
        std::getline(fin,level,',');
              int_level = std::stoi(level);
        std::getline(fin,tame,',');
              bool_tame=std::stoi(tame);
        std::getline(fin,faction,',');
              if(faction=="FLESHGORGER"){
                faction_faction=Ghoul::FLESHGORGER;
              }
              else if(faction=="PLAGUEWEAVER"){
                faction_faction=Ghoul::PLAGUEWEAVER;
              }
              else if(faction=="SHADOWSTALKER"){
                faction_faction=Ghoul::SHADOWSTALKER;
              }
              else{
                faction_faction=Ghoul::NONE;
              }
        std::getline(fin,junk,',');
        std::getline(fin,special,',');
              bool_summon=std::stoi(special);
        std::getline(fin,decay,',');
              int_decay=std::stoi(decay);
        std::getline(fin,junk,'\n');
        Creature* cB = new Ghoul(name,category_category,int_hp,int_level,bool_tame,int_decay,faction_faction,bool_transform);
        enterCavern(cB);
        delete cB;
        cB = nullptr;
      }
      if(type=="MINDFLAYER"){
        std::getline(fin,name,',');
        std::getline(fin,category,',');
              if(category=="ALIEN"){
                category_category=Creature::ALIEN;
              }
              else if(category=="MYSTICAL"){
                category_category=Creature::MYSTICAL;
              }
              else if(category=="UNDEAD"){
                category_category=Creature::UNDEAD;
              }
              else{
                category_category=Creature::UNKNOWN;
              }
        std::getline(fin,hp,',');
              int_hp =std::stoi(hp);
        std::getline(fin,level,',');
              int_level = std::stoi(level);
        std::getline(fin,tame,',');
              bool_tame=std::stoi(tame);
        std::getline(fin,junk,',');
        std::getline(fin,junk,',');
        std::getline(fin,special,',');
             bool_summon=std::stoi(special);
        std::getline(fin,junk,',');
        std::getline(fin,affinity,',');
              int count=0;
              std::string one_var;
              std::vector<Mindflayer::Variant> one;
              for(int i=0;i<affinity.length();i++){
                if(affinity[i]==';'){
                  count++;
                }
              }
              if(count==0){
                std::stringstream ss(affinity);
                std::getline(ss,one_var);
                      if(one_var=="PSIONIC"){
                        variant=Mindflayer::PSIONIC;
                        one.push_back(variant);
                      }
                      else if(one_var=="ILLUSIONARY"){
                        variant=Mindflayer::ILLUSIONARY;
                        one.push_back(variant);
                      }
                      else if(one_var=="TELEPATHIC"){
                        variant=Mindflayer::TELEPATHIC;
                        one.push_back(variant);
                      }
                      else{

                      }

              }
              if(count==1){
                std::stringstream ss(affinity);
                std::string first,second;
                std::getline(ss,first,';');
                      if(first=="PSIONIC"){
                        variant=Mindflayer::PSIONIC;
                        one.push_back(variant);
                      }
                      else if(first=="ILLUSIONARY"){
                        variant=Mindflayer::ILLUSIONARY;
                        one.push_back(variant);
                      }
                      else if(first=="TELEPATHIC"){
                        variant=Mindflayer::TELEPATHIC;
                        one.push_back(variant);
                      }
                      else{
                        
                      }
                std::getline(ss,second);
                      if(second=="PSIONIC"){
                        variant=Mindflayer::PSIONIC;
                        one.push_back(variant);
                      }
                      else if(second=="ILLUSIONARY"){
                        variant=Mindflayer::ILLUSIONARY;
                        one.push_back(variant);
                      }
                      else if(second=="TELEPATHIC"){
                        variant=Mindflayer::TELEPATHIC;
                        one.push_back(variant);
                      }
                      else{
                        
                      }


              }
              if(count==2){
                std::stringstream ss(affinity);
                std::string first,second,third;
                std::getline(ss,first,';');
                      if(first=="PSIONIC"){
                        variant=Mindflayer::PSIONIC;
                        one.push_back(variant);
                      }
                      else if(first=="ILLUSIONARY"){
                        variant=Mindflayer::ILLUSIONARY;
                        one.push_back(variant);
                      }
                      else if(first=="TELEPATHIC"){
                        variant=Mindflayer::TELEPATHIC;
                        one.push_back(variant);
                      }
                      else{
                        
                      }
                std::getline(ss,second,';');
                      if(second=="PSIONIC"){
                        variant=Mindflayer::PSIONIC;
                        one.push_back(variant);
                      }
                      else if(second=="ILLUSIONARY"){
                        variant=Mindflayer::ILLUSIONARY;
                        one.push_back(variant);
                      }
                      else if(second=="TELEPATHIC"){
                        variant=Mindflayer::TELEPATHIC;
                        one.push_back(variant);
                      }
                      else{
                        
                      }
                std::getline(ss,third);
                      if(third=="PSIONIC"){
                        variant=Mindflayer::PSIONIC;
                        one.push_back(variant);
                      }
                      else if(third=="ILLUSIONARY"){
                        variant=Mindflayer::ILLUSIONARY;
                        one.push_back(variant);
                      }
                      else if(third=="TELEPATHIC"){
                        variant=Mindflayer::TELEPATHIC;
                        one.push_back(variant);
                      }
                      else{
                        
                      }


              }
        std::getline(fin,proj,'\n');
          int count2=0;
              std::string pvar,pnum;
              int int_pnum;
              std::vector<Mindflayer::Projectile> proje;
              for(int i=0;i<proj.length();i++){
                if(proj[i]==';'){
                  count2++;
                }
              }
                if(count2==0){
                std::stringstream ss(proj);
                std::getline(ss,pvar,'-');
                      if(pvar=="PSIONIC"){
                        pvariant=Mindflayer::PSIONIC;
                      }
                      else if(pvar=="ILLUSIONARY"){
                        pvariant=Mindflayer::ILLUSIONARY;
                      }
                      else if(pvar=="TELEPATHIC"){
                        pvariant=Mindflayer::TELEPATHIC;
                      }
                      else{

                      }
               std::getline(ss,pnum);
                      int_pnum=std::stoi(pnum);
                
                proje.push_back({pvariant,int_pnum});



              
      }       
                if(count2==1){
                std::string pvar,pnum,pvar2,pnum2;
                int int_pnum,int_pnum2;
                std::stringstream ss(proj);
                std::getline(ss,pvar,'-');
                      if(pvar=="PSIONIC"){
                        pvariant=Mindflayer::PSIONIC;
                      }
                      else if(pvar=="ILLUSIONARY"){
                        pvariant=Mindflayer::ILLUSIONARY;
                      }
                      else if(pvar=="TELEPATHIC"){
                        pvariant=Mindflayer::TELEPATHIC;
                      }
                      else{

                      }
                 std::getline(ss,pnum,';');
                      int_pnum=std::stoi(pnum);
                
                proje.push_back({pvariant,int_pnum});

                std::getline(ss,pvar2,'-');
                      if(pvar=="PSIONIC"){
                        pvariant=Mindflayer::PSIONIC;
                      }
                      else if(pvar2=="ILLUSIONARY"){
                        pvariant=Mindflayer::ILLUSIONARY;
                      }
                      else if(pvar2=="TELEPATHIC"){
                        pvariant=Mindflayer::TELEPATHIC;
                      }
                      else{

                      }
                 std::getline(ss,pnum2);
                      int_pnum2=std::stoi(pnum2);
                
                proje.push_back({pvariant,int_pnum2});

              }
              if(count2==2){
                if(count2==1){
                std::string pvar,pnum,pvar2,pnum2,pvar3,pnum3;
                int int_pnum,int_pnum2,int_pnum3;
                std::stringstream ss(proj);
                std::getline(ss,pvar,'-');
                      if(pvar=="PSIONIC"){
                        pvariant=Mindflayer::PSIONIC;
                      }
                      else if(pvar=="ILLUSIONARY"){
                        pvariant=Mindflayer::ILLUSIONARY;
                      }
                      else if(pvar=="TELEPATHIC"){
                        pvariant=Mindflayer::TELEPATHIC;
                      }
                      else{

                      }
                 std::getline(ss,pnum,';');
                      int_pnum=std::stoi(pnum);
                
                proje.push_back({pvariant,int_pnum});

                std::getline(ss,pvar2,'-');
                      if(pvar=="PSIONIC"){
                        pvariant=Mindflayer::PSIONIC;
                      }
                      else if(pvar2=="ILLUSIONARY"){
                        pvariant=Mindflayer::ILLUSIONARY;
                      }
                      else if(pvar2=="TELEPATHIC"){
                        pvariant=Mindflayer::TELEPATHIC;
                      }
                      else{

                      }
                 std::getline(ss,pnum2,';');
                      int_pnum2=std::stoi(pnum2);
                
                proje.push_back({pvariant,int_pnum2});

                      std::getline(ss,pvar3,'-');
                      if(pvar=="PSIONIC"){
                        pvariant=Mindflayer::PSIONIC;
                      }
                      else if(pvar3=="ILLUSIONARY"){
                        pvariant=Mindflayer::ILLUSIONARY;
                      }
                      else if(pvar3=="TELEPATHIC"){
                        pvariant=Mindflayer::TELEPATHIC;
                      }
                      else{

                      }
                       std::getline(ss,pnum3);
                      int_pnum2=std::stoi(pnum3);
                
                proje.push_back({pvariant,int_pnum3});

              }

    }
    
     
}*/
}
}
    


bool Cavern::enterCavern( Creature* new_creature) {
  if (getIndexOf(new_creature) == -1) {
    if (add(new_creature)){
      level_sum_ += new_creature->getLevel();
      if (new_creature->isTame()) {
        tame_count_++;
      }
      return true;
    }
  }
  return false;
}

bool Cavern::exitCavern(Creature* creature_to_remove) {
  if (remove(creature_to_remove)) {
    level_sum_ -= creature_to_remove->getLevel();
    if (creature_to_remove->isTame()) {
      tame_count_--;
    }
    return true;
  }
  return false;
}

int Cavern::getLevelSum() const {
  return level_sum_;
}

int Cavern::calculateAvgLevel() const {
  if (isEmpty()) {
    return 0;
  }
  return round(level_sum_ / getCurrentSize());
}

int Cavern::getTameCount() const {
  return tame_count_;
}

double Cavern::calculateTamePercentage() const {
  if (isEmpty()) {
    return 0;
  }
  double tame_percent = (tame_count_>0) ?  (double(tame_count_) / item_count_) * 100: 0.0;
  // return the tame percentage rounded up to two decimal places

  return std::ceil(tame_percent * 100) / 100;
 
}

int Cavern::tallyCategory(const std::string& category) const {
  if(category != "UNKNOWN" && category != "UNDEAD" && category != "MYSTICAL" && category != "ALIEN") {
    return 0;
  }
  int count = 0;
  for (int i = 0; i < getCurrentSize(); i++) {
    if (items_[i]->getCategory() == category) {
      count++;
    }
  }
  return count;
}

int Cavern::releaseCreaturesBelowLevel(int level) {
  int count = 0;
  if (level < 0) {
    return 0;
  }
  else if (level == 0) {
    count = getCurrentSize();
    clear();
    return count;
  }
  else {
    int size = getCurrentSize();
    for (int i = 0; i < size; i++) {
      if (items_[i]->getLevel() < level) {
        exitCavern(items_[i]);
        count++;
      }
    }
    return count;
  }
}

int Cavern::releaseCreaturesOfCategory(const std::string& category) {
  int count = 0;
  if (category == "ALL") {
    count = getCurrentSize();
    clear();
    return count;
  }
  else if (category != "UNKNOWN" && category != "UNDEAD" && category != "MYSTICAL" && category != "ALIEN") {
    return 0;
  }
  else {
    int size = getCurrentSize();
    for (int i = 0; i < size; i++) {
    if (items_[i]->getCategory() == category) {
      exitCavern(items_[i]);
      count++;
    }
  }
  return count;
  }
}
/**
    @post: For every creature in the cavern, displays each creature's information
*/
 void Cavern::displayCreatures() const{
    for(int i=0; i<getCurrentSize();i++){
      items_[i]->display();
    }

 }
 /**
    @param: a string reference to a category
    @post: For every creature in the cavern of the given category (only exact matches to the input string), displays each creature's information

*/
 void Cavern::displayCategory(const std::string& cat)const{
    for(int i=0; i<getCurrentSize();i++){
      if(items_[i]->getCategory()==cat){
        items_[i]->display();
      }
    }


 }
 
/**
    @post: Every creature in the cavern eats a MycoMorsel.
*/
 void Cavern::mycoMorselFeast(){
    for(int i=0; i<getCurrentSize();i++){
      if(items_[i]->eatMycoMorsel()==true){
        exitCavern(items_[i]);
      }

    }


 }

void Cavern::cavernReport() const {
  std::cout << "UNKNOWN: " << tallyCategory("UNKNOWN") << std::endl;
  std::cout << "UNDEAD: " << tallyCategory("UNDEAD") << std::endl;
  std::cout << "MYSTICAL: " << tallyCategory("MYSTICAL") << std::endl;
  std::cout << "ALIEN: " << tallyCategory("ALIEN") << std::endl;
  std::cout << std::endl;

  std::cout << "AVERAGE LEVEL: " << calculateAvgLevel() << std::endl;
  std::cout << "TAME: " << calculateTamePercentage() << "%" << std::endl;
}