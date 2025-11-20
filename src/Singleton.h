#pragma once

template<typename T> class Singleton
{
public:

    static T& instance()
    {
        static T singletonInstance; //asumir T posee un constructor por defecto
        return singletonInstance;
    }
//    static std::unordered_map<std:string,T*> instances;
//    static T& instance(std::string name)
//    {
//        if(instances[name]==NULL){
//            static T singletonInstance; //asumir T posee un constructor por defecto
//            instances[name]=singletonInstance;
//        }
//        return instances[name];
//    }
};
