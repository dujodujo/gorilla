
#ifndef UTILS_H
#define UTILS_H

template<class T>
inline T maxOf(const T& a, const T&b) {
	if(a>b)
		return a;
	return b;
}

#endif