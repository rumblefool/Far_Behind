string line = "GeeksForGeeks is a must try";
vector <string> tokens; 
stringstream check1(line); 
string ele; 
while(getline(check1, ele, ' ')) { 
    tokens.push_back(ele);}