#pragma once

#include <map>
#include <typeindex>
#include <iostream>

class Context{
public:
    static Context& get_instance(){
        static Context context{}; 
        return context;
    }

    template<typename T, typename... Args>
    void emplace(Args&&... args){
        instances[typeid(T)] = static_cast<std::shared_ptr<void>>(
                std::make_shared<T>(std::forward<Args>(args)...)
                );
    }

    template<typename T>
    T* get(){
        if(instances.find(typeid(T)) == instances.end()){
            return nullptr;
        };
        return static_cast<T*>(instances[typeid(T)].get());
    }

private:
    Context(){};
    std::map<std::type_index, std::shared_ptr<void>> instances;
};
