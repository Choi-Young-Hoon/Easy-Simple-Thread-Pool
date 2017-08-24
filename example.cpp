#include <unistd.h>

#include "ThreadPool.hpp"
using namespace clib;
#include <iostream>
using namespace std;

class MyThreadPoolTest : public ThreadPoolInterFace<int> {
public:
	MyThreadPoolTest():ThreadPoolInterFace<int>(){}
	MyThreadPoolTest(int a):ThreadPoolInterFace<int>(a){}
	~MyThreadPoolTest(){}

	void AddData(int data){
		ThreadPoolInterFace<int>::AddWork(data);
	}

	virtual void DoWork(int data){
		cout << data << " ";
		if(data % 20 == 0)
			cout << endl;
	}
};

int main(void){
	MyThreadPoolTest test_pool(10);

	cout << "Insert Start " << endl;
	for(int o = 0; o < 4; o++){
		cout << endl << "Round Start============================================@@@@@@" << endl;
		for(int i = 0; i < 100; i++){
			//cout << "Insert Data : " << i << endl;
			test_pool.AddData(i);
		}
		sleep(1);
	}
	
	sleep(1);
	cout << endl << "EXIT" << endl;
	return 0;
}
