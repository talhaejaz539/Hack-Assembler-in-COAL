#include<iostream>
#include<fstream>
#include<sstream>       // stringstream() defined
#include<string>
#include<algorithm>     // center.erase() defined
using namespace std;

string removeSpaces(string a) {
	string c = "";
	for (int i = 0; i < a.length(); i++)
	    if (a[i] != ' ' && a[i] != '\t')
	        c += a[i];
	return c;
}
void decimalToBinary(ostream& out, int n) {
	int a[16], i;
	for (int i = 0; i < 16; i++)
		a[i] = 0;
	for (i = 15; n > 0; i--) {
		a[i] = n % 2;
		n = n / 2;
	}
	for (i = 0; i < 16; i++)
		out << a[i];
	out << '\n';
}
string getLeft(string a, char delim) {
	string c = "";
	for(int i=0;i<a.length();i++)
		if(a[i] == delim)
			break;
		else 
			c += a[i];
	return c;
}
string getRight(string a, char delim) {
	string c = "";
	bool flag = false;	int size;
	for(int i=0;i<a.length();i++)
		if(a[i] == delim) {
			flag = true;
			size = ++i;
			break;
		}
	for(int i=size;i<a.length();i++)
		c += a[i];	
	return c;
}
string getComp(string tempC) {
	string comp = "0000000";
	if(tempC == "0")
		comp = "0101010";
	else if(tempC == "1")
		comp = "0111111";
	else if(tempC == "-1")
		comp = "0111010";
	else if(tempC == "D")
		comp = "0001100";
	else if(tempC == "A")
		comp = "0110000";
	else if(tempC == "!D")
		comp = "0001101";
	else if(tempC == "!A")
		comp = "0110001";
	else if(tempC == "-D")
		comp = "0001111";
	else if(tempC == "-A")
		comp = "0110011";
	else if(tempC == "D+1")
		comp = "0011111";
	else if(tempC == "A+1")
		comp = "0110111";
	else if(tempC == "D-1")
		comp = "0001110";
	else if(tempC == "A-1")
		comp = "0110010";
	else if(tempC == "D+A")
		comp = "0000010";
	else if(tempC == "D-A")
		comp = "0010011";
	else if(tempC == "A-D")
		comp = "0000111";
	else if(tempC == "D&A")
		comp = "0000000";
	else if(tempC == "D|A")
		comp = "0010101";
	else if(tempC == "M")
		comp = "1110000";
	else if(tempC == "!M")
		comp = "1110001";
	else if(tempC == "-M")
		comp = "1110011";
	else if(tempC == "M+1")
		comp = "1110111";
	else if(tempC == "M-1")
		comp = "1110010";
	else if(tempC == "D+M")
		comp = "1000010";
	else if(tempC == "D-M")
		comp = "1010011";
	else if(tempC == "M-D")
		comp = "1000111";
	else if(tempC == "D&M")
		comp = "1000000";
	else if(tempC == "D|M")
		comp = "1010101";
	return comp;
}
string getDest(string temp) {
	string dest;
	if(temp == "null")
		dest = "000";
	else if(temp == "M")
		dest = "001";
	else if(temp == "D")
		dest = "010";
	else if(temp == "MD")
		dest = "011";
	else if(temp == "A")
		dest = "100";
	else if(temp == "AM")
		dest = "101";
	else if(temp == "AD")
		dest = "110";
	else if(temp == "AMD")
		dest = "111";
	return dest;
}
string getJump(string temp) {
	string jump;
	if(temp == "null")
		jump = "000";
	else if(temp == "JGT")
		jump = "001";
	else if(temp == "JEQ")
		jump = "010";
	else if(temp == "JGE")
		jump = "011";
	else if(temp == "JLT")
		jump = "100";
	else if(temp == "JNE")
		jump = "101";
	else if(temp == "JLE")
		jump = "110";
	else if(temp == "JMP")
		jump = "111";
	return jump;
}

int main() {
    cout << "\n\t\t\t Hack Assembler \n\n\n\n";
    ifstream in("test.asm");	// Input file
	ofstream out("test.hack");	// Output file
	bool flag = false;
	string input, center;	
	string fix = "111" , dest, jump, comp;
    while(true) {   // Till EOF
        getline(in,input);      // Input from file
        if(in.fail())   break;  // End of file check
        if(!input.empty()) {    // Empty Lines
        	flag = false;
            center = removeSpaces(center);      //Remove Indentation
            if(input[0] != '/'  && input[1] != '/') {       //Line Comments
                center = input;     // Input from file into a new string 'center'
                center.erase(remove(center.begin(), center.end(), ' '), center.end());      //Ignore Whitespaces
                center = center.substr(0,center.find("//",0));      //Inline Comments
                center = removeSpaces(center);      //Remove spaces after inline comments
                for(int i=0;i<center.size();i++)	
					if(center[i] == '=' || center[i] == ';')	
						flag = true;
                for(int i=0;i<center.size();i++) {
                    // A - Instruction
                    if(center[0] == '@') {
                        center = center.substr(1,center.find("@",1));	// Remove '@' sign
                        stringstream degree(center);
                        int valueA = 0;
                        degree >> valueA;	// String convert into integer
                        decimalToBinary(out,valueA);	// For Binary of A instruction
                        break;
                    }
                    // dest = comp
                    else if(center[i] == '=') {
                        jump = "000";	// For destination, jump = 000
                        
                        // dest
                        string temp = getLeft(center, '=');		// For Destination 
                        dest = getDest(temp);	// For Destination Binary
                        
                        //comp
                        string tempC = getRight(center, '=');	// For Computation
                        comp = getComp(tempC);	// For Computation Binary
                        
                        out << fix + comp + dest + jump;		// Final result
                        out << '\n';
                        break;
                    }
                    // comp ; jump
                    else if(center[i] == ';') {
                        dest = "000";	// For Jump, destination = 000
                        
                        //comp
                        string tempC = getLeft(center, ';');	// For Computation
                        comp = getComp(tempC);	// For Computation Binary
                        
                        // jump
                        string temp = getRight(center, ';');	// For Jump	
                        jump = getJump(temp);	// For Jump Binary
                        
                        out << fix + comp + dest + jump;	// Final result
                        out << '\n';
                        break;
                    }
                    else if(center[i] != '=' && center[i] != ';' && center[i] != '@' && flag == false){
                        dest = jump = "000";
                        comp = getComp(center);
                        out << fix + comp + dest + jump;
                        out << '\n';
                        break;
                    }
                }
            }
        }
    }
    cout << " File Write Successfully!\n";
	in.close();
	out.close();
    return 0;
}
//			Task Description
// For removing whitespaces; https://www.codegrepper.com/code-examples/cpp/c%2B%2B+remove+whitespace+from+string
// For parsing string; https://www.bitdegree.org/learn/string-to-int-c-plus-plus
// For inline comments; https://stackoverflow.com/questions/10392405/removing-everything-after-character-and-also-character
