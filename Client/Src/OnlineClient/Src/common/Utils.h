#pragma once

inline bool GetGlobalSetting(int formIDSetting, float *fSetting)
{
	TESGlobal *pGlobalSetting = (TESGlobal *)dyn_cast(::Game::GetFormById(formIDSetting), "TESForm", "TESGlobal");
	if (!pGlobalSetting)
		return 0.0f;
	*fSetting = ::GlobalVariable::GetValue(pGlobalSetting);
	return true;
}

inline bool SetGlobalSetting(int formIDSetting, float fSetting)
{
	TESGlobal *pGlobalSetting = (TESGlobal *)dyn_cast(::Game::GetFormById(formIDSetting), "TESForm", "TESGlobal");
	if (!pGlobalSetting)
		return false;
	::GlobalVariable::SetValue(pGlobalSetting,fSetting);
	return true;
}