#include <bits/stdc++.h>
using namespace std;

void encode2B1Q()
{
	lastSignalSignChoice:
	cout << "Was the previous level positive? Enter Yes/No.\n";
	string signOfLastSignal;
	cin >> signOfLastSignal;
	if(signOfLastSignal!="Yes" and signOfLastSignal!="No")
	{
		cout << "Please enter choice correctly.\n";
		goto lastSignalSignChoice;
	}

	string input, output;
	FILE* fp1 = freopen("2B1Qinput.txt","r",stdin); //reading input from file
	getline(cin, input);
	output = "";
	int sz = input.size(), check = 1;
	//first level depends on last non-zero level
	int lastSignalPositive = (signOfLastSignal[0]=='Y');

	if(sz%2)
	{
		check = 0;
	}

	int zc = count(input.begin(),input.end(),'0');
	int oc = count(input.begin(),input.end(),'1');
	if(sz!=(zc+oc))
	{
		check = 0;
	}

	map<string,string> lastSignalPositiveMap, lastSignalNegativeMap;

	lastSignalPositiveMap["00"] = "+1V";
	lastSignalPositiveMap["01"] = "+3V";
	lastSignalPositiveMap["10"] = "-1V";
	lastSignalPositiveMap["11"] = "-3V";

	lastSignalNegativeMap["00"] = "-1V";
	lastSignalNegativeMap["01"] = "-3V";
	lastSignalNegativeMap["10"] = "+1V";
	lastSignalNegativeMap["11"] = "+3V";

	if(check)
	{
		string s;
		s+=input[0];
		s+=input[1];
		if(lastSignalPositive)
		{
			if(lastSignalPositiveMap.find(s)==lastSignalPositiveMap.end())
			{
				check = 0;
			}
			else
			{
				output+=lastSignalPositiveMap[s];
			}
		}
		else
		{
			if(lastSignalNegativeMap.find(s)==lastSignalNegativeMap.end())
			{
				check = 0;
			}
			else
			{
				output+=lastSignalNegativeMap[s];
			}
		}

		int lastSignalPointer = 0;
		for(int i=2;i<sz and check;i+=2)
		{
			output+=" ";
			string s;
			s+=input[i];
			s+=input[i+1];
			lastSignalPositive = (output[lastSignalPointer]=='+');
			if(lastSignalPositive)
			{
				if(lastSignalPositiveMap.find(s)==lastSignalPositiveMap.end())
				{
					check = 0;
				}
				else
				{
					output+=lastSignalPositiveMap[s];
				}
			}
			else
			{
				if(lastSignalNegativeMap.find(s)==lastSignalNegativeMap.end())
				{
					check = 0;
				}
				else
				{
					output+=lastSignalNegativeMap[s];
				}
			}	
			lastSignalPointer+=4;		
		}		
	}

	cout << "Input:\n" << input << endl;
	cout << "Output after 2B1Q encoding:\n";
	if(check) cout << output << endl;
	else cout << "Input string cannot be encoded.\n";
	FILE* fp2 = freopen("2B1Qoutput.txt","w",stdout); // storing output in file
	if(check) cout << output << endl;
	else cout << "Input string cannot be encoded.\n";
	fclose(fp1);
	fclose(fp2);
	exit(0);
}

void decode2B1Q()
{
	lastSignalSignChoice:
	cout << "Was the previous level positive? Enter Yes/No.\n";
	string signOfLastSignal;
	cin >> signOfLastSignal;
	if(signOfLastSignal!="Yes" and signOfLastSignal!="No")
	{
		cout << "Please enter choice correctly.\n";
		goto lastSignalSignChoice;
	}

	string input, output;
	FILE* fp1 = freopen("2B1Qinput.txt","r",stdin); //reading input from file
	getline(cin, input);
	output = "";
	int sz = input.size(), check = 1;

	set<char> allowedCharacters[4];
	allowedCharacters[0].insert('+');
	allowedCharacters[0].insert('-');
	allowedCharacters[1].insert('1');
	allowedCharacters[1].insert('3');
	allowedCharacters[2].insert('V');
	allowedCharacters[3].insert(' ');

	for(int i=0;i<sz;i++)
	{
		char x = input[i];
		if(allowedCharacters[i%4].find(x)==allowedCharacters[i%4].end())
		{
			check = 0;
			break;
		}
	}
	//first level depends on last non-zero level
	int lastSignalPositive = (signOfLastSignal[0]=='Y');	
	
	
	map<string,string> lastSignalPositiveMap, lastSignalNegativeMap;

	lastSignalPositiveMap["+1"] = "00";
	lastSignalPositiveMap["+3"] = "01";
	lastSignalPositiveMap["-1"] = "10";
	lastSignalPositiveMap["-3"] = "11";

	lastSignalNegativeMap["-1"] = "00";
	lastSignalNegativeMap["-3"] = "01";
	lastSignalNegativeMap["+1"] = "10";
	lastSignalNegativeMap["+3"] = "11";

	if(check)
	{
		string s;
		s+=input[0];
		s+=input[1];
		if(lastSignalPositive)
		{
			if(lastSignalPositiveMap.find(s)==lastSignalPositiveMap.end())
			{
				check = 0;
			}
			else
			{
				output+=lastSignalPositiveMap[s];
			}
		}
		else
		{
			if(lastSignalNegativeMap.find(s)==lastSignalNegativeMap.end())
			{
				check = 0;
			}
			else
			{
				output+=lastSignalNegativeMap[s];
			}
		}
		int lastSignalPointer = 0;
		for(int i=4;i<sz and check;i+=4)
		{
			string s;
			s+=input[i];
			s+=input[i+1];
			lastSignalPositive = (input[lastSignalPointer]=='+');
			if(lastSignalPositive)
			{
				if(lastSignalPositiveMap.find(s)==lastSignalPositiveMap.end())
				{
					check = 0;
				}
				else
				{
					output+=lastSignalPositiveMap[s];
				}
			}
			else
			{
				if(lastSignalNegativeMap.find(s)==lastSignalNegativeMap.end())
				{
					check = 0;
				}
				else
				{
					output+=lastSignalNegativeMap[s];
				}
			}	
			lastSignalPointer+=4;		
		}
		
	}
	cout << "Input:\n" << input << endl;
	cout << "Output after 2B1Q decoding:\n";
	if(check) cout << output << endl;
	else cout << "Input string cannot be decoded.\n";
	FILE* fp2 = freopen("2B1Qoutput.txt","w",stdout); // storing output in file
	if(check) cout << output << endl;
	else cout << "Input string cannot be decoded.\n";
	fclose(fp1);
	fclose(fp2);
	exit(0);
}

void encodeMLT3()
{
	lastSignalSignChoice:
	cout << "Was the last non-zero level positive? Enter Yes/No.\n";
	string signOfLastSignal;
	cin >> signOfLastSignal;
	if(signOfLastSignal!="Yes" and signOfLastSignal!="No")
	{
		cout << "Please enter choice correctly.\n";
		goto lastSignalSignChoice;
	}

	string input, output;
	FILE* fp1 = freopen("MLT3input.txt","r",stdin); //reading input from file
	getline(cin, input);
	output = "";
	int sz = input.size(), check = 1;
	int lastSignalPositive = (signOfLastSignal[0]=='Y');	
	int zc = count(input.begin(),input.end(),'0');
	int oc = count(input.begin(),input.end(),'1');
	if(sz!=(zc+oc))
	{
		check = 0;
	}

	int lastElement = 0;
	if(check)
	{
		for(int i = 0; i<sz; i++)
		{
			if(i) output+=" ";
			if(input[i]=='1')
			{
				if(lastElement!=0)
				{
					lastElement = 0;
					output+="0V";
				}
				else
				{
					if(lastSignalPositive)
					{
						output+="-5V";
						lastElement = -1;
					}
					else
					{
						output+="+5V";
						lastElement = 1;
					}
					lastSignalPositive^=1;
				}
			}
			else
			{
				if(!lastElement)
				{
					output+="0V";
				}
				else if(lastElement==1)
				{
					output+="+5V";
				}
				else
				{
					output+="-5V";
				}
			}
		}
	}

	cout << "Input:\n" << input << endl;
	cout << "Output after MLT3 encoding:\n";
	if(check) cout << output << endl;
	else cout << "Input string cannot be encoded.\n";
	FILE* fp2 = freopen("MLT3output.txt","w",stdout); // storing output in file
	if(check) cout << output << endl;
	else cout << "Input string cannot be encoded.\n";
	fclose(fp1);
	fclose(fp2);
	exit(0);
}

void decodeMLT3()
{
	lastSignalSignChoice:
	cout << "Was the last non-zero level positive? Enter Yes/No.\n";
	string signOfLastSignal;
	cin >> signOfLastSignal;
	if(signOfLastSignal!="Yes" and signOfLastSignal!="No")
	{
		cout << "Please enter choice correctly.\n";
		goto lastSignalSignChoice;
	}


	string input, output;
	FILE* fp1 = freopen("MLT3input.txt","r",stdin); //reading input from file
	getline(cin, input);
	output = "";
	int sz = input.size(), check = 1;
	int lastSignalPositive = (signOfLastSignal[0]=='Y');
	char lastSign = '-';
	int lastZero = 1;
	if(lastSignalPositive) lastSign = '+';
	for(int i = 0; i<sz and check; )
	{
		if(input[i]=='0')
		{
			if(i>=sz-1) check = 0;
			else if(input[i+1]!='V') check = 0;
			else if(i+2!=sz and input[i+2]!=' ') check = 0;
			i+=3;
			lastZero = 1;
		}
		else if(input[i]=='+' or input[i]=='-')
		{
			if(i>=sz-2) {check = 0; cout << i << " 1\n";}
			else if(input[i]==lastSign and lastZero) {check = 0;}
			else if(input[i]!=lastSign and !lastZero) {check = 0;}
			else if(input[i+1]!='5' or input[i+2]!='V') {check = 0;}
			else if(i+3!=sz and input[i+3]!=' ') {check = 0;}
			lastSign = input[i];
			i+=4;
			lastZero=0;	
		}
		else
		{
			check = 0;
		}
	}
	if(check)
	{
		char lastSign = '-';
		if(lastSignalPositive) lastSign = '+';
		else lastSign = '-';
		int lastVoltage = 0;
		for(int i = 0; i<sz; )
		{
			if(input[i]=='0')
			{
				if(!lastVoltage)
				{
					output+='0';
				}
				else
				{
					output+='1';
					lastVoltage = 0;
				}
				lastSign = '#';
				i+=3;
			}
			else if(input[i]=='+')
			{
				if(lastVoltage == 1)
				{
					output+='0';
				}
				else
				{
					output+='1';
					lastVoltage = 1;
				}
				lastSign = '+';
				i+=4;
			}
			else
			{
				if(lastVoltage == -1)
				{
					output+='0';
				}
				else
				{
					output+='1';
					lastVoltage = -1;
				}
				lastSign = '-';
				i+=4;
			}
		}
	}

	cout << "Input:\n" << input << endl;
	cout << "Output after MLT3 decoding:\n";
	if(check) cout << output << endl;
	else cout << "Input string cannot be decoded.\n";
	FILE* fp2 = freopen("MLT3output.txt","w",stdout); // storing output in file
	if(check) cout << output << endl;
	else cout << "Input string cannot be decoded.\n";
	fclose(fp1);
	fclose(fp2);
	exit(0);
}

void encodeB8ZS()
{
	lastSignalSignChoice:
	cout << "Was the last non-zero level positive? Enter Yes/No.\n";
	string signOfLastSignal;
	cin >> signOfLastSignal;
	if(signOfLastSignal!="Yes" and signOfLastSignal!="No")
	{
		cout << "Please enter choice correctly.\n";
		goto lastSignalSignChoice;
	}
	string input, output;
	FILE* fp1 = freopen("B8ZSinput.txt","r",stdin); //reading input from file
	getline(cin, input);
	output = "";
	int sz = input.size(), check = 1;
	int lastSignalPositive = (signOfLastSignal[0]=='Y');
	string eightzeros = "00000000";
	int pos;
	int zc = count(input.begin(),input.end(),'0');
	int oc = count(input.begin(),input.end(),'1');
	if(sz!=(zc+oc))
	{
		check = 0;
	}
	for(pos = 0; pos<sz and check;)
	{
		if(pos) output+=" ";
		if(input[pos]=='1')
		{
			if(!lastSignalPositive) output+="+5V";
			else output+="-5V";
			lastSignalPositive^=1;
			pos++;
		}
		else
		{
			if(pos+8<=sz and input.substr(pos,8)==eightzeros)
			{
				for(int i = 0; i<3; i++) output+="0V ";
				int Vsign = lastSignalPositive;
				int Bsign = Vsign^1;
				if(Vsign)
				{
					output+="+5V -5V 0V -5V +5V";
				}
				else
				{
					output+="-5V +5V 0V +5V -5V";
				}
				pos+=8;
			}
			else
			{
				output+="0V";
				pos++;
			}
		}
	}

	cout << "Input:\n" << input << endl;
	cout << "Output after B8ZS encoding:\n";
	if(check) cout << output << endl;
	else cout << "Input string cannot be encoded.\n";
	FILE* fp2 = freopen("B8ZSoutput.txt","w",stdout); // storing output in file
	if(check) cout << output << endl;
	else cout << "Input string cannot be encoded.\n";
	fclose(fp1);
	fclose(fp2);
	exit(0);	
}

string opposite(string s)
{
	if(s=="+5V") return "-5V";
	if(s=="-5V") return "+5V";
	return s;
}

void decodeB8ZS()
{
	lastSignalSignChoice:
	cout << "Was the last non-zero level positive? Enter Yes/No.\n";
	string signOfLastSignal;
	cin >> signOfLastSignal;
	if(signOfLastSignal!="Yes" and signOfLastSignal!="No")
	{
		cout << "Please enter choice correctly.\n";
		goto lastSignalSignChoice;
	}
	string input, output;
	FILE* fp1 = freopen("B8ZSinput.txt","r",stdin); //reading input from file
	getline(cin, input);
	output = "";
	int sz = input.size(), check = 1;
	int lastSignalPositive = (signOfLastSignal[0]=='Y');
	stringstream ss(input);
	vector<string> all_levels;
	string curLevel;
	while(ss>>curLevel)
	{
		if(curLevel!="0V" and curLevel!="+5V" and curLevel!="-5V") check = 0;
		all_levels.push_back(curLevel);
	}
	sz = all_levels.size();
	string lastNonZeroVoltage = "-5V";
	if(lastSignalPositive) lastNonZeroVoltage = "+5V";
	for(int i = 0; i<sz and check;)
	{
		string curVoltage = all_levels[i];
		if(curVoltage!="0V")
		{
			if(curVoltage==lastNonZeroVoltage)
			{
				check = 0;
			}
			else
			{
				output+="1";
				lastNonZeroVoltage = opposite(lastNonZeroVoltage);
			}
			i++;
		}
		else if(i<=sz-8)
		{
			if(all_levels[i]=="0V" and all_levels[i+1]=="0V" 
				and all_levels[i+2]=="0V" and all_levels[i+3]==lastNonZeroVoltage 
				and all_levels[i+4]==opposite(all_levels[i+3]) and all_levels[i+5]=="0V"
				 and all_levels[i+6]==opposite(all_levels[i+3]) and all_levels[i+7]==all_levels[i+3])
			{
				output+="00000000";
				i+=8;
			}
			else
			{
				output+="0";
				i++;
			}
		}
		else
		{
			output+="0";
			i++;
		}
	}

	cout << "Input:\n" << input << endl;
	cout << "Output after B8ZS decoding:\n";
	if(check) cout << output << endl;
	else cout << "Input string cannot be decoded.\n";
	FILE* fp2 = freopen("B8ZSoutput.txt","w",stdout); // storing output in file
	if(check) cout << output << endl;
	else cout << "Input string cannot be decoded.\n";
	fclose(fp1);
	fclose(fp2);
	exit(0);
}

void encodeHDB3()
{
	lastSignalSignChoice:
	cout << "Was the last non-zero level positive? Enter Yes/No.\n";
	string signOfLastSignal;
	cin >> signOfLastSignal;
	if(signOfLastSignal!="Yes" and signOfLastSignal!="No")
	{
		cout << "Please enter choice correctly.\n";
		goto lastSignalSignChoice;
	}

	string input, output;
	FILE* fp1 = freopen("HDB3input.txt","r",stdin); //reading input from file
	getline(cin, input);
	output = "";
	int sz = input.size(), check = 1;
	int lastSignalPositive = (signOfLastSignal[0]=='Y');
	string fourzeros = "0000";
	int zc = count(input.begin(),input.end(),'0');
	int oc = count(input.begin(),input.end(),'1');
	if(sz!=(zc+oc))
	{
		check = 0;
	}
	int pos, nonzeropulses = 0;
	for(pos = 0; pos<sz and check;)
	{
		if(pos) output+=" ";
		if(input[pos]=='1')
		{
			if(!lastSignalPositive) output+="+5V";
			else output+="-5V";
			lastSignalPositive^=1;
			pos++;
			nonzeropulses++;
		}
		else
		{
			if(pos+4<=sz and input.substr(pos,4)==fourzeros)
			{
				if(nonzeropulses%2)
				{
					for(int i = 0; i<3; i++)
					{
						output+="0V ";
					}
					if(lastSignalPositive) output+="+5V";
					else output+="-5V"; 
				}
				else
				{
					if(!lastSignalPositive)
					{
						output+="+5V 0V 0V +5V";
					}
					else
					{
						output+="-5V 0V 0V -5V";
					}
					lastSignalPositive^=1;
				}
			
				nonzeropulses = 0;
				pos+=4;
			}
			else
			{
				output+="0V";
				pos++;
			}
		}
	}
	cout << "Input:\n" << input << endl;
	cout << "Output after HDB3 encoding:\n";
	if(check) cout << output << endl;
	else cout << "Input string cannot be encoded.\n";
	FILE* fp2 = freopen("HDB3output.txt","w",stdout); // storing output in file
	if(check) cout << output << endl;
	else cout << "Input string cannot be encoded.\n";
	fclose(fp1);
	fclose(fp2);
	exit(0);
}
	
vector<string> split(string str, string delim) {

    vector<string> splitStrings;
    size_t pos = 0;
    string token;

    while ((pos = str.find(delim)) != string::npos) {
        token = str.substr(0, pos);
        splitStrings.push_back(token);
        str.erase(0, pos + delim.length());
    }
    splitStrings.push_back(str);
    return splitStrings;
}

void decodeHDB3()
{
	string input;
	FILE* fp1 = freopen("HDB3input.txt","r",stdin); //reading input from file
	getline(cin, input);
	int sz = input.size(), check = 1;
	
	vector<string> levels = split(input, " ");
    bool prevState = false;
    
    string output = "";

    bool isNonZeroEven = true;

    int levelsSize = levels.size();
    for (int idx = 0; idx < levelsSize; idx++) {
                if ((idx + 3) < levelsSize)
                {
                    if (prevState) {
                       if (isNonZeroEven) {
                           if (levels[idx] == "-5V" && levels[idx + 1] == "0V" && levels[idx + 2] == "0V" && levels[idx + 3] == "-5V") {
                               output.append("0000");
                               idx += 3;
                               isNonZeroEven = true;
                               prevState = !prevState;
                               continue;
                           }
                       } else {
                           if (levels[idx] == "0V" && levels[idx + 1] == "0V" && levels[idx + 2] == "0V" && levels[idx + 3] == "+5V") {
                               output.append("0000");
                               idx += 3;
                               isNonZeroEven = true;
                               continue;
                            }
                       }
                    } else {
                        if (isNonZeroEven) {
                           if (levels[idx] == "+5V" && levels[idx + 1] == "0V" && levels[idx + 2] == "0V" && levels[idx + 3] == "+5V") {
                               output.append("0000");
                               idx += 3;
                               isNonZeroEven = true;
                               prevState = !prevState;
                               continue;
                           }
                       } else {
                           if (levels[idx] == "0V" && levels[idx + 1] == "0V" && levels[idx + 2] == "0V" && levels[idx + 3] == "-5V") {
                               output.append("0000");
                               idx += 3;
                               isNonZeroEven = true;
                               continue;
                           }
                       }
                    }
                    if (levels[idx] == "0V") {
                        output.append("0");
                    } else if ((levels[idx] == "+5V" && prevState) || (levels[idx] == "-5V" && !prevState)) {
                        //Invalid sequence.
                        check = 0;
                        break;
                    } else if (levels[idx] == "+5V" || levels[idx] == "-5V") {
                        output.append("1");
                        prevState = !prevState;
                        isNonZeroEven = !isNonZeroEven;
                    } else {
                       // Invalid voltage level found.
                        check = 0;
                        break;
                    }
                } else if (levels[idx] == "0V") {
                    output.append("0");
                } else if ((levels[idx] == "+5V" && prevState) || (levels[idx] == "-5V" && !prevState)) {
                    //Invalid sequence.
                    check = 0;
                    break;
                } else if (levels[idx] == "+5V" || levels[idx] == "-5V") {
                    output.append("1");
                    prevState = !prevState;
                    isNonZeroEven = !isNonZeroEven;
                } else {
                    //Invalid voltage level found.
                    check = 0;
                    break;
                }
            }
    cout << "Input:\n" << input << endl;
	cout << "Output after HDB3 decoding:\n";
	if(check) cout << output << endl;
	else cout << "Input string cannot be decoded.\n";
	FILE* fp2 = freopen("HDB3output.txt","w",stdout); // storing output in file
	if(check) cout << output << endl;
	else cout << "Input string cannot be decoded.\n";
	fclose(fp1);
	fclose(fp2);
	exit(0);
}

int main()
{
	int choiceofAction, choiceofScheme;
	ActionChoice:
	cout << "Enter your choice of action.\n";
	cout << "(1) Encode\n(2) Decode\n(3) Exit\n";
	cin >> choiceofAction;
	if(choiceofAction==1)
	{
		EncodingSchemeChoice:
		cout << "Enter your choice of scheme.\n";
		cout << "(1) 2B1Q\n(2) MLT3\n(3) B8ZS\n(4) HDB3\n(5) Back\n";
		cin >> choiceofScheme;
		if(choiceofScheme==1)
		{
			encode2B1Q();
		}
		else if(choiceofScheme==2)
		{
			encodeMLT3();
		}
		else if(choiceofScheme==3)
		{
			encodeB8ZS();
		}
		else if(choiceofScheme==4)
		{
			encodeHDB3();
		}
		else if(choiceofScheme==5)
		{
			goto ActionChoice;
		}
		else
		{
			cout << "Invalid choice. Try again.\n";
			goto EncodingSchemeChoice;
		}
		goto EncodingSchemeChoice;
	}
	else if(choiceofAction==2)
	{
		DecodingSchemeChoice:
		cout << "Enter your choice of scheme.\n";
		cout << "(1) 2B1Q\n(2) MLT3\n(3) B8ZS\n(4) HDB3\n(5) Back\n";
		cin >> choiceofScheme;
		if(choiceofScheme==1)
		{
			decode2B1Q();
		}
		else if(choiceofScheme==2)
		{
			decodeMLT3();
		}
		else if(choiceofScheme==3)
		{
			decodeB8ZS();
		}
		else if(choiceofScheme==4)
		{
			decodeHDB3();
		}
		else if(choiceofScheme==5)
		{
			goto ActionChoice;
		}
		else
		{
			cout << "Invalid choice. Try again.\n";
			goto DecodingSchemeChoice;
		}
		goto DecodingSchemeChoice;
	}
	else if(choiceofAction==3)
	{
		return 0;
	}
	else
	{
		cout << "Invalid choice. Try again.\n";
	}
}