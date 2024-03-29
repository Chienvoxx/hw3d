#include "WindowsMessageMap.h"
#include <string>
#include <sstream>
#include <iomanip>
#include <bitset>



std::string WindowsMessageMap::operator()(DWORD msg, LPARAM lp, WPARAM wp) const noexcept
{
	constexpr int col1 = 35;
	constexpr int col2 = 8;
	constexpr int col3 = 11;
	const auto i = map.find(msg);

	std::ostringstream oss;
	if (i != map.end())
	{
		oss << std::left << std::setw(col1) << i->second;
		oss << "0x" << std::left << std::setw(col2) << std::hex << std::setfill('0') << std::right << i->first;
	}
	else
	{
		oss << std::left << std::setw(col1) << "not found";
		oss << "0x" << std::left << std::setw(col2) << std::hex << std::setfill('0') << std::right << msg;
	}

	/* LP Hex */
	//oss << std::setfill(' ');
	//oss << std::right << std::setw(col3) << "LP: ";
	//oss << "0x" << std::left << std::setw(col2) << std::hex << std::setfill('0') << std::right << lp;
	//oss << std::setfill(' ');
	/* LP Binary */
	////std::bitset<32> l(lp);
	////oss << std::right << std::setw(2) << " ";
	////oss << std::left << std::setw(col2) << l;

	/* WP Hex */
	//oss << std::right << std::setw(col3) << "WP: ";
	//oss << "0x" << std::left << std::setw(col2) << std::hex << std::setfill('0') << std::right << wp;
	//oss << std::setfill(' ');
	/* WP Binary */
	////std::bitset<32> w(wp);
	////oss << std::right << std::setw(2) << " ";
	////oss << std::left << std::setw(col2) << w;
	
	oss << "\n";
	return oss.str();
}

#define ADD_MSG(msg) {msg,#msg}

WindowsMessageMap::WindowsMessageMap() noexcept
{
	map = std::unordered_map<DWORD, std::string>
	{
		ADD_MSG(WM_ACTIVATE),
		ADD_MSG(WM_ACTIVATEAPP),
		ADD_MSG(WM_AFXFIRST),
		ADD_MSG(WM_AFXLAST),
		ADD_MSG(WM_APPCOMMAND),
		ADD_MSG(WM_ASKCBFORMATNAME),
		ADD_MSG(WM_CANCELJOURNAL),
		ADD_MSG(WM_CANCELMODE),
		ADD_MSG(WM_CAPTURECHANGED),
		ADD_MSG(WM_CHANGECBCHAIN),
		ADD_MSG(WM_CHANGEUISTATE),
		ADD_MSG(WM_CHAR),
		ADD_MSG(WM_CHARTOITEM),
		ADD_MSG(WM_CHILDACTIVATE),
		ADD_MSG(WM_CLEAR),
		ADD_MSG(WM_CLIPBOARDUPDATE),
		ADD_MSG(WM_CLOSE),
		ADD_MSG(WM_COMMAND),
		ADD_MSG(WM_COMMNOTIFY),
		ADD_MSG(WM_COMPACTING),
		ADD_MSG(WM_COMPAREITEM),
		ADD_MSG(WM_CONTEXTMENU),
		ADD_MSG(WM_COPY),
		ADD_MSG(WM_COPYDATA),
		ADD_MSG(WM_CREATE),
		ADD_MSG(WM_CTLCOLORBTN),
		ADD_MSG(WM_CTLCOLORDLG),
		ADD_MSG(WM_CTLCOLOREDIT),
		ADD_MSG(WM_CTLCOLORLISTBOX),
		ADD_MSG(WM_CTLCOLORMSGBOX),
		ADD_MSG(WM_CTLCOLORSCROLLBAR),
		ADD_MSG(WM_CTLCOLORSTATIC),
		ADD_MSG(WM_CUT),
		ADD_MSG(WM_DEADCHAR),
		ADD_MSG(WM_DELETEITEM),
		ADD_MSG(WM_DESTROY),
		ADD_MSG(WM_DESTROYCLIPBOARD),
		ADD_MSG(WM_DEVICECHANGE),
		ADD_MSG(WM_DEVMODECHANGE),
		ADD_MSG(WM_DISPLAYCHANGE),
		ADD_MSG(WM_DPICHANGED),
		ADD_MSG(WM_DRAWCLIPBOARD),
		ADD_MSG(WM_DRAWITEM),
		ADD_MSG(WM_DROPFILES),
		ADD_MSG(WM_DWMCOLORIZATIONCOLORCHANGED),
		ADD_MSG(WM_DWMCOMPOSITIONCHANGED),
		ADD_MSG(WM_DWMNCRENDERINGCHANGED),
		ADD_MSG(WM_DWMSENDICONICLIVEPREVIEWBITMAP),
		ADD_MSG(WM_DWMSENDICONICTHUMBNAIL),
		ADD_MSG(WM_DWMWINDOWMAXIMIZEDCHANGE),
		ADD_MSG(WM_ENABLE),
		ADD_MSG(WM_ENDSESSION),
		ADD_MSG(WM_ENTERIDLE),
		ADD_MSG(WM_ENTERMENULOOP),
		ADD_MSG(WM_ENTERSIZEMOVE),
		ADD_MSG(WM_ERASEBKGND),
		ADD_MSG(WM_EXITMENULOOP),
		ADD_MSG(WM_EXITSIZEMOVE),
		ADD_MSG(WM_FONTCHANGE),
		ADD_MSG(WM_GESTURE),
		ADD_MSG(WM_GESTURENOTIFY),
		ADD_MSG(WM_GETDLGCODE),
		ADD_MSG(WM_GETFONT),
		ADD_MSG(WM_GETHOTKEY),
		ADD_MSG(WM_GETICON),
		ADD_MSG(WM_GETMINMAXINFO),
		ADD_MSG(WM_GETOBJECT),
		ADD_MSG(WM_GETTEXT),
		ADD_MSG(WM_GETTEXTLENGTH),
		ADD_MSG(WM_GETTITLEBARINFOEX),
		ADD_MSG(WM_HANDHELDFIRST),
		ADD_MSG(WM_HANDHELDLAST),
		ADD_MSG(WM_HELP),
		ADD_MSG(WM_HOTKEY),
		ADD_MSG(WM_HSCROLL),
		ADD_MSG(WM_HSCROLLCLIPBOARD),
		ADD_MSG(WM_ICONERASEBKGND),
		ADD_MSG(WM_IME_CHAR),
		ADD_MSG(WM_IME_COMPOSITION),
		ADD_MSG(WM_IME_COMPOSITIONFULL),
		ADD_MSG(WM_IME_CONTROL),
		ADD_MSG(WM_IME_ENDCOMPOSITION),
		ADD_MSG(WM_IME_KEYDOWN),
		ADD_MSG(WM_IME_KEYUP),
		ADD_MSG(WM_IME_NOTIFY),
		ADD_MSG(WM_IME_REQUEST),
		ADD_MSG(WM_IME_SELECT),
		ADD_MSG(WM_IME_SETCONTEXT),
		ADD_MSG(WM_IME_STARTCOMPOSITION),
		ADD_MSG(WM_INITDIALOG),
		ADD_MSG(WM_INITMENU),
		ADD_MSG(WM_INITMENUPOPUP),
		ADD_MSG(WM_INPUT),
		ADD_MSG(WM_INPUT_DEVICE_CHANGE),
		ADD_MSG(WM_INPUTLANGCHANGE),
		ADD_MSG(WM_INPUTLANGCHANGEREQUEST),
		ADD_MSG(WM_KEYDOWN),
		ADD_MSG(WM_KEYUP),
		ADD_MSG(WM_KILLFOCUS),
		ADD_MSG(WM_LBUTTONDBLCLK),
		ADD_MSG(WM_LBUTTONDOWN),
		ADD_MSG(WM_LBUTTONUP),
		ADD_MSG(WM_MBUTTONDBLCLK),
		ADD_MSG(WM_MBUTTONDOWN),
		ADD_MSG(WM_MBUTTONUP),
		ADD_MSG(WM_MDIACTIVATE),
		ADD_MSG(WM_MDICASCADE),
		ADD_MSG(WM_MDICREATE),
		ADD_MSG(WM_MDIDESTROY),
		ADD_MSG(WM_MDIGETACTIVE),
		ADD_MSG(WM_MDIICONARRANGE),
		ADD_MSG(WM_MDIMAXIMIZE),
		ADD_MSG(WM_MDINEXT),
		ADD_MSG(WM_MDIREFRESHMENU),
		ADD_MSG(WM_MDIRESTORE),
		ADD_MSG(WM_MDISETMENU),
		ADD_MSG(WM_MDITILE),
		ADD_MSG(WM_MEASUREITEM),
		ADD_MSG(WM_MENUCHAR),
		ADD_MSG(WM_MENUCOMMAND),
		ADD_MSG(WM_MENUDRAG),
		ADD_MSG(WM_MENUGETOBJECT),
		ADD_MSG(WM_MENURBUTTONUP),
		ADD_MSG(WM_MENUSELECT),
		ADD_MSG(WM_MOUSEACTIVATE),
		ADD_MSG(WM_MOUSEHOVER),
		ADD_MSG(WM_MOUSEHWHEEL),
		ADD_MSG(WM_MOUSELEAVE),
		ADD_MSG(WM_MOUSEMOVE),
		ADD_MSG(WM_MOUSEWHEEL),
		ADD_MSG(WM_MOVE),
		ADD_MSG(WM_MOVING),
		ADD_MSG(WM_NCACTIVATE),
		ADD_MSG(WM_NCCALCSIZE),
		ADD_MSG(WM_NCCREATE),
		ADD_MSG(WM_NCDESTROY),
		ADD_MSG(WM_NCHITTEST),
		ADD_MSG(WM_NCLBUTTONDBLCLK),
		ADD_MSG(WM_NCLBUTTONDOWN),
		ADD_MSG(WM_NCLBUTTONUP),
		ADD_MSG(WM_NCMBUTTONDBLCLK),
		ADD_MSG(WM_NCMBUTTONDOWN),
		ADD_MSG(WM_NCMBUTTONUP),
		ADD_MSG(WM_NCMOUSEHOVER),
		ADD_MSG(WM_NCMOUSELEAVE),
		ADD_MSG(WM_NCMOUSEMOVE),
		ADD_MSG(WM_NCPAINT),
		ADD_MSG(WM_NCPOINTERDOWN),
		ADD_MSG(WM_NCPOINTERUP),
		ADD_MSG(WM_NCPOINTERUPDATE),
		ADD_MSG(WM_NCRBUTTONDBLCLK),
		ADD_MSG(WM_NCRBUTTONDOWN),
		ADD_MSG(WM_NCRBUTTONUP),
		ADD_MSG(WM_NCXBUTTONDBLCLK),
		ADD_MSG(WM_NCXBUTTONDOWN),
		ADD_MSG(WM_NCXBUTTONUP),
		ADD_MSG(WM_NEXTDLGCTL),
		ADD_MSG(WM_NEXTMENU),
		ADD_MSG(WM_NOTIFY),
		ADD_MSG(WM_NOTIFYFORMAT),
		ADD_MSG(WM_NULL),
		ADD_MSG(WM_PAINT),
		ADD_MSG(WM_PAINTCLIPBOARD),
		ADD_MSG(WM_PAINTICON),
		ADD_MSG(WM_PALETTECHANGED),
		ADD_MSG(WM_PALETTEISCHANGING),
		ADD_MSG(WM_PARENTNOTIFY),
		ADD_MSG(WM_PASTE),
		ADD_MSG(WM_PENWINFIRST),
		ADD_MSG(WM_PENWINLAST),
		ADD_MSG(WM_POINTERACTIVATE),
		ADD_MSG(WM_POINTERCAPTURECHANGED),
		ADD_MSG(WM_POINTERDEVICECHANGE),
		ADD_MSG(WM_POINTERDEVICEINRANGE),
		ADD_MSG(WM_POINTERDEVICEOUTOFRANGE),
		ADD_MSG(WM_POINTERDOWN),
		ADD_MSG(WM_POINTERENTER),
		ADD_MSG(WM_POINTERHWHEEL),
		ADD_MSG(WM_POINTERLEAVE),
		ADD_MSG(WM_POINTERUP),
		ADD_MSG(WM_POINTERUPDATE),
		ADD_MSG(WM_POINTERWHEEL),
		ADD_MSG(WM_POWER),
		ADD_MSG(WM_POWERBROADCAST),
		ADD_MSG(WM_PRINT),
		ADD_MSG(WM_PRINTCLIENT),
		ADD_MSG(WM_QUERYDRAGICON),
		ADD_MSG(WM_QUERYENDSESSION),
		ADD_MSG(WM_QUERYNEWPALETTE),
		ADD_MSG(WM_QUERYOPEN),
		ADD_MSG(WM_QUERYUISTATE),
		ADD_MSG(WM_QUEUESYNC),
		ADD_MSG(WM_QUIT),
		ADD_MSG(WM_RBUTTONDBLCLK),
		ADD_MSG(WM_RBUTTONDOWN),
		ADD_MSG(WM_RBUTTONUP),
		ADD_MSG(WM_RENDERALLFORMATS),
		ADD_MSG(WM_RENDERFORMAT),
		ADD_MSG(WM_SETCURSOR),
		ADD_MSG(WM_SETFOCUS),
		ADD_MSG(WM_SETFONT),
		ADD_MSG(WM_SETHOTKEY),
		ADD_MSG(WM_SETICON),
		ADD_MSG(WM_SETREDRAW),
		ADD_MSG(WM_SETTEXT),
		ADD_MSG(WM_SHOWWINDOW),
		ADD_MSG(WM_SIZE),
		ADD_MSG(WM_SIZECLIPBOARD),
		ADD_MSG(WM_SIZING),
		ADD_MSG(WM_SPOOLERSTATUS),
		ADD_MSG(WM_STYLECHANGED),
		ADD_MSG(WM_STYLECHANGING),
		ADD_MSG(WM_SYNCPAINT),
		ADD_MSG(WM_SYSCHAR),
		ADD_MSG(WM_SYSCOLORCHANGE),
		ADD_MSG(WM_SYSCOMMAND),
		ADD_MSG(WM_SYSDEADCHAR),
		ADD_MSG(WM_SYSKEYDOWN),
		ADD_MSG(WM_SYSKEYUP),
		ADD_MSG(WM_TABLET_FIRST),
		ADD_MSG(WM_TABLET_LAST),
		ADD_MSG(WM_TCARD),
		ADD_MSG(WM_THEMECHANGED),
		ADD_MSG(WM_TIMECHANGE),
		ADD_MSG(WM_TIMER),
		ADD_MSG(WM_TOUCH),
		ADD_MSG(WM_TOUCHHITTESTING),
		ADD_MSG(WM_UNDO),
		ADD_MSG(WM_UNICHAR),
		ADD_MSG(WM_UNINITMENUPOPUP),
		ADD_MSG(WM_UPDATEUISTATE),
		ADD_MSG(WM_USERCHANGED),
		ADD_MSG(WM_VKEYTOITEM),
		ADD_MSG(WM_VSCROLL),
		ADD_MSG(WM_VSCROLLCLIPBOARD),
		ADD_MSG(WM_WINDOWPOSCHANGED),
		ADD_MSG(WM_WINDOWPOSCHANGING),
		ADD_MSG(WM_WININICHANGE),
		ADD_MSG(WM_WTSSESSION_CHANGE),
		ADD_MSG(WM_XBUTTONDBLCLK),
		ADD_MSG(WM_XBUTTONDOWN),
		ADD_MSG(WM_XBUTTONUP)
	};
}

