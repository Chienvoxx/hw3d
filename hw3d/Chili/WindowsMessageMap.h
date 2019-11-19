#pragma once
#include <unordered_map>
// Swapping Windows.h  -> ChiliWin.h causes several of the DWORD constants to be undefined
#include <Windows.h>
//#include "ChiliWin.h"


/*
	Pattern for WM_MESSAGES taken from Cihlitomatonoodle's video series 3D DirectX Tutorial
	and in particular the git commmit "sexy WM_ logging" 335287f06ae198ca21adada11f012d7016d397d5
	The implementation is my own.
*/
class WindowsMessageMap
{
public:
	WindowsMessageMap() noexcept;
	std::string operator()(DWORD msg, LPARAM lp, WPARAM wp) const noexcept;

private:
	std::unordered_map<DWORD, std::string> map;
};