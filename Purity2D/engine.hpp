#ifndef ENGINE_HPP_INCLUDED
#define ENGINE_HPP_INCLUDED

class Engine {
private:
    static Engine* instance;
    Engine();

public:
    static Engine* getInstance();
};


#endif // ENGINE_HPP_INCLUDED
