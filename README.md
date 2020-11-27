# (Beta)Var: a unique type for C++(with Python/JavaScript Stype)
Var type has the objective to micic the simplicity of Python/JS...  
variables, but with all the good performance and elegance that  
C++ offers.  
Please before making any comment make sure you are aware that   
this is a small trial of the actual proyect I want to build.  
This code is messy, redundant and untidy beacuse I just wanted to  
get an idea, and try some stuff. The real proyect will be in a   different repo, started from scratch with a much better/cleaner    aproach.   
It will obviously be Free Software.  
Any ideas, opinions, better approaches will be welcomed, as long as  
they are respectful and constructive. Thank you all in advance!   

## FAQ
### + Why do you use Unions
There are many different ways to approach this solution. After some ideas, I thought Unions would make the work since it can hold all the
different types without occuping too much memory, and more importantly,
it's a fast approach.

### + Why even bothering on this proyect if you could just use Python/etc.?  
Well, that might be true, but I like the idea of combining the   simplicity of high level languages(interpreted) with the amazing   features of c++ such as efficiency

### + Isn't this a waste of memory?
It is, but I will always try to make variables use the least memory possible. IMO thought, efficiency is much more important in most of  
the chases. The Var type is not thought to be used in limited-memory  
proyects
