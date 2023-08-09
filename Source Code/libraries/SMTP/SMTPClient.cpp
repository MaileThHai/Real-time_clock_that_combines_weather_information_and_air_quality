#include <Arduino.h>
#include <Base64.h>
#include "SMTPClient.h"




// Construction, destruction and initialisation
SMTPClient::SMTPClient()
{
	memset(m_strFromEmail, 0, m_nMaxLong);
	memset(m_strToEmail, 0, m_nMaxLong);
	memset(m_strUsername, 0, m_nMaxShort);
	memset(m_strPassword, 0, m_nMaxShort);
	memset(m_strTemp, 0, m_nMaxShort);
	memset(m_strSubject, 0, m_nMaxLong);
	memset(m_strContent, 0, m_nMaxXLong);
	memset(m_strSendStatus, 0, m_nMaxLong);
	memset(m_strDateTime, 0, m_nMaxShort);
}

SMTPClient::~SMTPClient()
{
}

// Interface
bool SMTPClient::connect(IPAddress ip)
{
	return (WiFiEspClient::connect(ip, 25) > 0) && waitAck();
}

bool SMTPClient::connect(const char *strHost)
{
	return (WiFiEspClient::connect(strHost, 25) > 0) && waitAck();
}

bool SMTPClient::sendEmail()
{
	bool bResult = false;

	if (connected())
	{
		write(F("AUTH LOGIN\r\n"));
		if (waitAck())
		{
			memset(m_strTemp, 0, m_nMaxShort);
			base64_decode(m_strTemp, m_strUsername, strlen(m_strUsername));
			strcat_P(m_strTemp, (PGM_P)F("\r\n"));
			
			WiFiEspClient::write(m_strTemp);
			if (waitAck())
			{
				memset(m_strTemp, 0, m_nMaxShort);
				base64_decode(m_strTemp, m_strPassword, strlen(m_strPassword));
				strcat_P(m_strTemp, (PGM_P)F("\r\n"));
				
				WiFiEspClient::write(m_strTemp);
				if (waitAck())
				{
					strcpy_P(m_strTemp, (PGM_P)F("MAIL From: <"));
					strcat(m_strTemp, m_strFromEmail);
					strcat_P(m_strTemp, (PGM_P)F(">\r\n"));
					WiFiEspClient::write(m_strTemp);
					if (waitAck())
					{
						strcpy_P(m_strTemp, (PGM_P)F("RCPT To: <"));
						strcat(m_strTemp, m_strToEmail);
						strcat_P(m_strTemp, (PGM_P)F(">\r\n"));
						WiFiEspClient::write(m_strTemp);
						if (waitAck())
						{
							write(F("DATA\r\n"));
							if (waitAck())
							{
								strcpy_P(m_strTemp, (PGM_P)F("To: <"));
								strcat(m_strTemp, m_strToEmail);
								strcat_P(m_strTemp, (PGM_P)F(">\r\n"));
								WiFiEspClient::write(m_strTemp);

								strcpy_P(m_strTemp, (PGM_P)F("From: Irrigation controller <"));
								strcat(m_strTemp, m_strFromEmail);
								strcat_P(m_strTemp, (PGM_P)F(">\r\n"));
								WiFiEspClient::write(m_strTemp);

								strcpy_P(m_strTemp, (PGM_P)F("Sent: "));
								strcat(m_strTemp, m_strDateTime);
								strcat_P(m_strTemp, (PGM_P)F("\r\n"));
								WiFiEspClient::write(m_strTemp);

								write(F("Subject: Soil moisture alarms triggered\r\n\r\n"));
								WiFiEspClient::write(m_strContent);
								write(F("\r\n.\r\n"));
								if (waitAck())
								{
									write(F("QUIT\r\n"));
									if (waitAck())
									{
										stop();
										bResult = true;
										strcpy_P(m_strSendStatus, (PGM_P)F("SMTPClient::sendEmail(): email sent!"));
									}
									else
										strcpy_P(m_strSendStatus, (PGM_P)F("ERROR in SMTPClient::sendEmail(): no response to QUIT!"));
								}
								else
									strcpy_P(m_strSendStatus, (PGM_P)F("ERROR in SMTPClient::sendEmail(): no response to DATA content!"));
							}
							else
								strcpy_P(m_strSendStatus, (PGM_P)F("ERROR in SMTPClient::sendEmail(): no response to DATA!"));
						}
						else
							strcpy_P(m_strSendStatus, (PGM_P)F("ERROR in SMTPClient::sendEmail(): no response to RCPT To: <...>!"));
					}
					else
						strcpy_P(m_strSendStatus, (PGM_P)F("ERROR in SMTPClient::sendEmail(): no response to MAIL From: <>!"));
				}
				else
					strcpy_P(m_strSendStatus, (PGM_P)F("ERROR in SMTPClient::sendEmail(): no response to password!"));
			}
			else
				strcpy_P(m_strSendStatus, (PGM_P)F("ERROR in SMTPClient::sendEmail(): no response to user name!"));
		}
		else
			strcpy_P(m_strSendStatus, (PGM_P)F("ERROR in SMTPClient::sendEmail(): no response to AUTH LOGIN!"));
	}
	else
		strcpy_P(m_strSendStatus, (PGM_P)F("ERROR in SMTPClient::sendEmail(): not connected!"));

	return bResult;
}

void SMTPClient::copy(const char* strSrc, char* strDest, const uint16_t nMaxLenDest)
{
	memset(strDest, 0, nMaxLenDest);
	strncpy(strDest, strSrc, nMaxLenDest);
}

void SMTPClient::setDateTime(const char* strDateTime)
{
	copy(strDateTime, m_strDateTime, m_nMaxShort);
}

void SMTPClient::setFrom(const char* str)
{
	copy(str, m_strFromEmail, m_nMaxLong);
}

void SMTPClient::setTo(const char* str)
{
	copy(str, m_strToEmail, m_nMaxLong);
}

void SMTPClient::setUsername(const char* str)
{
	copy(str, m_strUsername, m_nMaxLong);
}

void SMTPClient::setPassword(const char* str)
{
	copy(str, m_strPassword, m_nMaxLong);
}

void SMTPClient::setSubject(const char* str)
{
	copy(str, m_strSubject, m_nMaxLong);
}

void SMTPClient::setContent(const char* str)
{
	copy(str, m_strContent, m_nMaxLong);
}

void SMTPClient::copy(const __FlashStringHelper* strSrc, char* strDest, const uint16_t nMaxLenDest)
{
	memset(strDest, 0, nMaxLenDest);
	for (uint16_t nI = 0, nLen = strlen_P((PGM_P)strSrc); nI < nLen; nI++)
	{
		if (nI >= nMaxLenDest)
			break;
		strDest[nI] = pgm_read_byte((PGM_P)strSrc + nI);
	}
}

void SMTPClient::setFrom(const __FlashStringHelper* str)
{
	copy(str, m_strFromEmail, m_nMaxLong);
}

void SMTPClient::setTo(const __FlashStringHelper* str)
{
	copy(str, m_strToEmail, m_nMaxLong);
}

void SMTPClient::setUsername(const __FlashStringHelper* str)
{
	copy(str, m_strUsername, m_nMaxLong);
}

void SMTPClient::setPassword(const __FlashStringHelper* str)
{
	copy(str, m_strPassword, m_nMaxLong);
}

void SMTPClient::setSubject(const __FlashStringHelper* str)
{
	copy(str, m_strSubject, m_nMaxLong);
}

void SMTPClient::setContent(const __FlashStringHelper* str)
{
	copy(str, m_strContent, m_nMaxLong);
}

// Helper functions
size_t SMTPClient::write(const __FlashStringHelper* str)
{
	for (uint16_t nI = 0, nLen = strlen_P((PGM_P)str); nI < nLen; nI++)
		WiFiEspClient::write(pgm_read_byte((PGM_P)str + nI));
}

bool SMTPClient::waitAck()
{
  bool bResult = true;
  uint8_t nResponse;
  int16_t nCount = 0;
 
  while (!available())
  {
    delay(1);
    nCount++;
 
    // If nothing received for 10 seconds, timeout
    if (nCount > m_nTimeout) 
    {
      stop();
      bResult = false;
      break;
    }
  }
  if (bResult)
  {
    nResponse = peek();
   
    while (available())
    {  
       nResponse = read();    
    }    
    if (nResponse >= '4')
    {
      doFail();
      bResult = false; 
    }
  }
  return bResult;
}

bool SMTPClient::doFail()
{
  uint8_t nResponse = 0;
  int16_t nCount = 0;
  bool bResult = true;
 
  write(F("QUIT\r\n"));
 
  while(!available()) 
  {
    delay(1);
    nCount++;
 
    // If nothing received for 10 seconds, timeout
    if (nCount > m_nTimeout) 
    {
      stop();
      bResult = false;
      break;
    }
  }
  if (bResult)
  {
    while (available())
    {  
      nResponse = read();    
    }
    stop();
  }
  return bResult;
}



