#pragma once
#ifndef GUARD_VEC_H
#define GUARD_VEC_H

#include <memory>
#include <algorithm>
#include <cstddef>

using namespace std;
template <class T> class Vec
{
public:
	// 속성
	typedef T* iterator;
	typedef const T* const_iterator;
	typedef size_t size_type;
	typedef T value_type;
	typedef ptrdiff_t difference_type;
	typedef T& reference;

	Vec() {
		create();
	};
	explicit Vec(size_type n, const T& val = T()) {
		create(n, val);
	};
	Vec(const Vec& v) { create(v.begin(), v.end()); };
	Vec(const_iterator b, const_iterator e) { create(b, e); }

	size_type size() const { return avail - data; }
	T& operator[](size_type i) { return data[i]; }
	const T& operator[](size_type i) const { return data[i]; }

	Vec& operator=(const Vec&);

	iterator begin() { return data; }
	const_iterator begin() const { return data; }

	iterator end() { return avail; }
	const_iterator end() const { return avail; }

	//insert & assign 추가 (연습문제 12 +13)
	template <class In> void insert(iterator, In, In); 
	void assign(iterator, iterator);

	void push_back(const T& val) {
		if (avail == limit)
			grow();
		unchecked_append(val);
	}

	void push_back_grow_once(const T& t) {
		grow_once();
		unchecked_append(t);
	}

	~Vec() { uncreate(); };
	void clear() { uncreate(); };
	bool empty() const { return data == avail; }

private:
	iterator data;
	iterator avail;
	iterator limit;

	allocator<T> alloc;

	void create();
	void create(size_type, const T&);
	void create(const_iterator, const_iterator);

	void uncreate();

	void grow();
	void grow_once();
	void unchecked_append(const T&);


};

	template <class T> Vec<T>& Vec<T>::operator=(const Vec& rhs) {
	if (&rhs != this) {
		uncreate();
		create(rhs.begin(), rhs.end());
	}
	return *this;
	}

	template <class T> void Vec<T>::create() {
		data = avail = limit = 0;
	}
		template <class T> void Vec<T>::create(size_type n, const T & val) {
			data = alloc.allocate(n);
			limit = avail = data + n;
			uninitialized_fill(data, limit, val);
		}
		template <class T> 
		void Vec<T>::create(const_iterator i, const_iterator j) {
			data = alloc.allocate(j - i);
			limit = avail = uninitialized_copy(i, j, data);
		}
		template <class T> 
		void Vec<T>::uncreate() {
			if (data) {
				iterator it = avail;
				while (it != data)
					alloc.destroy(--it);
				alloc.deallocate(data, limit - data);
			}
			data = limit = avail = 0;
		}
		template <class T>
		void Vec<T>::unchecked_append(const T& val) {
			alloc.construct(avail++, val);
		}
		template <class T>
		void Vec<T>::grow() {
			size_type new_size = max(2 * (limit - data), ptrdiff_t(1));
			iterator new_data = alloc.allocate(new_size);
			iterator new_avail = uninitialized_copy(data, avail, new_data);
			uncreate();
			data = new_data;
			avail = new_avail;
			limit = data + new_size;

	}
		template <class T>
		void Vec<T>::grow_once() {
			size_type new_size = (limit - data + ptrdiff_t(1));

			iterator new_data = alloc.allocate(new_size);
			iterator new_avail = uninitialized_copy(data, avail, new_data);

			uncreate();

			data = new_data;
			avail = new_avail;
			limit = data + new_size;
		}

		//12장 - 연습문제 12
		template <class T>
		template <class In>
		void Vec<T>::insert(iterator d, In b, In e) {
			// 끝 부분과 차이 저장
			Vec<T> end(static_cast<const_iterator>(d), static_cast<const_iterator>(avail)); // d부터 끝까지 다른 Vec에서 data 저장

			// 끝 부분 소멸하기
			if (d) {
				// 역방향으로 d까지 요소를 제거/삭제하기
				while (avail != d)
					alloc.destroy(--avail);
			}

			// b부터 e까지 요소를 추가하기
			while (b != e)
				push_back(*b++);
			
			// 다시 끝 부분 추가하기 (불러오기)
			for (Vec<T>::const_iterator it = end.begin(); it != end.end(); ++it)
				push_back(*it);


		}

		//12장 - 연습문제 13
		template <class T>
		void Vec<T>::assign(iterator b, iterator e) {
			//Vec 소멸
			uncreate();

			//모든 반복자의 요소를 추가하기 
			while (b != e)
				push_back(*b++);
		}
		

#endif

		

