#ifndef _VAR_H
#define _VAR_H
#include <iostream>
#include <cstring>
#include <math.h>
#include <typeinfo>
#include <vector>
#include <map>

// using namespace std;
/*
    TODO: arreglar nested vectors

    -TODO: throw errors and terminate program when invalid sumation, etc
*/

#define N_VAR_TYPES 8

using namespace std;

class Var{
private:
    struct Value{
        int _type;
        size_t _len;

        union _Types{   // the hole union is only sizeof() the biggest type inside
            void* n;
            char c;
            long i;
            double f;
            bool b;
            std::string* s;
            std::vector<Var>* l;
            std::map<Var, Var>* d;    

        }value;
    }variable;
    //inside methods
    void _clearVar();
    void __tab(int k = 0); //couts a tab as many times as k

public:
    //type constants
    // longs are used as Int and double as Float for code simplification
    static constexpr int NullType = 0;
    static constexpr int CharType = 1;
    static constexpr int IntType = 2;
    static constexpr int FloatType = 3;
    static constexpr int BooleanType = 4;
    static constexpr int StringType = 5;
    static constexpr int ListType = 6;
    static constexpr int DictType = 7;
    static constexpr int __VarType = 8;

    //methods:
    void print(bool pretty = false, bool endLine = true);
    void printType(bool endLine = true);
    

    //constructors and destructors:
    Var(){
        this->variable._type = NullType;
        this->variable.value.n = nullptr;
        this->variable._len = -1;
    };
    template<class Any> 
    Var(Any v){
        _convertToVar(this, v);
    };

    ~Var(){ 
        this->_clearVar();
    };

private:
//Inside methods:
    template<class Any> 
    bool __isPointerOrArray(Any v){
        return (std::is_pointer<Any>::value || std::is_array<Any>::value);
    };
        
    template<class Any> 
    int __getVarTypeFromAnyType(Any v){
        size_t typeHash = typeid(v).hash_code();
        //Null
        if (typeHash == typeid(nullptr).hash_code()){ 
            return this->NullType;
        }
        //Char
        else if(typeHash == typeid(char).hash_code() || 
                typeHash == typeid(unsigned char).hash_code() ||
                typeHash == typeid(signed char).hash_code()){
            
            return this->CharType;
        }
        //Int
        else if(typeHash == typeid(unsigned short int).hash_code() ||
                typeHash == typeid(signed short int).hash_code() ||
                typeHash == typeid(unsigned int).hash_code() ||
                typeHash == typeid(signed int).hash_code() ||
                typeHash == typeid(unsigned long int).hash_code() ||
                typeHash == typeid(signed long int).hash_code()){
            return this->IntType;
        }
        //Float
        else if(typeHash == typeid(float).hash_code() ||
                typeHash == typeid(double).hash_code() ||
                typeHash == typeid(long double).hash_code()){
            return this->FloatType;
        }
        //Bool
        else if(typeHash == typeid(bool).hash_code()){
            return this->BooleanType;
        }
        //String
        else if(typeHash == typeid(char *).hash_code() ||
                typeHash == typeid(const char *).hash_code()){
            return this->StringType;
        }
        //any pointer/array is considered a list, or a vector
        else if(__isPointerOrArray(v) || 
                typeHash == typeid(std::vector<Var>).hash_code()){
            return this->ListType;
        }
        //already a Var
        else if(typeHash == typeid(Var).hash_code()){
            return this->__VarType;
        }
        else{
            //ERROR
        }

        return -1;
    };

    //C type to Var conversion functions:
    //For Null
    void __convertCTypeToVar(Var* var, std::nullptr_t v){
        var->variable._len = -1;
        var->variable.value.n = nullptr;
    };
    //For int, float and char
    void __convertCTypeToVar(Var* var ,const double& v){
        var->variable._len = -1;

        switch (var->variable._type)
        {
        case CharType:
            var->variable.value.c = (char)v;
            break;
        case IntType:
            var->variable.value.i = (long)v;
            break;
        case FloatType:
            var->variable.value.f = v;
            break;
        case BooleanType:
            var->variable.value.b = (bool)v;
            break;
        default:
            //Error
            break;
        }
    };    
    //For String
    void __convertCTypeToVar(Var* var, const char* v){
        var->variable._len = strlen(v);
        var->variable.value.s = new std::string(v);
    };
    //For Lists 
    /*
        TODO: ACEPTAR punteros a punteros, arrays con arrays
        usando recursividad?
    */
    void __convertCTypeToVar(Var* var, const void* v){
        
    };
    void __convertCTypeToVar(Var* var, vector<Var> &v){
        var->variable.value.l = new vector<Var>(v);
    };

    //general function to be called for C main types
    template<class Any>
    void _convertToVar(Var* var, Any v){
        var->variable._type = __getVarTypeFromAnyType(v);
        __convertCTypeToVar(var, v);
    };

    void _convertToVar(Var* var, Var &v){
        var->variable._type = v.variable._type;
        var->variable._len = v.variable._len;
        switch (this->variable._type)
        {
        case this->NullType:
            this->variable.value.n = nullptr;
            break;
        case this->CharType:
            this->variable.value.c = v.variable.value.c;
            break;
        case this->IntType:
            this->variable.value.i = v.variable.value.i;
            break;
        case this->FloatType:
            this->variable.value.f = v.variable.value.f;
            break;
        case this->BooleanType:
            this->variable.value.b = v.variable.value.b;
            break;
        case this->StringType: 
            this->variable.value.s = new std::string(*v.variable.value.s);
            break;
        case this->ListType:
            this->variable.value.l = new std::vector<Var>(*v.variable.value.l);
            break;
        case this->DictType:
            //TODO
            break;
        default:
            //ERROR. shouldnt reach here
            break;
        }
    };
    
//inner operation functions:
    Var _addition(Var &a, Var &b);
    void __number_addition(Var *result, Var &a, Var &b);
    void __char_addition(Var *result, Var &a, Var &b);
    void __char_addition(Var *result, Var &a, Var &b);
    //TODO: MAS

public:
    //Template operators:
    // assignment
    void operator=(Var &v){
        this->_clearVar();
        this->_convertToVar(this, v);
    };

    template<class Any> 
    void operator=(Any v){
        this->_clearVar();
        this->_convertToVar(this, v);
    };

    // addition
    void operator+(Var &v){
        
    };

    template<class Any> 
    void operator+(Any v){
        this->_convertToVar(this, v);
    };

public:
    //global functs that need friend
    template<class T, class... Args>
    friend Var list(T t, Args... args);

private://inner functions of global functions such as list()
    template<class T, class... Args>
    void _list(Var *p, T t, Args... args){
        Var *v = new Var(t);
        (p->variable.value.l)->push_back(*v);

        _list(p ,args...);
    };

    template<class T>
    void _list(Var *p, T t){
        Var *v = new Var(t);
        (p->variable.value.l)->push_back(*v);
    } 
};

//Global functions:
template<class T, class... Args>
Var list(T t, Args... args){
    Var p;
    p.variable._type = p.ListType;
    p.variable.value.l = new std::vector<Var>();
    
    p._list(&p , t, args...);

    return p;
}

#endif