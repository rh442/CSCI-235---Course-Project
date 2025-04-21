/*
Raymond Huang
Project-5
Pantry Implementation*/

#include "Pantry.hpp"

/*Default Constructor*/
Pantry::Pantry(){

}
/**
      Parameterized Constructor
      @param: A string representing a ingredient name
      @param: A string representing ingredient description
      @param: An int representing the ingredient's quantity
      @param: An int representing the ingredient's price
      @param: A vector holding Ingredient pointers representing the ingredient's recipe
      @post: Creates a new Ingredient object with the given parameters
  */
 /**
    @param: the name of an input file
    @pre: Formatting of the csv file is as follows:
        Name: A string
        Description: A string
        Quantity: A non negative integer
        Price: A non negative integer
        Recipe: A list of Ingredient titles of the form [NAME1] [NAME2];
        For example, to make this ingredient, you need (Ingredient 1 AND Ingredient 2)
        The value may be NONE.
    Notes:
        - The first line of the input file is a header and should be ignored.
        - The recipe are separated by a semicolon and may be NONE.
        - The recipe may be in any order.
        - If any of the recipe are not in the list, they should be created as new ingredients with the following information:
            - Title: The name of the ingredient
            - Description: "UNKNOWN"
            - Quantity: 0
            - Price: 0
            - Recipe: An empty vector
        - However, if you eventually encounter a ingredient that matches one of the "UNKNOWN" ingredients while parsing the file, you should update all the ingredient details.
        
        For example, given a row in the file:
        Inferno_Espresso,An energizing elixir brewed with mystical flames providing resistance to caffeine crashes for a limited time.,1,50,Fiery_Bean Ember_Spice

        The order of the ingredients in the list:
        Fiery_Bean, Ember_Spice, Inferno_Espresso
        Hint: update as needed using addIngredient()
        
    @post: Each line of the input file corresponds to a ingredient to be added to the list. No duplicates are allowed.
    Hint: use std::ifstream and getline()
*/
Pantry::Pantry(const std::string &csv){
    std::ifstream ingredList(csv);
    if(ingredList.fail()){
        std::cerr<<"file cannot be opened for reading."<<std::endl;
        exit(1);
    }
    std::string junk;
    //get ride of first line
    std::getline(ingredList,junk);
    std::string name,descript,quantity,price,rcp;

    while(ingredList.good()){
        std::getline(ingredList,name,',');
        std::getline(ingredList,descript,',');
        std::getline(ingredList,quantity,',');
        std::getline(ingredList,price,',');
        std::getline(ingredList,rcp);
        

        int qty = stoi(quantity);
        int prc = stoi(price);
        std::stringstream ss(rcp);
        std::vector<Ingredient*> rp;

        if(rcp=="NONE\r"||rcp=="NONE\n"){
            rp={};
        }
        else{
            //counter for spaces
        int counter=0;
        for(int i =0;i<rcp.size();i++){
            if(rcp[i]==' '){
                counter++;
            }
        }
        std::string name1;
        //get all Ingredients except last
        for(int i =0;i<counter;i++){
            std::getline(ss,name1,' ');
            Ingredient *A;
            if(contains(name1)){
                A = getPointerTo(getPosOf(name1))->getItem();
            }
            else{
                A = new Ingredient(name1,"UNKNOWN",0,0,{});
            }
            rp.push_back(A);
        }
        //get last ingredient;
        std::getline(ss,name1,';');
            Ingredient*B;
         if(contains(name1)){
                B = getPointerTo(getPosOf(name1))->getItem();
            }
            else{
                B = new Ingredient(name1,"UNKNOWN",0,0,{});
            }
            rp.push_back(B);
        }
        
            addIngredient(name,descript,qty,prc,rp);
       
            if(getPointerTo(getPosOf(name))->getItem()->description_=="UNKNOWN"){
                Ingredient* p = new Ingredient(name,descript,qty,prc,rp);
                getPointerTo(getPosOf(name))->setItem(p);
            
        }
    
    }
}
 /**
        Destructor
        @post: Explicitly deletes every dynamically allocated Ingredient object
*/

Pantry::~Pantry(){
    clear();
}
/**
    @param: A const string reference to a ingredient name
    @return: The integer position of the given ingredient if it is in the Pantry, -1 if not found. REMEMBER, indexing starts at 0.
*/

int Pantry::getPosOf(const std::string &Iname){
    Node<Ingredient*> *it = getHeadNode();
    int length = getLength();
    for(int i=0;i<length;i++){
        if(it->getItem()->name_==Iname){
            return i;
        }
        else{
        it=it->getNext();
        }
        }
       return -1;
    }
    

/**
    @param: A const string reference to a ingredient name
    @return: True if the ingredient information is already in the Pantry
*/
bool Pantry::contains(const std::string &Inam){
    if(getPosOf(Inam)>=0){
        return true;
    }
    else{
        return false;
    }
}
/**
    @param:  A pointer to an Ingredient object
    @post:  Inserts the given ingredient pointer into the Pantry, unless an ingredient of the same name is already in the pantry. 
            Each of its Ingredients in its recipe are also added to the Pantry IF not already in the list.
    @return: True if the ingredient was added successfully, false otherwise.
*/
bool Pantry::addIngredient(Ingredient* ingred){
    if(ingred==nullptr){
        //std::cout<<"INVALID POINTER"<<"\n";
        return false;
    }
    if(!contains(ingred->name_)){
        insert(getLength(),ingred);
        for(int i=0;i<ingred->recipe_.size();i++){
            addIngredient(ingred->recipe_[i]);
        }
        return true;
    }
    return false;
}
/**
    @param: A const string reference representing a ingredient name
    @param: A const string reference representing ingredient description
    @param: A const int reference representing the ingredient's quantity
    @param: A const int reference representing the ingredient's price
    @param: A const reference to a vector holding Ingredient pointers representing the ingredient's recipe
    @post:   Creates a new Ingredient object and inserts a pointer to it into the Pantry. 
            Each of its Ingredients in its recipe are also added to the Pantry IF not already in the list.
    @return: True if the ingredient was added successfully
*/
bool Pantry::addIngredient(const std::string &nam, const std::string &descript,const int &qty, const int &prce, const std::vector<Ingredient*> &rcp){
   Ingredient* iptr = new Ingredient(nam,descript,qty,prce,rcp);
   if(addIngredient(iptr)==true){
    return true;
   }
   else{
    return false;
   }
}
/**
    @param:  A Ingredient pointer
    @return: A boolean indicating if all the given ingredient can be created (all of the ingredients in its recipe can be created, or if you have enough of each ingredient in its recipe to create it)
*/
bool Pantry::canCreate( Ingredient* ingred){
    //checks if nullptr
    if(ingred==nullptr){
        //std::cout<<"INVALID POINTER"<<"\n";
        return false;
    }
  //check if ingredient has recipe
  if(ingred->recipe_.empty()){
    
    return false;
  }
  
    if(!contains(ingred->name_)){
        
        return false;
    }
    if(contains(ingred->name_)){
        for(int i=0;i<ingred->recipe_.size();i++){
            if(!contains(ingred->recipe_[i]->name_)){
                
                return false;
            }
            else if(ingred->recipe_[i]->quantity_<1&&!canCreate(ingred->recipe_[i])){
                
                return false;
            }
        }
}
return true;
}
/**
    @param: A Ingredient pointer
    @post: Prints the ingredient name, quantity, and description.
    The output should be of the form:
    [Ingredient Name]: [Quantity]\n
    [Ingredient Description]\n
    Price: [Price]\n
    Recipe:\n
    [Ingredient0] [Ingredient1]\n


    If the ingredient has no recipe, print "Recipe:\nNONE\n\n" after the price.
*/
void Pantry::printIngredient( Ingredient* ingred) const{
    if(ingred==nullptr){
        //std::cout<<"INVALID POINTER"<<"\n";
        return;
    }
    std::cout<<ingred->name_<<": "<<ingred->quantity_<<std::endl;
    std::cout<<ingred->description_<<std::endl;
    std::cout<<"Price: "<<ingred->price_<<std::endl;
        if(ingred->recipe_.empty()){
        std::cout<<"Recipe:\nNONE\n\n";
    }
    else{
        std::cout<<"Recipe:"<<std::endl;
        for(int i=0;i<ingred->recipe_.size();i++){
            std::cout<<ingred->recipe_[i]->name_<<" ";
        }
        std::cout<<"\n\n";
    }
}
// helper function for inquiryQuery
void Pantry::IQ(const std::string &nam){
    //Print ingredient with quantity of quantity > than 0
    if(getPointerTo(getPosOf(nam))->getItem()->quantity_==0){
         for(int i=0;i<getPointerTo(getPosOf(nam))->getItem()->recipe_.size();i++){
                if(getPointerTo(getPosOf(nam))->getItem()->recipe_[i]->quantity_>=1){
                std::cout<<getPointerTo(getPosOf(nam))->getItem()->recipe_[i]->name_<<"("<<getPointerTo(getPosOf(nam))->getItem()->recipe_[i]->quantity_<<")\n";
            }
            //if not print ingrendient with (C) and continues recursion
            else{
                if(canCreate(getPointerTo(getPosOf(nam))->getItem()->recipe_[i])){
                    
                    std::cout<<getPointerTo(getPosOf(nam))->getItem()->recipe_[i]->name_<<"(C) <- ";
                    IQ(getPointerTo(getPosOf(nam))->getItem()->recipe_[i]->name_); 
                }

    }
         }
         
    }


}
/**
    @param: A const string reference to a ingredient name
    @post:  Prints a list of ingredients that must be created before the given ingredient can be created (missing ingredients for its recipe, where you have 0 of the needed ingredient).
            If the ingredient is already in the pantry, print "In the pantry([quantity])\n"
            If there are no instances of the ingredient, if it cannot be crafted because of insufficient ingredients, print "[Ingredient Name](0)\nMISSING INGREDIENTS"
            If it can be crafted, recursively print the ingredients that need to be used (if there are instances of them) or created (if there are no instances of them) in the order that the ingredients appear in the recipe, joined by "<-".
            If the ingredient has no recipe, print "UNCRAFTABLE\n" at the end of the function.

            Below are some of the expected forms. "Scenario: [scenario] is not part of the output. It is just to help you understand the expected output.":

            Scenario: The Ingredient does not exist in the list
            Query: [Ingredient Name]
            No such ingredient

            Scenario: The Ingredient exists in the list, and there are >0 instances of it
            Query: [Ingredient Name]
            In the pantry ([Quantity])

            Scenario: The Ingredient exists in the list, and there are 0 instances of it, and it is craftable by using an ingredient that is already in the pantry
            Query: [Ingredient Name0]
            [Ingredient Name0](C)
            [Ingredient Name1](1)

            Scenario: The Ingredient exists in the list, and there are 0 instances of it, and it is craftable by using an ingredient that has to be crafted
            Query: [Ingredient Name0]
            [Ingredient Name0](C)
            [Ingredient Name1](C) <- [Ingredient Name2](3)
            
            Scenario: The Ingredient exists in the list, and there are 0 instances of it, and there are multiple ingredients that have to be crafted (each row represents a different ingredient inå the original recipe)
            Query: [Ingredient Name0]
            [Ingredient Name0](C)
            [Ingredient Name1](C) <- [Ingredient Name2](3)
            [Ingredient Name3](C) <- [Ingredient Name4](C) <- [Ingredient Name5] (3)

            Scenario: The Ingredient exists in the list, and there are 0 instances of it, and it is not craftable (it has no recipe)
            Query: [Ingredient Name0]
            UNCRAFTABLE

            Scenario: The Ingredient exists in the list, and there are 0 instances of it, and it has a recipe, but you do not have enough of the ingredients to craft it
            Query: [Ingredient Name0]
            [Ingredient Name0](0)
            MISSING INGREDIENTS
    
    HINT: Use canCreate() to determine if the ingredient can be created.
*/
void Pantry::ingredientQuery(const std::string &nam){
    std::cout<<"Query: "<<nam<<"\n";
    
    //Ingredient not in Pantry

    if(getPosOf(nam)==-1){
        
        std::cout<<"No such ingredient"<<"\n";

    }
    //Ingredient is in Pantry
    if(getPosOf(nam)>=0){
        //There is >1 of Ingredient
        if(getPointerTo(getPosOf(nam))->getItem()->quantity_>0){
            
            std::cout<<"In the pantry ("<<getPointerTo(getPosOf(nam))->getItem()->quantity_<<")"<<"\n";
            if(getPointerTo(getPosOf(nam))->getItem()->recipe_.empty()){
                std::cout<<"UNCRAFTABLE"<<"\n";
            }

        }
        //There is 0 instances of Ingredient
        if(getPointerTo(getPosOf(nam))->getItem()->quantity_==0){
            //check for recipe
            if(getPointerTo(getPosOf(nam))->getItem()->recipe_.empty()){
                std::cout<<"UNCRAFTABLE"<<"\n";
            }
            //check if enough ingredients in pantry to create ingredient
            else if(canCreate(getPointerTo(getPosOf(nam))->getItem())){
               std::cout<<nam<<"(C)"<<"\n";
            //loop to print each ingredient needed to be craftfed in recipe
            for(int i=0;i<getPointerTo(getPosOf(nam))->getItem()->recipe_.size();i++){
                //ingredients with >=1 quantity gets printed with quantity
                if(getPointerTo(getPosOf(nam))->getItem()->recipe_[i]->quantity_>=1){
                std::cout<<getPointerTo(getPosOf(nam))->getItem()->recipe_[i]->name_<<"("<<getPointerTo(getPosOf(nam))->getItem()->recipe_[i]->quantity_<<")\n";
            }
            else{
                //ingredients with <1 gets printed with (C) and tossed into reccursion
                    std::cout<<getPointerTo(getPosOf(nam))->getItem()->recipe_[i]->name_<<"(C) <- ";
                    IQ(getPointerTo(getPosOf(nam))->getItem()->recipe_[i]->name_); 
                    if(i==getPointerTo(getPosOf(nam))->getItem()->recipe_.size()){
                    std::cout<<"\n";  
            }
        
            }
            
            }
           
           
        
          
    }
    else{
                    std::cout<<nam<<"(0)\nMISSING INGREDIENTS\n"; 
                    return;
                }
        }
    
}
}

/**
    @return: An integer sum of the price of all the ingredients currently in the list.
    Note: This should only include price values from ingredients that you have 1 or more of. Do not consider ingredients that you have 0 of, even if you have the ingredients to make them.
*/
int Pantry::calculatePantryValue()const{
    Node<Ingredient*>* it = head_ptr_;
    int total=0;
  int price,quantity;
  while(it!=nullptr){
    price=it->getItem()->price_;
    quantity=it->getItem()->quantity_;
    total+=price*quantity;
    it=it->getNext();
  }
  return total;
}
/**
    @param: A const string reference to a filter with a default value of "NONE".
    @post: With default filter "NONE": Print out every ingredient in the list.
        With filter "CONTAINS":   Only print out the ingredients with >0 instances in the list.
        With filter "MISSING": Only print out the ingredients with 0 instances in the list.
        With filter "CRAFTABLE":  Only print out the ingredients where you have all the ingredients to craft them.
        If an invalid filter is passed, print "INVALID FILTER\n"
        Printing ingredients should be of the form:

        [Ingredient name]: [Quantity]
        [Ingredient description]\n
        Price: [price]\n
        Recipe:\n
        [Ingredient0] [Ingredient1]\n\n

        If the ingredient has no recipe, print "Recipe:\nNONE\n\n" after the price.
*/
void Pantry::pantryList(const std::string &name){ 
    Node<Ingredient*>* it = head_ptr_;
        int size= getLength();
    if(name=="NONE"){
        
        for(int i=0;i<size;i++){
            printIngredient(it->getItem());
            
            it=it->getNext();
        }
    }
    else if(name=="CONTAINS"){
        while(it!=nullptr){
            if(it->getItem()->quantity_>0){
                printIngredient(it->getItem());
                
                it=it->getNext();
            }
            else{
                it=it->getNext();
            }
        }
    }
    else if(name=="MISSING"){
         while(it!=nullptr){
            if(it->getItem()->quantity_==0){
                printIngredient(it->getItem());
                it=it->getNext();
            }
            else{
                it=it->getNext();
            }
        }

    }
    else if(name=="CRAFTABLE"){
         while(it!=nullptr){
        
          if(canCreate(it->getItem())){
            printIngredient(it->getItem());
            
            it=it->getNext();
          }
          else{
            it=it->getNext();
          }
           
        }

    }
    else{
        std::cout<<"INVALID FILTER\n";
    }
    }

