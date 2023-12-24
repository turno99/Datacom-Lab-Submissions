#include <bits/stdc++.h>
using namespace std;

vector<int> generateCode(vector<int> inputMsg, int m, int r)
{
    // size of code will be the
    // sum of message bits and
    // redundant bits
	int n = m + r;
	//container for the code
	//to be generated
	vector<int> hammingCode(n);

    //marking the positions of
    //parity bits with -1
	for (int i = 0; i < r; i++)
	{
		hammingCode[(1<<i) - 1] = -1;
	}

	int j = 0;

    // placing message bits
	for (int i = 0; i < n; i++)
	{
		if (hammingCode[i] != -1)
		{
			hammingCode[i] = inputMsg[j];
			j++;
		}
	}
    // placing parity bits
	for (int i = 0; i < n; i++)
	{
		// If current bit is not redundant
		// bit then continue
		if (hammingCode[i] != -1)
			continue;

		int x = log2(i + 1);
		int ones = 0;

		// Find msg bits containing
		// set bit at x'th position
		for (int j = i + 2;j <= n; ++j)
		{

			if (j & (1 << x))
			{
				if (hammingCode[j - 1] == 1)
				{
					ones++;
				}
			}
		}

		// Generating hamming code for
		// even parity
		hammingCode[i] = ones%2;
	}

	// Return the generated code
	return hammingCode;
}

// Function to find the hamming code
// of the given message bit msgBit[]
void findAndPrintCode(vector<int> &msgBit)
{
	// length of input message
	int m = msgBit.size();

	// r is the number of redundant bits
	int r = 1;

	// Find the number of redundant bits
	while ((1<<r) < (m + r + 1))
	{
		r++;
	}

	// Generating the code
	vector<int> ans = generateCode(msgBit, m, r);

	// Print the code
	cout << "Message: ";
	for (int i = 0; i < msgBit.size(); i++)
		cout << msgBit[i] << " ";

	cout << "\nHamming code: ";

	for (int i = 0; i < ans.size(); i++)
		cout << ans[i] << " ";
	cout << endl;
}

int main()
{
	vector<int> msgBit;
	int n;
	cout<<"Enter the number of bits:\n";
	cin >> n;

	//taking bitstream as input
	cout << "Enter the bits:\n";
	for (int i = 0; i < n; i++)
	{
		int temp;
		cin >> temp;
		if(temp!=1 and temp!=0) // not a valid bit
        {
            continue;
        }
        msgBit.push_back(temp);
	}

	findAndPrintCode(msgBit);

	return 0;
}
