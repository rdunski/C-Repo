#include <iostream>
#include <queue>
#include <chrono>

using namespace std;

int main()
{
	queue<int> queue;
	long long n;
	while (cin >> n)
	{
		long long pair = 0;
		long long check = 1;
		long long d = 2;
		long long ops = 0;
		chrono::system_clock::time_point start = chrono::system_clock::now();
		while (d*d <= n)
		{
			if (n % d == 0)
			{
				check = check + d;
				if (d*d != n)
				{
					check = check + (n / d);
				}
				ops = ops + 4;
			}
			++d;
			ops = ops + 3;
		}
		chrono::system_clock::time_point end = chrono::system_clock::now();
		auto total = chrono::duration_cast<chrono::milliseconds>(end - start);
		if (check == n)
		{
			cout << n << " perfect" << endl;
			ops = ops + 1;
		}
		else if (check <= (n + 2) && check >= (n - 2))
		{
			cout << n << " almost perfect" << endl;
			ops = ops + 5;
		}
		else
		{
			cout << n << " not perfect" << endl;
			ops = ops + 5;
		}

		cout << "function took " << total.count() << " milliseconds and " << ops << " operations" << endl;
	}
	return 0;
}
