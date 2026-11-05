#include "DxLib.h"
#include "Skill.h"
#include "../Input/Input.h"
#include "../Scene/SceneManager.h"

struct SkillAnimationParam
{
	int interval;
	int frameNum;
	int width;
	int height;
};

const SkillAnimationParam SKILL_ANIM_PARAM[SKILL_ANIM_MAX] =
{
	8, 8, 73, 90,
	8, 8, 90, 90,
	5, 8, 90, 90,
};

#define SKILL_DEFAULT_POS_X (0.0f)
#define SKILL_DEFAULT_POS_Y (0.0f)
#define SKILL_MOVE_SPEED (4.0f)

SkillData g_SkillData = { 0 };

void StartSkillAnimation(SkillAnimationType anim);
void UpdateSkillAnimation();

static bool g_SkillSelect = false;
static int g_SelectSkill = 0;
static int g_SkillDirection = 0;

void InitSkill()
{
	g_SkillSelect = false;
	g_SelectSkill = 0;
	g_SkillDirection = 0;
}

void LoadSkill()
{
	g_SkillData.animation[SKILL_ANIM_FIRE].handle = LoadGraph("Data/Skill/火（範囲攻撃）.png");
	g_SkillData.animation[SKILL_ANIM_WATER].handle = LoadGraph("Data/Skill/水（遠距離攻撃）.png");
	g_SkillData.animation[SKILL_ANIM_THUNDER].handle = LoadGraph("Data/Skill/雷（近距離攻撃）.png");
	g_SkillData.animation[SKILL_ANIM_METEO].handle = LoadGraph("Data/Skill/隕石（必殺技）.png");
	g_SkillData.animation[SKILL_ANIM_SCAFFOLD].handle = LoadGraph("Data/Skill/足場生成.png");
}

void StartSkill()
{
	g_SkillData.active = true;
}

void UpdateSkill(float playerX, float playerY, int playerDirection)
{
    if (IsTriggerKey(KEY_D))
    {
        g_SkillSelect = !g_SkillSelect;
    }

    if (g_SkillSelect)
    {
        if (IsTriggerKey(KEY_UP))
        {
            g_SelectSkill--;

            if (g_SelectSkill < 0)
                g_SelectSkill = SKILL_MAX - 1;
        }

        if (IsTriggerKey(KEY_DOWN))
        {
            g_SelectSkill++;

            if (g_SelectSkill >= SKILL_MAX)
                g_SelectSkill = 0;
        }


        if (IsTriggerKey(KEY_S))
        {
            if (g_SkillData.active)
                return;

            g_SkillData.pos.x = playerX;
            g_SkillData.pos.y = playerY;

            g_SkillData.move = VGet(
                (float)playerDirection,
                (float)g_SkillDirection,
                0.0f
            );

            switch (g_SelectSkill)
            {
            case SKILL_FIRE:
                StartSkillAnimation(SKILL_ANIM_FIRE);
                break;

            case SKILL_WATER:
                StartSkillAnimation(SKILL_ANIM_WATER);
                break;

            case SKILL_THUNDER:
                StartSkillAnimation(SKILL_ANIM_THUNDER);
                break;

            case SKILL_METEOR:
                StartSkillAnimation(SKILL_ANIM_METEO);
                break;

            case SKILL_PLATFORM:
                StartSkillAnimation(SKILL_ANIM_SCAFFOLD);
                break;

            case SKILL_TERRAIN:
                StartSkillAnimation(SKILL_ANIM_CHANGE);
                break;

            case SKILL_BREAK_WALL:
                StartSkillAnimation(SKILL_ANIM_WALL);
                break;

            case SKILL_TIME_STOP:
                StartSkillAnimation(SKILL_ANIM_TIMESTOP);
                break;
            }

            g_SkillData.active = true;
        }
    }
}

void DrawSkill()
{
    if (g_SkillData.active)
    {
        AnimationData* animData =
            &g_SkillData.animation[g_SkillData.skillAnim];

        DrawAnimation(
            animData,
            animData->posX,
            animData->posY,
            false,
            false
        );
    }

    if (!g_SkillSelect)
        return;

    const char* skillName[SKILL_MAX] =
    {
        "Fire",
        "Water",
        "Thunder",
        "Meteor",
        "Platform",
        "Terrain Change",
        "Break Wall",
        "Time Stop"
    };

    DrawBox(400, 150, 900, 650,
        GetColor(20, 20, 40), TRUE);

    DrawBox(400, 150, 900, 650,
        GetColor(255, 255, 255), FALSE);

    DrawString(550, 170, "SKILL SELECT",
        GetColor(255, 255, 255));

    for (int i = 0; i < SKILL_MAX; i++)
    {
        int y = 220 + i * 45;

        if (i == g_SelectSkill)
        {
            DrawBox(430, y - 5, 870, y + 35,
                GetColor(80, 100, 180), TRUE);
        }

        DrawString(460, y, skillName[i],
            GetColor(255, 255, 255));
    }
}

void FinSkill()
{
	for (int i = 0; i < SKILL_ANIM_MAX; i++)
	{
		DeleteGraph(g_SkillData.animation[i].handle);
	}
}

SkillData GetSkill()
{
	return g_SkillData;
}

void StartSkillAnimation(SkillAnimationType anim)
{
    g_SkillData.skillAnim = anim;

    AnimationData* animData =
        &g_SkillData.animation[anim];

    SkillAnimationParam animParam =
        SKILL_ANIM_PARAM[anim];

    StartAnimation(animData, g_SkillData.pos.x, g_SkillData.pos.y, animParam.interval, animParam.frameNum, animParam.width, animParam.height, false);   
}

void UpdateSkillAnimation()
{
    if (!g_SkillData.active)
        return;

    AnimationData* animData =
        &g_SkillData.animation[g_SkillData.skillAnim];

    UpdateAnimation(animData);

    if (!animData->active)
    {
        g_SkillData.active = false;
    }
}