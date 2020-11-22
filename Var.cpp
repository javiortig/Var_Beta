#include "Var.h"

//inside methods:
void Var::_clearVar(){
    switch (this->variable._type)
    {
    case this->StringType:
        //delete(this->variable.value.s);
        break;
    case this->ListType:
        //delete(this->variable.value.l);
        break;
    case this->DictType:
        //delete(this->variable.value.d);
        break;
    
    default:    //no need to clear
        break;
    }

    //clear
    this->variable._type = this->NullType;
    this->variable.value.n = nullptr;

}

//Methods:
void Var::print(bool endLine){
    switch (this->variable._type)
    {
    case this->NullType:
        std::cout << "Null";
        break;
    case this->CharType:
        std::cout << '\'' << this->variable.value.c << '\'';
        break;
    case this->IntType:
        std::cout << this->variable.value.i;
        break;
    case this->FloatType:
        std::cout << this->variable.value.f;
        break;
    case this->BooleanType:
        std::cout << this->variable.value.b;
        break;
    case this->StringType: 
        std::cout <<  '\"' <<*this->variable.value.s << '\"';
        break;
    case this->ListType:
        std::cout << '{';
        for (std::vector<Var>::iterator x = this->variable.value.l->begin(); x != this->variable.value.l->end(); ++x){
            std::cout << ' ';
            x->print(false);

            
        }
        std::cout << '}';
        break;
    case this->DictType:
        //TODO
        break;
    default:
        //ERROR. shouldnt reach here
        break;
    }

    if(endLine) printf("\n");
}

void Var::printType(bool endLine){
    switch (this->variable._type)
    {
    case this->NullType:
        printf("Null");
        break;
    case this->CharType:
        printf("Char");
        break;
    case this->IntType:
        printf("Int");
        break;
    case this->FloatType:
        printf("Float");
        break;
    case this->BooleanType:
        printf("Bool");
        break;
    case this->StringType:  //TODO: ver si funciona este caso
        printf("String");
        break;
    case this->ListType:
        printf("List");
        break;
    case this->DictType:
        printf("Dict");
        break;
    default:
        //ERROR. shouldnt reach here
        break;
    }

    if(endLine) printf("\n");
}


//Constructors and destructors:




