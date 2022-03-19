#define GREENTRACE
#include<string>
#include<vector>
#include "DynamicArray.h"
#include "../Helper/Number.h"
#include "../Helper/noisy.h"
#include "SList.h"
#include "SDList.h"
#include<iostream>

class Number;

template<typename T>
constexpr void test(T actual, T expected, std::string testName) {
	if (expected == actual) {
		std::cout << testName << " passed!!" << std::endl;
	}
	else {
		std::cout << testName << " failed!!" << std::endl;
		std::cout << "expected " << expected << " but was " << actual << std::endl;
	}
}

MyVector<int> getClone() {
	return MyVector<int>{1, 2, 3};
}

void runDynamicArrayUnitTests() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	MyVector<int> vreserve;
	test(vreserve.size(), static_cast<size_t>(0), "vreserve_size");
	vreserve.reserve(5);
	test(vreserve.size(), static_cast<size_t>(0), "vreserve_size");
	test(vreserve.capacity(), static_cast<size_t>(5), "vreserve_capacity");
	vreserve.push_back(1), vreserve.push_back(2), vreserve.push_back(3), vreserve.push_back(4), vreserve.push_back(5);
	test(vreserve.capacity(), static_cast<size_t>(5), "vreserve_capacity");
	test(vreserve.size(), static_cast<size_t>(5), "vreserve_size");
	test(vreserve[0], 1, "vreserve_access");
	test(vreserve[1], 2, "vreserve_access");
	test(vreserve[2], 3, "vreserve_access");
	test(vreserve[3], 4, "vreserve_access");
	test(vreserve[4], 5, "vreserve_access");

	MyVector<int> vempty;
	test(vempty.size(), static_cast<size_t>(0), "vempty_size");
	vempty.push_back(1), vempty.push_back(2), vempty.push_back(3), vempty.push_back(4), vempty.push_back(5);
	test(vempty.size(), static_cast<size_t>(5), "vempty_size");
	test(vempty[0], 1, "vempty_access");
	test(vempty[1], 2, "vempty_access");
	test(vempty[2], 3, "vempty_access");
	test(vempty[3], 4, "vempty_access");
	test(vempty[4], 5, "vempty_access");

	MyVector<int> v{ 1,2,3,4,5 };
	test(v.size(), static_cast<size_t>(5), "v_size");
	test(v[0], 1, "v_access");
	test(v[1], 2, "v_access");
	test(v[2], 3, "v_access");
	test(v[3], 4, "v_access");
	test(v[4], 5, "v_access");

	MyVector<int> vclone(3);
	vclone[0] = 1, vclone[1] = 2, vclone[2] = 3;
	test(vclone.size(), static_cast<size_t>(3), "v_clone_size");
	test(vclone[0], 1, "v_clone_access");
	test(vclone[1], 2, "v_clone_access");
	test(vclone[2], 3, "v_clone_access");

	vclone = v;
	test(vclone.size(), static_cast<size_t>(5), "vclone_size");
	test(vclone[0], 1, "vclone_access");
	test(vclone[1], 2, "vclone_access");
	test(vclone[2], 3, "vclone_access");
	test(vclone[3], 4, "vclone_access");
	test(vclone[4], 5, "vclone_access");

	MyVector<int> vpushback = { 1,2,3 };
	test(vpushback.size(), static_cast<size_t>(3), "v_pushback_size");
	test(vpushback.capacity(), static_cast<size_t>(3), "v_pushback_capacity");
	test(vpushback[0], 1, "v_pushback_access");
	test(vpushback[1], 2, "v_pushback_access");
	test(vpushback[2], 3, "v_pushback_access");
	vpushback.push_back(4);
	test(vpushback.size(), static_cast<size_t>(4), "v_pushback_size");
	test(vpushback.capacity(), static_cast<size_t>(6), "v_pushback_capacity");
	vpushback.push_back(5);
	vpushback.push_back(6);
	test(vpushback.size(), static_cast<size_t>(6), "v_pushback_size");
	test(vpushback.capacity(), static_cast<size_t>(6), "v_pushback_capacity");
	test(vpushback[0], 1, "v_pushback_access");
	test(vpushback[1], 2, "v_pushback_access");
	test(vpushback[2], 3, "v_pushback_access");
	test(vpushback[3], 4, "v_pushback_access");
	test(vpushback[4], 5, "v_pushback_access");
	test(vpushback[5], 6, "v_pushback_access");
	vpushback.push_back(7);
	test(vpushback.size(), static_cast<size_t>(7), "v_pushback_size");
	test(vpushback.capacity(), static_cast<size_t>(12), "v_pushback_capacity");
	test(vpushback[0], 1, "v_pushback_access");
	test(vpushback[1], 2, "v_pushback_access");
	test(vpushback[2], 3, "v_pushback_access");
	test(vpushback[3], 4, "v_pushback_access");
	test(vpushback[4], 5, "v_pushback_access");
	test(vpushback[5], 6, "v_pushback_access");
	test(vpushback[6], 7, "v_pushback_access");

	MyVector<int> vmove = getClone();
	test(vmove.size(), static_cast<size_t>(3), "v_move_size");
	test(vmove[0], 1, "v_move_access");
	test(vmove[1], 2, "v_move_access");
	test(vmove[2], 3, "v_move_access");

	auto it = vmove.begin();
	test(*it, 1, "v_move_iterator");
	++it;
	test(*it, 2, "v_move_iterator");
	++it;
	test(*it, 3, "v_move_iterator");
	it = vmove.begin();
	*it = 5;
	test(*it, 5, "v_move_iterator_modify");

	auto reverse_iterator_vector = MyVector{ 1, 2, 3 };
	auto ritb = reverse_iterator_vector.rbegin(), rite = reverse_iterator_vector.rend();
	int pos = reverse_iterator_vector.size() - 1;
	while (ritb != rite) {
		test(*ritb, reverse_iterator_vector[pos--], "reverse_iterator");
		++ritb;
	}
	test(pos, -1, "reverse_iterator");
	/*test(ritb, rite, "reverse_iterator");*/
	ritb = vmove.rbegin();
	*ritb = 5;
	test(*ritb, 5, "reverse_iterator_modify");

	MyVector<int> constvector{ 1, 2, 3 };
	auto cit = constvector.cbegin();
	test(*cit, 1, "v_move_const_iterator");
	++cit;
	test(*cit, 2, "v_move_const_iterator");
	++cit;
	test(*cit, 3, "v_move_const_iterator");
	/*
	cit = vmove.cbegin();
	*cit = 5;
	test(*cit, 5, "v_move_const_iterator_modify");*/
	MyVector<int> itvec = { 1,2,3,4,5 };
	auto itv = itvec.begin();
	auto newitv = itv++;
	test(*itv, 2, "v_move_iterator_postfix");
	test(*newitv, 1, "v_move_iterator_postfix");
	test((int)(itv - newitv), 1, "v_move_iterator_postfix");
	++itv;
	test(*itv, 3, "v_move_iterator_postfix");
	test((int)(itv - newitv), 2, "v_move_iterator_postfix");
	--itv;
	test(*itv, 2, "v_move_iterator_postfix");
	test((int)(itv - newitv), 1, "v_move_iterator_postfix");
	auto newnewitv = itv--;
	test(*newnewitv, 2, "v_move_iterator_postfix");
	test(*itv, 1, "v_move_iterator_postfix");
	test((int)(newnewitv - itv), 1, "v_move_iterator_postfix");
	test((int)(itv - newnewitv), -1, "v_move_iterator_postfix");
}

void runDoublyLinkedListUnitTests() {
	DList<int> iterator_list_forward = { 1,2,3,4,5 };
	std::vector<int> resultv = { 5,4,3,2,1 };
	DList<int>::Iterator itb = iterator_list_forward.begin(), ite = iterator_list_forward.end();
	int pos = 0;
	while (itb != ite) {
		test(*itb, resultv[pos++], "DList_Iterator");
		++itb;
	}
	test(pos, 5, "DList_Iterator");

	DList<int> random_jump_list = { 1,2,3,4,5 };
	DList<int>::Iterator random_jump_list_itb = random_jump_list.begin(), random_jump_list_ite = random_jump_list.end();
	random_jump_list_itb += 3;
	test(*random_jump_list_itb, 2, "random_jump_iterator_test");
	random_jump_list_itb -= 3;
	test(*random_jump_list_itb, 5, "random_jump_iterator_test");

	DList<int> iterator_list_reverse = { 1,2,3,4,5 };
	std::vector<int> result_reverse = { 1,2,3,4,5 };
	DList<int>::Reverse_Iterator iterator_list_reverse_itb = iterator_list_reverse.rbegin(), iterator_list_reverse_ite = iterator_list_reverse.rend();
	int rpos = 0;
	while (iterator_list_reverse_itb != iterator_list_reverse_ite) {
		test(*iterator_list_reverse_itb, result_reverse[rpos++], "DList_Iterator_reverse");
		++iterator_list_reverse_itb;
	}
	test(rpos, 5, "DList_Iterator_reverse");
}

int main() {
	runDynamicArrayUnitTests();
	runDoublyLinkedListUnitTests();
}