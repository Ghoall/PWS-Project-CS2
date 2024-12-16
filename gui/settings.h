#pragma once

namespace settings
{
	inline float MaxRenderFPS = 144.0f;

	namespace esp
	{
		inline bool bEspSwitch = false;

		inline bool bBox = false;
		inline float box_color_r{ 0.f };
		inline float box_color_g{ 0.f };
		inline float box_color_b{ 0.f };
		inline float box_color_a{ 1.f };
		inline float box_color[4] = { box_color_r, box_color_g, box_color_b, box_color_a };


		inline bool bCornerBox = false;
		inline float cornerbox_color_r{ 1.f };
		inline float cornerbox_color_g{ 0.f };
		inline float cornerbox_color_b{ 0.f };
		inline float cornerbox_color_a{ 1.f };
		inline float cornerbox_color[4] = { cornerbox_color_r, cornerbox_color_g, cornerbox_color_b, cornerbox_color_a };
		

		inline bool bSnapLines = false;
		inline float snaplines_color_r{ 1.f };
		inline float snaplines_color_g{ 0.f };
		inline float snaplines_color_b{ 0.f };
		inline float snaplines_color_a{ 1.f };
		inline float snaplines_color[4] = { snaplines_color_r, snaplines_color_g, snaplines_color_b, snaplines_color_a };
		

		inline bool bSkeleton = false;
		inline float skeleton_color[4] = { 0.f, 1.f, 0.f, 1.f };
		

		inline bool bFillBox = false;
		inline float fillbox_color_r{ 1.f };
		inline float fillbox_color_g{ 0.f };
		inline float fillbox_color_b{ 0.f };
		inline float fillbox_color_a{ 0.3f };
		inline float fillbox_color[4] = { fillbox_color_r, fillbox_color_g, fillbox_color_b, fillbox_color_a };

		inline bool bWeapon = false;
		inline float weapon_color[4] = { 1.f, 1.f, 1.f, 1.f };

		inline bool bAmmo = false;
		inline bool bNames = false;
		inline float name_color_r{ 1.f };
		inline float name_color_g{ 0.f };
		inline float name_color_b{ 0.f };
		inline float name_color_a{ 1.f };
		inline float name_color[4] = { fillbox_color_r, fillbox_color_g, fillbox_color_b, fillbox_color_a };
	}

	namespace aimbot
	{
		inline bool bAimbotSwitch = false;
		inline bool bAimbot = false;                inline int smoothing = 6.f;
		inline int aim_key;

		inline bool bFov = false;       
		inline float fov_color_r = { 1.f }; inline float fov_color_g{ 0.f }; inline float fov_color_b{ 0.f };  inline float fov_color_a{ 1.f };
		inline float fov_color[4] = { fov_color_r, fov_color_g, fov_color_b, fov_color_a };  
		inline int fovSize = 50;

	}

	namespace rcs
	{
		inline bool bRcs = false;
		inline int rcs_key;
	}

	namespace triggerbot
	{
		inline bool bTrigger = false;               inline int trigger_delay = 0;
		inline int trigger_key;
	}

	namespace misc
	{
		inline bool bRadar = false;
		inline bool bHitsound = false;              inline int hitsound = 0;
	}
}