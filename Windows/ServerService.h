#pragma once


// CServerSocket command target


class CServerService : public CAsyncSocket
{
		byte_t					m_buf[4096];
		ARSpace::arBuffer_t		*m_ar_buf;
		CString					m_pwd;

public:
		CServerService();
		virtual ~CServerService();

protected:
		void	on_mouse_event(const mouseEvent_t *me);
		void	on_keyboard_event(const keyboardEvent_t *ke);
		void	on_shortcuts_event(const shortcutsEvent_t *se);
public:
		virtual void OnReceive(int nErrorCode);
		virtual void OnSend(int nErrorCode );
public:
		void	SetPassword(const CString &pwd);

};


