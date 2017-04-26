#ifndef __CHATMESSAGE_H_INCLUDED__
#define __CHATMESSAGE_H_INCLUDED__

class ChatMessage
{
private:
	int timestamp;
public:
	ChatMessage();
	~ChatMessage();
	int getTimestamp();
	void setTimestamp(int &ts);

};

#endif