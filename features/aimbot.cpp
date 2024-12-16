#include "aimbot.h"

void aimbot::FindClosestPlayer(const Vector3& headpos, Vector3& bestaim, float& max)
{
    float distance = DistanceBetweenCross(headpos.x, headpos.y);

    if (IsInsideFOVCircle(settings::aimbot::fovSize, headpos.x, headpos.y) && distance < max)
    {
        max = distance;
        bestaim = headpos;
    }
}

void aimbot::DoAimbot(float x, float y)
{
    //By fredaikis
    float TargetX = 0.f;
    float TargetY = 0.f;
    if ((x > 0.0f) && (x < 1920.0f))
    {
        if (x > screen_center.x)
        {
            TargetX = (x - screen_center.x); 
            TargetX /= (float)settings::aimbot::smoothing;
            if (TargetX + screen_center.x > screen_center.x * 2) TargetX = 0;
        }

        if (x < screen_center.x)
        {
            TargetX = (x - screen_center.x);
            TargetX /= (float)settings::aimbot::smoothing;
            if (TargetX + screen_center.x < 0) TargetX = 0;
        }
    }
    if ((y > 0.0f) && (y < 1080.0f))
    {
        if (y > screen_center.y)
        {
            TargetY = (y - screen_center.y);
            TargetY /= (float)settings::aimbot::smoothing;
            if (TargetY + screen_center.y > screen_center.y * 2) TargetY = 0;
        }

        if (y < screen_center.y)
        {
            TargetY = (y - screen_center.y);
            TargetY /= (float)settings::aimbot::smoothing;
            if (TargetY + screen_center.y < 0) TargetY = 0;
        }
    }
    //if (true)
    //{
    mouse_event(0x0001, (UINT)TargetX, (UINT)TargetY, NULL, NULL);
    //    return;
    //}
    TargetX /= settings::aimbot::smoothing;
    TargetY /= settings::aimbot::smoothing;
    if (abs(TargetX) < 0.f)
    {
        if (TargetX > 0.f)
        {
            TargetX = .1f;
        }
        if (TargetX < .1f)
        {
            TargetX = -.1f;
        }
    }
    if (abs(TargetY) < 0.f)
    {
        if (TargetY > 0.f)
        {
            TargetY = .1f;
        }
        if (TargetY < 0.f)
        {
            TargetY = -.1f;
        }
    }
    mouse_event(0x0001, (UINT)TargetX, (UINT)TargetY, NULL, NULL); 
  
}
