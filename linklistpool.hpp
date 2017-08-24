#ifndef __LIB_INCLUDE_LINKLISTPOOL_HEADER__
#define __LIB_INCLUDE_LINKLISTPOOL_HEADER__
#include "node.hpp"
namespace clib {
	template<typename NODE_DATA_TYPE>
	class LinkListPool {
	public:
		LinkListPool()
			:node_maximum(default_node_poll_count) {}
		LinkListPool(const int node_maximum)
			:node_maximum(node_maximum) {}
		~LinkListPool() {}

		/*
		 * 원형 연결리스트를 구성한다.
		 * @return
		 * 성공시 true
		 * 실패시 false
		 */
		bool InitNodePool() {
			Oneway::Node<NODE_DATA_TYPE> * head_node = Oneway::Node<NODE_DATA_TYPE>::CreateNode();
			if (head_node == NULL) //Failed
				return false;
			node_count = 1;
			//원형 연결리스트 생성.
			Oneway::Node<NODE_DATA_TYPE> * node = head_node;
			for (int i = node_count; i < node_maximum; i++) {
				node->next = Oneway::Node<NODE_DATA_TYPE>::CreateNode();
				node = node->next;
				node_count++;
			}
			//노드 연결
			node->next = head_node;
			start = end = head_node;
			
			data_count = 0;
			return true;
		}

		/*
		 * 데이터를 추가한다.
		 * @param
		 * data - 추가할 데이터.
		 * @return
		 * 성공시 data_count(현재 데이터의 개수)를 반환하고 
		 * 실패시 -1을 반환
		 */
		int AddData(const NODE_DATA_TYPE & data) {
			if (data_count >= node_maximum)  //현재 Pool이 포화상태면.
				return AddNode(data);

			if (data_count > 0) { // 데이터가 있다면.
				end = end->next;
				end->SetData(data);
			} else {			  // 데이터가 없다면.
				start->SetData(data);
				end = start;
			}
			data_count++;
			return data_count;
		}

		

		// 첫 데이터를 가져온다.
		inline NODE_DATA_TYPE GetFrontData() {
			//@TODO 넣은 값이 없어도 반환은한다.....
			return start->GetData();
		}
		
		/*
		 * 앞의 데이터를 제거한다.
		 * 노드 최고치보다 많은 노드가 존재하면 노드 하나를 제거한다.
		 */
		void DelFrontData() {
			if (node_count > node_maximum) { //노드가 maximum 값보다 많으면
				Oneway::Node<NODE_DATA_TYPE> * temp_node = start;
				delete temp_node;
				start = start->next;
				end->next = start;
				node_count--;
			} else { 
				start = start->next;
			}
			data_count--;
		}


		/*
		 * 특정 data 가 있는지 검색한다.
		 * @param
		 * data - 검색할 데이터.
		 * @return
		 * 해당 데이터가 존재할 경우 해당 노드를 반환하고
		 * 해당 데이터를 찾지 못했을 경우 NULL을 반환한다.
		 */
		Oneway::Node<NODE_DATA_TYPE> * FindData(const NODE_DATA_TYPE & data){
			if(data_count <= 0) 
				return false;

			Oneway::Node<NODE_DATA_TYPE> * node = start;
			//@TODO 내부 노드 저장 구조....가....
			if(node->GetData() == data)
				return true;

			while(node != end){
				node = node->next;
				if(node->GetData() == data)
					return true;
			}
			return false;
		}


		//모든 노드를 제거한다.
		void Clear() {
			Oneway::Node<NODE_DATA_TYPE> * temp = NULL;
			for (int i = 0; i < node_count; i++) {
				temp = start->next;
				delete start;
				start = temp;
			}
			node_count = 0;
		}

		//Node 타입 정의
		typedef Oneway::Node<NODE_DATA_TYPE> * item;
		
		//getter
		inline int GetNodeCount() { return node_count; }
		inline int GetDataCount() { return data_count; }
		inline int GetNodeMaximum() { return node_maximum; }

		inline item GetFrontItem() { return (data_count > 0) ? start : NULL; }
		inline item GetEndItem() { return (data_count > 0) ? end : NULL;  }

		static inline int GetDefaultNodeCount() { return default_node_poll_count; }

	
private:
		/*
		* 새로운 노드를 추가한다.
		* @param
		* data - 새로운 노드에 추가될 데이터.
		* @return
		* 성공시 data_count(데이터 개수)를 반환하고
		* 실패시 -1을 반환한다.
		*/
		int AddNode(const NODE_DATA_TYPE & data) {
			end->next = Oneway::Node<NODE_DATA_TYPE>::CreateNode(data);
			if (end->next == NULL) // False;
				return -1;
			node_count++;
			data_count++;
			end = end->next;
			end->next = start;
			return data_count;
		}

private:
		Oneway::Node<NODE_DATA_TYPE> * start;
		Oneway::Node<NODE_DATA_TYPE> * end;
		int node_maximum;
		int data_count;
		int node_count;

		//Default Node Count
		static const int default_node_poll_count = 30;
	};
};
#endif // !
