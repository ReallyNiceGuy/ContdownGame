#include <array>
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <optional>
#include <set>
#include <bit>

bool next_combination(std::array<int,5>& indexes, int count)
{
	++indexes[4];
	if (indexes[4]>count-1)
	{
		++indexes[3];
		indexes[4] = indexes[3]+1;
		if (indexes[3]>count-2)
		{
			++indexes[2];
			indexes[3] = indexes[2]+1;
			indexes[4] = indexes[3]+1;
			if (indexes[3]>count-3)
			{
				++indexes[1];
				indexes[2] = indexes[1]+1;
				indexes[3] = indexes[2]+1;
				indexes[4] = indexes[3]+1;
				if (indexes[1]>count-4)
				{
					++indexes[0];
					indexes[1] = indexes[0]+1;
					indexes[2] = indexes[1]+1;
					indexes[3] = indexes[2]+1;
					indexes[4] = indexes[3]+1;
					if (indexes[0]>count-5)
						return false;
				}
			}
		}	
	}
	return true;
}

bool next_combination(std::array<int,4>& indexes, int count)
{
	++indexes[3];
	if (indexes[3]>count-1)
	{
		++indexes[2];
		indexes[3] = indexes[2]+1;
		if (indexes[2]>count-2)
		{
			++indexes[1];
			indexes[2] = indexes[1]+1;
			indexes[3] = indexes[2]+1;
			if (indexes[1]>count-3)
			{
				++indexes[0];
				indexes[1] = indexes[0]+1;
				indexes[2] = indexes[1]+1;
				indexes[3] = indexes[2]+1;
				if (indexes[0]>count-4)
					return false;
			}
		}	
	}
	return true;
}

bool next_combination(std::array<int,3>& indexes, int count)
{
	++indexes[2];
	if (indexes[2]>count-1)
	{
		++indexes[1];
		indexes[2] = indexes[1]+1;
		if (indexes[1]>count-2)
		{
			++indexes[0];
			indexes[1] = indexes[0]+1;
			indexes[2] = indexes[1]+1;
			if (indexes[0]>count-3)
				return false;
		}
	}	

	return true;
}

bool next_combination(std::array<int,2>& indexes, int count)
{
	++indexes[1];
	if (indexes[1]>count-1)
	{
		++indexes[0];
		indexes[1] = indexes[0]+1;
		if (indexes[0]>count-2)
			return false;
	}

	return true;
}

inline int get_operation(int variation, int index)
{
	return ((variation >> ((index-1)*2)) & 3);
}

std::set<std::array<int,6>> cache;

struct COUNTER
{
	std::array<char,1000> n{};
	int count{};
};

inline void set_number(COUNTER &c, int number)
{
	if (c.n[number]) return;
	c.n[number]=1;
	++c.count;
}

void check_targets(std::array<int,6>& numbers)
{
	COUNTER targets;
	std::sort(numbers.begin(),numbers.end());
	if (cache.contains(numbers)) return;
	cache.insert(numbers);
	std::cout << numbers[0] << ", "
			  << numbers[1] << ", "
			  << numbers[2] << ", "
			  << numbers[3] << ", "
			  << numbers[4] << ", "
			  << numbers[5] << ", ";
	do {
		for(int oper_index = 0; oper_index < 1024; ++oper_index)
		{
			int result = numbers[0];
			if (result == 100)
					set_number(targets, result);
			for(int partial=1; partial<6; ++partial)
			{
				switch(get_operation(oper_index, partial))
				{
					case 0:
						result=result + numbers[partial];
						break;
					case 1:
						result=result - numbers[partial];
						if (result<0) goto exit_loop;
						break;
					case 2:
						result=result * numbers[partial];
						break;
					case 3:
						if (result<numbers[partial]) goto exit_loop;
						auto res = std::div(result,numbers[partial]);
						if (res.rem) goto exit_loop;
						result = res.quot;
						break;
				}
				if (result>99 && result<1000)
					set_number(targets, result);
			}
			exit_loop:
				continue;
		}

	} while (std::next_permutation(numbers.begin(), numbers.end()));
	std::cout << targets.count << std::endl;
}

int main(int, char**)
{
	std::array<int,20> small{1,1,2,2,3,3,4,4,5,5,6,6,7,7,8,8,9,9,10,10};
	std::array<int,4> big{25,50,75,100};
	std::array<int,6> numbers{};

	for (int big_count=1; big_count<5;++big_count)
	{
		switch (big_count)
		{
			case 1:
				{
					for (int big_idx=0; big_idx<4; ++big_idx)
					{
						std::array<int,5> small_idx{0,1,2,3,4};
						do {
							numbers[0] = big[big_idx];
							numbers[1] = small[small_idx[0]];
							numbers[2] = small[small_idx[1]];
							numbers[3] = small[small_idx[2]];
							numbers[4] = small[small_idx[3]];
							numbers[5] = small[small_idx[4]];
							check_targets(numbers);
						} while (next_combination(small_idx,small.size()));
					}
				}
				break;
			case 2:
				{
					std::array<int,2> big_idx{0,1};
					do
					{
						std::array<int,4> small_idx{0,1,2,3};
						do {
							numbers[0] = big[big_idx[0]];
							numbers[1] = big[big_idx[1]];
							numbers[2] = small[small_idx[0]];
							numbers[3] = small[small_idx[1]];
							numbers[4] = small[small_idx[2]];
							numbers[5] = small[small_idx[3]];
							check_targets(numbers);
						} while (next_combination(small_idx,small.size()));
					} while (next_combination(big_idx, big.size()));
				}
				break;
			case 3:
				{
					std::array<int,3> big_idx{0,1,2};
					do
					{
						std::array<int,3> small_idx{0,1,2};
						do {
							numbers[0] = big[big_idx[0]];
							numbers[1] = big[big_idx[1]];
							numbers[2] = big[big_idx[2]];
							numbers[3] = small[small_idx[0]];
							numbers[4] = small[small_idx[1]];
							numbers[5] = small[small_idx[2]];
							check_targets(numbers);
						} while (next_combination(small_idx,small.size()));
					} while (next_combination(big_idx, big.size()));
				}
				break;
			case 4:
				{
					std::array<int,2> small_idx{0,1};
					{
						do {
							numbers[0] = big[0];
							numbers[1] = big[1];
							numbers[2] = big[2];
							numbers[3] = big[3];
							numbers[4] = small[small_idx[0]];
							numbers[5] = small[small_idx[1]];
							check_targets(numbers);
						} while (next_combination(small_idx,small.size()));
					}
				}				
				break;
		}
	}
}
