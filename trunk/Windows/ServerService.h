#pragma once


// CServerSocket command target

class SendData
{
public:
		arBuffer_t		*buf;
		CString			opposite_addr;
		UINT			opposite_port;
public:
		~SendData()
		{
				if(buf)
				{
						AR_DestroyBuffer(buf);
						buf = NULL;
				}
		}
};

class CServerService : public CAsyncSocket
{
		byte_t					m_buf[4096];
		ARSpace::arBuffer_t		*m_ar_buf;
		
		CList<SendData*>	m_output_list;

		CString					m_pwd;
public:
		CServerService();
		virtual ~CServerService();

protected:
		void	on_mouse_event(const mouseEvent_t *me);
		void	on_keyboard_event(const keyboardEvent_t *ke);
		void	on_shortcuts_event(const shortcutsEvent_t *se);
		void	on_discovery_request_event(const discoveryRequestEvent_t *se, const CString &opposite_addr, UINT opposite_port);
public:
		virtual void OnReceive(int nErrorCode);
		virtual void OnSend(int nErrorCode );
public:
		void	SetPassword(const CString &pwd);

};


