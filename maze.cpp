#include <iostream>
#include <stdio.h>
#include <conio.h>
using namespace std;

class cnode
{
public:
	char **x;
	cnode *pnext;
	int HR;
	int HC;
};

class cstack
{

public:

	cnode*phead;

public:

	cstack()
	{
		phead = NULL;
	}
	~cstack()
	{
		cnode*ptrav;
		while (phead != NULL)
		{
			ptrav = phead;
			phead = phead->pnext;
			delete ptrav;
		}
	}

	void push(cnode*pnn)
	{
		pnn->pnext = phead;
		phead = pnn;
	}

	cnode *pop()
	{
		if (phead == NULL)

		{
			return NULL;
		}

		else

		{
			cnode*ptrav = phead;
			phead = ptrav->pnext;
			ptrav->pnext = NULL;
			return ptrav;
		}
	}
	cnode *createfirstnode(int n,int m)
	{
		cnode *pnn;
		pnn = new cnode[1];
		pnn->x = new char *[n];
		for (int i = 0; i < n; i++)
		{
			pnn->x[i] = new char[m];
		}
		for (int i = 0; i < n; i++)
		{
			for (int k = 0; k < m; k++)
			{
				pnn->x[i][k] = '_';
			}
		}
		pnn->pnext = NULL;
		pnn->HR = 0;
		pnn->HC = 0;
		return pnn;
	}
};

void display(cnode *pnn,int n,int m)
{

	for (int i = 0; i < n; i++)
	{
		for (int k = 0; k < m; k++)
		{
			cout << pnn->x[i][k] << "|";
		}
		cout <<i+1<< endl;
	}

}

void obstacles_apple_position(cnode *pnn,int n,int m)
{
	int q,z,y,k,l;
	k = 0;
	l = 0;
	cout << "please enter the number of obstacles you want to enter" << endl;
	cin >> q;
	for (int i = 0; i < q; i++)
	{
		cout << "please enter the obstacle position between "<<n<<" rows and "<<m<<" coloumns" << endl;
		while (k != 1)
		{
			cin >> z;
			if (z>n || z == n)
			{
				cout << "please enter a valid row number" << endl;
			}
			else
			{
				k = 1;
			}
		}
		k = 0;
		while (k != 1)
		{
			cin >> y;
			if (y > m || y == m)
			{
				cout << "please enter a valid column number" << endl;
			}
			else
			{
				k = 1;
			}
		}
		k = 0;
		pnn->x[z][y] = '#';
	}
	cout << "please enter the position of the apple between " << n << " rows and " << m << " coloumns" << endl;
	while (l != 1)
	{
		while (k != 1)
		{
			cin >> z;
			if (z > n || z == n)
			{
				cout << "please enter a valid row number" << endl;
			}
			else
			{
				k = 1;
			}
		}
		k = 0;
		while (k != 1)
		{
			cin >> y;
			if (y > m || y == m)
			{
				cout << "please enter a valid column number" << endl;
			}
			else
			{
				k = 1;
			}
		}
		k = 0;
		if (pnn->x[z][y] != '#')
		{
			pnn->x[z][y] = '@';
			l = 1;
		}
		else
		{
			cout << "please enter a valid position there is an obstacle here" << endl;
		}
	}
	l = 0;
	cout << "please enter the position of the snake between " << n << " rows and " << m << " coloumns" << endl;
	while (l != 1)
	{
		while (k != 1)
		{
			cin >> pnn->HR;
			if (pnn->HR> n || pnn->HR == n)
			{
				cout << "please enter a valid row number" << endl;
			}
			else
			{
				k = 1;
			}
		}
		k = 0;
		while (k != 1)
		{
			cin >> pnn->HC;
			if (pnn->HC > m || pnn->HC == m)
			{
				cout << "please enter a valid column number" << endl;
			}
			else
			{
				k = 1;
			}
		}
		k = 0;
		if (pnn->x[pnn->HR][pnn->HC]=='_')
		{
			pnn->x[pnn->HR][pnn->HC] = 'H';
			l = 1;
		}
		else
		{
			cout << "please enter a valid position there is something in the selected cell" << endl;
		}
	}
	l = 0;
}

void expandchild(cnode *pparent, cstack &s, int &ct,int n,int m)
{
	cnode *pnn;
	int f = 0;
	int f2 = 0;
	int f3 = 0;
	for (int i = 0; i < 4; i++)
	{
		//copying and making new child
		pnn = new cnode[1];
		pnn->pnext = NULL;
		pnn->x = new char*[n];
		for (int k = 0; k < n; k++)
		{
			pnn->x[k] = new char[m];
		}
		for (int r = 0; r < n; r++)
		{
			for (int c = 0; c < m; c++)
			{
				pnn->x[r][c] = pparent->x[r][c];
			}
		}

		pnn->x[pparent->HR][pparent->HC] = '*';
		if (		i == 0 
				&&	pparent->HR + 1 < n 
				&&	pnn->x[pparent->HR + 1][pparent->HC] != '#'
				&&	pnn->x[pparent->HR+1][pparent->HC] != '*')
		{
			if (pnn->x[pparent->HR + 1][pparent->HC] == '@')
			{
				f2 = 1;
			}
			pnn->HR = pparent->HR + 1;
			pnn->HC = pparent->HC;
			pnn->x[pnn->HR][pnn->HC] = 'H';
		}
		else if (i==0)
		{
			f = 1;
		}

		if (	i == 1 
			&& pparent->HR - 1 >= 0 
			&& pnn->x[pparent->HR - 1][pparent->HC] != '#'
			&&	pnn->x[pparent->HR-1][pparent->HC] != '*')
		{
			if (pnn->x[pparent->HR - 1][pparent->HC] == '@')
			{
				f2 = 1;
			}
			pnn->HR = pparent->HR - 1;
			pnn->HC = pparent->HC;
			pnn->x[pnn->HR][pnn->HC] = 'H';
		}
		else if (i == 1)
		{
			f = 1;
		}
		if (	i == 2 
			&&	pparent->HC + 1 < m 
			&&	pnn->x[pparent->HR][pparent->HC + 1] != '#'
			&&	pnn->x[pparent->HR][pparent->HC+1] != '*')
		{
			if (pnn->x[pparent->HR][pparent->HC+1] == '@')
			{
				f2 = 1;
			}
			pnn->HC = pparent->HC + 1;
			pnn->HR = pparent->HR;
			pnn->x[pnn->HR][pnn->HC] = 'H';
		}
		else if (i == 2)
		{
			f = 1;
		}
		if (	i == 3 
			&&  pparent->HC - 1 >= 0 
			&&	pnn->x[pparent->HR][pparent->HC - 1] != '#'
			&&	pnn->x[pparent->HR][pparent->HC-1] != '*')
		{
			if (pnn->x[pparent->HR][pparent->HC-1] == '@')
			{
				f2 = 1;
			}
			pnn->HC = pparent->HC - 1;
			pnn->HR = pparent->HR;
			pnn->x[pnn->HR][pnn->HC] = 'H';
		}
		else if (i == 3)
		{
			f = 1;
		}
		//End of copying and making new child
		if (f2==1)
		{
			ct++;
			cout << "mabrouk the answer number "<<ct <<"is"<< endl;
			display(pnn,n,m);
		}
		if (f == 0&&f2==0)
		{
			s.push(pnn);
		}
		/*display(pnn);
		char zz;
		cin >> zz;//getch();*/
		f = 0;
		f2 = 0;
	}
}

void bk()
{
	cstack s;
	cnode *pnn,*pparent,*ptrav;
	int ct = 0;
	int n,m;
	cout << "please enter the size of rows of the maze" << endl;
	cin >> n;
	cout << "please enter the size of columns of the maze" << endl;
	cin >> m;
	pnn = s.createfirstnode(n,m);
	s.push(pnn);
	obstacles_apple_position(pnn,n,m);
	display(pnn,n,m);
	cout << endl;
	while (s.phead != NULL)
	{
		pparent = s.pop();
		expandchild(pparent, s,ct,n,m);
	}
}

void main()
{
	bk();
}