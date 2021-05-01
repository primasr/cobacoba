// C++ program for Shannon Fano Algorithm

// include header files
#include <bits/stdc++.h>
using namespace std;

// declare structure node
struct node {

	// for storing symbol
	string sym;

	// for storing probability or frquency
	float pro;
	int arr[20];
	int top;
} p[20];

typedef struct node node;

// function to find shannon code
void shannon(int l, int h, node p[])
{
	float pack1 = 0, pack2 = 0, diff1 = 0, diff2 = 0;
	int i, d, k, j;
	if ((l + 1) == h || l == h || l > h) {
		if (l == h || l > h)
			return;
		p[h].arr[++(p[h].top)] = 0;
		p[l].arr[++(p[l].top)] = 1;
		return;
	}
	else {
		for (i = l; i <= h - 1; i++)
			pack1 = pack1 + p[i].pro;
		pack2 = pack2 + p[h].pro;
		diff1 = pack1 - pack2;
		if (diff1 < 0)
			diff1 = diff1 * -1;
		j = 2;
		while (j != h - l + 1) {
			k = h - j;
			pack1 = pack2 = 0;
			for (i = l; i <= k; i++)
				pack1 = pack1 + p[i].pro;
			for (i = h; i > k; i--)
				pack2 = pack2 + p[i].pro;
			diff2 = pack1 - pack2;
			if (diff2 < 0)
				diff2 = diff2 * -1;
			if (diff2 >= diff1)
				break;
			diff1 = diff2;
			j++;
		}
		k++;
		for (i = l; i <= k; i++)
			p[i].arr[++(p[i].top)] = 1;
		for (i = k + 1; i <= h; i++)
			p[i].arr[++(p[i].top)] = 0;

		// Invoke shannon function
		shannon(l, k, p);
		shannon(k + 1, h, p);
	}
}

// Function to sort the symbols
// based on their probability or frequency
void sortByProbability(int n, node p[])
{
	int i, j;
	node temp;
	for (j = 1; j <= n - 1; j++) {
		for (i = 0; i < n - 1; i++) {
			if ((p[i].pro) > (p[i + 1].pro)) {
				temp.pro = p[i].pro;
				temp.sym = p[i].sym;

				p[i].pro = p[i + 1].pro;
				p[i].sym = p[i + 1].sym;

				p[i + 1].pro = temp.pro;
				p[i + 1].sym = temp.sym;
			}
		}
	}
}

// function to display shannon codes
void display(int n, node p[])
{
	int i, j;
	float total = 0;
	cout << "\n\n\n\tSymbol\tProbability\tLog2(1/Prob)\tProb*Log2(1/Prob)\tCode";
	for (i = n - 1; i >= 0; i--) {
        float prob = 1 / p[i].pro;
        float entropy = log2(prob);
        float probXentropy = p[i].pro*entropy;
        total += probXentropy;
//		cout << "\n\t" << p[i].sym << "\t" << setprecision(6) << p[i].pro << "\t";
        cout << "\n\t" << p[i].sym << "\t";
		printf("%0.6f\t",p[i].pro);

        printf("%0.6f\t",entropy);
		printf("%0.6f\t\t",probXentropy);

        for (j = 0; j <= p[i].top; j++)
        cout << p[i].arr[j];
	}

	int hmm = 8;
	printf("\n\n\tBefore Compression: %d bits/symbol\n", hmm);
	printf("\tAfter  Compression: %0.6f bits/symbol\n", total);
	printf("\tCompression ratio : %0.6f\n\n\n", 8/total);
}

// Driver code
int main()
{
	int n, i, j;
	float total = 0;
	string ch;
	node temp;
	float x[100];
	map<char , int >m;
	map<char , int >::iterator itr;

	cout << "Masukkan pesan: ";
//	cin >> ch;
    getline(cin,ch);
	n = ch.length();

    for(int i=0;i<n;i++){
        m[ch[i]]++;
//        p[i].sym += ch[i];
    }

    j = 0;
    for(itr=m.begin();itr!=m.end();itr++){
        p[j].sym += itr->first;
        float temp_float = (float)itr->second;
        x[j] = temp_float / n;
		p[j].pro = x[j];
		total = total + p[j].pro;
        j++;
    }

	p[j].pro = 1 - total;

	// Sorting the symbols based on
	// their probability or frequency
	sortByProbability(j, p);

	for (i = 0; i < j; i++)
		p[i].top = -1;

	// Find the shannon code
	shannon(0, j - 1, p);

	// Display the codes
	display(j, p);
	return 0;
}
