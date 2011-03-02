#include "Block.h"

CBlock::CBlock(HGE *phge, hgeFont *pfnt, hgeSprite *pframe)
{
    hge = phge;
    fnt = pfnt;
    frame = pframe;

    a = hge->Random_Int(1, 9);
    b = hge->Random_Int(1, 9);
    ans = a + b;

    nowpos = pos[0];
    nextpos = pos[1];

    isRight = true;
}

CBlock::~CBlock(void)
{
}

void CBlock::Render(float x, float y, int al)
{
    int p = GetNow();
    int alpha = (int)(((float)p / 5) * 0xff);
    float w, h;

    if(x == -9999 && y == -9999 && al == -9999) x = nowpos.x, y = nowpos.y, al = alpha;

    fnt->SetScale(1.0f);
    frame->SetColor(ARGB(al, isRight ? 0x00 : 0xff, 0x00, 0x00));
    fnt->SetColor(ARGB(al, isRight ? 0x00 : 0xff, 0x00, 0x00));

    char str[512];
    sprintf(str, "%d + %d", a, b);
    h = fnt->GetHeight();
    w = fnt->GetStringWidth(str);

    frame->Render(x, y);
    fnt->Render((x + (100 - w) / 2), (y + (38 - h) / 2), HGETEXT_LEFT, str);
}

void CBlock::AniRender(float timer)
{
    float dx = (timer / ANI_TIME) * (nextpos.x - nowpos.x);
    float dy = (timer / ANI_TIME) * (nextpos.y - nowpos.y);

    int opal = (int)(((float)GetNow() / 5) * 0xff);
    int edal = (GetNext() < 6) ? (int)(((float)GetNext() / 5) * 0xff) : 0;

    int da = (int)((timer / ANI_TIME) * (edal - opal));

    Render(nowpos.x + dx, nowpos.y + dy, opal + da);
}

KEY CBlock::GetKey()
{
    if(ans < 10) return Left;
    else
    if(ans > 10) return Right;
    else return Down;
}
