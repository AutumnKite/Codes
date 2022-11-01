#ifndef NTH_H
#define NTH_H
#include <bitset>
void report(unsigned);
constexpr int M(1<<21);
namespace Alice
{
	void initA(std::bitset<M>,unsigned,unsigned);
	void receiveA(bool);
	void sendA(bool);
}
namespace Bob
{
	void initB(std::bitset<M>,unsigned,unsigned);
	void receiveB(bool);
	void sendB(bool);
}
#endif
