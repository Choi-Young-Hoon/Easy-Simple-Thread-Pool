#ifndef __LIB_THREADPOOL_HEADER__
#define __LIB_THREADPOOL_HEADER__
#include <pthread.h>

#include <iostream>
#include <functional>
#include <thread>
#include <vector>
using namespace std;

#include "linklistpool.hpp"
#include "Sync.hpp"

namespace clib{
	template <typename ARG>
	class ThreadPoolInterFace {
	public:
		static const int default_thread_count = 5;
	public:
		ThreadPoolInterFace(){
			Init(default_thread_count);
		}
		ThreadPoolInterFace(const int thread_count){
			Init(thread_count);
		}
		~ThreadPoolInterFace(){
			Destroy();
		}

		

		void AddThread(){
			thread_list.push_back(thread([=](){ 
							//Thread 종료 요청이오면 바로 종료하도록.
							pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
							pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
							this->RunThread(); 
						}));
		}

		void RunThread(){
			ARG task_data;
			bool work_switch = false;
			while(true){
				work_switch = false;
				// Cond Signal 을 대기.
				thread_sync.Lock();
				while(task_queue.GetDataCount() == 0){
					thread_sync.Wait();
				}
					
				task_sync.Lock();
				if(task_queue.GetDataCount() != 0){
					task_data = task_queue.GetFrontData();
					task_queue.DelFrontData();
					work_switch = true;
				}
				task_sync.Unlock();
				
				thread_sync.Unlock();
				
				if(work_switch)
					DoWork(task_data);
			}
		}
		
		inline void AddWork(ARG task_data){
			task_sync.Lock();
			task_queue.AddData(task_data);	
			task_sync.Unlock();
			
			thread_sync.Signal();
		}

		inline void GetThreadCount(){
			return thread_list.size();
		}

		virtual void DoWork(ARG data) = 0;
	
	protected:
		void Init(const int thread_count){
			task_sync.Init();
			thread_sync.Init();
			task_queue.InitNodePool();

			for(int i = 0; i < thread_count; i++)
				AddThread();
		}

		void Destroy(){
			for(unsigned int i = 0; i < thread_list.size(); i++){
				pthread_cancel(thread_list[i].native_handle());
				thread_sync.Unlock();
				thread_list[i].join();
			}		

			thread_sync.Destroy();
			task_sync.Destroy();
			task_queue.Clear();

			
		}

	private:
		vector<thread> thread_list;
		Sync thread_sync;

		LinkListPool<ARG> task_queue;
		Sync task_sync;
	};
};
#endif
