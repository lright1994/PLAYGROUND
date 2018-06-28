//��ʽ����ģʽ
//����*�ɱ����ģ��*��*����ת��*
//

#ifndef SINGLETON_H
#define SINGLETON_H

#include <utility>
#include <iostream>
#include <string>

template<typename T>
class Singleton
{
public:
    template<typename... Args>
    static T* Instance(Args&&... args)
    {
        if(m_instance == nullptr)
        {
            m_instance = new T(std::forward<Args>(args)...);
        }
        return m_instance;
    }
    static void Destory(void)
    {
        delete m_instance;
        m_instance = nullptr;
    }
private:
    Singleton(void);
    virtual ~Singleton(void);
    Singleton(const Singleton&);
    Singleton& operator = (const Singleton&);
private:
    static T* m_instance;
};
template <class T> T*  Singleton<T>::m_instance = nullptr; //���˽�о�̬��Ա�ĳ�ʼ��������



struct TestA
{
    TestA(const std::string&) {std::cout<<"left"<<std::endl;}
    TestA(std::string&&) {std::cout<<"right"<<std::endl;}
};


#endif // SINGLETON_H
