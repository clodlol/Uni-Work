#include <iostream>
using namespace std;

class CustomDeque
{
private:
	int *arr;
	int capacity;
	int front;
	int rear;
	int count;

public:
	CustomDeque(int cap)
	{
		capacity = cap;
		arr = new int[capacity];
		front = 0;
		rear = -1;
		count = 0;
	}
	~CustomDeque()
	{
		delete[] arr;
	}
	bool isEmpty() { return count == 0; }
	bool isFull() { return count == capacity; }
	void push_back(int val)
	{
		if (isFull())
			return;
		rear = (rear + 1) % capacity;
		arr[rear] = val;
		count++;
	}
	void pop_back()
	{
		if (isEmpty())
			return;

		if (rear == 0)
		{
			rear = capacity - 1;
			count--;
			return;
		}

		rear--;
		count--;
	}
	void pop_front()
	{
		if (isEmpty())
			return;

		front = (front + 1) % capacity;
		count--;
	}
	int peek_front()
	{
		if (isEmpty())
			return -1;

		return arr[front];
	}
	int peek_back()
	{
		if (isEmpty())
			return -1;

		return arr[rear];
	}
};

class Solution
{
public:
	int shortestSubarray(int nums[], int n, long long k)
	{
		long long *prefixSums = new long long[n];

		for (int i = 0; i < n; ++i)
		{
			prefixSums[i] = i > 0 ? prefixSums[i - 1] + nums[i] : nums[i];
		}

		CustomDeque dq(n);
		int ans = INT_MAX;

		for (int i = 0; i < n; ++i)
		{
			if (prefixSums[i] >= k)
				ans = min(ans, i + 1);
			while (!dq.isEmpty() && prefixSums[i] - prefixSums[dq.peek_front()] >= k)
			{
				ans = min(ans, i - dq.peek_front());
				dq.pop_front();
			}

			while (!dq.isEmpty() && prefixSums[i] <= prefixSums[dq.peek_back()])
			{
				dq.pop_back();
			}

			dq.push_back(i);
		}

		delete[] prefixSums;
		return ans == INT_MAX ? -1 : ans;
	}
};

int main()
{
	Solution solution;
	int nums1[] = {2, -1, 2};
	int n1 = 3;
	long long k1 = 3;
	cout << " Test Case 1 Output : " << solution.shortestSubarray(nums1, n1, k1)
		 << " ( Expected : 3)" << endl;
	int nums2[] = {84, -37, 32, 40, 95};
	int n2 = 5;
	long long k2 = 167;
	cout << " Test Case 2 Output : " << solution.shortestSubarray(nums2, n2, k2)
		 << " ( Expected : 3)" << endl;
	return 0;
}