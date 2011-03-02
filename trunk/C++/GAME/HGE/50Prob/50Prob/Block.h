#pragma once
#include <hge.h>
#include <hgeFont.h>
#include <hgeSprite.h>
#include <cstdio>
#define ANI_TIME 0.2f

enum KEY { Left, Right, Down };

struct coor {
    float x, y;
};

const coor pos[9] = { { 100, 7 }, { 100, 5 }, { 100, 58 }, { 100, 111 }, 
    { 100, 164 }, { 100, 217 }, { -100, 217 }, { 300, 217 }, { 100, 600 } };

class CBlock
{
private:
    HGE *hge;
    hgeFont *fnt;
    hgeSprite *frame;
    int a, b;
    int ans;
    coor nowpos, nextpos;
    bool isRight;

public:
    CBlock(HGE *phge, hgeFont *pfnt, hgeSprite *pframe);
    ~CBlock(void);

    void SetNow(int i){ nowpos = pos[i]; }
    void SetNext(int i){ nextpos = pos[i]; }
    int GetNow(){ for(int i = 0; i < 8; i++) if(pos[i].x == nowpos.x && pos[i].y == nowpos.y) return i; }
    int GetNext(){ for(int i = 0; i < 8; i++) if(pos[i].x == nextpos.x && pos[i].y == nextpos.y) return i; }

    void Render(float x = -9999, float y = -9999, int al = -9999);
    void AniRender(float timer);
    void SetWrong(){ isRight = false; };

    KEY GetKey();
};
