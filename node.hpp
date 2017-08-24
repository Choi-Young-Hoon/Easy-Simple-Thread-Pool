#ifndef __LIB_INCLUDE_ONEWAY_NODE_HEADER__
#define __LIB_INCLUDE_ONEWAY_NODE_HEADER__
namespace clib {
	template <typename NODE_DATA_TYPE>
	class NodeData{
	public:
		NodeData(){}
		NodeData(const NODE_DATA_TYPE & _data):data(_data){}
		~NodeData(){}
		//setter
		inline void SetData(const NODE_DATA_TYPE & _data) { this->data = _data; }
		//getter
		inline NODE_DATA_TYPE GetData() { return data; }
	private:
		NODE_DATA_TYPE data;
	};

	// 단방향 노드
	namespace Oneway{
		template <typename NODE_DATA_TYPE>
		class Node : public NodeData<NODE_DATA_TYPE>{
		public:
			Node() 
				:NodeData<NODE_DATA_TYPE>(),
				 next(NULL) {}
			Node(const NODE_DATA_TYPE & _data) 
				:NodeData<NODE_DATA_TYPE>(_data),
				 next(NULL) {}
			~Node() {}
	
			//Creator
			static inline Node<NODE_DATA_TYPE> * CreateNode() {
				return new Oneway::Node<NODE_DATA_TYPE>();
			}
			static inline Node<NODE_DATA_TYPE> * CreateNode(const NODE_DATA_TYPE & data) {
				return new Oneway::Node<NODE_DATA_TYPE>(data);
			}
		public:	// Node Pointer
			Node<NODE_DATA_TYPE> * next;
		};
	};

	// 양방향 노드
	namespace Twoway{
		template <typename NODE_DATA_TYPE>
		class Node : public NodeData<NODE_DATA_TYPE>{
		public:
			Node()
				:NodeData<NODE_DATA_TYPE>(),
				 next(NULL), before(NULL) {}
			Node(const NODE_DATA_TYPE & _data) 
				:NodeData<NODE_DATA_TYPE>(_data),
				 next(NULL), before(NULL) {}
			~Node() {}

			//Creator
			static inline Node<NODE_DATA_TYPE> * CreateNode() {
				return new Node<NODE_DATA_TYPE>();
			}
			static inline Node<NODE_DATA_TYPE> * CreateNode(const NODE_DATA_TYPE & data){
				return new Node<NODE_DATA_TYPE>(data);
			}

		public: //Node Pointer
			Node<NODE_DATA_TYPE> * next;
			Node<NODE_DATA_TYPE> * before;
		};
	};

	//이진 트리 노드.
	namespace KeyNode{
		template<typename KEY_TYPE, typename NODE_DATA_TYPE>
		class Node : public NodeData<NODE_DATA_TYPE>{
		public:
			Node()
				:NodeData<NODE_DATA_TYPE>()
				,left(NULL), right(NULL){}
			Node(const KEY_TYPE & key, const NODE_DATA_TYPE & data)
				:NodeData<NODE_DATA_TYPE>(data) 
				,left(NULL), right(NULL)
				,key(key) {}
			~Node(){}

			//Creator
			static inline Node<KEY_TYPE, NODE_DATA_TYPE> * CreateNode(){
				return new Node<KEY_TYPE, NODE_DATA_TYPE>();
			}
			static inline Node<KEY_TYPE, NODE_DATA_TYPE> * CreateNode(const KEY_TYPE & key, const NODE_DATA_TYPE & data){
				return new Node<KEY_TYPE, NODE_DATA_TYPE>(key, data);
			}

			//setter
			inline void SetKey(const KEY_TYPE & key){ this->key = key; }
			//getter
			inline KEY_TYPE GetKey(){ return key; }

		public: //Node Pointer
			Node<KEY_TYPE, NODE_DATA_TYPE> * left;
			Node<KEY_TYPE, NODE_DATA_TYPE> * right;
		private: //Key 
			KEY_TYPE key;
		};
	};
};
#endif
