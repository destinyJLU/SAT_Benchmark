#ifndef MERSENNE_H_INCLUDED
#define MERSENNE_H_INCLUDED

class Mersenne {
  static const int N = 624; //������624��
  unsigned int mt[N];
  int mti;
public:
  Mersenne();             // Ĭ��Ϊ����Ϊʱ��
  Mersenne(int seed);     // ����������
  Mersenne(unsigned int *array, int count); // ����Ϊ����
  Mersenne(const Mersenne &copy);
  Mersenne &operator=(const Mersenne &copy);//����������

  void seed(int s);
  void seed(unsigned int *array, int len);

  unsigned int next32();  // generates random integer in [0..2^32-1]
  int next31();           // generates random integer in [0..2^31-1]
  double nextClosed();    // generates random float in [0..1], 2^53 possible values ������
  double nextHalfOpen();  // generates random float in [0..1), 2^53 possible values �뿪�������
  double nextOpen();      // generates random float in (0..1), 2^53 possible values ������
  int next(int bound);    // generates random integer in [0..bound), bound < 2^31
};


#endif // MERSENNE_H_INCLUDED
