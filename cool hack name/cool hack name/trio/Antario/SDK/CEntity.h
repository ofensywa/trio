#pragma once
#include "Definitions.h"
#include "IClientUnknown.h"
#include "IClientEntityList.h"
#include "..\Utils\Utils.h"
#include "..\Utils\NetvarManager.h"
#include "Studio.h"

// class predefinition
class C_BaseCombatWeapon;

class C_BaseEntity : public IClientUnknown, public IClientRenderable, public IClientNetworkable
{
private:
	template <typename T>
	T& read(uintptr_t offset)
	{
		return *reinterpret_cast<T*>(reinterpret_cast<uintptr_t>(this) + offset);
	}

	template <typename T>
	void write(uintptr_t offset, T data)
	{
		*reinterpret_cast<T*>(reinterpret_cast<uintptr_t>(this) + offset) = data;
	}

public:
	NETVAR("DT_CSPlayer", "m_iHealth", GetHealth, int);
	NETVAR("DT_CSPlayer", "m_fFlags", GetFlags, int);
	NETVAR("DT_CSPlayer", "m_iTeamNum", GetTeam, int);
	NETVAR("DT_BaseEntity", "m_vecMins", GetOBBMins, Vector);
	NETVAR("DT_BaseEntity", "m_vecMaxs", GetOBBMaxs, Vector);
	NETVAR("DT_CSPlayer", "m_angEyeAngles", GetEyeAngles, Vector);
	NETVAR("DT_CSPlayer", "m_flLowerBodyYawTarget", GetLowerBodyYaw, float);
	NETVAR("DT_BaseAnimating", "m_flCycle", GetCycle, float);
	NETVAR("DT_BaseAnimating", "m_nSequence", GetSequence, int);
	NETVAR("DT_CSPlayer", "m_flSimulationTime", GetSimulationTime, float);
	NETVAR("DT_BasePlayer", "m_vecOrigin", GetVecOrigin, Vector);
	NETVAR("DT_BasePlayer", "m_vecVelocity[0]", GetVelocity, Vector);
	NETVAR("DT_CSPlayer", "m_ArmorValue", GetArmor, int);
	NETVAR("DT_CSPlayer", "m_bHasHelmet", HasHelmet, bool);
	NETVAR("DT_CSPlayer", "m_nTickBase", GetTickBase, int);
	NETVAR("DT_CSPlayer", "m_bGunGameImmunity", GetIsSpawnProtected, bool);
	NETVAR("DT_CSPlayer", "m_bIsScoped", GetScoped, bool);
	NETVAR("DT_CSPlayer", "m_nMoveType", GetMoveType, int);
	NETVAR("DT_CSPlayer", "m_iAccount", GetBalance, int);
	NETVAR("DT_BasePlayer", "m_vecViewOffset[0]", GetViewOffset, Vector);
	NETVAR("DT_BaseViewModel", "m_hOwner", GetOwnerHandle, HANDLE);
	NETVAR("DT_CSPlayer", "m_bIsPlayerGhost", GetIsPlayerGhost, bool);
	NETVAR("DT_BasePlayer", "m_aimPunchAngle", GetAimPunch, Vector);
	NETVAR("DT_BasePlayer", "m_viewPunchAngle", GetViewPunch, Vector);
	NETVAR("DT_BasePlayer", "m_nHitboxSet", GetGitboxSet, int);
	NETVAR("DT_CSPlayer", "m_flDuckAmount", GetCrouchAmount, float);
	NETVAR("DT_CSPlayer", "m_flNextAttack", GetNextAttack, float);
	NETVAR("DT_SmokeGrenadeProjectile", "m_nSmokeEffectTickBegin", GetGrenadeSmokeTickBegin, int);
	NETVAR("DT_HEGrenade", "m_flDamage", GetHeDamage, float);
	NETVAR("DT_CSPlayer", "m_iShotsFired", GetShotsFired, int);
	NETVAR("DT_CSPlayer", "m_flFlashDuration", SetFlashDuration, float);
	NETVAR("DT_CSPlayer", "m_iFlashMaxAlpha", SetFlashAlpha, int);
	NETVAR("DT_CSPlayer", "m_iObserverMode", SetObserverMode, int);
	NETVAR("DT_CSPlayer", "m_lifeState", GetLifeState, int);
	NETVAR("DT_BaseEntity", "m_nFallbackPaintKit", fallbackPaintKit, int);
	NETVAR("DT_CSPlayer", "m_bIsDefusing", isDefusing, bool);
	NETVAR("DT_CSPlayer", "m_bHasDefuser", hasDefuser, bool);
	NETVAR("DT_PlantedC4", "m_flC4Blow", GetC4Blow, float);
	NETVAR("DT_PlantedC4", "m_flDefuseCountDown", GetDefuseCountDown, int);
	NETVAR("DT_BaseCombatWeapon", "m_iItemDefinitionIndex", GetItemDefinitionIndex, int);

	PlayerInfo_t GetPlayerInfo()
	{
		PlayerInfo_t info;
		g_pEngine->GetPlayerInfo(EntIndex(), &info);

		return info;
	}

	Vector& GetAbsOrigin()
	{
		return Utils::CallVTable<Vector&(__thiscall*)(void*)>(this, 10)(this);
	}

	int C_BaseEntity::GetIndex()
	{
		return *reinterpret_cast<int*>((uintptr_t)this + 0x64);
	}

	void C_BaseEntity::SetOrigin(Vector origin)
	{
		using SetAbsOriginFn = void(__thiscall*)(void*, const Vector &origin);
		static SetAbsOriginFn SetAbsOrigin = (SetAbsOriginFn)Utils::FindSignature("client_panorama.dll", "55 8B EC 83 E4 F8 51 53 56 57 8B F1 E8");
	
		SetAbsOrigin(this, origin);
	}

	void C_BaseEntity::SetAngles(const Vector &angles)
	{
		using SetAbsAnglesFn = void(__thiscall*)(void*, const Vector &angles);
		static SetAbsAnglesFn SetAbsAngles = (SetAbsAnglesFn)Utils::FindSignature("client_panorama.dll", "55 8B EC 83 E4 F8 83 EC 64 53 56 57 8B F1 E8");

		SetAbsAngles(this, angles);
	}

	bool IsAlive()
	{
		return this->GetHealth() > 0;
	}

	Vector GetEyePosition()
	{
		return this->GetVecOrigin() + this->GetViewOffset();
	}

	matrix3x4_t& get_rgflcoordinateframe()
	{
		static auto _m_rgflCoordinateFrame = sdk::util::getNetVar(sdk::util::fnv::hash("DT_CSPlayer"), sdk::util::fnv::hash("m_CollisionGroup")) - 0x30;
		return *reinterpret_cast<matrix3x4_t*>(reinterpret_cast<uintptr_t>(this) + _m_rgflCoordinateFrame);
	}

	C_BaseCombatWeapon* GetMyWeapons()
	{
		auto get_weapons = read<DWORD>(sdk::util::getNetVar(sdk::util::fnv::hash("DT_CSPlayer"), sdk::util::fnv::hash("m_hMyWeapons"))) & 0xFFF;
		return reinterpret_cast<C_BaseCombatWeapon*>(g_pEntityList->GetClientEntity(get_weapons));
	}

	C_BaseCombatWeapon* GetActiveWeapon()
	{
		auto active_weapon = read<DWORD>(sdk::util::getNetVar(sdk::util::fnv::hash("DT_CSPlayer"), sdk::util::fnv::hash("m_hActiveWeapon"))) & 0xFFF;
		return reinterpret_cast<C_BaseCombatWeapon*>(g_pEntityList->GetClientEntity(active_weapon));
	}

	Vector GetBonePos(int i)
	{
		matrix3x4_t boneMatrix[128];
		if (this->SetupBones(boneMatrix, 128, BONE_USED_BY_HITBOX, static_cast<float>(GetTickCount64())))
		{
			return Vector(boneMatrix[i][0][3], boneMatrix[i][1][3], boneMatrix[i][2][3]);
		}
		return Vector(0, 0, 0);
	}
};

class C_BaseCombatWeapon : public C_BaseEntity
{
private:
	template <typename T>
	T& read(uintptr_t offset)
	{
		return *reinterpret_cast<T*>(reinterpret_cast<uintptr_t>(this) + offset);
	}

	template <typename T>
	void write(uintptr_t offset, T data)
	{
		*reinterpret_cast<T*>(reinterpret_cast<uintptr_t>(this) + offset) = data;
	}
public:
	NETVAR("DT_BaseCombatWeapon", "m_iItemDefinitionIndex", GetItemDefinitionIndex, short);
	NETVAR("DT_BaseCombatWeapon", "m_flNextPrimaryAttack", GetNextPrimaryAttack, float);
	NETVAR("DT_BaseCombatWeapon", "m_iClip1", GetAmmo, int);

	WeaponInfo_t* GetCSWpnData()
	{
		return Utils::CallVTable< WeaponInfo_t*(__thiscall*)(void*) >(this, 448)(this);
	}

	bool realWeapon()
	{
		short idx = GetItemDefinitionIndex();

		return (idx == WEAPON_C4 || idx == WEAPON_KNIFE || idx == WEAPON_KNIFE_BAYONET || idx == WEAPON_KNIFE_BUTTERFLY || idx == WEAPON_KNIFE_FALCHION
			|| idx == WEAPON_KNIFE_FLIP || idx == WEAPON_KNIFE_GUT || idx == WEAPON_KNIFE_KARAMBIT || idx == WEAPON_KNIFE_M9_BAYONET || idx == WEAPON_KNIFE_PUSH
			|| idx == WEAPON_KNIFE_SURVIVAL_BOWIE || idx == WEAPON_KNIFE_T || idx == WEAPON_KNIFE_TACTICAL || idx == WEAPON_FLASHBANG || idx == WEAPON_HEGRENADE
			|| idx == WEAPON_SMOKEGRENADE || idx == WEAPON_MOLOTOV || idx == WEAPON_DECOY || idx == WEAPON_INCGRENADE || idx == WEAPON_TAGRENADE || idx == WEAPON_FISTS
			|| idx == WEAPON_HEALTHSHOT || idx == WEAPON_BREACHCHARGE || idx == WEAPON_TABLET || idx == WEAPON_MELEE || idx == WEAPON_AXE || idx == WEAPON_HAMMER
			|| idx == WEAPON_SPANNER || idx == WEAPON_KNIFE_GHOST || idx == WEAPON_FIREBOMB || idx == WEAPON_DIVERSION || idx == WEAPON_FRAG_GRENADE || idx == WEAPON_KNIFE_URSUS
			|| idx == WEAPON_KNIFE_GYPSY_JACKKNIFE || idx == WEAPON_KNIFE_STILETTO || idx == WEAPON_KNIFE_WIDOWMAKER);
	}

	char * getIcon()
	{
		switch (GetItemDefinitionIndex())
		{
		case WEAPON_KNIFE_BAYONET:
			return "1";
		case WEAPON_KNIFE_SURVIVAL_BOWIE:
			return "7";
		case WEAPON_KNIFE_BUTTERFLY:
			return "8";
		case WEAPON_KNIFE:
			return "]";
		case WEAPON_KNIFE_FALCHION:
			return "0";
		case WEAPON_KNIFE_FLIP:
			return "2";
		case WEAPON_KNIFE_GUT:
			return "3";
		case WEAPON_KNIFE_KARAMBIT:
			return "4";
		case WEAPON_KNIFE_M9_BAYONET:
			return "5";
		case WEAPON_KNIFE_T:
			return "[";
		case WEAPON_KNIFE_TACTICAL:
			return "6";
		case WEAPON_KNIFE_PUSH:
			return "]";
		case WEAPON_DEAGLE:
			return "A";
		case WEAPON_ELITE:
			return "B";
		case WEAPON_FIVESEVEN:
			return "C";
		case WEAPON_GLOCK:
			return "D";
		case WEAPON_HKP2000:
			return "E";
		case WEAPON_P250:
			return "F";
		case WEAPON_USP_SILENCER:
			return "G";
		case WEAPON_TEC9:
			return "H";
		case WEAPON_REVOLVER:
			return "J";
		case WEAPON_MAC10:
			return "K";
		case WEAPON_UMP45:
			return "L";
		case WEAPON_BIZON:
			return "M";
		case WEAPON_MP7:
			return "N";
		case WEAPON_MP9:
			return "O";
		case WEAPON_P90:
			return "P";
		case WEAPON_GALILAR:
			return "Q";
		case WEAPON_FAMAS:
			return "R";
		case WEAPON_M4A1_SILENCER:
			return "S";
		case WEAPON_M4A1:
			return "T";
		case WEAPON_AUG:
			return "U";
		case WEAPON_SG556:
			return "V";
		case WEAPON_AK47:
			return "W";
		case WEAPON_G3SG1:
			return "X";
		case WEAPON_SCAR20:
			return "Y";
		case WEAPON_AWP:
			return "Z";
		case WEAPON_SSG08:
			return "a";
		case WEAPON_XM1014:
			return "b";
		case WEAPON_SAWEDOFF:
			return "c";
		case WEAPON_MAG7:
			return "d";
		case WEAPON_NOVA:
			return "e";
		case WEAPON_NEGEV:
			return "f";
		case WEAPON_M249:
			return "g";
		case WEAPON_TASER:
			return "h";
		case WEAPON_FLASHBANG:
			return "i";
		case WEAPON_HEGRENADE:
			return "j";
		case WEAPON_SMOKEGRENADE:
			return "k";
		case WEAPON_MOLOTOV:
			return "l";
		case WEAPON_DECOY:
			return "m";
		case WEAPON_INCGRENADE:
			return "n";
		case WEAPON_C4:
			return "o";
		case WEAPON_CZ75A:
			return "I";
		case WEAPON_KNIFE_URSUS:
			return "]";
		case WEAPON_KNIFE_GYPSY_JACKKNIFE:
			return "]";
		case WEAPON_KNIFE_STILETTO:
			return "]";
		case WEAPON_KNIFE_WIDOWMAKER:
			return "]";
		default:
			return "  ";
		}
	}

	char * getNameLowerCase()
	{
		switch (GetItemDefinitionIndex())
		{
		case WEAPON_KNIFE_BAYONET:
			return "bayonet";
		case WEAPON_KNIFE_SURVIVAL_BOWIE:
			return "bowie";
		case WEAPON_KNIFE_BUTTERFLY:
			return "butterfly";
		case WEAPON_KNIFE:
			return "knife";
		case WEAPON_KNIFE_FALCHION:
			return "falchion";
		case WEAPON_KNIFE_FLIP:
			return "flip";
		case WEAPON_KNIFE_GUT:
			return "gut";
		case WEAPON_KNIFE_KARAMBIT:
			return "karambit";
		case WEAPON_KNIFE_M9_BAYONET:
			return "m9 bayonet";
		case WEAPON_KNIFE_T:
			return "knife";
		case WEAPON_KNIFE_TACTICAL:
			return "huntsman";
		case WEAPON_KNIFE_PUSH:
			return "daggers";
		case WEAPON_DEAGLE:
			return "desert eagle";
		case WEAPON_ELITE:
			return "berretas";
		case WEAPON_FIVESEVEN:
			return "fiveseven";
		case WEAPON_GLOCK:
			return "glock";
		case WEAPON_HKP2000:
			return "p2000";
		case WEAPON_P250:
			return "p250";
		case WEAPON_USP_SILENCER:
			return "usp-s";
		case WEAPON_TEC9:
			return "tec9";
		case WEAPON_REVOLVER:
			return "revolver";
		case WEAPON_MAC10:
			return "mac10";
		case WEAPON_UMP45:
			return "ump45";
		case WEAPON_BIZON:
			return "bizon";
		case WEAPON_MP7:
			return "mp7";
		case WEAPON_MP5:
			return "mp5";
		case WEAPON_MP9:
			return "mp9";
		case WEAPON_P90:
			return "p90";
		case WEAPON_GALILAR:
			return "galil";
		case WEAPON_FAMAS:
			return "famas";
		case WEAPON_M4A1_SILENCER:
			return "m4a1-s";
		case WEAPON_M4A1:
			return "m4a4";
		case WEAPON_AUG:
			return "aug";
		case WEAPON_SG556:
			return "sg556";
		case WEAPON_AK47:
			return "ak47";
		case WEAPON_G3SG1:
			return "g3sg1";
		case WEAPON_SCAR20:
			return "scar20";
		case WEAPON_AWP:
			return "awp";
		case WEAPON_SSG08:
			return "scout";
		case WEAPON_XM1014:
			return "xm1014";
		case WEAPON_SAWEDOFF:
			return "sawedoff";
		case WEAPON_MAG7:
			return "mag7";
		case WEAPON_NOVA:
			return "nova";
		case WEAPON_NEGEV:
			return "negev";
		case WEAPON_M249:
			return "m249";
		case WEAPON_TASER:
			return "zeus";
		case WEAPON_FLASHBANG:
			return "flashbang";
		case WEAPON_HEGRENADE:
			return "grenade";
		case WEAPON_SMOKEGRENADE:
			return "smoke";
		case WEAPON_MOLOTOV:
			return "molotov";
		case WEAPON_DECOY:
			return "decoy";
		case WEAPON_INCGRENADE:
			return "incendiary";
		case WEAPON_C4:
			return "bomb";
		case WEAPON_CZ75A:
			return "cz75a";
		case WEAPON_KNIFE_URSUS:
			return "ursus";
		case WEAPON_KNIFE_GYPSY_JACKKNIFE:
			return "navaja";
		case WEAPON_KNIFE_STILETTO:
			return "stiletto";
		case WEAPON_KNIFE_WIDOWMAKER:
			return "talon";
		case WEAPON_TAGRENADE:
			return "tactical awareness nade";
		case WEAPON_HEALTHSHOT:
			return "health shot";
		case WEAPON_FISTS:
			return "fists";
		case WEAPON_BREACHCHARGE:
			return "breach charge";
		case WEAPON_TABLET:
			return "tablet";
		case WEAPON_MELEE:
			return "knife";
		case WEAPON_AXE:
			return "axe";
		case WEAPON_HAMMER:
			return "hammer";
		case WEAPON_SPANNER:
			return "wrench";
		case WEAPON_KNIFE_GHOST:
			return "ghost knife";
		case WEAPON_FIREBOMB:
			return "fire bomb";
		case WEAPON_DIVERSION:
			return "diversion";
		case WEAPON_FRAG_GRENADE:
			return "frag";
		default:
			return "error";
		}
	}
};

