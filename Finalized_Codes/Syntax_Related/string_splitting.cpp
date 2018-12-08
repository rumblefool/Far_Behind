// this splitting is better than custom function(w.r.t time)
string line = "GeeksForGeeks is a must try"; 
// Vector of string to save tokens 
vector <string> tokens; 
// stringstream class check1 
stringstream check1(line); 
string ele; 
// Tokenizing w.r.t. space ' ' 
while(getline(check1, ele, ' ')) 
{ 
    tokens.push_back(ele); 
} 
