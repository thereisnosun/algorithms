#include <string>

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
}