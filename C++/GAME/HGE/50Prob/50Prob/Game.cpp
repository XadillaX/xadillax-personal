#include "Game.h"

#define COPYRIGHT "By XadillaX(http://www.xcoder.in), using HGE Engine"

HGE *hge = NULL;
hgeFont *fnt = NULL;
hgeResourceManager *rscript;
hgeSprite *frame = NULL, *hint = NULL;
HEFFECT SE, End;
float timer = 0.0f, droppingTimer = 0.0f;
int right = 0, wrong = 0;

bool started = false, end = false, dropping = false;

list<STATE> statlist;
list<CBlock *> blocklist;

bool LoadRes()
{
    /* 载入字体 */
    fnt = rscript->GetFont("fnt");
    if(!fnt) return false;

    /* 载入精灵 */
    frame = rscript->GetSprite("Frame");
    hint = rscript->GetSprite("Hint");
    if(!hint || !frame) return false;

    /* 载入音效 */
    SE = rscript->GetEffect("SE");
    End = rscript->GetEffect("End");
    if(!SE || !End) return false;

    fnt->SetZ(0);
    frame->SetZ(0.5f);
    hint->SetZ(1.0f);

    return true;
}

void WelcomeRender()
{
    fnt->SetColor(0xff000000);
    fnt->SetScale(0.8f);
    char *line[3] = { "Press <space> to start game", "during game, press", "<space> to restart" };
    float y[3] = { 100, 150, 170 };
    for(int i = 0; i < 3; i++)
    {
        float x = (300 - fnt->GetStringWidth(line[i])) / 2;

        fnt->Render(x, y[i], HGETEXT_LEFT, line[i]);
    }
}

void GamingRender()
{
    if(!dropping)
    {
        if(!statlist.empty())
        {
            int j = 0;
            for(list<CBlock *>::iterator i = blocklist.begin(); i != blocklist.end() && j < 6; i++, j++)
            {
                if(j == 0)
                {
                    if(statlist.front().key == Left) (*i)->SetNext(6);
                    else
                    if(statlist.front().key == Right) (*i)->SetNext(7);
                    else (*i)->SetNext(8);
                }
                else (*i)->SetNext(6 - j);
            }

            if(statlist.front().key == blocklist.front()->GetKey())
            {
                right++;
                hge->Effect_PlayEx(SE, 100, 0, 1);
            }
            else
            {
                wrong++;
                blocklist.front()->SetWrong();
                hge->Effect_PlayEx(SE, 100, 0, 2);
            }

            droppingTimer = 0.0f;
            dropping = true;
        }

        int j = 0;
        for(list<CBlock *>::iterator i = blocklist.begin(); i != blocklist.end() && j < 5; i++, j++)
            (*i)->Render();
    }
    else
    {
        if(droppingTimer <= ANI_TIME)
        {
            int j = 0;
            for(list<CBlock *>::iterator i = blocklist.begin(); i != blocklist.end() && j < 6; i++, j++)
                (*i)->AniRender(droppingTimer);
        }
        else
        {
            delete blocklist.front();
            statlist.pop_front();
            blocklist.pop_front();

            int j = 0;
            for(list<CBlock *>::iterator i = blocklist.begin(); i != blocklist.end() && j < 5; i++, j++)
            {
                (*i)->SetNow((*i)->GetNext());
                (*i)->SetNext((*i)->GetNow() - 1);
            }

            dropping = false;
            droppingTimer = 0.0f;

            if(blocklist.empty()) end = true;
        }
    }

    if(timer <= 3.0f)
    {
        float alpha = (int)(((3 - timer) / 3) * 0xff);
        hint->SetColor(ARGB(alpha, 0xff, 0xff, 0xff));

        hint->Render(5, 217);
    }
}

void TimerRender()
{
    fnt->SetScale(0.5f);
    fnt->SetColor(0xff000000);
    fnt->printf(5, 5, HGETEXT_LEFT, "%.2f s\n\n:) %d\n:( %d", timer, right, wrong);
}

void EndRender()
{
    fnt->SetColor(0xff000000);
    fnt->SetScale(0.8f);
    char line[512];

    sprintf(line, "Time: %.2f s\n:) %d\n:( %d\n\nPress <space> to restart", timer, right, wrong);

    float w = fnt->GetStringWidth(line);

    fnt->Render(300 / 2, 200, HGETEXT_CENTER, line);
}

bool RenderFunc()
{
    hge->Gfx_BeginScene();
    hge->Gfx_Clear(0xffffffff);

    if(!started) WelcomeRender();
    else
    if(started && !end) 
    {
        GamingRender();
        TimerRender();
    }
    else
    if(end) EndRender();

    fnt->SetScale(0.5);
    fnt->SetColor(0xff000000);
    fnt->printf(295, 570, HGETEXT_RIGHT, "FPS: %d\n%s", hge->Timer_GetFPS(), COPYRIGHT);

    hge->Gfx_EndScene();

    return false;
}

void StartFunc()
{
    while(!blocklist.empty())
    {
        delete blocklist.front();
        blocklist.pop_front();
    }
    while(!statlist.empty()) statlist.pop_back();

    for(int i = 0; i < 50; i++)
    {
        CBlock *tmp = new CBlock(hge, fnt, frame);

        if(i < 5) 
        {
            tmp->SetNow(5 - i);
            tmp->SetNext(5 - i + 1);
        }

        blocklist.push_back(tmp);
    }

    started = true, end = false, dropping = false;
    timer = 0.0f, right = 0, wrong = 0, droppingTimer = 0.0f;
}

bool FrameFunc()
{
    float dt = hge->Timer_GetDelta();

    if(hge->Input_KeyUp(HGEK_SPACE))
    {
        StartFunc();
        return false;
    }

    if(started && !end)
    {
        timer += dt;
        STATE sta;

        if(dropping) droppingTimer += dt;
        if(hge->Input_KeyUp(HGEK_LEFT))
        {
            sta.key = Left;
            statlist.push_back(sta);
        }
        else
        if(hge->Input_KeyUp(HGEK_RIGHT))
        {
            sta.key = Right;
            statlist.push_back(sta);
        }
        else
        if(hge->Input_KeyUp(HGEK_DOWN))
        {
            sta.key = Down;
            statlist.push_back(sta);
        }
    }

    return false;
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    hge = hgeCreate(HGE_VERSION);

    hge->System_SetState(HGE_LOGFILE, "50Prob.log");
    hge->System_SetState(HGE_SCREENHEIGHT, 600);
    hge->System_SetState(HGE_SCREENWIDTH, 300);
    hge->System_SetState(HGE_SCREENBPP, 32);
    hge->System_SetState(HGE_DONTSUSPEND, true);
    hge->System_SetState(HGE_SHOWSPLASH, false);
    hge->System_SetState(HGE_TITLE, "50 Problems");
    hge->System_SetState(HGE_WINDOWED, true);
    hge->System_SetState(HGE_ZBUFFER, true);
    hge->System_SetState(HGE_FRAMEFUNC, FrameFunc);
    hge->System_SetState(HGE_RENDERFUNC, RenderFunc);
    hge->System_SetState(HGE_ICON, "IDI_50PROB");

    if(hge->System_Initiate())
    {
        hge->Resource_AttachPack("Res.x2pak", "X2Studio");
        rscript = new hgeResourceManager("res");

        if(LoadRes()) hge->System_Start();
        else MessageBox(NULL, "Wrong resource.", "Wrong", MB_ICONSTOP);
    }
    else MessageBox(NULL, "There are problems with initialization.", "Wrong", MB_ICONSTOP);

    while(!blocklist.empty())
    {
        delete blocklist.front();
        blocklist.pop_front();
    }

    hge->System_Shutdown();
    hge->Release();

    return 0;
}
