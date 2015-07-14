#ifndef __GAME_OBJECT__
#define __GAME_OBJECT__

class GameObject {
    public:
        virtual void render() = 0;
        virtual void update() = 0;
        virtual void clean() = 0;
        virtual void load() = 0;

    protected:
        GameObject() {}
        virtual ~GameObject() {}

};

#endif

