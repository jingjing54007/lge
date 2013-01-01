#pragma once

template<typename T>
class MySingleton
{
public:
	MySingleton(void);
	virtual ~MySingleton();

	static T &getSingleton(void);
	static T *getSingletonPtr(void);

	static void destroySingleton(void);

private:
	static T*& getInnerPtr(void);
};

template<typename T>
inline MySingleton<T>::MySingleton(void)
{
}

template<typename T>
inline MySingleton<T>::~MySingleton(void)
{
}

template<typename T>
inline T &MySingleton<T>::getSingleton(void)
{
	return *getSingletonPtr();
}

template<typename T>
inline T * MySingleton<T>::getSingletonPtr(void)
{
	T*& innerPtr = getInnerPtr();
	if (innerPtr == NULL) {
		innerPtr = new T;
//		MYASSERT(innerPtr != NULL);
	}

	return innerPtr;
}

template<typename T>
inline void MySingleton<T>::destroySingleton(void)
{
	T*& innerPtr = getInnerPtr();
    delete innerPtr;
    innerPtr = NULL;
}

template<typename T>
inline T*& MySingleton<T>::getInnerPtr(void)
{
	static T* innerPtr = NULL;
	return innerPtr;
}
