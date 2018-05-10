#include <string>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
#include <map>
#include <set>
#include <vector>


namespace string
{
	bool checkIfPalindrome(const std::string& str)
	{
		size_t middleSize = str.size() / 2;
		for (size_t start = 0, end = str.size() - 1; start != middleSize && end != middleSize;
			++start, --end)
		{
			if (str.at(start) != str.at(end))
				return false;
		}
		return true;
	}

	bool ans(const std::string& a, const std::string& b, const std::string& c, int la, int lb, int lc) 
	{
		if (lc == c.length()) 
			return true;
		

		bool f = false;

		if (la<a.length() && a[la] == c[la + lb]) 
			f = f || ans(a, b, c, la + 1, lb, lc + 1);
		
		if (lb<b.length() && b[lb] == c[la + lb]) 
			f = f || ans(a, b, c, la, lb + 1, lc + 1);
		
		return f;
	}

	bool isInterleave(const std::string& A, const std::string& B, const std::string& C)
	{
		return ans(A, B, C, 0, 0, 0);
	}


	void getNumericAbreviationsWorker(const std::string& sample, int index,
		int max_index, std::string st)
	{
		if (index == max_index) 
		{
			std::cout << st << "\n";
			return;
		}

		st.push_back(sample[index]);
		getNumericAbreviationsWorker(sample, index + 1, max_index, st);
		st.pop_back();

		int count = 1;
		if (!st.empty()) 
		{
			if (isdigit(st.back())) 
			{
				count += (int)(st.back() - '0');
				st.pop_back();
			}
		}

		char to_print = (char)(count + '0');
		st.push_back(to_print);
		getNumericAbreviationsWorker(sample, index + 1, max_index, st);
	}

	// Wrapper function
	void getNumericAbreviations(const std::string& example)
	{
		if (example.empty())
			return;

		std::string st;
		getNumericAbreviationsWorker(example, 0, example.length(), st);
	}


	
}

namespace bits
{
	std::set<std::pair<int, int>> generatePairs(const std::vector<int>& inputNums)
	{

		std::set<std::pair<int, int>> pairs;
		std::set<int> explroredNums;

		for (size_t i = 0; i < inputNums.size(); ++i)
			for (size_t j = i + 1; j < inputNums.size(); ++j)
			{
				pairs.insert(std::make_pair(inputNums[i], inputNums[j]));
				pairs.insert(std::make_pair(inputNums[j], inputNums[i]));
			}
				

		return pairs;
	}


	int countOneBits(int number)
	{
		int counter = 0;
		while (number)
		{
			if (number % 2)
				++counter;
			number = number / 2;
		}
		return counter;
	}

	int diffBitSumsNaive(const std::vector<int>& inputNums)
	{
		if (inputNums.size() <= 1)
			return 0;

		std::set<std::pair<int, int>> pairs = generatePairs(inputNums);
		int totalSum = 0;
		for (const auto pair : pairs)
		{
			int xorRes = pair.first ^ pair.second;
			int currentBits = countOneBits(xorRes);
			totalSum += currentBits;
		}
		return totalSum;
	}


	int diffBitSumsLinear(const std::vector<int>& inputNums)
	{
		int ans = 0;

		for (int i = 0; i < 32; i++)
		{
			int count = 0;
			for (size_t j = 0; j < inputNums.size(); ++j)
				if ((inputNums[j] & (1 << i)))
					count++;

			ans += (count * (inputNums.size() - count) * 2);
		}

		return ans;
	}
}