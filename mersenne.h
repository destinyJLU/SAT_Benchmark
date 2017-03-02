#ifndef MERSENNE_H_INCLUDED
#define MERSENNE_H_INCLUDED

class Mersenne {
  static const int N = 624; //？？？624？
  unsigned int mt[N];
  int mti;
public:
  Mersenne();             // 默认为种子为时间
  Mersenne(int seed);     // 带整数种子
  Mersenne(unsigned int *array, int count); // 种子为数组
  Mersenne(const Mersenne &copy);
  Mersenne &operator=(const Mersenne &copy);//操作符重载

  void seed(int s);
  void seed(unsigned int *array, int len);

  unsigned int next32();  // generates random integer in [0..2^32-1]
  int next31();           // generates random integer in [0..2^31-1]
  double nextClosed();    // generates random float in [0..1], 2^53 possible values 闭区间
  double nextHalfOpen();  // generates random float in [0..1), 2^53 possible values 半开半闭区间
  double nextOpen();      // generates random float in (0..1), 2^53 possible values 开区间
  int next(int bound);    // generates random integer in [0..bound), bound < 2^31
};


#endif // MERSENNE_H_INCLUDED
