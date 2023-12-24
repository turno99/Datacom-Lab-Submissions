#include <bits/stdc++.h>
using namespace std;
string input;
//For bitstream, enter input as 0101110100...
//For voltage sequence, enter input ase +5V, -5V, +5V.... (consecutive voltages are separated by a single comma.)
int main()
{
    int option;
    optioninput:
    cout << "Enter choice. 1 for encoding or 2 for decoding:";
    cin >> option;
    if(option!=1 and option!=2)
    {
        cout << "Invalid choice. Try again.\n";
        goto optioninput;
    }
    if(option==1)
    {
        int encodingchoice;
        encodingoptioninput:
        cout << "Enter choice. 1 for NRZ-L encoding or 2 for NRZ-I encoding:";
        cin >> encodingchoice;
        if(encodingchoice!=1 and encodingchoice!=2)
        {
            cout << "Invalid choice. Try again.\n";
            goto encodingoptioninput;
        }
        freopen("encoder_input.txt","r",stdin);
        freopen("encoder_output.txt","w",stdout);
        cin >> input;
        int n = input.size();
        int c1 = count(input.begin(),input.end(),'1');
        int c0 = count(input.begin(),input.end(),'0');
        if(c1+c0!=n)
        {
            cout << "Input string cannot be encoded.\n";
            return 0;
        }
        string output = "";
        if(encodingchoice==1) //NRZ-L encoding
        {
            for(int i = 0; i<n; i++)
            {
                if(i) output+=",";
                if(input[i]=='0')
                {
                    output+="+5V";
                }
                else
                {
                    output+="-5V";
                }
            }
            cout << output << endl;
        }
        else //NRZ-I encoding
        {
            for(int i = 0; i<n; i++)
            {
                if(!i)
                {
                    if(input[i]=='1')
                    {
                        output.push_back(-5);
                    }
                    else
                    {
                        output.push_back(5);
                    }
                }
                else
                {
                    if(input[i]=='1')
                    {
                        output.push_back(-output[i-1]);
                    }
                    else
                    {
                        output.push_back(output[i-1]);
                    }
                }
            }
            string outputstr;
            for(int i = 0; i<n; i++)
            {
                if(i) outputstr+=",";
                if(output[i]==5)
                {
                    outputstr+="+5V";
                }
                else
                {
                    outputstr+="-5V";
                }
            }
            cout << outputstr << endl;
        }
    }
    else
    {
        int decodingchoice;
        decodingoptioninput:
        cout << "Enter choice. 1 for NRZ-L decoding or 2 for NRZ-I decoding:";
        cin >> decodingchoice;
        if(decodingchoice!=1 and decodingchoice!=2)
        {
            cout << "Invalid choice. Try again.\n";
            goto decodingoptioninput;
        }
        freopen("decoder_input.txt","r",stdin);
        freopen("decoder_output.txt","w",stdout);
        cin>>input;
        int n = input.size();
        bool ok = 1;
        string output = "";
        if(decodingchoice==1) // NRZ-L decoding
        {
            for(int i=0;i<n;)
            {
                    if(input[i]!='+' and input[i]!='-')
                    {
                        ok = 0;
                        break;
                    }
                if(input[i]=='+')
                {
                    output+="0";
                    i+=4;
                }
                else if(input[i]=='-')
                {
                    output+="1";
                    i+=4;
                }
                else
                {
                    ok = 0;
                    break;
                }
            }
            if(!ok)
            {
                cout << "Input string cannot be decoded.\n";
                return 0;
            }
            else
            {
                cout << output << endl;
            }
        }
        else //NRZ-I decoding
        {
            string output;
            for(int i = 0; i<n;)
            {
                if(!i)
                {
                    if(input[i]=='+') output.push_back('0');
                    else if(input[i]=='-') output.push_back('1');
                    else
                    {
                        ok = 0;
                        break;
                    }
                    i+=4;
                }
                else
                {
                    if(input[i]!='+' and input[i]!='-')
                    {
                        ok = 0;
                        break;
                    }
                    if(input[i]==input[i-4]) output.push_back('0');
                    else output.push_back('1');
                    i+=4;
                }
            }
            if(!ok)
            {
                cout << "Input string cannot be decoded.\n";
                return 0;
            }
            else
            {
                cout << output << endl;
            }
        }
    }
}
