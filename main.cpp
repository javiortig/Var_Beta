#include "Var.h"

/*
    Make sure you first read the README.md file 
*/

//This is a brief example to get an idea of what I'm trying to approach

void examplePrint(Var &v, const char &name){
    std::cout << "[Var "<< name << "] Type:";
    v.printType(false);
    std::cout << "  Value:";
    v.print();
}

int main(){
    Var a;
    Var b = 5;
    Var c = 'c';
    Var d = "Hello String";
    Var e = false;

    examplePrint(a, 'a');
    examplePrint(b, 'b');
    examplePrint(c, 'c');
    examplePrint(d, 'd');
    examplePrint(e, 'e');
    std::cout << endl;

    //Var can change to any value easily just like python/js
    Var f = a;
    f = "potatoe";
    examplePrint(f, 'f');
    f = d;
    examplePrint(f, 'f');
    f = -454.321;
    examplePrint(f, 'f');

    //Lists (and willing to add dictionaries):
    Var l = list(-2, 1,'2', nullptr, 3.14, "number 4", true);
    examplePrint(l, 'l');
    //nested list:
    l = list(a, b, 1, list("234", '5', -6.00001), list(list(7,list(8), 9), "10"));
    examplePrint(l, 'l');
    cout << endl;

    //operations:
    a = b + 5;
    Var g = b + 1.54;
    Var h = c + 1;
    Var v = l + "Last element";
    examplePrint(a, 'a');
    examplePrint(g, 'g');
    examplePrint(h, 'h');
    examplePrint(v, 'v');

    return 0;
}

int main(){
    Var a = "hello strin";
    Var b = a;
    b = a + 'g';
    Var l = list(1, 2, b, list("nested", 'c', true, a));

    Var n = 1;
    Var f;
    f = n + 5.675;

}