// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#pragma once
#define DLL_DUI
#include <dui\duistd.h>

// include Lua libs

#ifdef _DEBUG

#if defined(WIN32)
#pragma comment(lib,"lua-win32-debug-static.lib")
#endif

	#if defined(USING_ATL)
	# pragma comment(lib, "duiengine-win32-debug_atl.lib")
	#elif defined(DLL_DUI)
	# pragma comment(lib, "duiengine-win32-debug_shared.lib")
	#else
	# pragma comment(lib, "duiengine-win32-debug_static.lib")
	#endif
#else

#if defined(WIN32)
#pragma comment(lib,"lua-win32-release-static.lib")
#endif

	#if defined(USING_ATL)
	# pragma comment(lib, "duiengine-win32-release_atl.lib")
	#elif defined(DLL_DUI)
	# pragma comment(lib, "duiengine-win32-release_shared.lib")
	#else
	# pragma comment(lib, "duiengine-win32-release_static.lib")
	#endif

#endif

