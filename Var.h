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
    TODO: Reacer sin usar las clases de std pq se buguea la mem?
    TODO: arreglar nested vectors
    -TODO: throw errors and terminate program when invalid sumation, etc
*/
/*
    Tip: se podria reducir lineas de codigo en los nested switches
    de operaciones como adition utilizando la logica de una matriz 
    triangular
*/

#define N_VAR_TYPES 8

using namespace std;

class Var{
private:
    struct Value{
        int type;
        size_t len;

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
    void clearVar();
    void pTab(int k = 0); //couts a tab as many times as k

public:
    //type constants
    // longs are used as Int and double as Float for code simplification
    static constexpr int NullType = 0;
    static constexpr int CharType = 1;
    static constexpr int IntType = 2;
    static constexpr int FloatType = 3;
    static constexpr int BoolType = 4;
    static constexpr int StringType = 5;
    static constexpr int ListType = 6;
    static constexpr int DictType = 7;
    static constexpr int _VarType = 8;

    //methods:
    void print(bool pretty = false, bool endLine = true);
    void printType(bool endLine = true);
    

    //constructors and destructors:
    Var(){
        this->variable.type = NullType;
        this->variable.value.n = nullptr;
        this->variable.len = -1;
    };
    template<class Any> 
    Var(Any v){
        convertToVar(this, v);
    };

    ~Var(){ 
        this->clearVar();
    };

private:
//Inside methods:
    template<class Any> 
    bool isPointerOrArray(Any v){
        return (std::is_pointer<Any>::value || std::is_array<Any>::value);
    };
        
    template<class Any> 
    int getVarTypeFromAnyType(Any v){
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
            return this->BoolType;
        }
        //String
        else if(typeHash == typeid(char *).hash_code() ||
                typeHash == typeid(const char *).hash_code()){
            return this->StringType;
        }
        //any pointer/array is considered a list, or a vector
        else if(isPointerOrArray(v) || 
                typeHash == typeid(std::vector<Var>).hash_code()){
            return this->ListType;
        }
        //already a Var
        else if(typeHash == typeid(Var).hash_code()){
            return this->_VarType;
        }
        else{
            //ERROR
        }

        return -1;
    };

    //C type to Var conversion functions:
    //For Null
    void convertCTypeToVar(Var* var, std::nullptr_t v){
        var->variable.len = -1;
        var->variable.value.n = nullptr;
    };
    //For int, float and char
    void convertCTypeToVar(Var* var ,const double& v){
        var->variable.len = -1;

        switch (var->variable.type)
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
        case BoolType:
            var->variable.value.b = (bool)v;
            break;
        default:
            //Error
            break;
        }
    };    
    //For String
    void convertCTypeToVar(Var* var, const char* v){
        var->variable.len = strlen(v);
        var->variable.value.s = new std::string(v);
    };
    //For Lists 
    /*
        TODO: ACEPTAR punteros a punteros, arrays con arrays
        usando recursividad?
    */
    void convertCTypeToVar(Var* var, const void* v){
        
    };
    void convertCTypeToVar(Var* var, vector<Var> &v){
        var->variable.value.l = new vector<Var>(v);
    };

    //general function to be called for C main types
    template<class Any>
    void convertToVar(Var* var, Any v){
        var->variable.type = getVarTypeFromAnyType(v);
        convertCTypeToVar(var, v);
    };

    void convertToVar(Var* var, Var &v){
        var->variable.type = v.variable.type;
        var->variable.len = v.variable.len;
        switch (this->variable.type)
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
        case this->BoolType:
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
    
/*inner operation functions:*/
    //general:
        //float>char>int
    void numberBasicOperations(Var *result, Var &a, Var &b, char _operation);

    //addition:
    Var addition(Var &a, Var &b);
    void stringAddition(Var *result, Var &a, Var &b);//concatenation
    void listAddition(Var *result, Var &a, Var &b);//concatenation
    

public:
    //Template operators:
    // assignment
    void operator=(Var &v){
        this->clearVar();
        this->convertToVar(this, v);
    };

    template<class Any> 
    void operator=(Any v){
        this->clearVar();
        this->convertToVar(this, v);
    };

    // addition
    Var operator+(Var &v){
        return addition(*this, v);
    };
    template<class Any> 
    Var operator+(Any v){
        Var b;
        convertToVar(&b, v);

        return addition(*this, b);
    };

public:
    //global functs that need friend
    template<class T, class... Args>
    friend Var list(T t, Args... args);

private://inner functions of global functions such as list()
    template<class T, class... Args>
    void iList(Var *p, T t, Args... args){
        Var *v = new Var(t);
        p->variable.value.l->push_back(*v);

        iList(p ,args...);
    };

    template<class T>
    void iList(Var *p, T t){
        Var *v = new Var(t);
        (p->variable.value.l)->push_back(*v);
    } 
};

//Global functions:
template<class T, class... Args>
Var list(T t, Args... args){
    Var p;
    p.variable.type = p.ListType;
    p.variable.value.l = new std::vector<Var>();

    p.iList(&p , t, args...);

    return p;
}

#endif