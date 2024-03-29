#pragma once
#include "HighFactoryIf.h"


#define REGISTER_CLASS(n) DesignPatternsNamespace::HighFactory::getInstance().register_class<n>(#n)


namespace DesignPatternsNamespace
{

template <class T> 
// Ex 1 - No params for constructor
//void* constructor() 
// Ex 2
void* constructor(const std::string& param0)
{ 
    //return (void*)new T(); 
    return (void*)new T(param0); 
}


class HighFactory : public DesignPatternsNamespace::HighFactoryIf
{
public:

    ~HighFactory();
    
    std::string getName();
    
    // Singleton stuff
    static HighFactory& getInstance()
    {
        static HighFactory instance;
        return instance;
    } 
    
    HighFactory(HighFactory const&) = delete;
    void operator=(HighFactory const&) = delete;
    //

   template <class T>
   void register_class(std::string const& n)
   { 
        std::cout << "[HighFactory][register_class] Registering class " << n << std::endl;
        m_classes.insert(std::make_pair(n, &constructor<T> )); 
    }
    // Ex 1  - No param construct Test()
    // void* construct(std::string const& n )
    // Ex 2 - Construct object with one param std::string
    void* construct(std::string const& n, const std::string& param0)
   {
        map_type::iterator i = m_classes.find(n);
        if (i == m_classes.end()) return 0; // or throw or whatever you want
        // Ex 1 - No params for constructor
        // return i->second();
        // Ex 2
        std::cout << "[HighFactory][construct] Creating object " << param0 << std::endl;
        return i->second(param0);  // Pass arg as function param
   } 

private:

    HighFactory();

//int m_id;
static const std::string objectID;

// Ex 1 - No params for constructor
//typedef void*(*constructor_t)();
// Ex 2 - One (std::string) param for constructor
typedef void*(*constructor_t)(const std::string&);
typedef std::map<std::string, constructor_t> map_type;
map_type m_classes;
};

} // End of namespace

// Izmjena parametara za constructor:
/*
 * void* constructor(std::string param0) 
 * void* construct(std::string const& n, std::string param0)
 * typedef void*(*constructor_t)(std::string);
*/
