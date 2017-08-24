#ifndef __LIB_THREAD_SYNC_HEADER__
#define __LIB_THREAD_SYNC_HEADER__
#include <pthread.h>
namespace clib{
	class Sync{
	public:
		Sync(){}
		~Sync(){}

		void Init(){
			pthread_mutex_init(&mutex, NULL);
			pthread_cond_init(&cond, NULL);
		}

		inline void Destroy(){
			pthread_mutex_destroy(&mutex);
			pthread_cond_destroy(&cond);
		}

		// @TODO 주의 Wait() 과 Lock() 은 따로 사용되어야함.
		// 하나의 선언된 객체에서 두가지를 동시에 사용할 경우 문제가 됨.
		inline void Wait(){
			pthread_cond_wait(&cond, &mutex);
		}
		inline void Lock(){
			pthread_mutex_lock(&mutex);
		}
		////////////////////////////////////////

		inline void Unlock(){
			pthread_mutex_unlock(&mutex);
		}

		inline void Signal(){
			pthread_cond_signal(&cond);
		}
	private:
		pthread_mutex_t mutex;
		pthread_cond_t cond;
	};
};
#endif
