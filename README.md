###Why is it called Jabber?  
Because the gimmick of this programming languages is creating mini-languages, and the definition of jabber is to "talk rapidly and excitedly but with little sense". Which I think is both funny and fitting.  
This is just brain mush, please ignore  
core data types:  
int  
float  
string 
list  
language  
fun 

quantifiers:  
forall  
exists  
unique  
  
other reserved keywords:  
in  
rejects  
loner  
enumerate  
as  
return  
st  
  
language syntax:  
<type> language <name> <accepts/rejects> <identifier> st <condition>  
example: int language is_even accepts x st x%2=0  
<type> list language <name> <accepts/rejects> <quantifier> <identifier(s)> st <condition>  
example: int list language fizz accepts forall x st x%3=0  
  
accepts/rejects conditions:  
<variable>.language.accepts(fn1)  
enumerate input as i   
    in fizz print "fizz"   
    in buzz print "buzz"   
    rejected print i    
  
input in is_even print "even" not in print "odd" 
 
Example fizzbuzz:  
int language fizz accepts x st x%3=0   
int language buzz accepts x st x%5=0  
enumerate input as i   
    in fizz print "fizz"    
    in buzz print "buzz"   
    loner print i  