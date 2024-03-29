#include "Logging_Acceptor.h"
#include "Initiation_Dispatcher.h"



Reactor::Logging_Acceptor::Logging_Acceptor(int id) : m_id(id)
{
    std::cout << "[Logging_Acceptor] Constructor called" << '\n';
    // Register acceptor with the Initiation Dispatcher, which "double dispatches"
    // the Logging_Acceptor::get_handle() method to obtain the HANDLE.

    Reactor::Initiation_Dispatcher::getInstance().register_Logging_Acceptor(this);
};


Reactor::Logging_Acceptor::~Logging_Acceptor()
{
    std::cout << "[Logging_Acceptor] Destructor called" << std::endl;
}


int Reactor::Logging_Acceptor::handle_event(const std::string& eventType)
{
    std::cout << "[Logging_Acceptor] handle_event called ..." << '\n';
};


void Reactor::Logging_Acceptor::register_EventHandler(int clientId)
{
    // Create handler for each client (client <-> handler)
    //EventHandler* clientHandler = new EventHandler(clientId);
    //m_vecOfEventHandler.push_back(clientHandler);

    Event_Handler* client_Handler = new Event_Handler(clientId);
    m_vecOfEvent_Handler.push_back(client_Handler);
}


void Reactor::Logging_Acceptor::remove_EventHandler(int socketDescriptorId)
{
    for(auto it = m_vecOfEvent_Handler.begin(); it != m_vecOfEvent_Handler.end();) 
    {
        if( (*it)->getClientId() == socketDescriptorId ) 
        { 
            delete *it; 
            std::cout << "Deleting *it: " << *it << '\n'; 
            // Delete   
            it = m_vecOfEvent_Handler.erase(it);
        }
        else  
        { 
            ++it;  
        } 
    }  
}

/*
std::vector<EventHandler*>& Reactor::Logging_Acceptor::get_EventHandlerVec()
{
    return m_vecOfEventHandler;
}
*/

std::vector<Reactor::Event_Handler*>& Reactor::Logging_Acceptor::get_Event_HandlerVec()
{
    return m_vecOfEvent_Handler;
}

void Reactor::Logging_Acceptor::processMessage(const int clientId, const std::string& incomingMessage)
{
    std::cout << "Logging_Acceptor processing incoming message ..." << '\n';
    std::cout << "clientId: " << clientId << '\n';
    std::cout << "incoming message: " << incomingMessage << '\n';
}
