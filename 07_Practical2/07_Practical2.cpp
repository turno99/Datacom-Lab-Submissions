#include <bits/stdc++.h>
using namespace std;

void ManchesterEncoding()
{
	string input, output;
	FILE* fp1 = freopen("input.txt","r",stdin); //reading input from file
	getline(cin, input);
	output = "";
	int sz = input.size(), check = 1;
	for(int i = 0; i<sz; i++)
	{
		if(input[i]=='0')
		{
			output+="+5V,-5V";
		}
		else if(input[i]=='1')
		{
			output+="-5V,+5V";
		}
		else
		{
			check = 0; // the input string contains invalid characters
			break;
		}
		if(i!=sz-1) output+=" ";
	}
	cout << "Input:\n" << input << endl;
	cout << "Output after Manchester encoding:\n";
	if(check) cout << output << endl;
	else cout << "Input string cannot be encoded.\n";
	FILE* fp2 = freopen("output.txt","w",stdout);// storing output in file
	if(check) cout << output << endl;
	else cout << "Input string cannot be encoded.\n";
	fclose(fp1);
	fclose(fp2);
	exit(0);
}

void ManchesterDecoding()
{
	string input, output;
	FILE* fp1 = freopen("input.txt","r",stdin); //reading input from file
	getline(cin, input);
	output = "";
	int sz = input.size(), check = 1;

	for(int i = 0; i<sz; i+=8)
	{
		if(input[i]==input[i+4]) // two phases of biphase must not be same
		{
			check = 0;
			break;
		}
		if(input[i]=='+')
		{
			output+="0";
		}
		else if(input[i]=='-')
		{
			output+="1";
		}
		else
		{
			check = 0; // the input string contains invalid characters
			break;
		}
	}
	cout << "Input:\n" << input << endl;
	cout << "Output after Manchester decoding:\n";
	if(check) cout << output << endl;
	else cout << "Input string cannot be decoded.\n";
	FILE* fp2 = freopen("output.txt","w",stdout); // storing output in file
	if(check) cout << output << endl;
	else cout << "Input string cannot be decoded.\n";
	fclose(fp1);
	fclose(fp2);
	exit(0);
}

void DifferentialManchesterEncoding()
{

	lastSignalSignChoice:
	cout << "Was the last non-zero signal positive? Enter Yes/No.\n";
	string signOfLastSignal;
	cin >> signOfLastSignal;
	if(signOfLastSignal!="Yes" and signOfLastSignal!="No")
	{
		cout << "Please enter choice correctly.\n";
		goto lastSignalSignChoice;
	}

	string input, output;
	FILE* fp1 = freopen("input.txt","r",stdin); //reading input from file
	getline(cin, input);
	output = "";
	int sz = input.size(), check = 1;
	//first level depends on last non-zero level
	int lastSignalPositive = (signOfLastSignal[0]=='Y');

	if(input[0]=='0')
	{
		if(lastSignalPositive) output+="-5V,+5V";
		else output+="+5V,-5V";
	}
	else if(input[0]=='1')
	{
		if(!lastSignalPositive) output+="-5V,+5V";
		else output+="+5V,-5V";
	}
	else
	{
		check = 0; // the input string contains invalid characters
	}

	int lastSignalPointer = 0;	
	for(int i = 1; i<sz; i++)
	{
		output+=' ';
		if(input[i]=='1')
		{
			if(output[lastSignalPointer]=='+')
			{
				output+="-5V,+5V";
			}
			else
			{
				output+="+5V,-5V";
			}
		}
		else if(input[i]=='0')
		{
			if(output[lastSignalPointer]=='-')
			{
				output+="-5V,+5V";
			}
			else
			{
				output+="+5V,-5V";
			}
		}
		else
		{
			check = 0;// the input string contains invalid characters
			break;
		}
		lastSignalPointer+=8;
	}
	cout << "Input:\n" << input << endl;
	cout << "Output after differential Manchester encoding:\n";
	if(check) cout << output << endl;
	else cout << "Input string cannot be encoded.\n";
	FILE* fp2 = freopen("output.txt","w",stdout); // storing output in file
	if(check) cout << output << endl;
	else cout << "Input string cannot be encoded.\n";
	fclose(fp1);
	fclose(fp2);
	exit(0);
}

void DifferentialManchesterDecoding()
{
	lastSignalSignChoice:
	cout << "Was the last non-zero signal positive? Enter Yes/No.\n";
	string signOfLastSignal;
	cin >> signOfLastSignal;
	if(signOfLastSignal!="Yes" and signOfLastSignal!="No")
	{
		cout << "Please enter choice correctly.\n";
		goto lastSignalSignChoice;
	}

	string input, output;
	FILE* fp1 = freopen("input.txt","r",stdin); //reading input from file
	getline(cin, input);
	output = "";
	int sz = input.size(), check = 1;
	//first level depends on last non-zero level
	int lastSignalPositive = (signOfLastSignal[0]=='Y');

	if(input[0]=='+')
	{
		if(lastSignalPositive) output+='1';
		else output+='0';
	}
	else if(input[0]=='-')
	{
		if(!lastSignalPositive) output+='1';
		else output+='0';
	}
	
	for(int i = 8; i<sz; i+=8)
	{
		if(input[i]==input[i+4])
		{
			check = 0; // two phases of biphase must not be same
			break;
		}
		if(input[i]=='+')
		{
			if(input[i-8]=='+') output+='0';
			else if(input[i-8]=='-') output+='1';
			else
			{
				check = 0; // the input string contains invalid characters
				break;
			}
		}
		else if(input[i]=='-')
		{
			if(input[i-8]=='-') output+='0';
			else if(input[i-8]=='+') output+='1';
			else
			{
				check = 0; // the input string contains invalid characters
				break;
			}
		}
	}
	cout << "Input:\n" << input << endl;
	cout << "Output after differential Manchester decoding:\n";
	if(check) cout << output << endl;
	else cout << "Input string cannot be decoded.\n";
	FILE* fp2 = freopen("output.txt","w",stdout); // storing output in file
	if(check) cout << output << endl;
	else cout << "Input string cannot be decoded.\n";
	fclose(fp1);
	fclose(fp2);
	exit(0);
}

void AMIEncoding()
{
	lastSignalSignChoice:
	cout << "Was the last non-zero signal positive? Enter Yes/No.\n";
	string signOfLastSignal;
	cin >> signOfLastSignal;

	if(signOfLastSignal!="Yes" and signOfLastSignal!="No")
	{
		cout << "Please enter choice correctly.\n";
		goto lastSignalSignChoice;
	}
	//first level depends on last non-zero level
	string input, output;
	FILE* fp1 = freopen("input.txt","r",stdin); //reading input from file
	getline(cin, input);
	output = "";
	int sz = input.size(), check = 1;
	
	int lastOnePositive = (signOfLastSignal[0]=='Y');
	for(int i = 0; i<sz; i++)
	{
		if(input[i]=='0')
		{
			output+="0V";
		}
		else if(input[i]=='1')
		{
			if(!lastOnePositive) output+="+5V";
			else output+="-5V";
			lastOnePositive^=1; //non-zero levels alternate
		}
		else
		{
			check = 0; // the input string contains invalid characters
			break;
		}
		if(i!=sz-1) output+=", ";
	}

	cout << "Input:\n" << input << endl;
	cout << "Output after AMI encoding:\n";
	if(check) cout << output << endl;
	else cout << "Input string cannot be encoded.\n";
	FILE* fp2 = freopen("output.txt","w",stdout); // storing output in file
	if(check) cout << output << endl;
	else cout << "Input string cannot be encoded.\n";
	fclose(fp1);
	fclose(fp2);
	exit(0);
}

void AMIDecoding()
{
	string input, output;
	FILE* fp1 = freopen("input.txt","r",stdin); //reading input from file
	getline(cin, input);
	output = "";
	int sz = input.size(), check = 1;
	char lastSign = '#';
	for(int i = 0; i<sz; )
	{
		if(input[i]=='0')
		{
			output+='0';
			i+=4;
		}
		else if(input[i]=='+' or input[i]=='-')
		{ 
			if(input[i]==lastSign)
			{
				check = 0; //two consecutive non-zero levels must not be same
				break;
			}
			else
			{
				lastSign = input[i];
			}
			output+='1';
			i+=5;
		}
		else
		{
			check = 0; // the input string contains invalid characters
			break;
		}
	}
	cout << "Input:\n" << input << endl;
	cout << "Output after AMI decoding:\n";
	if(check) cout << output << endl;
	else cout << "Input string cannot be decoded.\n";
	FILE* fp2 = freopen("output.txt","w",stdout); // storing output in file
	if(check) cout << output << endl;
	else cout << "Input string cannot be decoded.\n";
	fclose(fp1);
	fclose(fp2);
	exit(0);
}


int main()
{	
	int actionchoice, schemechoice;

	actionchoiceinput:
	cout << "Enter your choice of action:\n(1) Encoding\n(2) Decoding\n(0) Exit\n";
	cin >> actionchoice;
	switch(actionchoice)
	{
		case 1:
		{
			encodingschemechoiceinput:
			cout << "Enter your choice of scheme:\n(1) Manchester\n(2) Differential Manchester\n(3) AMI\n(0) Back\n";
			cin >> schemechoice;
			switch(schemechoice)
			{
				case 1:
				{
					ManchesterEncoding();
					break;
				}
				case 2:
				{
					DifferentialManchesterEncoding();
					break;
				}
				case 3:
				{
					AMIEncoding();
					break;
				}
				case 0:
				{
					goto actionchoiceinput;
				}
				default:
				{					
					cout << "Invalid choice. Try again.\n";
					goto encodingschemechoiceinput;			
				}
			}
		}
		case 2:
		{
			decodingschemechoiceinput:
			cout << "Enter your choice of scheme:\n(1) Manchester\n(2) Differential Manchester\n(3) AMI\n(0) Back\n";
			cin >> schemechoice;
			switch(schemechoice)
			{
				case 1:
				{
					ManchesterDecoding();
					break;
				}
				case 2:
				{
					DifferentialManchesterDecoding();
					break;
				}
				case 3:
				{
					AMIDecoding();
					break;
				}
				case 0:
				{
					goto actionchoiceinput;
				}
				default:
				{
					cout << "Invalid choice. Try again.\n";
					goto decodingschemechoiceinput;
				}
			}
		}
		case 0:
		{
			return 0;
		}
		default:
		{
			cout << "Invalid choice. Try again.\n";
			goto actionchoiceinput;
		}
	}
	return 0;
}