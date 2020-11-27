# (Beta)Var: a unique type for C++(with Python/JavaScript Style)
Var type has the objective to micic the simplicity of Python/JS... variables, but with all the good performance and elegance that C++ offers.  
Please before making any comment make sure you are aware that this is a small trial of the actual project I want to build. This code is messy, redundant and untidy because I just wanted to get an idea, and try some stuff. The real project will be in a different repo, started from scratch with a much better and cleaner approach.   
It will obviously be Free Software.  
Any ideas, opinions, better approaches will be welcomed, as long as they are respectful and constructive. Thank you all in advance!     

## FAQ
### + Why do you use Unions
There are many different ways to approach this solution. After some ideas, I thought Unions would make the work since it can hold all the different types without occupying too much memory, and more importantly, it's a fast approach.

### + Why even bothering on this project if you could just use Python/etc.?  
Well, that might be true, but I like the idea of combining the simplicity of high level languages(interpreted) with the amazing features of c++ such as efficiency  

### + Isn't this a waste of memory?
It is, but I will always try to make variables use the least memory possible. IMO thought, efficiency is much more important in most of the cases. The Var type is not thought to be used in limited-memory projects

### + Isn't std::any or std::variant what you are trying to achieve?
It has very similar features, but i want to achieve the syntactical sugars I present in the main.cpp file. std::any/variant requires more typing/casting, etc etc. I want to create a Class that can be a dictionary, a list, a string, a char... All at once. again, check the main.cpp to see what I mean by 'syntactical sugars'.

### + Isn't this very inefficient?
It depends. If you are looking from a C perspective, it obviously is. There is nothing more efficient than using the C++ standards(in general terms). But in the other hand, if you compare it to languages such as python, this solution will be(one day, remember this is a messy beta far from waht i want to build) faster by orders of magnitude.

for any questions/suggestions/ideas go check https://www.reddit.com/r/cpp/comments/k21syx/looking_for_ideasadvices_betavar_a_unique_type/
