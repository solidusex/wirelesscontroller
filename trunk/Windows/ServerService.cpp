// ServerSocket.cpp : implementation file
//

#include "stdafx.h"
#include "WinSrv.h"

#include "NetMessage.h"
#include "ServerService.h"
#include "SendKeys.h"



// CServerSocket

CServerService::CServerService()
{
		m_ar_buf = AR_CreateBuffer(4096);
		
}

CServerService::~CServerService()
{
		AR_DestroyBuffer(m_ar_buf);
}


// CServerSocket member functions

/*

#define WI_PASSWORD             "PWD"
#define WI_EVENT_NAME           "EVT"
#define WI_MOUSE_EVENT_TYPE     "TP"
#define WI_MOUSE_X              "X"
#define WI_MOUSE_Y              "Y"
#define WI_MOUSE_DATA           "D"
*/
void CServerService::OnReceive(int nErrorCode)
{
		
		AR_UNUSED(nErrorCode);

		CString opposite_addr;
		UINT	opposite_port = 0;
		char *pwd = NULL;
		netEvent_t		e;

		int ret = this->ReceiveFrom((void*)m_buf, sizeof(m_buf) * sizeof(byte_t),  opposite_addr, opposite_port);

		if(ret == SOCKET_ERROR )
		{
				AR_LOG(L"read socket failed!\r\n");
				return;
		}

		AR_LOG(L"On net event from %ls : %u\r\n", (const wchar_t*)opposite_addr, opposite_port);
		
		AR_ClearBuffer(m_ar_buf);
		AR_InsertBuffer(m_ar_buf, m_buf, ret);

		
		
		if(m_pwd.GetLength() > 0)
		{
				pwd = AR_wcs_convto_str(AR_CP_ACP, m_pwd.GetString(), m_pwd.GetLength());
		}
		
		if(NetMessage_To_Event(&e, m_ar_buf, pwd) != AR_S_YES)
		{
				if(pwd)
				{
						AR_DEL(pwd);
						pwd = NULL;
				}
				return;
		}
		if(pwd)
		{
				AR_DEL(pwd);
				pwd = NULL;
		}

		switch(e.type)
		{
		case WI_MOUSE_EVENT_T:
		{
				this->on_mouse_event(&e.me);
		}
				break;
		case WI_KEYBOARD_EVENT_T:
		{
				this->on_keyboard_event(&e.ke);
		}
				break;
		case WI_SHORTCUTS_EVENT_T:
		{
				this->on_shortcuts_event(&e.se);
		}
				break;
		case WI_DISCOVERY_REQUEST_EVENT_T:
		{
				this->on_discovery_request_event(&e.discovery_request, opposite_addr, opposite_port);
		}
				break;
		default:
		{
				AR_ASSERT(false);
		}
		}
}


void CServerService::OnSend(int nErrorCode )
{
		AR_UNUSED(nErrorCode);
		
		if(m_output_list.GetCount() > 0)
		{
				SendData *data = m_output_list.RemoveHead();
				if(data)
				{
						this->SendTo(AR_GetBufferData(data->buf), AR_GetBufferAvailable(data->buf), data->opposite_port, data->opposite_addr);
						delete data;
				}
				data = NULL;
		}
}

void	CServerService::SetPassword(const CString &pwd)
{
		m_pwd = pwd;
}

/*
WI_MOUSEMOVE    =       0x0000,
        
        WI_LBUTTONDOWN  =       0x0001,
        WI_LBUTTONUP    =       0x0002,
        WI_LBUTTONDBLCLK=       0x0003,
        
        WI_RBUTTONDOWN  =       0x0004,
        WI_RBUTTONUP    =       0x0005,
        WI_RBUTTONDBLCLK=       0x0006,
        
        WI_MBUTTONDOWN  =       0x0007,
        WI_MBUTTONUP    =       0x0008,
        WI_MBUTTONDBLCLK=       0x0009,
        WI_MOUSEWHEEL   =       0x000A,
        WI_MOUSEHWHEEL  =       0x000B,
        
        WI_MBUTTONSGLCLK=       0x0010,
        WI_LBUTTONSGLCLK=       0x0011,
        WI_RBUTTONSGLCLK=       0x0012,
*/


void	CServerService::on_mouse_event(const mouseEvent_t *me)
{
		AR_ASSERT(me != NULL);

		switch(me->t)
		{
		case WI_MOUSEMOVE:
		{
				mouse_event(MOUSEEVENTF_MOVE, me->x,me->y,0,0);
		}
				break;
		case WI_LBUTTONDOWN:
		{
				mouse_event(MOUSEEVENTF_LEFTDOWN, 0,0,0,0);
		}
				break;
        case WI_LBUTTONUP:
		{
				mouse_event(MOUSEEVENTF_LEFTUP, 0,0,0,0);
		}
				break;
        case WI_LBUTTONDBLCLK:
		{
				mouse_event(MOUSEEVENTF_LEFTDOWN, 0,0,0,0);
				mouse_event(MOUSEEVENTF_LEFTUP, 0,0,0,0);

				mouse_event(MOUSEEVENTF_LEFTDOWN, 0,0,0,0);
				mouse_event(MOUSEEVENTF_LEFTUP, 0,0,0,0);
				
		}
				break;
        case WI_RBUTTONDOWN:
		{
				mouse_event(MOUSEEVENTF_RIGHTDOWN, 0,0,0,0);
		}
				break;
        case WI_RBUTTONUP: 
		{
				mouse_event(MOUSEEVENTF_RIGHTUP, 0,0,0,0);
		}
				break;
        case WI_RBUTTONDBLCLK:
		{
				mouse_event(MOUSEEVENTF_RIGHTDOWN, 0,0,0,0);
				mouse_event(MOUSEEVENTF_RIGHTUP, 0,0,0,0);

				mouse_event(MOUSEEVENTF_RIGHTDOWN, 0,0,0,0);
				mouse_event(MOUSEEVENTF_RIGHTUP, 0,0,0,0);
		}
				break;
        case WI_MBUTTONDOWN:
		{
				mouse_event(MOUSEEVENTF_MIDDLEDOWN, 0,0,0,0);
		}
				break;
        case WI_MBUTTONUP: 
		{
				mouse_event(MOUSEEVENTF_MIDDLEUP, 0,0,0,0);
		}
				break;
        case WI_MBUTTONDBLCLK:
		{
				mouse_event(MOUSEEVENTF_MIDDLEDOWN, 0,0,0,0);
				mouse_event(MOUSEEVENTF_MIDDLEUP, 0,0,0,0);
				mouse_event(MOUSEEVENTF_MIDDLEDOWN, 0,0,0,0);
				mouse_event(MOUSEEVENTF_MIDDLEUP, 0,0,0,0);
		}
				break;
        case WI_MOUSEWHEEL:
		{
				mouse_event(MOUSEEVENTF_WHEEL, 0,0, (DWORD)me->data, 0);
		}
				break;
        case WI_MOUSEHWHEEL:  
		{
				mouse_event(MOUSEEVENTF_HWHEEL, 0,0, (DWORD)me->data, 0);
				
		}
				break;
        case WI_MBUTTONSGLCLK:
		{
				mouse_event(WM_MBUTTONDOWN, 0,0,0,0);
				mouse_event(WM_MBUTTONUP, 0,0,0,0);
		}
				break;
        case WI_LBUTTONSGLCLK:
		{
				mouse_event(MOUSEEVENTF_LEFTDOWN, 0,0,0,0);
				mouse_event(MOUSEEVENTF_LEFTUP, 0,0,0,0);
		}
				break;
        case WI_RBUTTONSGLCLK:
		{
				mouse_event(MOUSEEVENTF_RIGHTDOWN, 0,0,0,0);
				mouse_event(MOUSEEVENTF_RIGHTUP, 0,0,0,0);
		}
				break;
		default:
				AR_printf(L"bad mouse event type\r\n");
				return;
				break;
		}

}



void	CServerService::on_keyboard_event(const keyboardEvent_t *ke)
{
		BYTE vk = 0;
		DWORD flags = 0;
		if(ke->type == WI_FUNCTION_KEY_T)
		{
				switch(ke->func_key)
				{
				case WI_KEY_FUNC_ESC_DONW:
						vk = VK_ESCAPE;
						break;
				case WI_KEY_FUNC_ESC_UP:
						vk = VK_ESCAPE;
						flags |= KEYEVENTF_KEYUP;
						break;
				case WI_KEY_FUNC_CMD_DONW:
						vk = VK_LWIN;
						
						break;
				case WI_KEY_FUNC_CMD_UP:
						vk = VK_LWIN;
						flags |= KEYEVENTF_KEYUP;
						break;
				case WI_KEY_FUNC_CTRL_DONW:
						vk = VK_CONTROL;
						
						break;
				case WI_KEY_FUNC_CTRL_UP:
						vk = VK_CONTROL;
						flags |= KEYEVENTF_KEYUP;
						break;
				case WI_KEY_FUNC_TAB_DONW:
						vk = VK_TAB;
						
						break;
				case WI_KEY_FUNC_TAB_UP:
						vk = VK_TAB;
						flags |= KEYEVENTF_KEYUP;
						break;
				case WI_KEY_FUNC_SHIFT_DONW:
						vk = VK_LSHIFT;
						
						break;
				case WI_KEY_FUNC_SHIFT_UP:
						vk = VK_LSHIFT;
						flags |= KEYEVENTF_KEYUP;
						break;
				case WI_KEY_FUNC_DELETE_DONW:
						vk = VK_DELETE;
						
						break;
				case WI_KEY_FUNC_DELETE_UP:
						vk = VK_DELETE;
						flags |= KEYEVENTF_KEYUP;
						break;
				case WI_KEY_FUNC_INSERT_DONW:
						vk = VK_INSERT;
						
						break;
				case WI_KEY_FUNC_INSERT_UP:
						vk = VK_INSERT;
						flags |= KEYEVENTF_KEYUP;
						break;
				case WI_KEY_FUNC_HOME_DONW:
						vk = VK_HOME;
						
						break;
				case WI_KEY_FUNC_HOME_UP:
						vk = VK_HOME;
						flags |= KEYEVENTF_KEYUP;
						break;
				case WI_KEY_FUNC_END_DONW:
						vk = VK_END;
						
						break;
				case WI_KEY_FUNC_END_UP:
						vk = VK_END;
						flags |= KEYEVENTF_KEYUP;
						break;
				case WI_KEY_FUNC_PAGEDOWN_DONW:
						vk = VK_NEXT;
						
						break;
				case WI_KEY_FUNC_PAGEDOWN_UP:
						vk = VK_NEXT;
						flags |= KEYEVENTF_KEYUP;
						break;
				case WI_KEY_FUNC_PAGEUP_DONW:
						vk = VK_PRIOR;
						
						break;
				case WI_KEY_FUNC_PAGEUP_UP:
						vk = VK_PRIOR;
						flags |= KEYEVENTF_KEYUP;
						break;
				case WI_KEY_FUNC_BACKSPACE_DONW:
						vk = VK_BACK;
						
						break;
				case WI_KEY_FUNC_BACKSPACE_UP:
						vk = VK_BACK;
						flags |= KEYEVENTF_KEYUP;
						break;
				case WI_KEY_FUNC_ALT_DONW:
						vk = VK_MENU;
						
						break;
				case WI_KEY_FUNC_ALT_UP:
						vk = VK_MENU;
						flags |= KEYEVENTF_KEYUP;
						break;
				case WI_KEY_FUNC_UP_DONW:
						vk = VK_UP;
						flags |= KEYEVENTF_EXTENDEDKEY;
						break;
				case WI_KEY_FUNC_UP_UP:
						vk = VK_UP;
						flags |= KEYEVENTF_KEYUP;
						flags |= KEYEVENTF_EXTENDEDKEY;
						break;
				case WI_KEY_FUNC_DOWN_DONW:
						vk = VK_DOWN;
						flags |= KEYEVENTF_EXTENDEDKEY;
						break;
				case WI_KEY_FUNC_DOWN_UP:
						vk = VK_DOWN;
						flags |= KEYEVENTF_EXTENDEDKEY;
						flags |= KEYEVENTF_KEYUP;
						break;
				case WI_KEY_FUNC_LEFT_DONW:
						vk = VK_LEFT;
						flags |= KEYEVENTF_EXTENDEDKEY;
						break;
				case WI_KEY_FUNC_LEFT_UP:
						vk = VK_LEFT;
						flags |= KEYEVENTF_EXTENDEDKEY;
						flags |= KEYEVENTF_KEYUP;
						break;
				case WI_KEY_FUNC_RIGHT_DONW:
						vk = VK_RIGHT;
						flags |= KEYEVENTF_EXTENDEDKEY;
						break;
				case WI_KEY_FUNC_RIGHT_UP:
						vk = VK_RIGHT;
						flags |= KEYEVENTF_EXTENDEDKEY;
						flags |= KEYEVENTF_KEYUP;
						break;
				default:
						AR_LOG(L"bad function key type\r\n");
						break;
				}
				keybd_event(vk, MapVirtualKeyA(vk,0), flags, 0);
		}else if(ke->type == WI_ASCII_KEY_T)
		{
				CSendKeys		sk;
				/*
				wchar_t buf[2] = {(BYTE)ke->ascii, 0};
				sk.SendKeys(buf);
				*/

				sk.SendChar(ke->ascii);

		}else if(ke->type == WI_TEXT_T)
		{

		}else
		{
				AR_ASSERT(false);
		}
}



void	CServerService::on_shortcuts_event(const shortcutsEvent_t *se)
{
		
}



bool_t AR_GetIPByHostName_V4(const wchar_t *host_name, struct sockaddr_in *out)
{
		ADDRINFOW		*res;
		ADDRINFOW		hints;
		static const wchar_t *serv = L"0";
		const ADDRINFOW *curr;
		int err;
		AR_ASSERT(host_name != NULL && out != NULL);

		memset(&hints, 0, sizeof(ADDRINFOW));
		hints.ai_family = AF_INET;
		hints.ai_protocol = AF_UNSPEC;
		hints.ai_flags = AI_CANONNAME;
		
		err = GetAddrInfoW(host_name, serv, &hints, &res);
		if(err != 0 || res == NULL)
		{
				return false;
		}

		curr = res;
		while(curr)
		{
				struct sockaddr_in *addr;
				err = GetNameInfoW((struct sockaddr*)curr->ai_addr, sizeof(struct	 sockaddr_in),  NULL, 0, NULL, 0, NI_NUMERICHOST);
				addr = (struct sockaddr_in *)(curr->ai_addr);
				if(err == 0)
				{
						AR_memcpy(out, addr, sizeof(*out));
						break;
				}else
				{
						curr = curr->ai_next;
				}
		}
		FreeAddrInfoW(res);
		return curr != NULL;
}


void	CServerService::on_discovery_request_event(const discoveryRequestEvent_t *se, const CString &opposite_addr, UINT opposite_port)
{
		AR_LOG(L"on_discovery_request_event\r\n");

		/*
		char buf[1024];
		::gethostname(buf, 1024);

		wchar_t *host_name = AR_str_convto_wcs(AR_CP_ACP, buf, strlen(buf));

		struct sockaddr_in addr;
		
		if(AR_GetIPByHostName_V4(host_name, &addr))
		{
				const char *s = inet_ntoa(addr.sin_addr);
				AR_LOG(L"%hs\r\n", s);
				discoveryReplyEvent_t reply;
				memset(&reply, 0, sizeof(reply));
				
				AR_strcpy(reply.ip, s);
				reply.port = 
				DiscoveryReplyEvent_To_NetMessage
		}

		
		if(host_name)
		{
				AR_DEL(host_name);
				host_name = NULL;
		}
		*/

		CString addr;
		UINT port;
		if(this->GetSockName(addr, port))
		{
				AR_LOG(L"local address = %ls : %u\r\n", addr.GetString(), port);

				discoveryReplyEvent_t reply;
				memset(&reply, 0, sizeof(reply));
				sprintf(reply.ip, "%ls", addr.GetString());
				reply.port = port;
				
				arBuffer_t *buf = DiscoveryReplyEvent_To_NetMessage(&reply);
				SendData *data = new SendData;
				
				data->buf = buf;
				data->opposite_addr = opposite_addr;
				data->opposite_port = opposite_port;

				m_output_list.AddTail(data);
				this->AsyncSelect(FD_READ|FD_WRITE);
		}
}
