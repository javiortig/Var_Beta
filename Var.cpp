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

void Var::__tab(int k){
    for(int i = 0; i < k; i++){
        cout << "    ";
    }
}

//Methods:
void Var::print(bool pretty, bool endLine){
    static int recursive_depth = -1;
    recursive_depth++;

    if(pretty && (this->variable._type != ListType)) 
        __tab(recursive_depth);

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
        if (pretty){
            //Prints in cascade (JSON-like)
            __tab(recursive_depth);
            std::cout << '{' << endl;
            for (size_t i=0; i < this->variable.value.l->size(); i++){
                this->variable.value.l->at(i).print(true, true);
            }
            __tab(recursive_depth);
            std::cout << '}';
        }
        else{
            //Prints horizontal
            std::cout << '{';
            for (size_t i=0; i < this->variable.value.l->size(); i++){
                std::cout << ' ';
                this->variable.value.l->at(i).print(false, false);
                if (i < this->variable.value.l->size() - 1){
                    cout << ',';
                }
            }
            std::cout << '}';
        }
        
        break;
    case this->DictType:
        //TODO
        break;
    default:
        //ERROR. shouldnt reach here
        break;
    }

    if(endLine) cout << endl;

    recursive_depth--;
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

//Inner operation functions:
Var Var::_addition(Var &a, Var &b){
    Var result;
    switch (this->variable._type)
    {
    case this->NullType:
        //error
        break;
    case this->CharType:
        
        break;
    case this->IntType:
        
        break;
    case this->FloatType:
        
        break;
    case this->BooleanType:
        
        break;
    case this->StringType: 
        
        break;
    case this->ListType:
        
        break;
    case this->DictType:
        
        break;
    default:
        
        break;
    }

}

//Constructors and destructors:



// switch (this->variable._type)
//     {
//     case this->NullType:

//         break;
//     case this->CharType:
        
//         break;
//     case this->IntType:
        
//         break;
//     case this->FloatType:
        
//         break;
//     case this->BooleanType:
        
//         break;
//     case this->StringType: 
        
//         break;
//     case this->ListType:
        
//         break;
//     case this->DictType:
        
//         break;
//     default:
        
//         break;
//     }