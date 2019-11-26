#pragma once
#include "ChiliWin.h"
#include <wrl.h>
#include <vector>
#include <dxgidebug.h>

/*	Adding wrl.h anywhere causes 2 errors wherever the wrl code is used. Even for the following code
		#include <wrl.h>
		Int WINAPI WinMain<(HINSTANCE, HINSTATNCE, LPSTR, int) {}
	In my case, I included it in two files which caused 5 files to use it, so it generated 10 total errors.
	Error	C7510	'Callback': use of dependent template name must be prefixed with 'template' (compiling source file Chili\DxgiInfoManager.cpp)
		c:\program files (x86)\windows kits\10\include\10.0.17134.0\winrt\wrl\event.h	316
	Error	C7510	'Callback': use of dependent template name must be prefixed with 'template' (compiling source file Chili\DxgiInfoManager.cpp)
		c:\program files (x86)\windows kits\10\include\10.0.17134.0\winrt\wrl\event.h	324
	
	In a comment in early November 2019 Chili said that he ran into this problem at some point and the solution was to update the compiler.
		It didn't work for me.
	The commenter he was responding to says he got the answer from StackOverflow,
	"you can get rid of it by going to the project properties -> C/C++ ->Language -> Conformance mode -> No."
		This did work for me.
*/

class DxgiInfoManager
{
public:
	DxgiInfoManager();
	~DxgiInfoManager() = default;
	DxgiInfoManager(const DxgiInfoManager&) = delete;
	DxgiInfoManager& operator=(const DxgiInfoManager&) = delete;
	void Set() noexcept;
	std::vector<std::string> GetMessages() const;
private:
	unsigned long long next = 0u;
	Microsoft::WRL::ComPtr<IDXGIInfoQueue> pDxgiInfoQueue;
};