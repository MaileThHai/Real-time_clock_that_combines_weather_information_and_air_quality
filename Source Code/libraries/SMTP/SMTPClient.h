#ifndef __SMTP_CLIENT_H
#define __SMTP_CLIENT_H




#include "WiFiEspClient.h"




class SMTPClient: public WiFiEspClient
{
	public:

		// Construction, destruction and initialisation
		SMTPClient();
		~SMTPClient();


		// Interface
		bool connect(IPAddress ip);
		bool connect(const char *strHost);

		void setFrom(const char* str);
		void setTo(const char* str);
		void setUsername(const char* str);
		void setPassword(const char* str);
		void setSubject(const char* str);
		void setContent(const char* str);
		void setDateTime(const char* str);

		void setFrom(const __FlashStringHelper* str);
		void setTo(const __FlashStringHelper* str);
		void setUsername(const __FlashStringHelper* str);
		void setPassword(const __FlashStringHelper* str);
		void setSubject(const __FlashStringHelper* str);
		void setContent(const __FlashStringHelper* str);

		bool sendEmail();
		const char* getSendStatus()
		{
			return m_strSendStatus;
		};

	protected:

		// Data
		static const uint16_t m_nTimeout = 1000;
		static const uint8_t m_nMaxXLong = 100;
		static const uint8_t m_nMaxLong = 50;
		static const uint8_t m_nMaxShort = 20;

		char m_strFromEmail[m_nMaxLong], m_strToEmail[m_nMaxLong], 
			 m_strUsername[m_nMaxShort], m_strPassword[m_nMaxShort], m_strTemp[m_nMaxShort],
			 m_strSubject[m_nMaxLong], m_strContent[m_nMaxXLong],
			 m_strSendStatus[m_nMaxLong], m_strDateTime[m_nMaxShort];
		

		// Helper functions
		bool doFail();
		bool waitAck();
		size_t write(const __FlashStringHelper* str);
		void copy(const char* strSrc, char* strDest, const uint16_t nMaxLenDest);
		void copy(const __FlashStringHelper* strSrc, char* strDest, const uint16_t nMaxLenDest);

};




#endif