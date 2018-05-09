#include <string>
#include <algorithm>
#include <unordered_set>
#include <set>

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

	/*bool isInterlived(const std::string& str1, const std::string& str2, const std::string& testStr)
	{
		std::unordered_set<char> uniqueSymblols;

		std::string totalStr = str1 + str2;
		for (size_t i = 0; i < testStr.size(); ++i)
		{
			std::string
			uniqueSymblols.insert(testStr[i]);

		}
	}*/

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
}