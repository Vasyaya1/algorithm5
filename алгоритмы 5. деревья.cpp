#include <iostream>
#include <fstream>

using namespace std;

//struct node {
//	int info;
//	node* left, * right;
//};
//typedef node* tinfo;
//struct stack {
//	tinfo info;
//	stack* next;
//};
//void show1(node*& top) {
//	if (top) {
//		cout << top->info << " ";
//		show1(top->left);
//		show1(top->right);
//	}
//}
//stack* stack_create() {
//	return NULL;
//}
//void push(stack*& top, tinfo x) {
//	stack* p = new stack;
//	p->info = x;
//	p->next = top;
//	top = p;
//}
//
//bool empty(stack*& top) {
//	return top == NULL;
//}
//
//tinfo pop(stack*& top) {
//	node* q = top->info;
//	if (!empty(top)) {
//		stack* p = top;
//		top = top->next;
//		delete p;
//	}
//	return q;
//}
//node* node_create(int x, node* l = NULL, node* r = NULL) {
//	node* p = new node;
//	p->info = x;
//	p->left = l;
//	p->right = r;
//	return p;
//}
////1)
//void MinMax(node*& root) {
//	if (!root)
//		return;
//	node* max, * min;
//	max = root;
//	min = root;
//	stack* st = stack_create();
//	push(st, root);
//	while (!(empty(st))) {
//		node* p = pop(st);
//		if (p->info < min->info)
//			min = p;
//		if (p->info > max->info)
//			max = p;
//		if (p->left)
//			push(st, p->left);
//		if (p->right)
//			push(st, p->right);
//	}
//	swap(min->info, max->info);
//}
//
////2)
//double mid_num(node*& root) {
//	if (!root)
//		return -1;
//	stack* st = stack_create();
//	double sum = 0;
//	int count = 0;
//	push(st, root);
//	while (!empty(st)) {
//		node* p = pop(st);
//		sum += p->info;
//		count++;
//		if (p->right)
//			push(st, p->right);
//		if (p->left)
//			push(st, p->left);
//	}
//	return sum / count;
//}
////3)
//bool is_equal(node* root1, node* root2) {
//	if (!root1 && !root2)
//		return true;
//	if (!root1 || !root2)
//		return false;
//	stack* st1 = stack_create();
//	stack* st2 = stack_create();
//	push(st1, root1);
//	push(st2, root2);
//	while (!empty(st1) && !empty(st2)) {
//		node* p1 = pop(st1);
//		node* p2 = pop(st2);
//		if (p1->info != p2->info) {
//			return false;
//			break;
//		}
//		if (p1->right && p2->right) {
//			push(st1, p1->right);
//			push(st2, p2->right);
//		}
//		else if (!(!p1->right && !p2->right)) {
//			return false;
//			break;
//		}
//		if (p1->left && p2->left) {
//			push(st1, p1->left);
//			push(st2, p2->left);
//		}
//		else if (!(!p1->left && !p2->left)) {
//			return false;
//			break;
//		}
//	}
//	return true;
//}
////4)
//node* copy(node* root) {
//	if (!root)
//		return NULL;
//	node* root1 = node_create(root->info);
//	stack* st = stack_create();
//	stack* st1 = stack_create();
//	push(st, root);
//	push(st1, root1);
//	while (!empty(st)) {
//		node* p = pop(st);
//		node* p1 = pop(st1);
//		if (p->right) {
//			p1->right = node_create(p->right->info);
//			push(st, p->right);
//			push(st1, p1->right);
//		}
//		if (p->left) {
//			p1->left = node_create(p->left->info);
//			push(st, p->left);
//			push(st1, p1->left);
//		}
//	}
//	return root1;
//}

//  BFS

struct node {
	int info;
	node* left, * right;
};
typedef node* tinfo;
struct elem {
	tinfo info;
	elem* next;
	elem* prev;
};
struct Queue {
	elem* first, * last;
};
Queue* create_queue() {
	Queue* q = new Queue;
	q->first = NULL;
	q->last = NULL;
	return q;
}
bool empty(Queue* q) {
	return q->first == NULL;
}
void EnQueue(Queue*& q, tinfo x) {
	elem* p = new elem;
	p->info = x;
	p->next = NULL;
	if (empty(q)) {
		p->next = NULL;
		p->prev = NULL;
		q->last = p;
	}
	else {
		p->next = q->first;
		p->prev = NULL;
		q->first->prev = p;
	}
	q->first = p;
}
tinfo DeQueue(Queue*& q) {
	if (!empty(q)) {
		elem* p = q->last;
		q->last = q->last->prev;
		if (q->last != NULL)
			q->last->next = NULL;
		else
			q->first = q->last;
		tinfo x = p->info;
		delete p;
		return x;
	}
}
void show(node* root) {
	if (root) {
		cout << root->info << " ";
		show(root->left);
		show(root->right);
	}
}

node* node_create(int x, node* l = NULL, node* r = NULL) {
	node* p = new node;
	p->info = x;
	p->left = l;
	p->right = r;
	return p;
}

//5)
node* create_tree(ifstream& in) {
	node* root = new node;
	int x;
	in >> x;
	Queue* q = create_queue();
	root = node_create(x);
	EnQueue(q, root);
	while (!in.eof()) {
		node* p = DeQueue(q);
		if (!in.eof()) {
			in >> x;
			p->left = node_create(x);
			EnQueue(q, p->left);
		}
		if (in.peek() != EOF) {
			in >> x;
			p->right = node_create(x);
			EnQueue(q, p->right);
		}
	}
	return root;
 }

//int main() {
//	ifstream in("abc.txt");
//	node* root = new node;
//	root = create_tree(in);
//	show(root);
//}


//6)
void H(node* root) {
	if (!root)
		return;
	Queue* q = create_queue();
	EnQueue(q, root);
	int cur = 1; 
	int next = 0; 
	int h = 0;
	while (!empty(q)) {
		node* p = DeQueue(q);
		cur--;
		if (p->left) { 
			EnQueue(q, p->left);
			next++;
		}
		if (p->right) {
			EnQueue(q, p->right);
			next++;
		}
		if (cur == 0) {
			cur = next;
			next = 0;
			h++;
		}
	}
	cout << h;
}


//7) 
void length(node* root, int x) {
	if (!root)
		return;
	Queue* q = create_queue();
	EnQueue(q, root);
	int cur = 1, next = 0;
	int dl = 1;
	while (!empty(q)) {
		node* p = DeQueue(q);
		cur--;
		if (p->info == x) {
			cout << dl;
			break;
		}
			
		if (p->left) {
			EnQueue(q, p->left);
			next++;
		}
		if (p->right) {
			EnQueue(q, p->right);
			next++;
		}
		if (cur == 0) {
			cur = next;
			next = 0;
			dl++;
		}
	}
}

//8)
void vertex_count(node* root, int n) {
	if (!root)
		return;
	Queue* q = create_queue();
	EnQueue(q, root);
	int cur = 1, next = 0;
	int k = 1;
	while (!empty(q)) {
		node* p = DeQueue(q);
		if (k == n) {
			cout << cur; // кол во вершин на заданном уровне
			break;
		}
		cur--;
		if (p->left) {
			EnQueue(q, p->left);
			next++;
		}
		if (p->right) {
			EnQueue(q, p->right);
			next++;
		}
		if (cur == 0) {
			cur = next;
			next = 0;
			k++;
		}
	}
}

//9)
void width(node* root) {
	if (!root)
		return;
	Queue* q = create_queue();
	EnQueue(q, root);
	int wid = 0;
	int cur = 1, next = 0;
	while (!(empty(q))) {
		node* p = DeQueue(q);
		cur--;
		if (p->left) {
			EnQueue(q, p->left);
			next++;
		}
		if (p->right) {
			EnQueue(q, p->right);
			next++;
		}
		if (cur == 0) {
			wid = max(wid, next);
			cur = next;
			next = 0;
		}
	}
	cout << wid;
}

//11) в чем то ошибка
//bool summ(node* root) {
//	if (!root)
//		return 0;
//	Queue* q = create_queue();
//	EnQueue(q, root);
//	int cur = 1, next = 0;
//	int k;
//	while (!empty(q)) {
//		int sum = 0;
//		k = cur;
//		for (int i = 0; i < k; i++) {
//			node* p = DeQueue(q);
//			cur--;
//			sum += p->info;
//			if (p->left) {
//				EnQueue(q, p->left);
//				next++;
//			}
//			if (p->right) {
//				EnQueue(q, p->right);
//				next++;
//			}
//		}
//		if (cur == 0) {
//			if (!empty(q)) {
//				int next_sum = 0;
//				for (int i = 0; i < next; i++) {
//					node* p = DeQueue(q);
//					next_sum += p->info;
//					EnQueue(q, p);
//				}
//				if (sum < next_sum)
//					return false;
//			}
//			cur = next;
//			next = 0;
//
//		}
//	}
//	return true;
//}

//11)
bool summ(node* root) {
	if (!root)
		return true;
	Queue* q = create_queue();
	EnQueue(q, root);
	int cur = 1, next = 0;
	int sum = 0, sum2= 0;
	while (!empty(q)) {
		//int sum = 0;
		node* p = DeQueue(q);
		sum += p->info;
		cur--;
		//int sum2 = 0;
		if (p->left) {
			EnQueue(q, p->left);
			next++;
			sum2 += p->left->info;
			//cout << p->left->info << endl;
		}
		if (p->right) {
			EnQueue(q, p->right);
			next++;
			sum2 += p->right->info;
			//cout << p->right->info << endl;
		}
		if (cur == 0) {
			if (sum2 > sum)
				return false;
			sum = 0;
			sum2 = 0;
			cur = next;
			next = 0;

		}
	}
	return true;
}


//рекурсия на деревьях
//1)
void del(node*& root) {
	if (root == NULL)
		return;
	del(root->left);
	del(root->right);
	delete root;
	root = NULL;
}
//2)
node* copy2(node*& root) {
	if (!root)
		return NULL;
	node* root1 = new node;
	root1->info = root->info;
	root1->left = copy2(root->left);
	root1->right = copy2(root->right);
	return root1;
}
//3)
bool is_equal2(node*& root1, node*&root2) {
	if (!root1 && !root2)
		return true;

	return (root1 && root2) && (root1->info == root2->info)
		&& is_equal2(root1->right, root2->right)
		&& is_equal2(root1->left, root2->left);
}

//4)
int  countX(node*& root, int x) {
	if (!root)
		return 0;
	int k = 0;
	if (root->info == x)
		k++;
	k += countX(root->left, x);
	k += countX(root->right, x);
	return k;

}
//5) 

int count_vertices(node* root, int n, int cur_n = 0) {
	if (!root)
		return 0;
	if (cur_n == n)
		return 1;
	return count_vertices(root->left, n, cur_n + 1) + count_vertices(root->right, n, cur_n + 1);
}


//6)
int depth(node*& root) {
	if (!root)
		return 0;
	int lef =1+ depth(root->left);
	int rig =1+ depth(root->right);
	return max(lef, rig);
}


//дерево поиска
//7)
void remove(node*& root, int x) {
	if (!root)
		return;
	if (root->info < x) {
		remove(root->right, x);
	}
	else if (root->info > x) {
		remove(root->left, x);
	}
	else {
		if (!root->left && !root->right) { // если оба потомки пустые удаляем вершину
			delete root;
			root = NULL;
		}
		else if (!root->left) {//если левое поддер пустое удаляю вершину
			                   
			node* p = root->right;
			delete root;
			root = p;
		}
		else if (!root->right) {
			node* p = root->left;
			delete root;
			root = p;
		}
		else {
			node* p = root->right;  // находим самый маленький эл из больших и ставим его на место вершины
			while (p->left) {
				p = p->left;
			}
			root->info = p->info; //меняем местами удаляемую  вершину и найденное число 
			remove(root->right, p->info); // и рекурсивно удалить
		}
	}
}
//8)
node* search(node* root, int x) {
	if (!root)
		return NULL;
	node* p = root;
	while (p) {
		if (p->info == x)
			return p;
		if (x > p->info)
			p = p->right;
		else
			p = p->left;
	}
	return p;
}


int main() {
	ifstream in("abc.txt");
	node* root1 = node_create(10);
	root1->left = node_create(8);
	root1->right = node_create(2);
	root1->left->left = node_create(-5);
	root1->left->right = node_create(6);
	root1->right->left = node_create(3);
	root1->right->right = node_create(4);
	if (summ(root1))
		cout << "YES";
	else
		cout << "no";

		//5)
	//node* root2 = new node;
	//root2 = create_tree(in);
	//show(root2);

}
		//6)
		/* H(root1);*/

		//7)
		//length(root1, 6);

		//8)
		//vertex_count(root1, 2);

		//9)
		//width(root1);
		//	node* root2 = node_create(10);
		//	root2->left = node_create(8);
		//	root2->right = node_create(7);
		//	root2->left->left = node_create(-5);
		//	root2->left->right = node_create(9);
		//	//root2->right->left = node_create(-4);
		//	root2->right->right = node_create(1);
		//
		//
		//	//3)
		//	//if (is_equal2(root1, root2))
		//	//	cout << "yes";
		//	//else
		//	//	cout << "NO";
		//
		//	//4)
		//	//cout << countX(root1, 8);
		//
		//	//5)
		//cout << count_vertices(root1, 2);

	//
	//	//6)
	//cout << depth(root1);
//}
//
//	//7)
//int main() {
//	node* root1 = node_create(8);
//	root1->left = node_create(3);
//	root1->right = node_create(10);
//	root1->left->left = node_create(1);
//	root1->left->right = node_create(6);
//	root1->left->right->left = node_create(4);
//	root1->left->right->right = node_create(7);
//	root1->right->right = node_create(14);
//	root1->right->right->left = node_create(13);
//
//	remove(root1, 3);
//	show(root1);
//}

//
//	/*node* tt = new node;
//	tt = search(root1, 5);
//	show(tt);*/
//
//}