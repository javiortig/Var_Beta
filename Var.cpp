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
    case this->BoolType:
        std::cout << ((this->variable.value.b)? "True":"False");
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
            std::cout << ' ' <<'}';
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
    case this->BoolType:
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

/*Inner operation functions:*/
//addition
Var Var::_addition(Var &a, Var &b){
    Var result;
    switch (a.variable._type)
    {
    case this->NullType:
        switch (b.variable._type)
        {
        case this->NullType:
            //do nothing
            break;
        case this->CharType:
        case this->IntType:
        case this->FloatType:
        case this->BoolType:
            result = b;
            break;
        case this->StringType: 
            __string_addition(&result, b, a);
            break;
        case this->ListType:
            __list_addition(&result, b, a);
            break;
        case this->DictType:
            
            break;
        default:
            
            break;
        }
        break;

    case this->CharType:
        switch (b.variable._type)
        {
        case this->NullType:
            result = a;
            break;
        case this->CharType:
        case this->IntType:
        case this->FloatType:
            __number_basic_operation(&result, a, b, '+');
            break;
        case this->BoolType:
            // Error
            break;
        case this->StringType: 
            __string_addition(&result, b, a);
            break;
        case this->ListType:
            __list_addition(&result, b, a);
            break;
        case this->DictType:
            
            break;
        default:
            
            break;
        }
        break;

    case this->IntType:
        switch (b.variable._type){
        case this->NullType:
            result = a;
            break;
        case this->CharType:
        case this->IntType:
        case this->FloatType:
            __number_basic_operation(&result, a, b, '+');
            break;
        case this->BoolType:
            //error
            break;
        case this->StringType: 
            __string_addition(&result, b, a);
            break;
        case this->ListType:
            __list_addition(&result, b, a);
            break;
        case this->DictType:
            
            break;
        default:
            
            break;
        }
        break;

    case this->FloatType:
        switch (b.variable._type){
        case this->NullType:
            result = a;
            break;
        case this->CharType:
        case this->IntType:
        case this->FloatType:
            __number_basic_operation(&result, a, b, '+');
            break;
        case this->BoolType:
            //error
            break;
        case this->StringType: 
            __string_addition(&result, b, a);
            break;
        case this->ListType:
            __list_addition(&result, b, a);
            break;
        case this->DictType:
            
            break;
        default:
            
            break;
        }

        break;

    case this->BoolType:
        switch (this->variable._type)
        {
        case this->NullType:
            result = a;
            break;
        case this->CharType:
            //error
            break;
        case this->IntType:
            //error
            break;
        case this->FloatType:
            //error
            break;
        case this->BoolType:
            result.variable._type = BoolType;
            result.variable.value.b = a.variable.value.b + b.variable.value.b;
            break;
        case this->StringType: 
            //error
            break;
        case this->ListType:
            __list_addition(&result, b, a);
            break;
        case this->DictType:
            
            break;
        default:
            
            break;
        }
        break;

    case this->StringType: 
        switch (this->variable._type)
        {
        case this->NullType:
            result = a;
            break;
        case this->CharType:
        case this->IntType:
        case this->FloatType:
            __string_addition(&result, a, b);
            break;
        case this->BoolType:
            //error
            break;
        case this->StringType: 
            __string_addition(&result, a, b);
            break;
        case this->ListType:
            __list_addition(&result, b, a);
            break;
        case this->DictType:
            
            break;
        default:
            
            break;
        }
        break;

    case this->ListType:
        switch (this->variable._type)
        {
        case this->NullType:
        case this->CharType:
        case this->IntType:
        case this->FloatType:
        case this->BoolType:
        case this->StringType: 
        case this->ListType:
            __list_addition(&result, a, b);
            break;
        case this->DictType:
            
            break;
        default:
            
            break;
        }
        break;

    case this->DictType:    
        //TODO:
        break;
    default:
        
        break;
    }

    return result;
}
void Var::__number_basic_operation(Var *result, Var &a, Var &b, char _operation){
    switch (_operation)
    {
    case '+':     
        switch (a.variable._type)
        {
        case this->CharType:
            switch (b.variable._type){
            case this->CharType:
                result->variable._type = CharType;
                result->variable.value.c = a.variable.value.c + b.variable.value.c;
                break;  

            case this->IntType:
                result->variable._type = IntType;
                result->variable.value.i = (long)a.variable.value.c + b.variable.value.i;
                break;

            case this->FloatType:
                result->variable._type = FloatType;
                result->variable.value.f = (double)a.variable.value.c + b.variable.value.f;
                break;
            default:
                //error
                break;
            }
            break;

        case this->IntType:
            switch (b.variable._type){
            case this->CharType:
                result->variable._type = IntType;
                result->variable.value.i = a.variable.value.i + (long)b.variable.value.c;
                break;

            case this->IntType:
                result->variable._type = IntType;
                result->variable.value.i = a.variable.value.i + b.variable.value.i;
                break;

            case this->FloatType:
                result->variable._type = FloatType;
                result->variable.value.f = (double)a.variable.value.i + b.variable.value.f;
                break;

            default:
                //error
                break;
            }
            break;

        case this->FloatType:
            switch (b.variable._type){
            case this->CharType:
                result->variable._type = FloatType;
                result->variable.value.f = a.variable.value.f + (double)b.variable.value.c;
                break;

            case this->IntType:
                result->variable._type = FloatType;
                result->variable.value.f = a.variable.value.f + (double)b.variable.value.i;
                break;
            case this->FloatType:
                result->variable._type = FloatType;
                result->variable.value.f = a.variable.value.f + b.variable.value.c;
                break;
            default:
                //error
                break;
            }
            break;
            
        default:
            //error
            break;
        }
        break;
        
    case '-':
    
        break;
    case '*':
    
        break;
    case '/':
    
        break;
    default:
    //error
        break;
    }

    
}   //Var string must be string
void Var::__string_addition(Var *result, Var &str, Var &any){
    result->variable.value.s = new std::string(*str.variable.value.s);
    result->variable._type = StringType;
    switch (any.variable._type)
    {
    case this->NullType:
        //Do nothing
        break;
    case this->CharType:
        result->variable.value.s->push_back(any.variable.value.c);
        break;
    case this->IntType:
        result->variable.value.s->append(std::to_string(any.variable.value.i));
        break;
    case this->StringType: 
        result->variable.value.s->append(*any.variable.value.s);
        break;
    default:
        //error
        break;
    }
}   //l must be a list
void Var::__list_addition(Var *result, Var &_l, Var &any){
    result->variable.value.l = new std::vector<Var>(*_l.variable.value.l);
    result->variable._type = ListType;

    result->variable.value.l->push_back(any);
}
//end addition

//Constructors and destructors:

/*

switch (this->variable._type)
    {
    case this->NullType:

        break;
    case this->CharType:
        
        break;
    case this->IntType:
        
        break;
    case this->FloatType:
        
        break;
    case this->BoolType:
        
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

*/
