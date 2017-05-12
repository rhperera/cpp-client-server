#pragma once

class ChatMessage
{
public:
	ChatMessage();
	~ChatMessage();
	int getTimestamp();
	void setTimestamp(int &ts);
protected:
private:
	int timestamp;

};